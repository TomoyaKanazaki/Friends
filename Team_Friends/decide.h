//=============================================================================
// 
//  人数選択画面(decideplayer.h)
//  Author : Tomoya Kanazaki
// 
//=============================================================================
#ifndef _DECIDEPLAYER_H_
#define _DECIDEPLAYER_H_
#include "scene.h"

//==========================================================================
// クラス定義
//==========================================================================
class CDecide : public CScene
{
public:

	CDecide();
	~CDecide();

	// オーバーライドされた関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

};

#endif
