//=============================================================================
// 
//  チュートリアル処理 [tutorial.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "tutorial.h"
#include "input.h"
#include "fade.h"
#include "renderer.h"
#include "calculation.h"
#include "debugproc.h"
#include "player.h"
#include "sound.h"
#include "tutorialstep.h"
#include "tutorialtext.h"
#include "tutorialplayer.h"
#include "compactcore.h"
#include "enemymanager.h"
#include "enemybase.h"

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================
CTutorialStep *CTutorial::m_pStep = nullptr;	// ステップ
bool CTutorial::m_bMovingPlayer = false;	// プレイヤーが動いてる判定

//==========================================================================
// コンストラクタ
//==========================================================================
CTutorial::CTutorial()
{
	// 値のクリア
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		m_apPlayer[i] = nullptr;	// プレイヤーのオブジェクト
	}

	m_pText = nullptr;
	m_pEnemyManager = nullptr;
	m_pEnemyBase = nullptr;
}

//==========================================================================
// デストラクタ
//==========================================================================
CTutorial::~CTutorial()
{

}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CTutorial::Init(void)
{
	// 各種変数の初期化

	// 初期化処理
	if (FAILED(CScene::Init()))
	{// 失敗した場合
		return E_FAIL;
	}

	// BGM再生
	CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_BGM_GAME);

	//**********************************
	// ステップ
	//**********************************
	m_pStep = CTutorialStep::Create();

	if (m_pStep == nullptr)
	{// NULLだったら
		return E_FAIL;
	}
	
	//**********************************
	// テキスト
	//**********************************
	m_pText = CTutorialText::Create();

	if (m_pText == nullptr)
	{// NULLだったら
		return E_FAIL;
	}

	//**********************************
	// 敵の拠点
	//**********************************
	m_pEnemyBase = CEnemyBase::Create("data\\TEXT\\enemydata\\base.txt");
	
	if (m_pEnemyBase == nullptr)
	{
		return E_FAIL;
	}

	//**********************************
	// 敵マネージャ
	//**********************************
	m_pEnemyManager = CEnemyManager::Create("data\\TEXT\\enemydata\\manager.txt");

	if (m_pEnemyManager == nullptr)
	{// NULLだったら
		return E_FAIL;
	}

	//**********************************
	// プレイヤー
	//**********************************
#if _DEBUG		
	//デバッグ用人数
	int nNumPlayer = 4;

	CManager::GetInstance()->SetNumPlayer(nNumPlayer);
	for (int i = 0; i < nNumPlayer; i++)
#else
	for (int nCntPlayer = 0; nCntPlayer < CManager::GetInstance()->GetNumPlayer(); nCntPlayer++)
#endif
	{
		m_apPlayer[i] = (CTutorialPlayer*)CManager::GetInstance()->GetScene()->GetPlayer(i);

		if (m_apPlayer[i] == nullptr)
		{
			m_apPlayer[i] = (CTutorialPlayer*)CTutorialPlayer::Create(i);
		}

		m_apPlayer[i]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 100.0f));
		m_apPlayer[i]->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	}

	// 成功
	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CTutorial::Uninit(void)
{
	// プレイヤーの破棄
	for (int i = 0; i < CManager::GetInstance()->GetNumPlayer(); i++)
	{
		m_apPlayer[i] = (CTutorialPlayer*)CManager::GetInstance()->GetScene()->GetPlayer(i);

		if (m_apPlayer[i] == nullptr)
		{
			continue;
		}

		m_apPlayer[i]->Kill();
		m_apPlayer[i] = nullptr;
	}

	// ステップの破棄
	if (m_pStep != nullptr)
	{// メモリの確保が出来ていたら

		m_pStep->Uninit();
		delete m_pStep;
		m_pStep = nullptr;
	}

	// テキストの破棄
	if (m_pText != nullptr)
	{// メモリの確保が出来ていたら
		m_pText = nullptr;
	}

	// 敵の拠点
	if (m_pEnemyBase != NULL)
	{
		m_pEnemyBase->Uninit();
		delete m_pEnemyBase;
		m_pEnemyBase = NULL;
	}

	if (m_pEnemyManager != nullptr)
	{// NULLだったら
		m_pEnemyManager->Kill();
		m_pEnemyManager = nullptr;
	}

	// 終了処理
	CScene::Uninit();
}

//==========================================================================
// 更新処理
//==========================================================================
void CTutorial::Update(void)
{
	// キーボード情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// ゲームパッド情報取得
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	if (m_pStep->IsEndAll() &&
		(pInputKeyboard->GetTrigger(DIK_BACKSPACE) || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_START, 0) == true))
	{
		// モード設定
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_GAME);
	}

	// ステップの破棄
	if (m_pText != nullptr)
	{// メモリの確保が出来ていたら
		m_pText->Update();
	}

	// 敵マネージャの更新処理
	//GetEnemyManager()->Update();

	if (pInputKeyboard->GetTrigger(DIK_L))
	{
		m_pStep->SetStep(m_pStep->GetNowStep());
		// モード設定
		m_pStep->AddStep();
	}

	// ステップの更新処理
	if (m_pStep != nullptr)
	{// nullptrじゃなかったら
		m_pStep->Update();
		//ステップ更新フラグ
		m_pStep->IsUpdate();
	}

	if (m_pEnemyBase != nullptr)
	{
		m_pEnemyBase->Update();
	}

	if (m_pEnemyManager != nullptr)
	{// NULLだったら

		if (m_pEnemyManager->GetNumAll() == 0)
		{

		}
	}


	//最終合体ステップに更新してて
	ResetScene();
}

//==========================================================================
// 描画処理
//==========================================================================
void CTutorial::Draw(void)
{
	// ステップの破棄
	if (m_pText != nullptr)
	{// メモリの確保が出来ていたら
		m_pText->Draw();
	}
}

//==========================================================================
// プレイヤーが動いてる判定
//==========================================================================
void CTutorial::SetEnableMovingPlayer(void)
{
	m_bMovingPlayer = true;
}

//==========================================================================
// プレイヤーが動いてる判定OFF
//==========================================================================
void CTutorial::SetDisableMovingPlayer(void)
{
	m_bMovingPlayer = false;
}

//==========================================================================
// プレイヤーが動いてる判定取得
//==========================================================================
bool CTutorial::IsMovingPlayer(void)
{
	return m_bMovingPlayer;
}

//==========================================================================
// ステップ取得
//==========================================================================
CTutorialStep *CTutorial::GetStep(void)
{
	return m_pStep;
}

//==========================================================================
// プレイヤーの取得
//==========================================================================
CPlayer **CTutorial::GetPlayer(void)
{
	return (CPlayer**)(&m_apPlayer[0]);
}

//==========================================================================
// プレイヤーの取得
//==========================================================================
CPlayer *CTutorial::GetPlayer(int nIdx)
{
	return (CPlayer*)(m_apPlayer[nIdx]);
}

//==========================================================================
// 各ステップ開始時の追加要素
//==========================================================================
void CTutorial::StepInitContent()
{
	CTutorialStep::STEP step = m_pStep->GetNowStep();

	if (!m_pStep->IsUpdate())
	{//更新されていなかった
		return;
	}

	//各ステップの初期要素
	switch (step)
	{
	case CTutorialStep::STEP_WAIT:
		break;

	case CTutorialStep::STEP_MOVE:			//移動
		break;

	case CTutorialStep::STEP_ATTACK:		//攻撃
		break;

	case CTutorialStep::STEP_POWERUP:		//強化
		break;

	case CTutorialStep::STEP_UNDER_UNION:		//簡易合体-合体
		CCompactCore::Create(D3DXVECTOR3(500.0f, 400.0f, 0.0f));
		break;

	case CTutorialStep::STEP_UNDER_FREE:		//簡易合体-自由
		break;

	case CTutorialStep::STEP_UNION_FREE:		//合体-自由
		break;

	case CTutorialStep::STEP_MAX:
		break;

	default:
		break;
	}
}
