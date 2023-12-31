//=============================================================================
// 
//  ステータスウィンドウ処理 [statuswindow.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "statuswindow.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"
#include "object2D.h"
#include "calculation.h"
#include "statuswindow_base.h"
#include "object_circlegauge2D.h"
#include "multinumber.h"

//==========================================================================
// マクロ定義
//==========================================================================

//==========================================================================
// 定数定義
//==========================================================================
namespace
{
	const char* TEXTURE_SHAPE = "data\\TEXTURE\\statuswindow\\statuswindow_shape02.png";		// 型のテクスチャ
	const char* TEXTURE_SHAPELID = "data\\TEXTURE\\statuswindow\\statuswindow_shapeLid2.png";	// 型のフタテクスチャ
	const char* TEXTURE_ONLINE = "data\\TEXTURE\\statuswindow\\ONLINE.png";		// オンライン
	const char* TEXTURE_OFFLINE = "data\\TEXTURE\\statuswindow\\OFFLINE.png";	// オフライン
	const char* TEXTURE_NUMBER = "data\\TEXTURE\\number_status.png";	// 数字
	const char* TEXTURE_STATUSTEXT[CGameManager::STATUS_MAX] =			// ステータステキスト
	{
		"data\\TEXTURE\\statuswindow\\status_attack.png",
		"data\\TEXTURE\\statuswindow\\status_speed.png",
		"data\\TEXTURE\\statuswindow\\status_life.png",
	};
}

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================

//==========================================================================
// コンストラクタ
//==========================================================================
CStatusWindow::CStatusWindow(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	memset(&m_apOnOffSign[0], NULL, sizeof(m_apOnOffSign));		// オンオフサイン
	memset(&m_apStatusText[0], NULL, sizeof(m_apStatusText));	// ステータステキスト
	memset(&m_apWindowShape[0], NULL, sizeof(m_apWindowShape));	// ウィンドウの型
	memset(&m_apWindowShapeLid[0], NULL, sizeof(m_apWindowShapeLid));	// ウィンドウの型
	memset(&m_pCircleGauge2D[0], NULL, sizeof(m_pCircleGauge2D));	// 円ゲージのポインタ
	memset(&m_pStatusNumber[0], NULL, sizeof(m_pStatusNumber));		// ステータスの数字
}

//==========================================================================
// デストラクタ
//==========================================================================
CStatusWindow::~CStatusWindow()
{

}

//==========================================================================
// 生成処理
//==========================================================================
CStatusWindow *CStatusWindow::Create(D3DXVECTOR3 pos, bool bJoin)
{
	// 生成用のオブジェクト
	CStatusWindow *pScore = NULL;

	if (pScore == NULL)
	{// NULLだったら

		// メモリの確保
		pScore = DEBUG_NEW CStatusWindow;

		if (pScore != NULL)
		{// メモリの確保が出来ていたら

			// 参加してるか
			pScore->m_bJoin = bJoin;

			// 位置設定
			pScore->SetPosition(pos);

			// 初期化処理
			pScore->Init();
		}

		return pScore;
	}

	return NULL;
}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CStatusWindow::Init(void)
{
	// 種類設定
	SetType(CObject::TYPE_OBJECT2D);

	D3DXVECTOR3 pos = GetPosition();

	// 下地生成
	CStatusWindow_Base *pBase = CStatusWindow_Base::Create(pos);

	D3DXVECTOR3 posBase = pBase->GetPosition();
	D3DXVECTOR2 sizeBase = pBase->GetSize();
	posBase.y = SCREEN_HEIGHT - sizeBase.y;
	pBase->SetPosition(posBase);

	// テクスチャのオブジェクト取得
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	int nIdxTex = pTexture->Regist(TEXTURE_SHAPE);
	int nIdxTexLid = pTexture->Regist(TEXTURE_SHAPELID);
	for (int i = 0; i < CGameManager::STATUS_MAX; i++)
	{
		if (m_apWindowShape[i] != NULL)
		{
			continue;
		}

		// ウィンドウの型生成
		m_apWindowShape[i] = CObject2D::Create(GetPriority());
		m_apWindowShape[i]->BindTexture(nIdxTex);
		m_apWindowShape[i]->SetSize(pTexture->GetImageSize(nIdxTex) * 0.078f);

		D3DXVECTOR3 WindowPos = mylib_const::DEFAULT_VECTOR3;
		D3DXVECTOR2 WindowSize = m_apWindowShape[i]->GetSize();
		D3DXCOLOR StatusColor = mylib_const::DEFAULT_COLOR;
		switch (i)
		{
		case CGameManager::STATUS_POWER:
			WindowPos = D3DXVECTOR3(pos.x - WindowSize.x * 1.5f, pos.y, pos.z);
			StatusColor = D3DXCOLOR(1.0f, 0.4f, 0.4f, 0.9f);
			break;

		case CGameManager::STATUS_SPEED:
			WindowPos = D3DXVECTOR3(pos.x + WindowSize.x * 1.5f, pos.y, pos.z);
			StatusColor = D3DXCOLOR(0.4f, 0.4f, 1.0f, 0.9f);
			break;

		case CGameManager::STATUS_LIFE:
			WindowPos = D3DXVECTOR3(pos.x, pos.y + WindowSize.y, pos.z);
			StatusColor = D3DXCOLOR(0.2f, 1.0f, 0.2f, 0.9f);
			break;
		}

		// 位置設定
		m_apWindowShape[i]->SetPosition(WindowPos);
		m_apWindowShape[i]->SetType(CObject::TYPE_OBJECT2D);


		// 多角形ゲージ生成
		m_pCircleGauge2D[i] = CObjectCircleGauge2D::Create(6, WindowSize.y * 0.9f);
		m_pCircleGauge2D[i]->SetType(CObject::TYPE_OBJECT2D);
		m_pCircleGauge2D[i]->SetPosition(WindowPos);
		m_pCircleGauge2D[i]->SetRotation(D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(30.0f)));
		m_pCircleGauge2D[i]->SetColor(StatusColor);

		// 枠の蓋生成
		m_apWindowShapeLid[i] = CObject2D::Create(GetPriority());
		m_apWindowShapeLid[i]->SetType(CObject::TYPE_OBJECT2D);
		m_apWindowShapeLid[i]->BindTexture(nIdxTexLid);
		m_apWindowShapeLid[i]->SetPosition(m_apWindowShape[i]->GetPosition());
		m_apWindowShapeLid[i]->SetSize(m_apWindowShape[i]->GetSize());

		// ステータスの数字
		m_pStatusNumber[i] = CMultiNumber::Create(
			D3DXVECTOR3(WindowPos.x + WindowSize.x * 0.15f, WindowPos.y + WindowSize.x * 0.15f, WindowPos.z),
			D3DXVECTOR2(WindowSize.x, WindowSize.x) * 0.15f,
			4,
			CNumber::OBJECTTYPE_2D,
			TEXTURE_NUMBER, true, 8);

		// ステータステキスト
		m_apStatusText[i] = CObject2D::Create(GetPriority());

		int nIdxTexText = pTexture->Regist(TEXTURE_STATUSTEXT[i]);
		m_apStatusText[i]->SetType(CObject::TYPE_OBJECT2D);
		m_apStatusText[i]->BindTexture(nIdxTexText);
		m_apStatusText[i]->SetSize(pTexture->GetImageSize(nIdxTexText) * 0.09f);
		m_apStatusText[i]->SetPosition(D3DXVECTOR3(WindowPos.x - WindowSize.x * 0.18f, WindowPos.y, WindowPos.z));

		// 値の設定処理
		m_pStatusNumber[i]->SetValue(100);

	}

	int nIdxTexOnOffline = pTexture->Regist(TEXTURE_ONLINE);
	for (int i = 0; i < 2; i++)
	{
		m_apOnOffSign[i] = CObject2D::Create(GetPriority());

		m_apOnOffSign[i]->SetType(CObject::TYPE_OBJECT2D);

		if (m_bJoin == true)
		{
			nIdxTexOnOffline = pTexture->Regist(TEXTURE_ONLINE);
		}
		else
		{
			nIdxTexOnOffline = pTexture->Regist(TEXTURE_OFFLINE);
			m_apOnOffSign[i]->SetColor(D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f));
		}
		m_apOnOffSign[i]->BindTexture(nIdxTexOnOffline);
		m_apOnOffSign[i]->SetSize(pTexture->GetImageSize(nIdxTexOnOffline) * 0.075f);

		D3DXVECTOR3 posShape = m_apWindowShape[i]->GetPosition();
		D3DXVECTOR2 WindowSize = m_apWindowShape[i]->GetSize();
		m_apOnOffSign[i]->SetPosition(D3DXVECTOR3(posShape.x, posShape.y + WindowSize.y * 1.5f, posShape.z));

	}
	
	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CStatusWindow::Uninit(void)
{
	
	// ウィンドウの型の終了処理
	for (int i = 0; i < CGameManager::STATUS_MAX; i++)
	{
		if (m_apWindowShape[i] == NULL)
		{
			continue;
		}
		m_apWindowShape[i] = NULL;
	}

	// ウィンドウの型の終了処理
	for (int i = 0; i < CGameManager::STATUS_MAX; i++)
	{
		if (m_apWindowShapeLid[i] == NULL)
		{
			continue;
		}
		m_apWindowShapeLid[i] = NULL;
	}

	// ステータステキストの終了処理
	for (int i = 0; i < CGameManager::STATUS_MAX; i++)
	{
		if (m_apStatusText[i] == NULL)
		{
			continue;
		}
		m_apStatusText[i] = NULL;
	}

	// 円ゲージのポインタの終了処理
	for (int i = 0; i < CGameManager::STATUS_MAX; i++)
	{
		if (m_pCircleGauge2D[i] == NULL)
		{
			continue;
		}
		m_pCircleGauge2D[i] = NULL;
	}

	// 数字のオブジェクトの終了処理
	for (int i = 0; i < CGameManager::STATUS_MAX; i++)
	{
		if (m_pStatusNumber[i] == NULL)
		{
			continue;
		}
		m_pStatusNumber[i]->Uninit();
		delete m_pStatusNumber[i];
		m_pStatusNumber[i] = NULL;
	}

	for (int i = 0; i < 2; i++)
	{
		if (m_pStatusNumber[i] == NULL)
		{
			continue;
		}
		m_apOnOffSign[i] = NULL;
	}

	// 情報削除
	Release();
}

//==========================================================================
// 削除処理
//==========================================================================
void CStatusWindow::Kill(void)
{
	// ウィンドウの型の終了処理
	for (int i = 0; i < CGameManager::STATUS_MAX; i++)
	{
		if (m_apWindowShape[i] == NULL)
		{
			continue;
		}
		m_apWindowShape[i]->Uninit();
		m_apWindowShape[i] = NULL;
	}

	// ウィンドウの型の終了処理
	for (int i = 0; i < CGameManager::STATUS_MAX; i++)
	{
		if (m_apWindowShapeLid[i] == NULL)
		{
			continue;
		}
		m_apWindowShapeLid[i]->Uninit();
		m_apWindowShapeLid[i] = NULL;
	}

	// ステータステキストの終了処理
	for (int i = 0; i < CGameManager::STATUS_MAX; i++)
	{
		if (m_apStatusText[i] == NULL)
		{
			continue;
		}
		m_apStatusText[i]->Uninit();
		m_apStatusText[i] = NULL;
	}

	// 円ゲージのポインタの終了処理
	for (int i = 0; i < CGameManager::STATUS_MAX; i++)
	{
		if (m_pCircleGauge2D[i] == NULL)
		{
			continue;
		}
		m_pCircleGauge2D[i]->Uninit();
		m_pCircleGauge2D[i] = NULL;
	}

	// 数字のオブジェクトの終了処理
	for (int i = 0; i < CGameManager::STATUS_MAX; i++)
	{
		if (m_pStatusNumber[i] == NULL)
		{
			continue;
		}
		m_pStatusNumber[i]->Release();
		delete m_pStatusNumber[i];
		m_pStatusNumber[i] = NULL;
	}

	for (int i = 0; i < 2; i++)
	{
		if (m_apOnOffSign[i] == NULL)
		{
			continue;
		}
		m_apOnOffSign[i]->Uninit();
		m_apOnOffSign[i] = NULL;
	}

	// 情報削除
	Release();
}

//==========================================================================
// 更新処理
//==========================================================================
void CStatusWindow::Update(void)
{
	// 数字のオブジェクトの更新処理
	for (int i = 0; i < CGameManager::STATUS_MAX; i++)
	{
		if (m_pStatusNumber[i] == NULL)
		{
			continue;
		}
		m_pStatusNumber[i]->Update();
	}
}

//==========================================================================
// 描画処理
//==========================================================================
void CStatusWindow::Draw(void)
{

}

//==========================================================================
// ゲージ取得
//==========================================================================
CObjectCircleGauge2D *CStatusWindow::GetGauge(CGameManager::eStatus status)
{
	return m_pCircleGauge2D[status];
}
