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

//==========================================================================
// マクロ定義
//==========================================================================
#define TEXTURE			"data\\TEXTURE\\number_blackclover_01.png"	// テクスチャのファイル
#define MAX_VALUE		(999999)						// 値の最大値
#define TEX_U			(0.1f)							// Uの分割
#define WIDTH			(40.0f)							// 横幅
#define HEIGHT			(50.0f)							// 縦幅
#define DIS_X			(50.0f)							// 間隔
#define SCROLL_SPEED	(-0.005f)						// スクロール速度

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================

//==========================================================================
// コンストラクタ
//==========================================================================
CTimer::CTimer(int nPriority)
{
	// 値のクリア
	m_apNumber = NULL;
	m_nNum = 0;		// 値
	m_nCntTime = 0;	// 時間のカウント
	m_nTexIdx = 0;		// テクスチャのインデックス番号
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
			pScore->Init();
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
HRESULT CTimer::Init(void)
{
	m_nNum = START_TIME;	// 値

	// 値の設定処理
	SetValue();

	return S_OK;
}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CTimer::Init(D3DXVECTOR3 pos)
{
	m_nNum = START_TIME;	// 値

	// 生成処理
	m_apNumber = CMultiNumber::Create(pos, D3DXVECTOR2(WIDTH, HEIGHT), NUM_TIMER, CNumber::OBJECTTYPE_2D);

	// 値の設定処理
	m_apNumber->SetValue();

	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CTimer::Uninit(void)
{
	// 数字のオブジェクトの終了処理
	if (m_apNumber != NULL)
	{
		m_apNumber->Uninit();
		delete m_apNumber;
		m_apNumber = NULL;
	}
}

//==========================================================================
// 更新処理
//==========================================================================
void CTimer::Update(void)
{
	// 時間のカウント加算
	m_nCntTime = (m_nCntTime + 1) % 60;

	if (m_nCntTime == 0)
	{// 1秒で更新

		// 1秒経過
		Add(-1);
	}

	// 値の設定処理
	m_apNumber->SetValue(m_nNum);
}

//==========================================================================
// 値の設定処理
//==========================================================================
void CTimer::SetValue(void)
{
	int aTexU[NUM_TIMER];
	int nMin;	// 分
	int nSec;	// 秒

	// 分を割り出し
	nMin = m_nNum / 60;

	// 秒を割り出し
	nSec = m_nNum % 60;

	// テクスチャ座標に代入する
	aTexU[0] = nMin % 100 / 10;	// 10の位
	aTexU[1] = nMin % 10;		// 1の位

	aTexU[2] = nSec % 100 / 10;	// 10の位
	aTexU[3] = nSec % 10;		// 1の位
}

//==========================================================================
// 描画処理
//==========================================================================
void CTimer::Draw(void)
{

}

//==========================================================================
// 加算処理
//==========================================================================
void CTimer::Add(int nValue)
{
	// 値加算
	m_nNum += nValue;

	if (m_nNum < 0)
	{// 0で固定
		m_nNum = 0;

		// モード設定
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RESULT);
	}

	// 値の設定処理
	SetValue();
}
