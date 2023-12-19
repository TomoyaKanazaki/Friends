//==========================================
//
//  リザルトメッセージ(result_message.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "result_message.h"
#include "manager.h"
#include "texture.h"
#include "camera.h"
#include "message_lose.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 DIFF_POS = D3DXVECTOR3(0.0f, 0.0f, 40.0f); // 位置
	const D3DXVECTOR3 MESSAGE_SIZE = D3DXVECTOR3(6.0f, 6.0f, 0.0f); // サイズ
}

//==========================================
//  コンストラクタ
//==========================================
CResultMessage::CResultMessage()
{

}

//==========================================
//  デストラクタ
//==========================================
CResultMessage::~CResultMessage()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CResultMessage::Init(void)
{
	// 初期化処理
	HRESULT hr = CLogo::Init();

	// タイプの設定
	SetType(CObject::TYPE_OBJECT3D);

	//ロゴの位置を設定
	SetPosition(CManager::GetInstance()->GetCamera()->GetPositionV() + DIFF_POS);

	// ロゴのサイズを設定
	SetSize(MESSAGE_SIZE);

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CResultMessage::Uninit(void)
{
	CLogo::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CResultMessage::Update(void)
{
	CLogo::Update();
}

//==========================================
//  描画処理
//==========================================
void CResultMessage::Draw(void)
{
	CLogo::Draw();
}

//==========================================
//  生成処理
//==========================================
CResultMessage* CResultMessage::Create(bool bClear)
{
	// 変数宣言
	CResultMessage* pMessage = nullptr;

	// インスタンス生成
	if (bClear) { pMessage = nullptr; }
	else { pMessage = DEBUG_NEW CMessageLose; }

	// NULLチェック
	if (pMessage == nullptr) { return nullptr; }

	// 初期化処理
	pMessage->Init();

	// 値を返す
	return pMessage;
}
