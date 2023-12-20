//==========================================
//
//  �s�k���b�Z�[�W(message_lose.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "message_lose.h"
#include "manager.h"
#include "texture.h"
#include "camera.h"
#include "calculation.h"
#include "glass.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const char* TEXPASS = "data\\TEXTURE\\result\\lose.png"; // �e�N�X�`���t�@�C���p�X
	const D3DXVECTOR3 DEF_POS = D3DXVECTOR3(0.0f, 0.0f, 2000.0f); // �J��������̑��Ώ����ʒu
	const D3DXVECTOR3 DIFF_POS = D3DXVECTOR3(0.0f, 0.0f, 100.0f); // �J��������̑��ΖړI�n
	const D3DXVECTOR3 LOGO_SIZE = D3DXVECTOR3(64.0f, 32.0f, 0.0f); //�|���S���T�C�Y
	const float MOVE_SPEED = 5.0f; // a * x ^ �ɂ�����萔a
}

//==========================================
//  �R���X�g���N�^
//==========================================
CMessageLose::CMessageLose() :
	m_fSec(0.0f),
	m_bMove(false)
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
	HRESULT hr = CObject3D::Init();

	// ��ނ�ݒ�
	CObject::SetType(CObject::TYPE_OBJECT3D);

	// �e�N�X�`���̊��蓖��
	BindTexture(CManager::GetInstance()->GetTexture()->Regist(TEXPASS));

	// ���S�̈ʒu��ݒ�
	SetPosition(CManager::GetInstance()->GetCamera()->GetPositionV() + DEF_POS);
	D3DXVECTOR3 pos = GetPosition();

	// ���S�̃T�C�Y��ݒ�
	SetSize(LOGO_SIZE);

	//�l��Ԃ�
	return hr;
}

//==========================================
//  �I������
//==========================================
void CMessageLose::Uninit(void)
{
	// �I��
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CMessageLose::Update(void)
{
	/// �ړ�
	if (!m_bMove)
	{
		Move();
	}

	// �X�V
	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CMessageLose::Draw(void)
{
	// �`��
	CObject3D::Draw();
}

//==========================================
//  ��������
//==========================================
CMessageLose* CMessageLose::Create()
{
	// �C���X�^���X����
	CMessageLose* pLose = DEBUG_NEW CMessageLose;

	// NULL�`�F�b�N
	if (pLose == nullptr) { return nullptr; }

	// ����������
	pLose->Init();

	// �l��Ԃ�
	return pLose;
}

//==========================================
//  �ړ�
//==========================================
void CMessageLose::Move()
{
	// �o�ߎ��Ԃ����Z
	m_fSec += CManager::GetInstance()->GetDeltaTime() * MOVE_SPEED;

	// �ʒu���擾
	D3DXVECTOR3 pos = GetPosition();

	// �ʒu���X�V
	pos.z -= m_fSec * m_fSec;

	// �ʒu��␳
	if ((CManager::GetInstance()->GetCamera()->GetPositionV() + DIFF_POS).z > pos.z)
	{
		pos = CManager::GetInstance()->GetCamera()->GetPositionV() + DIFF_POS;

		// �ړ������t���O���I��
		m_bMove = true;

		// �Ђъ���𐶐�
		CGlass::Create();
	}

	if (m_bMove)
	{
		CManager::GetInstance()->GetCamera()->SetShake(20, 10.0f, 0.0f);
	}

	// �ʒu��K�p
	SetPosition(pos);
}
