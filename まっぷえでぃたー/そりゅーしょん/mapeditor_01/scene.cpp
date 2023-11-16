//=============================================================================
// 
//  シーン処理 [scene.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "scene.h"
#include "renderer.h"
#include "calculation.h"
#include "Xload.h"
#include "map.h"
#include "fade.h"
#include "elevation.h"
#include "player.h"
#include "player_union.h"
#include "camera.h"

// 遷移先
#include "game.h"
#include "decideplayer.h"
#include "title.h"
#include "tutorial.h"
#include "result.h"
#include "ranking.h"

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================
CXLoad *CScene::m_pXLoad = NULL;				// Xファイルのオブジェクト
CElevation *CScene::m_pObject3DMesh = NULL;		// オブジェクト3Dメッシュのオブジェクト

//==========================================================================
// コンストラクタ
//==========================================================================
CScene::CScene()
{
	// 変数のクリア
	m_mode = MODE_TITLE;
	memset(&m_pPlayer[0], 0, sizeof(m_pPlayer));
	memset(&m_pMultiCamera[0], NULL, sizeof(m_pMultiCamera));	// カメラのオブジェクト
}

//==========================================================================
// デストラクタ
//==========================================================================
CScene::~CScene()
{

}

//==========================================================================
// 生成処理
//==========================================================================
CScene *CScene::Create(CScene::MODE mode)
{
	// 生成用のオブジェクト
	CScene *pScene = NULL;

	if (pScene == NULL)
	{// NULLだったら

		// 生成処理
		switch (mode)
		{
		case CScene::MODE_TITLE:
			pScene = DEBUG_NEW CTitle;
			break;

		case CScene::MODE_DECIDEPLAYER:
			pScene = DEBUG_NEW CDecidePlayer;
			break;

		case CScene::MODE_TUTORIAL:
			pScene = DEBUG_NEW CTutorial;
			break;

		case CScene::MODE_GAME:
			pScene = DEBUG_NEW CGame;
			break;

		case CScene::MODE_RESULT:
			pScene = DEBUG_NEW CResult;
			break;

		case CScene::MODE_RANKING:
			pScene = DEBUG_NEW CRanking;
			break;
		}

		if (pScene != NULL)
		{// メモリの確保が出来ていたら

			// モードの設定
			pScene->m_mode = mode;
		}

		return pScene;
	}

	return NULL;
}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CScene::Init(void)
{
	HRESULT hr;

	//**********************************
	// Xファイル
	//**********************************
	if (m_pXLoad != NULL)
	{// 確保されていたら
		return E_FAIL;
	}

	// メモリ確保
	m_pXLoad = DEBUG_NEW CXLoad;

	if (m_pXLoad == NULL)
	{// メモリの確保が出来ていなかったら
		return E_FAIL;
	}
	m_pXLoad->Init();

	//**********************************
	// マップの生成
	//**********************************
	if (FAILED(map::Create("data\\TEXT\\edit_info.txt")))
	{// 失敗した場合
		return E_FAIL;
	}

	//**********************************
	// 起伏の地面
	//**********************************
	m_pObject3DMesh = CElevation::Create("data\\TEXT\\elevation_field.txt");

	// 初期化処理
	hr = m_pXLoad->Init();

	if (FAILED(hr))
	{// 初期化処理が失敗した場合
		return E_FAIL;
	}

	// キャラ生成
	for (int nCntPlayer = 0; nCntPlayer < 1; nCntPlayer++)
	{
		m_pPlayer[nCntPlayer] = CPlayer::Create(nCntPlayer);
		if (m_pPlayer[nCntPlayer] == NULL)
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CScene::Uninit(void)
{
	// Xファイルの破棄
	if (m_pXLoad != NULL)
	{// メモリの確保が出来ていたら

		// 終了処理
		m_pXLoad->Uninit();

		// メモリの開放
		delete m_pXLoad;
		m_pXLoad = NULL;
	}

	// プレイヤーの破棄
	for (int nCntPlayer = 0; nCntPlayer < mylib_const::MAX_PLAYER; nCntPlayer++)
	{
		if (m_pPlayer[nCntPlayer] != NULL)
		{// メモリの確保が出来ていたら

			m_pPlayer[nCntPlayer]->Uninit();
			m_pPlayer[nCntPlayer] = NULL;
		}
	}

	// カメラの破棄
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		if (m_pMultiCamera[i] != NULL)
		{// メモリの確保が出来ていたら

			// 終了処理
			m_pMultiCamera[i]->Uninit();
			delete m_pMultiCamera[i];
			m_pMultiCamera[i] = NULL;
		}
	}

}

//==========================================================================
// 更新処理
//==========================================================================
void CScene::Update(void)
{
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		if (m_pMultiCamera[i] == NULL)
		{
			continue;
		}

		// カメラの設定
		m_pMultiCamera[i]->Update();
	}
}

//==========================================================================
// 描画処理
//==========================================================================
void CScene::Draw(void)
{
	
}

//==========================================================================
// シーンのリセット
//==========================================================================
void CScene::ResetScene(void)
{
	//**********************************
	// 破棄フェーズ
	//**********************************
	// プレイヤーの破棄
	for (int nCntPlayer = 0; nCntPlayer < mylib_const::MAX_PLAYER; nCntPlayer++)
	{
		if (m_pPlayer[nCntPlayer] != NULL)
		{// メモリの確保が出来ていたら

			m_pPlayer[nCntPlayer]->Uninit();
			m_pPlayer[nCntPlayer] = NULL;
		}
	}

	// カメラの破棄
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		if (m_pMultiCamera[i] != NULL)
		{// メモリの確保が出来ていたら

			// 終了処理
			m_pMultiCamera[i]->Uninit();
			delete m_pMultiCamera[i];
			m_pMultiCamera[i] = NULL;
		}
	}

	// マップ
	map::Release();

	//**********************************
	// 生成フェーズ
	//**********************************
	// マップ
	if (FAILED(map::Create("data\\TEXT\\edit_info_boss.txt")))
	{// 失敗した場合
		return;
	}

	// カメラ
	if (m_pMultiCamera[0] == NULL)
	{
		m_pMultiCamera[0] = DEBUG_NEW CCamera;
		if (m_pMultiCamera[0] != NULL)
		{// メモリの確保が出来ていたら

			// 初期化処理
			HRESULT hr = m_pMultiCamera[0]->Init();
			if (FAILED(hr))
			{// 初期化処理が失敗した場合
				return;
			}

			// ビューポートの設定
			m_pMultiCamera[0]->SetViewPort(mylib_const::DEFAULT_VECTOR3, D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
		}
	}


	// 合体後プレイヤー生成
	CPlayerUnion::Create();
}

//==========================================================================
// 現在のモード取得
//==========================================================================
CScene::MODE CScene::GetMode(void)
{
	return m_mode;
}

//==========================================================================
// Xファイルの取得
//==========================================================================
CXLoad *CScene::GetXLoad(void)
{
	return m_pXLoad;
}

//==========================================================================
// 3Dオブジェクトの取得
//==========================================================================
CElevation *CScene::GetElevation(void)
{
	return m_pObject3DMesh;
}

//==========================================================================
// プレイヤーの取得
//==========================================================================
CPlayer *CScene::GetPlayer(int nIdx)
{
	return m_pPlayer[nIdx];
}

//==========================================================================
// マルチカメラの取得
//==========================================================================
CCamera **CScene::GetMultiCamera(void)
{
	return &m_pMultiCamera[0];
}

//==========================================================================
// マルチカメラの取得
//==========================================================================
CCamera *CScene::GetMultiCamera(int nIdx)
{
	return m_pMultiCamera[nIdx];
}

//==========================================================================
// プレイヤーの終了
//==========================================================================
void CScene::UninitPlayer(int nIdx)
{
	m_pPlayer[nIdx] = NULL;
}
