//==========================================
//
//  ロゴのクラス(logo.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "logo.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
// 静的メンバ変数宣言
//==========================================
const char* CLogo::m_apTextureFile[] =
{
	"data\\TEXTURE\\title\\title_00.png", // 0
	"data\\TEXTURE\\title\\title_01.png", // 1
	"data\\TEXTURE\\title\\title_02.png", // 2
	"data\\TEXTURE\\title\\title_03.png", // 3
	"data\\TEXTURE\\title\\title_11.png", // 4
	"data\\TEXTURE\\result\\lose.png", // 5
	"data\\TEXTURE\\result\\win.png" // 6
};

//==========================================
//  コンストラクタ
//==========================================
CLogo::CLogo()
{
	m_bComplete = false;
}

//==========================================
//  デストラクタ
//==========================================
CLogo::~CLogo()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CLogo::Init(void)
{
	//初期化処理
	HRESULT hr = CObject3D::Init();

	//タイプの設定
	SetType(TYPE_OBJECT3D);

	//サイズを設定
	SetSize(D3DXVECTOR3(24.0f, 6.0f, 0.0f));

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CLogo::Uninit(void)
{
	//終了
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CLogo::Update(void)
{
	//更新
	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CLogo::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//描画
	CObject3D::Draw();

	// アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
