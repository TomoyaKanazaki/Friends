//==========================================
//
//  �s�k���b�Z�[�W(message_lose.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "message_lose.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CMessageLose::CMessageLose()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CMessageLose::~CMessageLose()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CMessageLose::Init(void)
{
	// ������
	HRESULT hr = CResultMessage::Init();

	// �e�N�X�`���̊��蓖��
	BindTexture(CManager::GetInstance()->GetTexture()->Regist(m_apTextureFile[5]));

	//�l��Ԃ�
	return hr;
}

//==========================================
//  �I������
//==========================================
void CMessageLose::Uninit(void)
{
	// �I��
	CResultMessage::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CMessageLose::Update(void)
{
	// �X�V
	CResultMessage::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CMessageLose::Draw(void)
{
	// �`��
	CResultMessage::Draw();
}
