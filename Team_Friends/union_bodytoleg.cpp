//=============================================================================
// 
//  プレイヤー処理 [union_bodytoleg.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "union_bodytoleg.h"
#include "player_union.h"
#include "game.h"
#include "camera.h"
#include "manager.h"
#include "debugproc.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "enemy.h"
#include "calculation.h"
#include "model.h"
#include "motion.h"
#include "objectChara.h"
#include "shadow.h"
#include "particle.h"
#include "3D_Effect.h"
#include "impactwave.h"


//==========================================================================
// マクロ定義
//==========================================================================
#define CHARAFILE		"data\\TEXT\\motion_set_player.txt"
#define JUMP			(20.0f * 1.5f)	// ジャンプ力初期値
#define MAX_LIFE		(100)			// 体力
#define TARGET_LEN		(400.0f)		// 目標までの距離
#define WALK_INT		(30)			// 歩行の時間
#define INVINCIBLE_INT	(2)				// 無敵の間隔
#define INVINCIBLE_TIME	(90)			// 無敵の時間
#define CONFUSIONTIME	(60 * 2)		// 混乱時間
#define DEADTIME		(120)
#define FADEOUTTIME		(60)
#define RADIUS			(250.0f)

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================
const char *CUnion_BodytoLeg::m_apModelFile[mylib_const::MAX_PLAYER] =	// モデルのファイル
{
	"data\\TEXT\\player_union\\motion_body.txt",
	"data\\TEXT\\player_union\\motion_leg.txt",
};

//==========================================================================
// コンストラクタ
//==========================================================================
CUnion_BodytoLeg::CUnion_BodytoLeg(int nPriority) : CPlayerUnion(nPriority)
{
	
}

//==========================================================================
// デストラクタ
//==========================================================================
CUnion_BodytoLeg::~CUnion_BodytoLeg()
{

}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CUnion_BodytoLeg::Init(void)
{
	// 初期化
	CPlayerUnion::Init();

	// 種類の設定
	SetType(TYPE_PLAYER);

	m_state = STATE_NONE;	// 状態

	SetPosition(D3DXVECTOR3(-600.0f, 0.0f, -1000.0f));
	return S_OK;
}


//==========================================================================
// パーツの設定
//==========================================================================
HRESULT CUnion_BodytoLeg::CreateParts(void)
{
	HRESULT hr;
	CObjectChara *pObjChar = NULL;

	//**********************************
	// 胴体
	//**********************************
	m_pObjChara[PARTS_BODY] = CObjectChara::Create(m_apModelFile[PARTS_BODY]);
	if (m_pObjChara[PARTS_BODY] == NULL)
	{// 失敗していたら
		return E_FAIL;
	}

	// モーションの生成処理
	m_pMotion[PARTS_BODY] = CMotion::Create(m_apModelFile[PARTS_BODY]);

	// オブジェクトキャラクターの情報取得
	pObjChar = m_pObjChara[PARTS_BODY]->GetObjectChara();

	// モーションの設定
	m_pMotion[PARTS_BODY]->SetModel(pObjChar->GetModel(), pObjChar->GetNumModel(), pObjChar);

	// ポーズのリセット
	m_pMotion[PARTS_BODY]->ResetPose(MOTION_DEF);


	//**********************************
	// 脚
	//**********************************
	m_pObjChara[PARTS_LEG] = CObjectChara::Create(m_apModelFile[PARTS_LEG]);
	if (m_pObjChara[PARTS_LEG] == NULL)
	{// 失敗していたら
		return E_FAIL;
	}

	// モーションの生成処理
	m_pMotion[PARTS_LEG] = CMotion::Create(m_apModelFile[PARTS_LEG]);

	// オブジェクトキャラクターの情報取得
	pObjChar = m_pObjChara[PARTS_LEG]->GetObjectChara();

	// モーションの設定
	m_pMotion[PARTS_LEG]->SetModel(pObjChar->GetModel(), pObjChar->GetNumModel(), pObjChar);

	// ポーズのリセット
	m_pMotion[PARTS_LEG]->ResetPose(MOTION_DEF);


	// 左腕の原点を体にする
	m_pObjChara[PARTS_LEG]->GetModel()[0]->SetParent(m_pObjChara[PARTS_BODY]->GetModel()[0]);
	m_pObjChara[PARTS_LEG]->GetModel()[3]->SetParent(m_pObjChara[PARTS_BODY]->GetModel()[0]);
	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CUnion_BodytoLeg::Uninit(void)
{
	// 終了処理
	CPlayerUnion::Uninit();
}

//==========================================================================
// 更新処理
//==========================================================================
void CUnion_BodytoLeg::Update(void)
{
	CPlayerUnion::Update();
}

//==========================================================================
// パーツのコントロール処理
//==========================================================================
void CUnion_BodytoLeg::ControllParts(void)
{
	// 各部位の操作	
	for (int i = 0; i < PARTS_MAX; i++)
	{
		int nPartsIdx = CManager::GetInstance()->GetByPlayerPartsType(i);
		
		if (i == m_nControllMoveIdx)
		{
			// 脚移動操作
			ControllLeg(i);
		}
		ControllATK(i);
	}
}

//==========================================================================
// 脚操作
//==========================================================================
void CUnion_BodytoLeg::ControllLeg(int nIdx)
{
	// ゲームパッド情報取得
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	// カメラの情報取得
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	// カメラの向き取得
	D3DXVECTOR3 Camerarot = pCamera->GetRotation();

	// 移動量取得
	float fMove = 2.5f;

	int nLeftArmIdx = CManager::GetInstance()->GetByPlayerPartsType(PARTS_L_ARM);
	int nRightArmIdx = CManager::GetInstance()->GetByPlayerPartsType(PARTS_R_ARM);

	if (m_state != STATE_DEAD &&
		m_state != STATE_FADEOUT)
	{// 移動可能モーションの時

		// 移動操作
		if (ControllMove(nIdx))
		{
			// 移動中にする
			for (int i = 0; i < PARTS_MAX; i++)
			{
				m_sMotionFrag[i].bMove = true;

				if (m_nControllMoveIdx != i &&
					m_pMotion[i]->GetType() != MOTION_WALK &&
					m_pMotion[i]->GetType() != MOTION_DEF)
				{// 移動を担ってるパーツ以外 && 移動してない && 待機でもない
					m_sMotionFrag[i].bMove = false;
				}
			}
		}
		else
		{
			for (int i = 0; i < PARTS_MAX; i++)
			{
				m_sMotionFrag[i].bMove = false;
			}
		}


		// 移動量取得
		D3DXVECTOR3 move = GetMove();

		if (m_bJump == false &&
			pInputGamepad->GetTrigger(CInputGamepad::BUTTON_LB, nIdx))
		{//SPACEが押された,ジャンプ

			m_bJump = true;
			move.y += 17.0f;

			// ジャンプ中にする
			for (int i = 0; i < PARTS_MAX; i++)
			{
				m_sMotionFrag[i].bJump = true;
				if (m_sMotionFrag[nRightArmIdx].bCharge == true)
				{
					m_sMotionFrag[nRightArmIdx].bJump = false;
				}
				if (m_sMotionFrag[nLeftArmIdx].bCharge == true)
				{
					m_sMotionFrag[nLeftArmIdx].bJump = false;
				}
			}

			// サウンド再生
			CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_JUMP);
		}

		// 移動量設定
		SetMove(move);
	}

}

//==========================================================================
// 攻撃操作
//==========================================================================
void CUnion_BodytoLeg::ControllATK(int nIdx)
{
	// ゲームパッド情報取得
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();
	
	if ((pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, nIdx)))
	{// 攻撃

		// チャージ判定
		m_sMotionFrag[nIdx].bCharge = true;
	}

	if (m_sMotionFrag[nIdx].bCharge == true &&
		pInputGamepad->GetRelease(CInputGamepad::BUTTON_A, nIdx))
	{// チャージ中に攻撃ボタンを離したら

		// 攻撃中
		m_sMotionFrag[nIdx].bCharge = false;
		m_sMotionFrag[nIdx].bATK = true;
	}
}

//==========================================================================
// モーションの設定
//==========================================================================
void CUnion_BodytoLeg::MotionSet(int nIdx)
{
	if (m_pMotion[nIdx] == NULL)
	{// モーションがNULLだったら
		return;
	}

	if (m_pMotion[nIdx]->IsFinish() == true)
	{// 終了していたら

		// 現在の種類取得
		int nType = m_pMotion[nIdx]->GetType();
		int nOldType = m_pMotion[nIdx]->GetOldType();

		if (m_sMotionFrag[nIdx].bMove == true &&
			m_sMotionFrag[nIdx].bATK == false &&
			m_bKnockBack == false &&
			m_bDead == false &&
			m_sMotionFrag[nIdx].bCharge == false &&
			m_bJump == false)
		{// 移動していたら


			// 移動モーション
			m_pMotion[nIdx]->Set(MOTION_WALK);
		}
		else if (m_sMotionFrag[nIdx].bJump == true &&
			m_sMotionFrag[nIdx].bATK == false &&
			m_sMotionFrag[nIdx].bCharge == false &&
			m_bKnockBack == false &&
			m_bDead == false)
		{// ジャンプ中

			// ジャンプのフラグOFF
			m_sMotionFrag[nIdx].bJump = false;

			// ジャンプモーション
			m_pMotion[nIdx]->Set(MOTION_JUMP);
		}
		else if (m_bJump == true &&
			m_sMotionFrag[nIdx].bJump == false &&
			m_sMotionFrag[nIdx].bATK == false &&
			m_sMotionFrag[nIdx].bCharge == false &&
			m_bKnockBack == false &&
			m_bDead == false)
		{// ジャンプ中&&ジャンプモーションが終わってる時

			// 落下モーション
			m_pMotion[nIdx]->Set(MOTION_FALL);
		}
		else if (m_sMotionFrag[nIdx].bCharge == true)
		{// チャージ中だったら

			// チャージモーション
			m_pMotion[nIdx]->Set(MOTION_CHARGE);
		}
		else if (m_bKnockBack == true)
		{// やられ中だったら

			// やられモーション
			m_pMotion[nIdx]->Set(MOTION_KNOCKBACK);
		}
		else if (m_bDead == true)
		{// 死亡中だったら

			// やられモーション
			m_pMotion[nIdx]->Set(MOTION_DEAD);
		}
		else if (m_sMotionFrag[nIdx].bATK == true)
		{// 攻撃していたら

			m_sMotionFrag[nIdx].bATK = false;		// 攻撃判定OFF
			m_pMotion[nIdx]->Set(MOTION_ATK, true);
		}
		else
		{
			// ニュートラルモーション
			m_pMotion[nIdx]->Set(MOTION_DEF);
		}
	}
}

//==========================================================================
// 攻撃時処理
//==========================================================================
void CUnion_BodytoLeg::AttackAction(int nIdx, int nModelNum, CMotion::AttackInfo ATKInfo)
{

	// 武器の位置
	D3DXVECTOR3 weponpos = m_pMotion[nIdx]->GetAttackPosition(m_pObjChara[nIdx]->GetModel(), ATKInfo);

	// 種類別
	switch (m_pMotion[nIdx]->GetType())
	{
	case MOTION_ATK:
		
		break;
	}
}

//==========================================================================
// ヒット処理
//==========================================================================
bool CUnion_BodytoLeg::Hit(const int nValue)
{
	// 体力取得
	int nLife = 50;

	//if (nLife <= 0)
	//{
	//	// 死んだ
	//	return true;
	//}

	if (m_state != STATE_DMG && m_state != STATE_KNOCKBACK && m_state != STATE_INVINCIBLE && m_state != STATE_DEAD && m_state != STATE_FADEOUT)
	{// ダメージ受付状態の時

		// 体力減らす
		nLife -= nValue;


		// ゲームパッド情報取得
		CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();
		pInputGamepad->SetVibration(CInputGamepad::VIBRATION_STATE_DMG, 0);

		m_KnokBackMove.y += 18.0f;
		m_bHitStage = false;

		// 体力設定
		//SetLife(nLife);

		if (nLife <= 0)
		{// 体力がなくなったら

			// 死状態
			m_state = STATE_DEAD;

			m_KnokBackMove.y = 8.0f;

			// 遷移カウンター設定
			m_nCntState = DEADTIME;

			// 体力設定
			//SetLife(0);

			// ノックバック判定にする
			m_bKnockBack = true;

			// やられモーション
			m_pMotion[PARTS_BODY]->Set(MOTION_KNOCKBACK);

			// ノックバックの位置更新
			D3DXVECTOR3 pos = GetPosition();
			D3DXVECTOR3 rot = GetRotation();
			m_posKnokBack = pos;

			// 衝撃波生成
			CImpactWave::Create
			(
				D3DXVECTOR3(pos.x, pos.y + 80.0f, pos.z),	// 位置
				D3DXVECTOR3(D3DX_PI * 0.5f, D3DX_PI + rot.y, D3DX_PI),				// 向き
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f),			// 色
				80.0f,										// 幅
				80.0f,										// 高さ
				0.0f,										// 中心からの間隔
				20,											// 寿命
				10.0f,										// 幅の移動量
				CImpactWave::TYPE_GIZAWHITE,				// テクスチャタイプ
				false										// 加算合成するか
			);

			CManager::GetInstance()->SetEnableHitStop(18);

			// 振動
			CManager::GetInstance()->GetCamera()->SetShake(21, 30.0f, 0.0f);

			// 死んだ
			return true;
		}

		// 過去の状態保存
		m_Oldstate = m_state;

		// 色設定
		m_mMatcol = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		// ダメージ状態にする
		m_state = STATE_DMG;

		// 遷移カウンター設定
		m_nCntState = 0;

		// ノックバックの位置更新
		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 rot = GetRotation();
		m_posKnokBack = pos;

		// ノックバック判定にする
		m_bKnockBack = true;

		// やられモーション
		m_pMotion[PARTS_BODY]->Set(MOTION_KNOCKBACK);

		// 衝撃波生成
		CImpactWave::Create
		(
			D3DXVECTOR3(pos.x, pos.y + 80.0f, pos.z),	// 位置
			D3DXVECTOR3(D3DX_PI * 0.5f, D3DX_PI + rot.y, D3DX_PI),				// 向き
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f),			// 色
			80.0f,										// 幅
			80.0f,										// 高さ
			0.0f,										// 中心からの間隔
			20,											// 寿命
			10.0f,										// 幅の移動量
			CImpactWave::TYPE_GIZAWHITE,				// テクスチャタイプ
			false										// 加算合成するか
		);

		CManager::GetInstance()->SetEnableHitStop(12);

		// 振動
		CManager::GetInstance()->GetCamera()->SetShake(12, 25.0f, 0.0f);

		// サウンド再生
		CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_PLAYERDMG);
	}

	// 死んでない
	return false;
}

//==========================================================================
// 描画処理
//==========================================================================
void CUnion_BodytoLeg::Draw(void)
{
	// 描画処理
	CPlayerUnion::Draw();
}