//==========================================
//
//  リザルトロゴ(logo_result.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "logo_result.h"
#include "manager.h"
#include "texture.h"
#include "camera.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 DIFF_POS = D3DXVECTOR3(0.0f, 15.0f, 50.0f);
}

//==========================================
//  コンストラクタ
//==========================================
CLogoResult::CLogoResult()
{

}

//==========================================
//  デストラクタ
//==========================================
CLogoResult::~CLogoResult()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CLogoResult::Init(void)
{
	// 初期化処理
	HRESULT hr = CLogo::Init();

	// タイプの設定
	SetType(CObject::TYPE_OBJECT3D);

	// テクスチャの割り当て
	BindTexture(CManager::GetInstance()->GetTexture()->Regist(m_apTextureFile[5]));

	//ロゴの位置を設定
	SetPosition(CManager::GetInstance()->GetCamera()->GetPositionV() + DIFF_POS);

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CLogoResult::Uninit(void)
{
	CLogo::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CLogoResult::Update(void)
{
	CLogo::Update();
}

//==========================================
//  描画処理
//==========================================
void CLogoResult::Draw(void)
{
	CLogo::Draw();
}

//==========================================
//  生成処理
//==========================================
CLogoResult* CLogoResult::Create()
{
	// インスタンス生成
	CLogoResult* pLogo = DEBUG_NEW CLogoResult;

	// NULLチェック
	if (pLogo == nullptr) { return nullptr; }

	// 初期化処理
	pLogo->Init();

	// 値を返す
	return pLogo;
}
