//==========================================
//
//  タイトルロゴ(title_logo.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "title_logo.h"
#include "logo_complete.h"
#include "logo_mechanion.h"
#include "logo_mekanion.h"
#include "logo_squadron.h"

#include "manager.h"
#include "input.h"

//==========================================
//  コンストラクタ
//==========================================
CTitleLogo::CTitleLogo()
{
	m_pMech = nullptr;
	m_pMeka = nullptr;
	m_pSqou = nullptr;
	m_pComp = nullptr;
	m_State = DEFAULT;
	m_bComplete = false;
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
	//タイプの設定
	SetType(TYPE_OBJECT3D);

	//MECHANIONロゴを表示
	if (m_pMech == nullptr)
	{
		m_pMech = CLogo_Mech::Create(D3DXVECTOR3(0.0f, 200.0f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

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

	//メカニオンロゴを破棄
	if (m_pMeka != nullptr)
	{
		m_pMeka->Uninit();
		m_pMeka = nullptr;
	}

	//戦隊ロゴを破棄
	if (m_pSqou != nullptr)
	{
		m_pSqou->Uninit();
		m_pSqou = nullptr;
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
	//状態更新
	UpdateState();

	//デバッグ用関数
	DebugFunction();
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

//==========================================
//  状態を更新
//==========================================
void CTitleLogo::UpdateState()
{
	//完成していないとき
	if (!m_bComplete)
	{
		switch (m_State)
		{
		case DEFAULT: // MECHANIONしかない

			if (m_pMech != nullptr && m_pMech->GetComplete())
			{
				//メカニオンロゴを表示
				if (m_pMeka == nullptr)
				{
					m_pMeka = CLogo_Meka::Create(D3DXVECTOR3(0.0f, 200.0f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}

				//状態を進める
				m_State = WAKE;
			}
			break;

		case WAKE: // メカニオンまで出てる

			if (m_pMeka != nullptr && m_pMeka->GetComplete())
			{
				//戦隊ロゴを表示
				if (m_pSqou == nullptr)
				{
					m_pSqou = CLogo_Sqou::Create(D3DXVECTOR3(0.0f, 200.0f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}

				//状態を進める
				m_State = FLASH;
			}
			break;

		case FLASH: //戦隊まで出てる

			if (m_pSqou != nullptr && m_pSqou->GetComplete())
			{
				//MECHANIONロゴを破棄
				if (m_pMech != nullptr)
				{
					m_pMech->Uninit();
					m_pMech = nullptr;
				}

				//メカニオンロゴを破棄
				if (m_pMeka != nullptr)
				{
					m_pMeka->Uninit();
					m_pMeka = nullptr;
				}

				//戦隊ロゴを破棄
				if (m_pSqou != nullptr)
				{
					m_pSqou->Uninit();
					m_pSqou = nullptr;
				}

				//完成したロゴを表示
				if (m_pComp == nullptr)
				{
					m_pComp = CLogo_Comp::Create(D3DXVECTOR3(0.0f, 200.0f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}

				//状態を進める
				m_State = COMPLETE;
			}
			break;

		case COMPLETE: // 完成している
			m_bComplete = true; // タイトルロゴを完成
			break;

		default:
			break;
		}
	}
}

//==========================================
//  デバッグ用の処理を詰めた関数
//==========================================
void CTitleLogo::DebugFunction()
{
	// キーボード情報取得
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

#ifdef _DEBUG

	if (pInputKeyboard->GetTrigger(DIK_5))
	{
		//MECHANIONロゴを破棄
		if (m_pMech != nullptr)
		{
			m_pMech->Uninit();
			m_pMech = nullptr;
		}

		//メカニオンロゴを破棄
		if (m_pMeka != nullptr)
		{
			m_pMeka->Uninit();
			m_pMeka = nullptr;
		}

		//戦隊ロゴを破棄
		if (m_pSqou != nullptr)
		{
			m_pSqou->Uninit();
			m_pSqou = nullptr;
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
