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

//==========================================
// 静的メンバ変数宣言
//==========================================
const char* CLogo_Meka::m_pTextureFile = "data\\TEXTURE\\title\\title_01.png";

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
	HRESULT hr = CObject3D::Init();

	//タイプの設定
	SetType(TYPE_OBJECT3D);

	//サイズを設定
	SetSize(D3DXVECTOR3(24.0f, 6.0f, 0.0f));

	//テクスチャの割り当て
	this->BindTexture(CManager::GetInstance()->GetTexture()->Regist(m_pTextureFile));

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CLogo_Meka::Uninit(void)
{
	//終了
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CLogo_Meka::Update(void)
{
	//更新
	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CLogo_Meka::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//描画
	CObject3D::Draw();

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
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
