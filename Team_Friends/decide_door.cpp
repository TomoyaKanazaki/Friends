//==========================================
// 
//  人数選択メニュー(decide_menu.cpp)
//  Author : Tomoya Kanazaki
// 
//==========================================
#include "decide_door.h"
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
	const char *m_apModelFile_fream = "data\\MODEL\\gate\\gate_frame.x";
	const char *m_apModelFile_door = "data\\MODEL\\gate\\gate_door.x";
}

//==========================================
//  コンストラクタ
//==========================================
CDecideDoor::CDecideDoor(int nPriority) : CObject(nPriority),
m_nNowSelect(0)
{
	memset(&m_pObjX[0], NULL, sizeof(m_pObjX)); // オブジェクト2Dのオブジェクト
	memset(&m_pSelectX[0], NULL, sizeof(m_pSelectX)); // 選択肢のオブジェクト
	memset(&m_nTexIdx_Select[0], 0, sizeof(m_nTexIdx_Select)); // テクスチャのインデックス番号
}

//==========================================
//  デストラクタ
//==========================================
CDecideDoor::~CDecideDoor()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CDecideDoor::Init(void)
{
	// 種類の設定
	SetType(TYPE_OBJECT3D);

	// 選択対象の生成
	CreateSelect();

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CDecideDoor::Uninit(void)
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

	// 情報削除
	Release();
}

//==========================================
//  更新処理
//==========================================
void CDecideDoor::Update(void)
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
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, 0))
	{// 決定が押された
		CManager::GetInstance()->SetNumPlayer(m_nNowSelect + 1);

		// ゲームに遷移する
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_GAME);

		return;
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
void CDecideDoor::Draw(void)
{

}

//==========================================
//  生成処理
//==========================================
CDecideDoor* CDecideDoor::Create(void)
{
	// 生成用のオブジェクト
	CDecideDoor* pTitleScreen = NULL;

	if (pTitleScreen == NULL)
	{// NULLだったら

	 // メモリの確保
		pTitleScreen = DEBUG_NEW CDecideDoor;

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
void CDecideDoor::UpdateSelect(int nCntSelect)
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
//  選択対象の生成
//==========================================
void CDecideDoor::CreateSelect(void)
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