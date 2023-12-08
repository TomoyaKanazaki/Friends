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
#include "player_union.h"

//==========================================================================
// マクロ定義
//==========================================================================
#define PLAYER_CREATE_POSX				(1200.0f)		// スポーンX座標
#define PLAYER_CREATE_POSY				(240.0f)		// スポーンY座標
#define PLAYER_DELETE_POSX				(-1200.0f)		// デスポーンX座標

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================
int CRanking::m_nRandStage = 0;	// ステージのランダムインデックス番号
CRankingScore *CRanking::m_pRankingScore = NULL;	// ランキングスコアのオブジェクト
CPlayerUnion *CRanking::m_pPlayerUnion = NULL;	//
bool CRanking::m_bAllArrival = false;		// 全て到着した判定
const char *CRanking::m_apModelFile = "data\\MODEL\\ranking_00.x";	// モデルのファイル

//==========================================================================
// コンストラクタ
//==========================================================================
CRanking::CRanking()
{
	m_pRankingScore = NULL;	// ランキングスコアのオブジェクト
	m_nCntSwitch = 0;		// 切り替えのカウンター
	m_nCnt = 0;				// 
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
	CObjectX *p = CObjectX::Create(m_apModelFile, D3DXVECTOR3(0.0f, 410.0f, 0.0f));
	p->SetType(CObject::TYPE_OBJECTX);

	// 合体キャラの生成
	UniCharCreate(D3DXVECTOR3(PLAYER_CREATE_POSX, PLAYER_CREATE_POSY, 1300.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

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

	if (m_bAllArrival == true)
	{
		m_nCnt++;

		if (m_nCnt >= 60 * 2)
		{
			// モード設定
			CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RANKING);

			m_nCnt = 60 * 2;
		}
	}

	// 合体キャラの生成
	if (m_pPlayerUnion->GetPosition().x <= PLAYER_DELETE_POSX)
	{
		m_pPlayerUnion->Kill();
		m_pPlayerUnion->Uninit();
		UniCharCreate(D3DXVECTOR3(PLAYER_CREATE_POSX, PLAYER_CREATE_POSY, 1300.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));
	}	

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, 0) == true)
	{
		m_bAllArrival = true;
		m_nCnt = 60 * 2;
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

//==========================================================================
//合体キャラの生成
//==========================================================================
void CRanking::UniCharCreate(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int i = Random(0, CPlayerRanking::MAX - 1);

	switch (i)
	{
	case CPlayerRanking::BODYtoLEG:
		m_nType = CPlayerRanking::BODYtoLEG;
		break;

	case CPlayerRanking::BODYtoARM:
		m_nType = CPlayerRanking::BODYtoARM;
		break;

	case CPlayerRanking::LEGtoARM:
		m_nType = CPlayerRanking::LEGtoARM;
		break;

	case CPlayerRanking::ARMtoARM:
		m_nType = CPlayerRanking::ARMtoARM;
		break;

	default:
		return;
	}

	m_pPlayerUnion = CPlayerRanking::Create(pos, rot, m_nType);
}

//==========================================================================
// 到着設定ON
//==========================================================================
CPlayerUnion *CRanking::GetPlayerUnion(void)
{
	return m_pPlayerUnion;
}
