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
#include "title_logo.h"
#include "fog_title.h"

//==========================================================================
// コンストラクタ
//==========================================================================
CTitle::CTitle()
{
	// 値のクリア
	m_nCntSwitch = 0;		// 切り替えのカウンター
	m_pLogo = nullptr;
	m_pFog = nullptr;
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

	//タイトルロゴの表示
	if (m_pLogo == nullptr)
	{
		m_pLogo = CTitleLogo::Create();
	}

	//フォグを生成
	if (m_pFog == nullptr)
	{
		m_pFog = DEBUG_NEW CFog_Title;
		m_pFog->Init();
	}

	// 成功
	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CTitle::Uninit(void)
{
	//フォグを破棄
	if (m_pFog != nullptr)
	{
		m_pFog->Uninit();
		m_pFog = nullptr;
	}

	// タイトルロゴを破棄
	if (m_pLogo != nullptr)
	{
		m_pLogo = nullptr;
	}

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

	//タイトルロゴが完成していないときは抜ける
	if (!m_pLogo->GetComplete())
	{
		return;
	}

	//フォグの更新
	if (m_pFog != nullptr)
	{
		m_pFog->Update();
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
}

//==========================================================================
// 描画処理
//==========================================================================
void CTitle::Draw(void)
{

}
