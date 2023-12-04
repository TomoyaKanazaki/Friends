//=============================================================================
// 
//  ランキングヘッダー [ranking.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _RANKING_H_
#define _RANKING_H_	// 二重インクルード防止

#include "main.h"
#include "manager.h"
#include "player_ranking.h"

//==========================================================================
// 前方宣言
//==========================================================================
class CRankingScore;

//==========================================================================
// クラス定義
//==========================================================================
// ランキングクラス定義
class CRanking : public CScene
{
public:

	CRanking();
	~CRanking();

	// オーバーライドされた関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetEnableArrival(void);
	static int GetRandStage(void) { return m_nRandStage; }

	static CPlayerUnion *GetPlayerUnion(void);		// 合体プレイヤーのオブジェクト

private:
	void UniCharCreate(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//合体キャラの生成

	int m_nCntSwitch;		// 切り替えのカウンター
	int m_nCntUniCharCre;		// 合体キャラの生成カウンター
	int m_nCntUniCharDel;		// 合体キャラの生成カウンター
	static bool m_bAllArrival;		// 全て到着した判定
	static int m_nRandStage;		// ステージのランダムインデックス番号
	static CRankingScore *m_pRankingScore;		// ランキングスコアのオブジェクト
	static CPlayerUnion *m_pPlayerUnion;		// 合体プレイヤーのオブジェクト

	static const char *m_apModelFile;		// モデルのファイル

	CPlayerRanking::MODEL m_nType;
};



#endif