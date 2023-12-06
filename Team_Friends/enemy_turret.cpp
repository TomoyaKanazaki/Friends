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
#include "limitarea.h"
#include "beam.h"
#include "bullet.h"
#include "player.h"

//==========================================================================
//  èè`
//==========================================================================
namespace
{
	const float VELOCITY_TACKLE = 2.0f;		// ^bN
	const float MORTAR_SPEED = 0.0f;		// e¬x
	const float TIME_WAIT = 3.0f;			// Ò@
	const float SEARCH_LENGTH = 600.0f;		//GA¶¬£
	const float AREA_LENGTH = 800.0f;		//{XGATCY
	const D3DXCOLOR BEAM_COLOR = {0.1f, 1.0f, 0.1f, 0.5f};		//{XGATCY
}

//==========================================================================
// Ö|C^
//==========================================================================
CEnemyTurret::ACT_FUNC CEnemyTurret::m_ActFuncList[] =
{
	&CEnemyTurret::ActAttackBeam,		// u
	&CEnemyTurret::ActAttackMortar,		// Ë
	&CEnemyTurret::ActWait,				// Ò@
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

	// s®
	m_Action = ACTION_WAIT;

	return S_OK;
}

//==========================================================================
//  I¹
//==========================================================================
void CEnemyTurret::Uninit(void)
{
	if (m_pLimitArea != nullptr)
	{
		m_pLimitArea->SetState(CLimitArea::STATE_FADEOUT);
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
	// óÔÊ
	(this->*(m_ActFuncList[m_Action]))();
}

//==========================================================================
// s®I
//==========================================================================
void CEnemyTurret::DrawingAction(void)
{
	//while (true)
	//{
	//	// s®I
	//	m_Action = (ACTION)(rand() % ACTION_MAX);

	//	if (m_Action != ACTION_WAIT)
	//	{// ùès®ÈO
	//		break;
	//	}
	//}

	m_Action = ACTION_MORTAR;

	// Ìs®Ê
	int nActRand;
	float fLength = 0.0f;
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

	// ^[QbgÌûðü­
	RotationTarget();

	// `[WtOð§Äé
	m_sMotionFrag.bCharge = true;
}

//==========================================================================
// r[U
//==========================================================================
void CEnemyTurret::AttackBeam(void)
{
	int nType = m_pMotion->GetType();

	if (nType == MOTION_BEAM && m_pMotion->IsFinish() == true)
	{// r[UªIíÁÄ½ç

		float fRot = GetRotDest();
		D3DXVECTOR3 move = {sinf(fRot + D3DX_PI) * MORTAR_SPEED,
							0.0f,
							cosf(fRot + D3DX_PI) * MORTAR_SPEED };

		CBeam::Create(GetPosition(), move, BEAM_COLOR, 50.0f, 2000.0f, 50, 100, 1, CCollisionObject::TAG_ENEMY);

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
	{// ^bN`[WªIíÁÄ½ç

		 // ^bNs®
		m_ActionBranch = ACTBRANCH_MORTAR_SHOT;

		// ^bNÝè
		m_pMotion->Set(MOTION_MORTAR);

		return;
	}

	if (nType != MOTION_CHARGE_MORTAR)
	{
		// ^bN`[WÝè
		m_pMotion->Set(MOTION_CHARGE_MORTAR);
	}

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

	// vC[îñ
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

		//eðú¨üãÉòÎ·
		CBullet *pBullet = CBullet::Create(CBullet::TYPE_ENEMY, CBullet::MOVETYPE_PARABOLA, GetPosition(), rot, move, 50.0f);
		pBullet->SetTargetPosition(pPlayer->GetPosition());

		float fRatio = GetFabsPosLength(GetPosition(), pPlayer->GetPosition()) / 1500.0f;
		ValueNormalize(fRatio, 1.0f, 0.0f);
		pBullet->SetParabolaHeight(1000.0f - (1000.0f * fRatio));
	}

	// ^bNs®
	m_Action = ACTION_WAIT;

	// ^bNÝè
	m_pMotion->Set(MOTION_DEF);

	if (m_pMotion->GetType() != MOTION_MORTAR)
	{
		// ^bN[VÝè
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
			//m_pMotion->Set(MOTION_CHARGE_MORTAR);
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
	rot.y += fRotDiff * 1.0f;
	RotNormalize(rot.y);

	// ü«Ýè
	SetRotation(rot);

	// ÚWÌü«Ýè
	SetRotDest(fRotDest);
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
// ÚWÌÊuÝè
//==========================================================================
void CEnemyTurret::SetTargetPosition(D3DXVECTOR3 pos)
{
	m_TargetPosition = pos;
}
