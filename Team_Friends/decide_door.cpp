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
#include "objectX.h"
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
		if (m_pObjX[nCntSelect] != NULL)
		{// NULLじゃなかったら

		 // 終了処理
			m_pObjX[nCntSelect] = NULL;
		}
	}

	for (int nCntSelect = 0; nCntSelect < MODELSELECT_MAX; nCntSelect++)
	{
		if (m_pSelectX[nCntSelect] != NULL)
		{// NULLじゃなかったら

		 // 終了処理
			m_pSelectX[nCntSelect] = NULL;
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
	

	for (int nCntSelect = 0; nCntSelect < MODELSELECT_MAX; nCntSelect++)
	{
		if (m_pSelectX[nCntSelect] == NULL)
		{// NULLだったら
			continue;
		}

		// 選択肢の更新処理
		UpdateSelect(nCntSelect);
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
		m_nNowSelect = (m_nNowSelect + (MODELSELECT_MAX - 1)) % MODELSELECT_MAX;

		// サウンド再生
		CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_CURSOR);
	}
	else if (pInputGamepad->GetStickSelect(CInputGamepad::STICK_X) == false && pInputGamepad->GetStickMoveL(0).x > 0 ||
		(pInputKeyboard->GetTrigger(DIK_D) == true || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_RIGHT, 0)))
	{// 右

	 // 左スティックの判定を渡す
		pInputGamepad->SetEnableStickSelect(true, CInputGamepad::STICK_X);

		// パターンNo.を更新
		m_nNowSelect = (m_nNowSelect + 1) % MODELSELECT_MAX;

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

	
}

//==========================================
//  選択対象の生成
//==========================================
void CDecideDoor::CreateSelect(void)
{
	// テクスチャのオブジェクト取得
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	for (int nCntSelect = 0; nCntSelect < MODELSELECT_MAX; nCntSelect++)
	{
		// 生成処理
		m_pSelectX[nCntSelect] = CObjectX::Create();

		// 種類の設定
		m_pSelectX[nCntSelect]->SetType(TYPE_OBJECT3D);

		// サイズ設定
		D3DXVECTOR3 size = pTexture->GetImageSize(m_nTexIdx_Select[nCntSelect]) * SCALE_SELECT;
		size.z = 0.0f;
		m_pSelectX[nCntSelect]->SetSize(size); // サイズ

												// 位置設定
		D3DXVECTOR3 pos = POS_SELECT;
		pos.x -= 1.5f * LENGTH_SELECT;
		pos.x += LENGTH_SELECT * nCntSelect;
		m_pSelectX[nCntSelect]->SetPosition(pos);

		// 色設定
		m_pSelectX[nCntSelect]->SetColor(mylib_const::DEFAULT_COLOR);
	}
}