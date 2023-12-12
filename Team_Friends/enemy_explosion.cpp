//==========================================
//
//  ��������G(enemy_explosion.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_explosion.h"
#include "player.h"
#include "manager.h"
#include "debugproc.h"
#include "calculation.h"
#include "hp_gauge.h"
#include "explosion.h"
#include "camera.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const float SEARCH_LENGTH = 1000.0f; // ���G�͈�
	const float EXPLOSION_LENGTH = 200.0f; // ��������
	const float TURN_SPEED = 0.05f; // �U��������x
	const float WALK_TIME = 4.0f; // �ړ�����
	const float COUNT_DAWN = 3.0f; // �J�E���g�_�E���̎���
	const float FLASH_SPEED = 10.0f; // �_�ł̑��x
	const float CHASE_SPEED = 2.5f; // �ǐՒ��̈ړ��{��
}

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemyExplosion::CEnemyExplosion(int nPriority) :
	m_Act(ACTION_ROAMING),
	m_fCntWalk(0.0f),
	m_fCntFind(0.0f),
	m_fCntEscape(0.0f),
	m_fRot(0.0f),
	m_fCountDawn(0.0f),
	m_fCol(0.0f)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemyExplosion::~CEnemyExplosion()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemyExplosion::Init(void)
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
void CEnemyExplosion::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemyExplosion::Update(void)
{
	// ���S�̔���
	if (IsDeath() == true)
	{// ���S�t���O�������Ă�����
		return;
	}

	// �s���ω�
	ActionSet();

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
void CEnemyExplosion::UpdateAction(void)
{
	if (m_state == STATE_DEAD ||
		m_state == STATE_FADEOUT)
	{
		return;
	}

	// �s�����Ƃ̍s��
	switch (m_Act)
	{
	case CEnemyExplosion::ACTION_ROAMING:

		// �����_���ȕ����]��
		RandTurn();

		// �ړ�
		Move();

		break;

	case CEnemyExplosion::ACTION_CHASE:

		// �v���C���[������
		RotationPlayer();

		// �ړ�
		Move();

		break;

	case CEnemyExplosion::ACTION_COUNTDOWN:

		// �v���C���[������
		RotationPlayer();

		// �ړ�
		Move();

		// �J�E���^�[�����Z
		m_fCountDawn += CManager::GetInstance()->GetDeltaTime();

		// �_��
		Flash();

		break;

	case ACTION_EXPROSION:

		// �v���C���[������
		RotationPlayer();

		break;

	case CEnemyExplosion::ACTION_FADE:

		// �����Ă���
		SetState(STATE_FADEOUT);

		break;

	default:
		break;
	}
}

//==========================================
//  �ړ�
//==========================================
void CEnemyExplosion::Move(void)
{
	// �ړ��t���O�𗧂Ă�
	m_sMotionFrag.bMove = true;

	// �p�x�̎擾
	D3DXVECTOR3 rot = GetRotation();

	// �ړ��ʂ��擾
	float fMove = GetVelocity();
	D3DXVECTOR3 move = GetMove();

	// �ړ��ʂɔ{����������
	if (m_Act != CEnemyExplosion::ACTION_ROAMING)
	{
		fMove *= CHASE_SPEED;
	}

	// �ړ��ʂ𕪉�����
	move.x = -sinf(rot.y) * fMove;
	move.z = -cosf(rot.y) * fMove;

	// �ړ��ʂ�K�p����
	SetMove(move);
}


//==========================================
//  �����_���ȕ����]��
//==========================================
void CEnemyExplosion::RandTurn(void)
{
	// �J�E���^�[�̉��Z
	m_fCntWalk += CManager::GetInstance()->GetDeltaTime();

	// ���ԓ���������֐��𔲂���
	if (m_fCntWalk < WALK_TIME)
	{
		// �ڕW�Ƃ̍���
		D3DXVECTOR3 rot = GetRotation();
		float fRotDiff = m_fRot - rot.y;

		//�p�x�̐��K��
		RotNormalize(fRotDiff);

		//�p�x�̕␳������
		rot.y += fRotDiff * TURN_SPEED;

		// �p�x�̐��K��
		RotNormalize(rot.y);

		// �����ݒ�
		SetRotation(rot);

		return;
	}

	// ��莞�Ԍo�߂��Ă����ꍇ���Z�b�g����
	m_fCntWalk = 0.0f;

	// �ړ�������ݒ�
	m_fRot = (float)(rand() % 624) * 0.01f - D3DX_PI;
}

//==========================================
//  �`�揈��
//==========================================
void CEnemyExplosion::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//==========================================
//  �E��
//==========================================
void CEnemyExplosion::Kill(void)
{
	// ���S����
	CEnemy::Kill();
}

//==========================================
//  ���[�V�����Z�b�g
//==========================================
void CEnemyExplosion::MotionSet(void)
{
	if (m_pMotion->IsFinish() == true)
	{// �I�����Ă�����

		// ���݂̎�ގ擾
		int nType = m_pMotion->GetType();

		if (m_Act == ACTION_EXPROSION)
		{ // �������

			// �������[�V����
			m_pMotion->Set(MOTION_ATK);
		}
		else if (m_sMotionFrag.bMove == true && m_sMotionFrag.bKnockback == false)
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
void CEnemyExplosion::ActionSet(void)
{
	// ���ŏ�Ԃ̏ꍇ�͔�����
	if (m_Act == ACTION_FADE)
	{
		return;
	}

	if (m_Act == ACTION_EXPROSION)
	{
		// �������[�V�������I������������
		if (m_pMotion->IsFinish())
		{
			m_Act = ACTION_FADE;
		}

		return;
	}

	// �J�E���g�_�E�����͕ς��Ȃ�
	if (m_Act == ACTION_COUNTDOWN)
	{
		// �J�E���g�_�E�������������甚��
		if (m_fCountDawn >= COUNT_DAWN)
		{
			m_sMotionFrag.bMove = false;
			m_Act = ACTION_EXPROSION;
		}

		return;
	}

	if (CalcLenPlayer(EXPLOSION_LENGTH))
	{
		// �������Ƃ��Ă��߂��Ɣ���
		m_Act = ACTION_COUNTDOWN;
	}
	else if (CalcLenPlayer(SEARCH_LENGTH))
	{
		// �������߂��Ɣ�����ԂɂȂ�
		m_Act = ACTION_CHASE;
	}
	else // ��L�ȊO�Ȃ�ҋ@���
	{
		m_Act = ACTION_ROAMING;
	}
}

//==========================================
//  �_��
//==========================================
void CEnemyExplosion::Flash(void)
{
	// �}�e���A���J���[���X�V
	m_mMatcol.g = cosf(m_fCol) * 0.5f + 0.5f;
	m_mMatcol.b = cosf(m_fCol) * 0.5f + 0.5f;

	// �J�E���^��ǉ�
	m_fCol += CManager::GetInstance()->GetDeltaTime() * FLASH_SPEED;
}


//==========================================================================
// �U��������
//==========================================================================
void CEnemyExplosion::AttackAction(int nModelNum, CMotion::AttackInfo ATKInfo)
{
	// ���[�V�������擾
	int nMotionType = m_pMotion->GetType();
	D3DXVECTOR3 weponpos = m_pMotion->GetAttackPosition(GetModel(), ATKInfo);

	// ���擾
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();

	// ���[�V�����ʏ���
	switch (nMotionType)
	{
	case MOTION_ATK:
		CExplosion::Create(CExplosion::TYPE_ENEMY, pos, 180.0f);
		// �U��
		CManager::GetInstance()->GetCamera()->SetShake(12, 20.0f, 0.0f);
		break;
	}
}

//==========================================================================
// �U�����蒆����
//==========================================================================
void CEnemyExplosion::AttackInDicision(CMotion::AttackInfo ATKInfo)
{
	// ���̍U�����蒆����
	CEnemy::AttackInDicision(ATKInfo);

	// ���[�V�������擾
	int nMotionType = m_pMotion->GetType();
	D3DXVECTOR3 weponpos = m_pMotion->GetAttackPosition(GetModel(), ATKInfo);

	// ���[�V�����ʏ���
	switch (nMotionType)
	{
	case MOTION_ATK:
		break;
	}
}