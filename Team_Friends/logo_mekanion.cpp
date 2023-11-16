//==========================================
//
//  ���J�j�I���̃��S(logo_mekanion.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "logo_mekanion.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "input.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CLogo_Meka::CLogo_Meka()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CLogo_Meka::~CLogo_Meka()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CLogo_Meka::Init(void)
{
	//����������
	HRESULT hr = CLogo::Init();

	//�e�N�X�`���̊��蓖��
	this->BindTexture(CManager::GetInstance()->GetTexture()->Regist(m_apTextureFile[1]));

	return hr;
}

//==========================================
//  �I������
//==========================================
void CLogo_Meka::Uninit(void)
{
	//�I��
	CLogo::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CLogo_Meka::Update(void)
{
	// �L�[�{�[�h���擾
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_6))
	{
		//�e�N�X�`���̊��蓖��
		this->BindTexture(CManager::GetInstance()->GetTexture()->Regist(m_apTextureFile[1]));
	}
	if (pInputKeyboard->GetTrigger(DIK_7))
	{
		//�e�N�X�`���̊��蓖��
		this->BindTexture(CManager::GetInstance()->GetTexture()->Regist(m_apTextureFile[4]));
	}

#ifdef _DEBUG
	if (pInputKeyboard->GetTrigger(DIK_2))
	{
		SetComplete(true);
	}
#endif

	//�X�V
	CLogo::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CLogo_Meka::Draw(void)
{
	//�`��
	CLogo::Draw();
}

//==========================================
//  ��������
//==========================================
CLogo_Meka* CLogo_Meka::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CLogo_Meka* pLogo = DEBUG_NEW CLogo_Meka;

	//����������
	pLogo->Init();

	//�l��ݒ�
	pLogo->SetPosition(pos);
	pLogo->SetRotation(rot);

	return pLogo;
}
