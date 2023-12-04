//==========================================
//
//  �R�s�y�p�̓G(enemy_roaming.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_roaming.h"
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
	const float ATTACK_LENGTH = 200.0f;	// �R�����g
	const float MOVE_SPEED = 0.01f;
}

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemyRoaming::CEnemyRoaming(int nPriority) :
	m_Act(ACTION_ROAMING)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemyRoaming::~CEnemyRoaming()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemyRoaming::Init(void)
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
void CEnemyRoaming::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemyRoaming::Update(void)
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
}

//==========================================
// �s���X�V
//==========================================
void CEnemyRoaming::UpdateAction(void)
{
	// �s�����Ƃ̍s��
	switch (m_Act)
	{
	case CEnemyRoaming::ACTION_ROAMING:

		// �ړ�
		Move();

		break;

	case CEnemyRoaming::ACTION_ATTACK:

		// �v���C���[������
		RotationPlayer();

		// �U��
		Attack();

		break;

	default:
		break;
	}
}

//==========================================
//  �`�揈��
//==========================================
void CEnemyRoaming::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//==========================================
//  �E��
//==========================================
void CEnemyRoaming::Kill(void)
{
	// ���S����
	CEnemy::Kill();
}

//==========================================
//  ���[�V�����Z�b�g
//==========================================
void CEnemyRoaming::MotionSet(void)
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
void CEnemyRoaming::ActionSet(void)
{
	if (CalcLenPlayer(ATTACK_LENGTH))
	{
		// �U���t���O�𗧂Ă�
		if (m_Act != ACTION_ATTACK)
		{
			m_sMotionFrag.bATK = true;
		}

		// �������߂��ƍU����ԂɂȂ�
		m_Act = ACTION_ATTACK;
	}
	else // ��L�ȊO�Ȃ�ҋ@���
	{
		m_Act = ACTION_ROAMING;
	}
}

//==========================================
//  �ړ�
//==========================================
void CEnemyRoaming::Move(void)
{
	// �ړ��t���O�𗧂Ă�
	m_sMotionFrag.bMove = true;

	// �ړ��J�E���^�[�����Z
	m_fMoveCount += MOVE_SPEED;

	// �ړ����x�擾
	float fMove = GetVelocity();

	// �ړ��ʂ�K�p
	D3DXVECTOR3 move = GetMove();
	move.x = sinf(m_fMoveCount) * fMove;
	move.z = cosf(m_fMoveCount) * fMove;
	SetMove(move);

	// �����]��
	MoveRotation();
}

//==========================================
//  �U��
//==========================================
void CEnemyRoaming::Attack(void)
{
	// �U������
	CEnemy::StateAttack();

	// ���[�V�����̏��擾
	CMotion::Info aInfo = m_pMotion->GetInfo(m_pMotion->GetType());

	// �U�����̑����擾
	int nNumAttackInfo = aInfo.nNumAttackInfo;

	bool bAtkWait = true;	// �U���ҋ@��
	for (int nCntAttack = 0; nCntAttack < nNumAttackInfo; nCntAttack++)
	{
		if (aInfo.AttackInfo[nCntAttack] == NULL)
		{// NULL��������
			continue;
		}

		// ���[�V�����J�E���^�[�擾
		if (m_pMotion->GetAllCount() > aInfo.AttackInfo[nCntAttack]->nMinCnt)
		{// �U�����蒆
			// �U�����蒆�ɂ���
			bAtkWait = false;
		}
	}

	if (bAtkWait == false)
	{// ���蒆�̎�
		return;
	}
}
