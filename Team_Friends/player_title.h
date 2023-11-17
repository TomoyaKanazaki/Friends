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
// マクロ定義
//==========================================================================

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
	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	void Draw(void) override;

protected:

private:

	// メンバ関数

	// メンバ変数
};



#endif