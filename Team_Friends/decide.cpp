//==========================================
// 
//  人数選択処理(decide.cpp)
//  Author : Tomoya Kanazaki
// 
//==========================================
#include "decide.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "debugproc.h"
#include "sound.h"
#include "decide_menu.h"

//==========================================
//  コンストラクタ
//==========================================
CDecide::CDecide()
{

}

//==========================================
//  デストラクタ
//==========================================
CDecide::~CDecide()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CDecide::Init(void)
{
	// BGM再生
	CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_BGM_SELECT_NUMBER);

	// 初期化処理
	if (FAILED(CScene::Init()))
	{// 失敗した場合
		return E_FAIL;
	}

	// 選択メニューの生成
	CDecideMenu::Create();

	// 成功
	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CDecide::Uninit(void)
{
	// 終了処理
	CScene::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CDecide::Update(void)
{
	CManager::GetInstance()->GetDebugProc()->Print(
		"現在のモード：【人数決め】\n");

	// キーボード情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// ゲームパッド情報取得
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	if (CManager::GetInstance()->GetFade()->GetState() != CFade::STATE_NONE)
	{// フェード中は抜ける
		return;
	}
}

//==========================================
//  描画処理
//==========================================
void CDecide::Draw(void)
{

}
