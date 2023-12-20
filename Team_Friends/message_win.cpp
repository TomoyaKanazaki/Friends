//==========================================
//
//  �������b�Z�[�W(message_win.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "message_win.h"
#include "manager.h"
#include "texture.h"
#include "camera.h"
#include "calculation.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const char* TEXPASS[2] = // �e�N�X�`���t�@�C���p�X
	{
		"data\\TEXTURE\\result\\perfect.png",
		"data\\TEXTURE\\result\\win.png"
	};
	const D3DXVECTOR3 DEF_POS = D3DXVECTOR3(1000.0f, 0.0f, 100.0f); // �J��������̑��Ώ����ʒu
	const D3DXVECTOR3 DIFF_POS = D3DXVECTOR3(51.2f, 0.0f, 150.0f); // �J��������̑��ΖړI�n
	const D3DXVECTOR3 LOGO_SIZE = D3DXVECTOR3(51.2f, 27.2f, 0.0f); //�|���S���T�C�Y
	const float MOVE_SPEED = 5.0f; // (a * x) ^ n�ɂ�����萔a
}

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
int CMessageWin::nIdx = 0;

//==========================================
//  �R���X�g���N�^
//==========================================
CMessageWin::CMessageWin() :
	m_fSec(0.0f),
	m_bMove(false),
	m_nIdx(nIdx)
{
	++nIdx;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CMessageWin::~CMessageWin()
{
	--nIdx;
}

//==========================================
//  ����������
//==========================================
HRESULT CMessageWin::Init(void)
{
	// ������
	HRESULT hr = CObject3D::Init();

	// ��ނ�ݒ�
	CObject::SetType(CObject::TYPE_OBJECT3D);

	// �e�N�X�`���̊��蓖��
	BindTexture(CManager::GetInstance()->GetTexture()->Regist(TEXPASS[m_nIdx]));

	// �ʒu��ݒ�
	D3DXVECTOR3 pos_Diff = DEF_POS;
	pos_target = DIFF_POS;
	if (m_nIdx == 0)
	{
		pos_Diff.x *= -1.0f;
		pos_target.x *= -1.0f;
	}
	pos_target += CManager::GetInstance()->GetCamera()->GetPositionV();
	SetPosition(CManager::GetInstance()->GetCamera()->GetPositionV() + pos_Diff);

	// �T�C�Y��ݒ�
	SetSize(LOGO_SIZE);

	//�l��Ԃ�
	return hr;
}

//==========================================
//  �I������
//==========================================
void CMessageWin::Uninit(void)
{
	// �I��
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CMessageWin::Update(void)
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
void CMessageWin::Draw(void)
{
	// �`��
	CObject3D::Draw();
}

//==========================================
//  ��������
//==========================================
CMessageWin* CMessageWin::Create()
{
	// �C���X�^���X����
	CMessageWin* pLose = DEBUG_NEW CMessageWin;

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
void CMessageWin::Move()
{
	// �o�ߎ��Ԃ����Z
	m_fSec += CManager::GetInstance()->GetDeltaTime() * MOVE_SPEED;

	// �ʒu���擾
	D3DXVECTOR3 pos = GetPosition();

	// �ʒu���X�V
	if (m_nIdx == 0)
	{
		pos.x += m_fSec * m_fSec;

		// �ʒu��␳
		if (pos_target.x < pos.x)
		{
			pos = pos_target;

			// �ړ������t���O���I��
			m_bMove = true;
		}
	}
	else
	{
		pos.x -= m_fSec * m_fSec;

		// �ʒu��␳
		if (pos_target.x > pos.x)
		{
			pos = pos_target;

			// �ړ������t���O���I��
			m_bMove = true;
		}
	}

	if (m_bMove)
	{
		CManager::GetInstance()->GetCamera()->SetShake(10, 10.0f, 0.0f);
	}

	// �ʒu��K�p
	SetPosition(pos);
}
