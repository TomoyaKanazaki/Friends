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
#define NUMBERTEXTURE		"data\\TEXTURE\\number_blackclover_03.png"	// テクスチャのファイル
#define NUMBERTEXTURE_01	"data\\TEXTURE\\number_blackclover_04.png"	// テクスチャのファイル
#define NUMBERTEXTURE_02	"data\\TEXTURE\\number_blackclover_05.png"	// テクスチャのファイル
#define NUMBERTEXTURE_03	"data\\TEXTURE\\number_blackclover_06.png"	// テクスチャのファイル
#define NUMBERTEXTURE_04	"data\\TEXTURE\\number_blackclover_07.png"	// テクスチャのファイル
#define TEX_U				(0.1f)				// Uの分割
#define BASE_WIDTH			(0.8f)		// 横幅
#define BASE_HEIGHT			(1.0f)		// 縦幅
#define BASE_DIS_X			(0.0f)		// 間隔
#define DIS_Y				(2.0f)				// 間隔
#define POSY_BASE			(330.0f)			// Y位置
#define BASETEXT_POSX		(180.0f)			// X位置
#define TEXT_MOVETIME		(50000)				// 移動時間
#define SIZE_MOVETIME		(20)				// 移動時間
#define INIT_POSX			(1600.0f)			// 初期位置
#define INIT_POSY			(943.0f)			// 初期位置
#define INIT_POS_A			(-1)			// 初期位置
#define INIT_POS_B			(3.3f)			// 初期位置

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================
const char *CRankingScore::m_apTexture3DFile[VTX3D_MAX] =		// テクスチャのファイル
{
	"data\\TEXTURE\\ranking_virtual_window_00.png",
	"data\\TEXTURE\\ranking_virtual_window_09.png",
	"data\\TEXTURE\\ranking_shadow_00.png",
	"data\\TEXTURE\\rankinglogo_02.png",
	"data\\TEXTURE\\neet_vision2.png",
};

const char *CRankingScore::m_apTexture3D_WinFile[POPAPP_TEX_NUM] =		// ポップアップテクスチャのファイル
{
	"data\\TEXTURE\\ranking_virtual_window_06.jpg",
	"data\\TEXTURE\\ranking_virtual_window_07.jpg",
	"data\\TEXTURE\\ranking_virtual_window_08.jpg",
};

//==========================================================================
// コンストラクタ
//==========================================================================
CRankingScore::CRankingScore(int nPriority)
{
	// 値のクリア
	m_nNumRanking = 0;				// ランキング数
	memset(&m_nScore[0], 0, sizeof(m_nScore));			// スコア
	memset(&m_nRank[0], 0, sizeof(m_nRank));			// 順位
	//memset(&m_nNowScore[0], 0, sizeof(m_nNowScore));	// 今回のスコア
	m_nNowScore = 0;
	m_nTexIdxNumber = 0;			// 数字テクスチャのインデックス番号
	m_nIdxNewRecord = 0;			// テクスチャのインデックス番号
	m_nCntNewRecord = 0;			// ニューレコードのカウンター
	m_nCnt = 0;						// 始め何秒か止まる処理
	m_nNumPA = 0;					// ポップアップウィンドウの数
	m_nCntCrePA = 0;				// 生成カウンター
	memset(&m_nCntDelPA[0], 0, sizeof(m_nCntDelPA));	// 削除カウンター
	m_nCreSecPA = 0;				// 生成する秒数
	memset(&m_nDelSecPA[0], 0, sizeof(m_nDelSecPA));	// 削除する秒数
	memset(&m_nPASize[0], 0, sizeof(m_nPASize));		// ポップアップウィンドウのサイズ
	memset(&m_nPASizeKeep[0], 0, sizeof(m_nPASizeKeep));// ポップアップウィンドウのサイズの保持
	memset(&m_nPAMag[0], 0, sizeof(m_nPAMag));			// ポップアップウィンドウのXZ座標の倍率
	memset(&m_nPAHeight[0], 0, sizeof(m_nPAHeight));	// ポップアップウィンドウの高さ
	memset(&m_fPosDestY[0], 0, sizeof(m_fPosDestY));	// 目標の位置
	m_bNewRecord = NULL;
	memset(&m_bArrival[0], NULL, sizeof(m_bArrival));	// 到着判定
	memset(&m_b[0], NULL, sizeof(m_b));					// 拡大中判定
	m_bEnd = false;					// スコア終了判定
	memset(&m_pScore[0], NULL, sizeof(m_pScore));		// 数字のオブジェクト
	memset(&m_pRank[0], NULL, sizeof(m_pRank));			// 順位のオブジェクト
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
		m_pObj3D[nCntVtx]->BindTexture(m_nTexIdx3D[nCntVtx]);

		// 各種変数の初期化
		switch (nCntVtx)
		{
		case VTX_LOGO:
			m_pObj3D[nCntVtx]->SetSize(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).x * 0.003f,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).y * 0.003f,
				0.0f));	// サイズ

			m_pObj3D[nCntVtx]->SetPosition(D3DXVECTOR3(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetSize().x + 63.0f - cosf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * 6.5f,
				m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetSize().y + INIT_POSY + 5.0f,
				-150.0f + sinf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * 6.5f));	// 位置

			m_pObj3D[nCntVtx]->SetRotation(D3DXVECTOR3(0.0f, 0.5f, 0.0f));	// 向き
			break;



		case VTX_SCREEN:
			m_pObj3D[nCntVtx]->SetSize(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).x * 0.7f,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).y * 0.5f,
				0.0f));	// サイズ

			m_pObj3D[nCntVtx]->SetPosition(D3DXVECTOR3(-15.0f, 1030.0f , 430.0f));	// 位置

			m_pObj3D[nCntVtx]->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// 向き
			break;



		case VTX3D_VIRTUAL_WINDOW_00:
			m_pObj3D[nCntVtx]->SetSize(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).x * 0.13f,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).y * 0.13f,
				0.0f));	// サイズ

			m_pObj3D[nCntVtx]->SetPosition(D3DXVECTOR3(m_pObj3D[nCntVtx]->GetSize().x + 63.0f, m_pObj3D[nCntVtx]->GetSize().y + INIT_POSY, -150.0f));	// 位置
			m_pObj3D[nCntVtx]->SetRotation(D3DXVECTOR3(0.0f, 0.5f, 0.0f));	// 向き
			break;



		case VTX3D_VIRTUAL_WINDOW_01:
			m_pObj3D[nCntVtx]->SetSize(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).x * 0.13f,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).y * 0.13f,
				0.0f));	// サイズ

			m_pObj3D[nCntVtx]->SetPosition(D3DXVECTOR3(m_pObj3D[nCntVtx]->GetSize().x + 63.0f, m_pObj3D[nCntVtx]->GetSize().y + INIT_POSY, -150.0f));	// 位置
			m_pObj3D[nCntVtx]->SetRotation(D3DXVECTOR3(0.0f, 0.5f, 0.0f));	// 向き
			break;



		case VTX3D_SHADOE_00:
			m_pObj3D[nCntVtx]->SetSize(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).x * 0.14f,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).y * 0.14f,
				0.0f));	// サイズ

			m_pObj3D[nCntVtx]->SetPosition(D3DXVECTOR3(m_pObj3D[nCntVtx]->GetSize().x + 66.0f, m_pObj3D[nCntVtx]->GetSize().y + INIT_POSY - 9.0f, -143.0f));	// 位置
			m_pObj3D[nCntVtx]->SetRotation(D3DXVECTOR3(D3DX_PI / 2, 0.5f, 0.0f));	// 向き
			break;

		default:
			break;
		}

		// 種類の設定
		m_pObj3D[nCntVtx]->SetType(CObject::TYPE_OBJECT3D);
	}

	//ポップアップウィンドウの情報ロード
	LoadPopAppInfo();

	// ポップアップウィンドウの生成
	for (int nCntVtx = 0; nCntVtx < m_nNumPA; nCntVtx++)
	{
		// 生成処理
		m_pObj3D_Win[nCntVtx] = CObject3D::Create(6);

		int i = Random(0, POPAPP_TEX_NUM - 1);

		// テクスチャの割り当て
		m_nTexIdx3D_Win = CManager::GetInstance()->GetTexture()->Regist(m_apTexture3D_WinFile[i]);

		// テクスチャの割り当て
		m_pObj3D_Win[nCntVtx]->BindTexture(m_nTexIdx3D_Win);


		m_pObj3D_Win[nCntVtx]->SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// サイズ

		m_fTexDest[nCntVtx] = m_nPASize[nCntVtx];
		m_nPASizeKeep[nCntVtx] = m_nPASize[nCntVtx];

		m_pObj3D_Win[nCntVtx]->SetPosition(D3DXVECTOR3(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetSize().x + 63.0f - cosf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * m_nPAMag[nCntVtx],
			m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetSize().y + INIT_POSY + m_nPAHeight[nCntVtx],
			-150.0f + sinf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * m_nPAMag[nCntVtx]));	// 位置


		m_pObj3D_Win[nCntVtx]->SetRotation(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation());	// 向き
		m_pObj3D_Win[nCntVtx]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f));

		// 種類の設定
		m_pObj3D_Win[nCntVtx]->SetType(CObject::TYPE_OBJECT3D);
	}


	// ランキングのスコア生成
	for (int nCntRanking = 0; nCntRanking < RANKINGNUM; nCntRanking++)
	{
		// 生成処理
		m_pScore[nCntRanking] = CMultiNumber::Create(D3DXVECTOR3(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetSize().x + 63.0f - cosf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * INIT_POS_A,
			-nCntRanking * DIS_Y + INIT_POSY + 10.0f,
			-150.0f + sinf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * INIT_POS_A),
			D3DXVECTOR2(BASE_WIDTH, BASE_HEIGHT),
			RANKINGSCORE_DIGIT,
			CNumber::OBJECTTYPE_3D,
			NUMBERTEXTURE,
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

		m_apTextureRank = NUMBERTEXTURE_04;

		switch (nCntRanking)
		{
		case 0:
			m_apTextureRank = NUMBERTEXTURE_01;
			break;

		case 1:
			m_apTextureRank = NUMBERTEXTURE_02;
			break;

		case 2:
			m_apTextureRank = NUMBERTEXTURE_03;
			break;
		}


		m_pRank[nCntRanking] = CMultiNumber::Create(D3DXVECTOR3(m_pScore[nCntRanking]->GetPosition().x - cosf(m_pScore[nCntRanking]->GetRotation().y) * INIT_POS_B,
			m_pScore[nCntRanking]->GetPosition().y,
			m_pScore[nCntRanking]->GetPosition().z + sinf(m_pScore[nCntRanking]->GetRotation().y) * INIT_POS_B),
			D3DXVECTOR2(BASE_WIDTH, BASE_HEIGHT),
			RANKINGRANK_DIGIT,
			CNumber::OBJECTTYPE_3D,
			m_apTextureRank,
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

	m_nNowScore = 120000;

	// ソート処理
	Sort();

	// セーブ処理
	Save();

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
	m_nCntCrePA++;

	// 開始時n秒動きを止める
	if (m_nCnt >= 60 * 2)
	{
		// 移動処理
		MovingScore();

		MovingRank();

		CreatePopApp();

		if (m_bEnd == false)
		{
			for (int nCntWindow = 0; nCntWindow < m_nNumPA; nCntWindow++)
			{
				if (m_b[nCntWindow] == true)
				{
					m_nCntDelPA[nCntWindow]++;

					if (m_nCntDelPA[nCntWindow] <= 60 * m_nDelSecPA[nCntWindow])
					{
						ExpansionSize(nCntWindow);
					}

					else
					{
						m_fTexDest[nCntWindow] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

						ReductionSize(nCntWindow);
					}
				}
			}
		}

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

	if (m_bEnd == true)
	{
		for (int nCntWindow = 0; nCntWindow < m_nNumPA; nCntWindow++)
		{
			if (m_b[nCntWindow] == true)
			{
				ReductionSize(nCntWindow);
			}
		}	
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, 0) == true)
	{
		if (m_bEnd == false)
		{
			for (int nCntWindow = 0; nCntWindow < m_nNumPA; nCntWindow++)
			{
				if (m_b[nCntWindow] == true)
				{
					m_fTexDest[nCntWindow] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}

			m_bEnd = true;
		}
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

				for (int nCntWindow = 0; nCntWindow < m_nNumPA; nCntWindow++)
				{
					m_fTexDest[nCntWindow] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}

				m_bEnd = true;
			}

			//// サウンド再生
			//CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_RANKINGSCORE);
		}

		// 位置設定
		m_pRank[nCntRanking]->SetPosition(pos);
	}
}

//==========================================================================
// 拡大処理
//==========================================================================
void CRankingScore::CreatePopApp(void)
{
	// n秒後に生成する
	if (m_nCntCrePA >= 60 * m_nCreSecPA)
	{
		// ポップアップを拡大する数
		int i = Random(2, 4);

		// どのポップアップを拡大するか
		for (int nCntWindow = 0; nCntWindow < i; nCntWindow++)
		{
			int n = Random(0, m_nNumPA - 1);

			while (1)
			{
				// 生成されていたら
				if (m_b[n] == true)
				{
					n = Random(0, m_nNumPA - 1);
				}

				else
				{
					break;
				}
			}

			m_b[n] = true;

			int m = Random(0, POPAPP_TEX_NUM - 1);

			// テクスチャの割り当て
			m_nTexIdx3D_Win = CManager::GetInstance()->GetTexture()->Regist(m_apTexture3D_WinFile[m]);

			// テクスチャの割り当て
			m_pObj3D_Win[n]->GetObject3D()->BindTexture(m_nTexIdx3D_Win);

			m_nDelSecPA[n] = Random(2, 5);
		}

		m_nCreSecPA = Random(2, 3);
		m_nCntCrePA = 0;
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
// 拡大処理
//==========================================================================
void CRankingScore::ExpansionSize(int CntWindow)
{
	// 位置取得
	D3DXVECTOR3 size = m_pObj3D_Win[CntWindow]->GetSize();

	//
	D3DXVECTOR3 nDest = m_fTexDest[CntWindow];

	// 目標の位置へ補正
	if (nDest.x > size.x)
	{
		size.x += nDest.x / (float)SIZE_MOVETIME;
	}

	if (nDest.y > size.y)
	{
		size.y += nDest.y / (float)SIZE_MOVETIME;
	}

	// 目標で固定
	if (nDest.x <= size.x)
	{
		size.x = m_fTexDest[CntWindow].x;
	}

	if (nDest.y <= size.y)
	{
		size.y = m_fTexDest[CntWindow].y;
	}

	// 位置設定
	m_pObj3D_Win[CntWindow]->SetSize(size);
}

//==========================================================================
// 縮小処理
//==========================================================================
void CRankingScore::ReductionSize(int CntWindow)
{
	// 位置取得
	D3DXVECTOR3 size = m_pObj3D_Win[CntWindow]->GetSize();

	D3DXVECTOR3 nDest = m_fTexDest[CntWindow] - m_nPASizeKeep[CntWindow];

	// 目標の位置へ補正
	if (nDest.x < size.x)
	{
		size.x += nDest.x / (float)SIZE_MOVETIME / 2;
	}

	if (nDest.y < size.y)
	{
		size.y += nDest.y / (float)SIZE_MOVETIME / 2;
	}


	if (m_fTexDest[CntWindow].x >= size.x)
	{// 目標で固定
		size.x = m_fTexDest[CntWindow].x;
		m_b[CntWindow] = false;
		m_nCntDelPA[CntWindow] = 0;
		m_fTexDest[CntWindow] = m_nPASize[CntWindow];
	}

	if (m_fTexDest[CntWindow].y >= size.y)
	{// 目標で固定
		size.y = m_fTexDest[CntWindow].y;
	}

	// 位置設定
	m_pObj3D_Win[CntWindow]->SetSize(size);
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
		if (m_bNewRecord == false)
		{
			if (m_nScore[m_nNumRanking - 1] < m_nNowScore)
			{// 入れ替え

				m_nScore[m_nNumRanking - 1] = m_nNowScore;	// 最小値と今回のデータ入れ替え
				m_bNewRecord = true;	// フラグON
			}
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

//==============================================================
// ロード処理
//==============================================================
void CRankingScore::LoadPopAppInfo(void)
{
	FILE *pFile = NULL;	// ファイルポインタを宣言

						// ファイルを開く
	pFile = fopen("data\\TEXT\\ranking_PopApp_window.txt", "r");

	if (pFile == NULL)
	{//ファイルが開けなかった場合
		return;
	}

	else if (pFile != NULL)
	{// ファイルが開けた場合

		fscanf(pFile, "%d", &m_nNumPA);	// 

	 // ファイルに数値を読み込む
		for (int nCnt = 0; nCnt <= m_nNumPA; nCnt++)
		{
			fscanf(pFile, "%f", &m_nPASize[nCnt].x);	// 
			fscanf(pFile, "%f", &m_nPASize[nCnt].y);	// 
			fscanf(pFile, "%f", &m_nPASize[nCnt].z);	// 

			fscanf(pFile, "%f", &m_nPAMag[nCnt]);	// 

			fscanf(pFile, "%f", &m_nPAHeight[nCnt]);	// 
		}
	}

	// ファイルを閉じる
	fclose(pFile);
}