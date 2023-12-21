//==========================================
//
//  ひび割れポリゴン(glass.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _GLASS_H_
#define _GLASS_H_
#include "object2D.h"

//==========================================
//  クラス定義
//==========================================
class CGlass : public CObject2D
{
public:

	// メンバ関数
	CGlass();
	~CGlass();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// 静的メンバ関数
	static CGlass* Create();

};

#endif
