//==========================================
//
//  メカニオンのロゴ(logo_mekanion.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "logo_mekanion.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "input.h"

//==========================================
//  コンストラクタ
//==========================================
CLogo_Meka::CLogo_Meka()
{

}

//==========================================
//  デストラクタ
//==========================================
CLogo_Meka::~CLogo_Meka()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CLogo_Meka::Init(void)
{
	//初期化処理
	HRESULT hr = CLogo::Init();

	//テクスチャの割り当て
	this->BindTexture(CManager::GetInstance()->GetTexture()->Regist(m_apTextureFile[1]));

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CLogo_Meka::Uninit(void)
{
	//終了
	CLogo::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CLogo_Meka::Update(void)
{
	// キーボード情報取得
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_6))
	{
		//テクスチャの割り当て
		this->BindTexture(CManager::GetInstance()->GetTexture()->Regist(m_apTextureFile[1]));
	}
	if (pInputKeyboard->GetTrigger(DIK_7))
	{
		//テクスチャの割り当て
		this->BindTexture(CManager::GetInstance()->GetTexture()->Regist(m_apTextureFile[4]));
	}

#ifdef _DEBUG
	if (pInputKeyboard->GetTrigger(DIK_2))
	{
		SetComplete(true);
	}
#endif

	//更新
	CLogo::Update();
}

//==========================================
//  描画処理
//==========================================
void CLogo_Meka::Draw(void)
{
	//描画
	CLogo::Draw();
}

//==========================================
//  生成処理
//==========================================
CLogo_Meka* CLogo_Meka::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CLogo_Meka* pLogo = DEBUG_NEW CLogo_Meka;

	//初期化処理
	pLogo->Init();

	//値を設定
	pLogo->SetPosition(pos);
	pLogo->SetRotation(rot);

	return pLogo;
}
