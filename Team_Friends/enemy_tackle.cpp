//==========================================
//
//  突撃敵(enemy_tackle.cpp)
//  Author : Kai Takada
//
//==========================================
#include "enemy_tackle.h"
#include "player.h"
#include "manager.h"
#include "debugproc.h"
#include "calculation.h"
#include "hp_gauge.h"
#include "bullet.h"
#include "collisionobject.h"

//デバッグ
#if _DEBUG
#include "particle.h"
#endif

//==========================================
//  定数定義
//==========================================
namespace
{
	const float SEARCH_LENGTH = 400.0f;		//索敵距離
	const float ATTACK_LENGTH = 200.0f;		//攻撃距離
	const float MOVE_SPEED = 1.0f;			//徘徊時速度
	const float ATTACK_SPEED = 10.0f;		//突撃速度
	const float READY_TIME = 3.0f;			//準備時間
	const float ATTACK_TIME = 1.0f;			//突撃時間
	const float AFTER_TIME = 2.0f;			//硬直時間
	const float SEARCH_ROT = 0.785f;		//正面からの索敵範囲(計算に変更)
	const float AFTER_FIXROT = 0.07f;		//硬直時の方向修正速度
	const float FIXROT_GRACE = 0.5f;		//方向修正までの猶予
	const float ROAM_CHANGE_ROT = 3.0f;		//徘徊時の方向転換タイミング
	const int ATTACK = 1;		//攻撃力
	const int FIXROT = 16;		//方向転換の片分割
}

//==========================================
//  コンストラクタ
//==========================================
CEnemyTackle::CEnemyTackle(int nPriority) :
	m_Act(ACTION_ROAMING),
	m_fActionCount(0.0f),
	m_moveLock(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_fRotLock(0.0f),
	m_nAttack(0)
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemyTackle::~CEnemyTackle()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemyTackle::Init(void)
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
void CEnemyTackle::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemyTackle::Update(void)
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
// 行動更新
//==========================================
void CEnemyTackle::UpdateAction(void)
{
	D3DXVECTOR3 pos = GetPosition();

	// 行動ごとの行動
	switch (m_Act)
	{
	case CEnemyTackle::ACTION_ROAMING:

		//移動
		Roaming();

		break;

	case CEnemyTackle::ACTION_READY:

		// 移動量を設定
		RotationPlayer();

		break;

	case CEnemyTackle::ACTION_ATTACK:

#if _DEBUG
		my_particle::Create(pos, my_particle::TYPE_CHECK);
#endif

		// 攻撃
		Attack();

		break;

	case CEnemyTackle::ACTION_AFTER:

		if (m_fActionCount > FIXROT_GRACE)
		{//猶予が過ぎたら方向転換
			FixRotation();
		}

		break;

	default:
		break;
	}

	// カウンターを加算
	m_fActionCount += CManager::GetInstance()->GetDeltaTime();
}

//==========================================
//  描画処理
//==========================================
void CEnemyTackle::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}

//==========================================
//  殺す
//==========================================
void CEnemyTackle::Kill(void)
{
	// 死亡処理
	CEnemy::Kill();
}

//==========================================
//  モーションセット
//==========================================
void CEnemyTackle::MotionSet(void)
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
void CEnemyTackle::ActionSet(void)
{
	switch (m_Act)
	{
	case CEnemyTackle::ACTION_ROAMING:

		if (SearchPlayer(SEARCH_LENGTH))
		{// 索敵

		 // 距離が近いと攻撃状態になる
			m_Act = ACTION_READY;
			m_fActionCount = 0.0f;
		}

		break;

	case CEnemyTackle::ACTION_READY:

		if (m_fActionCount >= READY_TIME)
		{
			m_Act = ACTION_ATTACK;
			m_fActionCount = 0.0f;
		}

		break;

	case CEnemyTackle::ACTION_ATTACK:
		
		if (m_fActionCount >= ATTACK_TIME)
		{
			m_Act = ACTION_AFTER;
			m_fActionCount = 0.0f;
			m_moveLock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		
		break;

	case CEnemyTackle::ACTION_AFTER:

		if (m_fActionCount >= AFTER_TIME)
		{
			m_Act = ACTION_ROAMING;
			m_fActionCount = 0.0f;
		}

		break;

	default:
		break;
	}
}

//==========================================
//  攻撃
//==========================================
void CEnemyTackle::Attack(void)
{
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 pos = GetPosition();//髪ゲーじゃん

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
		D3DXVECTOR3 rot = GetRotation();

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
		SetRotDest(m_fRotLock);

		// 移動量の設定
		move.x = sinf(rot.y + D3DX_PI) * ATTACK_SPEED;
		move.z = cosf(rot.y + D3DX_PI) * ATTACK_SPEED;
		SetMove(move);

		m_moveLock = move;

		return;
	}

	m_moveLock.y = move.y;
	SetMove(m_moveLock);
}

//==========================================
//　向きから移動量を設定
//==========================================
void CEnemyTackle::SetMoveRotation(void)
{
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 rot = GetRotation();

	// 移動速度取得
	float fMove = GetVelocity();

	move.x = sinf(rot.y) * fMove * ATTACK_SPEED;
	move.z = cosf(rot.y) * fMove * ATTACK_SPEED;
	SetMove(move);
}

//==========================================
//  プレイヤーを探す判定
//==========================================
bool CEnemyTackle::SearchPlayer(float fLen)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();
	D3DXVECTOR3 posL = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//索敵扇の左点
	D3DXVECTOR3 posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//索敵扇の右点

	float fRot = SEARCH_ROT;

	posL.x = pos.x + sinf(rot.y + fRot) * SEARCH_LENGTH;
	posL.z = pos.z + cosf(rot.y + fRot) * SEARCH_LENGTH;
	posR.x = pos.x + sinf(rot.y + -fRot) * SEARCH_LENGTH;
	posR.z = pos.z + cosf(rot.y + -fRot) * SEARCH_LENGTH;

	// プレイヤー情報
	CPlayer* pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(m_nTargetPlayerIndex);
	if (pPlayer == NULL)
	{
		return false;
	}

	// プレイヤーの位置取得
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

	// 一定範囲内の判定
	if (CollisionFan(pos, posL, posR, posPlayer, fRot))
	{
		return true;
	}

	return false;
}

//==========================================
// 指定方向に向く
//==========================================
void CEnemyTackle::FixRotation(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();
	float fRotDest = GetRotDest();

	// 目標との差分
	float fRotDiff = fRotDest - rot.y;

	//角度の正規化
	RotNormalize(fRotDiff);

	//角度の補正をする
	rot.y += fRotDiff * AFTER_FIXROT;

	// 角度の正規化
	RotNormalize(rot.y);

	// 向き設定
	SetRotation(rot);
}

//==========================================
// 徘徊
//==========================================
void CEnemyTackle::Roaming(void)
{
	D3DXVECTOR3 rot = GetRotation();
	float fRotDest = GetRotDest();
	D3DXVECTOR3 move = GetMove();

	//一定カウントでランダムにrot変更
	if (int(m_fActionCount * 100) % int(ROAM_CHANGE_ROT * 100) == 0)
	{
		float fRotDiff = (Random(-FIXROT, FIXROT) / 1.0f);
		RotNormalize(fRotDiff);
		rot.y += fRotDiff;
		RotNormalize(rot.y);
		SetRotDest(rot.y);

		m_fActionCount = 0.0f;
	}

	if (rot.y - fRotDest > -0.1f && rot.y - fRotDest < 0.1f)
	{//あらかた方向が目標方向合ったら
		//移動
		move.x = sinf(rot.y + D3DX_PI) * MOVE_SPEED;
		move.z = cosf(rot.y + D3DX_PI) * MOVE_SPEED;
		SetMove(move);
	}
	else
	{
		FixRotation();
	}
}

//==========================================================================
// プレイヤーを向く処理
//==========================================================================
void CEnemyTackle::RotationPlayer(void)
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
	rot.y += fRotDiff;

	// 角度の正規化
	RotNormalize(rot.y);

	// 向き設定
	SetRotation(rot);

	// 目標の向き設定
	SetRotDest(fRotDest);
}
