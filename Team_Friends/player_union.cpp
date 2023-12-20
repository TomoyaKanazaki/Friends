//=============================================================================
// 
//  合体プレイヤー処理 [player_union.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "game.h"
#include "player_union.h"
#include "camera.h"
#include "manager.h"
#include "debugproc.h"
#include "renderer.h"
#include "input.h"
#include "enemy.h"
#include "calculation.h"
#include "score.h"
#include "texture.h"
#include "Xload.h"
#include "model.h"
#include "motion.h"
#include "hp_gauge.h"
#include "objectChara.h"
#include "elevation.h"
#include "shadow.h"
#include "particle.h"
#include "3D_Effect.h"
#include "ballast.h"
#include "impactwave.h"
#include "sound.h"
#include "enemymanager.h"
#include "bullet.h"
#include "stage.h"
#include "objectX.h"
#include "gamemanager.h"
#include "instantfade.h"
#include "hp_gauge_player.h"
#include "fade.h"
#include "listmanager.h"
#include "item.h"
#include "injectiontable.h"
#include "enemy_boss.h"
#include "beam.h"
#include "unioncore.h"
#include "ultwindow.h"
#include "object_circlegauge2D.h"

// 派生先
#include "union_bodytoleg.h"
#include "union_bodytoarm.h"
#include "union_armtoarm.h"
#include "union_legtoarm.h"

//==========================================================================
// 定数定義
//==========================================================================
namespace
{
	char* TEXTURE_INITPLAYER[mylib_const::MAX_PLAYER][mylib_const::MAX_PLAYER] =	// 初期プレイヤーのテクスチャ
	{
		{// 胴
			"data\\TEXTURE\\union\\SuperUnion\\Head\\union_head_UV_Red.jpg",
			"data\\TEXTURE\\union\\SuperUnion\\Head\\union_head_UV_Blue.jpg",
			"data\\TEXTURE\\union\\SuperUnion\\Head\\union_head_UV_Green.jpg",
			"data\\TEXTURE\\union\\SuperUnion\\Head\\union_head_UV_Yellow.jpg",
		},
		{// 脚
			"data\\TEXTURE\\union\\SuperUnion\\Feet\\union_feet_UV_Red.jpg",
			"data\\TEXTURE\\union\\SuperUnion\\Feet\\union_feet_UV_Blue.jpg",
			"data\\TEXTURE\\union\\SuperUnion\\Feet\\union_feet_UV_Green.jpg",
			"data\\TEXTURE\\union\\SuperUnion\\Feet\\union_feet_UV_Yellow.jpg",
		},
		{// 腕
			"data\\TEXTURE\\union\\SuperUnion\\Arm\\union_arm_UV_Red.jpg",
			"data\\TEXTURE\\union\\SuperUnion\\Arm\\union_arm_UV_Blue.jpg",
			"data\\TEXTURE\\union\\SuperUnion\\Arm\\union_arm_UV_Green.jpg",
			"data\\TEXTURE\\union\\SuperUnion\\Arm\\union_arm_UV_Yellow.jpg",
		},
		{// 腕
			"data\\TEXTURE\\union\\SuperUnion\\Arm\\union_arm_UV_Red.jpg",
			"data\\TEXTURE\\union\\SuperUnion\\Arm\\union_arm_UV_Blue.jpg",
			"data\\TEXTURE\\union\\SuperUnion\\Arm\\union_arm_UV_Green.jpg",
			"data\\TEXTURE\\union\\SuperUnion\\Arm\\union_arm_UV_Yellow.jpg",
		}
	};
	const float MAX_ULTGAUGEVALUE = 200.0f;	// 必殺ゲージの最大量
	const float ADD_AUTO_ULTGAUGEVALUE = 0.1f;	// 必殺ゲージの自動加算量
	const float COOLTIME_BOOST = 120.0f;	// ブーストのクールタイム
	const float TIME_BOOST = 20.0f;	// ブーストのタイム
}
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
bool CPlayerUnion::m_bAllLandInjectionTable = false;	// 全員の射出台着地判定
bool CPlayerUnion::m_bLandInjectionTable[mylib_const::MAX_PLAYER] = {};	// 射出台の着地判定


//==========================================================================
// 関数ポインタ
//==========================================================================
CPlayerUnion::ULT_FUNC CPlayerUnion::m_UltFuncList[] =
{
	&CPlayerUnion::UltBeam,		// ビーム
	&CPlayerUnion::UltBigPunch,	// デカパンチ
	&CPlayerUnion::UltRiderKick,	// ライダーキック
};

//==========================================================================
// コンストラクタ
//==========================================================================
CPlayerUnion::CPlayerUnion(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	// 共有変数
	m_bJump = false;			// ジャンプ中かどうか
	m_bLandOld = false;			// 過去の着地情報
	m_bHitStage = false;		// ステージの当たり判定
	m_bLandField = false;		// フィールドの着地判定
	m_bHitWall = false;			// 壁の当たり判定
	m_bKnockBack = false;		// ノックバック中かどうか
	m_bDead = false;			// 死亡中かどうか
	m_nUnionLife = 0;			// 合体時間
	m_nCntWalk = 0;				// 歩行カウンター
	m_nCntInputAtk = 0;			// 攻撃の入力カウンター
	m_state = STATE_NONE;		// 状態
	memset(&m_pMotion[0], NULL, sizeof(m_pMotion));	// パーツ分のモーションポインタ
	memset(&m_sMotionFrag[0], false, sizeof(m_sMotionFrag));	// モーションのフラグ

	// プライベート変数
	memset(&m_pObjChara[0], NULL, sizeof(m_pObjChara));	// パーツ分のオブジェクトキャラクターポインタ

	m_Oldstate = STATE_NONE;			// 前回の状態
	m_mMatcol = mylib_const::DEFAULT_COLOR;		// マテリアルの色
	m_posKnokBack = mylib_const::DEFAULT_VECTOR3;	// ノックバックの位置
	m_KnokBackMove = mylib_const::DEFAULT_VECTOR3;	// ノックバックの移動量
	m_nCntState = 0;			// 状態遷移カウンター
	m_nTexIdx = 0;				// テクスチャのインデックス番号
	m_nIdxXFile = 0;			// Xファイルのインデックス番号
	memset(&m_nPartsIdx[0], 0, sizeof(m_nPartsIdx));	// プレイヤー毎のパーツインデックス番号
	m_nMyPlayerIdx = 0;			// プレイヤーインデックス番号
	m_nControllMoveIdx = 0;		// 移動操作するやつのインデックス番号
	m_fRotDest = 0.0f;
	m_pShadow = NULL;			// 影の情報
	m_pTargetP = NULL;			// 目標の地点
	m_pHPGauge = NULL;			// HPゲージの情報
	m_pUnionCore = NULL;		// 合体後コア
	m_UltType = ULT_BEAM;		// 必殺技の種類
	m_UltBranch = ULTBRANCH_CHARGE_BEAM;	// 必殺技の分岐
	m_bUltBigArm = false;		// ウルトで腕デカくしたか
	memset(&m_fUltGaugeValue[0], 0, sizeof(m_fUltGaugeValue));	// 必殺ゲージの量
	m_fCooltimeBoost = 0.0f;	// ブーストのクールタイム
	m_fBoostTime = 0.0f;	// ブーストのタイム

	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		m_nModelIdx[i].clear();	// 各パーツごとのモデルインデックス番号
	}

	memset(&m_apModel[0], NULL, sizeof(m_apModel));	// モデル(パーツ)のポインタ
}

//==========================================================================
// デストラクタ
//==========================================================================
CPlayerUnion::~CPlayerUnion()
{

}

//==========================================================================
// 生成処理
//==========================================================================
CPlayerUnion *CPlayerUnion::Create(eType type)
{
	// 生成用のオブジェクト
	CPlayerUnion *pPlayer = NULL;

	if (pPlayer == NULL)
	{// NULLだったら

		// メモリの確保
		switch (type)
		{
		case TYPE_ALL:
			pPlayer = DEBUG_NEW CPlayerUnion;
			break;

		case TYPE_BODYtoLEG:
			pPlayer = DEBUG_NEW CUnion_BodytoLeg;
			break;

		case TYPE_BODYtoARM:
			pPlayer = DEBUG_NEW CUnion_BodytoArm;
			break;

		case TYPE_LEGtoARM:
			pPlayer = DEBUG_NEW CUnion_LegtoArm;
			break;

		case TYPE_ARMtoARM:
			pPlayer = DEBUG_NEW CUnion_ArntoArm;
			break;

		default:
			return NULL;
			break;
		}

		if (pPlayer != NULL)
		{// メモリの確保が出来ていたら

			// プレイヤーインデックス番号
			//pPlayer->m_nMyPlayerIdx = nIdx;

			// 初期化処理
			pPlayer->Init();
		}

		return pPlayer;
	}

	return NULL;
}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CPlayerUnion::Init(void)
{
	// 種類の設定
	SetType(TYPE_PLAYER);

	m_state = STATE_APPEARANCE;	// 状態
	m_nCntState = 0;		// 状態遷移カウンター
	m_bLandOld = true;		// 前回の着地状態
	m_bAllLandInjectionTable = false;	// 全員の射出台着地判定
	memset(&m_bLandInjectionTable[0], false, sizeof(m_bLandInjectionTable));	// 射出台の着地判定
	m_nUnionLife = 0;		// 合体時間

	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		m_nPartsIdx[i] = -1;
	}

	// キャラ作成
	CreateParts();

	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// 体力ゲージ
	//m_pHPGauge = CHP_GaugePlayer::Create(D3DXVECTOR3(250.0f, 600.0f, 0.0f), 50);

	// 影の生成
	m_pShadow = CShadow::Create(pos, 50.0f);

	SetPosition(D3DXVECTOR3(-600.0f, 500.0f, 0.0f));

	return S_OK;
}

//==========================================================================
// パーツの設定
//==========================================================================
HRESULT CPlayerUnion::CreateParts(void)
{
	// 複数キャラ読み込み
	ReadMultiCharacter("data\\TEXT\\multicharacter\\SuperUnion.txt");

	// プレイヤーインデックス毎のテクスチャ設定
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		BindByPlayerIdxTexture(i, CManager::GetInstance()->GetByPlayerPartsType(i));
	}
	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CPlayerUnion::Uninit(void)
{
	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pMotion[i] != NULL)
		{
			m_pMotion[i]->Uninit();
			delete m_pMotion[i];
			m_pMotion[i] = NULL;
		}
	}

	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pObjChara[i] != NULL)
		{
			m_pObjChara[i] = NULL;
		}
	}

	// HPゲージを消す
	if (m_pHPGauge != NULL)
	{
		m_pHPGauge->Uninit();
		m_pHPGauge = NULL;
	}

	// 影を消す
	if (m_pShadow != NULL)
	{
		//m_pShadow->Uninit();
		m_pShadow = NULL;
	}

	// 終了処理
	CObject::Release();

	// モード別終了処理
	UninitByMode();
}

//==========================================================================
// モード別終了処理
//==========================================================================
void  CPlayerUnion::UninitByMode(void)
{
	//CScene *pScene = CManager::GetInstance()->GetScene();
	//if (pScene != NULL)
	//{
	//	// プレイヤーをNULL
	//	CManager::GetInstance()->GetScene()->UninitPlayer(m_nMyPlayerIdx);
	//}
}

//==========================================================================
// 終了処理
//==========================================================================
void CPlayerUnion::Kill(void)
{

	my_particle::Create(GetPosition(), my_particle::TYPE_ENEMY_FADE);

	// HPゲージを消す
	if (m_pHPGauge != NULL)
	{
		m_pHPGauge->Kill();
		m_pHPGauge = NULL;
	}

	// 影を消す
	if (m_pShadow != NULL)
	{
		m_pShadow->Uninit();
		m_pShadow = NULL;
	}

	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pObjChara[i] != NULL)
		{
			m_pObjChara[i]->Uninit();
			m_pObjChara[i] = NULL;
		}
	}
}

//==========================================================================
// 更新処理
//==========================================================================
void CPlayerUnion::Update(void)
{
	if (IsDeath() == true)
	{
		return;
	}

	// キーボード情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	if (pInputKeyboard->GetTrigger(DIK_F5) == true)
	{// F5でリセット
		SetPosition(D3DXVECTOR3(0.0f, 0.0f, -1000.0f));
		SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	// エディット中は抜ける
	if (CGame::GetElevation()->IsEdit())
	{
		return;
	}

	// エディット中は抜ける
	if (CGame::GetEditType() != CGame::EDITTYPE_OFF)
	{
		return;
	}

	// コンボ演出中は抜ける
	if (CManager::GetInstance()->GetScene()->GetMode() != CScene::MODE_RANKING)
	{
		if (CGame::GetEnemyManager()->GetState() == CEnemyManager::STATE_COMBOANIM)
		{
			return;
		}
	}

	// 過去の位置保存
	SetOldPosition(GetPosition());

	// 操作
	if (CManager::GetInstance()->GetScene()->GetMode() != CScene::MODE_RANKING)
	{
		Controll();
	}

	for (int i = 0; i < PARTS_MAX; i++)
	{
		// モーションの設定処理
		MotionSet(i);
	}

	// モーション更新
	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pMotion[i] == NULL)
		{
			continue;
		}
		D3DXVECTOR3 pos = m_pObjChara[i]->GetPosition();

		// モーション更新
		m_pMotion[i]->Update();

		// 差分
		D3DXVECTOR3 posDiff = m_pObjChara[i]->GetPosition() - pos;
		SetPosition(GetPosition() + posDiff);

		// 攻撃処理
		Atack(i);
	}

	// 状態更新
	UpdateState();


	// ブーストのクールタイム
	m_fCooltimeBoost -= 1.0f;
	ValueNormalize(m_fCooltimeBoost, COOLTIME_BOOST, 0.0f);

	// ブーストのタイム
	m_fBoostTime -= 1.0f;
	ValueNormalize(m_fBoostTime, TIME_BOOST, 0.0f);

	// 自動加算量分加算
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		m_fUltGaugeValue[i] += ADD_AUTO_ULTGAUGEVALUE;
		ValueNormalize(m_fUltGaugeValue[i], MAX_ULTGAUGEVALUE, 0.0f);

		// ステータスウィンドウ
		CUltWindow *pUltWindow = CGame::GetUltWindow(i);
		if (pUltWindow != NULL)
		{
			// ゲージの割合更新
			pUltWindow->GetGauge()->SetRateDest(m_fUltGaugeValue[i] / MAX_ULTGAUGEVALUE);
		}
	}


	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	if (CGame::GetEnemyManager() != NULL && CGame::GetEnemyManager()->GetBoss() != NULL)
	{
		CEnemyBoss *pEnemyBoss = CGame::GetEnemyManager()->GetBoss();
		if (pEnemyBoss != NULL)
		{
			pEnemyBoss->SetTargetPosition(pos);
		}
	}

	// 移動量取得
	D3DXVECTOR3 move = GetMove();

	// 向き取得
	D3DXVECTOR3 rot = GetRotation();

	// 位置・向き設定
	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pObjChara[i] == NULL)
		{
			continue;
		}

		m_pObjChara[i]->SetPosition(pos);
		m_pObjChara[i]->SetRotation(rot);
	}

	// 影の位置更新
	if (m_pShadow != NULL)
	{
		m_pShadow->SetPosition(D3DXVECTOR3(pos.x, m_pShadow->GetPosition().y, pos.z));
	}

	// HPゲージの位置更新
	if (m_pHPGauge != NULL)
	{
		m_pHPGauge->Update();
		m_pHPGauge->SetLife(50);
	}

}

//==========================================================================
// 操作処理
//==========================================================================
void CPlayerUnion::Controll(void)
{

	// キーボード情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// ゲームパッド情報取得
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	// 位置取得
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 newPosition = GetPosition();
	D3DXVECTOR3 sakiPos = GetPosition();

	// 向き取得
	D3DXVECTOR3 rot = GetRotation();

	// 経過時間取得
	float fCurrentTime = CManager::GetInstance()->GetDeltaTime();

	if (CGame::GetGameManager()->IsControll())
	{// 行動できるとき

		// パーツのコントロール処理
		ControllParts();
	}

#if _DEBUG

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		m_state = STATE_ULT;	// 状態
		m_UltType = ULT_BIGPUNCH;
		m_UltBranch = ULTBRANCH_CHARGE_BIGPUNCH;
	}
#endif

	// 移動量取得
	D3DXVECTOR3 move = GetMove();

	// 移動量加算
	newPosition.x += move.x;
	newPosition.z += move.z;

	sakiPos.x = newPosition.x + sinf(D3DX_PI + rot.y) * RADIUS;
	sakiPos.z = newPosition.z + cosf(D3DX_PI + rot.y) * RADIUS;

	// 角度の正規化
	RotNormalize(m_fRotDest);

	// 現在と目標の差分を求める
	float fRotDiff = m_fRotDest - rot.y;

	// 角度の正規化
	RotNormalize(fRotDiff);

	// 角度の補正をする
	rot.y += fRotDiff * 0.15f;

	// 角度の正規化
	RotNormalize(rot.y);

	// 重力処理
	if (m_state != STATE_KNOCKBACK && m_state != STATE_DMG && m_state != STATE_DEAD && m_state != STATE_FADEOUT)
	{
		move.y -= mylib_const::GRAVITY;

		// 位置更新
		newPosition.y += move.y;
		sakiPos.y = newPosition.y;
	}

	// 射出台の着地判定
	m_bLandInjectionTable[m_nMyPlayerIdx] = false;

	//**********************************
	// 当たり判定
	//**********************************
	bool bLandStage = Collision(sakiPos, move);

	bool bMove = false;
	if (m_bLandOld == false && bLandStage == true)
	{// 前回は着地していなくて、今回は着地している場合

		bMove = false;
	}

	if (m_bLandOld == true && bLandStage == true)
	{// 前回も今回も着地している場合
		bMove = true;
	}

	if (m_bHitWall == false && 
		(bLandStage == false || bMove == true || m_bLandField == true || m_bJump == true || m_bKnockBack == true || m_bDead == true))
	{
		pos.x = newPosition.x;
		pos.z = newPosition.z;
		pos.y = sakiPos.y;
		Collision(pos, move);

		// 前回は乗ってたことにする
		m_bLandOld = true;
	}
	else
	{
		D3DXVECTOR3 posOld = GetOldPosition();
		pos.x = posOld.x;
		pos.z = posOld.z;
		pos = posOld;
		move.x = 0.0f;
		pos.y -= mylib_const::GRAVITY * 7.0f;

		if (m_bJump == false)
		{
			m_bJump = true;
		}

		Collision(pos, move);
	}

	// 位置更新
	//pos.y += move.y;

	// 慣性補正
	if (m_state != STATE_KNOCKBACK && m_state != STATE_DMG && m_state != STATE_DEAD && m_state != STATE_FADEOUT)
	{
		move.x += (0.0f - move.x) * 0.25f;
		move.z += (0.0f - move.z) * 0.25f;
	}

	// 位置設定
	SetPosition(pos);

	// 移動量設定
	SetMove(move);

	// 向き設定
	SetRotation(rot);


	// カメラの情報取得
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	D3DXVECTOR3 TargetPos = pos;
	TargetPos.y += 300.0f;
	pCamera->SetTargetPosition(TargetPos);
	pCamera->SetTargetRotation(rot);

	// 目標の向き設定
	//SetRotDest(m_fRotDest);

}

//==========================================================================
// パーツのコントロール処理(バーチャル)
//==========================================================================
void CPlayerUnion::ControllParts(void)
{
	// 各部位の操作	
	for (int i = 0; i < PARTS_MAX; i++)
	{
		int nPartsIdx = CManager::GetInstance()->GetByPlayerPartsType(i);
		switch (nPartsIdx)
		{
		case PARTS_BODY:
			ControllBody(nPartsIdx, i);
			break;

		case PARTS_LEG:
			ControllLeg(nPartsIdx, i);
			break;

		case PARTS_L_ARM:
			ControllLeftArm(nPartsIdx, i);
			break;

		case PARTS_R_ARM:
			ControllRightArm(nPartsIdx, i);
			break;
		}
	}
}

//==========================================================================
// 胴操作
//==========================================================================
void CPlayerUnion::ControllBody(int nIdx, int nLoop)
{
	// ゲームパッド情報取得
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

}

//==========================================================================
// 脚操作
//==========================================================================
void CPlayerUnion::ControllLeg(int nIdx, int nLoop)
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

	if (m_state == STATE_DEAD ||
		m_state == STATE_FADEOUT)
	{
		return;
	}

	if (CGame::GetGameManager()->IsControll() &&
		m_pMotion[nIdx]->IsGetMove(m_pMotion[nIdx]->GetType()))
	{// 行動できるとき

		// 移動操作
		if (ControllMove(nLoop))
		{
			// 移動中にする
			for (int i = 0; i < PARTS_MAX; i++)
			{
				m_sMotionFrag[i].bMove = true;
				if (m_sMotionFrag[nRightArmIdx].bCharge == true)
				{
					m_sMotionFrag[nRightArmIdx].bMove = false;
				}
				if (m_sMotionFrag[nLeftArmIdx].bCharge == true)
				{
					m_sMotionFrag[nLeftArmIdx].bMove = false;
				}

				if (m_fBoostTime > 0.0f)
				{
					m_pMotion[i]->Set(MOTION_BOOST);
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

		// ジャンプ
#if 0
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
#endif

		// 移動量設定
		SetMove(move);
	}
	
	if ((pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, nLoop)))
	{// 攻撃

		// チャージ判定
		m_sMotionFrag[nIdx].bCharge = true;

		for (int i = 0; i < PARTS_MAX; i++)
		{
			m_sMotionFrag[i].bMove = false;
		}
	}

	if (m_sMotionFrag[nIdx].bCharge == true &&
		pInputGamepad->GetRelease(CInputGamepad::BUTTON_A, nLoop))
	{// チャージ中に攻撃ボタンを離したら

		// 攻撃中
		m_sMotionFrag[nIdx].bCharge = false;
		m_sMotionFrag[nIdx].bATK = true;

		for (int i = 0; i < PARTS_MAX; i++)
		{
			m_sMotionFrag[i].bMove = false;
		}
		m_pMotion[nIdx]->Set(MOTION_NORMAL_ATK);
	}
}

//==========================================================================
// 右腕操作
//==========================================================================
void CPlayerUnion::ControllRightArm(int nIdx, int nLoop)
{
	// ゲームパッド情報取得
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();
	
	if ((pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, nLoop)))
	{// 攻撃

		// チャージ判定
		m_sMotionFrag[nIdx].bCharge = true;
	}

	if (m_sMotionFrag[nIdx].bCharge == true &&
		pInputGamepad->GetRelease(CInputGamepad::BUTTON_A, nLoop))
	{// チャージ中に攻撃ボタンを離したら

		// 攻撃中
		m_sMotionFrag[nIdx].bCharge = false;
		m_sMotionFrag[nIdx].bATK = true;
		m_pMotion[nIdx]->Set(MOTION_NORMAL_ATK);
	}
}

//==========================================================================
// 左腕操作
//==========================================================================
void CPlayerUnion::ControllLeftArm(int nIdx, int nLoop)
{
	// ゲームパッド情報取得
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();
	
	if ((pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, nLoop)))
	{// 攻撃

		// チャージ判定
		m_sMotionFrag[nIdx].bCharge = true;
	}

	if (m_sMotionFrag[nIdx].bCharge == true &&
		pInputGamepad->GetRelease(CInputGamepad::BUTTON_A, nLoop))
	{// チャージ中に攻撃ボタンを離したら

		// 攻撃中
		m_sMotionFrag[nIdx].bCharge = false;
		m_sMotionFrag[nIdx].bATK = true;
		m_pMotion[nIdx]->Set(MOTION_NORMAL_ATK);
	}
}

//==========================================================================
// 移動操作
//==========================================================================
bool CPlayerUnion::ControllMove(int nIdx)
{

	// キーボード情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// ゲームパッド情報取得
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	// 移動量取得
	D3DXVECTOR3 move = GetMove();

	// カメラの情報取得
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	// カメラの向き取得
	D3DXVECTOR3 Camerarot = pCamera->GetRotation();

	// 移動量取得
	float fMove = 0.5f;

	bool bMove = true;

	if (m_fCooltimeBoost <= 0.0f &&
		m_fBoostTime <= 0.0f &&
		(pInputKeyboard->GetPress(DIK_SPACE) == true || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_B, nIdx)))
	{
		m_fCooltimeBoost = COOLTIME_BOOST;
		m_fBoostTime = TIME_BOOST;
		m_pMotion[nIdx]->Set(MOTION_BOOST);
	}

	if (m_fBoostTime > 0.0f)
	{
		fMove *= 15.0f;
		m_pMotion[nIdx]->Set(MOTION_BOOST);
	}

	if (pInputKeyboard->GetPress(DIK_A) == true || pInputGamepad->GetStickMoveL(nIdx).x < 0)
	{//←キーが押された,左移動

		if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(nIdx).y > 0)
		{//A+W,左上移動

			move.x += sinf(-D3DX_PI * 0.25f + Camerarot.y) * fMove;
			move.z += cosf(-D3DX_PI * 0.25f + Camerarot.y) * fMove;
			m_fRotDest = D3DX_PI * 0.75f + Camerarot.y;
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(nIdx).y < 0)
		{//A+S,左下移動

			move.x += sinf(-D3DX_PI * 0.75f + Camerarot.y) * fMove;
			move.z += cosf(-D3DX_PI * 0.75f + Camerarot.y) * fMove;
			m_fRotDest = D3DX_PI * 0.25f + Camerarot.y;
		}
		else
		{//A,左移動

			move.x += sinf(-D3DX_PI * 0.5f + Camerarot.y) * fMove;
			move.z += cosf(-D3DX_PI * 0.5f + Camerarot.y) * fMove;
			m_fRotDest = D3DX_PI * 0.5f + Camerarot.y;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true || pInputGamepad->GetStickMoveL(nIdx).x > 0)
	{//Dキーが押された,右移動

		if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(nIdx).y > 0)
		{//D+W,右上移動

			move.x += sinf(D3DX_PI * 0.25f + Camerarot.y) * fMove;
			move.z += cosf(D3DX_PI * 0.25f + Camerarot.y) * fMove;
			m_fRotDest = -D3DX_PI * 0.75f + Camerarot.y;
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(nIdx).y < 0)
		{//D+S,右下移動

			move.x += sinf(D3DX_PI * 0.75f + Camerarot.y) * fMove;
			move.z += cosf(D3DX_PI * 0.75f + Camerarot.y) * fMove;
			m_fRotDest = -D3DX_PI * 0.25f + Camerarot.y;
		}
		else
		{//D,右移動

			move.x += sinf(D3DX_PI * 0.5f + Camerarot.y) * fMove;
			move.z += cosf(D3DX_PI * 0.5f + Camerarot.y) * fMove;
			m_fRotDest = -D3DX_PI * 0.5f + Camerarot.y;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(nIdx).y > 0)
	{//Wが押された、上移動

		move.x += sinf(D3DX_PI * 0.0f + Camerarot.y) * fMove;
		move.z += cosf(D3DX_PI * 0.0f + Camerarot.y) * fMove;
		m_fRotDest = D3DX_PI * 1.0f + Camerarot.y;
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(nIdx).y < 0)
	{//Sが押された、下移動

		move.x += sinf(D3DX_PI * 1.0f + Camerarot.y) * fMove;
		move.z += cosf(D3DX_PI * 1.0f + Camerarot.y) * fMove;
		m_fRotDest = D3DX_PI * 0.0f + Camerarot.y;
	}
	else
	{
		bMove = false;
	}

	// 移動量設定
	SetMove(move);

	return bMove;
}

//==========================================================================
// 回転操作
//==========================================================================
void CPlayerUnion::ControllRotation(int nIdx)
{
	// キーボード情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// ゲームパッド情報取得
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	// カメラの情報取得
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	// カメラの向き取得
	D3DXVECTOR3 Camerarot = pCamera->GetRotation();

	if (pInputKeyboard->GetPress(DIK_A) == true || pInputGamepad->GetStickMoveL(nIdx).x < 0)
	{//←キーが押された,左移動

		if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(nIdx).y > 0)
		{//A+W,左上移動
			m_fRotDest = D3DX_PI * 0.75f + Camerarot.y;
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(nIdx).y < 0)
		{//A+S,左下移動
			m_fRotDest = D3DX_PI * 0.25f + Camerarot.y;
		}
		else
		{//A,左移動
			m_fRotDest = D3DX_PI * 0.5f + Camerarot.y;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true || pInputGamepad->GetStickMoveL(nIdx).x > 0)
	{//Dキーが押された,右移動

		if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(nIdx).y > 0)
		{//D+W,右上移動
			m_fRotDest = -D3DX_PI * 0.75f + Camerarot.y;
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(nIdx).y < 0)
		{//D+S,右下移動
			m_fRotDest = -D3DX_PI * 0.25f + Camerarot.y;
		}
		else
		{//D,右移動
			m_fRotDest = -D3DX_PI * 0.5f + Camerarot.y;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(nIdx).y > 0)
	{//Wが押された、上移動
		m_fRotDest = D3DX_PI * 1.0f + Camerarot.y;
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(nIdx).y < 0)
	{//Sが押された、下移動
		m_fRotDest = D3DX_PI * 0.0f + Camerarot.y;
	}
}

//==========================================================================
// モーションの設定
//==========================================================================
void CPlayerUnion::MotionSet(int nIdx)
{
	if (m_pMotion[nIdx] == NULL)
	{// モーションがNULLだったら
		return;
	}

	if (m_state == STATE_ULT)
	{
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
			if (nIdx == PARTS_R_ARM || nIdx == PARTS_L_ARM)
			{// 腕パーツ
				m_pMotion[nIdx]->SetNowPattern(m_pMotion[PARTS_BODY]->GetNowPattern());
				m_pMotion[nIdx]->SetFrameCount(m_pMotion[PARTS_BODY]->GetFrameCount());
			}
		}
		else if (m_sMotionFrag[nIdx].bCharge == true)
		{// チャージ中だったら

			// チャージモーション
			m_pMotion[nIdx]->Set(MOTION_NORMAL_CHARGE);
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
			m_pMotion[nIdx]->Set(MOTION_NORMAL_ATK);
		}
		else
		{
			// ニュートラルモーション
			m_pMotion[nIdx]->Set(MOTION_DEF);
		}
	}
}

//==========================================================================
// 攻撃
//==========================================================================
void CPlayerUnion::Atack(int nIdx)
{
	if (m_pMotion[nIdx] == NULL)
	{// モーションがNULLだったら
		return;
	}

	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// 向き取得
	D3DXVECTOR3 rot = GetRotation();

	// カメラの情報取得
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	// カメラの向き取得
	D3DXVECTOR3 Camerarot = pCamera->GetRotation();

	// モーションの情報取得
	CMotion::Info aInfo = m_pMotion[nIdx]->GetInfo(m_pMotion[nIdx]->GetType());

	// 攻撃情報の総数取得
	int nNumAttackInfo = aInfo.nNumAttackInfo;

	for (int nCntAttack = 0; nCntAttack < nNumAttackInfo; nCntAttack++)
	{
		if (aInfo.AttackInfo[nCntAttack] == NULL)
		{// NULLだったら
			continue;
		}

		// 攻撃情報保存
		CMotion::AttackInfo atkInfo = *aInfo.AttackInfo[nCntAttack];

		if (atkInfo.bOnlyOneTime && nIdx != 0)
		{// 1度だけ判定を取る場合
			return;
		}

		if (nIdx != GetModelIdxtFromPartsIdx(atkInfo.nCollisionNum))
		{// 判定を取るインデックスが現在のパーツに無かったら
			continue;
		}


		if (m_pMotion[nIdx]->IsImpactFrame(atkInfo))
		{// 衝撃のカウントと同じとき

			// 攻撃時処理
			AttackAction(nIdx, atkInfo.nCollisionNum, atkInfo, nCntAttack);
		}

		// モーションカウンター取得
		if (m_pMotion[nIdx]->GetAllCount() >= atkInfo.nMinCnt && m_pMotion[nIdx]->GetAllCount() < atkInfo.nMaxCnt)
		{// 攻撃判定中
			
			// 攻撃判定中処理
			AttackInDicision(nIdx, atkInfo, nCntAttack);
		}
	}

	CManager::GetInstance()->GetDebugProc()->Print(
			"モーションカウンター[%d]：%d\n", nIdx, m_pMotion[nIdx]->GetAllCount());
}

//==========================================================================
// 攻撃時処理
//==========================================================================
void CPlayerUnion::AttackAction(int nIdx, int nModelNum, CMotion::AttackInfo ATKInfo, int nCntATK)
{

	// 武器の位置
	D3DXVECTOR3 weponpos = m_pMotion[nIdx]->GetAttackPosition(m_apModel[ATKInfo.nCollisionNum], ATKInfo);

	// 向き取得
	D3DXVECTOR3 rot = GetRotation();

	// 種類別
	switch (m_pMotion[nIdx]->GetType())
	{
	case MOTION_ULT_BEAMATK:
	{
		float fMove = 0.5f;
		CBeam::Create(
			weponpos,							// 位置
			D3DXVECTOR3(
				sinf(D3DX_PI + rot.y) * fMove,
				cosf(D3DX_PI * 0.5f) * fMove,
				cosf(D3DX_PI + rot.y) * fMove),	// 移動量
			mylib_const::UNIONBEAM_COLOR,		// 色
			200.0f,		// 半径
			14000.0f,		// 長さ
			200,			// 寿命
			180,			// 密度
			1,	// ダメージ
			CCollisionObject::TAG_PLAYER,	// タグ
			CBeam::TYPE_RESIDUAL
		);

		// 衝撃波生成
		CImpactWave::Create
		(
			weponpos,	// 位置
			D3DXVECTOR3(D3DX_PI * 0.5f, D3DX_PI + rot.y, 0.0f),				// 向き
			mylib_const::PLAYERBEAM_COLOR,			// 色
			30.0f,						// 幅
			8.0f,						// 高さ
			60.0f,						// 中心からの距離
			20,							// 寿命
			30.0f,						// 幅の移動量
			CImpactWave::TYPE_PURPLE4,	// テクスチャタイプ
			true						// 加算合成するか
		);

		// 振動
		CManager::GetInstance()->GetCamera()->SetShake(36, 50.0f, 0.0f);
	}
		break;

	case MOTION_WALK:
		
		// 煙
		my_particle::Create(weponpos, my_particle::TYPE_UNIONWALK);

		// 振動
		CManager::GetInstance()->GetCamera()->SetShake(12, 10.0f, 0.0f);

		// 瓦礫
		CBallast::Create(weponpos, D3DXVECTOR3(3.0f, 8.0f, 3.0f), 10, 1.0f, CBallast::TYPE_STONE);
		break;

	case MOTION_ULT_BIGPUNCHCHARGE:

		if (nCntATK == 0)
		{
			// 合体後コア生成
			m_pUnionCore = CUnionCore::Create(weponpos);
			m_pUnionCore->SetUp(ATKInfo.Offset, m_apModel[ATKInfo.nCollisionNum]->GetPtrWorldMtx());

			// 振動
			CManager::GetInstance()->GetCamera()->SetShake(18, 10.0f, 0.0f);
		}
		else if (nCntATK == 1 && m_pUnionCore != nullptr)
		{
			m_pUnionCore->Uninit();
			m_pUnionCore = nullptr;

			// 振動
			CManager::GetInstance()->GetCamera()->SetShake(20, 15.0f, 0.0f);
		}
		else if (nCntATK == 2)
		{
			D3DXVECTOR3 rot = GetRotation();

			// 衝撃波生成
			CImpactWave *pWave = CImpactWave::Create
			(
				weponpos,	// 位置
				D3DXVECTOR3(D3DX_PI * 0.25f, D3DX_PI * 0.5f + rot.y, 0.0f),				// 向き
				D3DXCOLOR(0.9f, 0.5f, 0.1f, 0.8f),			// 色
				150.0f,										// 幅
				0.0f,										// 高さ
				0.0f,										// 中心からの間隔
				20,											// 寿命
				30.0f,										// 幅の移動量
				CImpactWave::TYPE_GIZAGRADATION,				// テクスチャタイプ
				true										// 加算合成するか
			);

			// 衝撃波生成
			CImpactWave::Create
			(
				weponpos,	// 位置
				D3DXVECTOR3(D3DX_PI * 0.75f, D3DX_PI * 0.5f + rot.y, 0.0f),				// 向き
				D3DXCOLOR(0.9f, 0.5f, 0.1f, 0.8f),			// 色
				150.0f,										// 幅
				0.0f,										// 高さ
				0.0f,										// 中心からの間隔
				20,											// 寿命
				30.0f,										// 幅の移動量
				CImpactWave::TYPE_GIZAGRADATION,				// テクスチャタイプ
				true										// 加算合成するか
			);

			// 振動
			CManager::GetInstance()->GetCamera()->SetShake(20, 15.0f, 0.0f);

			// ウルトで腕デカくした判定
			m_bUltBigArm = true;
		}

		break;	// MOTION_ULT_BIGPUNCHCHARGEの終端

	case MOTION_ULT_BIGPUNCHATK:

		// 衝撃波生成
		CImpactWave::Create
		(
			weponpos,	// 位置
			D3DXVECTOR3(D3DX_PI * 1.0f, 0.0f, 0.0f),	// 向き
			D3DXCOLOR(0.9f, 0.5f, 0.1f, 0.8f),			// 色
			10.0f,										// 幅
			150.0f,										// 高さ
			0.0f,										// 中心からの間隔
			20,											// 寿命
			60.0f,										// 幅の移動量
			CImpactWave::TYPE_GIZAGRADATION,			// テクスチャタイプ
			true										// 加算合成するか
		);

		D3DXVECTOR3 moveeffect = mylib_const::DEFAULT_VECTOR3;
		for (int nCntUse = 0; nCntUse < 10; nCntUse++)
		{
			float fMove = (float)Random(200, 220) * 0.1f;		// 移動量
			float fMoveY = (float)Random(80, 120) * 0.1f;		// 移動量

			float fRot = GetRandomCircleValue();
			float fRandCol = Random(-100, 100) * 0.001f;

			// 移動量の設定
			moveeffect.x = sinf(fRot) * fMove;
			moveeffect.y = fMoveY;
			moveeffect.z = cosf(fRot) * fMove;

			// エフェクトの設定
			CEffect3D::Create(
				GetPosition(),
				moveeffect,
				D3DXCOLOR(0.8f + fRandCol, 0.8f + fRandCol, 0.8f + fRandCol, 1.0f),
				300.0f + Random(-50, 50),
				30,
				CEffect3D::MOVEEFFECT_ADD,
				CEffect3D::TYPE_SMOKEBLACK,
				0.0f);
		}



		// 振動
		CManager::GetInstance()->GetCamera()->SetShake(20, 15.0f, 0.0f);

		break;	// MOTION_ULT_BIGPUNCHCHARGEの終端
	}
}

//==========================================================================
// 攻撃判定中処理
//==========================================================================
void CPlayerUnion::AttackInDicision(int nIdx, CMotion::AttackInfo ATKInfo, int nCntATK)
{
	// 武器の位置
	D3DXVECTOR3 weponpos = m_pMotion[nIdx]->GetAttackPosition(m_apModel[ATKInfo.nCollisionNum], ATKInfo);

#if _DEBUG
	CEffect3D::Create(weponpos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), ATKInfo.fRangeSize, 10, CEffect3D::MOVEEFFECT_NONE, CEffect3D::TYPE_NORMAL);
#endif

	CEffect3D *pEffect = nullptr;

	// 向き取得
	D3DXVECTOR3 rot = GetRotation();

	// モーションカウンター取得
	float fAllCount = m_pMotion[nIdx]->GetAllCount();
	int repeat = 10 - (int)((fAllCount - ATKInfo.nMinCnt) / 12.0f);
	ValueNormalize(repeat, 9999, 1);

	// 種類別
	switch (m_pMotion[nIdx]->GetType())
	{
	case MOTION_BOOST:
	{
		// 炎
		float fMove = 16.0f + Random(-2, 4);
		float fRot = Random(-20, 20) * 0.01f;

		pEffect = CEffect3D::Create(
			weponpos,
			D3DXVECTOR3(
				sinf(D3DX_PI + rot.y + fRot) * -fMove,
				static_cast<float>(Random(-40, 40)) * 0.1f,
				cosf(D3DX_PI + rot.y + fRot) * -fMove),
			D3DXCOLOR(1.0f + Random(-10, 0) * 0.01f, 0.0f, 0.0f, 1.0f),
			150.0f + (float)Random(-20, 20),
			15,
			CEffect3D::MOVEEFFECT_ADD,
			CEffect3D::TYPE_SMOKE);

		if (pEffect != NULL)
		{
			// セットアップ位置設定
			pEffect->SetUp(ATKInfo.Offset, m_apModel[ATKInfo.nCollisionNum]->GetPtrWorldMtx(), CObject::GetObject(), SetEffectParent(pEffect));
		}

		fRot = Random(-20, 20) * 0.01f;
		// 炎
		pEffect = CEffect3D::Create(
			weponpos,
			D3DXVECTOR3(
				sinf(D3DX_PI + rot.y + fRot) * -fMove,
				static_cast<float>(Random(-40, 40)) * 0.1f,
				cosf(D3DX_PI + rot.y + fRot) * -fMove),
			D3DXCOLOR(0.8f + Random(-10, 0) * 0.01f, 0.5f + Random(-10, 0) * 0.01f, 0.0f, 1.0f),
			100.0f + (float)Random(-10, 10),
			15,
			CEffect3D::MOVEEFFECT_ADD,
			CEffect3D::TYPE_SMOKE);
		if (pEffect != NULL)
		{
			// セットアップ位置設定
			pEffect->SetUp(ATKInfo.Offset, m_apModel[ATKInfo.nCollisionNum]->GetPtrWorldMtx(), CObject::GetObject(), SetEffectParent(pEffect));
		}
	}
		break;

	case MOTION_ULT_BEAMCHARGE:
		if ((int)fAllCount % repeat == 0)
		{
			my_particle::Create(weponpos, my_particle::TYPE_ULT_BEAM_CHARGE);
		}

		if (ATKInfo.nCollisionNum == 1 && (int)fAllCount % 8 == 0)
		{
			int repeat = (int)((fAllCount - ATKInfo.nMinCnt) / 8.0f);
			CEffect3D::Create(
				weponpos,
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				mylib_const::UNIONBEAM_COLOR,
				20.0f, 20, CEffect3D::MOVEEFFECT_ADD, CEffect3D::TYPE_NORMAL, repeat * 1.1f);
		}
		break;

	case MOTION_ULT_BEAMATK:
		break;

	case MOTION_ULT_BIGPUNCHCHARGE:
		if (nCntATK == 3)
		{
			D3DXVECTOR3 RandPos = mylib_const::DEFAULT_VECTOR3;
			RandPos.x = Random(-5, 5) * 10.0f;
			RandPos.y = Random(-5, 5) * 10.0f;
			RandPos.z = Random(-5, 5) * 10.0f;

			CEffect3D *pEffect = CEffect3D::Create(
				weponpos + RandPos,
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.2f, 0.2f, 0.9f, 1.0f),
				100.0f + (float)Random(-20, 20), 6,
				CEffect3D::MOVEEFFECT_ADD,
				CEffect3D::TYPE_THUNDER);
			pEffect->SetRotation(D3DXVECTOR3(0.0f, 0.0f, GetRandomCircleValue()));
		}
		else if (nCntATK >= 4)
		{
			D3DXVECTOR3 RandPos = mylib_const::DEFAULT_VECTOR3;

			int nMax = 1;
			float fSize = 200.0f;
			if (m_bUltBigArm)
			{
				nMax = 3;
				fSize = 300.0f;
			}

			for (int i = 0; i < nMax; i++)
			{
				RandPos.x = Random(-5, 5) * 10.0f;
				RandPos.y = Random(-5, 5) * 10.0f;
				RandPos.z = Random(-5, 5) * 10.0f;

				CEffect3D *pEffect = CEffect3D::Create(
					weponpos + RandPos,
					D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.2f, 0.2f, 0.9f, 1.0f),
					fSize, 6,
					CEffect3D::MOVEEFFECT_ADD,
					CEffect3D::TYPE_THUNDER);

				RandPos.x = Random(-5, 5) * 10.0f;
				RandPos.y = Random(-5, 5) * 10.0f;
				RandPos.z = Random(-5, 5) * 10.0f;
				CEffect3D::Create(
					weponpos + RandPos,
					D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.2f, 0.2f, 0.9f, 1.0f),
					fSize, 6,
					CEffect3D::MOVEEFFECT_ADD,
					CEffect3D::TYPE_POINT);
				pEffect->SetRotation(D3DXVECTOR3(0.0f, 0.0f, GetRandomCircleValue()));
			}
		}
		break;

	case MOTION_ULT_BIGPUNCHATK:
	{
		D3DXVECTOR3 RandPos = mylib_const::DEFAULT_VECTOR3;
		for (int i = 0; i < 3; i++)
		{
			RandPos.x = Random(-5, 5) * 10.0f;
			RandPos.y = Random(-5, 5) * 10.0f;
			RandPos.z = Random(-5, 5) * 10.0f;

			CEffect3D *pEffect = CEffect3D::Create(
				weponpos + RandPos,
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.2f, 0.2f, 0.9f, 1.0f),
				300.0f, 6,
				CEffect3D::MOVEEFFECT_ADD,
				CEffect3D::TYPE_THUNDER);

			RandPos.x = Random(-5, 5) * 10.0f;
			RandPos.y = Random(-5, 5) * 10.0f;
			RandPos.z = Random(-5, 5) * 10.0f;
			CEffect3D::Create(
				weponpos + RandPos,
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.2f, 0.2f, 0.9f, 1.0f),
				300.0f, 6,
				CEffect3D::MOVEEFFECT_ADD,
				CEffect3D::TYPE_POINT);
			pEffect->SetRotation(D3DXVECTOR3(0.0f, 0.0f, GetRandomCircleValue()));
		}
	}
	break;

	}// 終端


	if (ATKInfo.fRangeSize == 0.0f)
	{
		return;
	}

	// 敵取得
	CEnemyManager *pEnemyManager = CGame::GetEnemyManager();
	if (pEnemyManager == NULL)
	{
		return;
	}

	CEnemy **ppEnemy = pEnemyManager->GetEnemy();

	// 総数取得
	int nNumAll = pEnemyManager->GetNumAll();
	int i = -1, nCntEnemy = 0;

	while (1)
	{
		if (nCntEnemy >= nNumAll)
		{// 総数超えたら終わり
			break;
		}

		// インデックス加算
		i++;
		if (ppEnemy[i] == NULL)
		{
			continue;
		}

		// 敵の位置取得
		D3DXVECTOR3 TargetPos = ppEnemy[i]->GetPosition();

		// 判定サイズ取得
		float fTargetRadius = ppEnemy[i]->GetRadius();

		if (SphereRange(weponpos, TargetPos, ATKInfo.fRangeSize, fTargetRadius))
		{// 球の判定

			if (ppEnemy[i]->Hit(ATKInfo.nDamage) == true)
			{// 当たってたら

			}
		}

		// 敵の数加算
		nCntEnemy++;
	}
}

//==========================================================================
// 当たり判定
//==========================================================================
bool CPlayerUnion::Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &move)
{

	// 向き取得
	D3DXVECTOR3 rot = GetRotation();

	// 着地したかどうか
	bool bLand = false;
	float fHeight = 0.0f;
	m_bLandField = false;
	m_bHitWall = false;			// 壁の当たり判定

								// 高さ取得
	if (m_state != STATE_KNOCKBACK && m_state != STATE_DMG && m_state != STATE_DEAD && m_state != STATE_FADEOUT)
	{
		fHeight = CManager::GetInstance()->GetScene()->GetElevation()->GetHeight(pos, bLand);
	}
	else
	{
		fHeight = pos.y;
	}

	if (fHeight > pos.y)
	{// 地面の方が自分より高かったら

		// 地面の高さに補正
		pos.y = fHeight;
		m_bLandField = true;

		if (bLand == true)
		{// 着地してたら

		 // ジャンプ使用可能にする
			m_bJump = false;
			move.y = 0.0f;
			m_bLandOld = true;
		}
	}

	if (pos.y < 0.0f)
	{
		pos.y = 0.0f;
	}


	// Xファイルとの判定
	CStage *pStage = CGame::GetStage();
	if (pStage == NULL)
	{// NULLだったら
		return false;
	}

	bool bNowLand = false;

	// ステージに当たった判定
	m_bHitStage = false;
	for (int nCntStage = 0; nCntStage < pStage->GetNumAll(); nCntStage++)
	{
		// オブジェクト取得
		CObjectX *pObjX = pStage->GetObj(nCntStage);

		if (pObjX == NULL)
		{// NULLだったら
			continue;
		}

		// 高さ取得
		bool bLand = false;
		fHeight = pObjX->GetHeight(pos, bLand);

		if (bLand == true && fHeight > pos.y)
		{// 地面の方が自分より高かったら

		 // 地面の高さに補正
			if (pos.y + 50.0f <= fHeight)
			{// 自分より壁が高すぎる
				m_bHitWall = true;
			}
			else
			{
				pos.y = fHeight;
			}

			m_bHitStage = true;
			m_bLandField = false;

			if (bLand == true)
			{// 着地してたら

				if ((m_bKnockBack == true || m_bJump == true) && GetPosition().y >= fHeight)
				{
					m_bLandOld = true;
				}

				if (m_bJump == true)
				{// ジャンプ中だったら
					m_pMotion[PARTS_BODY]->ToggleFinish(true);
				}

				// ジャンプ使用可能にする
				m_bJump = false;
				move.y = 0.0f;
				bNowLand = true;

				for (int i = 0; i < PARTS_MAX; i++)
				{
					m_sMotionFrag[i].bJump = false;
				}
			}
		}
	}




	// オブジェクト取得
	CObjectX *pObjX = pStage->GetInjectionTable();

	// 高さ取得
	bLand = false;
	fHeight = pObjX->GetHeight(pos, bLand);

	if (bLand == true && fHeight > pos.y)
	{// 地面の方が自分より高かったら

		// 地面の高さに補正
		if (pos.y + 50.0f <= fHeight)
		{// 自分より壁が高すぎる
			m_bHitWall = true;
		}
		else
		{
			pos.y = fHeight;
		}

		m_bHitStage = true;
		m_bLandField = false;

		if (bLand == true)
		{// 着地してたら

			if ((m_bKnockBack || m_bJump == true) && GetPosition().y >= fHeight)
			{
				m_bLandOld = true;
			}

			if (m_bJump == true)
			{// ジャンプ中だったら
				m_pMotion[PARTS_BODY]->ToggleFinish(true);
			}

			// ジャンプ使用可能にする
			m_bJump = false;
			move.y = 0.0f;
			bNowLand = true;
			
			for (int i = 0; i < PARTS_MAX; i++)
			{
				m_sMotionFrag[i].bJump = false;
			}

			// 射出台の着地判定
			m_bLandInjectionTable[m_nMyPlayerIdx] = true;

		}
	}

	int nLandNum = 0;
	for (int i = 0; i < CManager::GetInstance()->GetNumPlayer(); i++)
	{
		// 射出台の着地確認
		if (m_bLandInjectionTable[i] == true)
		{
			nLandNum++;
		}
	}

	// 全員着地状態設定
	if (nLandNum >= CManager::GetInstance()->GetNumPlayer())
	{
		m_bAllLandInjectionTable = true;
	}
	else
	{
		m_bAllLandInjectionTable = false;
	}

	if (CGame::GetGameManager()->GetType() == CGameManager::SCENE_MAINCLEAR &&
		pStage->GetInjectionTable()->GetState() != CInjectionTable::STATE_UP)
	{// 通常クリアだったら

		if (m_bAllLandInjectionTable == true)
		{// 全員射出台に乗っている

			// チャージ状態
			pStage->GetInjectionTable()->SetState(CInjectionTable::STATE_CHARGE);
		}
		else
		{
			// リセット
			pStage->GetInjectionTable()->SetState(CInjectionTable::STATE_NONE, 0);
		}
	}





	// 位置取得
	D3DXVECTOR3 posOld = GetPosition();

	//// 箱
	//float fLen = CGame::GetElevation()->GetWidthLen();
	//int nBlock = CGame::GetElevation()->GetWidthBlock();
	//nBlock /= 2;
	//if (pos.x + RADIUS >= fLen * nBlock) { pos.x = fLen * nBlock - RADIUS; }
	//if (pos.x - RADIUS <= -fLen * nBlock) { pos.x = -fLen * nBlock + RADIUS; }
	//if (pos.z + RADIUS >= fLen * nBlock) { pos.z = fLen * nBlock - RADIUS; }
	//if (pos.z - RADIUS <= -fLen * nBlock) { pos.z = -fLen * nBlock + RADIUS; }

	// 向き設定
	SetRotation(rot);

	return bNowLand;
}

//==========================================================================
// ヒット処理
//==========================================================================
bool CPlayerUnion::Hit(const int nValue)
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
// 状態更新処理
//==========================================================================
void CPlayerUnion::UpdateState(void)
{
	switch (m_state)
	{
	case STATE_NONE:
		// 色設定
		m_mMatcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;

	case STATE_INVINCIBLE:
		Invincible();
		break;

	case STATE_DMG:
		Damage();
		break;

	case STATE_DEAD:
		Dead();
		break;

	case STATE_FADEOUT:
		FadeOut();
		break;

	case STATE_KNOCKBACK:
		KnockBack();
		break;

	case STATE_APPEARANCE:
		Appearance();
		break;

	case STATE_ULT:
		Ultimate();
		break;
	}
}

//==========================================================================
// 無敵
//==========================================================================
void CPlayerUnion::Invincible(void)
{
	// 状態遷移カウンター減算
	m_nCntState--;

	if (m_nCntState % INVINCIBLE_INT == 0)
	{// 規定間隔
		
		// 色設定
		if (m_mMatcol.a == 1.0f)
		{
			m_mMatcol.a = 0.4f;
		}
		else
		{
			m_mMatcol.a = 1.0f;
		}
	}

	if (m_nCntState <= 0)
	{// 遷移カウンターが0になったら

		// なにもない状態にする
		m_state = STATE_NONE;
		m_nCntState = 0;

		// 色設定
		m_mMatcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

}

//==========================================================================
// ダメージ
//==========================================================================
void CPlayerUnion::Damage(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// 移動量取得
	D3DXVECTOR3 move = GetMove();

	// 向き取得
	D3DXVECTOR3 rot = GetRotation();

	// 状態遷移カウンター減算
	m_nCntState++;

	// 色設定
	m_mMatcol = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	// 位置更新
	pos.y = (-0.4f * (float)(m_nCntState * m_nCntState) + m_KnokBackMove.y * (float)m_nCntState) + m_posKnokBack.y;
	pos.x += move.x;
	/*pos.x += move.x;
	pos.z += move.z;*/

	// 起伏との判定
	if ((CManager::GetInstance()->GetScene()->GetElevation()->IsHit(pos) || m_bHitStage) && m_nCntState >= 10)
	{// 地面と当たっていたら
		m_state = STATE_INVINCIBLE;
		m_nCntState = INVINCIBLE_TIME;
		m_KnokBackMove.y = 0.0f;	// 移動量ゼロ
		m_bLandOld = true;

		// 色設定
		m_mMatcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ノックバック判定消す
		m_bKnockBack = false;
		m_pMotion[PARTS_BODY]->ToggleFinish(true);


		// Xファイルとの判定
		CStage *pStage = CGame::GetStage();
		if (pStage == NULL)
		{// NULLだったら
			return;
		}

		// ステージに当たった判定
		for (int nCntStage = 0; nCntStage < pStage->GetNumAll(); nCntStage++)
		{
			// オブジェクト取得
			CObjectX *pObjX = pStage->GetObj(nCntStage);

			if (pObjX == NULL)
			{// NULLだったら
				continue;
			}

			// 高さ取得
			bool bLand = false;
			pos.y = pObjX->GetHeight(pos, bLand);
		}


	}
	else if (m_nCntState >= 30)
	{// 遷移カウンターが30になったら

		// ノックバック状態にする
		m_state = STATE_KNOCKBACK;
	}


	// 位置設定
	SetPosition(pos);

	// 移動量設定
	SetMove(move);

	// 向き設定
	SetRotation(rot);
}

//==========================================================================
// 死亡
//==========================================================================
void CPlayerUnion::Dead(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// 移動量取得
	D3DXVECTOR3 move = GetMove();

	// 位置更新
	if (m_nCntState > 0)
	{
		int nCnt = DEADTIME - m_nCntState;
		pos.y = (-0.1f * (float)(nCnt * nCnt) + m_KnokBackMove.y * (float)nCnt) + m_posKnokBack.y;
		pos.x += move.x;
	}

	// 状態遷移カウンター減算
	m_nCntState--;

	// 起伏との判定
	if ((CManager::GetInstance()->GetScene()->GetElevation()->IsHit(pos) || m_bHitStage) && m_nCntState >= 10)
	{// 地面と当たっていたら

		//// フェードを設定する
		//CManager::GetInstance()->GetInstantFade()->SetFade();

		//if (CManager::GetInstance()->GetInstantFade()->GetState() == CInstantFade::STATE_FADECOMPLETION)
		//{// フェード完了した時



		//}

		m_state = STATE_FADEOUT;	// フェードアウト
		m_nCntState = FADEOUTTIME;
		m_KnokBackMove.y = 0.0f;	// 移動量ゼロ
		m_bLandOld = true;
		move.x = 0.0f;

		// 色設定
		m_mMatcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ノックバック判定消す
		m_bKnockBack = false;
		m_bDead = true;
		//m_pMotion->ToggleFinish(true);

		// ぶっ倒れモーション
		m_pMotion[PARTS_BODY]->Set(MOTION_DEAD);

		// Xファイルとの判定
		CStage *pStage = CGame::GetStage();
		if (pStage == NULL)
		{// NULLだったら
			return;
		}

		// ステージに当たった判定
		for (int nCntStage = 0; nCntStage < pStage->GetNumAll(); nCntStage++)
		{
			// オブジェクト取得
			CObjectX *pObjX = pStage->GetObj(nCntStage);

			if (pObjX == NULL)
			{// NULLだったら
				continue;
			}

			// 高さ取得
			bool bLand = false;
			pos.y = pObjX->GetHeight(pos, bLand);
		}
	}

	// 位置設定
	SetPosition(pos);

	// 移動量設定
	SetMove(move);
}

//==========================================================================
// フェードアウト
//==========================================================================
void CPlayerUnion::FadeOut(void)
{

	// 状態遷移カウンター減算
	m_nCntState--;

	// 色設定
	m_mMatcol.a = (float)m_nCntState / (float)FADEOUTTIME;

	if (m_nCntState <= 0)
	{// 遷移カウンターが0になったら

		// モード設定
		//CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RESULT);

		// 死亡処理
		Kill();

		// 終了処理
		Uninit();
		return;
	}
}

//==========================================================================
// ノックバック
//==========================================================================
void CPlayerUnion::KnockBack(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// 移動量取得
	D3DXVECTOR3 move = GetMove();

	// 向き取得
	D3DXVECTOR3 rot = GetRotation();

	// 現在と目標の差分
	float fRotDiff = 0.0f;

	// 距離の判定
	bool bLen = false;


	// 状態遷移カウンター減算
	m_nCntState++;

	// 位置更新
	pos.y = (-0.4f * (float)(m_nCntState * m_nCntState) + m_KnokBackMove.y * (float)m_nCntState) + m_posKnokBack.y;
	pos.x += move.x;
	/*pos.x += move.x;
	pos.z += move.z;*/

	// 起伏との判定
	if ((CManager::GetInstance()->GetScene()->GetElevation()->IsHit(pos) || m_bHitStage))
	{// 地面と当たっていたら
		m_state = STATE_INVINCIBLE;
		m_nCntState = INVINCIBLE_TIME;
		m_KnokBackMove.y = 0.0f;	// 移動量ゼロ
		m_bLandOld = true;

		// 色設定
		m_mMatcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		
		// ノックバック判定消す
		m_bKnockBack = false;
		//m_pMotion[PARTS_BODY]->ToggleFinish(true);

		// Xファイルとの判定
		CStage *pStage = CGame::GetStage();
		if (pStage == NULL)
		{// NULLだったら
			return;
		}

		// ステージに当たった判定
		for (int nCntStage = 0; nCntStage < pStage->GetNumAll(); nCntStage++)
		{
			// オブジェクト取得
			CObjectX *pObjX = pStage->GetObj(nCntStage);

			if (pObjX == NULL)
			{// NULLだったら
				continue;
			}

			// 高さ取得
			bool bLand = false;
			pos.y = pObjX->GetHeight(pos, bLand);
		}
	}


	// 位置設定
	SetPosition(pos);

	// 移動量設定
	SetMove(move);

	// 向き設定
	SetRotation(rot);
}

//==========================================================================
// 出現
//==========================================================================
void CPlayerUnion::Appearance(void)
{
	int nType = m_pMotion[0]->GetType();
	if (nType == MOTION_APPEARANCE && m_pMotion[0]->IsFinish() == true)
	{// 登場演出が終わってたら
		m_nCntState = 0;
		m_state = STATE_NONE;
	}

	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pMotion[i] == NULL)
		{
			continue;
		}
		// 登場モーション設定
		m_pMotion[i]->Set(MOTION_APPEARANCE);
	}
}

//==========================================================================
// 必殺技
//==========================================================================
void CPlayerUnion::Ultimate(void)
{
	// 状態別処理
	(this->*(m_UltFuncList[m_UltType]))();
}

//==========================================================================
// 必殺：ビーム
//==========================================================================
void CPlayerUnion::UltBeam(void)
{
	switch (m_UltBranch)
	{
	case CPlayerUnion::ULTBRANCH_CHARGE_BEAM:
		UltChargeBeam();
		break;

	case CPlayerUnion::ULTBRANCH_ATTACK_BEAM:
		UltAttackBeam();
		break;

	default:
		m_UltBranch = ULTBRANCH_CHARGE_BEAM;
		break;
	}
}

//==========================================================================
// ビームチャージ
//==========================================================================
void CPlayerUnion::UltChargeBeam(void)
{

	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		if (m_pMotion[i] == NULL)
		{
			continue;
		}

		int nType = m_pMotion[i]->GetType();
		if (nType == MOTION_ULT_BEAMCHARGE && m_pMotion[i]->IsFinish() == true)
		{// チャージが終わってたら

			// 待機行動
			m_UltBranch = ULTBRANCH_ATTACK_BEAM;

			// 必殺ビームモーション設定
			m_pMotion[i]->Set(MOTION_ULT_BEAMATK);
			return;
		}

		if (nType != MOTION_ULT_BEAMCHARGE)
		{
			// チャージモーション設定
			m_pMotion[i]->Set(MOTION_ULT_BEAMCHARGE);
		}
	}
}

//==========================================================================
// ビーム攻撃
//==========================================================================
void CPlayerUnion::UltAttackBeam(void)
{
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		if (m_pMotion[i] == NULL)
		{
			continue;
		}

		int nType = m_pMotion[i]->GetType();
		if (nType == MOTION_ULT_BEAMATK && m_pMotion[i]->IsFinish() == true)
		{// チャージが終わってたら

			// なにもない状態
			m_state = STATE_NONE;

			// 必殺ビームモーション設定
			m_pMotion[i]->Set(MOTION_DEF);
			return;
		}

		if (nType != MOTION_ULT_BEAMATK)
		{
			// ビームモーション設定
			m_pMotion[i]->Set(MOTION_ULT_BEAMATK);
		}
	}
}


//==========================================================================
// 必殺：デカパンチ
//==========================================================================
void CPlayerUnion::UltBigPunch(void)
{
	switch (m_UltBranch)
	{
	case CPlayerUnion::ULTBRANCH_CHARGE_BIGPUNCH:
		UltChargeBigPunch();
		break;

	case CPlayerUnion::ULTBRANCH_ATTACK_BIGPUNCH:
		UltAttackBigPunch();
		break;

	default:
		m_UltBranch = ULTBRANCH_CHARGE_BIGPUNCH;
		break;
	}
}

//==========================================================================
// デカパンチチャージ
//==========================================================================
void CPlayerUnion::UltChargeBigPunch(void)
{

	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		if (m_pMotion[i] == NULL)
		{
			continue;
		}

		int nType = m_pMotion[i]->GetType();
		if (nType == MOTION_ULT_BIGPUNCHCHARGE && m_pMotion[i]->IsFinish() == true)
		{// チャージが終わってたら

			// 待機行動
			m_UltBranch = ULTBRANCH_ATTACK_BIGPUNCH;

			// 必殺ビームモーション設定
			m_pMotion[i]->Set(MOTION_ULT_BIGPUNCHATK);
			return;
		}

		if (nType != MOTION_ULT_BIGPUNCHCHARGE)
		{
			// チャージモーション設定
			m_pMotion[i]->Set(MOTION_ULT_BIGPUNCHCHARGE);

			// ウルトで腕デカくした判定
			m_bUltBigArm = false;
		}
	}
}

//==========================================================================
// デカパンチ攻撃
//==========================================================================
void CPlayerUnion::UltAttackBigPunch(void)
{
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		if (m_pMotion[i] == NULL)
		{
			continue;
		}

		int nType = m_pMotion[i]->GetType();
		if (nType == MOTION_ULT_BIGPUNCHATK && m_pMotion[i]->IsFinish() == true)
		{// チャージが終わってたら

			// なにもない状態
			m_state = STATE_NONE;

			// 必殺ビームモーション設定
			m_pMotion[i]->Set(MOTION_DEF);
			return;
		}

		if (nType != MOTION_ULT_BIGPUNCHATK)
		{
			// ビームモーション設定
			m_pMotion[i]->Set(MOTION_ULT_BIGPUNCHATK);
		}
	}
}

//==========================================================================
// ライダーキック
//==========================================================================
void CPlayerUnion::UltRiderKick(void)
{
	switch (m_UltBranch)
	{
	case CPlayerUnion::ULTBRANCH_CHARGE_RIDERKICK:
		UltChargeRiderKick();
		break;

	case CPlayerUnion::ULTBRANCH_ATTACK_RIDERKICK:
		UltAttackRiderKick();
		break;

	default:
		m_UltBranch = ULTBRANCH_CHARGE_RIDERKICK;
		break;
	}
}

//==========================================================================
// ライダーキックチャージ
//==========================================================================
void CPlayerUnion::UltChargeRiderKick(void)
{
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		if (m_pMotion[i] == NULL)
		{
			continue;
		}

		int nType = m_pMotion[i]->GetType();
		if (nType == MOTION_ULT_BIGPUNCHCHARGE && m_pMotion[i]->IsFinish() == true)
		{// チャージが終わってたら

			// 待機行動
			m_UltBranch = ULTBRANCH_ATTACK_BIGPUNCH;

			// 必殺ビームモーション設定
			m_pMotion[i]->Set(MOTION_ULT_BIGPUNCHATK);
			return;
		}

		if (nType != MOTION_ULT_BIGPUNCHCHARGE)
		{
			// チャージモーション設定
			m_pMotion[i]->Set(MOTION_ULT_BIGPUNCHCHARGE);
		}
	}
}

//==========================================================================
// ライダーキック攻撃
//==========================================================================
void CPlayerUnion::UltAttackRiderKick(void)
{
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		if (m_pMotion[i] == NULL)
		{
			continue;
		}

		int nType = m_pMotion[i]->GetType();
		if (nType == MOTION_ULT_BIGPUNCHATK && m_pMotion[i]->IsFinish() == true)
		{// チャージが終わってたら

			// なにもない状態
			m_state = STATE_NONE;

			// 必殺ビームモーション設定
			m_pMotion[i]->Set(MOTION_DEF);
			return;
		}

		if (nType != MOTION_ULT_BIGPUNCHATK)
		{
			// ビームモーション設定
			m_pMotion[i]->Set(MOTION_ULT_BIGPUNCHATK);
		}
	}
}

//==========================================================================
// 描画処理
//==========================================================================
void CPlayerUnion::Draw(void)
{

	/*if (m_state == STATE_DMG)
	{
		CObjectChara::Draw(m_mMatcol);
	}
	else if (m_state == STATE_INVINCIBLE || m_state == STATE_FADEOUT)
	{
		CObjectChara::Draw(m_mMatcol.a);
	}
	else
	{
		CObjectChara::Draw();
	}*/

	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pObjChara[i] == NULL)
		{
			continue;
		}

		// 攻撃処理
		//m_pObjChara[i]->Draw();		// 胴体
	}

	// HPゲージ
	if (m_pHPGauge != NULL)
	{
		m_pHPGauge->Draw();
	}
}

//==========================================================================
// プレイヤーインデックス毎のテクスチャ設定
//==========================================================================
void CPlayerUnion::BindByPlayerIdxTexture(int nIdx, int nPartsIdx)
{
	ValueNormalize(nPartsIdx, 4, 0);

	// ファイルインデックス番号取得
	int nIdxXFile = m_pObjChara[nPartsIdx]->GetIdxFile();
	CObjectChara::Load LoadData = m_pObjChara[nPartsIdx]->GetLoadData(nIdxXFile);

	// モデル取得
	CModel **ppModel = m_pObjChara[nPartsIdx]->GetModel();

	// 初期テクスチャ
	int nIdxTex = CManager::GetInstance()->GetTexture()->Regist(TEXTURE_INITPLAYER[nPartsIdx][nIdx]);
	for (int i = 0; i < m_pObjChara[nPartsIdx]->GetNumModel(); i++)
	{
		if (ppModel[i] == NULL)
		{
			continue;
		}

		// Xファイルのデータ取得
		CXLoad::SXFile *pXData = CScene::GetXLoad()->GetMyObject(ppModel[i]->GetIdxXFile());

		for (int nMat = 0; nMat < (int)pXData->dwNumMat; nMat++)
		{
			ppModel[i]->SetIdxTexture(nMat, nIdxTex);
		}
	}

}

//==========================================================================
// 複数キャラクター読み込み
//==========================================================================
void CPlayerUnion::ReadMultiCharacter(const char *pTextFile)
{
	FILE *pFile = NULL;	// ファイルポインタを宣言

	// ファイルを開く
	pFile = fopen(pTextFile, "r");

	if (pFile == NULL)
	{//ファイルが開けた場合
		return;
	}

	// 各パーツごとのモデルインデックスリセット
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		m_nModelIdx[i].clear();
	}

	char aComment[MAX_COMMENT];	// コメント

	std::string CharacterFile[mylib_const::MAX_PLAYER];
	std::string MotionFile;
	int nCntFileName = 0;
	int nNumParts = 0;
	int nCntModel = 0;

	while (1)
	{// END_SCRIPTが来るまで繰り返す

		// 文字列の読み込み
		fscanf(pFile, "%s", &aComment[0]);

		// パーツ数の設定
		if (strcmp(aComment, "NUM_PARTS") == 0)
		{// NUM_PARTSがきたら

			fscanf(pFile, "%s", &aComment[0]);	// =の分
			fscanf(pFile, "%d", &nNumParts);	// パーツ数
		}

		// モーションファイル名
		if (strcmp(aComment, "MOTION_FILENAME") == 0)
		{// MOTION_FILENAMEがきたら

			fscanf(pFile, "%s", &aComment[0]);	// =の分
			fscanf(pFile, "%s", &aComment[0]);	// ファイル名

			// ファイル名保存
			MotionFile = aComment;

			// セットアップ情報
			while (nCntFileName != nNumParts)
			{// モデルの数分読み込むまで繰り返し

				// 文字列の読み込み
				fscanf(pFile, "%s", &aComment[0]);

				// セットアップの設定
				if (strcmp(aComment, "SETUP_FILENAME") == 0)
				{// SETUP_FILENAMEがきたら

					fscanf(pFile, "%s", &aComment[0]);	// =の分
					fscanf(pFile, "%s", &aComment[0]);	// ファイル名

					// ファイル名保存
					CharacterFile[nCntFileName] = aComment;


					//**********************************
					// キャラクター生成
					//**********************************
					m_pObjChara[nCntFileName] = CObjectChara::Create(CharacterFile[nCntFileName]);
					if (m_pObjChara[nCntFileName] == NULL)
					{// 失敗していたら
						return;
					}
					m_pObjChara[nCntFileName]->SetType(CObject::TYPE_OBJECTX);

					// モーションの生成処理
					m_pMotion[nCntFileName] = CMotion::Create(MotionFile);

					// オブジェクトキャラクターの情報取得
					CObjectChara *pObjChar = m_pObjChara[nCntFileName]->GetObjectChara();

					// モーションの設定
					m_pMotion[nCntFileName]->SetModel(pObjChar->GetModel(), pObjChar->GetNumModel(), pObjChar);

					// ポーズのリセット
					m_pMotion[nCntFileName]->ResetPose(MOTION_DEF);

					// モデルコピー
					CModel **ppModel = pObjChar->GetModel();
					for (int i = 0; i < pObjChar->GetNumModel(); i++)
					{
						// 各パーツごとのモデルインデックス保存
						m_nModelIdx[nCntFileName].push_back(nCntModel);

						m_apModel[nCntModel] = ppModel[i];
						nCntModel++;
					}

					nCntFileName++;	// ファイル数加算
				}
			}
		}

		// 各パーツの設定
		if (strcmp(aComment, "PARENTSET") == 0)
		{// 親設定の読み込みを開始

			int nFileNumber = -1, nModelIdx = -1, nParentFileNumber = -1, nParentModelIdx = -1;

			while (strcmp(aComment, "END_PARENTSET") != 0)
			{// END_PARENTSETが来るまで繰り返し

				fscanf(pFile, "%s", &aComment[0]);	//確認する

				if (strcmp(aComment, "FILENUMBER") == 0)
				{// FILENUMBERで設定するキャラクターファイル番号読み込み

					fscanf(pFile, "%s", &aComment[0]);	// =の分
					fscanf(pFile, "%d", &nFileNumber);	// キャラクターファイル番号
				}

				if (strcmp(aComment, "MODELINDEX") == 0)
				{// MODELINDEXで設定するモデル番号読み込み

					fscanf(pFile, "%s", &aComment[0]);	// =の分
					fscanf(pFile, "%d", &nModelIdx);	// 設定するモデル番号
				}

				if (strcmp(aComment, "PARENT_FILENUMBER") == 0)
				{// PARENT_FILENUMBERで親にするキャラクターファイル番号読み込み

					fscanf(pFile, "%s", &aComment[0]);	// =の分
					fscanf(pFile, "%d", &nParentFileNumber);	// キャラクターファイル番号
				}

				if (strcmp(aComment, "PARENT_MODELINDEX") == 0)
				{// PARENT_MODELINDEXで親にするモデル番号読み込み

					fscanf(pFile, "%s", &aComment[0]);	// =の分
					fscanf(pFile, "%d", &nParentModelIdx);	// 設定するモデル番号
				}
			}// END_PARENTSETのかっこ

			// 原点設定
			m_pObjChara[nFileNumber]->GetModel()[nModelIdx]->SetParent(m_pObjChara[nParentFileNumber]->GetModel()[nParentModelIdx]);
		}

		if (strcmp(aComment, "END_SCRIPT") == 0)
		{// 終了文字でループを抜ける
			break;
		}
	}

	// ファイルを閉じる
	fclose(pFile);

}

//==========================================================================
// プレイヤー毎のパーツインデックス番号設定
//==========================================================================
void CPlayerUnion::SetPlayerByPartsIdx(int nPartsIdx, int nPlayerIdx)
{
	m_nPartsIdx[nPartsIdx] = nPlayerIdx;
	m_nInputSuperAtkIdx = nPlayerIdx;
}

//==========================================================================
// 移動の操作するインデックス番号設定
//==========================================================================
void CPlayerUnion::SetControllMoveIdx(int nIdx)
{
	m_nControllMoveIdx = nIdx;
}

//==========================================================================
// モデルインデックスからパーツのインデックス取得
//==========================================================================
int CPlayerUnion::GetModelIdxtFromPartsIdx(int nModelIdx)
{
	for (int nParts = 0; nParts < mylib_const::MAX_PLAYER; nParts++)
	{
		for (int i = 0; i < static_cast<int>(m_nModelIdx[nParts].size()); i++)
		{
			if (m_nModelIdx[nParts][i] != nModelIdx)
			{
				continue;
			}

			return nParts;
		}
	}
	return 0;
}

//==========================================================================
// 状態取得
//==========================================================================
int CPlayerUnion::GetState(void)
{
	return m_state;
}