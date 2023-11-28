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
		a,
		b,
		c,
		d,
		BODYtoLEG, //
		MAX,
	};

	CPlayerRanking(int nPriority = mylib_const::DEF2D_PRIORITY);
	~CPlayerRanking();

	// オーバーライドされた関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// 静的メンバ関数
	static CPlayerRanking* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL type);

private:

	//メンバ変数
	int m_nModelType;

};

#endif
