//=============================================================================
// 
//  �v���C���[���� [player_title.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "game.h"
#include "player_title.h"
#include "manager.h"
#include "debugproc.h"
#include "input.h"
#include "model.h"
#include "motion.h"
#include "objectChara.h"
#include "shadow.h"
#include "calculation.h"

//==========================================
//  �萔��` : �������
//==========================================
namespace
{
	// �t�@�C���p�X
	const char* CHARAFILE =
	{
		"data\\TEXT\\character\\player\\motion_player.txt"
	};

	const float MOVE_SPEED = 1.5f; // �ړ��ʔ{��
}

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
int CPlayerTitle::m_nIdx = 0;

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CPlayerTitle::CPlayerTitle(int nPriority) : CPlayer(nPriority),
m_nModelType(NONE),
m_posTarget(0.0f),
m_bMove(false)
{
	// �l�̃N���A
	
	// �C���f�b�N�X���L�^
	m_nMyPlayerIdx = m_nIdx;

	// �C���f�b�N�X�����Z
	++m_nIdx;
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CPlayerTitle::~CPlayerTitle()
{
	// �C���f�b�N�X�����Z
	--m_nIdx;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CPlayerTitle::Init(void)
{
	// ��ނ̐ݒ�
	SetType(TYPE_PLAYER);

	m_state = STATE_NONE;	// ���

	// �L�����쐬
	HRESULT hr = SetCharacter(CHARAFILE);

	if (FAILED(hr))
	{// ���s���Ă�����
		return E_FAIL;
	}

	// ���[�V�����̐�������
	m_pMotion = CMotion::Create(CHARAFILE);

	// �I�u�W�F�N�g�L�����N�^�[�̏��擾
	CObjectChara *pObjChar = GetObjectChara();

	// ���[�V�����̐ݒ�
	m_pMotion->SetModel(pObjChar->GetModel(), pObjChar->GetNumModel(), CObjectChara::GetObjectChara());
	
	// ���f���̍����ւ�
	switch (m_nModelType)
	{
	case PLAYER_BODY:
		SetEvolusion(CGameManager::STATUS_LIFE, true);
		break;

	case PLAYER_ARM:
		SetEvolusion(CGameManager::STATUS_POWER, true);
		break;

	case PLAYER_LEG:
		SetEvolusion(CGameManager::STATUS_SPEED, true);
		break;

	default:
		break;
	}

	// �e�N�X�`����ݒ�
	BindByPlayerIdxTexture();

	// �|�[�Y�̃��Z�b�g
	m_pMotion->ResetPose(MOTION_DEF);

	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CPlayerTitle::Uninit(void)
{
	// �I������
	CPlayer::Uninit();
}

//==========================================================================
// �X�V����
//==========================================================================
void CPlayerTitle::Update(void)
{
	if (IsDeath() == true)
	{
		return;
	}

	// �ߋ��̈ʒu�ۑ�
	SetOldPosition(GetPosition());

	// �����o������
	if (m_bMove)
	{
		if (m_nModelType == PLAYER_ARM) // �r�͔�яオ��
		{
			Fly();
		}
		else // ���̑��͑���o��
		{
			Forward();
		}

		// �ʒu���X�V
		D3DXVECTOR3 pos = GetPosition();
		pos += GetMove();
		SetPosition(pos);
	}

	// �V�[�����擾
	if (CManager::GetInstance()->GetScene()->GetMode() == CScene::MODE_DECIDE)
	{
		// �ړ�����
		Move();
	}

	// ���[�V�����X�V
	if (m_pMotion != NULL)
	{
		m_pMotion->Update();
	}

	// �e�̈ʒu�X�V
	if (m_pShadow != NULL)
	{
		// �ʒu�擾
		D3DXVECTOR3 pos = GetPosition();

		m_pShadow->SetPosition(D3DXVECTOR3(pos.x, m_pShadow->GetPosition().y, pos.z));
	}
}

//==========================================================================
// �`�揈��
//==========================================================================
void CPlayerTitle::Draw(void)
{
	// �`�揈��
	CPlayer::Draw();
}

//==========================================
//  �������� : �������
//==========================================
CPlayerTitle* CPlayerTitle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL type)
{
	// �C���X�^���X����
	CPlayerTitle* pPlayer = DEBUG_NEW CPlayerTitle;

	//���f����ݒ�
	pPlayer->m_nModelType = (int)type;

	// ����������
	pPlayer->Init();

	// �l��ۑ�
	pPlayer->SetTarget(pos.z);
	pPlayer->SetPosition(pos);
	pPlayer->SetRotation(rot);

	return pPlayer;
}

//==========================================
//  ��]
//==========================================
void CPlayerTitle::Rotation(void)
{
	// �ړ����[�V�����ɂ���
	m_pMotion->Set(CPlayer::MOTION_WALK);

	// �ړ��������Z�o
	D3DXVECTOR3 move = -GetMove();
	D3DXVECTOR3 rotTarget = GetRotation();
	rotTarget.y = atan2f(move.x, move.z);

	// �p�x�̐��K��
	RotNormalize(rotTarget);

	// �ړI�̕����ƌ��݂̕����̍������Z�o
	D3DXVECTOR3 rot = GetRotation();
	D3DXVECTOR3 rotdiff = rotTarget - rot;

	// �p�x�̐��K��
	RotNormalize(rotdiff);

	// �����]�����x��␳
	rotdiff *= 0.1f;

	// �p�x�����Z
	rot += rotdiff;

	// �ړ�������K�p
	SetRotation(rot);
}

//==========================================
//  �ړ����鏈��
//==========================================
void CPlayerTitle::Move(void)
{
	// �l�̎擾
	D3DXVECTOR3 pos = GetPosition(); // �ʒu
	D3DXVECTOR3 move = GetMove(); // �ړ���

	// �ړ�����
	if (pos.z > m_posTarget) // �ړ��ʐ���
	{
		// ��~
		pos.z = m_posTarget;
		move.z = 0.0f;

		// �ҋ@���[�V�����ɂ���
		m_pMotion->Set(CPlayer::MOTION_DEF);
	}
	else if (pos.z < 0.0f) // �ړ��ʐ���
	{
		// ��~
		pos.z = 0.0f;
		move.z = 0.0f;

		// �ҋ@���[�V�����ɂ���
		m_pMotion->Set(CPlayer::MOTION_DEF);
	}

	// ���������Ă΂�������[�ˁI
	pos += move;

	// �����Ă�Ƃ��͌�����ς���
	if (move.z != 0.0f)
	{
		// ��]����
		Rotation();
	}

	// �l�̓K�p
	SetPosition(pos);
	SetMove(move);
}

//==========================================
//  ��яオ��
//==========================================
void CPlayerTitle::Fly(void)
{
	// �p�x�̎擾
	D3DXVECTOR3 rot = GetRotation();

	// �ړ��ʂ��擾
	float fMove = GetVelocity();
	D3DXVECTOR3 move = GetMove();

	// �ړ��ʂ𕪉�����
	move.y = fMove * MOVE_SPEED;

	// �ړ��ʂ�K�p����
	SetMove(move);
}

//==========================================
//  ����o��
//==========================================
void CPlayerTitle::Forward(void)
{
	// �ړ����[�V�����ɂ���
	m_pMotion->Set(CPlayer::MOTION_WALK);

	// �p�x�̎擾
	D3DXVECTOR3 rot = GetRotation();

	// �ړ��ʂ��擾
	float fMove = GetVelocity();
	D3DXVECTOR3 move = GetMove();

	// �ړ��ʂ𕪉�����
	move.x = -sinf(rot.y) * fMove * MOVE_SPEED;
	move.z = -cosf(rot.y) * fMove * MOVE_SPEED;

	// �ړ��ʂ�K�p����
	SetMove(move);
}
