//==========================================
//
//  �M�K���g�G�b�W(enemy_riot.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_riot.h"
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
	const float ATTACK_LENGTH = 200.0f; // �U�����鋗��
	const float MOVE_SPEED = 0.01f; // �ړ����x(�{��)
}

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemyRiot::CEnemyRiot(int nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemyRiot::~CEnemyRiot()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemyRiot::Init(void)
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
void CEnemyRiot::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemyRiot::Update(void)
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
//  �`�揈��
//==========================================
void CEnemyRiot::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//==========================================
//  �E��
//==========================================
void CEnemyRiot::Kill(void)
{
	// ���S����
	CEnemy::Kill();
}

//==========================================
//  ���[�V�����Z�b�g
//==========================================
void CEnemyRiot::MotionSet(void)
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
//  �s���Z�b�g
//==========================================
void CEnemyRiot::ActionSet(void)
{

}

//==========================================
//  �ړ�
//==========================================
void CEnemyRiot::Move(void)
{

}

//==========================================
//  �U��
//==========================================
void CEnemyRiot::Attack(void)
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
