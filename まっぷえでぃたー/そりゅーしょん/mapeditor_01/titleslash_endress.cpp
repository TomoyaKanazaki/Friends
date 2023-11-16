//=============================================================================
// 
//  �^�C�g���̎a������ [titleslash_endress.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "titleslash_endress.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "object2D.h"
#include "calculation.h"
#include "titleslash.h"

//==========================================================================
// �}�N����`
//==========================================================================
#define LOGO_POSITION		(D3DXVECTOR3(640.0f, 200.0f, 0.0f))		// �����ʒu
#define LOGOSIZE_MULTIPLY	(0.55f)									// ���S�T�C�Y�̔{��
#define MAX_LIFE			(40)									// ����
#define DEST_LOGOALPHA		(D3DXVECTOR3(250.0f, -120.0f, 0.0f))	// �ڕW�̈ʒu

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
const char *CTitleSlashEndress::m_apTextureFile[VTX_LOGO_MAX] =			// �e�N�X�`���̃t�@�C��
{
	"data\\TEXTURE\\titlelogo_02.png",
	"data\\TEXTURE\\titlelogo_02.png",
	"data\\TEXTURE\\titlelogo_01.png",
};

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CTitleSlashEndress::CTitleSlashEndress(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	memset(&m_pObj2D[0], NULL, sizeof(m_pObj2D));	// �I�u�W�F�N�g2D�̃I�u�W�F�N�g
	memset(&m_nTexIdx[0], 0, sizeof(m_nTexIdx));	// �e�N�X�`���̃C���f�b�N�X�ԍ�
	m_nLife = 0;									// ����
	m_DestSize = D3DXVECTOR2(0.0f, 0.0f);			// �ڕW�̃T�C�Y
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CTitleSlashEndress::~CTitleSlashEndress()
{

}

//==========================================================================
// ��������
//==========================================================================
CTitleSlashEndress *CTitleSlashEndress::Create(void)
{
	// �����p�̃I�u�W�F�N�g
	CTitleSlashEndress *pTitleScreen = NULL;

	if (pTitleScreen == NULL)
	{// NULL��������

		// �������̊m��
		pTitleScreen = DEBUG_NEW CTitleSlashEndress;

		if (pTitleScreen != NULL)
		{// �������̊m�ۂ��o���Ă�����

			// ����������
			pTitleScreen->Init();
		}

		return pTitleScreen;
	}

	return NULL;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CTitleSlashEndress::Init(void)
{
	// ��ނ̐ݒ�
	SetType(TYPE_OBJECT2D);

	// ����
	m_nLife = MAX_LIFE;

	for (int nCntSelect = 0; nCntSelect < VTX_LOGO_MAX; nCntSelect++)
	{
		// ��������
		m_pObj2D[nCntSelect] = CObject2D::Create(8);

		// ��ނ̐ݒ�
		m_pObj2D[nCntSelect]->SetType(TYPE_OBJECT2D);

		// �e�N�X�`���̊��蓖��
		m_nTexIdx[nCntSelect] = CManager::GetInstance()->GetTexture()->Regist(m_apTextureFile[nCntSelect]);

		// �e�N�X�`���̊��蓖��
		m_pObj2D[nCntSelect]->BindTexture(m_nTexIdx[nCntSelect]);

		D3DXVECTOR2 size;
		// �e��ϐ��̏�����
		switch (nCntSelect)
		{
		case VTX_LOGOALPHA1:
			// �T�C�Y�擾
			size = CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx[nCntSelect]);
			m_pObj2D[nCntSelect]->SetSize(size * LOGOSIZE_MULTIPLY);	// �T�C�Y
			m_pObj2D[nCntSelect]->SetPosition(LOGO_POSITION);	// �ʒu
			m_pObj2D[nCntSelect]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));	// �F
			break;

		case VTX_LOGOALPHA2:
			// �T�C�Y�擾
			size = CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx[nCntSelect]);
			m_pObj2D[nCntSelect]->SetSize(size * LOGOSIZE_MULTIPLY);	// �T�C�Y
			m_pObj2D[nCntSelect]->SetPosition(LOGO_POSITION);	// �ʒu
			m_pObj2D[nCntSelect]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));	// �F
			break;

		case VTX_LOGOPERFECTALPHA:
			// �T�C�Y�擾
			size = CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx[nCntSelect]);
			m_pObj2D[nCntSelect]->SetSize(size * LOGOSIZE_MULTIPLY);	// �T�C�Y
			m_DestSize = size * 1.2f;									// �ڕW�̃T�C�Y
			m_pObj2D[nCntSelect]->SetPosition(LOGO_POSITION);	// �ʒu
			m_pObj2D[nCntSelect]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f));	// �F
			break;
		}
	}

	// �e�N�X�`�����擾
	CTexture *pTexture = CManager::GetInstance()->GetTexture();
	int nTex = pTexture->Regist("data\\TEXTURE\\title_slash.png");

	// �a������
	CTitleSlash::Create(LOGO_POSITION);

	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CTitleSlashEndress::Uninit(void)
{
	for (int nCntSelect = 0; nCntSelect < VTX_LOGO_MAX; nCntSelect++)
	{
		if (m_pObj2D[nCntSelect] != NULL)
		{// NULL����Ȃ�������

			// �I������
			m_pObj2D[nCntSelect] = NULL;
		}
	}

	// ���폜
	Release();
}

//==========================================================================
// �X�V����
//==========================================================================
void CTitleSlashEndress::Update(void)
{

	// �a���X�V
	UpdateSlash();

	for (int nCntSelect = 0; nCntSelect < VTX_LOGO_MAX; nCntSelect++)
	{
		if (m_pObj2D[nCntSelect] == NULL)
		{// NULL��������
			continue;
		}

		// ���_���ݒ�
		m_pObj2D[nCntSelect]->SetVtx(nCntSelect);
	}

	if (m_nLife < 0)
	{
		for (int nCntSelect = 0; nCntSelect < VTX_LOGO_MAX; nCntSelect++)
		{
			if (m_pObj2D[nCntSelect] != NULL)
			{// NULL����Ȃ�������

				// �I������
				m_pObj2D[nCntSelect]->Uninit();
				m_pObj2D[nCntSelect] = NULL;
			}
		}

		// �I������
		Uninit();
	}
}

//==========================================================================
// �a���X�V
//==========================================================================
void CTitleSlashEndress::UpdateSlash()
{
	// �������Z
	m_nLife--;

	for (int nCntSelect = 0; nCntSelect < VTX_LOGO_MAX; nCntSelect++)
	{
		if (m_pObj2D[nCntSelect] == NULL)
		{// NULL��������
			continue;
		}

		// �F�擾
		D3DXCOLOR col = m_pObj2D[nCntSelect]->GetColor();
		D3DXVECTOR2 size = m_pObj2D[nCntSelect]->GetSize();

		if (nCntSelect == VTX_LOGOALPHA1 ||
			nCntSelect == VTX_LOGOALPHA2)
		{
			// �����̏���
			UpdateSlashAlpha(nCntSelect);
			continue;
		}
		else if (nCntSelect == VTX_LOGOPERFECTALPHA)
		{
			// �T�C�Y���Z
			size += (m_DestSize - size) * 0.1f;

			// �F
			col.a = 0.15f * ((float)m_nLife / (float)MAX_LIFE);
		}

		// �F�ݒ�
		m_pObj2D[nCntSelect]->SetColor(col);
		m_pObj2D[nCntSelect]->SetSize(size);
	}
}

//==========================================================================
// �����̎a���X�V
//==========================================================================
void CTitleSlashEndress::UpdateSlashAlpha(int nCntSelect)
{
	// ���擾
	D3DXCOLOR col = m_pObj2D[nCntSelect]->GetColor();
	D3DXVECTOR3 pos = m_pObj2D[nCntSelect]->GetPosition();

	// �ڕW�̈ʒu
	D3DXVECTOR3 posDiff = DEST_LOGOALPHA;
	if (nCntSelect != 0)
	{
		posDiff.x *= -1;
		posDiff.y *= -1;
	}
	D3DXVECTOR3 posDest = LOGO_POSITION + posDiff;

	// �F
	col.a = 0.3f * ((float)m_nLife / (float)MAX_LIFE);

	// �ʒu�X�V
	pos += (posDest - pos) * 0.1f;

	// ���ݒ�
	m_pObj2D[nCntSelect]->SetColor(col);
	m_pObj2D[nCntSelect]->SetPosition(pos);

}

//==========================================================================
// ���S�̍X�V����
//==========================================================================
void CTitleSlashEndress::UpdateLogo(int nCntSelect)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = m_pObj2D[nCntSelect]->GetPosition();


	// �ʒu�ݒ�
	m_pObj2D[nCntSelect]->SetPosition(pos);
}

//==========================================================================
// �`�揈��
//==========================================================================
void CTitleSlashEndress::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	for (int nCntSelect = 0; nCntSelect < VTX_LOGO_MAX; nCntSelect++)
	{
		// �`�揈��
		m_pObj2D[nCntSelect]->Draw();
	}

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

