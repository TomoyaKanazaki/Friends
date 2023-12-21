//==========================================
//
//  メタルスライム(enemy_escape.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_escape.h"
#include "player.h"
#include "manager.h"
#include "debugproc.h"
#include "calculation.h"
#include "hp_gauge.h"
#include "model.h"
#include "game.h"
#include "tutorial.h"
#include "tutorialmanager.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const float SEARCH_LENGTH = 400.0f;
	const float TURN_SPEED = 0.05f;
	const float ESCAPE_SPEED = 4.00f;
	const float WALK_TIME = 1.0f;
	const float FIND_TIME = 0.5f;
	const float TURN_TIME = 0.5f;
	const float ESCAPE_TIME = 3.0f;
}

//==========================================
//  コンストラクタ
//==========================================
CEnemyEscape::CEnemyEscape(int nPriority) :
	m_Act(ACTION_ROAMING),
	m_fCntWalk(0.0f),
	m_fCntFind(0.0f),
	m_fCntEscape(0.0f),
	m_fRot(0.0f)
{
	m_rotParts = mylib_const::DEFAULT_VECTOR3;	// パーツ回転用
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

	if (CManager::GetInstance()->GetScene()->GetMode() == CScene::MODE_TUTORIAL)
	{
		if (!CTutorial::GetTutorialManager()->IsControll())
		{// 行動できるとき
			return;
		}
	}
	else
	{
		if (!CGame::GetGameManager()->IsControll())
		{// 行動できるとき
			return;
		}
	}

	// モーションの情報取得
	CMotion::Info aInfo = m_pMotion->GetInfo(MOTION_DEF);

	// 攻撃情報の総数取得
	int nNumAttackInfo = aInfo.nNumAttackInfo;

	// 回転
	m_rotParts.y += D3DX_PI * 0.2f;
	RotNormalize(m_rotParts.y);

	for (int nCntAttack = 0; nCntAttack < nNumAttackInfo; nCntAttack++)
	{
		CModel *pModel = GetModel()[aInfo.AttackInfo[nCntAttack]->nCollisionNum];
		if (pModel == NULL)
		{
			continue;
		}

		// モーションデータ取得
		CMotion::Info info = m_pMotion->GetInfo(m_pMotion->GetType());

		D3DXVECTOR3 rot = pModel->GetRotation();
		rot.y = m_rotParts.y;
		pModel->SetRotation(rot);
	}
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

		RandTurn();
		// 移動
		Move();

		break;

	case CEnemyEscape::ACTION_FIND:

		// プレイヤーを向く
		RotationPlayer();

		// カウンターを加算
		m_fCntFind += CManager::GetInstance()->GetDeltaTime();

		break;

	case CEnemyEscape::ACTION_TURN:

		// プレイヤーじゃない方を向く
		Turn();

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
//  移動
//==========================================
void CEnemyEscape::Move(void)
{
	// 角度の取得
	D3DXVECTOR3 rot = GetRotation();

	// 移動量を取得
	float fMove = GetVelocity();
	D3DXVECTOR3 move = GetMove();

	// 移動量を分解する
	move.x = -sinf(rot.y) * fMove * CManager::GetInstance()->GetDeltaTime();
	move.z = -cosf(rot.y) * fMove * CManager::GetInstance()->GetDeltaTime();

	// 移動量を適用する
	SetMove(move);
}

//==========================================
//  プレイヤーを向く
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
	rot.y += fRotDiff * TURN_TIME;

	// 角度の正規化
	RotNormalize(rot.y);

	// 向き設定
	SetRotation(rot);

	// 目標の向き設定
	SetRotDest(fRotDest);
}

//==========================================
//  ランダムな方向転換
//==========================================
void CEnemyEscape::RandTurn(void)
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
//  向き直る行動
//=~========================================
void CEnemyEscape::Turn(void)
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

	// 逆方向に補正する
	fRotDest += D3DX_PI;

	// 角度の補正
	RotNormalize(fRotDest);

	// 目標との差分
	float fRotDiff = fRotDest - rot.y;

	//角度の正規化
	RotNormalize(fRotDiff);

	//角度の補正をする
	rot.y += fRotDiff * TURN_SPEED;

	// 角度の正規化
	RotNormalize(rot.y);

	// 向き設定
	SetRotation(rot);

	// 目標の向き設定
	SetRotDest(fRotDest);
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

	// 発見状態から向き直る状態へ移行する
	if (m_Act == ACTION_FIND)
	{
		if (m_fCntFind >= FIND_TIME)
		{
			m_fCntFind = 0.0f;
			m_Act = ACTION_TURN;
		}
		return;
	}

	// 向き直る状態から逃走状態へ移行する
	if (m_Act == ACTION_TURN)
	{
		if (m_fCntFind >= TURN_TIME)
		{
			m_fCntFind = 0.0f;
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
//  逃走
//==========================================
void CEnemyEscape::Escape(void)
{
	// 向き直る
	Turn();

	// 移動量を設定
	Move();

	// 移動量に倍率をかける
	SetMove(GetMove() * ESCAPE_SPEED);
}
