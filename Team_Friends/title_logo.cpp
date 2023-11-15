//==========================================
//
//  タイトルロゴ(title_logo.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "title_logo.h"
#include "logo_complete.h"
#include "logo_mechanion.h"

#include "manager.h"
#include "input.h"

//==========================================
//  コンストラクタ
//==========================================
CTitleLogo::CTitleLogo()
{
	m_pMech = nullptr;
	m_pComp = nullptr;
}

//==========================================
//  デストラクタ
//==========================================
CTitleLogo::~CTitleLogo()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CTitleLogo::Init(void)
{
	//MECHANIONロゴを表示
	if (m_pMech == nullptr)
	{
		m_pMech = CLogo_Mech::Create(D3DXVECTOR3(0.0f, 200.0f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	//タイプの設定
	SetType(TYPE_OBJECT3D);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CTitleLogo::Uninit(void)
{	 
	//MECHANIONロゴを破棄
	if (m_pMech != nullptr)
	{
		m_pMech->Uninit();
		m_pMech = nullptr;
	}

	//完成したロゴを破棄
	if (m_pComp != nullptr)
	{
		m_pComp->Uninit();
		m_pComp = nullptr;
	}

	//オブジェクトの破棄
	Release();
}

//==========================================
//  更新処理
//==========================================
void CTitleLogo::Update(void)
{	
	// キーボード情報取得
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

#ifdef _DEBUG
	if (pInputKeyboard->GetTrigger(DIK_SPACE))
	{
		//完成したロゴを表示
		if (m_pComp == nullptr)
		{
			m_pComp = CLogo_Comp::Create(D3DXVECTOR3(0.0f, 200.0f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_1))
	{
		//MECHANIONロゴを破棄
		if (m_pMech != nullptr)
		{
			m_pMech->Uninit();
			m_pMech = nullptr;
		}

		//完成したロゴを破棄
		if (m_pComp != nullptr)
		{
			m_pComp->Uninit();
			m_pComp = nullptr;
		}
	}
#endif
}

//==========================================
//  描画処理
//==========================================
void CTitleLogo::Draw(void)
{

}

//==========================================
//  生成処理
//==========================================
CTitleLogo* CTitleLogo::Create()
{
	//インスタンス生成
	CTitleLogo* pLogo = DEBUG_NEW CTitleLogo;

	//初期化処理
	pLogo->Init();

	return pLogo;
}
