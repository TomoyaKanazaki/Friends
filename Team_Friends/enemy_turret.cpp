//==========================================
//
//  �C�䒆�{�X�G(enemy_turret.cpp)
//  Author : Kai Takada
//
//==========================================
#include "enemy_turret.h"
#include "player.h"
#include "manager.h"
#include "debugproc.h"
#include "calculation.h"
#include "hp_gauge.h"
#include "particle.h"
#include "particle.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const float ATTACK_LENGTH = 200.0f;
	const float MOVE_SPEED = 0.01f;
	const float ATTACK_SPEED = 10.0f;
	const float MOVE_X = 2.0f;
	const float MOVE_Z = 2.0f;
	const float READY_TIME = 3.0f;
	const float ATTACK_TIME = 1.0f;
	const float AFTER_TIME = 2.0f;
	const float SEARCH_ROT = 45.0f;
	const float AFTER_FIXROT = 0.07f;
}

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemyTurret::CEnemyTurret(int nPriority) :
	m_Act(ACTION_ROAMING),
	m_Atk(ATTACK_NONE),
	m_fActionCount(0.0f),
	m_moveLock(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_fRotLock(0.0f)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemyTurret::~CEnemyTurret()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemyTurret::Init(void)
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
void CEnemyTurret::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemyTurret::Update(void)
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
}

//==========================================================================
// �s���X�V
//==========================================================================
void CEnemyTurret::UpdateAction(void)
{
	D3DXVECTOR3 pos = GetPosition();

	// �s�����Ƃ̍s��
	switch (m_Act)
	{
	case CEnemyTurret::ACTION_ROAMING:

		//�ړ�
		Move();

		break;

	case CEnemyTurret::ACTION_READY:

		//�f�o�b�O�p
		my_particle::Create(pos, my_particle::TYPE_SMOKE);

		// �ړ��ʂ�ݒ�
		RotationPlayer();

		break;

	case CEnemyTurret::ACTION_ATTACK:

		//�f�o�b�O�p
		my_particle::Create(pos, my_particle::TYPE_SMOKE_RED);

		// �U��
		Attack();

		break;

	case CEnemyTurret::ACTION_AFTER:

		//�f�o�b�O�p
		my_particle::Create(pos, my_particle::TYPE_SMOKE);

		FixRotation();

		break;

	default:
		break;
	}

	if (m_Act != ACTION_ROAMING)
	{
		// �J�E���^�[�����Z
		m_fActionCount += CManager::GetInstance()->GetDeltaTime();
	}
}

//==========================================
//  �`�揈��
//==========================================
void CEnemyTurret::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//==========================================
//  �E��
//==========================================
void CEnemyTurret::Kill(void)
{
	// ���S����
	CEnemy::Kill();
}

//==========================================
//  ���[�V�����Z�b�g
//==========================================
void CEnemyTurret::MotionSet(void)
{
	if (m_pMotion->IsFinish() == true)
	{// �I�����Ă�����

		// ���݂̎�ގ擾
		int nType = m_pMotion->GetType();

		if (m_sMotionFrag.bKnockback == true)
		{// ���ꒆ��������

			// ���ꃂ�[�V����
			m_pMotion->Set(MOTION_KNOCKBACK);
		}
		else if (m_sMotionFrag.bATK == true)
		{// �U�����Ă�����

			m_sMotionFrag.bATK = false;		// �U������OFF

			// �U�����[�V����
			if (m_Atk == ATTACK_BEAM)
			{
				m_pMotion->Set(MOTION_ATK_BEAM);
			}
			else if (m_Atk == ATTACK_MORTAR)
			{
				m_pMotion->Set(MOTION_ATK_MORTAR);
			}
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
void CEnemyTurret::ActionSet(void)
{
	if (m_Act == ACTION_READY)
	{
		if (m_fActionCount >= READY_TIME)
		{
			m_Act = ACTION_ATTACK;
			m_fActionCount = 0.0f;
		}

		return;
	}
	else if (m_Act == ACTION_ATTACK)
	{
		if (m_fActionCount >= ATTACK_TIME)
		{
			m_Act = ACTION_AFTER;
			m_fActionCount = 0.0f;
			m_moveLock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}

		return;
	}
	else if (m_Act == ACTION_AFTER)
	{
		if (m_fActionCount >= AFTER_TIME)
		{
			m_Act = ACTION_ROAMING;
			m_fActionCount = 0.0f;
		}

		return;
	}

	if (m_Act == ACTION_ROAMING)
	{
		//�U���Ɉڍs
		//�U���̌�����@�ǂ�����

		// �������߂��ƍU����ԂɂȂ�
		m_Act = ACTION_READY;
		m_fActionCount = 0.0f;
	}
}

//==========================================
//  �ړ�
//==========================================
void CEnemyTurret::Move(void)
{
	// �ړ��t���O�𗧂Ă�
	m_sMotionFrag.bMove = true;

	// �ړ��J�E���^�[�����Z
	m_fActionCount += MOVE_SPEED;

	// �ړ��ʂ�K�p
	D3DXVECTOR3 move = GetMove();
	move.x = sinf(m_fActionCount) * MOVE_X;
	move.z = cosf(m_fActionCount) * MOVE_Z;
	SetMove(move);

	// �����]��
	MoveRotation();
}

//==========================================
//  �ړ���������������
//==========================================
void CEnemyTurret::MoveRotation(void)
{
	// �K�v�Ȓl���擾
	D3DXVECTOR3 rot = GetRotation();
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 posDest = pos + move;
	D3DXVECTOR3 posDiff = posDest - pos;

	// �������Z�o
	float fRot = atan2f(-posDiff.x, -posDiff.z);

	//�p�x�̐��K��
	RotNormalize(fRot);

	//�p�x�̕␳������
	rot.y = fRot;

	// �����ݒ�
	SetRotation(rot);
}

//==========================================
//  �U��
//==========================================
void CEnemyTurret::Attack(void)
{
	D3DXVECTOR3 move = GetMove();

	if (m_moveLock == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		m_sMotionFrag.bATK = true;

		// �v���C���[���
		CPlayer* pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(m_nTargetPlayerIndex);
		if (pPlayer == NULL)
		{
			return;
		}

		// ���擾
		D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
		D3DXVECTOR3 pos = GetPosition();

		//�U������A����

		// �v���C���[���玩�g�Ɍ������x�N�g�����Z�o
		D3DXVECTOR3 vecToPlayer = posPlayer - pos;

		// �x�N�g���̐��K��
		vecToPlayer.y = 0.0f;
		D3DXVec3Normalize(&vecToPlayer, &vecToPlayer);
		vecToPlayer *= ATTACK_SPEED;

		//�p�x�𔽓]
		m_fRotLock = GetRotation().y + D3DX_PI;
		RotNormalize(m_fRotLock);

		// �ړ��ʂ̐ݒ�
		move.x = vecToPlayer.x;
		move.z = vecToPlayer.z;
		SetMove(move);

		m_moveLock = move;

		return;
	}

	SetMove(m_moveLock);
}

//==========================================
//  �v���C���[����������
//==========================================
void CEnemyTurret::RotationPlayer(void)
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
	rot.y += fRotDiff * 0.025f;

	// �p�x�̐��K��
	RotNormalize(rot.y);

	// �����ݒ�
	SetRotation(rot);

	// �ڕW�̌����ݒ�
	SetRotDest(fRotDest);
}

//==========================================
//�@��������ړ��ʂ�ݒ�
//==========================================
void CEnemyTurret::SetMoveRotation(void)
{
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 rot = GetRotation();
	move.x = sinf(rot.y) * MOVE_X * ATTACK_SPEED;
	move.z = cosf(rot.y) * MOVE_Z * ATTACK_SPEED;
	SetMove(move);
}

//==========================================
//  �v���C���[��T������
//==========================================
bool CEnemyTurret::SearchPlayer(float fLen)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();
	D3DXVECTOR3 posL = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���G��̍��_
	D3DXVECTOR3 posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���G��̉E�_

	//float fRot = SEARCH_ROT * D3DX_PI / 180;
	float fRot = 0.785f;


	//�v���C���[�̐l����c��

	//��ԋ߂����W�I�ɂ���
	for (int nCnt = 0; nCnt < mylib_const::MAX_PLAYER; nCnt++)
	{
		// �v���C���[���
		CPlayer* pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(nCnt);
		if (pPlayer == NULL)
		{
			continue;
		}
	}



	// �v���C���[�̈ʒu�擾
	//D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

	//// ���͈͓��̔���
	//if (CollisionFan(pos, posL, posR, posPlayer, fRot))
	//{
	//	return true;
	//}

	return false;
}

//==========================================
// �w������Ɍ���
//==========================================
void CEnemyTurret::FixRotation(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();

	// �ڕW�Ƃ̍���
	float fRotDiff = m_fRotLock - rot.y;

	//�p�x�̐��K��
	RotNormalize(fRotDiff);

	//�p�x�̕␳������
	rot.y += fRotDiff * AFTER_FIXROT;

	// �p�x�̐��K��
	RotNormalize(rot.y);

	// �����ݒ�
	SetRotation(rot);

	// �ڕW�̌����ݒ�
	SetRotDest(m_fRotLock);
}
