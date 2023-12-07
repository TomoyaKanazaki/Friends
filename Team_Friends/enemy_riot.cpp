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
#include "camera.h"
#include "particle.h"
#include "3D_Effect.h"
#include "impactwave.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const float ATTACK_LENGTH = 200.0f; // �U�����鋗��
	const float WAIT_TIMER = 2.0f; // �����ҋ@����
	const float ROTATION_TIMER = 1.0f; // �����킹�ɗv���鎞��
	const float TACKLE_TIMER = 1.0f; // �ːi���鎞��
	const int MAX_ATTACK = 3; // �A���U���̍ő吔
}

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemyRiot::CEnemyRiot(int nPriority) :
	m_Act(ACTION_DEF),
	m_fWaitTime(0.0f),
	m_nCntAction(0)
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

	// �o���ҋ@��Ԃɂ���
	m_state = STATE_SPAWNWAIT;
	m_Act = ACTION_SPAWN;

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

	// �X�N���[�����̑��ݔ���
	if (m_state == STATE_SPAWNWAIT && CManager::GetInstance()->GetCamera()->OnScreen(GetPosition()))
	{
		m_state = STATE_SPAWN;
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
		}
	}
}

//==========================================
// �X�|�[��
//==========================================
void CEnemyRiot::Spawn(void)
{
	// ���c����ցA�R�s�[���Ă�
	int nType = m_pMotion->GetType();
	if (nType == MOTION_SPAWN && m_pMotion->IsFinish() == true)
	{// �o�ꂪ�I����Ă���

		// �Ȃɂ��Ȃ�
		m_state = STATE_NONE;
		m_Act = ACTION_DEF;
		return;
	}

	// ���[�V�����J�E���^�[�擾
	float fAllCount = m_pMotion->GetAllCount();
	if ((int)fAllCount % 10 == 0)
	{
		// �p�x�̎擾
		D3DXVECTOR3 rot = GetRotation();

		// �Ռ��g����
		CImpactWave *pWave = CImpactWave::Create
		(
			GetCenterPosition(),	// �ʒu
			D3DXVECTOR3((float)Random(-31, 31) * 0.1f, D3DX_PI * 0.5f + rot.y, 0.0f),	// ����
			D3DXCOLOR(0.9f, 0.2f, 0.9f, 0.8f),	// �F
			150.0f,								// ��
			0.0f,								// ����
			90.0f,								// ���S����̊Ԋu
			20,									// ����
			8.0f,								// ���̈ړ���
			CImpactWave::TYPE_GIZAGRADATION,	// �e�N�X�`���^�C�v
			true								// ���Z�������邩
		);
	}

	if ((int)fAllCount % 12 == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			int repeat = (int)(fAllCount / 12.0f);
			CEffect3D::Create(
				GetCenterPosition(),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.9f, 0.2f, 0.9f, 1.0f),
				20.0f, 20, CEffect3D::MOVEEFFECT_ADD, CEffect3D::TYPE_NORMAL, repeat * 2.0f);
		}
	}

	// �o�ꉉ�o
	my_particle::Create(GetCenterPosition(), my_particle::TYPE_UNDERBOSS_SPAWN);

	if (nType != MOTION_SPAWN)
	{
		// �o�ꃂ�[�V�����ݒ�
		m_pMotion->Set(MOTION_SPAWN);
	}
}

//==========================================
//  �s���Z�b�g
//==========================================
void CEnemyRiot::ActionSet(void)
{

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

		break;

	case ACTION_AXIS: // �����킹���

		if (m_fWaitTime >= ROTATION_TIMER)
		{
			// �ҋ@���Ԃ����Z�b�g
			m_fWaitTime = 0.0f;

			// �v���C���[�Ƃ̋������v��
			if (CalcLenPlayer(ATTACK_LENGTH) && m_nCntAction <= MAX_ATTACK) // �߂���΍U��
			{
				m_Act = ACTION_ATTACK;
				++m_nCntAction;
			}
			else // ����������^�b�N��
			{
				m_Act = ACTION_TACKLE;
				m_nCntAction = 0;
			}
		}
		else
		{
			// �ҋ@���Ԃ����Z
			m_fWaitTime += CManager::GetInstance()->GetDeltaTime();

			// �v���C���[�̕���������
			RotationPlayer();
		}

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
	float fMove = GetVelocity();
	D3DXVECTOR3 move = GetMove();

	// �ړ��ʂ𕪉�����
	move.x = -sinf(rot.y) * fMove * CManager::GetInstance()->GetDeltaTime();
	move.z = -cosf(rot.y) * fMove * CManager::GetInstance()->GetDeltaTime();

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
