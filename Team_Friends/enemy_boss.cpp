//==========================================================================
// 
//  ボス処理 [enemy_boss.cpp]
//  Author : 相馬靜雅
// 
//==========================================================================
#include "enemy_boss.h"
#include "manager.h"
#include "debugproc.h"
#include "calculation.h"
#include "hp_gauge.h"

//==========================================================================
//  定数定義
//==========================================================================
namespace
{
	const float LENGTH_CHASEWALK = 1000.0f;	// 歩き追従の長さ
}

//==========================================================================
// 関数ポインタ
//==========================================================================
CEnemyBoss::ACT_FUNC CEnemyBoss::m_ActFuncList[] =
{
	&CEnemyBoss::ActChase,				// 追い掛け
	&CEnemyBoss::ActAttackProximity,	// 近接
	&CEnemyBoss::ActAttackRemote,		// 遠隔
	&CEnemyBoss::ActAttackAssault,		// 突撃
	&CEnemyBoss::ActAttackExplosion,	// 自爆
};

//==========================================================================
//  コンストラクタ
//==========================================================================
CEnemyBoss::CEnemyBoss(int nPriority) : CEnemy(nPriority)
{
	m_Action = ACTION_CHASE;		// 行動
	m_ActionBranch = ACTBRANCH_CHASE_SLOW;	// 行動分岐
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
// 行動設定
//==========================================================================
void CEnemyBoss::ActionSet(void)
{

	while (1)
	{
		// 行動抽選
		m_Action = (ACTION)(rand() % ACTION_MAX);

		if (m_Action != ACTION_SELFEXPLOSION &&
			m_Action != ACTION_CHASE)
		{// 既定行動以外
			break;
		}
	}

	// 次の行動別
	int nActRand;
	switch (m_Action)
	{
	case CEnemyBoss::ACTION_CHASE:	// 追従
		if (CalcLenPlayer(LENGTH_CHASEWALK))
		{// 歩きの範囲
			m_ActionBranch = ACTBRANCH_CHASE_SLOW;
		}
		else
		{
			m_ActionBranch = ACTBRANCH_CHASE_DASH;
		}
		break;

	case CEnemyBoss::ACTION_PROXIMITY:	// 近接攻撃
		nActRand = Random(ACTBRANCH_PROXIMITY_PUNCH, ACTBRANCH_PROXIMITY_KICK);
		m_ActionBranch = static_cast<eActionBranch>(nActRand);
		break;

	case CEnemyBoss::ACTION_REMOTE:	// 遠隔攻撃
		m_ActionBranch = ACTBRANCH_REMOTE_BEAM;
		break;

	case CEnemyBoss::ACTION_ASSAULT:	// 突撃攻撃
		m_ActionBranch = ACTBRANCH_ASSAULT_CHARGE;
		break;

	default:
		break;
	}
}

//==========================================================================
// 行動更新
//==========================================================================
void CEnemyBoss::UpdateAction(void)
{
	// 状態別処理
	(this->*(m_ActFuncList[m_Action]))();
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
	switch (m_ActionBranch)
	{
	case CEnemyBoss::ACTBRANCH_CHASE_SLOW:
		ChaseSlow();
		break;

	case CEnemyBoss::ACTBRANCH_CHASE_DASH:
		ChaseDash();
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
// 近接攻撃
//==========================================================================
void CEnemyBoss::ActAttackProximity(void)
{
	// 攻撃フラグを立てる
	m_sMotionFrag.bATK = true;

	// ターゲットの方を向く
	RotationTarget();

	// 行動別移動処理
	switch (m_ActionBranch)
	{
	case CEnemyBoss::ACTBRANCH_PROXIMITY_PUNCH:
		AttackPunch();
		break;

	case CEnemyBoss::ACTBRANCH_PROXIMITY_KICK:
		AttackKick();
		break;

	default:
		break;
	}
}

//==========================================================================
// パンチ攻撃
//==========================================================================
void CEnemyBoss::AttackPunch(void)
{

}

//==========================================================================
// キック攻撃
//==========================================================================
void CEnemyBoss::AttackKick(void)
{

}

//==========================================================================
// 遠隔攻撃
//==========================================================================
void CEnemyBoss::ActAttackRemote(void)
{
	// 攻撃フラグを立てる
	m_sMotionFrag.bATK = true;

	// ターゲットの方を向く
	RotationTarget();

	// 行動別移動処理
	switch (m_ActionBranch)
	{
	case CEnemyBoss::ACTBRANCH_REMOTE_BEAM:
		AttackBeam();
		break;

	default:
		break;
	}
}

//==========================================================================
// ビーム攻撃
//==========================================================================
void CEnemyBoss::AttackBeam(void)
{

}

//==========================================================================
// 突撃攻撃
//==========================================================================
void CEnemyBoss::ActAttackAssault(void)
{
	// 攻撃フラグを立てる
	m_sMotionFrag.bATK = true;

	// ターゲットの方を向く
	RotationTarget();

	// 行動別移動処理
	switch (m_ActionBranch)
	{
	case CEnemyBoss::ACTBRANCH_ASSAULT_CHARGE:
		ChargeTackle();
		break;

	case CEnemyBoss::ACTBRANCH_ASSAULT_TACKLE:
		AttackTackle();
		break;

	default:
		break;
	}
}

//==========================================================================
// タックルチャージ
//==========================================================================
void CEnemyBoss::ChargeTackle(void)
{

}

//==========================================================================
// タックル攻撃
//==========================================================================
void CEnemyBoss::AttackTackle(void)
{

}

//==========================================================================
// 自爆攻撃
//==========================================================================
void CEnemyBoss::ActAttackExplosion(void)
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

