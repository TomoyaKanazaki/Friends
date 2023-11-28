//=============================================================================
// 
//  ランキング処理 [ranking.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "renderer.h"
#include "calculation.h"
#include "debugproc.h"
#include "rankingscore.h"
#include "enemymanager.h"
#include "objectX.h"
#include "player_ranking.h"
#include "player_union.h"

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================
int CRanking::m_nRandStage = 0;	// ステージのランダムインデックス番号
CRankingScore *CRanking::m_pRankingScore = NULL;	// ランキングスコアのオブジェクト
bool CRanking::m_bAllArrival = false;		// 全て到着した判定
const char *CRanking::m_apModelFile = "data\\MODEL\\ranking_00.x";	// モデルのファイル

//==========================================================================
// コンストラクタ
//==========================================================================
CRanking::CRanking()
{
	m_pRankingScore = NULL;	// ランキングスコアのオブジェクト
	m_nCntSwitch = 0;		// 切り替えのカウンター
	m_bAllArrival = false;	// 全て到着した判定
}

//==========================================================================
// デストラクタ
//==========================================================================
CRanking::~CRanking()
{

}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CRanking::Init(void)
{
	// ステージのランダムインデックス番号
	m_nRandStage = Random(1, 3);

	// 初期化処理
	if (FAILED(CScene::Init()))
	{// 失敗した場合
		return E_FAIL;
	}

	// 生成処理
	CObjectX *p = CObjectX::Create(m_apModelFile, D3DXVECTOR3(0.0f, 1000.0f, 0.0f));
	p->SetType(CObject::TYPE_OBJECTX);

	CPlayerRanking::Create(D3DXVECTOR3(-200.0f, 900.0f, 1300.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), CPlayerRanking::BODYtoLEG);

	// ランキングのスコア生成
	m_pRankingScore = CRankingScore::Create();

	// 成功
	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CRanking::Uninit(void)
{
	// ランキングスコアのオブジェクト
	m_pRankingScore = NULL;

	// 終了処理
	CScene::Uninit();
}

//==========================================================================
// 更新処理
//==========================================================================
void CRanking::Update(void)
{
	CManager::GetInstance()->GetDebugProc()->Print(
		"現在のモード：【ランキング】\n"
		"切り替え：【 F 】\n\n");

	// キーボード情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// ゲームパッド情報取得
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	// 切り替えのカウンター加算
	m_nCntSwitch++;

	if (m_nCntSwitch >= 60 * 3600)
	{
		// モード設定
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RANKING);
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, 0) == true)
	{
		if (m_bAllArrival == true)
		{
			// モード設定
			CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RANKING);
		}

		else
		{
			// 全ての到着処理
			//m_pRankingScore->SetAllArrival();
			m_bAllArrival = true;
		}
	}
}

//==========================================================================
// 描画処理
//==========================================================================
void CRanking::Draw(void)
{

}

//==========================================================================
// 到着設定ON
//==========================================================================
void CRanking::SetEnableArrival(void)
{
	m_bAllArrival = true;
}