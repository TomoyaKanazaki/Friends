//==========================================
//
//  敗北メッセージ(message_lose.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "message_lose.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  コンストラクタ
//==========================================
CMessageLose::CMessageLose()
{

}

//==========================================
//  デストラクタ
//==========================================
CMessageLose::~CMessageLose()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CMessageLose::Init(void)
{
	// 初期化
	HRESULT hr = CResultMessage::Init();

	// テクスチャの割り当て
	BindTexture(CManager::GetInstance()->GetTexture()->Regist(m_apTextureFile[5]));

	//値を返す
	return hr;
}

//==========================================
//  終了処理
//==========================================
void CMessageLose::Uninit(void)
{
	// 終了
	CResultMessage::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CMessageLose::Update(void)
{
	// 更新
	CResultMessage::Update();
}

//==========================================
//  描画処理
//==========================================
void CMessageLose::Draw(void)
{
	// 描画
	CResultMessage::Draw();
}
