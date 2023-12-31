//=============================================================================
// 
//  eÌen_ [bullet_point.cpp]
//  Author : ûücÀË
// 
//=============================================================================
#include "bullet_point.h"
#include "texture.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "elevation.h"

//==========================================================================
// ÃIoÏé¾
//==========================================================================
int CBulletPoint::m_nNumAll = 0;						// eÌ

//==========================================================================
// RXgN^
//==========================================================================
CBulletPoint::CBulletPoint(int nPriority) : CObject3D(nPriority)
{
	m_pObject = NULL;	// IuWFNgÌ|C^
	m_nNumAll = 0;		// 
	m_nTexIdx = 0;		// eNX`ÌCfbNXÔ

	// ÁZ
	m_nNumAll++;
}

//==========================================================================
// fXgN^
//==========================================================================
CBulletPoint::~CBulletPoint()
{
	
}

//==========================================================================
// ¶¬
//==========================================================================
CBulletPoint *CBulletPoint::Create(void)
{
	// ¶¬pÌIuWFNg
	CBulletPoint *pShadow = NULL;

	if (pShadow == NULL)
	{// NULL¾Á½ç

		// ÌmÛ
		pShadow = DEBUG_NEW CBulletPoint;

		//if (pShadow->GetID() < 0)
		//{// mÛÉ¸sµÄ¢½ç

		//	delete pShadow;
		//	return NULL;
		//}

		if (pShadow != NULL)
		{// ÌmÛªoÄ¢½ç

			// ú»
			pShadow->Init();
		}

		return pShadow;
	}

	return NULL;
}

//==========================================================================
// ¶¬(I[o[[h)
//==========================================================================
CBulletPoint *CBulletPoint::Create(D3DXVECTOR3 pos, float size)
{
	// ¶¬pÌIuWFNg
	CBulletPoint *pShadow = NULL;

	if (pShadow == NULL)
	{// NULL¾Á½ç

		// ÌmÛ
		pShadow = DEBUG_NEW CBulletPoint;

		//if (pShadow->GetID() < 0)
		//{// mÛÉ¸sµÄ¢½ç

		//	delete pShadow;
		//	return NULL;
		//}

		if (pShadow != NULL)
		{// ÌmÛªoÄ¢½ç

			// ÊuèÄ
			pShadow->SetPosition(pos);
			pShadow->SetSize(D3DXVECTOR3(size, 0.0f, size));	// TCY

			// ú»
			pShadow->Init();
		}
		return pShadow;
	}

	return NULL;
}

//==========================================================================
// ú»
//==========================================================================
HRESULT CBulletPoint::Init(void)
{
	HRESULT hr;

	// eíÏÌú»
	SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));	// F

	// íÞÌÝè
	SetType(TYPE_SHADOW);

	D3DXVECTOR3 pos = GetPosition();
	SetPosition(D3DXVECTOR3(pos.x, pos.y + 1.0f, pos.z));

	// ú»
	hr = CObject3D::Init();

	if (FAILED(hr))
	{// ¸sµ½Æ«

		return E_FAIL;
	}

	// eNX`ÌèÄ
	m_nTexIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\caution\\target.png");

	// eNX`ÌèÄ
	BindTexture(m_nTexIdx);

	return S_OK;
}

//==========================================================================
// I¹
//==========================================================================
void CBulletPoint::Uninit(void)
{
	// I¹
	CObject3D::Uninit();

	// ¸Z
	m_nNumAll--;
}

//==========================================================================
// XV
//==========================================================================
void CBulletPoint::Update(void)
{
	// SÌ»è
	if (IsDeath() == true)
	{// StOª§ÁÄ¢½ç
		return;
	}

	// Êuæ¾
	D3DXVECTOR3 pos = GetPosition();

	// ³æ¾
	bool bLand = false;
	pos.y = CGame::GetElevation()->GetHeight(pos, bLand);

	// ÊuÝè
	SetPosition(pos);

	// ¸_îñÝè
	CObject3D::SetVtx();
}

//==========================================================================
// `æ
//==========================================================================
void CBulletPoint::Draw(void)
{
	// `æ
	CObject3D::Draw();
}

//==========================================================================
// æ¾
//==========================================================================
int CBulletPoint::GetNumAll(void)
{
	return m_nNumAll;
}
