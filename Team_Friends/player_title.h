//=============================================================================
// 
//  プレイヤーヘッダー [player_title.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _PLAYER_TITLE_H_
#define _PLAYER_TITLE_H_	// 二重インクルード防止

#include "player.h"

//==========================================================================
// クラス定義
//==========================================================================
class CPlayerTitle : public CPlayer
{
public:

	//タイプ
	enum MODEL
	{
		PLAYER_UNION = 0, //合体やーつ
		PLAYER_ARM, //腕のやつ
		PLAYER_LEG, //足のやつ
		PLAYER_BODY, //胴のやつ
		MAX,
		NONE
	};

	CPlayerTitle(int nPriority = mylib_const::PRIORITY_DEF2D);
	~CPlayerTitle();

	// オーバーライドされた関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// 静的メンバ関数
	static CPlayerTitle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL type = PLAYER_UNION);

private:

	//メンバ変数
	int m_nModelType;

	// 静的メンバ変数
	static int m_nIdx; // インデックス

};

#endif
