//==========================================
//
//  ギガントエッジ(enemy_riot.cpp)
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
//  定数定義
//==========================================
namespace
{
	const float ATTACK_LENGTH = 200.0f; // 攻撃する距離
	const float MOVE_SPEED = 300.0f; // 移動速度
	const float WAIT_TIMER = 3.0f; // 初期待機時間
	const float ROTATION_TIMER = 1.0f; // 軸合わせに要する時間
	const float TACKLE_TIMER = 2.0f; // 軸合わせに要する時間
}

//==========================================
//  コンストラクタ
//==========================================
CEnemyRiot::CEnemyRiot(int nPriority) :
	m_Act(ACTION_DEF),
	m_fWaitTime(0.0f)
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemyRiot::~CEnemyRiot()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemyRiot::Init(void)
{
	//初期化処理
	CEnemy::Init();

	// HPの設定
	m_pHPGauge = CHP_Gauge::Create(100.0f, GetLifeOrigin());

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CEnemyRiot::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemyRiot::Update(void)
{
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

//==========================================
//  描画処理
//==========================================
void CEnemyRiot::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}

//==========================================
//  殺す
//==========================================
void CEnemyRiot::Kill(void)
{
	// 死亡処理
	CEnemy::Kill();
}

//==========================================
//  モーションセット
//==========================================
void CEnemyRiot::MotionSet(void)
{
	if (m_pMotion->IsFinish() == true)
	{// 終了していたら

		// 場合分け
		switch (m_Act)
		{
		case ACTION_DEF: // 待機行動
			m_pMotion->Set(MOTION_DEF); // 待機モーション
			break;

		case ACTION_MOVE: // 移動行動
			m_pMotion->Set(MOTION_WALK); // 移動モーション
			break;

		case ACTION_AXIS: // 軸合わせ行動
			m_pMotion->Set(MOTION_DEF); // 待機モーション
			break;

		case ACTION_TACKLE: // 突進行動
			m_pMotion->Set(MOTION_WALK); // 移動モーション
			break;

		case ACTION_ATTACK: // 攻撃行動
			m_pMotion->Set(MOTION_ATK); // 攻撃モーション
			break;

		default:
			m_pMotion->Set(MOTION_DEF); // 待機モーション
			break;
		}
	}
}

//==========================================
//  行動セット
//==========================================
void CEnemyRiot::ActionSet(void)
{
	// デバッグ表示
	CManager::GetInstance()->GetDebugProc()->Print
	(
		"カウンター : %f\n"
		"中ボスのアクション : ",
		m_fWaitTime
	);

	switch (m_Act)
	{
	case ACTION_ATTACK: // 攻撃状態

		if (m_pMotion->IsFinish())
		{
			//軸合わせに移行
			m_Act = ACTION_AXIS;
		}
		else
		{
			// 待機時間を加算
			m_fWaitTime += CManager::GetInstance()->GetDeltaTime();

			// 攻撃をする
			Attack();
		}

		// デバッグ表示
		CManager::GetInstance()->GetDebugProc()->Print
		(
			"攻撃\n\n"
		);

		break;

	case ACTION_TACKLE: // 突進状態

		if (m_fWaitTime >= TACKLE_TIMER)
		{
			// 待機時間をリセット
			m_fWaitTime = 0.0f;

			//軸合わせに移行
			m_Act = ACTION_AXIS;
		}
		else
		{
			// 待機時間を加算
			m_fWaitTime += CManager::GetInstance()->GetDeltaTime();

			// タックル
			Move();
		}

		// デバッグ表示
		CManager::GetInstance()->GetDebugProc()->Print
		(
			"突進\n\n"
		);

		break;

	case ACTION_AXIS: // 軸合わせ状態

		if (m_fWaitTime >= ROTATION_TIMER)
		{
			// 待機時間をリセット
			m_fWaitTime = 0.0f;

			// プレイヤーとの距離を計測
			if (CalcLenPlayer(ATTACK_LENGTH)) // 近ければ攻撃
			{
				m_Act = ACTION_ATTACK;
			}
			else // 遠かったらタックル
			{
				m_Act = ACTION_TACKLE;
			}
		}
		else
		{
			// 待機時間を加算
			m_fWaitTime += CManager::GetInstance()->GetDeltaTime();

			// プレイヤーの方向を向く
			RotationPlayer();
		}

		// デバッグ表示
		CManager::GetInstance()->GetDebugProc()->Print
		(
			"軸合わせ\n\n"
		);

		break;

	case ACTION_DEF: // 初期待機状態

		if (m_fWaitTime >= WAIT_TIMER)
		{
			// 待機時間をリセット
			m_fWaitTime = 0.0f;

			//軸合わせに移行
			m_Act = ACTION_AXIS;
		}
		else
		{
			// 待機時間を加算
			m_fWaitTime += CManager::GetInstance()->GetDeltaTime();
		}

		// デバッグ表示
		CManager::GetInstance()->GetDebugProc()->Print
		(
			"待機\n\n"
		);

		break;

	default:
		break;
	}
}

//==========================================
//  移動
//==========================================
void CEnemyRiot::Move(void)
{
	// 角度の取得
	D3DXVECTOR3 rot = GetRotation();

	// 移動量を取得
	D3DXVECTOR3 move = GetMove();

	// 移動量を分解する
	move.x = -cosf(rot.y) * MOVE_SPEED * CManager::GetInstance()->GetDeltaTime();
	move.z = -sinf(rot.y) * MOVE_SPEED * CManager::GetInstance()->GetDeltaTime();

	// 移動量を適用する
	SetMove(move);
}

//==========================================
//  攻撃
//==========================================
void CEnemyRiot::Attack(void)
{
	// 攻撃処理
	CEnemy::StateAttack();

	// モーションの情報取得
	CMotion::Info aInfo = m_pMotion->GetInfo(m_pMotion->GetType());

	// 攻撃情報の総数取得
	int nNumAttackInfo = aInfo.nNumAttackInfo;

	bool bAtkWait = true;	// 攻撃待機中
	for (int nCntAttack = 0; nCntAttack < nNumAttackInfo; nCntAttack++)
	{
		if (aInfo.AttackInfo[nCntAttack] == NULL)
		{// NULLだったら
			continue;
		}

		// モーションカウンター取得
		if (m_pMotion->GetAllCount() > aInfo.AttackInfo[nCntAttack]->nMinCnt)
		{// 攻撃判定中
			// 攻撃判定中にする
			bAtkWait = false;
		}
	}

	if (bAtkWait == false)
	{// 判定中の時
		return;
	}
}
