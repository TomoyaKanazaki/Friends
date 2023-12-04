//=============================================================================================================
// 
//  �{�X���� [enemy_boss.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================================================
#include "enemy_boss.h"
#include "player.h"
#include "manager.h"
#include "debugproc.h"
#include "calculation.h"
#include "hp_gauge.h"

//==========================================================================
//  �萔��`
//==========================================================================
namespace
{
	const float ATTACK_LENGTH = 200.0f;
	const float MOVE_SPEED = 0.01f;
	const float MOVE_X = 2.0f;
	const float MOVE_Z = 2.0f;
}

//==========================================================================
// �֐��|�C���^
//==========================================================================
CEnemyBoss::ACT_FUNC CEnemyBoss::m_ActFuncList[] =
{
	&CEnemyBoss::ActChase,
	&CEnemyBoss::ActAttack,
	&CEnemyBoss::ActCharge,
};

//==========================================================================
//  �R���X�g���N�^
//==========================================================================
CEnemyBoss::CEnemyBoss(int nPriority) : CEnemy(nPriority)
{
	m_Act = ACTION_CHASE;		// �s��
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
// �s���X�V
//==========================================================================
void CEnemyBoss::UpdateAction(void)
{
	// ��ԕʏ���
	(this->*(m_ActFuncList[m_Act]))();
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
	switch (m_Act)
	{
	case CEnemyBoss::ACTION_CHASE:
		break;

	case CEnemyBoss::ACTION_CHASE_DASH:
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
// �U��
//==========================================================================
void CEnemyBoss::ActAttack(void)
{
	// �ړ��t���O�𗧂Ă�
	m_sMotionFrag.bMove = true;

	// �^�[�Q�b�g�̕�������
	RotationTarget();

	// �s���ʈړ�����
	switch (m_Act)
	{
	case CEnemyBoss::ACTION_CHASE:
		break;

	case CEnemyBoss::ACTION_CHASE_DASH:
		break;

	default:
		break;
	}
}

//==========================================================================
// �`���[�W
//==========================================================================
void CEnemyBoss::ActCharge(void)
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
//
////==========================================================================
////  �U��
////==========================================================================
//void CEnemyBoss::Attack(void)
//{
//	// �U������
//	CEnemy::StateAttack();
//
//	// ���[�V�����̏��擾
//	CMotion::Info aInfo = m_pMotion->GetInfo(m_pMotion->GetType());
//
//	// �U�����̑����擾
//	int nNumAttackInfo = aInfo.nNumAttackInfo;
//
//	bool bAtkWait = true;	// �U���ҋ@��
//	for (int nCntAttack = 0; nCntAttack < nNumAttackInfo; nCntAttack++)
//	{
//		if (aInfo.AttackInfo[nCntAttack] == NULL)
//		{// NULL��������
//			continue;
//		}
//
//		// ���[�V�����J�E���^�[�擾
//		if (m_pMotion->GetAllCount() > aInfo.AttackInfo[nCntAttack]->nMinCnt)
//		{// �U�����蒆
//			// �U�����蒆�ɂ���
//			bAtkWait = false;
//		}
//	}
//
//	if (bAtkWait == false)
//	{// ���蒆�̎�
//		return;
//	}
//}

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

