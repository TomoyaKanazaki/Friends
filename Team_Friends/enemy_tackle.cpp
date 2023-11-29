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

//==========================================
//  定数定義
//==========================================
namespace
{
	const float SEARCH_LENGTH = 400.0f;
	const float ATTACK_LENGTH = 200.0f;
	const float MOVE_SPEED = 0.01f;
	const float ATTACK_SPEED = 0.01f;
	const float MOVE_X = 2.0f;
	const float MOVE_Z = 2.0f;
	const float ATTACK_TIME = 3.0f;
	const float READY_TIME = 3.0f;
	const float AFTER_TIME = 3.0f;
	const float SEARCH_ROT = 45.0f;
}

//==========================================
//  コンストラクタ
//==========================================
CEnemyTackle::CEnemyTackle(int nPriority) :
	m_Act(ACTION_ROAMING),
	m_fActionCount(0.0f)
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

	// 行動状態の更新
	ActionSet();

	// モーションの更新
	MotionSet();
}

//==========================================================================
// 行動更新
//==========================================================================
void CEnemyTackle::UpdateAction(void)
{
	// 行動ごとの行動
	switch (m_Act)
	{
	case CEnemyTackle::ACTION_ROAMING:

		// 移動
		//Move();

		break;

	case CEnemyTackle::ACTION_ATTACK:

		// プレイヤーを向く
		//RotationPlayer();

		// 攻撃
		Attack();

		break;

	default:
		break;
	}
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
	// 逃走状態から消滅する
	if (m_Act == ACTION_READY)
	{
		if (m_fActionCount >= READY_TIME)
		{
			m_Act = ACTION_ATTACK;
		}

		return;
	}

	// 逃走状態から消滅する
	if (m_Act == ACTION_ATTACK)
	{
		if (m_fActionCount >= ATTACK_TIME)
		{
			m_Act = ACTION_AFTER;
		}

		return;
	}

	// 逃走状態から消滅する
	if (m_Act == ACTION_AFTER)
	{
		if (m_fActionCount >= ATTACK_TIME)
		{
			m_Act = ACTION_ROAMING;
		}

		return;
	}

	if (SearchPlayer(SEARCH_LENGTH))
	{// 索敵

		// 攻撃フラグを立てる
		if (m_Act == ACTION_ROAMING)
		{
			// 距離が近いと攻撃状態になる
			m_Act = ACTION_ATTACK;
		}
	}
}

//==========================================
//  移動
//==========================================
void CEnemyTackle::Move(void)
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
void CEnemyTackle::MoveRotation(void)
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
void CEnemyTackle::Attack(void)
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
		vecToPlayer *= ATTACK_SPEED;

		// 移動量の取得
		D3DXVECTOR3 move = GetMove();

		// 移動量の設定
		move.x = vecToPlayer.x;
		move.z = vecToPlayer.z;
		SetMove(move);

		// 方向転換
		MoveRotation();

		//攻撃判定アリ凸

		return;
	}
	else
	{//準備中

		//プレイヤーの方を向く
		RotationPlayer();

		return;
	}
}

//==========================================
//  プレイヤーを向く処理
//==========================================
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
	rot.y += fRotDiff * 0.025f;

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
bool CEnemyTackle::SearchPlayer(float fLen)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 posL = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//索敵扇の左点
	D3DXVECTOR3 posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//索敵扇の右点

	//float fRot = SEARCH_ROT * D3DX_PI / 180;
	float fRot = 0.7f;

	posL.x = pos.x + sinf(fRot) * SEARCH_LENGTH;
	posL.z = pos.z + cosf(fRot) * SEARCH_LENGTH;
	posR.x = pos.x + sinf(-fRot) * SEARCH_LENGTH;
	posR.z = pos.z + cosf(-fRot) * SEARCH_LENGTH;

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
