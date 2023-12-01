//==========================================
//
//  �R�s�y�p�̓G(enemy_escape.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_escape.h"
#include "player.h"
#include "manager.h"
#include "debugproc.h"
#include "calculation.h"
#include "hp_gauge.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const float SEARCH_LENGTH = 400.0f;
	const float MOVE_SPEED = 0.03f;
	const float ESCAPE_SPEED = 5.00f;
	const float MOVE_X = 2.0f;
	const float MOVE_Z = 2.0f;
	const float FIND_TIME = 0.5f;
	const float ESCAPE_TIME = 3.0f;
}

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemyEscape::CEnemyEscape(int nPriority) :
	m_Act(ACTION_ROAMING),
	m_fMoveCount(0.0f),
	m_fCntFind(0.0f),
	m_fCntEscape(0.0f)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemyEscape::~CEnemyEscape()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemyEscape::Init(void)
{
	//����������
	CEnemy::Init();

	// HP�̐ݒ�
	m_pHPGauge = CHP_Gauge::Create(100.0f, GetLifeOrigin());

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CEnemyEscape::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemyEscape::Update(void)
{
	// ���S�̔���
	if (IsDeath() == true)
	{// ���S�t���O�������Ă�����
		return;
	}

	// �X�V����
	CEnemy::Update();

	if (IsDeath() == true)
	{// ���S�t���O�������Ă�����
		return;
	}

	// �s����Ԃ̍X�V
	ActionSet();

	// ���[�V�����̍X�V
	MotionSet();

	CManager::GetInstance()->GetDebugProc()->Print
	(
		"���[�V���� : %d\n", m_pMotion->GetType()
	);
}

//==========================================
// �s���X�V
//==========================================
void CEnemyEscape::UpdateAction(void)
{
	if (m_state == STATE_DEAD ||
		m_state == STATE_FADEOUT)
	{
		return;
	}

	// �s�����Ƃ̍s��
	switch (m_Act)
	{
	case CEnemyEscape::ACTION_ROAMING:

		// �ړ�
		Move();

		break;

	case CEnemyEscape::ACTION_FIND:

		// �v���C���[������
		RotationPlayer();

		// �J�E���^�[�����Z
		m_fCntFind += CManager::GetInstance()->GetDeltaTime();

		break;

	case CEnemyEscape::ACTION_ESCAPE:

		// ����
		Escape();

		// �J�E���^�[�����Z
		m_fCntEscape += CManager::GetInstance()->GetDeltaTime();

		break;

	case CEnemyEscape::ACTION_FADE:

		// ����
		Escape();

		// �����Ă���
		SetState(STATE_FADEOUT);

		break;

	default:
		break;
	}
}

//==========================================
//  �`�揈��
//==========================================
void CEnemyEscape::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//==========================================
//  �E��
//==========================================
void CEnemyEscape::Kill(void)
{
	// ���S����
	CEnemy::Kill();
}

//==========================================
//  ���[�V�����Z�b�g
//==========================================
void CEnemyEscape::MotionSet(void)
{
	if (m_pMotion->IsFinish() == true)
	{// �I�����Ă�����

		// ���݂̎�ގ擾
		int nType = m_pMotion->GetType();

		if (m_sMotionFrag.bMove == true && m_sMotionFrag.bKnockback == false)
		{// �ړ����Ă�����
			// �U�����Ă��Ȃ�
			m_sMotionFrag.bATK = false;

			// �ړ����[�V����
			m_pMotion->Set(MOTION_WALK);
		}
		else if (m_sMotionFrag.bKnockback == true)
		{// ���ꒆ��������

			// ���ꃂ�[�V����
			m_pMotion->Set(MOTION_KNOCKBACK);
		}
		else if (m_sMotionFrag.bATK == true)
		{// �U�����Ă�����

			m_sMotionFrag.bATK = false;		// �U������OFF

			// �U�����[�V����
			m_pMotion->Set(MOTION_ATK);
		}
		else
		{
			// �j���[�g�������[�V����
			m_pMotion->Set(MOTION_DEF);
		}
	}
}

//==========================================
//  �s���ݒ�
//==========================================
void CEnemyEscape::ActionSet(void)
{
	// ���ŏ�Ԃ̏ꍇ�͔�����
	if (m_Act == ACTION_FADE)
	{
		return;
	}

	// ������Ԃ�����ł���
	if (m_Act == ACTION_ESCAPE)
	{
		if (m_fCntEscape >= ESCAPE_TIME)
		{
			m_Act = ACTION_FADE;
		}
		return;
	}

	// ������Ԃ��瓦����Ԃֈڍs����
	if (m_Act == ACTION_FIND)
	{
		if (m_fCntFind >= FIND_TIME)
		{
			m_Act = ACTION_ESCAPE;
		}
		return;
	}

	if (CalcLenPlayer(SEARCH_LENGTH))
	{
		// �������߂��Ɣ�����ԂɂȂ�
		m_Act = ACTION_FIND;
	}
	else // ��L�ȊO�Ȃ�ҋ@���
	{
		m_Act = ACTION_ROAMING;
	}
}

//==========================================
//  �ړ�
//==========================================
void CEnemyEscape::Move(void)
{
	// �ړ��t���O�𗧂Ă�
	m_sMotionFrag.bMove = true;

	// �ړ��J�E���^�[�����Z
	m_fMoveCount += MOVE_SPEED;

	// �ړ��ʂ�K�p
	D3DXVECTOR3 move = GetMove();
	move.x = sinf(m_fMoveCount) * MOVE_X;
	move.z = cosf(m_fMoveCount) * MOVE_Z;
	SetMove(move);

	// �����]��
	MoveRotation();
}

//==========================================
//  ����
//==========================================
void CEnemyEscape::Escape(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �v���C���[���
	CPlayer* pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(m_nTargetPlayerIndex);
	if (pPlayer == NULL)
	{
		return;
	}

	// �v���C���[�̈ʒu�擾
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

	// �v���C���[���玩�g�Ɍ������x�N�g�����Z�o
	D3DXVECTOR3 vecToPlayer = pos - posPlayer;

	// �x�N�g���̐��K��
	vecToPlayer.y = 0.0f;
	D3DXVec3Normalize(&vecToPlayer, &vecToPlayer);
	vecToPlayer *= ESCAPE_SPEED;

	// �ړ��ʂ̎擾
	D3DXVECTOR3 move = GetMove();

	// �ړ��ʂ̐ݒ�
	move.x = vecToPlayer.x;
	move.z = vecToPlayer.z;
	SetMove(move);

	// �����]��
	MoveRotation();
}

//==========================================
//  �ړ���������������
//==========================================
void CEnemyEscape::MoveRotation(void)
{
	// �K�v�Ȓl���擾
	D3DXVECTOR3 rot = GetRotation();
	D3DXVECTOR3 move = GetMove();

	// �������Z�o
	float fRot = atan2f(-move.x, -move.z);

	//�p�x�̐��K��
	RotNormalize(fRot);

	//�p�x�̕␳������
	rot.y = fRot;

	// �����ݒ�
	SetRotation(rot);
}

//==========================================
//  �v���C���[����������
//==========================================
void CEnemyEscape::RotationPlayer(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();

	// �v���C���[���
	CPlayer* pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(m_nTargetPlayerIndex);
	if (pPlayer == NULL)
	{
		return;
	}

	// �v���C���[�̈ʒu�擾
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

	// �ڕW�̊p�x�����߂�
	float fRotDest = atan2f((pos.x - posPlayer.x), (pos.z - posPlayer.z));

	// �ڕW�Ƃ̍���
	float fRotDiff = fRotDest - rot.y;

	//�p�x�̐��K��
	RotNormalize(fRotDiff);

	//�p�x�̕␳������
	rot.y += fRotDiff * 0.1f;

	// �p�x�̐��K��
	RotNormalize(rot.y);

	// �����ݒ�
	SetRotation(rot);

	// �ڕW�̌����ݒ�
	SetRotDest(fRotDest);
}

//==========================================
//  �v���C���[�Ƃ̋����𔻒�
//==========================================
bool CEnemyEscape::CalcLenPlayer(float fLen)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �v���C���[���
	CPlayer* pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(m_nTargetPlayerIndex);
	if (pPlayer == NULL)
	{
		return false;
	}

	// �v���C���[�̈ʒu�擾
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

	// ��_�Ԃ��q���x�N�g���̎Z�o
	D3DXVECTOR3 vecToPlayer = pos - posPlayer;

	// �x�N�g���̑傫����2����Z�o
	float fLength = vecToPlayer.x * vecToPlayer.x + vecToPlayer.z * vecToPlayer.z;

	// ���͈͓��̔���
	if (fLen * fLen >= fLength)
	{
		return true;
	}

	return false;
}
