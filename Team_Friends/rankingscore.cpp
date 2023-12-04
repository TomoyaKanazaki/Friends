//=============================================================================
// 
//  ランキングスコア処理 [rankingscore.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "rankingscore.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"
#include "object2D.h"
#include "multinumber.h"
#include "calculation.h"
#include "ranking.h"
#include "rankingmanager.h"
#include "sound.h"
#include "input.h"

//==========================================================================
// マクロ定義
//==========================================================================
#define RANKINGFILE			"data\\BIN\\ranking.bin"
#define NUMBERTEXTURE		"data\\TEXTURE\\number_blackclover_01.png"	// テクスチャのファイル
#define TEX_U				(0.1f)				// Uの分割
#define BASE_WIDTH			(0.8f)		// 横幅
#define BASE_HEIGHT			(1.0f)		// 縦幅
#define BASE_DIS_X			(0.0f)		// 間隔
#define DIS_Y				(2.0f)				// 間隔
#define POSY_BASE			(330.0f)			// Y位置
#define BASETEXT_POSX		(180.0f)			// X位置
#define TEXT_MOVETIME		(50000)				// 移動時間
#define INIT_POSX			(1600.0f)			// 初期位置
#define INIT_POSY			(943.0f)			// 初期位置
#define INIT_POS_A			(-1)			// 初期位置
#define INIT_POS_B			(3.5f)			// 初期位置

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================
const char *CRankingScore::m_apTexture3DFile[VTX3D_MAX] =		// テクスチャのファイル
{
	"data\\TEXTURE\\rankingnum_01.png",
	"data\\TEXTURE\\ranking_virtual_window_00.png",
	"data\\TEXTURE\\ranking_virtual_window_01.png",
	"data\\TEXTURE\\ranking_shadow_00.png",
	"data\\TEXTURE\\rankinglogo_02.png",
};

const char *CRankingScore::m_apTexture3D_WinFile =		// テクスチャのファイル
{
	"data\\TEXTURE\\ranking_virtual_window_03.png",
};

//==========================================================================
// コンストラクタ
//==========================================================================
CRankingScore::CRankingScore(int nPriority)
{
	// 値のクリア
	m_nNumRanking = 0;				// ランキング数
	memset(&m_nScore[0], 0, sizeof(m_nScore));	// スコア
	memset(&m_nRank[0], 0, sizeof(m_nRank));	// スコア
	m_nNowScore = 0;		// 今回のスコア
	m_nTexIdxNumber = 0;			// 数字テクスチャのインデックス番号
	m_nIdxNewRecord = 0;	// テクスチャのインデックス番号
	m_nCntNewRecord = 0;			// ニューレコードのカウンター
	m_nCnt = 0;
	memset(&m_fPosDestY[0], 0, sizeof(m_fPosDestY));	// 目標の位置
	m_bNewRecord = 0;	// オブジェクト2Dのオブジェクト
	memset(&m_bArrival[0], NULL, sizeof(m_bArrival));	// 到着判定
	memset(&m_pScore[0], NULL, sizeof(m_pScore));	// 数字のオブジェクト
	memset(&m_pRank[0], NULL, sizeof(m_pRank));	// 数字のオブジェクト
}

//==========================================================================
// デストラクタ
//==========================================================================
CRankingScore::~CRankingScore()
{

}

//==========================================================================
// 生成処理
//==========================================================================
CRankingScore *CRankingScore::Create(void)
{
	// 生成用のオブジェクト
	CRankingScore *pScore = NULL;

	if (pScore == NULL)
	{// NULLだったら

	 // メモリの確保
		pScore = DEBUG_NEW CRankingScore;

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
// 初期化処理
//==========================================================================
HRESULT CRankingScore::Init(void)
{
	// 種類設定
	SetType(CObject::TYPE_SCORE);

	for (int nCntVtx = 0; nCntVtx < VTX3D_MAX; nCntVtx++)
	{
		// 生成処理
		m_pObj3D[nCntVtx] = CObject3D::Create(6);

		// テクスチャの割り当て
		m_nTexIdx3D[nCntVtx] = CManager::GetInstance()->GetTexture()->Regist(m_apTexture3DFile[nCntVtx]);

		// テクスチャの割り当て
		m_pObj3D[nCntVtx]->GetObject3D()->BindTexture(m_nTexIdx3D[nCntVtx]);

		// 各種変数の初期化
		switch (nCntVtx)
		{
		case VTX_LOGO:
			m_pObj3D[nCntVtx]->GetObject3D()->SetSize(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).x * 0.003f,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).y * 0.003f,
				0.0f));	// サイズ

			m_pObj3D[nCntVtx]->GetObject3D()->SetPosition(D3DXVECTOR3(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetSize().x + 63.0f - cosf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * 6.5f,
				m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetSize().y + INIT_POSY + 5.0f,
				-150.0f + sinf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * 6.5f));	// 位置

			m_pObj3D[nCntVtx]->GetObject3D()->SetRotation(D3DXVECTOR3(0.0f, 0.5f, 0.0f));	// 向き
			break;



		case VTX_NUM:
			m_pObj3D[nCntVtx]->GetObject3D()->SetSize(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).x * 0.5f,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).y * 0.5f,
				0.0f));	// サイズ

			m_pObj3D[nCntVtx]->SetPosition(D3DXVECTOR3(m_pObj3D[nCntVtx]->GetSize().x, 360.0f, 0.0f));	// 位置
			break;



		case VTX3D_VIRTUAL_WINDOW_00:
			m_pObj3D[nCntVtx]->GetObject3D()->SetSize(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).x * 0.13f,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).y * 0.13f,
				0.0f));	// サイズ

			m_pObj3D[nCntVtx]->GetObject3D()->SetPosition(D3DXVECTOR3(m_pObj3D[nCntVtx]->GetSize().x + 63.0f, m_pObj3D[nCntVtx]->GetSize().y + INIT_POSY, -150.0f));	// 位置
			m_pObj3D[nCntVtx]->GetObject3D()->SetRotation(D3DXVECTOR3(0.0f, 0.5f, 0.0f));	// 向き
			break;



		case VTX3D_VIRTUAL_WINDOW_01:
			m_pObj3D[nCntVtx]->GetObject3D()->SetSize(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).x * 0.13f,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).y * 0.13f,
				0.0f));	// サイズ

			m_pObj3D[nCntVtx]->GetObject3D()->SetPosition(D3DXVECTOR3(m_pObj3D[nCntVtx]->GetSize().x + 63.0f, m_pObj3D[nCntVtx]->GetSize().y + INIT_POSY, -150.0f));	// 位置
			m_pObj3D[nCntVtx]->GetObject3D()->SetRotation(D3DXVECTOR3(0.0f, 0.5f, 0.0f));	// 向き
			break;



		case VTX3D_SHADOE_00:
			m_pObj3D[nCntVtx]->GetObject3D()->SetSize(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).x * 0.14f,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).y * 0.14f,
				0.0f));	// サイズ

			m_pObj3D[nCntVtx]->GetObject3D()->SetPosition(D3DXVECTOR3(m_pObj3D[nCntVtx]->GetSize().x + 66.0f, m_pObj3D[nCntVtx]->GetSize().y + INIT_POSY - 9.0f, -143.0f));	// 位置
			m_pObj3D[nCntVtx]->GetObject3D()->SetRotation(D3DXVECTOR3(D3DX_PI / 2, 0.5f, 0.0f));	// 向き
			break;

		default:
			break;
		}

		// 種類の設定
		m_pObj3D[nCntVtx]->GetObject3D()->SetType(CObject::TYPE_OBJECT3D);
	}

	for (int nCntVtx = 0; nCntVtx < WINDOW_WHITE_NUM; nCntVtx++)
	{
		// 生成処理
		m_pObj3D_Win[nCntVtx] = CObject3D::Create(6);

		// テクスチャの割り当て
		m_nTexIdx3D_Win = CManager::GetInstance()->GetTexture()->Regist(m_apTexture3D_WinFile);

		// テクスチャの割り当て
		m_pObj3D_Win[nCntVtx]->GetObject3D()->BindTexture(m_nTexIdx3D_Win);

		switch (nCntVtx)
		{
		case 0:
			m_pObj3D_Win[nCntVtx]->GetObject3D()->SetSize(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D_Win).x * 0.12f,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D_Win).y * 0.12f,
				0.0f));	// サイズ

			m_pObj3D_Win[nCntVtx]->GetObject3D()->SetPosition(D3DXVECTOR3(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetSize().x + 63.0f - cosf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * 6.5f,
				m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetSize().y + INIT_POSY + 1.5f,
				-150.0f + sinf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * 6.5f));	// 位置

			break;



		case 1:
			m_pObj3D_Win[nCntVtx]->GetObject3D()->SetSize(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D_Win).x * 0.08f,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D_Win).y * 0.08f,
				0.0f));	// サイズ

			m_pObj3D_Win[nCntVtx]->GetObject3D()->SetPosition(D3DXVECTOR3(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetSize().x + 63.0f - cosf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * 4.6f,
				m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetSize().y + INIT_POSY + 0.2f,
				-150.0f + sinf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * 4.6f));	// 位置
			break;



		case 2:
			m_pObj3D_Win[nCntVtx]->GetObject3D()->SetSize(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D_Win).x * 0.1f,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D_Win).y * 0.1f,
				0.0f));	// サイズ

			m_pObj3D_Win[nCntVtx]->GetObject3D()->SetPosition(D3DXVECTOR3(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetSize().x + 63.0f - cosf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * 5.6f,
				m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetSize().y + INIT_POSY - 1.6f,
				-150.0f + sinf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * 5.6f));	// 位置
			break;

		default:
			break;
		}

		m_pObj3D_Win[nCntVtx]->GetObject3D()->SetRotation(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation());	// 向き

		// 種類の設定
		m_pObj3D_Win[nCntVtx]->GetObject3D()->SetType(CObject::TYPE_OBJECT3D);
	}

	for (int nCntRanking = 0; nCntRanking < RANKINGNUM; nCntRanking++)
	{
		// 生成処理
		m_pScore[nCntRanking] = CMultiNumber::Create(D3DXVECTOR3(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetSize().x + 63.0f - cosf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * INIT_POS_A,
			-nCntRanking * DIS_Y + INIT_POSY + 10.0f,
			-150.0f + sinf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * INIT_POS_A),
			D3DXVECTOR2(BASE_WIDTH, BASE_HEIGHT),
			RANKINGSCORE_DIGIT,
			CNumber::OBJECTTYPE_3D,
			true,
			7);

		m_pScore[nCntRanking]->SetRotation(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation());
		m_pScore[nCntRanking]->SetPosition(m_pScore[nCntRanking]->GetPosition());

		if (nCntRanking >= RANKING_DISPLAY_NUM)
		{
			m_pScore[nCntRanking]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}

		// 目標の位置
		m_fPosDestY[nCntRanking] = INIT_POSY + 11.0f + RANKINGNUM * DIS_Y;


		m_pRank[nCntRanking] = CMultiNumber::Create(D3DXVECTOR3(m_pScore[nCntRanking]->GetPosition().x - cosf(m_pScore[nCntRanking]->GetRotation().y) * INIT_POS_B,
			m_pScore[nCntRanking]->GetPosition().y,
			m_pScore[nCntRanking]->GetPosition().z + sinf(m_pScore[nCntRanking]->GetRotation().y) * INIT_POS_B),
			D3DXVECTOR2(BASE_WIDTH, BASE_HEIGHT),
			RANKINGRANK_DIGIT,
			CNumber::OBJECTTYPE_3D,
			true,
			7);

		m_pRank[nCntRanking]->SetRotation(m_pScore[nCntRanking]->GetRotation());
		m_pRank[nCntRanking]->SetPosition(m_pRank[nCntRanking]->GetPosition());

		if (nCntRanking >= RANKING_DISPLAY_NUM)
		{
			m_pRank[nCntRanking]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}

	// ランキング読み込み
	Load();

	for (int nCntRanking = 1; nCntRanking <= m_nNumRanking; nCntRanking++)
	{
		m_nRank[nCntRanking - 1] = nCntRanking;
	}

	if (CManager::GetInstance()->GetOldMode() == CScene::MODE_RESULT)
	{
		m_nNowScore = CManager::GetInstance()->GetRankingManager()->GetNowScore();

		// ソート処理
		Sort();

		// セーブ処理
		Save();
	}

	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CRankingScore::Uninit(void)
{
	// 終了処理
	for (int nCntVtx = 0; nCntVtx < VTX3D_MAX; nCntVtx++)
	{
		if (m_pObj3D[nCntVtx] != NULL)
		{// メモリの確保がされていたら

		 // 終了処理
			m_pObj3D[nCntVtx]->Uninit();
			m_pObj3D[nCntVtx] = NULL;
		}
	}

	for (int nCntRanking = 0; nCntRanking < RANKINGNUM; nCntRanking++)
	{
		// 終了処理
		if (m_pScore[nCntRanking] != NULL)
		{// メモリの確保がされていたら

		 // 終了処理
			m_pScore[nCntRanking]->Uninit();
			delete m_pScore[nCntRanking];
			m_pScore[nCntRanking] = NULL;
		}
	}

	for (int nCntRanking = 0; nCntRanking < RANKINGNUM; nCntRanking++)
	{
		// 終了処理
		if (m_pRank[nCntRanking] != NULL)
		{// メモリの確保がされていたら

		 // 終了処理
			m_pRank[nCntRanking]->Uninit();
			delete m_pRank[nCntRanking];
			m_pRank[nCntRanking] = NULL;
		}
	}

	// 情報削除
	Release();
}

//==========================================================================
// 更新処理
//==========================================================================
void CRankingScore::Update(void)
{
	// キーボード情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// ゲームパッド情報取得
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	m_nCnt++;

	if (m_nCnt >= 60 * 2)
	{
		// 移動処理
		MovingScore();

		MovingRank();

		m_nCnt = 60 * 2;
	}

	// 値の設定処理
	for (int nCntRanking = 0; nCntRanking < RANKINGNUM; nCntRanking++)
	{
		m_pScore[nCntRanking]->SetValue(m_nScore[nCntRanking]);

		m_pScore[nCntRanking]->Update();

		m_pRank[nCntRanking]->SetValue(m_nRank[nCntRanking]);

		m_pRank[nCntRanking]->Update();
	}

	if (m_bNewRecord == true)
	{// 記録更新していたら

	 // ニューレコードの更新処理
		UpdateNewRecord();
	}
}

//==========================================================================
// 移動処理
//==========================================================================
void CRankingScore::MovingScore(void)
{
	for (int nCntRanking = 0; nCntRanking < RANKINGNUM; nCntRanking++)
	{
		// 位置取得
		D3DXVECTOR3 pos = m_pScore[nCntRanking]->GetPosition();

		if (pos.y >= INIT_POSY + 11.2f)
		{
			D3DXCOLOR col = m_pScore[nCntRanking]->GetColor();

			col.a -= 0.05f;

			m_pScore[nCntRanking]->SetColor(col);
		}

		else if (pos.y >= INIT_POSY + 9.0f - ((RANKING_DISPLAY_NUM - 1) * DIS_Y) && pos.y < INIT_POSY + 9.0f)
		{
			D3DXCOLOR col = m_pScore[nCntRanking]->GetColor();

			col.a += 0.05f;

			if (col.a >= 1.0f)
			{
				col.a = 1.0f;
			}

			m_pScore[nCntRanking]->SetColor(col);
		}

		float fDest = m_fPosDestY[nCntRanking] - nCntRanking * DIS_Y;


		// 目標の位置へ補正
		if (fDest > pos.y)
		{
			pos.y += (fDest - (nCntRanking * DIS_Y)) / (float)TEXT_MOVETIME;
		}

		if (fDest < pos.y)
		{// 目標で固定
			pos.y = m_fPosDestY[nCntRanking] + nCntRanking * DIS_Y;
			m_bArrival[nCntRanking] = true;

			if (nCntRanking == RANKINGNUM - 1)
			{
				CRanking::SetEnableArrival();
			}

			//// サウンド再生
			//CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_RANKINGSCORE);
		}

		// 位置設定
		m_pScore[nCntRanking]->SetPosition(pos);
	}
}

//==========================================================================
// 移動処理
//==========================================================================
void CRankingScore::MovingRank(void)
{
	for (int nCntRanking = 0; nCntRanking < RANKINGNUM; nCntRanking++)
	{
		// 位置取得
		D3DXVECTOR3 pos = m_pRank[nCntRanking]->GetPosition();

		if (pos.y >= INIT_POSY + 11.2f)
		{
			D3DXCOLOR col = m_pRank[nCntRanking]->GetColor();

			col.a -= 0.05f;

			m_pRank[nCntRanking]->SetColor(col);
		}

		else if (pos.y >= INIT_POSY + 9.0f - ((RANKING_DISPLAY_NUM - 1) * DIS_Y) && pos.y < INIT_POSY + 9.0f)
		{
			D3DXCOLOR col = m_pRank[nCntRanking]->GetColor();

			col.a += 0.05f;

			if (col.a >= 1.0f)
			{
				col.a = 1.0f;
			}

			m_pRank[nCntRanking]->SetColor(col);
		}

		float fDest = m_fPosDestY[nCntRanking] - nCntRanking * DIS_Y;


		// 目標の位置へ補正
		if (fDest > pos.y)
		{
			pos.y += (fDest - (nCntRanking * DIS_Y)) / (float)TEXT_MOVETIME;
		}

		if (fDest < pos.y)
		{// 目標で固定
			pos.y = m_fPosDestY[nCntRanking] + nCntRanking * DIS_Y;
			m_bArrival[nCntRanking] = true;

			if (nCntRanking == RANKINGNUM - 1)
			{
				CRanking::SetEnableArrival();
			}

			//// サウンド再生
			//CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_RANKINGSCORE);
		}

		// 位置設定
		m_pRank[nCntRanking]->SetPosition(pos);
	}
}

//==========================================================================
// ニューレコードの更新処理
//==========================================================================
void CRankingScore::UpdateNewRecord(void)
{

	// 位置取得
	D3DXVECTOR3 pos = m_pScore[m_nIdxNewRecord]->GetPosition();

	// 色取得
	D3DXCOLOR col = m_pScore[m_nIdxNewRecord]->GetColor();

	// 曲線補正
	CuadricCurveComp(col.a, 180, 0.3f, 1.0f, m_nCntNewRecord);

	// 位置設定
	m_pScore[m_nIdxNewRecord]->SetPosition(pos);

	// 色設定
	m_pScore[m_nIdxNewRecord]->SetColor(col);
}

//==========================================================================
// 全ての到着設定
//==========================================================================
void CRankingScore::SetAllArrival(void)
{

	for (int nCntRanking = 0; nCntRanking < RANKINGNUM; nCntRanking++)
	{
		m_bArrival[nCntRanking] = true;	// 到着判定
	}

	for (int nCntRanking = 0; nCntRanking < RANKINGNUM; nCntRanking++)
	{
		// 位置取得
		D3DXVECTOR3 pos = m_pScore[nCntRanking]->GetPosition();

		if (pos.x == INIT_POSX)
		{
			// サウンド再生
			CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_NUMBERMOVE);
		}

		// 色取得
		D3DXCOLOR col = m_pScore[nCntRanking]->GetColor();

		// 移動
		float fDest = m_fPosDestY[nCntRanking] + nCntRanking * DIS_Y;
		pos.x = fDest;

		// 不透明度設定
		col.a = 1.0f;

		// 位置設定
		m_pScore[nCntRanking]->SetPosition(pos);

		// 色設定
		m_pScore[nCntRanking]->SetColor(col);
	}

}


//==========================================================================
// 描画処理
//==========================================================================
void CRankingScore::Draw(void)
{

}

//==============================================================
// ソート処理
//==============================================================
void CRankingScore::Sort(void)
{
	// 降順処理

	for (int nCntData = 0; nCntData < m_nNumRanking - 1; nCntData++)
	{
		for (int nCntSort = nCntData + 1; nCntSort < m_nNumRanking; nCntSort++)
		{
			if (m_nScore[nCntData] < m_nScore[nCntSort])
			{// 要素1より要素2が大きかったら

				int nTemp = m_nScore[nCntData];
				m_nScore[nCntData] = m_nScore[nCntSort];
				m_nScore[nCntSort] = nTemp;
			}

		}

		// ランキング最大値よりも今回のが小さかったら
		if (m_nScore[m_nNumRanking - 1] < m_nNowScore)
		{// 入れ替え

			m_nScore[m_nNumRanking - 1] = m_nNowScore;	// 最小値と今回のデータ入れ替え
			m_bNewRecord = true;	// フラグON
		}
	}



	// 降順処理
	for (int nCntData = 0; nCntData < m_nNumRanking - 1; nCntData++)
	{
		for (int nCntSort = nCntData + 1; nCntSort < m_nNumRanking; nCntSort++)
		{
			if (m_nScore[nCntData] < m_nScore[nCntSort])
			{// 要素1より要素2が大きかったら

				int nTemp = m_nScore[nCntData];
				m_nScore[nCntData] = m_nScore[nCntSort];
				m_nScore[nCntSort] = nTemp;
			}
		}


		if (m_bNewRecord == true)
		{// ニューレコードの時

			for (int nCount = RANKINGNUM; nCount > 0; nCount--)
			{// 要素番号記憶して抜ける

				if (m_nScore[nCount - 1] == m_nNowScore)
				{
					m_nIdxNewRecord = nCount - 1;
					break;
				}
			}
		}
	}
}

//==============================================================
// セーブ処理
//==============================================================
void CRankingScore::Save(void)
{
	FILE *pFile;

	// ファイルを開く
	pFile = fopen(RANKINGFILE, "wb");

	if (pFile != NULL)
	{// ファイルが開けた場合

	 // ファイルに数値を書き出す
		fwrite(&m_nNumRanking, sizeof(int), 1, pFile);

		fwrite(&m_nScore[0], sizeof(int), m_nNumRanking, pFile);

		// ファイルを閉じる
		fclose(pFile);
	}
}

//==============================================================
// ロード処理
//==============================================================
void CRankingScore::Load(void)
{
	FILE *pFile;

	// ファイルを開く
	pFile = fopen(RANKINGFILE, "rb");

	if (pFile != NULL)
	{// ファイルが開けた場合
	 // ファイルに数値を読み込む
		fread(&m_nNumRanking, sizeof(int), 1, pFile);

		fread(&m_nScore[0], sizeof(int), m_nNumRanking, pFile);

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{// ファイルが開けなかった場合

		m_nNumRanking = RANKINGNUM;

		for (int nCount = 0; nCount < m_nNumRanking; nCount++)
		{// 全部ゼロ
			m_nScore[nCount] = 150000 - nCount * 5000;
		}

		// セーブ
		Save();
	}
}