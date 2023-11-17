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
// プレイヤークラス定義
class CPlayerTitle : public CPlayer
{
public:

	CPlayerTitle(int nPriority = mylib_const::DEF2D_PRIORITY);
	~CPlayerTitle();

	// オーバーライドされた関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// 静的メンバ関数
	static CPlayerTitle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

};

#endif
