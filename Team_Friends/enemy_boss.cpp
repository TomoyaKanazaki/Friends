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
#include "blackframe.h"
#include "beam.h"
#include "particle.h"
#include "hp_gauge_boss.h"

//==========================================================================
// �萔��`
//==========================================================================
namespace
{
	// �s�����I�̍\����
	struct sProbability 
	{
		CEnemyBoss::ACTION action;	// �s��
		float fProbability;			// �m��
	};

	const float LENGTH_PUNCH = 300.0f;		// �p���`�̒���
	const float LENGTH_KICK = 500.0f;		// �L�b�N�̒���
	const float LENGTH_CHASEWALK = 800.0f;	// �����Ǐ]�̒���
	const float VELOCITY_WALK = 1.0f;		// ����
	const float VELOCITY_DASH = 3.5f;		// �_�b�V��
	const float VELOCITY_TACKLE = 6.0f;		// �^�b�N��
	const float TIME_WAIT = 2.0f;			// �ҋ@
	const float TIME_PROXIMITYCHASE = 5.0f;	// �ߐڍU���̒Ǐ]���ԍő�l
	std::vector<sProbability> ACT_PROBABILITY =	// �s���̒��I�m��
	{
		{ CEnemyBoss::ACTION_CHASE, 0.0f },			// �Ǐ]
		{ CEnemyBoss::ACTION_PROXIMITY, 0.5f },		// �ߐڍU��
		{ CEnemyBoss::ACTION_REMOTE, 0.3f },		// ���u�U��
		{ CEnemyBoss::ACTION_ASSAULT, 0.2f },		// �ˌ��U��
		{ CEnemyBoss::ACTION_WAIT, 0.0f },			// �ҋ@
		{ CEnemyBoss::ACTION_GUARD, 0.0f },			// �K�[�h
		{ CEnemyBoss::ACTION_SELFEXPLOSION, 0.0f },	// ����
	};
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
	&CEnemyBoss::ActWait,				// �ҋ@
	&CEnemyBoss::ActGuard,				// �K�[�h
	&CEnemyBoss::ActAttackExplosion,	// ����
};

//==========================================================================
//  �R���X�g���N�^
//==========================================================================
CEnemyBoss::CEnemyBoss(int nPriority) : CEnemy(nPriority)
{
	m_Action = ACTION_CHASE;		// �s��
	m_ActionBranch = ACTBRANCH_CHASE_SLOW;		// �s������
	m_MakeForActionBranch = ACTBRANCH_CHASE_SLOW;	// �s������ׂ̍s��
	m_TargetPosition = mylib_const::DEFAULT_VECTOR3;	// �ڕW�̈ʒu
	m_fActTime = 0.0f;			// �s���J�E���^�[
	m_fAssultLength = 0.0f;		// �ˌ�����
	m_fAssultLengthDest = 0.0f;	// �ڕW�̓ˌ�����
	m_bCatchUp = false;			// �ǂ���������
	m_pBossHPGauge = nullptr;	// �{�X��HP�Q�[�W
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
	m_pBossHPGauge = CHP_GaugeBoss::Create(D3DXVECTOR3(640.0f, 50.0f, 0.0f), GetLifeOrigin());	// �{�X��HP�Q�[�W
	m_pBossHPGauge->SetLife(0);

	// ���t���[���J����
	CManager::GetInstance()->GetBlackFrame()->SetState(CBlackFrame::STATE_OUT);

	// �s��
	m_Action = ACTION_WAIT;

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

	// HP�X�V
	m_pBossHPGauge->SetLife(GetLife());

	// ���t���[���J����
	if (CManager::GetInstance()->GetBlackFrame()->GetState() == CBlackFrame::STATE_INCOMPLETION)
	{
		CManager::GetInstance()->GetBlackFrame()->SetState(CBlackFrame::STATE_OUT);
	}
}

//==========================================================================
// �s���ݒ�
//==========================================================================
void CEnemyBoss::ActionSet(void)
{

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
// �s�����I
//==========================================================================
void CEnemyBoss::DrawingAction(void)
{

	// 0�`1�̃����_���l�擾
	float fRandomValue = static_cast<float>(std::rand()) / RAND_MAX;

	// �m�����Z�p�ϐ�
	float fDrawingProbability = 0.0;

	// �s�����I�v�f���J��Ԃ�
	for (const auto& candidate : ACT_PROBABILITY)
	{
		// ����̊m���������Z
		fDrawingProbability += candidate.fProbability;

		if (fRandomValue < fDrawingProbability)
		{// ����̃����_���l���m���𒴂�����

			// �s������
			m_Action = candidate.action;

			// �s���J�E���^�[���Z�b�g
			m_fActTime = 0.0f;
			break;
		}
	}

	// ���̍s����
	int nActRand;
	float fLength = 0.0f;
	switch (m_Action)
	{
	case CEnemyBoss::ACTION_CHASE:	// �Ǐ]
		if (CircleRange3D(GetPosition(), m_TargetPosition, LENGTH_CHASEWALK, 0.0f))
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

		// �s���ʈړ�����
		fLength = 0.0f;
		switch (m_ActionBranch)
		{
		case CEnemyBoss::ACTBRANCH_PROXIMITY_PUNCH:
			fLength = LENGTH_PUNCH;
			break;

		case CEnemyBoss::ACTBRANCH_PROXIMITY_KICK:
			fLength = LENGTH_KICK;
			break;
		}

		// �s������ׂ̍s������
		if (CircleRange3D(GetPosition(), m_TargetPosition, fLength, 0.0f))
		{// �U���͈͓�

			// �ǂ�������
			m_bCatchUp = true;
		}
		else
		{
			// �ǂ������ĂȂ�
			m_bCatchUp = false;

			if (CircleRange3D(GetPosition(), m_TargetPosition, LENGTH_CHASEWALK, 0.0f))
			{// �����͈̔�
				m_MakeForActionBranch = ACTBRANCH_CHASE_SLOW;
			}
			else
			{
				m_MakeForActionBranch = ACTBRANCH_CHASE_DASH;
			}
		}
		break;

	case CEnemyBoss::ACTION_REMOTE:	// ���u�U��
		m_ActionBranch = ACTBRANCH_REMOTE_BEAM;
		break;

	case CEnemyBoss::ACTION_ASSAULT:	// �ˌ��U��
		m_ActionBranch = ACTBRANCH_ASSAULT_CHARGE;
		m_fAssultLength = 0.0f;
		break;

	default:
		break;
	}
}

//==========================================================================
// �ҋ@
//==========================================================================
void CEnemyBoss::ActWait(void)
{
	// �ҋ@���[�V�����ݒ�
	m_pMotion->Set(MOTION_DEF);

	// �s���J�E���^�[���Z
	m_fActTime += CManager::GetInstance()->GetDeltaTime();

	// �^�[�Q�b�g�̕�������
	RotationTarget();

	if (TIME_WAIT <= m_fActTime)
	{// �ҋ@���Ԓ�������

		// �s�����I
		DrawingAction();
		m_fActTime = 0.0f;
	}
}


//==========================================================================
// �K�[�h
//==========================================================================
void CEnemyBoss::ActGuard(void)
{
	// �K�[�h���[�V�����ݒ�
	m_pMotion->Set(MOTION_GUARD);

	// �s���J�E���^�[���Z�b�g
	m_fActTime = 0.0f;

	// �^�[�Q�b�g�̕�������
	RotationTarget();
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
	// ���擾
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 rot = GetRotation();
	float fMove = GetVelocity();

	// �ړ��ʐݒ�
	move.x = sinf(D3DX_PI + rot.y) * fMove * VELOCITY_WALK;
	move.z = cosf(D3DX_PI + rot.y) * fMove * VELOCITY_WALK;

	// �ړ��ʐݒ�
	SetMove(move);
}

//==========================================================================
// �_�b�V���ǂ��|��
//==========================================================================
void CEnemyBoss::ChaseDash(void)
{
	// ���擾
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 rot = GetRotation();
	float fMove = GetVelocity();

	// �ړ��ʐݒ�
	move.x = sinf(D3DX_PI + rot.y) * fMove * VELOCITY_DASH;
	move.z = cosf(D3DX_PI + rot.y) * fMove * VELOCITY_DASH;

	// �ړ��ʐݒ�
	SetMove(move);
}

//==========================================================================
// �ߐڍU��
//==========================================================================
void CEnemyBoss::ActAttackProximity(void)
{
	if (m_bCatchUp == false)
	{// �ǂ������ĂȂ���

		// �^�[�Q�b�g�̕�������
		RotationTarget();

		// �ړ��t���O�𗧂Ă�
		m_sMotionFrag.bMove = true;

		// �s������ׂ̍s���ʈړ�����
		switch (m_MakeForActionBranch)
		{
		case CEnemyBoss::ACTBRANCH_CHASE_SLOW:
			ChaseSlow();
			break;

		case CEnemyBoss::ACTBRANCH_CHASE_DASH:
			ChaseDash();
			break;
		}

		// �s���ʈړ�����
		float fLength = 0.0f;
		switch (m_ActionBranch)
		{
		case CEnemyBoss::ACTBRANCH_PROXIMITY_PUNCH:
			fLength = LENGTH_PUNCH;
			break;

		case CEnemyBoss::ACTBRANCH_PROXIMITY_KICK:
			fLength = LENGTH_KICK;
			break;
		}

		// �ǂ���������
		m_bCatchUp = CircleRange3D(GetPosition(), m_TargetPosition, fLength, 0.0f);

		// �s���J�E���^�[���Z
		m_fActTime += CManager::GetInstance()->GetDeltaTime();;
		if (TIME_PROXIMITYCHASE <= m_fActTime)
		{
			// �ǂ���������
			m_bCatchUp = true;
		}
	}
	else
	{// �U���̒�����

		// �U���t���O�𗧂Ă�
		m_sMotionFrag.bATK = true;

		// �s���ʈړ�����
		switch (m_ActionBranch)
		{
		case CEnemyBoss::ACTBRANCH_PROXIMITY_PUNCH:
			AttackPunch();
			break;

		case CEnemyBoss::ACTBRANCH_PROXIMITY_KICK:
			AttackKick();
			break;
		}
	}
}

//==========================================================================
// �p���`�U��
//==========================================================================
void CEnemyBoss::AttackPunch(void)
{
	int nType = m_pMotion->GetType();
	if (nType == MOTION_PUNCH && m_pMotion->IsFinish() == true)
	{// �p���`�U�����I����Ă���

		// �ҋ@�s��
		m_Action = ACTION_WAIT;

		// �ҋ@���[�V�����ݒ�
		m_pMotion->Set(MOTION_DEF);
		return;
	}

	if (nType != MOTION_PUNCH)
	{
		// �p���`���[�V�����ݒ�
		m_pMotion->Set(MOTION_PUNCH);
	}

	// �U���t���O�𗧂Ă�
	m_sMotionFrag.bATK = true;
}

//==========================================================================
// �L�b�N�U��
//==========================================================================
void CEnemyBoss::AttackKick(void)
{
	int nType = m_pMotion->GetType();
	if (nType == MOTION_KICK && m_pMotion->IsFinish() == true)
	{// �L�b�N�U�����I����Ă���

		// �ҋ@�s��
		m_Action = ACTION_WAIT;

		// �ҋ@���[�V�����ݒ�
		m_pMotion->Set(MOTION_DEF);
		return;
	}

	if (nType != MOTION_KICK)
	{
		// �L�b�N���[�V�����ݒ�
		m_pMotion->Set(MOTION_KICK);
	}

	// �U���t���O�𗧂Ă�
	m_sMotionFrag.bATK = true;
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
	int nType = m_pMotion->GetType();
	if (nType == MOTION_BEAM && m_pMotion->IsFinish() == true)
	{// �r�[���U�����I����Ă���

		// �ҋ@�s��
		m_Action = ACTION_WAIT;

		// �ҋ@���[�V�����ݒ�
		m_pMotion->Set(MOTION_DEF);
		return;
	}

	if (nType != MOTION_BEAM)
	{
		// �r�[�����[�V�����ݒ�
		m_pMotion->Set(MOTION_BEAM);
	}

	// �U���t���O�𗧂Ă�
	m_sMotionFrag.bATK = true;
}

//==========================================================================
// �ˌ��U��
//==========================================================================
void CEnemyBoss::ActAttackAssault(void)
{

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
	int nType = m_pMotion->GetType();
	if (nType == MOTION_CHARGE_TACKLE && m_pMotion->IsFinish() == true)
	{// �^�b�N���`���[�W���I����Ă���

		// �^�b�N���s��
		m_ActionBranch = ACTBRANCH_ASSAULT_TACKLE;

		// �^�b�N���ݒ�
		m_pMotion->Set(MOTION_TACKLE);

		// �ڕW�Ƃ̋����Z�o
		m_fAssultLengthDest = GetFabsPosLength(GetPosition(), m_TargetPosition);
		
		// �ڕW�̓ˌ�����
		m_fAssultLengthDest *= 1.5f;
		return;
	}

	if (nType != MOTION_CHARGE_TACKLE)
	{
		// �^�b�N���`���[�W�ݒ�
		m_pMotion->Set(MOTION_CHARGE_TACKLE);
	}

	// �^�[�Q�b�g�̕�������
	RotationTarget();

	// �`���[�W�t���O�𗧂Ă�
	m_sMotionFrag.bCharge = true;
}

//==========================================================================
// �^�b�N���U��
//==========================================================================
void CEnemyBoss::AttackTackle(void)
{
	if (m_fAssultLength >= m_fAssultLengthDest)
	{// �^�b�N���U�����ڕW�̒������ړ�������

		// �ҋ@�s��
		m_Action = ACTION_WAIT;

		// �ҋ@���[�V�����ݒ�
		m_pMotion->Set(MOTION_DEF);
		return;
	}

	// �ˌ��̋���
	float fMove = GetVelocity();
	m_fAssultLength += fMove * VELOCITY_TACKLE;

	// �U�����蒆�ɒǉ�����\��
#if 1
	// ���擾
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 rot = GetRotation();

	// �^�b�N���ړ��ʐݒ�
	move.x = sinf(D3DX_PI + rot.y) * fMove * VELOCITY_TACKLE;
	move.z = cosf(D3DX_PI + rot.y) * fMove * VELOCITY_TACKLE;

	// �ړ��ʐݒ�
	SetMove(move);
#endif

	if (m_pMotion->GetType() != MOTION_TACKLE)
	{
		// �^�b�N�����[�V�����ݒ�
		m_pMotion->Set(MOTION_TACKLE);
	}

	// �U���t���O�𗧂Ă�
	m_sMotionFrag.bATK = true;
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
	if (m_pHPGauge != nullptr)
	{
		m_pBossHPGauge->Kill();
		m_pBossHPGauge = nullptr;
	}

	// ���S����
	CEnemy::Kill();
}

//==========================================================================
//  ���[�V�����Z�b�g
//==========================================================================
void CEnemyBoss::MotionSet(void)
{
	if (m_Action == ACTION_GUARD)
	{
		return;
	}

	if (m_pMotion->IsFinish() == true)
	{// �I�����Ă�����

		// ���݂̎�ގ擾
		int nType = m_pMotion->GetType();

		if (m_sMotionFrag.bMove == true && m_sMotionFrag.bKnockback == false && m_sMotionFrag.bATK == false)
		{// �ړ����Ă�����

			// �U�����Ă��Ȃ�
			m_sMotionFrag.bATK = false;

			// �s���ʐݒ菈��
			switch (m_MakeForActionBranch)
			{
			case CEnemyBoss::ACTBRANCH_CHASE_SLOW:
				m_pMotion->Set(MOTION_WALK);
				break;

			case CEnemyBoss::ACTBRANCH_CHASE_DASH:
				m_pMotion->Set(MOTION_DASH);
				break;
			}
		}
		else if (m_sMotionFrag.bKnockback == true)
		{// ���ꒆ��������

			// ���ꃂ�[�V����
			m_pMotion->Set(MOTION_KNOCKBACK);
		}
		else if (m_sMotionFrag.bCharge == true)
		{// �`���[�W����������
			
			m_sMotionFrag.bCharge = false;
			// �`���[�W���[�V����
			m_pMotion->Set(MOTION_CHARGE_TACKLE);
		}
		else if (m_sMotionFrag.bATK == true)
		{// �U�����Ă�����

			// �U������OFF
			m_sMotionFrag.bATK = false;

			// �s���ʐݒ菈��
			switch (m_ActionBranch)
			{
			case ACTBRANCH_PROXIMITY_PUNCH:
				m_pMotion->Set(MOTION_PUNCH);
				break;

			case ACTBRANCH_PROXIMITY_KICK:
				m_pMotion->Set(MOTION_KICK);
				break;

			case ACTBRANCH_REMOTE_BEAM:
				m_pMotion->Set(MOTION_BEAM);
				break;

			case ACTBRANCH_ASSAULT_TACKLE:
				m_pMotion->Set(MOTION_TACKLE);
				break;
			}
		}
		//else
		//{
		//	// �j���[�g�������[�V����
		//	m_pMotion->Set(MOTION_DEF);
		//}
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
	rot.y += fRotDiff * 0.1f;
	RotNormalize(rot.y);

	// �����ݒ�
	SetRotation(rot);

	// �ڕW�̌����ݒ�
	SetRotDest(fRotDest);
}

//==========================================================================
// �U��������
//==========================================================================
void CEnemyBoss::AttackAction(int nModelNum, CMotion::AttackInfo ATKInfo)
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
	case MOTION_PUNCH:
		break;

	case MOTION_KICK:
		break;

	case MOTION_BEAM:
	{
		D3DXCOLOR col = D3DXCOLOR(
			0.5f + Random(-100, 100) * 0.001f,
			0.1f + Random(-100, 100) * 0.001f,
			0.5f + Random(-100, 100) * 0.001f,	// �F
			1.0f);

		CBeam::Create(
			weponpos,	// �ʒu
			D3DXVECTOR3(
				sinf(D3DX_PI + rot.y) * 100.0f,
				cosf(D3DX_PI * 0.55f) * 100.0f,
				cosf(D3DX_PI + rot.y) * 100.0f),	// �ړ���
			col,	// �F
			60.0f,	// ���a
			400.0f,	// ����
			30,		// ����
			32,		// ���x
			1,		// �_���[�W
			CCollisionObject::TAG_ENEMY	// �^�O
		);
	}
	break;

	case MOTION_CHARGE_TACKLE:
		break;

	case MOTION_TACKLE:
		break;
	}
}

//==========================================================================
// �U�����蒆����
//==========================================================================
void CEnemyBoss::AttackInDicision(CMotion::AttackInfo ATKInfo)
{
	// ���̍U�����蒆����
	CEnemy::AttackInDicision(ATKInfo);

	// ���[�V�������擾
	int nMotionType = m_pMotion->GetType();
	D3DXVECTOR3 weponpos = m_pMotion->GetAttackPosition(GetModel(), ATKInfo);

	// ���[�V�����ʏ���
	switch (nMotionType)
	{
	case MOTION_PUNCH:
		break;

	case MOTION_KICK:
		break;

	case MOTION_BEAM:
		my_particle::Create(weponpos, my_particle::TYPE_ATTACK_BODY);
		break;

	case MOTION_CHARGE_TACKLE:
		break;

	case MOTION_TACKLE:
		break;
	}
}

//==========================================================================
// �ڕW�̈ʒu�ݒ�
//==========================================================================
void CEnemyBoss::SetTargetPosition(D3DXVECTOR3 pos)
{
	m_TargetPosition = pos;
}
