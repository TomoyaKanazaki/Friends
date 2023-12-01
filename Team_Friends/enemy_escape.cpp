//==========================================
//
//  コピペ用の敵(enemy_escape.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_escape.h"
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
	const float SEARCH_LENGTH = 400.0f;
	const float MOVE_SPEED = 0.03f;
	const float ESCAPE_SPEED = 5.00f;
	const float MOVE_X = 2.0f;
	const float MOVE_Z = 2.0f;
	const float FIND_TIME = 0.5f;
	const float ESCAPE_TIME = 3.0f;
}

//==========================================
//  コンストラクタ
//==========================================
CEnemyEscape::CEnemyEscape(int nPriority) :
	m_Act(ACTION_ROAMING),
	m_fMoveCount(0.0f),
	m_fCntFind(0.0f),
	m_fCntEscape(0.0f)
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemyEscape::~CEnemyEscape()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemyEscape::Init(void)
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
void CEnemyEscape::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemyEscape::Update(void)
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

	// 行動状態の更新
	ActionSet();

	// モーションの更新
	MotionSet();

	CManager::GetInstance()->GetDebugProc()->Print
	(
		"モーション : %d\n", m_pMotion->GetType()
	);
}

//==========================================
// 行動更新
//==========================================
void CEnemyEscape::UpdateAction(void)
{
	if (m_state == STATE_DEAD ||
		m_state == STATE_FADEOUT)
	{
		return;
	}

	// 行動ごとの行動
	switch (m_Act)
	{
	case CEnemyEscape::ACTION_ROAMING:

		// 移動
		Move();

		break;

	case CEnemyEscape::ACTION_FIND:

		// プレイヤーを向く
		RotationPlayer();

		// カウンターを加算
		m_fCntFind += CManager::GetInstance()->GetDeltaTime();

		break;

	case CEnemyEscape::ACTION_ESCAPE:

		// 逃走
		Escape();

		// カウンターを加算
		m_fCntEscape += CManager::GetInstance()->GetDeltaTime();

		break;

	case CEnemyEscape::ACTION_FADE:

		// 逃走
		Escape();

		// 消えてくれ
		SetState(STATE_FADEOUT);

		break;

	default:
		break;
	}
}

//==========================================
//  描画処理
//==========================================
void CEnemyEscape::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}

//==========================================
//  殺す
//==========================================
void CEnemyEscape::Kill(void)
{
	// 死亡処理
	CEnemy::Kill();
}

//==========================================
//  モーションセット
//==========================================
void CEnemyEscape::MotionSet(void)
{
	if (m_pMotion->IsFinish() == true)
	{// 終了していたら

		// 現在の種類取得
		int nType = m_pMotion->GetType();

		if (m_sMotionFrag.bMove == true && m_sMotionFrag.bKnockback == false)
		{// 移動していたら
			// 攻撃していない
			m_sMotionFrag.bATK = false;

			// 移動モーション
			m_pMotion->Set(MOTION_WALK);
		}
		else if (m_sMotionFrag.bKnockback == true)
		{// やられ中だったら

			// やられモーション
			m_pMotion->Set(MOTION_KNOCKBACK);
		}
		else if (m_sMotionFrag.bATK == true)
		{// 攻撃していたら

			m_sMotionFrag.bATK = false;		// 攻撃判定OFF

			// 攻撃モーション
			m_pMotion->Set(MOTION_ATK);
		}
		else
		{
			// ニュートラルモーション
			m_pMotion->Set(MOTION_DEF);
		}
	}
}

//==========================================
//  行動設定
//==========================================
void CEnemyEscape::ActionSet(void)
{
	// 消滅状態の場合は抜ける
	if (m_Act == ACTION_FADE)
	{
		return;
	}

	// 逃走状態から消滅する
	if (m_Act == ACTION_ESCAPE)
	{
		if (m_fCntEscape >= ESCAPE_TIME)
		{
			m_Act = ACTION_FADE;
		}
		return;
	}

	// 発見状態から逃走状態へ移行する
	if (m_Act == ACTION_FIND)
	{
		if (m_fCntFind >= FIND_TIME)
		{
			m_Act = ACTION_ESCAPE;
		}
		return;
	}

	if (CalcLenPlayer(SEARCH_LENGTH))
	{
		// 距離が近いと発見状態になる
		m_Act = ACTION_FIND;
	}
	else // 上記以外なら待機状態
	{
		m_Act = ACTION_ROAMING;
	}
}

//==========================================
//  移動
//==========================================
void CEnemyEscape::Move(void)
{
	// 移動フラグを立てる
	m_sMotionFrag.bMove = true;

	// 移動カウンターを加算
	m_fMoveCount += MOVE_SPEED;

	// 移動量を適用
	D3DXVECTOR3 move = GetMove();
	move.x = sinf(m_fMoveCount) * MOVE_X;
	move.z = cosf(m_fMoveCount) * MOVE_Z;
	SetMove(move);

	// 方向転換
	MoveRotation();
}

//==========================================
//  逃走
//==========================================
void CEnemyEscape::Escape(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// プレイヤー情報
	CPlayer* pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(m_nTargetPlayerIndex);
	if (pPlayer == NULL)
	{
		return;
	}

	// プレイヤーの位置取得
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

	// プレイヤーから自身に向かうベクトルを算出
	D3DXVECTOR3 vecToPlayer = pos - posPlayer;

	// ベクトルの正規化
	vecToPlayer.y = 0.0f;
	D3DXVec3Normalize(&vecToPlayer, &vecToPlayer);
	vecToPlayer *= ESCAPE_SPEED;

	// 移動量の取得
	D3DXVECTOR3 move = GetMove();

	// 移動量の設定
	move.x = vecToPlayer.x;
	move.z = vecToPlayer.z;
	SetMove(move);

	// 方向転換
	MoveRotation();
}

//==========================================
//  移動方向を向く処理
//==========================================
void CEnemyEscape::MoveRotation(void)
{
	// 必要な値を取得
	D3DXVECTOR3 rot = GetRotation();
	D3DXVECTOR3 move = GetMove();

	// 方向を算出
	float fRot = atan2f(-move.x, -move.z);

	//角度の正規化
	RotNormalize(fRot);

	//角度の補正をする
	rot.y = fRot;

	// 向き設定
	SetRotation(rot);
}

//==========================================
//  プレイヤーを向く処理
//==========================================
void CEnemyEscape::RotationPlayer(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();

	// プレイヤー情報
	CPlayer* pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(m_nTargetPlayerIndex);
	if (pPlayer == NULL)
	{
		return;
	}

	// プレイヤーの位置取得
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

	// 目標の角度を求める
	float fRotDest = atan2f((pos.x - posPlayer.x), (pos.z - posPlayer.z));

	// 目標との差分
	float fRotDiff = fRotDest - rot.y;

	//角度の正規化
	RotNormalize(fRotDiff);

	//角度の補正をする
	rot.y += fRotDiff * 0.1f;

	// 角度の正規化
	RotNormalize(rot.y);

	// 向き設定
	SetRotation(rot);

	// 目標の向き設定
	SetRotDest(fRotDest);
}

//==========================================
//  プレイヤーとの距離を判定
//==========================================
bool CEnemyEscape::CalcLenPlayer(float fLen)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// プレイヤー情報
	CPlayer* pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(m_nTargetPlayerIndex);
	if (pPlayer == NULL)
	{
		return false;
	}

	// プレイヤーの位置取得
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

	// 二点間を繋ぐベクトルの算出
	D3DXVECTOR3 vecToPlayer = pos - posPlayer;

	// ベクトルの大きさの2乗を算出
	float fLength = vecToPlayer.x * vecToPlayer.x + vecToPlayer.z * vecToPlayer.z;

	// 一定範囲内の判定
	if (fLen * fLen >= fLength)
	{
		return true;
	}

	return false;
}
