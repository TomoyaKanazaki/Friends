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
		ARMtoARM = 0, //
		BODYtoLEG,
		BODYtoARM,
		LEGtoARM,
		MAX,
	};

	CPlayerRanking(int nPriority = mylib_const::DEF2D_PRIORITY);
	CPlayerRanking(MODEL nType, int nPriority = mylib_const::DEF2D_PRIORITY);
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

	void BODYtoLEGMove(void);
	void BODYtoARMMove(void);
	void LEGtoARMMove(void);
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
