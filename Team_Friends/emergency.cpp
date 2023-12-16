//=============================================================================
// 
//  警報処理 [emergency.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "emergency.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"
#include "object2D.h"
#include "calculation.h"
#include "game.h"
#include "gamemanager.h"
#include "input.h"
#include "fade.h"

//==========================================================================
// 定数定義
//==========================================================================
namespace
{
	const float TIME_EMERGENCY = 4.0f;				// 警報時間
	const int NUM_FLASH = 3;						// 点滅回数
	const float TIME_SPAWN_MISSIONWINDOW = 0.2f;	// ミッションウィンドウの出現時間
	const float TIME_SPAWN_MISSIONTEXT = 0.5f;		// ミッションテキストの出現時間
	const float DEST_POSITION_SCROLLTEXT = -500.0f;	// 目的のスクロール位置
	const char* TEXTURE_EMERGENCY = "data\\TEXTURE\\emergency\\emaergency_01.png";	// 警報のテクスチャ
	const char* TEXTURE_MISSION = "data\\TEXTURE\\emergency\\mission_01.png";			// ミッションのテクスチャ
	const char* TEXTURE_WINDOW = "data\\TEXTURE\\emergency\\window_02.png";			// ウィンドウのテクスチャ
	const char* TEXTURE_FRAME = "data\\TEXTURE\\emergency\\warning_02.png";			// フレームのテクスチャ
}

//==========================================================================
// 関数リスト
//==========================================================================
CEmergency::STATE_FUNC CEmergency::m_StateFuncList[] =
{
	&CEmergency::UpdateEmergency,	// 警報
	&CEmergency::UpdateWindow,		// ウィンドウ
	&CEmergency::UpdateMission,		// ミッション
	&CEmergency::UpdateEnd,	// 終了
};

//==========================================================================
// コンストラクタ
//==========================================================================
CEmergency::CEmergency(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_satate = STATE_EMERGENCY;	// 状態
	m_bEndEmergency = false;	// 警報が終わったか
	m_fTime = 0.0f;				// 警報時間
	m_pEmergencyFlash = nullptr;// 警報時点滅
	m_pEmergencyText = nullptr;	// 警報テキスト
	m_pMissionText = nullptr;	// ミッションテキスト
	m_pWindow = nullptr;		// ウィンドウ
	memset(&m_pWarningFrame[0], NULL, sizeof(m_pWarningFrame));	// 警告のフレーム
}

//==========================================================================
// デストラクタ
//==========================================================================
CEmergency::~CEmergency()
{

}

//==========================================================================
// 生成処理
//==========================================================================
CEmergency *CEmergency::Create(void)
{
	// 生成用のオブジェクト
	CEmergency *pScore = nullptr;

	if (pScore == nullptr)
	{// nullptrだったら

		// メモリの確保
		pScore = DEBUG_NEW CEmergency;

		if (pScore != nullptr)
		{// メモリの確保が出来ていたら

			// 初期化処理
			pScore->Init();
		}

		return pScore;
	}

	return nullptr;
}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CEmergency::Init(void)
{
	// 種類設定
	SetType(CObject::TYPE_OBJECT2D);

	// テクスチャのオブジェクト取得
	CTexture *pTexture = CManager::GetInstance()->GetTexture();
	int nIdxTex = 0;

	//==========================
	// 警報時点滅
	//==========================
	m_pEmergencyFlash = CObject2D::Create(7);
	m_pEmergencyFlash->SetType(CObject::TYPE_OBJECT2D);
	m_pEmergencyFlash->SetSize(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f));
	m_pEmergencyFlash->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f));
	m_pEmergencyFlash->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	//==========================
	// 警報テキスト
	//==========================
	m_pEmergencyText = CObject2D::Create(7);
	m_pEmergencyText->SetType(CObject::TYPE_OBJECT2D);

	nIdxTex = pTexture->Regist(TEXTURE_EMERGENCY);
	m_pEmergencyText->BindTexture(nIdxTex);
	m_pEmergencyText->SetSize(pTexture->GetImageSize(nIdxTex) * 1.0f);
	m_pEmergencyText->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + m_pEmergencyText->GetSize().x, SCREEN_HEIGHT * 0.5f, 0.0f));
	m_pEmergencyText->SetOriginPosition(m_pEmergencyText->GetPosition());

	//==========================
	// ウィンドウ
	//==========================
	m_pWindow = CObject2D::Create(7);
	m_pWindow->SetType(CObject::TYPE_OBJECT2D);

	nIdxTex = pTexture->Regist(TEXTURE_WINDOW);
	m_pWindow->BindTexture(nIdxTex);
	m_pWindow->SetSize(pTexture->GetImageSize(nIdxTex) * 0.5f);
	m_pWindow->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_pWindow->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	//==========================
	// ミッションテキスト
	//==========================
	m_pMissionText = CObject2D::Create(7);
	m_pMissionText->SetType(CObject::TYPE_OBJECT2D);

	nIdxTex = pTexture->Regist(TEXTURE_MISSION);
	m_pMissionText->BindTexture(nIdxTex);
	m_pMissionText->SetSize(pTexture->GetImageSize(nIdxTex) * 5.0f);
	m_pMissionText->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_pMissionText->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	//==========================
	// 警告のフレーム
	//==========================
	for (int i = 0; i < 2; i++)
	{
		m_pWarningFrame[i] = CObject2D::Create(7);
		m_pWarningFrame[i]->SetType(CObject::TYPE_OBJECT2D);

		nIdxTex = pTexture->Regist(TEXTURE_FRAME);
		m_pWarningFrame[i]->BindTexture(nIdxTex);
		m_pWarningFrame[i]->SetSize(pTexture->GetImageSize(nIdxTex) * 1.0f);
		m_pWarningFrame[i]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		float fAdjSize = -60.0f;

		if (i == 0)
		{
			m_pWarningFrame[i]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT - (m_pWarningFrame[i]->GetSize().y + fAdjSize), 0.0f));
		}
		else
		{
			m_pWarningFrame[i]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, m_pWarningFrame[i]->GetSize().y + fAdjSize, 0.0f));
		}
	}

	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CEmergency::Uninit(void)
{
	// 情報削除
	Release();
}

//==========================================================================
// 更新処理
//==========================================================================
void CEmergency::Update(void)
{
	if (CManager::GetInstance()->GetFade()->GetState() != CFade::STATE_NONE)
	{
		return;
	}

	for (int i = 0; i < 2; i++)
	{
		if (m_pWarningFrame[i] == nullptr)
		{
			continue;
		}

		D3DXVECTOR2 *pTex = m_pWarningFrame[i]->GetTex();
		float fMove = 0.001f - 0.002f * i;

		for (int nTex = 0; nTex < 4; nTex++)
		{
			pTex[nTex].x += fMove;
		}
	}

	// 状態別処理
	(this->*(m_StateFuncList[m_satate]))();
}

//==========================================================================
// 警報の更新
//==========================================================================
void CEmergency::UpdateEmergency(void)
{
	// 時間加算
	m_fTime += CManager::GetInstance()->GetDeltaTime();

	// 位置取得
	D3DXVECTOR3 textpos = m_pEmergencyText->GetPosition();
	textpos.x = EasingLinear(m_pEmergencyText->GetOriginPosition().x, DEST_POSITION_SCROLLTEXT, m_fTime / TIME_EMERGENCY);
	m_pEmergencyText->SetPosition(textpos);

	// 点滅処理
	D3DXCOLOR flashcolor = m_pEmergencyFlash->GetColor();
	flashcolor.a = 0.5f * sinf(D3DX_PI * (m_fTime / (TIME_EMERGENCY / static_cast<float>(NUM_FLASH))) * 2.0f);
	float fAlpha = 0.2f * sinf(D3DX_PI * (m_fTime / (TIME_EMERGENCY * 0.3f))) + 0.8f;
	m_pEmergencyFlash->SetColor(flashcolor);
	m_pEmergencyText->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha));

	if (m_fTime >= TIME_EMERGENCY)
	{
		// 終了処理
		m_pEmergencyText->Uninit();
		m_pEmergencyText = nullptr;

		m_pEmergencyFlash->Uninit();
		m_pEmergencyFlash = nullptr;

		// 状態遷移
		m_satate = STATE_WINDOW;
		m_fTime = 0.0f;
	}

}

//==========================================================================
// ウィンドウの更新
//==========================================================================
void CEmergency::UpdateWindow(void)
{
	// 時間加算
	m_fTime += CManager::GetInstance()->GetDeltaTime();

	D3DXCOLOR windowcolor = m_pWindow->GetColor();
	windowcolor.a = EasingLinear(0.0f, 1.0f, m_fTime / TIME_SPAWN_MISSIONWINDOW);
	m_pWindow->SetColor(windowcolor);

	for (int i = 0; i < 2; i++)
	{
		m_pWarningFrame[i]->SetColor(windowcolor);
	}

	if (m_fTime >= TIME_SPAWN_MISSIONWINDOW)
	{
		// 状態遷移
		m_satate = STATE_MISSION;
		m_fTime = 0.0f;
		m_pMissionText->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

//==========================================================================
// ミッションの更新
//==========================================================================
void CEmergency::UpdateMission(void)
{
	// 時間加算
	m_fTime += CManager::GetInstance()->GetDeltaTime();

	// テクスチャのオブジェクト取得
	CTexture *pTexture = CManager::GetInstance()->GetTexture();
	D3DXVECTOR2 imagesize = pTexture->GetImageSize(m_pMissionText->GetIdxTexture()) * 0.5f;

	// サイズ更新
	D3DXVECTOR2 size = m_pMissionText->GetSize();
	InertiaCorrection(size.x, imagesize.x, 0.25f);
	InertiaCorrection(size.y, imagesize.y, 0.25f);
	m_pMissionText->SetSize(size);

	if (m_fTime >= TIME_SPAWN_MISSIONTEXT)
	{
		// 状態遷移
		m_satate = STATE_END;
		m_fTime = 0.0f;
	}
}

//==========================================================================
// 終了
//==========================================================================
void CEmergency::UpdateEnd(void)
{
	// キーボード情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// ゲームパッド情報取得
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, 0))
	{
		// 終了処理
		m_pWindow->Uninit();
		m_pWindow = nullptr;
		m_pMissionText->Uninit();
		m_pMissionText = nullptr;

		for (int i = 0; i < 2; i++)
		{
			m_pWarningFrame[i]->Uninit();
			m_pWarningFrame[i] = nullptr;
		}

		Uninit();

		CGame::GetGameManager()->SetType(CGameManager::SCENE_MAIN);
	}
}

//==========================================================================
// 描画処理
//==========================================================================
void CEmergency::Draw(void)
{

}
