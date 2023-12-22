//=============================================================================
// 
//  チュートリアル処理 [tutorial.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "tutorial.h"
#include "input.h"
#include "fade.h"
#include "renderer.h"
#include "calculation.h"
#include "debugproc.h"
#include "player.h"
#include "sound.h"
#include "tutorialstep.h"
#include "tutorialtext.h"
#include "tutorialplayer.h"
#include "compactcore.h"
#include "enemymanager.h"
#include "tutorialmanager.h"
#include "enemybase.h"
#include "bulletmanager.h"
#include "limitereamanager.h"
#include "limitarea.h"
#include "stage.h"
#include "camera.h"

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================
CTutorialStep *CTutorial::m_pStep = nullptr;					// ステップ
bool CTutorial::m_bMovingPlayer = false;						// プレイヤーが動いてる判定
CTutorialManager *CTutorial::m_pTutorialManager = nullptr;			// チュートリアルマネージャのオブジェクト
CEnemyManager *CTutorial::m_pEnemyManager = nullptr;				// 敵マネージャー
CEnemyBase *CTutorial::m_pEnemyBase = nullptr;						// 敵拠点
CBulletManager *CTutorial::m_pBulletManager = nullptr;				// 弾マネージャのオブジェクト
CLimitAreaManager *CTutorial::m_pLimitEreaManager = nullptr;		// エリア制限マネージャのオブジェクト
CLimitArea *CTutorial::m_pLimitArea = nullptr;						// エリア制限のオブジェクト
CStage *CTutorial::m_pStage = nullptr;								// ステージのオブジェクト

//==========================================================================
// コンストラクタ
//==========================================================================
CTutorial::CTutorial()
{
	// 値のクリア
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		m_apPlayer[i] = nullptr;	// プレイヤーのオブジェクト
	}

	m_pText = nullptr;
}

//==========================================================================
// デストラクタ
//==========================================================================
CTutorial::~CTutorial()
{

}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CTutorial::Init(void)
{
	// 各種変数の初期化

	// 初期化処理
	if (FAILED(CScene::Init()))
	{// 失敗した場合
		return E_FAIL;
	}

	// BGM再生
	CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_BGM_GAME);

	//**********************************
	// ステップ
	//**********************************
	m_pStep = CTutorialStep::Create();

	if (m_pStep == nullptr)
	{// NULLだったら
		return E_FAIL;
	}
	
	//**********************************
	// テキスト
	//**********************************
	m_pText = CTutorialText::Create();

	if (m_pText == nullptr)
	{// NULLだったら
		return E_FAIL;
	}

	//**********************************
	// チュートリアルマネージャの拠点
	//**********************************
	m_pTutorialManager = CTutorialManager::Create();

	if (m_pTutorialManager == nullptr)
	{
		return E_FAIL;
	}

	//**********************************
	// エリア制限マネージャ
	//**********************************
	m_pLimitEreaManager = CLimitAreaManager::Create();

	if (m_pLimitEreaManager == nullptr)
	{// NULLだったら
		return E_FAIL;
	}

	//**********************************
	// 敵の拠点
	//**********************************
	m_pEnemyBase = CEnemyBase::Create("data\\TEXT\\enemydata\\base.txt");

	if (m_pEnemyBase == nullptr)
	{
		return E_FAIL;
	}

	//**********************************
	// 敵マネージャ
	//**********************************
	m_pEnemyManager = CEnemyManager::Create("data\\TEXT\\enemydata\\manager.txt");

	if (m_pEnemyManager == nullptr)
	{// NULLだったら
		return E_FAIL;
	}

	//**********************************
	// 弾マネージャ
	//**********************************
	m_pBulletManager = CBulletManager::Create();

	if (m_pBulletManager == nullptr)
	{// NULLだったら
		return E_FAIL;
	}

	//**********************************
	// ステージ(地面)
	//**********************************
	m_pStage = CStage::Create("data\\TEXT\\stage\\info.txt");

	if (m_pStage == nullptr)
	{// NULLだったら
		return E_FAIL;
	}

	CManager::GetInstance()->GetCamera()->Reset(CScene::MODE_TUTORIAL);

	//**********************************
	// エリア制限
	//**********************************
	CLimitArea::sLimitEreaInfo info;
	info.fMaxX = 13000.0f;
	info.fMaxZ = 1200.0f;
	info.fMinX = -1200.0f;
	info.fMinZ = -1200.0f;
	m_pLimitArea = CLimitArea::Create(info);

	if (m_pLimitArea == nullptr)
	{// NULLだったら
		return E_FAIL;
	}
	m_pLimitArea->SetEnableDisp(false);

	//**********************************
	// プレイヤー
	//**********************************
//#if _DEBUG		
//	//デバッグ用人数
//	int nNumPlayer = 4;
//
//	CManager::GetInstance()->SetNumPlayer(nNumPlayer);
//	for (int i = 0; i < nNumPlayer; i++)
//#else
//	for (int nCntPlayer = 0; nCntPlayer < CManager::GetInstance()->GetNumPlayer(); nCntPlayer++)
//#endif
//	{
//		m_apPlayer[nCntPlayer] = (CTutorialPlayer*)CManager::G[etInstance()->GetScene()->GetPlayer(nCntPlayer);
//
//		if (m_apPlayer[nCntPlayer] == nullptr)
//		{
//			m_apPlayer[nCntPlayer] = (CTutorialPlayer*)CTutorialPlayer::Create(nCntPlayer);
//		}
//
//		m_apPlayer[nCntPlayer]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 100.0f));
//		m_apPlayer[nCntPlayer]->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
//	}

//	CManager::GetInstance()->SetNumPlayer(nNumPlayer);
//	for (int i = 0; i < nNumPlayer; i++)
//#else
//	for (int nCntPlayer = 0; nCntPlayer < CManager::GetInstance()->GetNumPlayer(); nCntPlayer++)
//#endif
	{
		//m_apPlayer[i] = (CTutorialPlayer*)CManager::GetInstance()->GetScene()->GetPlayer(i);

		//if (m_apPlayer[i] == nullptr)
		//{
		//	m_apPlayer[i] = (CTutorialPlayer*)CTutorialPlayer::Create(i);
		//}

		//m_apPlayer[i]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 100.0f));
		//m_apPlayer[i]->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	}

	// 成功
	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CTutorial::Uninit(void)
{
	// プレイヤーの破棄
	for (int i = 0; i < CManager::GetInstance()->GetNumPlayer(); i++)
	{
		m_apPlayer[i] = (CTutorialPlayer*)CManager::GetInstance()->GetScene()->GetPlayer(i);

		if (m_apPlayer[i] == nullptr)
		{
			continue;
		}

		m_apPlayer[i]->Kill();
		m_apPlayer[i] = nullptr;
	}

	// ステップの破棄
	if (m_pStep != nullptr)
	{// メモリの確保が出来ていたら

		m_pStep->Uninit();
		delete m_pStep;
		m_pStep = nullptr;
	}

	// テキストの破棄
	if (m_pText != nullptr)
	{// メモリの確保が出来ていたら
		m_pText = nullptr;
	}

	//=======================
	// ゲーム引用
	if (m_pTutorialManager != nullptr)
	{
		m_pTutorialManager->Uninit();
		delete m_pTutorialManager;
		m_pTutorialManager = nullptr;
	}

	if (m_pBulletManager != nullptr)
	{
		// 終了させる
		m_pBulletManager->Uninit();
		delete m_pBulletManager;
		m_pBulletManager = nullptr;
	}

	if (m_pLimitEreaManager != nullptr)
	{
		// 終了させる
		m_pLimitEreaManager->Uninit();
		delete m_pLimitEreaManager;
		m_pLimitEreaManager = nullptr;
	}

	// ステージの破棄
	if (m_pStage != nullptr)
	{// メモリの確保が出来ていたら

	 // 終了処理
		m_pStage->Uninit();
		delete m_pStage;
		m_pStage = nullptr;
	}

	// 敵マネージャ
	if (m_pEnemyManager != nullptr)
	{
		m_pEnemyManager->Uninit();
		delete m_pEnemyManager;
		m_pEnemyManager = nullptr;
	}

	// 敵の拠点
	if (m_pEnemyBase != nullptr)
	{
		m_pEnemyBase->Uninit();
		delete m_pEnemyBase;
		m_pEnemyBase = nullptr;
	}
	//=======================

	// 終了処理
	CScene::Uninit();
}

//==========================================================================
// 更新処理
//==========================================================================
void CTutorial::Update(void)
{
	// キーボード情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// ゲームパッド情報取得
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	//チュートリアルマネージャ
	if (m_pTutorialManager == nullptr)
	{
		m_pTutorialManager->Update();
	}

	if (m_pStep->IsEndAll() &&
		(pInputKeyboard->GetTrigger(DIK_BACKSPACE) || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_START, 0) == true))
	{
		// モード設定
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_GAME);
	}

	// ステップの破棄
	if (m_pText != nullptr)
	{// メモリの確保が出来ていたら
		m_pText->Update();
	}

	// 敵マネージャの更新処理
	//GetEnemyManager()->Update();

	if (pInputKeyboard->GetTrigger(DIK_L))
	{
		m_pStep->SetStep(m_pStep->GetNowStep());
		// モード設定
		m_pStep->AddStep();
	}

	// ステップの更新処理
	if (m_pStep != nullptr)
	{// nullptrじゃなかったら
		m_pStep->Update();
	}

	if (m_pEnemyManager != nullptr)
	{// NULLだったら

		if (m_pEnemyManager->GetNumAll() == 0)
		{
			//敵がいなくステップが
			if (m_pStep->GetNowStep() == CTutorialStep::STEP_MOVE)
			{
				return;
			}

			if (m_pEnemyBase != nullptr)
			{
				m_pEnemyBase->CreatePos(1, 1, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
			}
		}

		////最終合体ステップに更新してて
		//ResetScene();
	}

	if (GetEnemyManager() != NULL)
	{// 敵マネージャの更新処理
		GetEnemyManager()->Update();
	}

	// 敵の拠点
	if (m_pEnemyBase != NULL)
	{
		m_pEnemyBase->Update();
	}

	// ステージの更新
	if (m_pStage != NULL)
	{
		m_pStage->Update();
	}

	CScene::Update();
}

//==========================================================================
// 描画処理
//==========================================================================
void CTutorial::Draw(void)
{
	// ステップの破棄
	if (m_pText != nullptr)
	{// メモリの確保が出来ていたら
		m_pText->Draw();
	}
}

//==========================================================================
// プレイヤーが動いてる判定
//==========================================================================
void CTutorial::SetEnableMovingPlayer(void)
{
	m_bMovingPlayer = true;
}

//==========================================================================
// プレイヤーが動いてる判定OFF
//==========================================================================
void CTutorial::SetDisableMovingPlayer(void)
{
	m_bMovingPlayer = false;
}

//==========================================================================
// プレイヤーが動いてる判定取得
//==========================================================================
bool CTutorial::IsMovingPlayer(void)
{
	return m_bMovingPlayer;
}

//==========================================================================
// ステップ取得
//==========================================================================
CTutorialStep *CTutorial::GetStep(void)
{
	return m_pStep;
}

//==========================================================================
// プレイヤーの取得
//==========================================================================
CPlayer **CTutorial::GetPlayer(void)
{
	return (CPlayer**)(&m_apPlayer[0]);
}

//==========================================================================
// プレイヤーの取得
//==========================================================================
CPlayer *CTutorial::GetPlayer(int nIdx)
{
	return (CPlayer*)(m_apPlayer[nIdx]);
}

//==========================================================================
// 各ステップ開始時の追加要素
//==========================================================================
void CTutorial::StepInitContent()
{
	CTutorialStep::STEP step = m_pStep->GetNowStep();

	if (!m_pStep->IsUpdate())
	{//更新されていなかった
		return;
	}

	//各ステップの初期要素
	switch (step)
	{
	case CTutorialStep::STEP_WAIT:
		break;

	case CTutorialStep::STEP_MOVE:			//移動
		break;

	case CTutorialStep::STEP_ATTACK:		//攻撃
		break;

	case CTutorialStep::STEP_POWERUP:		//強化
		break;

	case CTutorialStep::STEP_UNDER_UNION:		//簡易合体-合体
		CCompactCore::Create(D3DXVECTOR3(500.0f, 400.0f, 0.0f));
		break;

	case CTutorialStep::STEP_UNDER_FREE:		//簡易合体-自由
		break;

	case CTutorialStep::STEP_UNION_FREE:		//合体-自由
		break;

	case CTutorialStep::STEP_MAX:
		break;

	default:
		break;
	}
}

//==========================================================================
// 弾マネージャの取得
//==========================================================================
CTutorialManager *CTutorial::GetTutorialManager(void)
{
	return m_pTutorialManager;
}

//==========================================================================
// 弾マネージャの取得
//==========================================================================
CBulletManager *CTutorial::GetBulletManager(void)
{
	return m_pBulletManager;
}

//==========================================================================
// エリア制限マネージャマネージャの取得
//==========================================================================
CLimitAreaManager *CTutorial::GetLimitEreaManager(void)
{
	return m_pLimitEreaManager;
}

//==========================================================================
// ステージの取得
//==========================================================================
CStage *CTutorial::GetStage(void)
{
	return m_pStage;
}

//==========================================================================
// 敵マネージャの取得
//==========================================================================
CEnemyManager *CTutorial::GetEnemyManager(void)
{
	return m_pEnemyManager;
}

//==========================================================================
// 敵の拠点
//==========================================================================
CEnemyBase *CTutorial::GetEnemyBase(void)
{
	return m_pEnemyBase;
}

//==========================================================================
// リセット処理
//==========================================================================
void CTutorial::Reset(void)
{
	// ステージの破棄
	if (m_pStage != NULL)
	{// メモリの確保が出来ていたら

	 // 終了処理
		m_pStage->Release();
		delete m_pStage;
		m_pStage = NULL;
	}

	// 敵の拠点
	if (m_pEnemyBase != NULL)
	{
		m_pEnemyBase->Uninit();
		delete m_pEnemyBase;
		m_pEnemyBase = NULL;
	}

	// 敵マネージャ
	if (m_pEnemyManager != NULL)
	{
		m_pEnemyManager->Kill();
	}

	// エリア制限
	if (m_pLimitArea != NULL)
	{
		m_pLimitArea->Uninit();
		m_pLimitArea = NULL;
	}

	// ステージ
	m_pStage = CStage::Create("data\\TEXT\\stage\\boss_info.txt");

	//**********************************
	// 敵の拠点
	//**********************************
	m_pEnemyBase = CEnemyBase::Create("data\\TEXT\\enemydata\\base_boss.txt");
	if (m_pEnemyBase == NULL)
	{// NULLだったら
		return;
	}

	/*if (m_pLimitArea == NULL)
	{
	CLimitArea::sLimitEreaInfo info;
	info.fMaxX = 8200.0f, info.fMaxZ = 785.0f, info.fMinX = -785.0f, info.fMinZ = -785.0f;
	m_pLimitArea = CLimitArea::Create(info);
	}*/
}
