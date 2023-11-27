//==========================================
//
//  コピペ用の敵(enemy_test.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_test.h"
#include "player.h"
#include "manager.h"
#include "debugproc.h"
#include "calculation.h"

//==========================================
//  敵についての説明
//==========================================
/*
	※このファイルに記述されているコードは敵を動かす最低限です。消さないでください。※

	1.[ enemydata ]フォルダ内の[ manager.txt ]に使用したいモデルのテキストファイルを追加する
	2.[ enemy.h ]のTYPE列挙に新しいタイプを追加する
	3.[ enemydata ]フォルダ内の[ base.txt ]で追加したタイプを呼び出す
	4.実行したらいる！！！
*/

//==========================================
//  定数定義
//==========================================
namespace
{
	const float SEARCH_LENGTH = 500.0f;
	const float ATTACK_LENGTH = 50.0f;
	const float SPIN_ROTATION = 0.03f;
}

//==========================================
//  コンストラクタ
//==========================================
CEnemyTest::CEnemyTest(int nPriority) :
	m_Act(ACTION_DEF),
	m_posDefault(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemyTest::~CEnemyTest()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemyTest::Init(void)
{
	//初期化処理
	CEnemy::Init();

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CEnemyTest::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemyTest::Update(void)
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

	// 行動ごとの行動
	switch (m_Act)
	{
	case CEnemyTest::ACTION_RETURN:

		// 初期位置を向く
		RotationDefault();

		break;

	case CEnemyTest::ACTION_ATTACK:

		// プレイヤーを向く
		RotationPlayer();

		break;

	case CEnemyTest::ACTION_SEARCH:

		// くるくるする
		SpinRotation();

		break;

	case CEnemyTest::ACTION_CHASE:

		// プレイヤーを向く
		RotationPlayer();

		break;

	default:
		break;
	}

	// 行動状態の更新
	ActionSet();

	// モーションの更新
	MotionSet();
}

//==========================================
//  描画処理
//==========================================
void CEnemyTest::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}

//==========================================
//  殺す
//==========================================
void CEnemyTest::Kill(void)
{
	// 死亡処理
	CEnemy::Kill();
}

//==========================================
//  モーションセット
//==========================================
void CEnemyTest::MotionSet(void)
{
	if (m_pMotion->IsFinish() == true)
	{// 終了していたら

		// 現在の種類取得
		int nType = m_pMotion->GetType();

		if (m_sMotionFrag.bMove == true && m_sMotionFrag.bKnockback == false)
		{// 移動していたら

			m_sMotionFrag.bMove = false;	// 移動判定OFF

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
//  初期位置の設定
//==========================================
void CEnemyTest::SetDefaultPos(const D3DXVECTOR3 pos)
{
	//数値を設定
	m_posDefault = pos;
}

//==========================================
//  行動設定
//==========================================
void CEnemyTest::ActionSet(void)
{
	if (CalcLenPlayer(ATTACK_LENGTH))
	{
		// 攻撃フラグを立てる
		if (m_Act != ACTION_ATTACK)
		{
			m_sMotionFrag.bATK = true;
		}

		// 距離が近いと攻撃状態になる
		m_Act = ACTION_ATTACK;
	}
	else if (CalcLenPlayer(SEARCH_LENGTH))
	{
		// 距離が近いと追跡状態になる
		m_Act = ACTION_CHASE;
	}
	else if(CalcLenDefault())
	{
		// プレイヤーが近くにいなかったら元の位置に帰る
		m_Act = ACTION_RETURN;
	}
	else // 上記以外なら待機状態
	{
		m_Act = ACTION_DEF;
	}
}

//==========================================
//  その場で回転する処理
//==========================================
void CEnemyTest::SpinRotation(void)
{
	// 角度を取得
	D3DXVECTOR3 rot = GetRotation();

	// 目標との差分
	float fRotDiff = rot.y + SPIN_ROTATION;

	//角度の正規化
	RotNormalize(fRotDiff);

	//角度の補正をする
	rot.y += fRotDiff * 0.025f;

	// 角度の正規化
	RotNormalize(rot.y);

	// 向き設定
	SetRotation(rot);
}

//==========================================
//  初期位置を向く処理
//==========================================
void CEnemyTest::RotationDefault(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();

	// 目標の角度を求める
	float fRotDest = atan2f((pos.x - m_posDefault.x), (pos.z - m_posDefault.z));

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
//  初期位置に戻る処理
//==========================================
bool CEnemyTest::CalcLenDefault(void)
{
	// 二点間を繋ぐベクトルの算出
	D3DXVECTOR3 vecToPlayer = GetPosition() - m_posDefault;

	// ベクトルの大きさの2乗を算出
	float fLength = vecToPlayer.x * vecToPlayer.x + vecToPlayer.z * vecToPlayer.z;

	// 一定範囲内の判定
	if (SEARCH_LENGTH * SEARCH_LENGTH >= fLength)
	{
		return false;
	}

	return true;
}

//==========================================
//  プレイヤーを向く処理
//==========================================
void CEnemyTest::RotationPlayer(void)
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
bool CEnemyTest::CalcLenPlayer(float fLen)
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
