//==========================================================================
// 
//  中ボス(砲台) [enemy_turret.cpp]
//  Author : 髙田佳依
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
//  定数定義
//==========================================================================
namespace
{
	const float VELOCITY_TACKLE = 2.0f;		// タックル
	const float MORTAR_SPEED = 0.0f;		// 迫撃弾速度
	const float TIME_WAIT = 3.0f;			// 待機
	const float SEARCH_LENGTH = 600.0f;		//エリア生成距離
	const float AREA_LENGTH = 800.0f;		//ボスエリアサイズ
	const D3DXCOLOR BEAM_COLOR = {0.1f, 1.0f, 0.1f, 0.5f};		//ボスエリアサイズ
}

//==========================================================================
// 関数ポインタ
//==========================================================================
CEnemyTurret::ACT_FUNC CEnemyTurret::m_ActFuncList[] =
{
	&CEnemyTurret::ActAttackBeam,		// 遠隔
	&CEnemyTurret::ActAttackMortar,		// 突撃
	&CEnemyTurret::ActWait,				// 待機
};

//==========================================================================
//  コンストラクタ
//==========================================================================
CEnemyTurret::CEnemyTurret(int nPriority) : CEnemy(nPriority)
{
	m_Action = ACTION_WAIT;		// 行動
	m_ActionBranch = ACTBRANCH_MORTAR_CHARGE;		// 行動分岐
	m_MakeForActionBranch = ACTBRANCH_MORTAR_CHARGE;	// 行動する為の行動
	m_TargetPosition = mylib_const::DEFAULT_VECTOR3;	// 目標の位置
	m_fActTime = 0.0f;			// 行動カウンター
	m_fRotLock = 0.0f;
	m_pLimitArea = nullptr;
	m_bArea = false;
}

//==========================================================================
//  デストラクタ
//==========================================================================
CEnemyTurret::~CEnemyTurret()
{

}

//==========================================================================
//  初期化処理
//==========================================================================
HRESULT CEnemyTurret::Init(void)
{
	//初期化処理
	CEnemy::Init();

	// HPの設定
	m_pHPGauge = CHP_Gauge::Create(100.0f, GetLifeOrigin());

	// 行動
	m_Action = ACTION_WAIT;

	return S_OK;
}

//==========================================================================
//  終了処理
//==========================================================================
void CEnemyTurret::Uninit(void)
{
	if (m_pLimitArea != nullptr)
	{
		m_pLimitArea->SetState(CLimitArea::STATE_FADEOUT);
	}

	// 終了処理
	CEnemy::Uninit();
}

//==========================================================================
//  更新処理
//==========================================================================
void CEnemyTurret::Update(void)
{
	if (m_bArea == false)
	{//エリア未生成なら
		SummonArea();
	}

	// 死亡の判定
	if (IsDeath() == true)
	{// 死亡フラグが立っていたら
		return;
	}

	// 更新処理
	CEnemy::Update();

	if (IsDeath() == true)
	{// 死亡フラグが立っていたら
		return;
	}
}

//==========================================================================
// 行動設定
//==========================================================================
void CEnemyTurret::ActionSet(void)
{

}

//==========================================================================
// 行動更新
//==========================================================================
void CEnemyTurret::UpdateAction(void)
{
	// 状態別処理
	(this->*(m_ActFuncList[m_Action]))();
}

//==========================================================================
// 行動抽選
//==========================================================================
void CEnemyTurret::DrawingAction(void)
{
	//while (true)
	//{
	//	// 行動抽選
	//	m_Action = (ACTION)(rand() % ACTION_MAX);

	//	if (m_Action != ACTION_WAIT)
	//	{// 既定行動以外
	//		break;
	//	}
	//}

	m_Action = ACTION_BEAM;

	// 次の行動別
	int nActRand;
	float fLength = 0.0f;
	switch (m_Action)
	{
	case CEnemyTurret::ACTION_BEAM:	// 遠隔攻撃
		m_ActionBranch = ACTBRANCH_BEAM_CHARGE;
		break;

	case CEnemyTurret::ACTION_MORTAR:	// 突撃攻撃
		m_ActionBranch = ACTBRANCH_MORTAR_CHARGE;
		break;

	default:
		break;
	}
}

//==========================================================================
// 待機
//==========================================================================
void CEnemyTurret::ActWait(void)
{
	// 待機モーション設定
	m_pMotion->Set(MOTION_DEF);

	// 行動カウンター加算
	m_fActTime += CManager::GetInstance()->GetDeltaTime();

	// ターゲットの方を向く
	RotationTarget();

	if (TIME_WAIT <= m_fActTime)
	{// 待機時間超えたら

	 // 行動抽選
		DrawingAction();
		m_fActTime = 0.0f;
	}
}

//==========================================================================
// ビーム攻撃
//==========================================================================
void CEnemyTurret::ActAttackBeam(void)
{
	// 攻撃フラグを立てる
	m_sMotionFrag.bATK = true;

	// ターゲットの方を向く
	RotationTarget();

	// 行動別移動処理
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
// ビームチャージ
//==========================================================================
void CEnemyTurret::ChargeBeam(void)
{
	int nType = m_pMotion->GetType();

	if (nType == MOTION_CHARGE_BEAM && m_pMotion->IsFinish() == true)
	{// ビームチャージが終わってたら

	 // ビーム行動
		m_ActionBranch = ACTBRANCH_BEAM_SHOT;

		// ビーム設定
		m_pMotion->Set(MOTION_BEAM);
	}

	if (nType != MOTION_CHARGE_BEAM)
	{
		// ビームチャージ設定
		m_pMotion->Set(MOTION_CHARGE_BEAM);
	}

	// ターゲットの方を向く
	RotationTarget();

	// チャージフラグを立てる
	m_sMotionFrag.bCharge = true;
}

//==========================================================================
// ビーム攻撃
//==========================================================================
void CEnemyTurret::AttackBeam(void)
{
	int nType = m_pMotion->GetType();

	if (nType == MOTION_BEAM && m_pMotion->IsFinish() == true)
	{// ビーム攻撃が終わってたら

		float fRot = GetRotDest();
		D3DXVECTOR3 move = {sinf(fRot + D3DX_PI) * MORTAR_SPEED,
							0.0f,
							cosf(fRot + D3DX_PI) * MORTAR_SPEED };

		CBeam::Create(GetPosition(), move, BEAM_COLOR, 50.0f, 2000.0f, 50, 100, 1, CCollisionObject::TAG_ENEMY);

		// 待機行動
		m_Action = ACTION_WAIT;

		// 待機モーション設定
		m_pMotion->Set(MOTION_DEF);
		return;
	}

	if (nType != MOTION_BEAM)
	{
		// ビームモーション設定
		m_pMotion->Set(MOTION_BEAM);
	}

	// 攻撃フラグを立てる
	m_sMotionFrag.bATK = true;
}

//==========================================================================
// 迫撃攻撃
//==========================================================================
void CEnemyTurret::ActAttackMortar(void)
{
	// 行動別移動処理
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
// 迫撃チャージ
//==========================================================================
void CEnemyTurret::ChargeMortar(void)
{
	int nType = m_pMotion->GetType();

	if (nType == MOTION_CHARGE_MORTAR && m_pMotion->IsFinish() == true)
	{// タックルチャージが終わってたら

		 // タックル行動
		m_ActionBranch = ACTBRANCH_MORTAR_SHOT;

		// タックル設定
		m_pMotion->Set(MOTION_MORTAR);

		return;
	}

	if (nType != MOTION_CHARGE_MORTAR)
	{
		// タックルチャージ設定
		m_pMotion->Set(MOTION_CHARGE_MORTAR);
	}

	// ターゲットの方を向く
	RotationTarget();

	// チャージフラグを立てる
	m_sMotionFrag.bCharge = true;
}

//==========================================================================
// 迫撃発射
//==========================================================================
void CEnemyTurret::AttackMortar(void)
{
	// 突撃の距離
	float fMove = GetVelocity();

	D3DXVECTOR3 rot = GetRotation();
	D3DXVECTOR3 move = GetMove();

	// プレイヤー情報
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

		//弾を放物線上に飛ばす
		CBullet::Create(CBullet::TYPE_ENEMY, CBullet::MOVETYPE_PARABOLA, GetPosition(), rot, move, 50.0f);
	}

	// タックル行動
	m_Action = ACTION_WAIT;

	// タックル設定
	m_pMotion->Set(MOTION_DEF);

	if (m_pMotion->GetType() != MOTION_MORTAR)
	{
		// タックルモーション設定
		m_pMotion->Set(MOTION_MORTAR);
	}

	// 攻撃フラグを立てる
	m_sMotionFrag.bATK = true;
}

//==========================================================================
//  描画処理
//==========================================================================
void CEnemyTurret::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}

//==========================================================================
//  殺す
//==========================================================================
void CEnemyTurret::Kill(void)
{
	// 死亡処理
	CEnemy::Kill();
}

//==========================================================================
//  モーションセット
//==========================================================================
void CEnemyTurret::MotionSet(void)
{
	if (m_pMotion->IsFinish() == true)
	{// 終了していたら

	 // 現在の種類取得
		int nType = m_pMotion->GetType();

		if (m_sMotionFrag.bMove == true && m_sMotionFrag.bKnockback == false && m_sMotionFrag.bATK == false)
		{// 移動していたら

			 // 攻撃していない
			m_sMotionFrag.bATK = false;
		}
		else if (m_sMotionFrag.bKnockback == true)
		{// やられ中だったら

			 // やられモーション
			m_pMotion->Set(MOTION_KNOCKBACK);
		}
		else if (m_sMotionFrag.bCharge == true)
		{// チャージ中だったら

			m_sMotionFrag.bCharge = false;
			// チャージモーション
			//m_pMotion->Set(MOTION_CHARGE_MORTAR);
		}
		else if (m_sMotionFrag.bATK == true)
		{// 攻撃していたら

		 // 攻撃判定OFF
			m_sMotionFrag.bATK = false;

			// 行動別設定処理
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
		//	// ニュートラルモーション
		//	m_pMotion->Set(MOTION_DEF);
		//}
	}
}

//==========================================================================
// ターゲットの方を向く
//==========================================================================
void CEnemyTurret::RotationTarget(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();

	// 目標の角度を求める
	float fRotDest = atan2f((pos.x - m_TargetPosition.x), (pos.z - m_TargetPosition.z));

	// 目標との差分
	float fRotDiff = fRotDest - rot.y;

	//角度の正規化
	RotNormalize(fRotDiff);

	//角度の補正をする
	rot.y += fRotDiff * 1.0f;
	RotNormalize(rot.y);

	// 向き設定
	SetRotation(rot);

	// 目標の向き設定
	SetRotDest(fRotDest);
}

//==========================================================================
// エリア生成
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
// 目標の位置設定
//==========================================================================
void CEnemyTurret::SetTargetPosition(D3DXVECTOR3 pos)
{
	m_TargetPosition = pos;
}
