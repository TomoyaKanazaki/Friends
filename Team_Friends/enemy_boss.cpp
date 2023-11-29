//=============================================================================
// 
//  ボス処理 [enemy_boss.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "enemy_boss.h"
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
	const float ATTACK_LENGTH = 200.0f;
	const float MOVE_SPEED = 0.01f;
	const float MOVE_X = 2.0f;
	const float MOVE_Z = 2.0f;
}

//==========================================================================
// 関数ポインタ
//==========================================================================
CEnemyBoss::ACT_FUNC CEnemyBoss::m_ActFuncList[] =
{
	&CEnemyBoss::Move,
};

//==========================================
//  コンストラクタ
//==========================================
CEnemyBoss::CEnemyBoss(int nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemyBoss::~CEnemyBoss()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemyBoss::Init(void)
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
void CEnemyBoss::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemyBoss::Update(void)
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

	// モーションの更新
	MotionSet();
}


//==========================================
//  移動
//==========================================
void CEnemyBoss::Move(void)
{
	//// 移動フラグを立てる
	//m_sMotionFrag.bMove = true;

	//// 移動カウンターを加算
	//m_fMoveCount += MOVE_SPEED;

	//// 移動量を適用
	//D3DXVECTOR3 move = GetMove();
	//move.x = sinf(m_fMoveCount) * MOVE_X;
	//move.z = cosf(m_fMoveCount) * MOVE_Z;
	//SetMove(move);

	//// 方向転換
	//MoveRotation();
}

//==========================================
//  描画処理
//==========================================
void CEnemyBoss::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}

//==========================================
//  殺す
//==========================================
void CEnemyBoss::Kill(void)
{
	// 死亡処理
	CEnemy::Kill();
}

//==========================================
//  モーションセット
//==========================================
void CEnemyBoss::MotionSet(void)
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
//
////==========================================
////  攻撃
////==========================================
//void CEnemyBoss::Attack(void)
//{
//	// 攻撃処理
//	CEnemy::StateAttack();
//
//	// モーションの情報取得
//	CMotion::Info aInfo = m_pMotion->GetInfo(m_pMotion->GetType());
//
//	// 攻撃情報の総数取得
//	int nNumAttackInfo = aInfo.nNumAttackInfo;
//
//	bool bAtkWait = true;	// 攻撃待機中
//	for (int nCntAttack = 0; nCntAttack < nNumAttackInfo; nCntAttack++)
//	{
//		if (aInfo.AttackInfo[nCntAttack] == NULL)
//		{// NULLだったら
//			continue;
//		}
//
//		// モーションカウンター取得
//		if (m_pMotion->GetAllCount() > aInfo.AttackInfo[nCntAttack]->nMinCnt)
//		{// 攻撃判定中
//			// 攻撃判定中にする
//			bAtkWait = false;
//		}
//	}
//
//	if (bAtkWait == false)
//	{// 判定中の時
//		return;
//	}
//}
//
////==========================================
////  プレイヤーを向く処理
////==========================================
//void CEnemyBoss::RotationPlayer(void)
//{
//	// 位置取得
//	D3DXVECTOR3 pos = GetPosition();
//	D3DXVECTOR3 rot = GetRotation();
//
//	// プレイヤー情報
//	CPlayer* pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(m_nTargetPlayerIndex);
//	if (pPlayer == NULL)
//	{
//		return;
//	}
//
//	// プレイヤーの位置取得
//	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
//
//	// 目標の角度を求める
//	float fRotDest = atan2f((pos.x - posPlayer.x), (pos.z - posPlayer.z));
//
//	// 目標との差分
//	float fRotDiff = fRotDest - rot.y;
//
//	//角度の正規化
//	RotNormalize(fRotDiff);
//
//	//角度の補正をする
//	rot.y += fRotDiff * 0.025f;
//
//	// 角度の正規化
//	RotNormalize(rot.y);
//
//	// 向き設定
//	SetRotation(rot);
//
//	// 目標の向き設定
//	SetRotDest(fRotDest);
//}
//
////==========================================
////  プレイヤーとの距離を判定
////==========================================
//bool CEnemyBoss::CalcLenPlayer(float fLen)
//{
//	// 位置取得
//	D3DXVECTOR3 pos = GetPosition();
//
//	// プレイヤー情報
//	CPlayer* pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(m_nTargetPlayerIndex);
//	if (pPlayer == NULL)
//	{
//		return false;
//	}
//
//	// プレイヤーの位置取得
//	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
//
//	// 二点間を繋ぐベクトルの算出
//	D3DXVECTOR3 vecToPlayer = pos - posPlayer;
//
//	// ベクトルの大きさの2乗を算出
//	float fLength = vecToPlayer.x * vecToPlayer.x + vecToPlayer.z * vecToPlayer.z;
//
//	// 一定範囲内の判定
//	if (fLen * fLen >= fLength)
//	{
//		return true;
//	}
//
//	return false;
//}
