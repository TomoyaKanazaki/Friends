//==========================================
//
//  自爆する敵(enemy_explosion.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_explosion.h"
#include "player.h"
#include "manager.h"
#include "debugproc.h"
#include "calculation.h"
#include "hp_gauge.h"
#include "explosion.h"
#include "camera.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const float SEARCH_LENGTH = 1000.0f; // 索敵範囲
	const float EXPLOSION_LENGTH = 200.0f; // 爆発距離
	const float TURN_SPEED = 0.05f; // 振り向き速度
	const float WALK_TIME = 4.0f; // 移動時間
	const float COUNT_DAWN = 3.0f; // カウントダウンの時間
	const float FLASH_SPEED = 10.0f; // 点滅の速度
	const float CHASE_SPEED = 2.5f; // 追跡中の移動倍率
}

//==========================================
//  コンストラクタ
//==========================================
CEnemyExplosion::CEnemyExplosion(int nPriority) :
	m_Act(ACTION_ROAMING),
	m_fCntWalk(0.0f),
	m_fCntFind(0.0f),
	m_fCntEscape(0.0f),
	m_fRot(0.0f),
	m_fCountDawn(0.0f),
	m_fCol(0.0f)
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemyExplosion::~CEnemyExplosion()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemyExplosion::Init(void)
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
void CEnemyExplosion::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemyExplosion::Update(void)
{
	// 死亡の判定
	if (IsDeath() == true)
	{// 死亡フラグが立っていたら
		return;
	}

	// 行動変化
	ActionSet();

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
void CEnemyExplosion::UpdateAction(void)
{
	if (m_state == STATE_DEAD ||
		m_state == STATE_FADEOUT)
	{
		return;
	}

	// 行動ごとの行動
	switch (m_Act)
	{
	case CEnemyExplosion::ACTION_ROAMING:

		// ランダムな方向転換
		RandTurn();

		// 移動
		Move();

		break;

	case CEnemyExplosion::ACTION_CHASE:

		// プレイヤーを向く
		RotationPlayer();

		// 移動
		Move();

		break;

	case CEnemyExplosion::ACTION_COUNTDOWN:

		// プレイヤーを向く
		RotationPlayer();

		// 移動
		Move();

		// カウンターを加算
		m_fCountDawn += CManager::GetInstance()->GetDeltaTime();

		// 点滅
		Flash();

		break;

	case ACTION_EXPROSION:

		// プレイヤーを向く
		RotationPlayer();

		break;

	case CEnemyExplosion::ACTION_FADE:

		// 消えてくれ
		SetState(STATE_FADEOUT);

		break;

	default:
		break;
	}
}

//==========================================
//  移動
//==========================================
void CEnemyExplosion::Move(void)
{
	// 移動フラグを立てる
	m_sMotionFrag.bMove = true;

	// 角度の取得
	D3DXVECTOR3 rot = GetRotation();

	// 移動量を取得
	float fMove = GetVelocity();
	D3DXVECTOR3 move = GetMove();

	// 移動量に倍率をかける
	if (m_Act != CEnemyExplosion::ACTION_ROAMING)
	{
		fMove *= CHASE_SPEED;
	}

	// 移動量を分解する
	move.x = -sinf(rot.y) * fMove;
	move.z = -cosf(rot.y) * fMove;

	// 移動量を適用する
	SetMove(move);
}


//==========================================
//  ランダムな方向転換
//==========================================
void CEnemyExplosion::RandTurn(void)
{
	// カウンターの加算
	m_fCntWalk += CManager::GetInstance()->GetDeltaTime();

	// 時間内だったら関数を抜ける
	if (m_fCntWalk < WALK_TIME)
	{
		// 目標との差分
		D3DXVECTOR3 rot = GetRotation();
		float fRotDiff = m_fRot - rot.y;

		//角度の正規化
		RotNormalize(fRotDiff);

		//角度の補正をする
		rot.y += fRotDiff * TURN_SPEED;

		// 角度の正規化
		RotNormalize(rot.y);

		// 向き設定
		SetRotation(rot);

		return;
	}

	// 一定時間経過していた場合リセットする
	m_fCntWalk = 0.0f;

	// 移動方向を設定
	m_fRot = (float)(rand() % 624) * 0.01f - D3DX_PI;
}

//==========================================
//  描画処理
//==========================================
void CEnemyExplosion::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}

//==========================================
//  殺す
//==========================================
void CEnemyExplosion::Kill(void)
{
	// 死亡処理
	CEnemy::Kill();
}

//==========================================
//  モーションセット
//==========================================
void CEnemyExplosion::MotionSet(void)
{
	if (m_pMotion->IsFinish() == true)
	{// 終了していたら

		// 現在の種類取得
		int nType = m_pMotion->GetType();

		if (m_Act == ACTION_EXPROSION)
		{ // 爆発状態

			// 爆発モーション
			m_pMotion->Set(MOTION_ATK);
		}
		else if (m_sMotionFrag.bMove == true && m_sMotionFrag.bKnockback == false)
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
void CEnemyExplosion::ActionSet(void)
{
	// 消滅状態の場合は抜ける
	if (m_Act == ACTION_FADE)
	{
		return;
	}

	if (m_Act == ACTION_EXPROSION)
	{
		// 爆発モーションが終わったら消える
		if (m_pMotion->IsFinish())
		{
			m_Act = ACTION_FADE;
		}

		return;
	}

	// カウントダウン中は変わらない
	if (m_Act == ACTION_COUNTDOWN)
	{
		// カウントダウンが完了したら爆発
		if (m_fCountDawn >= COUNT_DAWN)
		{
			m_sMotionFrag.bMove = false;
			m_Act = ACTION_EXPROSION;
		}

		return;
	}

	if (CalcLenPlayer(EXPLOSION_LENGTH))
	{
		// 距離がとっても近いと爆発
		m_Act = ACTION_COUNTDOWN;
	}
	else if (CalcLenPlayer(SEARCH_LENGTH))
	{
		// 距離が近いと発見状態になる
		m_Act = ACTION_CHASE;
	}
	else // 上記以外なら待機状態
	{
		m_Act = ACTION_ROAMING;
	}
}

//==========================================
//  点滅
//==========================================
void CEnemyExplosion::Flash(void)
{
	// マテリアルカラーを更新
	m_mMatcol.g = cosf(m_fCol) * 0.5f + 0.5f;
	m_mMatcol.b = cosf(m_fCol) * 0.5f + 0.5f;

	// カウンタを追加
	m_fCol += CManager::GetInstance()->GetDeltaTime() * FLASH_SPEED;
}


//==========================================================================
// 攻撃時処理
//==========================================================================
void CEnemyExplosion::AttackAction(int nModelNum, CMotion::AttackInfo ATKInfo)
{
	// モーション情報取得
	int nMotionType = m_pMotion->GetType();
	D3DXVECTOR3 weponpos = m_pMotion->GetAttackPosition(GetModel(), ATKInfo);

	// 情報取得
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();

	// モーション別処理
	switch (nMotionType)
	{
	case MOTION_ATK:
		CExplosion::Create(CExplosion::TYPE_ENEMY, pos, 180.0f);
		// 振動
		CManager::GetInstance()->GetCamera()->SetShake(12, 20.0f, 0.0f);
		break;
	}
}

//==========================================================================
// 攻撃判定中処理
//==========================================================================
void CEnemyExplosion::AttackInDicision(CMotion::AttackInfo ATKInfo)
{
	// 基底の攻撃判定中処理
	CEnemy::AttackInDicision(ATKInfo);

	// モーション情報取得
	int nMotionType = m_pMotion->GetType();
	D3DXVECTOR3 weponpos = m_pMotion->GetAttackPosition(GetModel(), ATKInfo);

	// モーション別処理
	switch (nMotionType)
	{
	case MOTION_ATK:
		break;
	}
}