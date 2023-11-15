//==========================================
//
//  �^�C�g�����S(title_logo.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "title_logo.h"
#include "logo_complete.h"
#include "logo_mechanion.h"

#include "manager.h"
#include "input.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CTitleLogo::CTitleLogo()
{
	m_pMech = nullptr;
	m_pComp = nullptr;
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
	//MECHANION���S��\��
	if (m_pMech == nullptr)
	{
		m_pMech = CLogo_Mech::Create(D3DXVECTOR3(0.0f, 200.0f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	//�^�C�v�̐ݒ�
	SetType(TYPE_OBJECT3D);

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
	// �L�[�{�[�h���擾
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

#ifdef _DEBUG
	if (pInputKeyboard->GetTrigger(DIK_SPACE))
	{
		//�����������S��\��
		if (m_pComp == nullptr)
		{
			m_pComp = CLogo_Comp::Create(D3DXVECTOR3(0.0f, 200.0f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_1))
	{
		//MECHANION���S��j��
		if (m_pMech != nullptr)
		{
			m_pMech->Uninit();
			m_pMech = nullptr;
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
