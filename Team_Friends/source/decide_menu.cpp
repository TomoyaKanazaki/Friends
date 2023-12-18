//==========================================
// 
//  人数選択メニュー(decide_menu.cpp)
//  Author : Tomoya Kanazaki
// 
//==========================================
#include "decide_menu.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "object2D.h"
#include "calculation.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "debugproc.h"
#include "fog.h"
#include "player_title.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 POS_UI = D3DXVECTOR3(0.0f, 1000.0f, 0.0f); // UIの位置
	const int ALPHATIME = 60; // 不透明度更新の時間
	const D3DXVECTOR3 POS_SELECT = D3DXVECTOR3(0.0f, 30.0f, 0.0f); // 選択肢の基準位置
	const float LENGTH_SELECT = 150.0f; // 選択肢の基準位置
	const float SCALE_SELECT = 0.15f; // 選択肢の倍率
	const float PLAYER_SPEED = 5.0f; // プレイヤーの移動量
	const float PLAYER_TARGET = 500.0f; // プレイヤーの座標

	// テクスチャのファイル
	const char* m_apTextureFile[CDecideMenu::VTX_MAX] =
	{
		"data\\TEXTURE\\decideplayer_text.png",
	};

	// テクスチャのファイル
	const char* m_apTextureFile_Select[CDecideMenu::VTXSELECT_MAX] =
	{
		"data\\TEXTURE\\decideplayer_select01.png",
		"data\\TEXTURE\\decideplayer_select02.png",
		"data\\TEXTURE\\decideplayer_select03.png",
		"data\\TEXTURE\\decideplayer_select04.png",
	};
}

//==========================================
//  コンストラクタ
//==========================================
CDecideMenu::CDecideMenu(int nPriority) : CObject(nPriority),
	m_nCntAlpha(0),
	m_nNowSelect(0)
{
	memset(&m_pObj3D[0], NULL, sizeof(m_pObj3D)); // オブジェクト2Dのオブジェクト
	memset(&m_pSelect3D[0], NULL, sizeof(m_pSelect3D)); // 選択肢のオブジェクト
	memset(&m_nTexIdx[0], 0, sizeof(m_nTexIdx)); // テクスチャのインデックス番号
	memset(&m_nTexIdx_Select[0], 0, sizeof(m_nTexIdx_Select)); // テクスチャのインデックス番号

	// プレイヤーポインタの初期化
	for (int nCnt = 0; nCnt < VTXSELECT_MAX; ++nCnt)
	{
		m_apPlayer[nCnt] = nullptr;
	}
}

//==========================================
//  デストラクタ
//==========================================
CDecideMenu::~CDecideMenu()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CDecideMenu::Init(void)
{
	// 種類の設定
	SetType(TYPE_OBJECT3D);

	// UIの生成
	//CreateUI();

	// 選択対象の生成
	CreateSelect();

	// プレイヤーの生成
	CretePlayer();

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CDecideMenu::Uninit(void)
{
	for (int nCntSelect = 0; nCntSelect < VTX_MAX; nCntSelect++)
	{
		if (m_pObj3D[nCntSelect] != NULL)
		{// NULLじゃなかったら

			// 終了処理
			m_pObj3D[nCntSelect] = NULL;
		}
	}

	for (int nCntSelect = 0; nCntSelect < VTXSELECT_MAX; nCntSelect++)
	{
		if (m_pSelect3D[nCntSelect] != NULL)
		{// NULLじゃなかったら

			// 終了処理
			m_pSelect3D[nCntSelect] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < VTXSELECT_MAX; ++nCnt)
	{
		if (m_apPlayer[nCnt] != nullptr)
		{
			m_apPlayer[nCnt] = nullptr;
		}
	}

	// 情報削除
	Release();
}

//==========================================
//  更新処理
//==========================================
void CDecideMenu::Update(void)
{
	for (int nCntSelect = 0; nCntSelect < VTX_MAX; nCntSelect++)
	{
		if (m_pObj3D[nCntSelect] == NULL)
		{// NULLだったら
			continue;
		}

		// 頂点情報設定
		m_pObj3D[nCntSelect]->SetVtx();
	}

	for (int nCntSelect = 0; nCntSelect < VTXSELECT_MAX; nCntSelect++)
	{
		if (m_pSelect3D[nCntSelect] == NULL)
		{// NULLだったら
			continue;
		}

		// 選択肢の更新処理
		UpdateSelect(nCntSelect);

		// 頂点情報設定
		m_pSelect3D[nCntSelect]->SetVtx();
	}

	if (CManager::GetInstance()->GetFade()->GetState() != CFade::STATE_NONE)
	{// フェード中は抜ける
		return;
	}


	// キーボード情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// ゲームパッド情報取得
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	// 現在の選択肢更新
	if ((pInputGamepad->GetStickSelect(CInputGamepad::STICK_X) == false && pInputGamepad->GetStickMoveL(0).x < 0) ||
		(pInputKeyboard->GetTrigger(DIK_A) == true || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_LEFT, 0)))
	{// 左

		// 左スティックの判定を渡す
		pInputGamepad->SetEnableStickSelect(true, CInputGamepad::STICK_X);

		// パターンNo.を更新
		m_nNowSelect = (m_nNowSelect + (VTXSELECT_MAX - 1)) % VTXSELECT_MAX;

		// サウンド再生
		CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_CURSOR);

		// カウンターリセット
		m_nCntAlpha = 0;
	}
	else if (pInputGamepad->GetStickSelect(CInputGamepad::STICK_X) == false && pInputGamepad->GetStickMoveL(0).x > 0 ||
		(pInputKeyboard->GetTrigger(DIK_D) == true || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_RIGHT, 0)))
	{// 右

		// 左スティックの判定を渡す
		pInputGamepad->SetEnableStickSelect(true, CInputGamepad::STICK_X);

		// パターンNo.を更新
		m_nNowSelect = (m_nNowSelect + 1) % VTXSELECT_MAX;

		// サウンド再生
		CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_CURSOR);

		// カウンターリセット
		m_nCntAlpha = 0;
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, 0))
	{// 決定が押された
		CManager::GetInstance()->SetNumPlayer(m_nNowSelect + 1);

		// ゲームに遷移する
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_GAME);

		return;
	}

	// 移動
	for (int nCnt = 0; nCnt < VTXSELECT_MAX; ++nCnt)
	{
		if (nCnt <= m_nNowSelect)
		{
			if (m_apPlayer[nCnt]->GetPosition().z != 0.0f)
			{
				Go(nCnt);
			}
		}
		else
		{
			if (m_apPlayer[nCnt]->GetPosition().z != PLAYER_TARGET)
			{
				Back(nCnt);
			}
		}
	}

	// デバッグ表示
	CManager::GetInstance()->GetDebugProc()->Print
	(
		"選択人数 : %d\n\n", m_nNowSelect + 1
	);

#ifdef _DEBUG
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_LSHIFT))
	{
		Go(0);
	}
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RSHIFT))
	{
		Back(0);
	}
#endif
}

//==========================================
//  描画処理
//==========================================
void CDecideMenu::Draw(void)
{

}

//==========================================
//  前に進む処理
//==========================================
void CDecideMenu::Go(int nIdx)
{
	// 値を取得
	D3DXVECTOR3 move = m_apPlayer[nIdx]->GetMove();

	// 値を代入
	move.z = -PLAYER_SPEED;

	// 値を適用
	m_apPlayer[nIdx]->SetMove(move);
}

//==========================================
//  後ろに下がる処理
//==========================================
void CDecideMenu::Back(int nIdx)
{
	// 値を取得
	D3DXVECTOR3 move = m_apPlayer[nIdx]->GetMove();

	// 値を代入
	move.z = PLAYER_SPEED;

	// 値を適用
	m_apPlayer[nIdx]->SetMove(move);

	// 目的地を設定
	m_apPlayer[nIdx]->SetTarget(PLAYER_TARGET);
}

//==========================================
//  生成処理
//==========================================
CDecideMenu* CDecideMenu::Create(void)
{
	// 生成用のオブジェクト
	CDecideMenu* pTitleScreen = NULL;

	if (pTitleScreen == NULL)
	{// NULLだったら

		// メモリの確保
		pTitleScreen = DEBUG_NEW CDecideMenu;

		if (pTitleScreen != NULL)
		{// メモリの確保が出来ていたら

			// 初期化処理
			pTitleScreen->Init();
		}

		return pTitleScreen;
	}

	return NULL;
}

//==========================================
//  選択肢の更新処理
//==========================================
void CDecideMenu::UpdateSelect(int nCntSelect)
{
	// 色取得
	D3DXCOLOR col = m_pSelect3D[nCntSelect]->GetColor();

	// 不透明度更新
	if (m_nNowSelect == nCntSelect)
	{
		CuadricCurveComp(col.a, ALPHATIME, 0.3f, 1.0f, m_nCntAlpha);
	}
	else
	{
		col.a = 1.0f;
	}

	// 色設定
	m_pSelect3D[nCntSelect]->SetColor(col);
}

//==========================================
//  UIの生成
//==========================================
void CDecideMenu::CreateUI(void)
{
	// テクスチャのオブジェクト取得
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	for (int nCntSelect = 0; nCntSelect < VTX_MAX; nCntSelect++)
	{
		// 生成処理
		switch (nCntSelect)
		{
		case VTX_TEXT:
			m_pObj3D[nCntSelect] = CObject3D::Create(8);
			break;
		}

		// 種類の設定
		m_pObj3D[nCntSelect]->SetType(TYPE_OBJECT3D);

		// テクスチャの割り当て
		m_nTexIdx[nCntSelect] = pTexture->Regist(m_apTextureFile[nCntSelect]);

		// テクスチャの割り当て
		m_pObj3D[nCntSelect]->BindTexture(m_nTexIdx[nCntSelect]);

		// サイズ取得
		D3DXVECTOR3 size = pTexture->GetImageSize(m_nTexIdx[nCntSelect]);

		// 各種変数の初期化
		switch (nCntSelect)
		{
		case VTX_TEXT:
			size.z = 0.0f;
			m_pObj3D[nCntSelect]->SetSize(size * 0.4f);	// サイズ
			m_pObj3D[nCntSelect]->SetPosition(POS_UI);	// 位置
			m_pObj3D[nCntSelect]->SetColor(mylib_const::DEFAULT_COLOR);	// 色
			break;
		}
	}
}

//==========================================
//  選択対象の生成
//==========================================
void CDecideMenu::CreateSelect(void)
{
	// テクスチャのオブジェクト取得
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	for (int nCntSelect = 0; nCntSelect < VTXSELECT_MAX; nCntSelect++)
	{
		// 生成処理
		m_pSelect3D[nCntSelect] = CObject3D::Create(8);

		// 種類の設定
		m_pSelect3D[nCntSelect]->SetType(TYPE_OBJECT3D);

		// テクスチャの割り当て
		m_nTexIdx_Select[nCntSelect] = pTexture->Regist(m_apTextureFile_Select[nCntSelect]);

		// テクスチャの割り当て
		m_pSelect3D[nCntSelect]->BindTexture(m_nTexIdx_Select[nCntSelect]);

		// サイズ設定
		D3DXVECTOR3 size = pTexture->GetImageSize(m_nTexIdx_Select[nCntSelect]) * SCALE_SELECT;
		size.z = 0.0f;
		m_pSelect3D[nCntSelect]->SetSize(size); // サイズ

		// 位置設定
		D3DXVECTOR3 pos = POS_SELECT;
		pos.x -= 1.5f * LENGTH_SELECT;
		pos.x += LENGTH_SELECT * nCntSelect;
		m_pSelect3D[nCntSelect]->SetPosition(pos);

		// 色設定
		m_pSelect3D[nCntSelect]->SetColor(mylib_const::DEFAULT_COLOR);
	}
}

//==========================================
//  プレイヤーの生成
//==========================================
void CDecideMenu::CretePlayer(void)
{
	// プレイヤーの生成
	for (int nCnt = 0; nCnt < VTXSELECT_MAX; ++nCnt)
	{
		// UIの位置を取得する
		D3DXVECTOR3 pos = m_pSelect3D[nCnt]->GetPosition();
		
		// 初期位置を補正
		pos.z = PLAYER_TARGET;

		// 生成
		m_apPlayer[nCnt] = CPlayerTitle::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
}
