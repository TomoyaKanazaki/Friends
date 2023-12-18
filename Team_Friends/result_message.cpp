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

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 DIFF_POS = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
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
	// �C���X�^���X����
	CResultMessage* pMessage = DEBUG_NEW CResultMessage;

	// NULL�`�F�b�N
	if (pMessage == nullptr) { return nullptr; }

	// �e�N�X�`���̊��蓖��
	if (bClear)
	{
		pMessage->BindTexture(CManager::GetInstance()->GetTexture()->Regist(m_apTextureFile[7]));
	}
	else
	{
		pMessage->BindTexture(CManager::GetInstance()->GetTexture()->Regist(m_apTextureFile[6]));
	}

	// ����������
	pMessage->Init();

	// �l��Ԃ�
	return pMessage;
}
