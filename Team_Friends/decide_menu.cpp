//==========================================================================
// 
//  人数選択メニュー(decide_menu.cpp)
//  Author : 橋本 賢太
// 
//==========================================================================
#include "decide_menu.h"
#include "decide_door.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "object2D.h"
#include "objectX.h"
#include "calculation.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "debugproc.h"
#include "fog.h"
#include "player_title.h"
#include "3D_effect.h"
#include "number.h"

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================
CPlayerTitle *CDecideMenu::m_apPlayer[VTXSELECT_MAX] = {};					// マネージャのオブジェクト

//==========================================================================
//  定数定義
//==========================================================================
namespace
{
	const D3DXVECTOR3 POS_UI = D3DXVECTOR3(0.0f, 1000.0f, 0.0f); // UIの位置
	const int ALPHATIME = 60; // 不透明度更新の時間
	const D3DXVECTOR3 POS_SELECT = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // 選択肢の基準位置
	const float LAMP_POS_Y = 280.0f; // ランプのY座標
	const float LAMP_POS_Z = 200.0f; // ランプのZ座標
	const float LENGTH_SELECT = 192.0f; // ランプのk間隔
	const float SCALE_SELECT = 0.15f; // 選択肢の倍率
	const float PLAYER_SPEED = 5.0f; // プレイヤーの移動量
	const float PLAYER_TARGET = 500.0f; // プレイヤーの座標
	const float TEX_U = 0.1f; // Uの分割
	const float NUMBER_UI_POS_X = -140.5f; // 数字のUIのX座標
	const float NUMBER_UI_POS_Y = 415.0f; // 数字のUIのY座標
	const float NUMBER_UI_POS_Z = 200.0f; // 数字のUIのZ座標
	const float NUMBER_UI_SCALE = 0.15f; // 数字のUIの倍率

	const float ELECBORAD_UI_POS_X = 10.0f; // 電光掲示板のUIのX座標
	const float ELECBORAD_UI_POS_Y = -10.0f; // 数字のUIを基準に電光掲示板のUIのY座標
	const float ELECBORAD_UI_SCALE = 0.35f; // 電光掲示板のUIの倍率


	const char* m_apTextureFile_Number = "data\\TEXTURE\\number\\degital_01.png";
	const char* m_apTextureFile_Elecborad = "data\\TEXTURE\\number\\gowait.png";

	// テクスチャのファイル
	const char* m_apModelFile_Select = "data\\MODEL\\gate\\gate_lamp.x";
}

//==========================================================================
//  コンストラクタ
//==========================================================================
CDecideMenu::CDecideMenu(int nPriority) : CObject(nPriority),
	m_nCntAlpha(0),
	m_nNowSelect(0)
{
	memset(&m_pNumber3D[0], NULL, sizeof(m_pNumber3D)); // オブジェクト2Dのオブジェクト
	memset(&m_pElecboard3D[0], NULL, sizeof(m_pElecboard3D)); // オブジェクト2Dのオブジェクト
	memset(&m_pObj3D[0], NULL, sizeof(m_pObj3D)); // オブジェクト2Dのオブジェクト
	memset(&m_pSelectX[0], NULL, sizeof(m_pSelectX)); // 選択肢のオブジェクト
	m_pDecideDoor = nullptr;	// ドアのオブジェクト
	m_nTexIdx_Select = 0;

	// プレイヤーポインタの初期化
	for (int nCnt = 0; nCnt < VTXSELECT_MAX; ++nCnt)
	{
		m_apPlayer[nCnt] = nullptr;
	}
}

//==========================================================================
//  デストラクタ
//==========================================================================
CDecideMenu::~CDecideMenu()
{

}

//==========================================================================
//  初期化処理
//==========================================================================
HRESULT CDecideMenu::Init(void)
{
	// 種類の設定
	SetType(TYPE_OBJECT3D);

	// 選択対象の生成
	CreateSelect();

	// プレイヤーの生成
	CretePlayer();

	CreateNumber();

	CreateElecboard();

	// ドア生成
	m_pDecideDoor = CDecideDoor::Create();

	for (int nCnt = 0; nCnt < VTX_MAX; nCnt++)
	{
		SetValue(m_nNowSelect + 1);
	}

	return S_OK;
}

//==========================================================================
//  終了処理
//==========================================================================
void CDecideMenu::Uninit(void)
{
	for (int nCntSelect = 0; nCntSelect < VTX_MAX; nCntSelect++)
	{
		if (m_pNumber3D[nCntSelect] != NULL)
		{// NULLじゃなかったら

		 // 終了処理
			m_pNumber3D[nCntSelect]->Uninit();
			delete m_pNumber3D[nCntSelect];
			m_pNumber3D[nCntSelect] = NULL;
		}
	}

	for (int nCntSelect = 0; nCntSelect < VTX_MAX; nCntSelect++)
	{
		if (m_pElecboard3D[nCntSelect] != NULL)
		{// NULLじゃなかったら

		 // 終了処理
			m_pElecboard3D[nCntSelect] = NULL;
		}
	}

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
		if (m_pSelectX[nCntSelect] != NULL)
		{// NULLじゃなかったら

			// 終了処理
			m_pSelectX[nCntSelect] = NULL;
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

//==========================================================================
//  更新処理
//==========================================================================
void CDecideMenu::Update(void)
{
	for (int nCntSelect = 0; nCntSelect < VTX_MAX; nCntSelect++)
	{
		if (m_pNumber3D[nCntSelect] == NULL)
		{// NULLだったら
			continue;
		}

		// 値の設定処理
		for (int nCnt = 0; nCnt < VTX_MAX; nCnt++)
		{
			SetValue(m_nNowSelect + 1);
		}

		// 頂点情報設定
		m_pNumber3D[nCntSelect]->SetVtx();
	}

	for (int nCntSelect = 0; nCntSelect < VTX_MAX; nCntSelect++)
	{
		if (m_pElecboard3D[nCntSelect] == NULL)
		{// NULLだったら
			continue;
		}

		// 頂点情報設定
		m_pElecboard3D[nCntSelect]->SetVtx();
	}

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
		if (m_pSelectX[nCntSelect] == NULL)
		{// NULLだったら
			continue;
		}

		// 選択肢の更新処理
		UpdateSelect(nCntSelect);

		// 頂点情報設定
		m_pSelectX[nCntSelect]->SetVtx();
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
	if ((pInputGamepad->GetStickSelect(CInputGamepad::STICK_X) == false && pInputGamepad->GetStickMoveL(0).y < 0) ||
		(pInputKeyboard->GetTrigger(DIK_S) == true || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_LEFT, 0)))
	{// 左

		// 左スティックの判定を渡す
		pInputGamepad->SetEnableStickSelect(true, CInputGamepad::STICK_X);

		// パターンNo.を更新
		m_nNowSelect = (m_nNowSelect + (VTXSELECT_MAX - 1)) % VTXSELECT_MAX;

		// サウンド再生
		CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_CURSOR);

		// カウンターリセット
		m_nCntAlpha = 0;

		// 選択肢設定
		if (m_pDecideDoor != nullptr)
		{
			m_pDecideDoor->SetSelect(m_nNowSelect);
		}

	}
	else if (pInputGamepad->GetStickSelect(CInputGamepad::STICK_X) == false && pInputGamepad->GetStickMoveL(0).y > 0 ||
		(pInputKeyboard->GetTrigger(DIK_W) == true || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_RIGHT, 0)))
	{// 右

		// 左スティックの判定を渡す
		pInputGamepad->SetEnableStickSelect(true, CInputGamepad::STICK_X);

		// パターンNo.を更新
		m_nNowSelect = (m_nNowSelect + 1) % VTXSELECT_MAX;

		// サウンド再生
		CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_CURSOR);

		// カウンターリセット
		m_nCntAlpha = 0;

		// 選択肢設定
		if (m_pDecideDoor != nullptr)
		{
			m_pDecideDoor->SetSelect(m_nNowSelect);
		}
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

//==========================================================================
//  描画処理
//==========================================================================
void CDecideMenu::Draw(void)
{

}

//==========================================================================
//  前に進む処理
//==========================================================================
void CDecideMenu::Go(int nIdx)
{
	// 値を取得
	D3DXVECTOR3 move = m_apPlayer[nIdx]->GetMove();

	// 値を代入
	move.z = -PLAYER_SPEED;

	// 値を適用
	m_apPlayer[nIdx]->SetMove(move);
}

//==========================================================================
//  後ろに下がる処理
//==========================================================================
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

//==========================================================================
//  生成処理
//==========================================================================
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

//==========================================================================
//  選択肢の更新処理
//==========================================================================
void CDecideMenu::UpdateSelect(int nCntSelect)
{
	// 色
	D3DXCOLOR col = mylib_const::DEFAULT_COLOR;

	if (m_nNowSelect >= nCntSelect)
	{
		col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	}
	else
	{
		col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}

	D3DXVECTOR3 pos = m_pSelectX[nCntSelect]->GetPosition();
	pos.z -= 30.0f;

	for (int i = 0; i < 4; i++)
	{
		CEffect3D::Create(
			pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			col, 200.0f, 2, CEffect3D::MOVEEFFECT_NONE, CEffect3D::TYPE_POINT);
	}
}

//==========================================================================
//  選択対象の生成
//==========================================================================
void CDecideMenu::CreateSelect(void)
{
	// テクスチャのオブジェクト取得
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	for (int nCntSelect = 0; nCntSelect < VTXSELECT_MAX; nCntSelect++)
	{
		// 生成処理
		m_pSelectX[nCntSelect] = CObjectX::Create(m_apModelFile_Select);

		// 種類の設定
		m_pSelectX[nCntSelect]->SetType(TYPE_OBJECTX);

		// 位置設定
		D3DXVECTOR3 pos = POS_SELECT;
		pos.x -= 1.5f * LENGTH_SELECT;
		pos.x += LENGTH_SELECT * nCntSelect;
		pos.y += LAMP_POS_Y;
		pos.z += LAMP_POS_Z;
		m_pSelectX[nCntSelect]->SetPosition(pos);

		// 色設定
		m_pSelectX[nCntSelect]->SetColor(mylib_const::DEFAULT_COLOR);
	}
}

//==========================================================================
//  プレイヤーの生成
//==========================================================================
void CDecideMenu::CretePlayer(void)
{
	// プレイヤーの生成
	for (int nCnt = 0; nCnt < VTXSELECT_MAX; ++nCnt)
	{
		// UIの位置を取得する
		D3DXVECTOR3 pos = m_pSelectX[nCnt]->GetPosition();

		pos.y -= LAMP_POS_Y;
		
		// 初期位置を補正
		pos.z = PLAYER_TARGET;

		// 生成
		m_apPlayer[nCnt] = CPlayerTitle::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
}

//==========================================================================
//  選択対象の生成
//==========================================================================
void CDecideMenu::CreateNumber(void)
{

	for (int nCntSelect = 0; nCntSelect < VTX_MAX; nCntSelect++)
	{
		// 生成処理
		m_pNumber3D[nCntSelect] = CNumber::Create(CNumber::OBJECTTYPE_3D, 8);

		switch (nCntSelect)
		{
		case VTX_TEXT:

			// テクスチャの割り当て
			m_nTexIdx_Number = CManager::GetInstance()->GetTexture()->Regist(m_apTextureFile_Number);

			m_pNumber3D[nCntSelect]->BindTexture(m_nTexIdx_Number);

			m_pNumber3D[nCntSelect]->SetSize3D(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx_Number).x / 10 * NUMBER_UI_SCALE,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx_Number).y * NUMBER_UI_SCALE,
				0.0f));

		default:
			break;
		}

		// 位置設定
		D3DXVECTOR3 pos = POS_SELECT;
		pos.x += NUMBER_UI_POS_X;
		pos.y += NUMBER_UI_POS_Y;
		pos.z += NUMBER_UI_POS_Z;
		m_pNumber3D[nCntSelect]->SetPosition(pos);

		// 色設定
		m_pNumber3D[nCntSelect]->SetColor(mylib_const::DEFAULT_COLOR);

		// 種類の設定
		m_pNumber3D[nCntSelect]->SetType(TYPE_OBJECT3D);
	}
}

//==========================================================================
//  選択対象の生成
//==========================================================================
void CDecideMenu::CreateElecboard(void)
{

	for (int nCntSelect = 0; nCntSelect < VTX_UI_MAX; nCntSelect++)
	{
		// 生成処理
		m_pElecboard3D[nCntSelect] = CObject3D::Create(8);

		// テクスチャの割り当て
		m_nTexIdx_Elecborad[nCntSelect] = CManager::GetInstance()->GetTexture()->Regist(m_apTextureFile_Elecborad);

		m_pElecboard3D[nCntSelect]->BindTexture(m_nTexIdx_Elecborad[nCntSelect]);

		switch (nCntSelect)
		{
		case VTX_UI_ELECBORAD:
			m_pElecboard3D[nCntSelect]->SetSize(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx_Elecborad[nCntSelect]).x * ELECBORAD_UI_SCALE,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx_Elecborad[nCntSelect]).y * ELECBORAD_UI_SCALE,
				0.0f));

		default:
			break;
		}

		// 位置設定
		D3DXVECTOR3 pos = POS_SELECT;
		pos.x += ELECBORAD_UI_POS_X;
		pos.y += NUMBER_UI_POS_Y + ELECBORAD_UI_POS_Y;
		pos.z += NUMBER_UI_POS_Z;
		m_pElecboard3D[nCntSelect]->SetPosition(pos);

		// 色設定
		m_pElecboard3D[nCntSelect]->SetColor(mylib_const::DEFAULT_COLOR);

		// 種類の設定
		m_pElecboard3D[nCntSelect]->SetType(TYPE_OBJECT3D);
	}
}

//==========================================================================
//  選択対象の生成
//==========================================================================
void CDecideMenu::SetValue(int nNowPlayer)
{
	for (int nCntSelect = 0; nCntSelect < VTX_MAX; nCntSelect++)
	{
		// テクスチャポインタ取得
		D3DXVECTOR2 *pTex = m_pNumber3D[nCntSelect]->GetTex();

		// テクスチャ座標の設定
		pTex[0] = D3DXVECTOR2(nNowPlayer * TEX_U, 0.0f);
		pTex[1] = D3DXVECTOR2(nNowPlayer * TEX_U + TEX_U, 0.0f);
		pTex[2] = D3DXVECTOR2(nNowPlayer * TEX_U, 1.0f);
		pTex[3] = D3DXVECTOR2(nNowPlayer * TEX_U + TEX_U, 1.0f);

		// 頂点設定
		m_pNumber3D[nCntSelect]->SetVtx();
	}
}

//==========================================================================
//  プレイヤーの生成
//==========================================================================
CPlayerTitle *CDecideMenu::GetPlayerTitle(int Cnt)
{
	return m_apPlayer[Cnt];
}
