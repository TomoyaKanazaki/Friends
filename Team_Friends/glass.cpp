//==========================================
//
//  ひび割れポリゴン(glass.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "glass.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const char* TEX_PASS = "data\\TEXTURE\\result\\glass.jpg"; // テクスチャパス
}

//==========================================
//  コンストラクタ
//==========================================
CGlass::CGlass() : CObject2D(8)
{

}

//==========================================
//  デストラクタ
//==========================================
CGlass::~CGlass()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CGlass::Init(void)
{
	// 初期化
	HRESULT hr = CObject2D::Init();

	// 種類の設定
	CObject::SetType(CObject::TYPE_EFFECT2D);

	// テクスチャの割り当て
	BindTexture(CManager::GetInstance()->GetTexture()->Regist(TEX_PASS));

	// 位置の設定
	SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	// サイズの設定
	SetSize(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f));

	// 値を返す
	return hr;
}

//==========================================
//  終了処理
//==========================================
void CGlass::Uninit(void)
{
	// 終了
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CGlass::Update(void)
{
	// 更新
	CObject2D::Update();
}

//==========================================
//  描画処理
//==========================================
void CGlass::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CManager::GetInstance()->GetRenderer()->GetDevice();

	// αブレンディングを加算合成に設定
	pDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// アルファテストを有効にする
	pDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDev->SetRenderState(D3DRS_ALPHAREF, 0);

	// 描画処理
	CObject2D::Draw();

	// αブレンディングを元に戻す
	pDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// アルファテストを有効にする
	pDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDev->SetRenderState(D3DRS_ALPHAREF, 0);
}

//==========================================
//  生成処理
//==========================================
CGlass* CGlass::Create()
{
	// インスタンス生成
	CGlass* pGlass = DEBUG_NEW CGlass;

	// NULLチェック
	if (pGlass == nullptr) { return nullptr; }

	// 初期化処理
	pGlass->Init();

	// 値を返す
	return pGlass;
}
