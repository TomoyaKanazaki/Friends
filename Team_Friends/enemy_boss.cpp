//=============================================================================================================
// 
//  ボス処理 [enemy_boss.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================================================
#include "enemy_boss.h"
#include "player.h"
#include "manager.h"
#include "debugproc.h"
#include "calculation.h"
#include "hp_gauge.h"

//==========================================================================
//  定数定義
//==========================================================================
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
	&CEnemyBoss::ActChase,
	&CEnemyBoss::ActAttack,
	&CEnemyBoss::ActCharge,
};

//==========================================================================
//  コンストラクタ
//==========================================================================
CEnemyBoss::CEnemyBoss(int nPriority) : CEnemy(nPriority)
{
	m_Act = ACTION_CHASE;		// 行動
	m_TargetPosition = mylib_const::DEFAULT_VECTOR3;	// 目標の位置
	m_fActTime = 0.0f;			// 行動カウンター
}

//==========================================================================
//  デストラクタ
//==========================================================================
CEnemyBoss::~CEnemyBoss()
{

}

//==========================================================================
//  初期化処理
//==========================================================================
HRESULT CEnemyBoss::Init(void)
{
	//初期化処理
	CEnemy::Init();

	// HPの設定
	m_pHPGauge = CHP_Gauge::Create(100.0f, GetLifeOrigin());

	return S_OK;
}

//==========================================================================
//  終了処理
//==========================================================================
void CEnemyBoss::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//==========================================================================
//  更新処理
//==========================================================================
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

//==========================================================================
// 行動更新
//==========================================================================
void CEnemyBoss::UpdateAction(void)
{
	// 状態別処理
	(this->*(m_ActFuncList[m_Act]))();
}

//==========================================================================
// 追い掛け
//==========================================================================
void CEnemyBoss::ActChase(void)
{
	// 移動フラグを立てる
	m_sMotionFrag.bMove = true;

	// ターゲットの方を向く
	RotationTarget();

	// 行動別移動処理
	switch (m_Act)
	{
	case CEnemyBoss::ACTION_CHASE:
		break;

	case CEnemyBoss::ACTION_CHASE_DASH:
		break;

	default:
		break;
	}
}

//==========================================================================
// 歩き追い掛け
//==========================================================================
void CEnemyBoss::ChaseSlow(void)
{

}

//==========================================================================
// ダッシュ追い掛け
//==========================================================================
void CEnemyBoss::ChaseDash(void)
{

}

//==========================================================================
// 攻撃
//==========================================================================
void CEnemyBoss::ActAttack(void)
{
	// 移動フラグを立てる
	m_sMotionFrag.bMove = true;

	// ターゲットの方を向く
	RotationTarget();

	// 行動別移動処理
	switch (m_Act)
	{
	case CEnemyBoss::ACTION_CHASE:
		break;

	case CEnemyBoss::ACTION_CHASE_DASH:
		break;

	default:
		break;
	}
}

//==========================================================================
// チャージ
//==========================================================================
void CEnemyBoss::ActCharge(void)
{

}

//==========================================================================
//  描画処理
//==========================================================================
void CEnemyBoss::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}

//==========================================================================
//  殺す
//==========================================================================
void CEnemyBoss::Kill(void)
{
	// 死亡処理
	CEnemy::Kill();
}

//==========================================================================
//  モーションセット
//==========================================================================
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
////==========================================================================
////  攻撃
////==========================================================================
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

//==========================================================================
// ターゲットの方を向く
//==========================================================================
void CEnemyBoss::RotationTarget(void)
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
	rot.y += fRotDiff * 0.025f;
	RotNormalize(rot.y);

	// 向き設定
	SetRotation(rot);

	// 目標の向き設定
	SetRotDest(fRotDest);
}

