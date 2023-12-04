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
	const float MOVE_SPEED = 300.0f; // �ړ����x
	const float WAIT_TIMER = 3.0f; // �����ҋ@����
	const float ROTATION_TIMER = 1.0f; // �����킹�ɗv���鎞��
	const float TACKLE_TIMER = 2.0f; // �����킹�ɗv���鎞��
}

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemyRiot::CEnemyRiot(int nPriority) :
	m_Act(ACTION_DEF),
	m_fWaitTime(0.0f)
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

		// �ꍇ����
		switch (m_Act)
		{
		case ACTION_DEF: // �ҋ@�s��
			m_pMotion->Set(MOTION_DEF); // �ҋ@���[�V����
			break;

		case ACTION_MOVE: // �ړ��s��
			m_pMotion->Set(MOTION_WALK); // �ړ����[�V����
			break;

		case ACTION_AXIS: // �����킹�s��
			m_pMotion->Set(MOTION_DEF); // �ҋ@���[�V����
			break;

		case ACTION_TACKLE: // �ːi�s��
			m_pMotion->Set(MOTION_WALK); // �ړ����[�V����
			break;

		case ACTION_ATTACK: // �U���s��
			m_pMotion->Set(MOTION_ATK); // �U�����[�V����
			break;

		default:
			m_pMotion->Set(MOTION_DEF); // �ҋ@���[�V����
			break;
		}
	}
}

//==========================================
//  �s���Z�b�g
//==========================================
void CEnemyRiot::ActionSet(void)
{
	// �f�o�b�O�\��
	CManager::GetInstance()->GetDebugProc()->Print
	(
		"�J�E���^�[ : %f\n"
		"���{�X�̃A�N�V���� : ",
		m_fWaitTime
	);

	switch (m_Act)
	{
	case ACTION_ATTACK: // �U�����

		if (m_pMotion->IsFinish())
		{
			//�����킹�Ɉڍs
			m_Act = ACTION_AXIS;
		}
		else
		{
			// �ҋ@���Ԃ����Z
			m_fWaitTime += CManager::GetInstance()->GetDeltaTime();

			// �U��������
			Attack();
		}

		// �f�o�b�O�\��
		CManager::GetInstance()->GetDebugProc()->Print
		(
			"�U��\n\n"
		);

		break;

	case ACTION_TACKLE: // �ːi���

		if (m_fWaitTime >= TACKLE_TIMER)
		{
			// �ҋ@���Ԃ����Z�b�g
			m_fWaitTime = 0.0f;

			//�����킹�Ɉڍs
			m_Act = ACTION_AXIS;
		}
		else
		{
			// �ҋ@���Ԃ����Z
			m_fWaitTime += CManager::GetInstance()->GetDeltaTime();

			// �^�b�N��
			Move();
		}

		// �f�o�b�O�\��
		CManager::GetInstance()->GetDebugProc()->Print
		(
			"�ːi\n\n"
		);

		break;

	case ACTION_AXIS: // �����킹���

		if (m_fWaitTime >= ROTATION_TIMER)
		{
			// �ҋ@���Ԃ����Z�b�g
			m_fWaitTime = 0.0f;

			// �v���C���[�Ƃ̋������v��
			if (CalcLenPlayer(ATTACK_LENGTH)) // �߂���΍U��
			{
				m_Act = ACTION_ATTACK;
			}
			else // ����������^�b�N��
			{
				m_Act = ACTION_TACKLE;
			}
		}
		else
		{
			// �ҋ@���Ԃ����Z
			m_fWaitTime += CManager::GetInstance()->GetDeltaTime();

			// �v���C���[�̕���������
			RotationPlayer();
		}

		// �f�o�b�O�\��
		CManager::GetInstance()->GetDebugProc()->Print
		(
			"�����킹\n\n"
		);

		break;

	case ACTION_DEF: // �����ҋ@���

		if (m_fWaitTime >= WAIT_TIMER)
		{
			// �ҋ@���Ԃ����Z�b�g
			m_fWaitTime = 0.0f;

			//�����킹�Ɉڍs
			m_Act = ACTION_AXIS;
		}
		else
		{
			// �ҋ@���Ԃ����Z
			m_fWaitTime += CManager::GetInstance()->GetDeltaTime();
		}

		// �f�o�b�O�\��
		CManager::GetInstance()->GetDebugProc()->Print
		(
			"�ҋ@\n\n"
		);

		break;

	default:
		break;
	}
}

//==========================================
//  �ړ�
//==========================================
void CEnemyRiot::Move(void)
{
	// �p�x�̎擾
	D3DXVECTOR3 rot = GetRotation();

	// �ړ��ʂ��擾
	D3DXVECTOR3 move = GetMove();

	// �ړ��ʂ𕪉�����
	move.x = -cosf(rot.y) * MOVE_SPEED * CManager::GetInstance()->GetDeltaTime();
	move.z = -sinf(rot.y) * MOVE_SPEED * CManager::GetInstance()->GetDeltaTime();

	// �ړ��ʂ�K�p����
	SetMove(move);
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
