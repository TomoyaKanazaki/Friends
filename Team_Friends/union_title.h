//==========================================
//
//  タイトルの合体ロボ(union_title.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _UNION_TITLE_H_
#define _UNION_TITLE_H_
#include "player_union.h"

//==========================================
//  クラス定義
//==========================================
class CUnionTitle : public CPlayerUnion
{
public:

	CUnionTitle(int nPriority = mylib_const::DEF2D_PRIORITY);
	~CUnionTitle();

	// オーバーライドされた関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CUnionTitle* Create(D3DXVECTOR3 pos);

};

#endif
