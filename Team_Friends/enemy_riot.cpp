//==========================================
//
//  ギガントエッジ(enemy_riot.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_riot.h"
#include "player.h"
#include "manager.h"
#include "debugproc.h"
#include "calculation.h"
#include "hp_gauge.h"
#include "camera.h"
#include "particle.h"
#include "3D_Effect.h"
#include "impactwave.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const float ATTACK_LENGTH = 200.0f; // 攻撃する距離
	const float WAIT_TIMER = 2.0f; // 初期待機時間
	const float ROTATION_TIMER = 1.0f; // 軸合わせに要する時間
	const float TACKLE_TIMER = 1.0f; // 突進する時間
	const int MAX_ATTACK = 3; // 連続攻撃の最大数
}

//==========================================
//  コンストラクタ
//==========================================
CEnemyRiot::CEnemyRiot(int nPriority) :
	m_Act(ACTION_DEF),
	m_fWaitTime(0.0f),
	m_nCntAction(0)
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemyRiot::~CEnemyRiot()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemyRiot::Init(void)
{
	//初期化処理
	CEnemy::Init();

	// HPの設定
	m_pHPGauge = CHP_Gauge::Create(100.0f, GetLifeOrigin());

	// 出現待機状態にする
	m_state = STATE_SPAWNWAIT;
	m_Act = ACTION_SPAWN;

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CEnemyRiot::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemyRiot::Update(void)
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

	// スクリーン内の存在判定
	if (m_state == STATE_SPAWNWAIT && CManager::GetInstance()->GetCamera()->OnScreen(GetPosition()))
	{
		m_state = STATE_SPAWN;
	}
}

//==========================================
//  描画処理
//==========================================
void CEnemyRiot::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}

//==========================================
//  殺す
//==========================================
void CEnemyRiot::Kill(void)
{
	// 死亡処理
	CEnemy::Kill();
}

//==========================================
//  モーションセット
//==========================================
void CEnemyRiot::MotionSet(void)
{
	if (m_pMotion->IsFinish() == true)
	{// 終了していたら

		// 場合分け
		switch (m_Act)
		{
		case ACTION_DEF: // 待機行動
			m_pMotion->Set(MOTION_DEF); // 待機モーション
			break;

		case ACTION_MOVE: // 移動行動
			m_pMotion->Set(MOTION_WALK); // 移動モーション
			break;

		case ACTION_AXIS: // 軸合わせ行動
			m_pMotion->Set(MOTION_DEF); // 待機モーション
			break;

		case ACTION_TACKLE: // 突進行動
			m_pMotion->Set(MOTION_WALK); // 移動モーション
			break;

		case ACTION_ATTACK: // 攻撃行動
			m_pMotion->Set(MOTION_ATK); // 攻撃モーション
			break;
		}
	}
}

//==========================================
// スポーン
//==========================================
void CEnemyRiot::Spawn(void)
{
	// ��田くんへ、コピーしてね
	int nType = m_pMotion->GetType();
	if (nType == MOTION_SPAWN && m_pMotion->IsFinish() == true)
	{// 登場が終わってたら

		// なにもない
		m_state = STATE_NONE;
		m_Act = ACTION_DEF;
		return;
	}

	// モーションカウンター取得
	float fAllCount = m_pMotion->GetAllCount();
	if ((int)fAllCount % 10 == 0)
	{
		// 角度の取得
		D3DXVECTOR3 rot = GetRotation();

		// 衝撃波生成
		CImpactWave *pWave = CImpactWave::Create
		(
			GetCenterPosition(),	// 位置
			D3DXVECTOR3((float)Random(-31, 31) * 0.1f, D3DX_PI * 0.5f + rot.y, 0.0f),	// 向き
			D3DXCOLOR(0.9f, 0.2f, 0.9f, 0.8f),	// 色
			150.0f,								// 幅
			0.0f,								// 高さ
			90.0f,								// 中心からの間隔
			20,									// 寿命
			8.0f,								// 幅の移動量
			CImpactWave::TYPE_GIZAGRADATION,	// テクスチャタイプ
			true								// 加算合成するか
		);
	}

	if ((int)fAllCount % 12 == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			int repeat = (int)(fAllCount / 12.0f);
			CEffect3D::Create(
				GetCenterPosition(),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.9f, 0.2f, 0.9f, 1.0f),
				20.0f, 20, CEffect3D::MOVEEFFECT_ADD, CEffect3D::TYPE_NORMAL, repeat * 2.0f);
		}
	}

	// 登場演出
	my_particle::Create(GetCenterPosition(), my_particle::TYPE_UNDERBOSS_SPAWN);

	if (nType != MOTION_SPAWN)
	{
		// 登場モーション設定
		m_pMotion->Set(MOTION_SPAWN);
	}
}

//==========================================
//  行動セット
//==========================================
void CEnemyRiot::ActionSet(void)
{

	switch (m_Act)
	{
	case ACTION_ATTACK: // 攻撃状態

		if (m_pMotion->IsFinish())
		{
			//軸合わせに移行
			m_Act = ACTION_AXIS;
		}
		else
		{
			// 待機時間を加算
			m_fWaitTime += CManager::GetInstance()->GetDeltaTime();

			// 攻撃をする
			Attack();
		}

		break;

	case ACTION_TACKLE: // 突進状態

		if (m_fWaitTime >= TACKLE_TIMER)
		{
			// 待機時間をリセット
			m_fWaitTime = 0.0f;

			//軸合わせに移行
			m_Act = ACTION_AXIS;
		}
		else
		{
			// 待機時間を加算
			m_fWaitTime += CManager::GetInstance()->GetDeltaTime();

			// タックル
			Move();
		}

		break;

	case ACTION_AXIS: // 軸合わせ状態

		if (m_fWaitTime >= ROTATION_TIMER)
		{
			// 待機時間をリセット
			m_fWaitTime = 0.0f;

			// プレイヤーとの距離を計測
			if (CalcLenPlayer(ATTACK_LENGTH) && m_nCntAction <= MAX_ATTACK) // 近ければ攻撃
			{
				m_Act = ACTION_ATTACK;
				++m_nCntAction;
			}
			else // 遠かったらタックル
			{
				m_Act = ACTION_TACKLE;
				m_nCntAction = 0;
			}
		}
		else
		{
			// 待機時間を加算
			m_fWaitTime += CManager::GetInstance()->GetDeltaTime();

			// プレイヤーの方向を向く
			RotationPlayer();
		}

		break;

	case ACTION_DEF: // 初期待機状態

		if (m_fWaitTime >= WAIT_TIMER)
		{
			// 待機時間をリセット
			m_fWaitTime = 0.0f;

			//軸合わせに移行
			m_Act = ACTION_AXIS;
		}
		else
		{
			// 待機時間を加算
			m_fWaitTime += CManager::GetInstance()->GetDeltaTime();
		}

		break;

	default:
		break;
	}
}

//==========================================
//  移動
//==========================================
void CEnemyRiot::Move(void)
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
//  攻撃
//==========================================
void CEnemyRiot::Attack(void)
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
		return;
	}
}
