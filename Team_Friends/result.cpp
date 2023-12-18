//=============================================================================
// 
//  リザルト処理 [result.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "result.h"
#include "input.h"
#include "fade.h"
#include "renderer.h"
#include "calculation.h"
#include "debugproc.h"
#include "player.h"
#include "sound.h"
#include "resultscore.h"
#include "fog.h"

//==========================================
//  定数定義 金崎
//==========================================
namespace
{
	const D3DXCOLOR TARGET_COLOR = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	const float START_LENGTH = 300.0f; // 初期距離
	const float END_LENGTH = 2000.0f; // 目標距離
	const float FUNCTION = 0.02f; //倍率
	const float SWITCH_TIME = 140.0f;
}

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================
CResultScore *CResult::m_pResultScore = NULL;	// リザルトスクリーンのオブジェクト
bool CResult::m_bAllArrival = false;		// 全て到着した判定

//==========================================================================
// コンストラクタ
//==========================================================================
CResult::CResult() :
	m_fLength(END_LENGTH),
	m_col(TARGET_COLOR)
{
	// 値のクリア
	m_bAllArrival = false;	// 全て到着した判定
}

//==========================================================================
// デストラクタ
//==========================================================================
CResult::~CResult()
{

}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CResult::Init(void)
{
	//プレイヤー数をリセット
	CManager::GetInstance()->SetNumPlayer(0);

	// 初期化処理
	if (FAILED(CScene::Init()))
	{// 失敗した場合
		return E_FAIL;
	}

	// BGM再生
	CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_BGM_RESULT);

	// 煙をかける
	Fog::Set(true);

	// フォグの値を設定する
	Fog::SetStart(START_LENGTH);
	Fog::SetEnd(m_fLength);
	Fog::SetCol(m_col);

	// リザルト画面
	m_pResultScore = CResultScore::Create();

	// 成功
	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CResult::Uninit(void)
{
	m_pResultScore = NULL;

	// 終了処理
	CScene::Uninit();
}

//==========================================================================
// 更新処理
//==========================================================================
void CResult::Update(void)
{
	CManager::GetInstance()->GetDebugProc()->Print(
		"現在のモード：【リザルト】\n"
		"切り替え：【 F 】\n\n");

	// キーボード情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// ゲームパッド情報取得
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	static int n = 0;
	n = (n + 1) % 5;
	if (n == 0)
	{
		// モード設定
		//CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_TITLE);
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, 0) == true)
	{
		if (m_bAllArrival == true)
		{
			// モード設定
			CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RANKING);
		}

		if (CManager::GetInstance()->GetFade()->GetState() == CFade::STATE_NONE)
		{
			// 全ての到着処理
			if (m_pResultScore != NULL)
			{
				m_pResultScore->SetAllArrival();
			}
			m_bAllArrival = true;
		}
	}
}

//==========================================================================
// 描画処理
//==========================================================================
void CResult::Draw(void)
{

}

//==========================================================================
// リザルトスクリーンの情報取得
//==========================================================================
CResultScore *CResult::GetResultScore(void)
{
	return m_pResultScore;
}

//==========================================================================
// 到着設定ON
//==========================================================================
void CResult::SetEnableArrival(void)
{
	m_bAllArrival = true;
}
