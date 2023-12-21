//=============================================================================
// 
//  必殺ウィンドウ処理 [ultwindow.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "ultwindow.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"
#include "object2D.h"
#include "calculation.h"
#include "statuswindow_base.h"
#include "object_circlegauge2D.h"
#include "multinumber.h"

//==========================================================================
// 定数定義
//==========================================================================
namespace
{
	const float RATIO = 1.2f;
	const char* TEXTURE_SHAPE = "data\\TEXTURE\\statuswindow\\statuswindow_shape02.png";		// 型のテクスチャ
	const char* TEXTURE_SHAPELID = "data\\TEXTURE\\statuswindow\\statuswindow_shapeLid2.png";	// 型のフタテクスチャ
	const char* TEXTURE_ONLINE = "data\\TEXTURE\\statuswindow\\ONLINE.png";			// オンライン
	const char* TEXTURE_OFFLINE = "data\\TEXTURE\\statuswindow\\OFFLINE.png";		// オフライン
	const char* TEXTURE_NUMBER = "data\\TEXTURE\\number_status.png";				// 数字
	const char* TEXTURE_STATUSTEXT = "data\\TEXTURE\\statuswindow\\status_ult.png"; // 必殺テキスト
	const D3DXCOLOR DEFAULT_GAUGECOLOR = D3DXCOLOR(0.2f, 1.0f, 0.2f, 0.9f);			// デフォルトのゲージ色
	const float CYCLE_GAUGEFLASH = 1.2f;	// ゲージ点滅の周期	
}

//==========================================================================
// コンストラクタ
//==========================================================================
CUltWindow::CUltWindow(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	memset(&m_pOnOffSign[0], NULL, sizeof(m_pOnOffSign));		// オンオフサイン
	m_pUltText = nullptr;				// 必殺テキスト
	m_pWindowShape = nullptr;			// ウィンドウの型
	m_pWindowShapeLid = nullptr;		// ウィンドウの型の蓋
	m_pCircleGauge2D = nullptr;			// 円ゲージのポインタ
	m_pUltNumber = nullptr;				// 必殺の数字
	m_bEndCharge = false;				// チャージ完了
	m_fColorFlashValue = 0.0f;			// 点滅の色
}

//==========================================================================
// デストラクタ
//==========================================================================
CUltWindow::~CUltWindow()
{

}

//==========================================================================
// 生成処理
//==========================================================================
CUltWindow *CUltWindow::Create(D3DXVECTOR3 pos, bool bJoin)
{
	// 生成用のオブジェクト
	CUltWindow *pScore = NULL;

	if (pScore == NULL)
	{// NULLだったら

		// メモリの確保
		pScore = DEBUG_NEW CUltWindow;

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
HRESULT CUltWindow::Init(void)
{
	// 種類設定
	SetType(CObject::TYPE_OBJECT2D);

	D3DXVECTOR3 pos = GetPosition();
	CStatusWindow_Base *pBase = CStatusWindow_Base::Create(pos);
	D3DXVECTOR3 posBase = pBase->GetPosition();
	D3DXVECTOR2 sizeBase = pBase->GetSize();
	posBase.y = SCREEN_HEIGHT - sizeBase.y;
	pBase->SetPosition(posBase);
	pBase->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f));

	// テクスチャのオブジェクト取得
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	int nIdxTex = pTexture->Regist(TEXTURE_SHAPE);
	int nIdxTexLid = pTexture->Regist(TEXTURE_SHAPELID);

	// ウィンドウの型生成
	m_pWindowShape = CObject2D::Create(GetPriority());
	m_pWindowShape->BindTexture(nIdxTex);
	m_pWindowShape->SetSize(pTexture->GetImageSize(nIdxTex) * 0.078f * RATIO);

	D3DXVECTOR3 WindowPos = mylib_const::DEFAULT_VECTOR3;
	D3DXVECTOR2 WindowSize = m_pWindowShape->GetSize();
	D3DXCOLOR UltColor = mylib_const::DEFAULT_COLOR;
	WindowPos = D3DXVECTOR3(pos.x, pos.y + WindowSize.y * 0.5f, pos.z);
	UltColor = DEFAULT_GAUGECOLOR;

	// 位置設定
	m_pWindowShape->SetPosition(WindowPos);
	m_pWindowShape->SetType(CObject::TYPE_OBJECT2D);


	// 多角形ゲージ生成
	m_pCircleGauge2D = CObjectCircleGauge2D::Create(6, WindowSize.y * 0.8f * RATIO);
	m_pCircleGauge2D->SetType(CObject::TYPE_OBJECT2D);
	m_pCircleGauge2D->SetPosition(WindowPos);
	m_pCircleGauge2D->SetRotation(D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(30.0f)));
	m_pCircleGauge2D->SetColor(UltColor);

	// 枠の蓋生成
	m_pWindowShapeLid = CObject2D::Create(GetPriority());
	m_pWindowShapeLid->SetType(CObject::TYPE_OBJECT2D);
	m_pWindowShapeLid->BindTexture(nIdxTexLid);
	m_pWindowShapeLid->SetPosition(m_pWindowShape->GetPosition());
	m_pWindowShapeLid->SetSize(m_pWindowShape->GetSize());

	// 必殺の数字
	m_pUltNumber = CMultiNumber::Create(
		D3DXVECTOR3(WindowPos.x + WindowSize.x * 0.15f, WindowPos.y + WindowSize.x * 0.15f, WindowPos.z),
		D3DXVECTOR2(WindowSize.x, WindowSize.x) * 0.15f,
		4,
		CNumber::OBJECTTYPE_2D,
		TEXTURE_NUMBER, true, 8);

	// 必殺テキスト
	m_pUltText = CObject2D::Create(GetPriority());

	int nIdxTexText = pTexture->Regist(TEXTURE_STATUSTEXT);
	m_pUltText->SetType(CObject::TYPE_OBJECT2D);
	m_pUltText->BindTexture(nIdxTexText);
	m_pUltText->SetSize(pTexture->GetImageSize(nIdxTexText) * 0.09f * RATIO * 1.2f);
	m_pUltText->SetPosition(D3DXVECTOR3(WindowPos.x - WindowSize.x * 0.2f * 1.2f, WindowPos.y, WindowPos.z));

	// 値の設定処理
	m_pUltNumber->SetValue(100);


	int nIdxTexOnOffline = pTexture->Regist(TEXTURE_ONLINE);
	for (int i = 0; i < 2; i++)
	{
		m_pOnOffSign[i] = CObject2D::Create(GetPriority());

		m_pOnOffSign[i]->SetType(CObject::TYPE_OBJECT2D);

		if (m_bJoin == true)
		{
			nIdxTexOnOffline = pTexture->Regist(TEXTURE_ONLINE);
		}
		else
		{
			nIdxTexOnOffline = pTexture->Regist(TEXTURE_OFFLINE);
			m_pOnOffSign[i]->SetColor(D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f));
		}
		m_pOnOffSign[i]->BindTexture(nIdxTexOnOffline);
		m_pOnOffSign[i]->SetSize(pTexture->GetImageSize(nIdxTexOnOffline) * 0.075f * RATIO);

		D3DXVECTOR3 posShape = m_pWindowShape->GetPosition();
		D3DXVECTOR2 WindowSize = m_pWindowShape->GetSize();
		WindowSize.x *= 1.2f;

		m_pOnOffSign[i]->SetPosition(D3DXVECTOR3(posShape.x - WindowSize.x + (WindowSize.x * 2.0f * i), posShape.y + WindowSize.y * 0.75f, posShape.z));
	}

	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CUltWindow::Uninit(void)
{
	// 数字のオブジェクトの終了処理
	if (m_pUltNumber != NULL)
	{
		m_pUltNumber->Uninit();
		delete m_pUltNumber;
		m_pUltNumber = NULL;
	}

	// 情報削除
	Release();
}

//==========================================================================
// 更新処理
//==========================================================================
void CUltWindow::Update(void)
{

	float fRate = m_pCircleGauge2D->GetRateDest();
	if (fRate >= 1.0f)
	{
		m_bEndCharge = true;
	}
	else
	{
		m_bEndCharge = false;
		D3DXCOLOR col = m_pCircleGauge2D->GetColor();

		col += (col - DEFAULT_GAUGECOLOR) * 0.15f;

		m_pCircleGauge2D->SetColor(col);
	}

	if (m_bEndCharge)
	{
		GaugeFlash();
	}

	// 数字のオブジェクトの更新処理
	if (m_pUltNumber != NULL)
	{
		m_pUltNumber->Update();
	}
}

//==========================================================================
// ゲージの点滅処理
//==========================================================================
void CUltWindow::GaugeFlash(void)
{
	// 色取得
	D3DXCOLOR col = m_pCircleGauge2D->GetColor();

	// 点滅の色
	m_fColorFlashValue += CManager::GetInstance()->GetDeltaTime();

	float fValue = sinf(D3DX_PI * (m_fColorFlashValue / CYCLE_GAUGEFLASH)) * 0.5f;
	col.r = DEFAULT_GAUGECOLOR.r + fValue;
	col.g = DEFAULT_GAUGECOLOR.g + fValue;
	col.b = DEFAULT_GAUGECOLOR.b + fValue;

	if (m_fColorFlashValue >= CYCLE_GAUGEFLASH * 1.0f)
	{
		m_fColorFlashValue = 0.0f;
	}

	// 色設定
	m_pCircleGauge2D->SetColor(col);
}

//==========================================================================
// 描画処理
//==========================================================================
void CUltWindow::Draw(void)
{

}

//==========================================================================
// ゲージ取得
//==========================================================================
CObjectCircleGauge2D *CUltWindow::GetGauge()
{
	return m_pCircleGauge2D;
}
