//==========================================================================
// 
//  {X(Cä) [enemy_turret.cpp]
//  Author : ûücÀË
//
//==========================================================================
#include "enemy_turret.h"
#include "manager.h"
#include "debugproc.h"
#include "calculation.h"
#include "hp_gauge.h"
#include "limitarea.h"			//{XGA
#include "beam.h"				//r[
#include "bullet.h"				//
#include "player.h"				//vC[´m
#include "camera.h"				//o»oÌ½ßÌJ»è
#include "game.h"
#include "gamemanager.h"
#include "particle.h"			//o»o
#include "3D_Effect.h"			//o»o
#include "impactwave.h"			//o»o
#include "bullet_point.h"		//en_

//==========================================================================
//  èè`
//==========================================================================
namespace
{
	// s®IÌ\¢Ì
	struct sProbability
	{
		CEnemyTurret::ACTION action;	// s®
		float fProbability;			// m¦
	};

	const float VELOCITY_TACKLE = 2.0f;		// ^bN
	const float MORTAR_SPEED = 10.0f;		// e¬x
	const float TIME_WAIT = 3.0f;			// Ò@
	const float SEARCH_LENGTH = 600.0f;		//GA¶¬£
	const float AREA_LENGTH = 800.0f;		//{XGATCY
	const float BEAM_LENGTH = 1000.0f;		//r[Ì·³
	std::vector<sProbability> ACT_PROBABILITY =	// s®ÌIm¦
	{
		{ CEnemyTurret::ACTION_BEAM, 0.3f },		// r[U
		{ CEnemyTurret::ACTION_MORTAR, 0.7f },		// U
		{ CEnemyTurret::ACTION_WAIT, 0.0f },		// Ò@
	};
}

//==========================================================================
// Ö|C^
//==========================================================================
CEnemyTurret::ACT_FUNC CEnemyTurret::m_ActFuncList[] =
{
	&CEnemyTurret::ActAttackBeam,		// u
	&CEnemyTurret::ActAttackMortar,		// Ë
	&CEnemyTurret::ActWait,				// Ò@
	&CEnemyTurret::Spawn,				// X|[
};

//==========================================================================
//  RXgN^
//==========================================================================
CEnemyTurret::CEnemyTurret(int nPriority) : CEnemy(nPriority)
{
	m_Action = ACTION_WAIT;		// s®
	m_ActionBranch = ACTBRANCH_MORTAR_CHARGE;		// s®ªò
	m_MakeForActionBranch = ACTBRANCH_MORTAR_CHARGE;	// s®·é×Ìs®
	m_TargetPosition = mylib_const::DEFAULT_VECTOR3;	// ÚWÌÊu
	m_fActTime = 0.0f;			// s®JE^[
	m_fRotLock = 0.0f;
	m_pLimitArea = nullptr;
	m_bArea = false;

	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		if (m_pBullet[i] != nullptr)
		{
			m_pBulletPoint[i] = nullptr;
		}

		if (m_pBullet[i] != nullptr)
		{
			m_pBullet[i] = nullptr;
		}
	}
}

//==========================================================================
//  fXgN^
//==========================================================================
CEnemyTurret::~CEnemyTurret()
{

}

//==========================================================================
//  ú»
//==========================================================================
HRESULT CEnemyTurret::Init(void)
{
	//ú»
	CEnemy::Init();

	// HPÌÝè
	m_pHPGauge = CHP_Gauge::Create(100.0f, GetLifeOrigin());

	// o»Ò@óÔÉ·é
	m_state = CEnemy::STATE_SPAWNWAIT;
	m_Action = ACTION_SPAWN;

	return S_OK;
}

//==========================================================================
//  I¹
//==========================================================================
void CEnemyTurret::Uninit(void)
{
	CScene *pScene = CManager::GetInstance()->GetScene();

	//Q[ÈçvC[i»
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

	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		if (m_pBullet[i] != nullptr)
		{
			m_pBullet[i] = nullptr;
		}

		if (m_pBulletPoint[i] != nullptr)
		{
			m_pBulletPoint[i]->Uninit();
			m_pBulletPoint[i] = nullptr;
		}
	}

	// I¹
	CEnemy::Uninit();
}

//==========================================================================
//  XV
//==========================================================================
void CEnemyTurret::Update(void)
{
	if (m_bArea == false)
	{//GA¢¶¬Èç
		SummonArea();
	}

	// SÌ»è
	if (IsDeath() == true)
	{// StOª§ÁÄ¢½ç
		return;
	}

	// XV
	CEnemy::Update();

	if (IsDeath() == true)
	{// StOª§ÁÄ¢½ç
		return;
	}

	//eÁµ
	DeleteTarget();

	// XN[àÌ¶Ý»è
	if (m_state == CEnemy::STATE_SPAWNWAIT && CManager::GetInstance()->GetCamera()->OnScreen(GetPosition()))
	{
		m_state = STATE_SPAWN;
	}
}

//==========================================================================
// s®Ýè
//==========================================================================
void CEnemyTurret::ActionSet(void)
{

}

//==========================================================================
// s®XV
//==========================================================================
void CEnemyTurret::UpdateAction(void)
{
	if (m_state == STATE_DEAD ||
		m_state == STATE_FADEOUT)
	{
		return;
	}

	// óÔÊ
	(this->*(m_ActFuncList[m_Action]))();
}

//==========================================
// X|[
//==========================================
void CEnemyTurret::Spawn(void)
{
	if (m_state == STATE_SPAWNWAIT)
	{
		return;
	}

	int nType = m_pMotion->GetType();

	if (nType == MOTION_SPAWN && m_pMotion->IsFinish() == true)
	{// oêªIíÁÄ½ç

	 // ÈÉàÈ¢
		m_state = STATE_NONE;
		m_Action = ACTION_WAIT;
		return;
	}

	// [VJE^[æ¾
	float fAllCount = m_pMotion->GetAllCount();
	if ((int)fAllCount % 10 == 0)
	{
		// pxÌæ¾
		D3DXVECTOR3 rot = GetRotation();

		// Õg¶¬
		CImpactWave *pWave = CImpactWave::Create
		(
			GetCenterPosition(),	// Êu
			D3DXVECTOR3((float)Random(-31, 31) * 0.1f, D3DX_PI * 0.5f + rot.y, 0.0f),	// ü«
			D3DXCOLOR(0.9f, 0.2f, 0.9f, 0.8f),	// F
			150.0f,								// 
			0.0f,								// ³
			90.0f,								// S©çÌÔu
			20,									// õ½
			8.0f,								// ÌÚ®Ê
			CImpactWave::TYPE_GIZAGRADATION,	// eNX`^Cv
			true								// ÁZ¬·é©
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

	// oêo
	my_particle::Create(GetCenterPosition(), my_particle::TYPE_UNDERBOSS_SPAWN);

	if (nType != MOTION_SPAWN)
	{
		// oê[VÝè
		m_pMotion->Set(MOTION_SPAWN);
	}
}

//==========================================================================
// s®I
//==========================================================================
void CEnemyTurret::DrawingAction(void)
{
	// 0`1Ì_læ¾
	float fRandomValue = static_cast<float>(std::rand()) / RAND_MAX;

	// m¦ÁZpÏ
	float fDrawingProbability = 0.0;

	// s®IvfªJèÔµ
	for (const auto& candidate : ACT_PROBABILITY)
	{
		// ¡ñÌm¦ªðÁZ
		fDrawingProbability += candidate.fProbability;

		if (fRandomValue < fDrawingProbability)
		{// ¡ñÌ_lªm¦ð´¦½ç

		 // s®è
			m_Action = candidate.action;

			// s®JE^[Zbg
			m_fActTime = 0.0f;
			break;
		}
	}

	// Ìs®Ê
	switch (m_Action)
	{
	case CEnemyTurret::ACTION_BEAM:	// uU
		m_ActionBranch = ACTBRANCH_BEAM_CHARGE;
		break;

	case CEnemyTurret::ACTION_MORTAR:	// ËU
		m_ActionBranch = ACTBRANCH_MORTAR_CHARGE;
		break;

	default:
		break;
	}
}

//==========================================================================
// Ò@
//==========================================================================
void CEnemyTurret::ActWait(void)
{
	// Ò@[VÝè
	m_pMotion->Set(MOTION_DEF);

	// s®JE^[ÁZ
	m_fActTime += CManager::GetInstance()->GetDeltaTime();

	// ^[QbgÌûðü­
	RotationTarget();

	if (TIME_WAIT <= m_fActTime)
	{// Ò@Ô´¦½ç

	 // s®I
		DrawingAction();
		m_fActTime = 0.0f;
	}
}

//==========================================================================
// r[U
//==========================================================================
void CEnemyTurret::ActAttackBeam(void)
{
	// UtOð§Äé
	m_sMotionFrag.bATK = true;

	// ^[QbgÌûðü­
	RotationTarget();

	// s®ÊÚ®
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
// r[`[W
//==========================================================================
void CEnemyTurret::ChargeBeam(void)
{
	int nType = m_pMotion->GetType();

	if (nType == MOTION_CHARGE_BEAM && m_pMotion->IsFinish() == true)
	{// r[`[WªIíÁÄ½ç

	 // r[s®
		m_ActionBranch = ACTBRANCH_BEAM_SHOT;

		// r[Ýè
		m_pMotion->Set(MOTION_BEAM);
	}

	if (nType != MOTION_CHARGE_BEAM)
	{
		// r[`[WÝè
		m_pMotion->Set(MOTION_CHARGE_BEAM);
	}

	D3DXVECTOR3 pos = GetPosition();
	pos.y += 100.0f;

	//`[WGtFNg
	my_particle::Create(pos, my_particle::TYPE_BEAM_CHARGE);

	//êÔß¢vC[ðF¯·é
	SetTargetPlayer();

	// ^[QbgÌûðü­
	RotationTarget();

	// `[WtOð§Äé
	m_sMotionFrag.bCharge = true;
}

//==========================================================================
// r[­Ë
//==========================================================================
void CEnemyTurret::AttackBeam(void)
{
	int nType = m_pMotion->GetType();

	if (nType == MOTION_BEAM && m_pMotion->IsFinish() == true)
	{// r[UªIíÁÄ½ç

		float fRot = GetRotation().y;
		D3DXVECTOR3 move = {sinf(fRot + D3DX_PI) * MORTAR_SPEED,
							0.0f,
							cosf(fRot + D3DX_PI) * MORTAR_SPEED };

		D3DXVECTOR3 pos = GetPosition();
		pos.y += 100.0f;

		CBeam::Create(pos, move, mylib_const::ENEMYBEAM_COLOR, 50.0f, BEAM_LENGTH, 50, 40, 1, CCollisionObject::TAG_ENEMY);

		// Ò@s®
		m_Action = ACTION_WAIT;

		// Ò@[VÝè
		m_pMotion->Set(MOTION_DEF);
		return;
	}

	if (nType != MOTION_BEAM)
	{
		// r[[VÝè
		m_pMotion->Set(MOTION_BEAM);
	}

	// UtOð§Äé
	m_sMotionFrag.bATK = true;
}

//==========================================================================
// U
//==========================================================================
void CEnemyTurret::ActAttackMortar(void)
{
	// s®ÊÚ®
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
// `[W
//==========================================================================
void CEnemyTurret::ChargeMortar(void)
{
	int nType = m_pMotion->GetType();

	if (nType == MOTION_CHARGE_MORTAR && m_pMotion->IsFinish() == true)
	{// `[WªIíÁÄ½ç

		// s®
		m_ActionBranch = ACTBRANCH_MORTAR_SHOT;

		// Ýè
		m_pMotion->Set(MOTION_MORTAR);

		return;
	}

	if (nType != MOTION_CHARGE_MORTAR)
	{
		// `[WÝè
		m_pMotion->Set(MOTION_CHARGE_MORTAR);
	}

	// vC[îñ
	CPlayer* pPlayer = nullptr;

	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(i);

		if (pPlayer == nullptr)
		{
			continue;
		}

		if (m_pBulletPoint[i] != nullptr)
		{
			m_pBulletPoint[i]->Uninit();
			m_pBulletPoint[i] = nullptr;
		}

		//en_É}[N\¦
		m_pBulletPoint[i] = CBulletPoint::Create(pPlayer->GetPosition());
	}

	D3DXVECTOR3 pos = GetPosition();
	pos.y += 100.0f;

	//`[WGtFNg
	my_particle::Create(pos, my_particle::TYPE_MORTAR_CHARGE);

	// ^[QbgÌûðü­
	RotationTarget();

	// `[WtOð§Äé
	m_sMotionFrag.bCharge = true;
}

//==========================================================================
// ­Ë
//==========================================================================
void CEnemyTurret::AttackMortar(void)
{
	// ËÌ£
	float fMove = GetVelocity();
	D3DXVECTOR3 rot = GetRotation();
	D3DXVECTOR3 move = GetMove();

	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		if (m_pBulletPoint[i] == nullptr)
		{
			continue;
		}

		if (m_pBullet[i] != nullptr)
		{
			m_pBullet[i] = nullptr;
		}

		//eðú¨üãÉòÎ·
		m_pBullet[i] = CBullet::Create(CBullet::TYPE_ENEMY, CBullet::MOVETYPE_PARABOLA, GetPosition(), rot, move, 50.0f);
		m_pBullet[i]->SetTargetPosition(m_pBulletPoint[i]->GetPosition());
		m_pBullet[i]->SetReverseAutoDeath();	// ©®íÌ»èí

		float fRatio = GetFabsPosLength(GetPosition(), m_pBulletPoint[i]->GetPosition()) / 1500.0f;
		ValueNormalize(fRatio, 1.0f, 0.0f);
		m_pBullet[i]->SetParabolaHeight(1000.0f - (1000.0f * fRatio));
	}

	// s®
	m_Action = ACTION_WAIT;

	// Ýè
	m_pMotion->Set(MOTION_DEF);

	if (m_pMotion->GetType() != MOTION_MORTAR)
	{
		// [VÝè
		m_pMotion->Set(MOTION_MORTAR);
	}

	// UtOð§Äé
	m_sMotionFrag.bATK = true;
}

//==========================================================================
//  `æ
//==========================================================================
void CEnemyTurret::Draw(void)
{
	// `æ
	CEnemy::Draw();
}

//==========================================================================
//  E·
//==========================================================================
void CEnemyTurret::Kill(void)
{
	// S
	CEnemy::Kill();
}

//==========================================================================
//  [VZbg
//==========================================================================
void CEnemyTurret::MotionSet(void)
{
	if (m_pMotion->IsFinish() == true)
	{// I¹µÄ¢½ç

	 // »ÝÌíÞæ¾
		int nType = m_pMotion->GetType();

		if (m_sMotionFrag.bMove == true && m_sMotionFrag.bKnockback == false && m_sMotionFrag.bATK == false)
		{// Ú®µÄ¢½ç

			 // UµÄ¢È¢
			m_sMotionFrag.bATK = false;
		}
		else if (m_sMotionFrag.bKnockback == true)
		{// âçê¾Á½ç

			 // âçê[V
			m_pMotion->Set(MOTION_KNOCKBACK);
		}
		else if (m_sMotionFrag.bCharge == true)
		{// `[W¾Á½ç

			m_sMotionFrag.bCharge = false;
			// `[W[V
			//if (m_Action == ACTION_BEAM) m_pMotion->Set(MOTION_CHARGE_BEAM);
			//else if (m_Action == ACTION_MORTAR) m_pMotion->Set(MOTION_CHARGE_MORTAR);
		}
		else if (m_sMotionFrag.bATK == true)
		{// UµÄ¢½ç

		 // U»èOFF
			m_sMotionFrag.bATK = false;

			// s®ÊÝè
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
		//	// j[g[V
		//	m_pMotion->Set(MOTION_DEF);
		//}
	}
}

//==========================================================================
// ^[QbgÌûðü­
//==========================================================================
void CEnemyTurret::RotationTarget(void)
{
	// Êuæ¾
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();

	// ÚWÌpxðßé
	float fRotDest = atan2f((pos.x - m_TargetPosition.x), (pos.z - m_TargetPosition.z));

	// ÚWÆÌ·ª
	float fRotDiff = fRotDest - rot.y;
	
	//pxÌ³K»
	RotNormalize(fRotDiff);
	
	//pxÌâ³ð·é
	if (fabsf(fRotDiff) > 0.1f)
	{
		rot.y += fRotDiff * 0.05f;
	}
	else
	{
		rot.y += fRotDiff * 1.0f;
	}

	RotNormalize(rot.y);

	// ü«Ýè
	SetRotation(rot);

	// ÚWÌü«Ýè
	SetRotDest(fRotDest);
}

//==========================================================================
// ÇÌvC[Ì^[Qbg
//==========================================================================
void CEnemyTurret::SetTargetPlayer(void)
{
	// Êuæ¾
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 posPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fLength = 0.0f, fLengthDiff = 0.0f;
	CPlayer* pPlayer = nullptr;

	//úlüê
	pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(0);

	if (pPlayer == NULL)
	{
		return;
	}

	posPlayer = pPlayer->GetPosition();
	fLengthDiff = GetFabsPosLength(pos, posPlayer);
	m_nTargetPlayerIndex = 0;
	SetTargetPosition(posPlayer);

	// vC[îñ
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(i);

		if (pPlayer == NULL)
		{
			continue;
		}

		// vC[ÌÊuæ¾
		posPlayer = pPlayer->GetPosition();

		fLength = GetFabsPosLength(pos, posPlayer);

		if (fLength < fLengthDiff)
		{//æèß¢
			m_nTargetPlayerIndex = i;
			fLengthDiff = fLength;
			SetTargetPosition(posPlayer);
		}
	}
}

//==========================================================================
// GA¶¬
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
// eÁµ
//==========================================================================
void CEnemyTurret::DeleteTarget(void)
{
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		if (m_pBullet[i] == nullptr)
		{
			continue;
		}
		
		if (m_pBullet[i]->IsFinish())
		{
			m_pBullet[i]->Uninit();
			m_pBullet[i] = nullptr;

			if (m_pBulletPoint[i] != nullptr)
			{
				m_pBulletPoint[i]->Uninit();
				m_pBulletPoint[i] = nullptr;
			}
		}
	}
}

//==========================================================================
// ÚWÌÊuÝè
//==========================================================================
void CEnemyTurret::SetTargetPosition(D3DXVECTOR3 pos)
{
	m_TargetPosition = pos;
}
