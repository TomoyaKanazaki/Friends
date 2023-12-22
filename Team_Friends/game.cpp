//=============================================================================
// 
//  ゲーム処理 [game.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "manager.h"
#include "game.h"
#include "renderer.h"
#include "calculation.h"
#include "debugproc.h"
#include "fade.h"
#include "camera.h"
#include "pause.h"

#include "input.h"
#include "player.h"
#include "enemy.h"
#include "score.h"
#include "timer.h"
#include "map.h"
#include "elevation.h"
#include "sound.h"
#include "edit_enemybase.h"
#include "bulletmanager.h"
#include "itemmanager.h"
#include "stage.h"
#include "compactcore.h"
#include "statuswindow.h"
#include "ultwindow.h"
#include "emergency.h"

#include "enemymanager.h"
#include "player.h"
#include "player_union.h"
#include "enemybase.h"
#include "limitarea.h"
#include "limitereamanager.h"

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================
CScore *CGame::m_pScore = NULL;					// スコアのオブジェクト
CTimer *CGame::m_pTimer = NULL;						// タイマーのオブジェクト
CBulletManager *CGame::m_pBulletManager = NULL;		// 弾マネージャのオブジェクト
CItemManager *CGame::m_pItemManager = nullptr;			// アイテムマネージャのオブジェクト
CLimitAreaManager *CGame::m_pLimitEreaManager = NULL;	// エリア制限マネージャのオブジェクト
CLimitArea *CGame::m_pLimitArea = NULL;					// エリア制限のオブジェクト
CEditEnemyBase *CGame::m_pEditEnemyBase = NULL;		// 敵の拠点エディター
CStage *CGame::m_pStage = NULL;						// ステージのオブジェクト
CGameManager *CGame::m_pGameManager = NULL;			// ゲームマネージャのオブジェクト
CGame::EEditType CGame::m_EditType = EDITTYPE_OFF;		// エディットの種類
CEnemyBase *CGame::m_pEnemyBase = NULL;	// 敵の拠点
CEnemyManager *CGame::m_pEnemyManager = NULL;	// 敵マネージャのオブジェクト
CStatusWindow *CGame::m_pStatusWindow[mylib_const::MAX_PLAYER] = {};	// ステータスウィンドウのオブジェクト
CUltWindow *CGame::m_pUltWindow[mylib_const::MAX_PLAYER] = {};			// 必殺のウィンドウ
bool CGame::m_bEdit = false;				// エディットの判定
bool CGame::m_clear = false;				// クリア判定

//==========================================================================
// コンストラクタ
//==========================================================================
CGame::CGame()
{
	// 値のクリア
}

//==========================================================================
// デストラクタ
//==========================================================================
CGame::~CGame()
{

}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CGame::Init(void)
{
	// エディット判定OFF
	m_bEdit = false;
	m_clear = false;

	// BGM再生
	CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_BGM_GAME);

	// 初期化処理
	if (FAILED(CScene::Init()))
	{// 失敗した場合
		return E_FAIL;
	}

	//**********************************
	// ゲームマネージャ
	//**********************************
	m_pGameManager = CGameManager::Create();


	//**********************************
	// エリア制限マネージャ
	//**********************************
	m_pLimitEreaManager = CLimitAreaManager::Create();

	//**********************************
	// 敵の拠点
	//**********************************
	m_pEnemyBase = CEnemyBase::Create("data\\TEXT\\enemydata\\base.txt");
	if (m_pEnemyBase == NULL)
	{// NULLだったら
		return E_FAIL;
	}

	//**********************************
	// 敵マネージャ
	//**********************************
	m_pEnemyManager = CEnemyManager::Create("data\\TEXT\\enemydata\\manager.txt");
	if (m_pEnemyManager == NULL)
	{// NULLだったら
		return E_FAIL;
	}

	//**********************************
	// プレイヤー
	//**********************************
	for (int nCntPlayer = 0; nCntPlayer < CManager::GetInstance()->GetNumPlayer(); nCntPlayer++)
	{
		CPlayer *pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(nCntPlayer);
		if (pPlayer != NULL)
		{
			pPlayer->SetPosition(D3DXVECTOR3(-500.0f + nCntPlayer * 50.0f, 5000.0f, 0.0f));
			pPlayer->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}

	for (int nCntPlayer = 0; nCntPlayer < mylib_const::MAX_PLAYER; nCntPlayer++)
	{
		bool bJoin = true;
		if (CManager::GetInstance()->GetNumPlayer() <= nCntPlayer)
		{
			bJoin = false;
		}
		m_pStatusWindow[nCntPlayer] = CStatusWindow::Create(D3DXVECTOR3(160.0f + nCntPlayer * 320.0f, 600.0f, 0.0f), bJoin);
	}

	//**********************************
	// 弾マネージャ
	//**********************************
	m_pBulletManager = CBulletManager::Create();


	//**********************************
	// アイテムマネージャ
	//**********************************
	m_pItemManager = CItemManager::Create();


	// ステージ
	m_pStage = CStage::Create("data\\TEXT\\stage\\info.txt");

	// スコアの生成処理
	//m_pScore = CScore::Create(D3DXVECTOR3(1000.0f, 50.0f, 0.0f));

	CManager::GetInstance()->GetCamera()->Reset(CScene::MODE_GAME);

	// BGM再生
	CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_BGM_GAME);

	// 簡易合体コア
	//CCompactCore::Create(D3DXVECTOR3(500.0f, 400.0f, 0.0f));

	CLimitArea::sLimitEreaInfo info;
	info.fMaxX = 13000.0f;
	info.fMaxZ = 1200.0f;
	info.fMinX = -1200.0f;
	info.fMinZ = -1200.0f;
	m_pLimitArea = CLimitArea::Create(info);
	m_pLimitArea->SetEnableDisp(false);
	//CMeshWall::Create(D3DXVECTOR3(0.0f, 0.0f, 1500.0f), mylib_const::DEFAULT_VECTOR3, 200.0f, 200.0f, 8, 1);

	// 進化先設定後リセット
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		CManager::GetInstance()->SetByPlayerPartsType(i, -1);
	}

	// タイマー
	m_pTimer = CTimer::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f));

	CEmergency::Create();

	// 成功
	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CGame::Uninit(void)
{

	// スコアの破棄
	if (m_pScore != NULL)
	{// メモリの確保が出来ていたら

		// 終了処理
		m_pScore->Uninit();

		// メモリの開放
		delete m_pScore;
		m_pScore = NULL;
	}

	// タイマーの破棄
	if (m_pTimer != NULL)
	{
		// 終了処理
		m_pTimer->Uninit();
		delete m_pTimer;
		m_pTimer = NULL;
	}

	if (m_pBulletManager != NULL)
	{
		// 終了させる
		m_pBulletManager->Uninit();
		delete m_pBulletManager;
		m_pBulletManager = NULL;
	}

	if (m_pItemManager != NULL)
	{
		// 終了させる
		m_pItemManager->Uninit();
		delete m_pItemManager;
		m_pItemManager = NULL;
	}

	if (m_pLimitEreaManager != NULL)
	{
		// 終了させる
		m_pLimitEreaManager->Uninit();
		delete m_pLimitEreaManager;
		m_pLimitEreaManager = NULL;
	}

	if (m_pEditEnemyBase != NULL)
	{
		// 終了させる
		m_pEditEnemyBase->Uninit();
		delete m_pEditEnemyBase;
		m_pEditEnemyBase = NULL;
	}

	// ステージの破棄
	if (m_pStage != NULL)
	{// メモリの確保が出来ていたら

		// 終了処理
		m_pStage->Uninit();
		delete m_pStage;
		m_pStage = NULL;
	}

	if (m_pGameManager != NULL)
	{
		// 終了処理
		m_pGameManager->Uninit();
		delete m_pGameManager;
		m_pGameManager = NULL;
	}

	// 敵マネージャ
	if (m_pEnemyManager != NULL)
	{
		m_pEnemyManager->Uninit();
		delete m_pEnemyManager;
		m_pEnemyManager = NULL;
	}

	// 敵の拠点
	if (m_pEnemyBase != NULL)
	{
		m_pEnemyBase->Uninit();
		delete m_pEnemyBase;
		m_pEnemyBase = NULL;
	}

	// 終了処理
	CScene::Uninit();
}

//==========================================================================
// 更新処理
//==========================================================================
void CGame::Update(void)
{
	// ゲームマネージャ
	if (m_pGameManager != NULL)
	{
		// 更新処理
		m_pGameManager->Update();
	}

	CManager::GetInstance()->GetDebugProc()->Print(
		"現在のモード：【ゲーム】\n"
		"切り替え：【 F 】\n\n");

#ifdef _DEBUG
	// クリア判定切り替え
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_V))
	{
		m_clear = !m_clear;
	}
	CManager::GetInstance()->GetDebugProc()->Print
	(
		"今終わると : "
	);
	if (m_clear)
	{
		CManager::GetInstance()->GetDebugProc()->Print
		(
			"成功\n\n"
		);
	}
	else
	{
		CManager::GetInstance()->GetDebugProc()->Print
		(
			"失敗\n\n"
		);
	}
#endif

	// キーボード情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// ゲームパッド情報取得
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

#if 1
	if (m_pScore != NULL &&
		CManager::GetInstance()->GetEdit() == NULL &&
		m_pEnemyManager != NULL &&
		GetEnemyManager()->GetState() != CEnemyManager::STATE_COMBOANIM)
	{
		// スコアの更新処理
		m_pScore->Update();
	}
#endif

#if _DEBUG
	if (pInputKeyboard->GetTrigger(DIK_F4))
	{// F4でエディット切り替え

		// 切り替え
		m_EditType = (EEditType)(((int)m_EditType + 1) % (int)EDITTYPE_MAX);	// 追従の種類

		// リセット
		EditReset();

		// エディット判定ON
		m_bEdit = true;

		switch (m_EditType)
		{
		case CGame::EDITTYPE_OFF:	// 全部オフ
			// エディット判定OFF
			m_bEdit = false;
			break;

		case EDITTYPE_ENEMYBASE:
			if (m_pEditEnemyBase == NULL)
			{// NULLだったら

				// エディットの生成処理
				m_pEditEnemyBase = CEditEnemyBase::Create();
			}
			break;

		}
	}
#endif

	if (GetEnemyManager() != NULL)
	{// 敵マネージャの更新処理
		GetEnemyManager()->Update();
	}

	if (m_pEditEnemyBase != NULL)
	{// 敵の拠点エディターの更新処理
		m_pEditEnemyBase->Update();
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


	// タイマー更新
	if (m_pTimer != NULL &&
		!CManager::GetInstance()->GetPause()->IsPause())
	{
		m_pTimer->Update();
	}

#if _DEBUG

	if (pInputKeyboard->GetTrigger(DIK_F))
	{
		// モード設定
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RESULT);
	}

	if (pInputKeyboard->GetTrigger(DIK_I))
	{
		CCompactCore::Create(D3DXVECTOR3(500.0f, 200.0f, 0.0f));
	}

#endif

	// シーンの更新
	CScene::Update();

}

//==========================================================================
// 描画処理
//==========================================================================
void CGame::Draw(void)
{

}

//==========================================================================
// スコアの取得
//==========================================================================
CScore *CGame::GetScore(void)
{
	return m_pScore;
}

//==========================================================================
// 弾マネージャの取得
//==========================================================================
CBulletManager *CGame::GetBulletManager(void)
{
	return m_pBulletManager;
}

//==========================================================================
// エリア制限マネージャマネージャの取得
//==========================================================================
CLimitAreaManager *CGame::GetLimitEreaManager(void)
{
	return m_pLimitEreaManager;
}

//==========================================================================
// ステージの取得
//==========================================================================
CStage *CGame::GetStage(void)
{
	return m_pStage;
}

//==========================================================================
// ゲームマネージャの取得
//==========================================================================
CGameManager *CGame::GetGameManager(void)
{
	return m_pGameManager;
}

//==========================================================================
// 敵マネージャの取得
//==========================================================================
CEnemyManager *CGame::GetEnemyManager(void)
{
	return m_pEnemyManager;
}

//==========================================================================
// アイテムマネージャの取得
//==========================================================================
CItemManager *CGame::GetItemManager(void)
{
	return m_pItemManager;
}

//==========================================================================
// 敵の拠点
//==========================================================================
CEnemyBase *CGame::GetEnemyBase(void)
{
	return m_pEnemyBase;
}

//==========================================================================
// ステータスウィンドウ
//==========================================================================
CStatusWindow *CGame::GetStatusWindow(int nIdx)
{
	return m_pStatusWindow[nIdx];
}

//==========================================================================
// 必殺のウィンドウ取得
//==========================================================================
CUltWindow *CGame::GetUltWindow(int nIdx)
{
	return m_pUltWindow[nIdx];
}

//==========================================================================
// リセット処理
//==========================================================================
void CGame::Reset(void)
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

	// アイテムマネージャ
	if (m_pItemManager != NULL)
	{
		m_pItemManager->KillAll();
	}

	// エリア制限
	if (m_pLimitArea != NULL)
	{
		m_pLimitArea->Uninit();
		m_pLimitArea = NULL;
	}

	// ステージ
	m_pStage = CStage::Create("data\\TEXT\\stage\\boss_info.txt");

	// ステータスウィンドウ
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		if (m_pStatusWindow[i] == nullptr)
		{
			continue;
		}
		m_pStatusWindow[i]->Kill();
		m_pStatusWindow[i] = nullptr;
	}

	//**********************************
	// 敵の拠点
	//**********************************
	m_pEnemyBase = CEnemyBase::Create("data\\TEXT\\enemydata\\base_boss.txt");
	if (m_pEnemyBase == NULL)
	{// NULLだったら
		return;
	}

	// 必殺ゲージ
	for (int nCntPlayer = 0; nCntPlayer < mylib_const::MAX_PLAYER; nCntPlayer++)
	{
		bool bJoin = true;
		if (CManager::GetInstance()->GetNumPlayer() <= nCntPlayer)
		{
			bJoin = false;
		}
		m_pUltWindow[nCntPlayer] = CUltWindow::Create(D3DXVECTOR3(160.0f + nCntPlayer * 320.0f, 600.0f, 0.0f), bJoin);
	}
}

//==========================================================================
// エディターリセット処理
//==========================================================================
void CGame::EditReset(void)
{
	
	if (m_pEditEnemyBase != NULL)
	{
		// 終了させる
		m_pEditEnemyBase->Release();
		m_pEditEnemyBase->Uninit();
		delete m_pEditEnemyBase;
		m_pEditEnemyBase = NULL;
	}

}
