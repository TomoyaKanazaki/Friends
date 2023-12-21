//=============================================================================
// 
//  フェード処理 [fade.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "fade.h"
#include "manager.h"
#include "renderer.h"
#include "object2D.h"

//==========================================================================
// マクロ定義
//==========================================================================
#define ALPHAMOVE	(0.025f)

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================

//==========================================================================
// コンストラクタ
//==========================================================================
CFade::CFade()
{
	// 値のクリア
	m_aObject2D = NULL;					// オブジェクト2Dのオブジェクト
	m_ModeNext = CScene::MODE_TITLE;	// 次のモード
	m_state = STATE_NONE;				// 状態
}

//==========================================================================
// デストラクタ
//==========================================================================
CFade::~CFade()
{

}

//==========================================================================
// 生成処理
//==========================================================================
CFade *CFade::Create(void)
{
	// 生成用のオブジェクト
	CFade *pFade = NULL;

	if (pFade == NULL)
	{// NULLだったら

		// メモリの確保
		pFade = DEBUG_NEW CFade;

		if (pFade != NULL)
		{// メモリの確保が出来ていたら

			// 初期化処理
			if (FAILED(pFade->Init()))
			{// 失敗していたら
				return NULL;
			}
		}
		else
		{
			delete pFade;
			pFade = NULL;
		}

		return pFade;
	}

	return NULL;
}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CFade::Init(void)
{
	// 生成処理
	m_aObject2D = CObject2D::Create(8);

	if (m_aObject2D == NULL)
	{// 失敗していたら
		return E_FAIL;
	}

	m_state = STATE_FADEIN;			// 状態
#if _DEBUG
	m_ModeNext = CScene::MODE_TUTORIAL;	// 次のモード
	//m_ModeNext = CScene::MODE_TITLE;	// 次のモード
	//m_ModeNext = CScene::MODE_DECIDE;	// 次のモード
	//m_ModeNext = CScene::MODE_RESULT;	// 次のモード
#else
	m_ModeNext = CScene::MODE_TITLE;	// 次のモード
#endif
	
	m_aObject2D->SetSize(D3DXVECTOR2(640.0f, 360.0f));	// サイズ
	m_aObject2D->SetPosition(D3DXVECTOR3(640.0f, 360.0f, 0.0f));	// 位置
	m_aObject2D->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));	// 色設定

	// 最初だけ次の画面へ
	CManager::GetInstance()->SetMode(m_ModeNext);

	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CFade::Uninit(void)
{
	if (m_aObject2D != NULL)
	{// NULLじゃなかったら

		// 終了処理
		m_aObject2D->Uninit();
		delete m_aObject2D;
		m_aObject2D = NULL;
	}
}

//==========================================================================
// 更新処理
//==========================================================================
void CFade::Update(void)
{
	// 色取得
	D3DXCOLOR col = m_aObject2D->GetColor();

	switch (m_state)
	{
	case STATE_NONE:
		break;

	case STATE_FADEOUT:

		// 不透明度増加
		col.a += ALPHAMOVE;

		if (col.a >= 1.0f)
		{
			col.a = 1.0f;
			m_state = STATE_FADEIN;

			// 次の画面へ
			CManager::GetInstance()->SetMode(m_ModeNext);
		}
		break;

	case STATE_FADEIN:

		// 不透明度減少
		col.a -= ALPHAMOVE;

		if (col.a <= 0.0f)
		{
			col.a = 0.0f;
			m_state = STATE_NONE;
		}
		break;
	}

	// 色設定
	m_aObject2D->SetColor(col);

	// 更新処理
	m_aObject2D->Update();

	m_aObject2D->SetVtx();

}

//==========================================================================
// 描画処理
//==========================================================================
void CFade::Draw(void)
{
	// 描画処理
	m_aObject2D->Draw();
}

//==========================================================================
// 次のモード設定
//==========================================================================
void CFade::SetFade(CScene::MODE mode)
{
	if (m_state == STATE_NONE)
	{// 何もしていないとき

		// 次のモード設定
		m_ModeNext = mode;
		m_state = STATE_FADEOUT;	// フェードアウト状態に設定

		// 色設定
		m_aObject2D->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
}

//==========================================================================
// 状態取得
//==========================================================================
CFade::STATE CFade::GetState(void)
{
	return m_state;
}

//==========================================================================
// オブジェクト2Dオブジェクトの取得
//==========================================================================
CObject2D *CFade::GetMyObject(void)
{
	return m_aObject2D;
}