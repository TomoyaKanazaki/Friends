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
#include "fog.h"
#include "player_title.h"
#include "union_title.h"
#include "enemy.h"
#include "3D_Effect.h"

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

	//モデルの配置位置
	const D3DXVECTOR3 CENTER	= D3DXVECTOR3(0.0f, 0.0f, -2000.0f);
	const D3DXVECTOR3 IN_LEFT	= D3DXVECTOR3(-160.0f, 0.0f, -2900.0f);
	const D3DXVECTOR3 IN_RIGHT	= D3DXVECTOR3(160.0f, 0.0f, -2900.0f);
	const D3DXVECTOR3 OUT_LEFT	= D3DXVECTOR3(-300.0f, 0.0f, -3000.0f);
	const D3DXVECTOR3 OUT_RIGHT	= D3DXVECTOR3(300.0f, 0.0f, -3000.0f);
}
bool CTitle::m_bPressEnter = false;	// エンター押下判定

//==========================================================================
// コンストラクタ
//==========================================================================
CTitle::CTitle() :
m_col(D3DXCOLOR(0.0f, 0.0, 0.0f, 1.0f)),
m_fLength(START_LENGTH)
{
	// 値のクリア
	m_fCnt = 0.0f;		// 切り替えのカウンター
	m_pLogo = nullptr;
	m_nCntEmission = 0;	// 発生物カウンター
	m_pUnionTitle = nullptr;	// タイトルの合体プレイヤーオブジェクト
	m_bPressEnter = false;		// エンター押下判定
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
	// 判定リセット
	m_bPressEnter = false;

	//プレイヤー数をリセット
	CManager::GetInstance()->SetNumPlayer(0);

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

	// 煙をかける
	Fog::Set(true);

	// フォグの値を設定する
	Fog::SetStart(START_LENGTH);
	Fog::SetEnd(m_fLength);
	Fog::SetCol(m_col);

	// プレイヤーを置いてみる
	m_pUnionTitle = CUnionTitle::Create(CENTER);
	CPlayerTitle::Create(IN_RIGHT, D3DXVECTOR3(0.0f, 0.0f, 0.0f), CPlayerTitle::PLAYER_ARM);
	CPlayerTitle::Create(IN_LEFT, D3DXVECTOR3(0.0f, 0.0f, 0.0f), CPlayerTitle::PLAYER_ARM);
	CPlayerTitle::Create(OUT_RIGHT, D3DXVECTOR3(0.0f, 0.0f, 0.0f), CPlayerTitle::PLAYER_LEG);
	CPlayerTitle::Create(OUT_LEFT, D3DXVECTOR3(0.0f, 0.0f, 0.0f), CPlayerTitle::PLAYER_BODY);

	// 進化先設定後リセット
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		CManager::GetInstance()->SetByPlayerPartsType(i, -1);
	}

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

	// タイトルロゴを破棄
	if (m_pLogo != nullptr)
	{
		m_pLogo = nullptr;
	}

	// 合体プレイヤーをnull
	m_pUnionTitle = nullptr;

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

	if (CManager::GetInstance()->GetFade()->GetState() != CFade::STATE_NONE)
	{// フェード中は抜ける
		return;
	}

	//タイトルロゴが完成していないときは抜ける
	if (m_pLogo == nullptr || !m_pLogo->GetComplete())
	{
		return;
	}

	//フォグを引く
	WhiteOut();

	// 発生物のインターバル
	int nIntervalEmission = 16;
	int nLife = 360;
	if (m_bPressEnter)
	{
		nIntervalEmission = 4;
		nLife = 90;
	}

	m_nCntEmission = (m_nCntEmission + 1) % nIntervalEmission;	// 発生物カウンター

	if (m_nCntEmission == 0)
	{
		int nWidth = 20;
		float fWidthDistance = 100.0f;
		for (int i = 0; i < nWidth; i++)
		{
			D3DXVECTOR3 pos = CENTER;
			pos.x = ((static_cast<float>(nWidth) * 0.5f) * fWidthDistance) - fWidthDistance * i;
			pos.y = CENTER.y + 50.0f;
			pos.z += 400.0f + Random(-50, 50);

			D3DXVECTOR3 posDest = pos;
			posDest.z -= 1800.0f;
			posDest.y = 0.0f;
			posDest.x += Random(-20, 20) * 10.0f;

			float fColRand = Random(-20, 20) * 0.01f;
			CEffect3D *pEffect = CEffect3D::Create(
				pos,
				mylib_const::DEFAULT_VECTOR3,
				D3DXCOLOR(0.6f + fColRand, 0.6f + fColRand, 0.6f + fColRand, 1.0f),
				150.0f + (float)Random(-5, 5) * 10.0f,
				nLife,
				CEffect3D::MOVEEFFECT_ADD,
				CEffect3D::TYPE_SMOKEBLACK);

			// 目標の位置設定
			pEffect->SetPositionDest(posDest);
			pEffect->SetRotation(D3DXVECTOR3(0.0f, GetRandomCircleValue(), 0.0f));
		}
	}

	// 切り替えのカウンター加算
	m_fCnt += CManager::GetInstance()->GetDeltaTime();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, 0) == true)
	{
#if 1
		if (m_pUnionTitle != nullptr)
		{
			m_pUnionTitle->SetEnablePressEnter();
		}
#else
		// モード設定
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_DECIDE);
#endif
	}

	if (m_fCnt >= SWITCH_TIME)
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

//==========================================
//  フォグを引く処理
//==========================================
void CTitle::WhiteOut()
{
	// 目標距離まで引き伸ばす
	m_fLength += (END_LENGTH - m_fLength) * FUNCTION;

	// 目標色まで補正する
	m_col += (TARGET_COLOR - m_col) * FUNCTION;

	// 距離を適用する
	Fog::SetEnd(m_fLength);

	// 色を適用する
	Fog::SetCol(m_col);

#ifdef _DEBUG
	// キーボード情報取得
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	if (pInputKeyboard->GetTrigger(DIK_1))
	{
		// fog消し
		Fog::Set(false);
	}
	if (pInputKeyboard->GetTrigger(DIK_2))
	{
		// fog焚き
		Fog::Set(true);
	}

	if (pInputKeyboard->GetTrigger(DIK_3))
	{
		// モード設定
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_DECIDE);
	}

	if (pInputKeyboard->GetTrigger(DIK_4))
	{// 自動遷移
		// モード設定
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RANKING);
	}
#endif
}
