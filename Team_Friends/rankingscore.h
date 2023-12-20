//=============================================================================
// 
//  ランキングスコアヘッダー [rankingscore.h]
//  Author : 橋本賢太
// 
//=============================================================================

#ifndef _RANKINGSCORE_H_
#define _RANKINGSCORE_H_	// 二重インクルード防止

#include "main.h"
#include "object.h"

//==========================================================================
// マクロ定義
//==========================================================================
#define RANKINGRANK_DIGIT	(2)	// 順位桁数
#define RANKINGSCORE_DIGIT	(6)	// 桁数
#define RANKINGNUM	(20)	// 総数
#define RANKING_DISPLAY_NUM	(5)	// 初期表示数
#define WINDOW_POPAPP_NUM	(12)	// 
#define POPAPP_TEX_NUM	(3)	// 

//==========================================================================
// 前方宣言
//==========================================================================
class CMultiNumber;

//==========================================================================
// クラス定義
//==========================================================================
// ランキングスコアクラス定義
class CRankingScore : public CObject
{
public:

	CRankingScore(int nPriority = 7);
	~CRankingScore();

	// オーバーライドされた関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetAllArrival(void);	// 全ての到着設定
	void UpdateNewRecord(void);	// ニューレコードの更新処理
	void MovingScore(void);	// 移動処理
	void MovingRank(void);	// 移動処理
	void CreatePopApp(void);	// 移動処理
	void ExpansionSize(int nCntWindow);	// 拡大処理
	void ReductionSize(int nCntWindow);	// 縮小処理
	static CRankingScore *Create(void);
private:

	enum VTX3D
	{
		VTX3D_VIRTUAL_WINDOW_00 = 0,
		VTX3D_VIRTUAL_WINDOW_01,
		VTX3D_SHADOE_00,
		VTX_LOGO,
		VTX_SCREEN,
		VTX3D_MAX
	};

	void Load(void);	// ロード
	void Save(void);	// セーブ
	void Sort(void);	// ソート

	void LoadPopAppInfo(void);	// ロード

	int m_nNumRanking;				// ランキング数
	int m_nScore[RANKINGNUM];		// スコア
	int m_nRank[RANKINGNUM];		// スコア
	int m_nNowScore;		// 今回のスコア
	int m_nTexIdx3D[VTX3D_MAX];					// テクスチャのインデックス番号
	int m_nTexIdx3D_Win;					// テクスチャのインデックス番号
	int m_nTexIdxNumber;			// 数字テクスチャのインデックス番号
	int m_nIdxNewRecord;			// ニューレコードのインデックス番号
	int m_nCntNewRecord;			// ニューレコードのカウンター
	int m_nCnt;						// 始め何秒か止まる処理

	int m_nNumPA;					// ポップアップウィンドウの数
	int m_nCntCrePA;				// 生成カウンター
	int m_nCntDelPA[WINDOW_POPAPP_NUM];				// 削除カウンター
	int m_nCreSecPA;				// 生成する秒数
	int m_nDelSecPA[WINDOW_POPAPP_NUM];				// 削除する秒数
	D3DXVECTOR3 m_nPASize[WINDOW_POPAPP_NUM];		// ポップアップウィンドウのサイズ
	D3DXVECTOR3 m_nPASizeKeep[WINDOW_POPAPP_NUM];	// ポップアップウィンドウのサイズの保持
	float m_nPAMag[WINDOW_POPAPP_NUM];				// ポップアップウィンドウのXZ座標の倍率
	float m_nPAHeight[WINDOW_POPAPP_NUM];			// ポップアップウィンドウの高さ

	float m_fPosDestY[RANKINGNUM];	// 目標の位置
	D3DXVECTOR3 m_fTexDest[WINDOW_POPAPP_NUM];	// 目標の位置

	bool m_bNewRecord;	// ニューレコードのフラグ
	bool m_bArrival[RANKINGNUM];	// 到着判定
	bool m_b[WINDOW_POPAPP_NUM];	// 拡大中判定
	bool m_bEnd;					// スコア終了判定

	CObject3D *m_pObj3D[VTX3D_MAX];	// オブジェクト3Dのオブジェクト
	CObject3D *m_pObj3D_Win[WINDOW_POPAPP_NUM];	// オブジェクト3Dのオブジェクト
	CMultiNumber *m_pScore[RANKINGNUM];			// 数字のオブジェクト
	CMultiNumber *m_pRank[RANKINGNUM];			// 順位のオブジェクト
	char *m_apTextureRank;						// テクスチャのファイル
	static const char *m_apTexture3DFile[VTX3D_MAX];	// テクスチャのファイル
	static const char *m_apTexture3D_WinFile[POPAPP_TEX_NUM];	// ポップアップテクスチャのファイル
};



#endif