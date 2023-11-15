//==========================================
//
//  ƒ^ƒCƒgƒ‹ƒƒS(title_logo.cpp)
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
//  ƒRƒ“ƒXƒgƒ‰ƒNƒ^
//==========================================
CTitleLogo::CTitleLogo()
{
	m_pMech = nullptr;
	m_pMeka = nullptr;
	m_pSqou = nullptr;
	m_pComp = nullptr;
}

//==========================================
//  ƒfƒXƒgƒ‰ƒNƒ^
//==========================================
CTitleLogo::~CTitleLogo()
{

}

//==========================================
//  ‰Šú‰»ˆ—
//==========================================
HRESULT CTitleLogo::Init(void)
{
	//ƒ^ƒCƒv‚ÌÝ’è
	SetType(TYPE_OBJECT3D);

	return S_OK;
}

//==========================================
//  I—¹ˆ—
//==========================================
void CTitleLogo::Uninit(void)
{	 
	//MECHANIONƒƒS‚ð”jŠü
	if (m_pMech != nullptr)
	{
		m_pMech->Uninit();
		m_pMech = nullptr;
	}

	//ƒƒJƒjƒIƒ“ƒƒS‚ð”jŠü
	if (m_pMeka != nullptr)
	{
		m_pMeka->Uninit();
		m_pMeka = nullptr;
	}

	//í‘àƒƒS‚ð”jŠü
	if (m_pSqou != nullptr)
	{
		m_pSqou->Uninit();
		m_pSqou = nullptr;
	}

	//Š®¬‚µ‚½ƒƒS‚ð”jŠü
	if (m_pComp != nullptr)
	{
		m_pComp->Uninit();
		m_pComp = nullptr;
	}

	//ƒIƒuƒWƒFƒNƒg‚Ì”jŠü
	Release();
}

//==========================================
//  XVˆ—
//==========================================
void CTitleLogo::Update(void)
{	
	// ƒL[ƒ{[ƒhî•ñŽæ“¾
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

#ifdef _DEBUG

	if (pInputKeyboard->GetTrigger(DIK_1))
	{
		//MECHANIONƒƒS‚ð•\Ž¦
		if (m_pMech == nullptr)
		{
			m_pMech = CLogo_Mech::Create(D3DXVECTOR3(0.0f, 200.0f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_2))
	{
		//ƒƒJƒjƒIƒ“ƒƒS‚ð•\Ž¦
		if (m_pMeka == nullptr)
		{
			m_pMeka = CLogo_Meka::Create(D3DXVECTOR3(0.0f, 200.0f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_3))
	{
		//í‘àƒƒS‚ð•\Ž¦
		if (m_pSqou == nullptr)
		{
			m_pSqou = CLogo_Sqou::Create(D3DXVECTOR3(0.0f, 200.0f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_4))
	{
		//Š®¬‚µ‚½ƒƒS‚ð•\Ž¦
		if (m_pComp == nullptr)
		{
			m_pComp = CLogo_Comp::Create(D3DXVECTOR3(0.0f, 200.0f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_5))
	{
		//MECHANIONƒƒS‚ð”jŠü
		if (m_pMech != nullptr)
		{
			m_pMech->Uninit();
			m_pMech = nullptr;
		}

		//ƒƒJƒjƒIƒ“ƒƒS‚ð”jŠü
		if (m_pMeka != nullptr)
		{
			m_pMeka->Uninit();
			m_pMeka = nullptr;
		}

		//í‘àƒƒS‚ð”jŠü
		if (m_pSqou != nullptr)
		{
			m_pSqou->Uninit();
			m_pSqou = nullptr;
		}

		//Š®¬‚µ‚½ƒƒS‚ð”jŠü
		if (m_pComp != nullptr)
		{
			m_pComp->Uninit();
			m_pComp = nullptr;
		}
	}

#endif
}

//==========================================
//  •`‰æˆ—
//==========================================
void CTitleLogo::Draw(void)
{

}

//==========================================
//  ¶¬ˆ—
//==========================================
CTitleLogo* CTitleLogo::Create()
{
	//ƒCƒ“ƒXƒ^ƒ“ƒX¶¬
	CTitleLogo* pLogo = DEBUG_NEW CTitleLogo;

	//‰Šú‰»ˆ—
	pLogo->Init();

	return pLogo;
}
