//=============================================================================
// 
//  タイトルヘッダー [title.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _TITLE_H_
#define _TITLE_H_	// 二重インクルード防止

#include "main.h"
#include "manager.h"

//==========================================================================
// クラス定義
//==========================================================================
// タイトルクラス定義
class CTitle : public CScene
{
public:

	CTitle();
	~CTitle();

	// オーバーライドされた関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	int m_nCntSwitch;		// 切り替えのカウンター

};



#endif