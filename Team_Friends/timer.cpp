//=============================================================================
// 
//  タイマー処理 [timer.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "timer.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"
#include "object2D.h"
#include "multinumber.h"
#include "fade.h"
#include "debugproc.h"
#include "calculation.h"

//==========================================================================
// マクロ定義
//==========================================================================
namespace
{
	const char* TEXTURE = "data\\TEXTURE\\number_blackclover_01.png";	// テクスチャのファイル
	const float TEX_U = 0.1f;			// Uの分割
	const float WIDTH = 50.0f;			// 横幅
	const float HEIGHT = 50.0f;			// 縦幅
	const float DIS_X = 50.0f;			// 間隔
	const int MAX_VALUE = 999999;		// 値の最大値
	const int NUM_TIMER = 2;			// 桁数
	const int MAX_TIME = (60 * 99) * 1000;		// タイマーの最大数
	const int START_TIME = 60 * 30;		// タイマーの初期値
}

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================

//==========================================================================
// コンストラクタ
//==========================================================================
CTimer::CTimer(int nPriority)
{
	// 値のクリア
	m_pMinutes = nullptr;		// 分のオブジェクト
	m_pSeconds = nullptr;		// 秒のオブジェクト
	m_pMilliSeconds = nullptr;	// ミリ秒のオブジェクト
	m_fTime = 0.0f;				// 時間
}

//==========================================================================
// デストラクタ
//==========================================================================
CTimer::~CTimer()
{

}

//==========================================================================
// 生成処理
//==========================================================================
CTimer *CTimer::Create(void)
{
	// 生成用のオブジェクト
	CTimer *pScore = NULL;

	if (pScore == NULL)
	{// NULLだったら

		// メモリの確保
		pScore = DEBUG_NEW CTimer;

		if (pScore != NULL)
		{// メモリの確保が出来ていたら

			// 初期化処理
			pScore->Init(mylib_const::DEFAULT_VECTOR3);
		}

		return pScore;
	}

	return NULL;
}

//==========================================================================
// 生成処理
//==========================================================================
CTimer *CTimer::Create(D3DXVECTOR3 pos)
{
	// 生成用のオブジェクト
	CTimer *pScore = NULL;

	if (pScore == NULL)
	{// NULLだったら

		// メモリの確保
		pScore = DEBUG_NEW CTimer;

		if (pScore != NULL)
		{// メモリの確保が出来ていたら

			// 初期化処理
			pScore->Init(pos);
		}

		return pScore;
	}

	return NULL;
}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CTimer::Init(D3DXVECTOR3 pos)
{
	m_fTime = START_TIME * 1000.0f;	// 時間

	// 生成処理
	D3DXVECTOR3 spawnpos = pos;
	m_pMinutes = CMultiNumber::Create(spawnpos, D3DXVECTOR2(WIDTH, HEIGHT), NUM_TIMER, CNumber::OBJECTTYPE_2D, TEXTURE, false);

	spawnpos.x += (WIDTH * NUM_TIMER) * 1.3f;
	m_pSeconds = CMultiNumber::Create(spawnpos, D3DXVECTOR2(WIDTH, HEIGHT), NUM_TIMER, CNumber::OBJECTTYPE_2D, TEXTURE, false);

	spawnpos.x += (WIDTH * NUM_TIMER) * 1.3f;
	m_pMilliSeconds = CMultiNumber::Create(spawnpos, D3DXVECTOR2(WIDTH, HEIGHT), NUM_TIMER, CNumber::OBJECTTYPE_2D, TEXTURE, false);

	// 値の設定処理
	m_pMinutes->SetValue();
	m_pSeconds->SetValue();
	m_pMilliSeconds->SetValue();

	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CTimer::Uninit(void)
{
	// 数字のオブジェクトの終了処理
	if (m_pMinutes != NULL)
	{
		m_pMinutes->Uninit();
		delete m_pMinutes;
		m_pMinutes = NULL;
	}
	if (m_pSeconds != NULL)
	{
		m_pSeconds->Uninit();
		delete m_pSeconds;
		m_pSeconds = NULL;
	}
	if (m_pMilliSeconds != NULL)
	{
		m_pMilliSeconds->Uninit();
		delete m_pMilliSeconds;
		m_pMilliSeconds = NULL;
	}
}

//==========================================================================
// 更新処理
//==========================================================================
void CTimer::Update(void)
{
	// 時間減算
	m_fTime -= CManager::GetInstance()->GetDeltaTime() * 1000.0f;
	ValueNormalize(m_fTime, static_cast<float>(MAX_TIME), 0.0f);

	// 分、秒、ミリ秒の計算
	int minutes = static_cast<int>(m_fTime) / (60 * 1000);
	int seconds = (static_cast<int>(m_fTime) % (60 * 1000)) / 1000;
	int milliseconds = static_cast<int>(m_fTime) % 1000;

	// 値の設定処理
	if (m_pMinutes != NULL)
	{
		m_pMinutes->SetValue(minutes);
	}
	if (m_pSeconds != NULL)
	{
		m_pSeconds->SetValue(seconds);
	}
	if (m_pMilliSeconds != NULL)
	{
		m_pMilliSeconds->SetValue(milliseconds);
	}
	// デバッグ表示
	CManager::GetInstance()->GetDebugProc()->Print(
		"------------------[時間：%d分、%d秒、%d]------------------\n", minutes, seconds, milliseconds);
}

//==========================================================================
// 描画処理
//==========================================================================
void CTimer::Draw(void)
{

}
