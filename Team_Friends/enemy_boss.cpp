//==========================================================================
// 
//  �{�X���� [enemy_boss.cpp]
//  Author : ���n�Ή�
// 
//==========================================================================
#include "enemy_boss.h"
#include "manager.h"
#include "debugproc.h"
#include "calculation.h"
#include "hp_gauge.h"

//==========================================================================
//  �萔��`
//==========================================================================
namespace
{
	const float LENGTH_CHASEWALK = 1000.0f;	// �����Ǐ]�̒���
}

//==========================================================================
// �֐��|�C���^
//==========================================================================
CEnemyBoss::ACT_FUNC CEnemyBoss::m_ActFuncList[] =
{
	&CEnemyBoss::ActChase,				// �ǂ��|��
	&CEnemyBoss::ActAttackProximity,	// �ߐ�
	&CEnemyBoss::ActAttackRemote,		// ���u
	&CEnemyBoss::ActAttackAssault,		// �ˌ�
	&CEnemyBoss::ActAttackExplosion,	// ����
};

//==========================================================================
//  �R���X�g���N�^
//==========================================================================
CEnemyBoss::CEnemyBoss(int nPriority) : CEnemy(nPriority)
{
	m_Action = ACTION_CHASE;		// �s��
	m_ActionBranch = ACTBRANCH_CHASE_SLOW;	// �s������
	m_TargetPosition = mylib_const::DEFAULT_VECTOR3;	// �ڕW�̈ʒu
	m_fActTime = 0.0f;			// �s���J�E���^�[
}

//==========================================================================
//  �f�X�g���N�^
//==========================================================================
CEnemyBoss::~CEnemyBoss()
{

}

//==========================================================================
//  ����������
//==========================================================================
HRESULT CEnemyBoss::Init(void)
{
	//����������
	CEnemy::Init();

	// HP�̐ݒ�
	m_pHPGauge = CHP_Gauge::Create(100.0f, GetLifeOrigin());

	return S_OK;
}

//==========================================================================
//  �I������
//==========================================================================
void CEnemyBoss::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//==========================================================================
//  �X�V����
//==========================================================================
void CEnemyBoss::Update(void)
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

	// ���[�V�����̍X�V
	MotionSet();
}

//==========================================================================
// �s���ݒ�
//==========================================================================
void CEnemyBoss::ActionSet(void)
{

	while (1)
	{
		// �s�����I
		m_Action = (ACTION)(rand() % ACTION_MAX);

		if (m_Action != ACTION_SELFEXPLOSION &&
			m_Action != ACTION_CHASE)
		{// ����s���ȊO
			break;
		}
	}

	// ���̍s����
	int nActRand;
	switch (m_Action)
	{
	case CEnemyBoss::ACTION_CHASE:	// �Ǐ]
		if (CalcLenPlayer(LENGTH_CHASEWALK))
		{// �����͈̔�
			m_ActionBranch = ACTBRANCH_CHASE_SLOW;
		}
		else
		{
			m_ActionBranch = ACTBRANCH_CHASE_DASH;
		}
		break;

	case CEnemyBoss::ACTION_PROXIMITY:	// �ߐڍU��
		nActRand = Random(ACTBRANCH_PROXIMITY_PUNCH, ACTBRANCH_PROXIMITY_KICK);
		m_ActionBranch = static_cast<eActionBranch>(nActRand);
		break;

	case CEnemyBoss::ACTION_REMOTE:	// ���u�U��
		m_ActionBranch = ACTBRANCH_REMOTE_BEAM;
		break;

	case CEnemyBoss::ACTION_ASSAULT:	// �ˌ��U��
		m_ActionBranch = ACTBRANCH_ASSAULT_CHARGE;
		break;

	default:
		break;
	}
}

//==========================================================================
// �s���X�V
//==========================================================================
void CEnemyBoss::UpdateAction(void)
{
	// ��ԕʏ���
	(this->*(m_ActFuncList[m_Action]))();
}

//==========================================================================
// �ǂ��|��
//==========================================================================
void CEnemyBoss::ActChase(void)
{
	// �ړ��t���O�𗧂Ă�
	m_sMotionFrag.bMove = true;

	// �^�[�Q�b�g�̕�������
	RotationTarget();

	// �s���ʈړ�����
	switch (m_ActionBranch)
	{
	case CEnemyBoss::ACTBRANCH_CHASE_SLOW:
		ChaseSlow();
		break;

	case CEnemyBoss::ACTBRANCH_CHASE_DASH:
		ChaseDash();
		break;

	default:
		break;
	}
}

//==========================================================================
// �����ǂ��|��
//==========================================================================
void CEnemyBoss::ChaseSlow(void)
{

}

//==========================================================================
// �_�b�V���ǂ��|��
//==========================================================================
void CEnemyBoss::ChaseDash(void)
{

}

//==========================================================================
// �ߐڍU��
//==========================================================================
void CEnemyBoss::ActAttackProximity(void)
{
	// �U���t���O�𗧂Ă�
	m_sMotionFrag.bATK = true;

	// �^�[�Q�b�g�̕�������
	RotationTarget();

	// �s���ʈړ�����
	switch (m_ActionBranch)
	{
	case CEnemyBoss::ACTBRANCH_PROXIMITY_PUNCH:
		AttackPunch();
		break;

	case CEnemyBoss::ACTBRANCH_PROXIMITY_KICK:
		AttackKick();
		break;

	default:
		break;
	}
}

//==========================================================================
// �p���`�U��
//==========================================================================
void CEnemyBoss::AttackPunch(void)
{

}

//==========================================================================
// �L�b�N�U��
//==========================================================================
void CEnemyBoss::AttackKick(void)
{

}

//==========================================================================
// ���u�U��
//==========================================================================
void CEnemyBoss::ActAttackRemote(void)
{
	// �U���t���O�𗧂Ă�
	m_sMotionFrag.bATK = true;

	// �^�[�Q�b�g�̕�������
	RotationTarget();

	// �s���ʈړ�����
	switch (m_ActionBranch)
	{
	case CEnemyBoss::ACTBRANCH_REMOTE_BEAM:
		AttackBeam();
		break;

	default:
		break;
	}
}

//==========================================================================
// �r�[���U��
//==========================================================================
void CEnemyBoss::AttackBeam(void)
{

}

//==========================================================================
// �ˌ��U��
//==========================================================================
void CEnemyBoss::ActAttackAssault(void)
{
	// �U���t���O�𗧂Ă�
	m_sMotionFrag.bATK = true;

	// �^�[�Q�b�g�̕�������
	RotationTarget();

	// �s���ʈړ�����
	switch (m_ActionBranch)
	{
	case CEnemyBoss::ACTBRANCH_ASSAULT_CHARGE:
		ChargeTackle();
		break;

	case CEnemyBoss::ACTBRANCH_ASSAULT_TACKLE:
		AttackTackle();
		break;

	default:
		break;
	}
}

//==========================================================================
// �^�b�N���`���[�W
//==========================================================================
void CEnemyBoss::ChargeTackle(void)
{

}

//==========================================================================
// �^�b�N���U��
//==========================================================================
void CEnemyBoss::AttackTackle(void)
{

}

//==========================================================================
// �����U��
//==========================================================================
void CEnemyBoss::ActAttackExplosion(void)
{

}

//==========================================================================
//  �`�揈��
//==========================================================================
void CEnemyBoss::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//==========================================================================
//  �E��
//==========================================================================
void CEnemyBoss::Kill(void)
{
	// ���S����
	CEnemy::Kill();
}

//==========================================================================
//  ���[�V�����Z�b�g
//==========================================================================
void CEnemyBoss::MotionSet(void)
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

//==========================================================================
// �^�[�Q�b�g�̕�������
//==========================================================================
void CEnemyBoss::RotationTarget(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();

	// �ڕW�̊p�x�����߂�
	float fRotDest = atan2f((pos.x - m_TargetPosition.x), (pos.z - m_TargetPosition.z));

	// �ڕW�Ƃ̍���
	float fRotDiff = fRotDest - rot.y;

	//�p�x�̐��K��
	RotNormalize(fRotDiff);

	//�p�x�̕␳������
	rot.y += fRotDiff * 0.025f;
	RotNormalize(rot.y);

	// �����ݒ�
	SetRotation(rot);

	// �ڕW�̌����ݒ�
	SetRotDest(fRotDest);
}

