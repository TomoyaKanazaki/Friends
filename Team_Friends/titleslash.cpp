//=============================================================================
// 
// �^�C�g���a������ [titleslash.cpp]
// Author : ���n�Ή�
// 
//=============================================================================
#include "titleslash.h"
#include "renderer.h"
#include "texture.h"
#include "manager.h"
#include "sound.h"

//==========================================================================
// �}�N����`
//==========================================================================
#define TEXTURE	"data\\TEXTURE\\title_slash.png"
#define LIFE	(8)
#define FADEOUT	(40)

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CTitleSlash::CTitleSlash(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
	m_nLife = 0;								// ����
	m_nMaxLife = 0;								// �ő����(�Œ�)
	m_nTexIdx = 0;		// �e�N�X�`���̃C���f�b�N�X�ԍ�
	m_fMaxWidth = 0.0f;		// �ő�̉���
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CTitleSlash::~CTitleSlash()
{

}

//==========================================================================
// ��������
//==========================================================================
CTitleSlash *CTitleSlash::Create(const D3DXVECTOR3 pos)
{
	// �����p�̃I�u�W�F�N�g
	CTitleSlash *pEffect = NULL;

	if (pEffect == NULL)
	{// NULL��������

		// �������̊m��
		pEffect = DEBUG_NEW CTitleSlash;

		if (pEffect != NULL)
		{// �������̊m�ۂ��o���Ă�����

			// �^�C�g���a��
			CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_TITLESLASH);

			// ����������
			pEffect->Init();

			// �T�C�Y�擾
			D3DXVECTOR2 size = CManager::GetInstance()->GetTexture()->GetImageSize(pEffect->m_nTexIdx) * 0.5f;
			pEffect->m_fMaxWidth = size.x;
			pEffect->SetSize(D3DXVECTOR2(0.0f, size.y));	// �T�C�Y�ݒ�
			pEffect->SetPosition(D3DXVECTOR3(pos.x - size.x, pos.y, pos.z));
		}

		return pEffect;
	}

	return NULL;
}

//==================================================================================
// ����������
//==================================================================================
HRESULT CTitleSlash::Init(void)
{
	HRESULT hr;

	// ����������
	hr = CObject2D::Init();
	if (FAILED(hr))
	{// ���s�����Ƃ�
		return E_FAIL;
	}

	// ��ނ̐ݒ�
	SetType(TYPE_EFFECT2D);

	// �e�N�X�`���̊��蓖��
	m_nTexIdx = CManager::GetInstance()->GetTexture()->Regist(TEXTURE);

	// �e�N�X�`���̊��蓖��
	BindTexture(m_nTexIdx);

	// �e��ϐ��̏�����
	m_nLife = LIFE;		// ����
	m_nMaxLife = LIFE;	// �ő����

	return S_OK;
}

//==================================================================================
// �I������
//==================================================================================
void CTitleSlash::Uninit(void)
{
	// �I������
	CObject2D::Uninit();
}

//==================================================================================
// �X�V����
//==================================================================================
void CTitleSlash::Update(void)
{

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// �F�擾
	D3DXCOLOR col = GetColor();

	// �������Z
	m_nLife--;

	if (m_nLife <= 0)
	{// ������0�����������

		// �s�����x�v�Z
		col.a = ((float)FADEOUT - fabsf((float)m_nLife)) / (float)FADEOUT;

		SetColor(col);

		if (m_nLife <= -FADEOUT)
		{
			Uninit();
			return;
		}
	}

	// ���_���W�̐ݒ�
	SetVtx();
}

//==================================================================================
// �`�揈��
//==================================================================================
void CTitleSlash::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// �`�揈��
	CObject2D::Draw();

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//==========================================================================
// ���_���ݒ菈��
//==========================================================================
void CTitleSlash::SetVtx(void)
{
	// �e�N�X�`�����W�擾
	D3DXVECTOR2 *pTex = GetTex();

	int nLife = m_nLife;
	if (nLife <= 0)
	{
		nLife = 0;
	}

	// �e�N�X�`���̊��������߂�
	float fTex = 1.0f - ((float)nLife / (float)LIFE);

	// �e�N�X�`�����W�v�Z
	pTex[0] = D3DXVECTOR2(0.0f, 0.0f);
	pTex[1] = D3DXVECTOR2(fTex, 0.0f);
	pTex[2] = D3DXVECTOR2(0.0f, 1.0f);
	pTex[3] = D3DXVECTOR2(fTex, 1.0f);

	// ���_�ݒ�
	CObject2D::SetVtx();

	// ���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR2 size = GetSize();

	// �T�C�Y�ݒ�
	size.x = (1.0f - ((float)nLife / (float)LIFE)) * m_fMaxWidth;

	SetSize(size);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x + 0.0f, pos.y + -size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x * 2.0f, pos.y + -size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x + 0.0f, pos.y + size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x * 2.0f, pos.y + size.y, 0.0f);

	// ���_�o�b�t�@���A�����b�N���b�N
	GetVtxBuff()->Unlock();

}

