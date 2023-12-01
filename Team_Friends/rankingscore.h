//=============================================================================
// 
//  ランキングスコアヘッダー [rankingscore.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _RANKINGSCORE_H_
#define _RANKINGSCORE_H_	// 二重インクルード防止

#include "main.h"
#include "object.h"

//==========================================================================
// マクロ定義
//==========================================================================
#define RANKINGSCORE_DIGIT	(6)	// 桁数
#define RANKINGNUM	(20)	// 桁数
#define RANKING_DISPLAY_NUM	(5)	// 桁数

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
	void SetValue(void);	// 値の設定処理
	void Moving(void);	// 移動処理
	static CRankingScore *Create(void);
private:

	enum VTX3D
	{
		VTX_NUM = 0,		// リザルトロゴ
		VTX3D_VIRTUAL_WINDOW_00,
		VTX3D_VIRTUAL_WINDOW_01,
		VTX3D_SHADOE_00,
		VTX_LOGO,
		VTX3D_MAX
	};

	void Load(void);	// ロード
	void Save(void);	// セーブ
	void Sort(void);	// ソート
	
	int m_nNumRanking;				// ランキング数
	int m_nScore[RANKINGNUM];		// スコア
	int m_nNowScore;		// 今回のスコア
	int m_nTexIdx3D[VTX3D_MAX];					// テクスチャのインデックス番号
	int m_nTexIdxNumber;			// 数字テクスチャのインデックス番号
	int m_nIdxNewRecord;			// ニューレコードのインデックス番号
	int m_nCntNewRecord;			// ニューレコードのカウンター
	float m_fPosDestX[RANKINGNUM];	// 目標の位置
	bool m_bNewRecord;				// ニューレコードのフラグ
	bool m_bArrival[RANKINGNUM];	// 到着判定
	CObject3D *m_pObj3D[VTX3D_MAX];	// オブジェクト2Dのオブジェクト
	CMultiNumber *m_pScore[RANKINGNUM];			// 数字のオブジェクト
	static const char *m_apTexture3DFile[VTX3D_MAX];	// テクスチャのファイル
};



#endif