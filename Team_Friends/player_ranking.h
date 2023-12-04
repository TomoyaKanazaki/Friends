#pragma once
//=============================================================================
// 
//  プレイヤーヘッダー [player_title.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _PLAYER_RANKING_H_
#define _PLAYER_RANKING_H_	// 二重インクルード防止

#include "player_union.h"

//==========================================================================
// クラス定義
//==========================================================================
// プレイヤークラス定義
class CPlayerRanking : public CPlayerUnion
{
public:

	//タイプ
	enum MODEL
	{
		BODYtoLEG,
		BODYtoARM,
		LEGtoARM,
		ARMtoARM, //
		MAX,
	};

	CPlayerRanking(int nPriority = mylib_const::PRIORITY_DEF2D);
	CPlayerRanking(MODEL nType, int nPriority = mylib_const::PRIORITY_DEF2D);
	~CPlayerRanking();

	// オーバーライドされた関数
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CPlayerUnion* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL type);
	virtual HRESULT CreateParts(void) override;

private:

	void ARMtoARMMove(void);

	//メンバ変数
	int m_nModelType;
	MODEL m_nType;

	int m_nCntSwitch;		// 切り替えのカウンター
	int m_nMovePtaCnt;
	int m_nSpinCnt;
	bool m_bRight;
	bool m_bLeft;
	bool m_bOldLeft;

};

#endif
