//=============================================================================
// 
//  タイトル処理 [title.cpp]
//  Author : 相馬靜雅
//  Added by 金崎朋弥
// 
//=============================================================================
#include "title.h"
#include "input.h"
#include "fade.h"
#include "renderer.h"
#include "calculation.h"
#include "debugproc.h"
#include "sound.h"
#include "fog.h"
#include "title_logo.h"

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================

//==========================================================================
// コンストラクタ
//==========================================================================
CTitle::CTitle()
{
	// 値のクリア
	m_nCntSwitch = 0;		// 切り替えのカウンター
}

//==========================================================================
// デストラクタ
//==========================================================================
CTitle::~CTitle()
{

}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CTitle::Init(void)
{
	// BGM再生
	CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_BGM_TITLE);

	// 初期化処理
	if (FAILED(CScene::Init()))
	{// 失敗した場合
		return E_FAIL;
	}

	//煙をかける
	Fog::Set(true);

	//フォグの値を設定する
	Fog::SetStart(100.0f);
	Fog::SetEnd(100.0f);
	Fog::SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	//タイトルロゴの表示
	CTitleLogo::Create();

	// 成功
	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CTitle::Uninit(void)
{
	//煙を払う
	Fog::Set(false);

	// 終了処理
	CScene::Uninit();
}

//==========================================================================
// 更新処理
//==========================================================================
void CTitle::Update(void)
{
	CManager::GetInstance()->GetDebugProc()->Print(
		"現在のモード：【タイトル】\n"
		"切り替え：【 F 】\n\n");

	// キーボード情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// ゲームパッド情報取得
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	// 切り替えのカウンター加算
	m_nCntSwitch++;

	if (CManager::GetInstance()->GetFade()->GetState() != CFade::STATE_NONE)
	{// フェード中は抜ける
		return;
	}

	if (m_nCntSwitch <= 120)
	{
		return;
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, 0) == true)
	{
		// モード設定
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_DECIDEPLAYER);
	}

	if (m_nCntSwitch >= 60 * 40)
	{// 自動遷移

		// モード設定
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RANKING);
	}

#ifdef _DEBUG
	if (pInputKeyboard->GetPress(DIK_UP))
	{
		float fLength = Fog::GetEnd();
		Fog::SetEnd(fLength + 30.0f);
	}
	if (pInputKeyboard->GetPress(DIK_DOWN))
	{
		float fLength = Fog::GetEnd();
		Fog::SetEnd(fLength - 30.0f);
	}
	if (pInputKeyboard->GetTrigger(DIK_LEFT))
	{
		Fog::SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	}
	if (pInputKeyboard->GetTrigger(DIK_RIGHT))
	{
		Fog::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
#endif
}

//==========================================================================
// 描画処理
//==========================================================================
void CTitle::Draw(void)
{

}
