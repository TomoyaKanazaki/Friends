//==========================================
//
//  砲台中ボス敵(enemy_turret.cpp)
//  Author : Kai Takada
//
//==========================================
#include "enemy_turret.h"
#include "player.h"
#include "manager.h"
#include "debugproc.h"
#include "calculation.h"
#include "hp_gauge.h"
#include "particle.h"
#include "particle.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const float ATTACK_LENGTH = 200.0f;
	const float MOVE_SPEED = 0.01f;
	const float ATTACK_SPEED = 10.0f;
	const float MOVE_X = 2.0f;
	const float MOVE_Z = 2.0f;
	const float READY_TIME = 3.0f;
	const float ATTACK_TIME = 1.0f;
	const float AFTER_TIME = 2.0f;
	const float SEARCH_ROT = 45.0f;
	const float AFTER_FIXROT = 0.07f;
}

//==========================================
//  コンストラクタ
//==========================================
CEnemyTurret::CEnemyTurret(int nPriority) :
	m_Act(ACTION_ROAMING),
	m_Atk(ATTACK_NONE),
	m_fActionCount(0.0f),
	m_moveLock(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_fRotLock(0.0f)
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemyTurret::~CEnemyTurret()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemyTurret::Init(void)
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
void CEnemyTurret::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemyTurret::Update(void)
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
}

//==========================================================================
// 行動更新
//==========================================================================
void CEnemyTurret::UpdateAction(void)
{
	D3DXVECTOR3 pos = GetPosition();

	// 行動ごとの行動
	switch (m_Act)
	{
	case CEnemyTurret::ACTION_ROAMING:

		//移動
		Move();

		break;

	case CEnemyTurret::ACTION_READY:

		//デバッグ用
		my_particle::Create(pos, my_particle::TYPE_SMOKE);

		// 移動量を設定
		RotationPlayer();

		break;

	case CEnemyTurret::ACTION_ATTACK:

		//デバッグ用
		my_particle::Create(pos, my_particle::TYPE_SMOKE_RED);

		// 攻撃
		Attack();

		break;

	case CEnemyTurret::ACTION_AFTER:

		//デバッグ用
		my_particle::Create(pos, my_particle::TYPE_SMOKE);

		FixRotation();

		break;

	default:
		break;
	}

	if (m_Act != ACTION_ROAMING)
	{
		// カウンターを加算
		m_fActionCount += CManager::GetInstance()->GetDeltaTime();
	}
}

//==========================================
//  描画処理
//==========================================
void CEnemyTurret::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}

//==========================================
//  殺す
//==========================================
void CEnemyTurret::Kill(void)
{
	// 死亡処理
	CEnemy::Kill();
}

//==========================================
//  モーションセット
//==========================================
void CEnemyTurret::MotionSet(void)
{
	if (m_pMotion->IsFinish() == true)
	{// 終了していたら

		// 現在の種類取得
		int nType = m_pMotion->GetType();

		if (m_sMotionFrag.bKnockback == true)
		{// やられ中だったら

			// やられモーション
			m_pMotion->Set(MOTION_KNOCKBACK);
		}
		else if (m_sMotionFrag.bATK == true)
		{// 攻撃していたら

			m_sMotionFrag.bATK = false;		// 攻撃判定OFF

			// 攻撃モーション
			if (m_Atk == ATTACK_BEAM)
			{
				m_pMotion->Set(MOTION_ATK_BEAM);
			}
			else if (m_Atk == ATTACK_MORTAR)
			{
				m_pMotion->Set(MOTION_ATK_MORTAR);
			}
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
void CEnemyTurret::ActionSet(void)
{
	if (m_Act == ACTION_READY)
	{
		if (m_fActionCount >= READY_TIME)
		{
			m_Act = ACTION_ATTACK;
			m_fActionCount = 0.0f;
		}

		return;
	}
	else if (m_Act == ACTION_ATTACK)
	{
		if (m_fActionCount >= ATTACK_TIME)
		{
			m_Act = ACTION_AFTER;
			m_fActionCount = 0.0f;
			m_moveLock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}

		return;
	}
	else if (m_Act == ACTION_AFTER)
	{
		if (m_fActionCount >= AFTER_TIME)
		{
			m_Act = ACTION_ROAMING;
			m_fActionCount = 0.0f;
		}

		return;
	}

	if (m_Act == ACTION_ROAMING)
	{
		//攻撃に移行
		//攻撃の決定方法どうする

		// 距離が近いと攻撃状態になる
		m_Act = ACTION_READY;
		m_fActionCount = 0.0f;
	}
}

//==========================================
//  移動
//==========================================
void CEnemyTurret::Move(void)
{
	// 移動フラグを立てる
	m_sMotionFrag.bMove = true;

	// 移動カウンターを加算
	m_fActionCount += MOVE_SPEED;

	// 移動量を適用
	D3DXVECTOR3 move = GetMove();
	move.x = sinf(m_fActionCount) * MOVE_X;
	move.z = cosf(m_fActionCount) * MOVE_Z;
	SetMove(move);

	// 方向転換
	MoveRotation();
}

//==========================================
//  移動方向を向く処理
//==========================================
void CEnemyTurret::MoveRotation(void)
{
	// 必要な値を取得
	D3DXVECTOR3 rot = GetRotation();
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 posDest = pos + move;
	D3DXVECTOR3 posDiff = posDest - pos;

	// 方向を算出
	float fRot = atan2f(-posDiff.x, -posDiff.z);

	//角度の正規化
	RotNormalize(fRot);

	//角度の補正をする
	rot.y = fRot;

	// 向き設定
	SetRotation(rot);
}

//==========================================
//  攻撃
//==========================================
void CEnemyTurret::Attack(void)
{
	D3DXVECTOR3 move = GetMove();

	if (m_moveLock == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		m_sMotionFrag.bATK = true;

		// プレイヤー情報
		CPlayer* pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(m_nTargetPlayerIndex);
		if (pPlayer == NULL)
		{
			return;
		}

		// 情報取得
		D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
		D3DXVECTOR3 pos = GetPosition();

		//攻撃判定アリ凸

		// プレイヤーから自身に向かうベクトルを算出
		D3DXVECTOR3 vecToPlayer = posPlayer - pos;

		// ベクトルの正規化
		vecToPlayer.y = 0.0f;
		D3DXVec3Normalize(&vecToPlayer, &vecToPlayer);
		vecToPlayer *= ATTACK_SPEED;

		//角度を反転
		m_fRotLock = GetRotation().y + D3DX_PI;
		RotNormalize(m_fRotLock);

		// 移動量の設定
		move.x = vecToPlayer.x;
		move.z = vecToPlayer.z;
		SetMove(move);

		m_moveLock = move;

		return;
	}

	SetMove(m_moveLock);
}

//==========================================
//  プレイヤーを向く処理
//==========================================
void CEnemyTurret::RotationPlayer(void)
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
	rot.y += fRotDiff * 0.025f;

	// 角度の正規化
	RotNormalize(rot.y);

	// 向き設定
	SetRotation(rot);

	// 目標の向き設定
	SetRotDest(fRotDest);
}

//==========================================
//　向きから移動量を設定
//==========================================
void CEnemyTurret::SetMoveRotation(void)
{
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 rot = GetRotation();
	move.x = sinf(rot.y) * MOVE_X * ATTACK_SPEED;
	move.z = cosf(rot.y) * MOVE_Z * ATTACK_SPEED;
	SetMove(move);
}

//==========================================
//  プレイヤーを探す判定
//==========================================
bool CEnemyTurret::SearchPlayer(float fLen)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();
	D3DXVECTOR3 posL = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//索敵扇の左点
	D3DXVECTOR3 posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//索敵扇の右点

	//float fRot = SEARCH_ROT * D3DX_PI / 180;
	float fRot = 0.785f;


	//プレイヤーの人数を把握

	//一番近いやつを標的にする
	for (int nCnt = 0; nCnt < mylib_const::MAX_PLAYER; nCnt++)
	{
		// プレイヤー情報
		CPlayer* pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(nCnt);
		if (pPlayer == NULL)
		{
			continue;
		}
	}



	// プレイヤーの位置取得
	//D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

	//// 一定範囲内の判定
	//if (CollisionFan(pos, posL, posR, posPlayer, fRot))
	//{
	//	return true;
	//}

	return false;
}

//==========================================
// 指定方向に向く
//==========================================
void CEnemyTurret::FixRotation(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();

	// 目標との差分
	float fRotDiff = m_fRotLock - rot.y;

	//角度の正規化
	RotNormalize(fRotDiff);

	//角度の補正をする
	rot.y += fRotDiff * AFTER_FIXROT;

	// 角度の正規化
	RotNormalize(rot.y);

	// 向き設定
	SetRotation(rot);

	// 目標の向き設定
	SetRotDest(m_fRotLock);
}
