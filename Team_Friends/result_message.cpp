//==========================================
//
//  ���U���g���b�Z�[�W(result_message.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "result_message.h"
#include "manager.h"
#include "texture.h"
#include "camera.h"
#include "message_lose.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 DIFF_POS = D3DXVECTOR3(0.0f, 0.0f, 40.0f); // �ʒu
	const D3DXVECTOR3 MESSAGE_SIZE = D3DXVECTOR3(6.0f, 6.0f, 0.0f); // �T�C�Y
}

//==========================================
//  �R���X�g���N�^
//==========================================
CResultMessage::CResultMessage()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CResultMessage::~CResultMessage()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CResultMessage::Init(void)
{
	// ����������
	HRESULT hr = CLogo::Init();

	// �^�C�v�̐ݒ�
	SetType(CObject::TYPE_OBJECT3D);

	//���S�̈ʒu��ݒ�
	SetPosition(CManager::GetInstance()->GetCamera()->GetPositionV() + DIFF_POS);

	// ���S�̃T�C�Y��ݒ�
	SetSize(MESSAGE_SIZE);

	return hr;
}

//==========================================
//  �I������
//==========================================
void CResultMessage::Uninit(void)
{
	CLogo::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CResultMessage::Update(void)
{
	CLogo::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CResultMessage::Draw(void)
{
	CLogo::Draw();
}

//==========================================
//  ��������
//==========================================
CResultMessage* CResultMessage::Create(bool bClear)
{
	// �ϐ��錾
	CResultMessage* pMessage = nullptr;

	// �C���X�^���X����
	if (bClear) { pMessage = nullptr; }
	else { pMessage = DEBUG_NEW CMessageLose; }

	// NULL�`�F�b�N
	if (pMessage == nullptr) { return nullptr; }

	// ����������
	pMessage->Init();

	// �l��Ԃ�
	return pMessage;
}
