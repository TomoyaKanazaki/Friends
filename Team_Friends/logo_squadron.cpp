//==========================================
//
//  戦隊のロゴ(logo_squadron.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "logo_squadron.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  コンストラクタ
//==========================================
CLogo_Sqou::CLogo_Sqou()
{

}

//==========================================
//  デストラクタ
//==========================================
CLogo_Sqou::~CLogo_Sqou()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CLogo_Sqou::Init(void)
{
	//初期化処理
	HRESULT hr = CLogo::Init();

	//テクスチャの割り当て
	this->BindTexture(CManager::GetInstance()->GetTexture()->Regist(m_apTextureFile[2]));

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CLogo_Sqou::Uninit(void)
{
	//終了
	CLogo::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CLogo_Sqou::Update(void)
{
	//更新
	CLogo::Update();
}

//==========================================
//  描画処理
//==========================================
void CLogo_Sqou::Draw(void)
{
	//描画
	CLogo::Draw();
}

//==========================================
//  生成処理
//==========================================
CLogo_Sqou* CLogo_Sqou::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CLogo_Sqou* pLogo = DEBUG_NEW CLogo_Sqou;

	//初期化処理
	pLogo->Init();

	//値を設定
	pLogo->SetPosition(pos);
	pLogo->SetRotation(rot);

	return pLogo;
}
