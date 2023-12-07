//==========================================================================
// 
//  ���{�X(�C��) [enemy_turret.cpp]
//  Author : ���c����
//
//==========================================================================
#include "enemy_turret.h"
#include "manager.h"
#include "debugproc.h"
#include "calculation.h"
#include "hp_gauge.h"
#include "limitarea.h"
#include "beam.h"
#include "bullet.h"
#include "player.h"
#include "camera.h"
#include "game.h"
#include "gamemanager.h"
#include "particle.h"
#include "3D_Effect.h"
#include "impactwave.h"

//==========================================================================
//  �萔��`
//==========================================================================
namespace
{
	// �s�����I�̍\����
	struct sProbability
	{
		CEnemyTurret::ACTION action;	// �s��
		float fProbability;			// �m��
	};

	const float VELOCITY_TACKLE = 2.0f;		// �^�b�N��
	const float MORTAR_SPEED = 10.0f;		// �����e���x
	const float TIME_WAIT = 3.0f;			// �ҋ@
	const float SEARCH_LENGTH = 600.0f;		//�G���A��������
	const float AREA_LENGTH = 800.0f;		//�{�X�G���A�T�C�Y
	const float BEAM_LENGTH = 1000.0f;		//�r�[���̒���
	const D3DXCOLOR BEAM_COLOR = { 0.5f, 0.1f, 1.0f, 0.5f};		//�r�[���̐F
	std::vector<sProbability> ACT_PROBABILITY =	// �s���̒��I�m��
	{
		{ CEnemyTurret::ACTION_BEAM, 0.3f },		// �r�[���U��
		{ CEnemyTurret::ACTION_MORTAR, 0.7f },		// �����U��
		{ CEnemyTurret::ACTION_WAIT, 0.0f },		// �ҋ@
	};
}

//==========================================================================
// �֐��|�C���^
//==========================================================================
CEnemyTurret::ACT_FUNC CEnemyTurret::m_ActFuncList[] =
{
	&CEnemyTurret::ActAttackBeam,		// ���u
	&CEnemyTurret::ActAttackMortar,		// �ˌ�
	&CEnemyTurret::ActWait,				// �ҋ@
	&CEnemyTurret::Spawn,				// �X�|�[��
};

//==========================================================================
//  �R���X�g���N�^
//==========================================================================
CEnemyTurret::CEnemyTurret(int nPriority) : CEnemy(nPriority)
{
	m_Action = ACTION_WAIT;		// �s��
	m_ActionBranch = ACTBRANCH_MORTAR_CHARGE;		// �s������
	m_MakeForActionBranch = ACTBRANCH_MORTAR_CHARGE;	// �s������ׂ̍s��
	m_TargetPosition = mylib_const::DEFAULT_VECTOR3;	// �ڕW�̈ʒu
	m_fActTime = 0.0f;			// �s���J�E���^�[
	m_fRotLock = 0.0f;
	m_pLimitArea = nullptr;
	m_bArea = false;
}

//==========================================================================
//  �f�X�g���N�^
//==========================================================================
CEnemyTurret::~CEnemyTurret()
{

}

//==========================================================================
//  ����������
//==========================================================================
HRESULT CEnemyTurret::Init(void)
{
	//����������
	CEnemy::Init();

	// HP�̐ݒ�
	m_pHPGauge = CHP_Gauge::Create(100.0f, GetLifeOrigin());

	// �o���ҋ@��Ԃɂ���
	m_state = CEnemy::STATE_SPAWNWAIT;
	m_Action = ACTION_SPAWN;

	return S_OK;
}

//==========================================================================
//  �I������
//==========================================================================
void CEnemyTurret::Uninit(void)
{
	CScene *pScene = CManager::GetInstance()->GetScene();

	//�Q�[���Ȃ�v���C���[�i��
	if (pScene != nullptr)
	{
		if (pScene->GetMode() == CScene::MODE_GAME)
		{
			if (!CGame::GetGameManager()->IsSetEvolusion())
			{
				CGame::GetGameManager()->SetEnableEvolusion();
			}
		}
	}

	if (m_pLimitArea != nullptr)
	{
		m_pLimitArea->SetState(CLimitArea::STATE_FADEOUT);
	}

	// �I������
	CEnemy::Uninit();
}

//==========================================================================
//  �X�V����
//==========================================================================
void CEnemyTurret::Update(void)
{
	if (m_bArea == false)
	{//�G���A�������Ȃ�
		SummonArea();
	}

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
	if (m_state == CEnemy::STATE_SPAWNWAIT && CManager::GetInstance()->GetCamera()->OnScreen(GetPosition()))
	{
		m_state = STATE_SPAWN;
	}
}

//==========================================================================
// �s���ݒ�
//==========================================================================
void CEnemyTurret::ActionSet(void)
{

}

//==========================================================================
// �s���X�V
//==========================================================================
void CEnemyTurret::UpdateAction(void)
{
	// ��ԕʏ���
	(this->*(m_ActFuncList[m_Action]))();
}

//==========================================
// �X�|�[��
//==========================================
void CEnemyTurret::Spawn(void)
{
	if (m_state == STATE_SPAWNWAIT)
	{
		return;
	}

	int nType = m_pMotion->GetType();

	if (nType == MOTION_SPAWN && m_pMotion->IsFinish() == true)
	{// �o�ꂪ�I����Ă���

	 // �Ȃɂ��Ȃ�
		m_state = STATE_NONE;
		m_Action = ACTION_WAIT;
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

//==========================================================================
// �s�����I
//==========================================================================
void CEnemyTurret::DrawingAction(void)
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
	switch (m_Action)
	{
	case CEnemyTurret::ACTION_BEAM:	// ���u�U��
		m_ActionBranch = ACTBRANCH_BEAM_CHARGE;
		break;

	case CEnemyTurret::ACTION_MORTAR:	// �ˌ��U��
		m_ActionBranch = ACTBRANCH_MORTAR_CHARGE;
		break;

	default:
		break;
	}
}

//==========================================================================
// �ҋ@
//==========================================================================
void CEnemyTurret::ActWait(void)
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
// �r�[���U��
//==========================================================================
void CEnemyTurret::ActAttackBeam(void)
{
	// �U���t���O�𗧂Ă�
	m_sMotionFrag.bATK = true;

	// �^�[�Q�b�g�̕�������
	RotationTarget();

	// �s���ʈړ�����
	switch (m_ActionBranch)
	{
	case CEnemyTurret::ACTBRANCH_BEAM_CHARGE:
		ChargeBeam();
		break;

	case CEnemyTurret::ACTBRANCH_BEAM_SHOT:
		AttackBeam();
		break;

	default:
		break;
	}
}

//==========================================================================
// �r�[���`���[�W
//==========================================================================
void CEnemyTurret::ChargeBeam(void)
{
	int nType = m_pMotion->GetType();

	if (nType == MOTION_CHARGE_BEAM && m_pMotion->IsFinish() == true)
	{// �r�[���`���[�W���I����Ă���

	 // �r�[���s��
		m_ActionBranch = ACTBRANCH_BEAM_SHOT;

		// �r�[���ݒ�
		m_pMotion->Set(MOTION_BEAM);
	}

	if (nType != MOTION_CHARGE_BEAM)
	{
		// �r�[���`���[�W�ݒ�
		m_pMotion->Set(MOTION_CHARGE_BEAM);
	}

	//��ԋ߂��v���C���[��F������
	SetTargetPlayer();

	// �^�[�Q�b�g�̕�������
	RotationTarget();

	// �`���[�W�t���O�𗧂Ă�
	m_sMotionFrag.bCharge = true;
}

//==========================================================================
// �r�[������
//==========================================================================
void CEnemyTurret::AttackBeam(void)
{
	int nType = m_pMotion->GetType();

	if (nType == MOTION_BEAM && m_pMotion->IsFinish() == true)
	{// �r�[���U�����I����Ă���

		float fRot = GetRotation().y;
		D3DXVECTOR3 move = {sinf(fRot + D3DX_PI) * MORTAR_SPEED,
							0.0f,
							cosf(fRot + D3DX_PI) * MORTAR_SPEED };

		CBeam::Create(GetPosition(), move, BEAM_COLOR, 50.0f, BEAM_LENGTH, 50, 10, 1, CCollisionObject::TAG_ENEMY);

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
// �����U��
//==========================================================================
void CEnemyTurret::ActAttackMortar(void)
{
	// �s���ʈړ�����
	switch (m_ActionBranch)
	{
	case CEnemyTurret::ACTBRANCH_MORTAR_CHARGE:
		ChargeMortar();
		break;

	case CEnemyTurret::ACTBRANCH_MORTAR_SHOT:
		AttackMortar();
		break;

	default:
		break;
	}
}

//==========================================================================
// �����`���[�W
//==========================================================================
void CEnemyTurret::ChargeMortar(void)
{
	int nType = m_pMotion->GetType();

	if (nType == MOTION_CHARGE_MORTAR && m_pMotion->IsFinish() == true)
	{// �^�b�N���`���[�W���I����Ă���

		 // �^�b�N���s��
		m_ActionBranch = ACTBRANCH_MORTAR_SHOT;

		// �^�b�N���ݒ�
		m_pMotion->Set(MOTION_MORTAR);

		return;
	}

	if (nType != MOTION_CHARGE_MORTAR)
	{
		// �^�b�N���`���[�W�ݒ�
		m_pMotion->Set(MOTION_CHARGE_MORTAR);
	}

	// �^�[�Q�b�g�̕�������
	RotationTarget();

	// �`���[�W�t���O�𗧂Ă�
	m_sMotionFrag.bCharge = true;
}

//==========================================================================
// ��������
//==========================================================================
void CEnemyTurret::AttackMortar(void)
{
	// �ˌ��̋���
	float fMove = GetVelocity();

	D3DXVECTOR3 rot = GetRotation();
	D3DXVECTOR3 move = GetMove();

	// �v���C���[���
	CPlayer* pPlayer = nullptr;

	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(i);

		if (pPlayer == NULL)
		{
			continue;
		}

		SetTargetPosition(pPlayer->GetPosition());
		RotationTarget();

		rot = GetRotation();
		move = {sinf(rot.y + D3DX_PI) * 100.0f,
				0.0f,
				cosf(rot.y + D3DX_PI) * 100.0f };

		//�e���������ɔ�΂�
		CBullet *pBullet = CBullet::Create(CBullet::TYPE_ENEMY, CBullet::MOVETYPE_PARABOLA, GetPosition(), rot, move, 50.0f);
		pBullet->SetTargetPosition(pPlayer->GetPosition());

		float fRatio = GetFabsPosLength(GetPosition(), pPlayer->GetPosition()) / 1500.0f;
		ValueNormalize(fRatio, 1.0f, 0.0f);
		pBullet->SetParabolaHeight(1000.0f - (1000.0f * fRatio));
	}

	// �^�b�N���s��
	m_Action = ACTION_WAIT;

	// �^�b�N���ݒ�
	m_pMotion->Set(MOTION_DEF);

	if (m_pMotion->GetType() != MOTION_MORTAR)
	{
		// �^�b�N�����[�V�����ݒ�
		m_pMotion->Set(MOTION_MORTAR);
	}

	// �U���t���O�𗧂Ă�
	m_sMotionFrag.bATK = true;
}

//==========================================================================
//  �`�揈��
//==========================================================================
void CEnemyTurret::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//==========================================================================
//  �E��
//==========================================================================
void CEnemyTurret::Kill(void)
{
	// ���S����
	CEnemy::Kill();
}

//==========================================================================
//  ���[�V�����Z�b�g
//==========================================================================
void CEnemyTurret::MotionSet(void)
{
	if (m_pMotion->IsFinish() == true)
	{// �I�����Ă�����

	 // ���݂̎�ގ擾
		int nType = m_pMotion->GetType();

		if (m_sMotionFrag.bMove == true && m_sMotionFrag.bKnockback == false && m_sMotionFrag.bATK == false)
		{// �ړ����Ă�����

			 // �U�����Ă��Ȃ�
			m_sMotionFrag.bATK = false;
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
			//m_pMotion->Set(MOTION_CHARGE_MORTAR);
		}
		else if (m_sMotionFrag.bATK == true)
		{// �U�����Ă�����

		 // �U������OFF
			m_sMotionFrag.bATK = false;

			// �s���ʐݒ菈��
			switch (m_ActionBranch)
			{
			case ACTBRANCH_BEAM_SHOT:
				m_pMotion->Set(MOTION_BEAM);
				break;

			case ACTBRANCH_MORTAR_SHOT:
				m_pMotion->Set(MOTION_MORTAR);
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
void CEnemyTurret::RotationTarget(void)
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
	if (fabsf(fRotDiff) > 0.1f)
	{
		rot.y += fRotDiff * 0.05f;
	}
	else
	{
		rot.y += fRotDiff * 1.0f;
	}

	RotNormalize(rot.y);

	// �����ݒ�
	SetRotation(rot);

	// �ڕW�̌����ݒ�
	SetRotDest(fRotDest);
}

//==========================================================================
// �ǂ̃v���C���[�̃^�[�Q�b�g
//==========================================================================
void CEnemyTurret::SetTargetPlayer(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 posPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fLength = 0.0f, fLengthDiff = 0.0f;
	CPlayer* pPlayer = nullptr;

	//�����l����
	pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(0);

	if (pPlayer == NULL)
	{
		return;
	}

	posPlayer = pPlayer->GetPosition();
	fLengthDiff = GetFabsPosLength(pos, posPlayer);
	m_nTargetPlayerIndex = 0;
	SetTargetPosition(posPlayer);

	// �v���C���[���
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(i);

		if (pPlayer == NULL)
		{
			continue;
		}

		// �v���C���[�̈ʒu�擾
		posPlayer = pPlayer->GetPosition();

		fLength = GetFabsPosLength(pos, posPlayer);

		if (fLength < fLengthDiff)
		{//���߂�
			m_nTargetPlayerIndex = i;
			fLengthDiff = fLength;
			SetTargetPosition(posPlayer);
		}
	}
}

//==========================================================================
// �G���A����
//==========================================================================
void CEnemyTurret::SummonArea(void)
{
	if (CalcLenPlayer(SEARCH_LENGTH))
	{
		D3DXVECTOR3 pos = GetPosition();
		CLimitArea::sLimitEreaInfo info = {};
		info.fMinX = pos.x - AREA_LENGTH;
		info.fMaxX = pos.x + AREA_LENGTH;
		info.fMinZ = pos.z - AREA_LENGTH;
		info.fMaxZ = pos.z + AREA_LENGTH;

		if (m_pLimitArea != nullptr)
		{
			m_pLimitArea->Uninit();
			m_pLimitArea = nullptr;
		}

		m_pLimitArea = CLimitArea::Create(info);

		m_bArea = true;
	}
}

//==========================================================================
// �ڕW�̈ʒu�ݒ�
//==========================================================================
void CEnemyTurret::SetTargetPosition(D3DXVECTOR3 pos)
{
	m_TargetPosition = pos;
}
