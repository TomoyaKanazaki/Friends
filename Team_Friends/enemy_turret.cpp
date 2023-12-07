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
#include "camera.h"
#include "game.h"
#include "gamemanager.h"
#include "particle.h"
#include "3D_Effect.h"
#include "impactwave.h"

//==========================================================================
//  定数定義
//==========================================================================
namespace
{
	// 行動抽選の構造体
	struct sProbability
	{
		CEnemyTurret::ACTION action;	// 行動
		float fProbability;			// 確率
	};

	const float VELOCITY_TACKLE = 2.0f;		// タックル
	const float MORTAR_SPEED = 10.0f;		// 迫撃弾速度
	const float TIME_WAIT = 3.0f;			// 待機
	const float SEARCH_LENGTH = 600.0f;		//エリア生成距離
	const float AREA_LENGTH = 800.0f;		//ボスエリアサイズ
	const float BEAM_LENGTH = 1000.0f;		//ビームの長さ
	const D3DXCOLOR BEAM_COLOR = { 0.5f, 0.1f, 1.0f, 0.5f};		//ビームの色
	std::vector<sProbability> ACT_PROBABILITY =	// 行動の抽選確率
	{
		{ CEnemyTurret::ACTION_BEAM, 0.3f },		// ビーム攻撃
		{ CEnemyTurret::ACTION_MORTAR, 0.7f },		// 迫撃攻撃
		{ CEnemyTurret::ACTION_WAIT, 0.0f },		// 待機
	};
}

//==========================================================================
// 関数ポインタ
//==========================================================================
CEnemyTurret::ACT_FUNC CEnemyTurret::m_ActFuncList[] =
{
	&CEnemyTurret::ActAttackBeam,		// 遠隔
	&CEnemyTurret::ActAttackMortar,		// 突撃
	&CEnemyTurret::ActWait,				// 待機
	&CEnemyTurret::Spawn,				// スポーン
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

	// 出現待機状態にする
	m_state = CEnemy::STATE_SPAWNWAIT;
	m_Action = ACTION_SPAWN;

	return S_OK;
}

//==========================================================================
//  終了処理
//==========================================================================
void CEnemyTurret::Uninit(void)
{
	CScene *pScene = CManager::GetInstance()->GetScene();

	//ゲームならプレイヤー進化
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

	// スクリーン内の存在判定
	if (m_state == CEnemy::STATE_SPAWNWAIT && CManager::GetInstance()->GetCamera()->OnScreen(GetPosition()))
	{
		m_state = STATE_SPAWN;
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

//==========================================
// スポーン
//==========================================
void CEnemyTurret::Spawn(void)
{
	if (m_state == STATE_SPAWNWAIT)
	{
		return;
	}

	int nType = m_pMotion->GetType();

	if (nType == MOTION_SPAWN && m_pMotion->IsFinish() == true)
	{// 登場が終わってたら

	 // なにもない
		m_state = STATE_NONE;
		m_Action = ACTION_WAIT;
		return;
	}

	// モーションカウンター取得
	float fAllCount = m_pMotion->GetAllCount();
	if ((int)fAllCount % 10 == 0)
	{
		// 角度の取得
		D3DXVECTOR3 rot = GetRotation();

		// 衝撃波生成
		CImpactWave *pWave = CImpactWave::Create
		(
			GetCenterPosition(),	// 位置
			D3DXVECTOR3((float)Random(-31, 31) * 0.1f, D3DX_PI * 0.5f + rot.y, 0.0f),	// 向き
			D3DXCOLOR(0.9f, 0.2f, 0.9f, 0.8f),	// 色
			150.0f,								// 幅
			0.0f,								// 高さ
			90.0f,								// 中心からの間隔
			20,									// 寿命
			8.0f,								// 幅の移動量
			CImpactWave::TYPE_GIZAGRADATION,	// テクスチャタイプ
			true								// 加算合成するか
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

	// 登場演出
	my_particle::Create(GetCenterPosition(), my_particle::TYPE_UNDERBOSS_SPAWN);

	if (nType != MOTION_SPAWN)
	{
		// 登場モーション設定
		m_pMotion->Set(MOTION_SPAWN);
	}
}

//==========================================================================
// 行動抽選
//==========================================================================
void CEnemyTurret::DrawingAction(void)
{
	// 0～1のランダム値取得
	float fRandomValue = static_cast<float>(std::rand()) / RAND_MAX;

	// 確率加算用変数
	float fDrawingProbability = 0.0;

	// 行動抽選要素分繰り返し
	for (const auto& candidate : ACT_PROBABILITY)
	{
		// 今回の確率分を加算
		fDrawingProbability += candidate.fProbability;

		if (fRandomValue < fDrawingProbability)
		{// 今回のランダム値が確率を超えたら

		 // 行動決定
			m_Action = candidate.action;

			// 行動カウンターリセット
			m_fActTime = 0.0f;
			break;
		}
	}

	// 次の行動別
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

	//一番近いプレイヤーを認識する
	SetTargetPlayer();

	// ターゲットの方を向く
	RotationTarget();

	// チャージフラグを立てる
	m_sMotionFrag.bCharge = true;
}

//==========================================================================
// ビーム発射
//==========================================================================
void CEnemyTurret::AttackBeam(void)
{
	int nType = m_pMotion->GetType();

	if (nType == MOTION_BEAM && m_pMotion->IsFinish() == true)
	{// ビーム攻撃が終わってたら

		float fRot = GetRotation().y;
		D3DXVECTOR3 move = {sinf(fRot + D3DX_PI) * MORTAR_SPEED,
							0.0f,
							cosf(fRot + D3DX_PI) * MORTAR_SPEED };

		CBeam::Create(GetPosition(), move, BEAM_COLOR, 50.0f, BEAM_LENGTH, 50, 10, 1, CCollisionObject::TAG_ENEMY);

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
		CBullet *pBullet = CBullet::Create(CBullet::TYPE_ENEMY, CBullet::MOVETYPE_PARABOLA, GetPosition(), rot, move, 50.0f);
		pBullet->SetTargetPosition(pPlayer->GetPosition());

		float fRatio = GetFabsPosLength(GetPosition(), pPlayer->GetPosition()) / 1500.0f;
		ValueNormalize(fRatio, 1.0f, 0.0f);
		pBullet->SetParabolaHeight(1000.0f - (1000.0f * fRatio));
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
	if (fabsf(fRotDiff) > 0.1f)
	{
		rot.y += fRotDiff * 0.05f;
	}
	else
	{
		rot.y += fRotDiff * 1.0f;
	}

	RotNormalize(rot.y);

	// 向き設定
	SetRotation(rot);

	// 目標の向き設定
	SetRotDest(fRotDest);
}

//==========================================================================
// どのプレイヤーのターゲット
//==========================================================================
void CEnemyTurret::SetTargetPlayer(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 posPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fLength = 0.0f, fLengthDiff = 0.0f;
	CPlayer* pPlayer = nullptr;

	//初期値入れ
	pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(0);

	if (pPlayer == NULL)
	{
		return;
	}

	posPlayer = pPlayer->GetPosition();
	fLengthDiff = GetFabsPosLength(pos, posPlayer);
	m_nTargetPlayerIndex = 0;
	SetTargetPosition(posPlayer);

	// プレイヤー情報
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(i);

		if (pPlayer == NULL)
		{
			continue;
		}

		// プレイヤーの位置取得
		posPlayer = pPlayer->GetPosition();

		fLength = GetFabsPosLength(pos, posPlayer);

		if (fLength < fLengthDiff)
		{//より近い
			m_nTargetPlayerIndex = i;
			fLengthDiff = fLength;
			SetTargetPosition(posPlayer);
		}
	}
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
