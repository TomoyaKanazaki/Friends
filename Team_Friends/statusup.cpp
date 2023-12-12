//=============================================================================
// 
// �X�e�[�^�X�A�b�v���� [statusup.cpp]
// Author : ���n�Ή�
// 
//=============================================================================
#include "statusup.h"
#include "renderer.h"
#include "texture.h"
#include "manager.h"
#include "calculation.h"

//==========================================================================
// �}�N����`
//==========================================================================
namespace
{
	const char* TEXTURE[CGameManager::STATUS_MAX] =
	{
		"data\\TEXTURE\\status\\statusup_power.png",
		"data\\TEXTURE\\status\\statusup_speed.png",
		"data\\TEXTURE\\status\\statusup_life.png",
	};
	const int MAX_LIFE = 40;			// ����
	const int TIME_FADEOUT = 20;		// �t�F�[�h�A�E�g����
	const float DISTANCE = 200.0f;		// �Ԋu
	const float DESTSIZE_RATIO = 0.07f;	// �ڕW�̃T�C�Y����
}

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
int CStatusUp::m_nTexIdx[CGameManager::STATUS_MAX] = {};	// �e�N�X�`���̃C���f�b�N�X�ԍ�

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CStatusUp::CStatusUp(int nPriority) : CObjectBillboard(nPriority)
{
	// �l�̃N���A
	m_nLife = 0;							// ����
	m_type = CGameManager::STATUS_POWER;	// ���
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CStatusUp::~CStatusUp()
{
	
}

//==========================================================================
// �e�N�X�`���ǂݍ���
//==========================================================================
void CStatusUp::LoadTexture(void)
{
	// �e�N�X�`���̓ǂݍ���
	for (int nCntTex = 0; nCntTex < CGameManager::STATUS_MAX; nCntTex++)
	{// �e�N�X�`���f�[�^�̔z�񕪌J��Ԃ�
		m_nTexIdx[nCntTex] = CManager::GetInstance()->GetTexture()->Regist(TEXTURE[nCntTex]);
	}
}

//==========================================================================
// ��������
//==========================================================================
CStatusUp *CStatusUp::Create(const D3DXVECTOR3 pos, CGameManager::eStatus type)
{
	// �����p�̃I�u�W�F�N�g
	CStatusUp *pEffect = NULL;

	if (pEffect == NULL)
	{// NULL��������

		// �������̊m��
		pEffect = DEBUG_NEW CStatusUp;

		if (pEffect != NULL)
		{// �������̊m�ۂ��o���Ă�����

			// ���
			pEffect->m_type = type;

			// �ʒu�ݒ�
			pEffect->SetPosition(pos);
			pEffect->SetOriginPosition(pos);

			// ����������
			pEffect->Init();
		}

		return pEffect;
	}

	return NULL;
}

//==================================================================================
// ����������
//==================================================================================
HRESULT CStatusUp::Init(void)
{
	HRESULT hr;

	// ��ނ̐ݒ�
	SetType(TYPE_OBJECTBILLBOARD);

	// �e�N�X�`���̊��蓖��
	if (m_nTexIdx[m_type] == 0)
	{
		m_nTexIdx[m_type] = CManager::GetInstance()->GetTexture()->Regist(TEXTURE[m_type]);
	}

	// �e�N�X�`���̊��蓖��
	BindTexture(m_nTexIdx[m_type]);

	// ����������
	hr = CObjectBillboard::Init();
	if (FAILED(hr))
	{// ���s�����Ƃ�

		Uninit();
		return E_FAIL;
	}

	// �T�C�Y�ݒ�
	SetSize(mylib_const::DEFAULT_VECTOR2);
	m_nLife = MAX_LIFE;	// ����

	return S_OK;
}

//==================================================================================
// �I������
//==================================================================================
void CStatusUp::Uninit(void)
{
	
	// �I������
	CObjectBillboard::Uninit();
}

//==================================================================================
// �X�V����
//==================================================================================
void CStatusUp::Update(void)
{
	// �ߋ��̈ʒu�ݒ�
	SetOldPosition(GetPosition());

	// �ړ�����
	UpdateMove();

	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	// �T�C�Y�擾
	D3DXVECTOR2 size = GetSize();

	// �����␳
	InertiaCorrection(size.x, pTexture->GetImageSize(m_nTexIdx[m_type]).x * DESTSIZE_RATIO, 0.15f);
	InertiaCorrection(size.y, pTexture->GetImageSize(m_nTexIdx[m_type]).y * DESTSIZE_RATIO, 0.15f);

	// �T�C�Y�ݒ�
	SetSize(size);

	// �����̍X�V
	m_nLife--;

	if (m_nLife <= 0)
	{// �������s������
		
		// �F�擾
		D3DXCOLOR col = GetColor();

		// �s�����x�̍X�V
		col.a = (float)(m_nLife + TIME_FADEOUT) / (float)TIME_FADEOUT;

		// �F�ݒ�
		SetColor(col);

		if (m_nLife <= -TIME_FADEOUT)
		{// �������s������

			// �폜
			Uninit();
			return;
		}
	}

	// ���_���W�̐ݒ�
	SetVtx();

}

//==================================================================================
// �ړ�����
//==================================================================================
void CStatusUp::UpdateMove(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �����␳
	InertiaCorrection(pos.y, GetOriginPosition().y + DISTANCE, 0.15f);

	// �ʒu�ݒ�
	SetPosition(pos);
}

//==================================================================================
// �`�揈��
//==================================================================================
void CStatusUp::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �`�揈��
	CObjectBillboard::Draw();

	// ���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}