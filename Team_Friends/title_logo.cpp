//==========================================
//
//  �^�C�g�����S(title_logo.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "title_logo.h"
#include "logo_complete.h"
#include "logo_mechanion.h"
#include "logo_mekanion.h"
#include "logo_squadron.h"

#include "manager.h"
#include "input.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CTitleLogo::CTitleLogo()
{
	m_pMech = nullptr;
	m_pMeka = nullptr;
	m_pSqou = nullptr;
	m_pComp = nullptr;
	m_State = DEFAULT;
	m_bComplete = false;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CTitleLogo::~CTitleLogo()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CTitleLogo::Init(void)
{
	//�^�C�v�̐ݒ�
	SetType(TYPE_OBJECT3D);

	//MECHANION���S��\��
	if (m_pMech == nullptr)
	{
		m_pMech = CLogo_Mech::Create(D3DXVECTOR3(0.0f, 200.0f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CTitleLogo::Uninit(void)
{	 
	//MECHANION���S��j��
	if (m_pMech != nullptr)
	{
		m_pMech->Uninit();
		m_pMech = nullptr;
	}

	//���J�j�I�����S��j��
	if (m_pMeka != nullptr)
	{
		m_pMeka->Uninit();
		m_pMeka = nullptr;
	}

	//������S��j��
	if (m_pSqou != nullptr)
	{
		m_pSqou->Uninit();
		m_pSqou = nullptr;
	}

	//�����������S��j��
	if (m_pComp != nullptr)
	{
		m_pComp->Uninit();
		m_pComp = nullptr;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//==========================================
//  �X�V����
//==========================================
void CTitleLogo::Update(void)
{	
	//��ԍX�V
	UpdateState();

	//�f�o�b�O�p�֐�
	DebugFunction();
}

//==========================================
//  �`�揈��
//==========================================
void CTitleLogo::Draw(void)
{

}

//==========================================
//  ��������
//==========================================
CTitleLogo* CTitleLogo::Create()
{
	//�C���X�^���X����
	CTitleLogo* pLogo = DEBUG_NEW CTitleLogo;

	//����������
	pLogo->Init();

	return pLogo;
}

//==========================================
//  ��Ԃ��X�V
//==========================================
void CTitleLogo::UpdateState()
{
	//�������Ă��Ȃ��Ƃ�
	if (!m_bComplete)
	{
		switch (m_State)
		{
		case DEFAULT: // MECHANION�����Ȃ�

			if (m_pMech != nullptr && m_pMech->GetComplete())
			{
				//���J�j�I�����S��\��
				if (m_pMeka == nullptr)
				{
					m_pMeka = CLogo_Meka::Create(D3DXVECTOR3(0.0f, 200.0f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}

				//��Ԃ�i�߂�
				m_State = WAKE;
			}
			break;

		case WAKE: // ���J�j�I���܂ŏo�Ă�

			if (m_pMeka != nullptr && m_pMeka->GetComplete())
			{
				//������S��\��
				if (m_pSqou == nullptr)
				{
					m_pSqou = CLogo_Sqou::Create(D3DXVECTOR3(0.0f, 200.0f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}

				//��Ԃ�i�߂�
				m_State = FLASH;
			}
			break;

		case FLASH: //����܂ŏo�Ă�

			if (m_pSqou != nullptr && m_pSqou->GetComplete())
			{
				//MECHANION���S��j��
				if (m_pMech != nullptr)
				{
					m_pMech->Uninit();
					m_pMech = nullptr;
				}

				//���J�j�I�����S��j��
				if (m_pMeka != nullptr)
				{
					m_pMeka->Uninit();
					m_pMeka = nullptr;
				}

				//������S��j��
				if (m_pSqou != nullptr)
				{
					m_pSqou->Uninit();
					m_pSqou = nullptr;
				}

				//�����������S��\��
				if (m_pComp == nullptr)
				{
					m_pComp = CLogo_Comp::Create(D3DXVECTOR3(0.0f, 200.0f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}

				//��Ԃ�i�߂�
				m_State = COMPLETE;
			}
			break;

		case COMPLETE: // �������Ă���
			m_bComplete = true; // �^�C�g�����S������
			break;

		default:
			break;
		}
	}
}

//==========================================
//  �f�o�b�O�p�̏������l�߂��֐�
//==========================================
void CTitleLogo::DebugFunction()
{
	// �L�[�{�[�h���擾
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

#ifdef _DEBUG

	if (pInputKeyboard->GetTrigger(DIK_5))
	{
		//MECHANION���S��j��
		if (m_pMech != nullptr)
		{
			m_pMech->Uninit();
			m_pMech = nullptr;
		}

		//���J�j�I�����S��j��
		if (m_pMeka != nullptr)
		{
			m_pMeka->Uninit();
			m_pMeka = nullptr;
		}

		//������S��j��
		if (m_pSqou != nullptr)
		{
			m_pSqou->Uninit();
			m_pSqou = nullptr;
		}

		//�����������S��j��
		if (m_pComp != nullptr)
		{
			m_pComp->Uninit();
			m_pComp = nullptr;
		}
	}

#endif
}
