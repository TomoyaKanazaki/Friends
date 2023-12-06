//==========================================
//
//  �p�j����G(enemy_roaming.cpp)
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
	const float ATTACK_LENGTH = 200.0f; // �U�����鋗��
	const float ROTATION_SPEED = D3DX_PI * 0.25f; // ��]���x
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

		// ��]
		Rotation();

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

		if (m_sMotionFrag.bMove == true && m_sMotionFrag.bKnockback == false && m_sMotionFrag.bATK == false)
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
//  ��]�Ƃ���ɔ����ړ�
//==========================================
void CEnemyRoaming::Rotation(void)
{
	// ����̉�]�p�x���Z�o
	float fRotation = ROTATION_SPEED * CManager::GetInstance()->GetDeltaTime();

	// ���݂̊p�x���擾
	D3DXVECTOR3 rot = GetRotation();

	// �p�x�����Z
	rot.y += fRotation;

	// �p�x��K�p
	SetRotation(rot);
}

//==========================================
//  �ړ�
//==========================================
void CEnemyRoaming::Move(void)
{
	// ���݂̊p�x���擾
	D3DXVECTOR3 rot = GetRotation();

	// �ړ��ʂ��擾
	float fMove = GetVelocity();
	D3DXVECTOR3 move;

	// �p�x�𕪉�
	move.x = -sinf(rot.y) * fMove;
	move.z = -cosf(rot.y) * fMove;

	// �ړ��ʂ�K�p
	SetMove(move);
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
		float fAllCount = m_pMotion->GetAllCount();
		if (fAllCount > aInfo.AttackInfo[nCntAttack]->nMinCnt && fAllCount < aInfo.AttackInfo[nCntAttack]->nMaxCnt)
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
