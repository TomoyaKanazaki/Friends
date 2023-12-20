//=============================================================================
// 
//  必殺ウィンドウヘッダー [ultwindow.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _ULTWINDOW_H_
#define _ULTWINDOW_H_	// 二重インクルード防止

#include "object.h"
#include "gamemanager.h"

//==========================================================================
// 前方宣言
//==========================================================================
class CObjectCircleGauge2D;
class CMultiNumber;

//==========================================================================
// クラス定義
//==========================================================================
// 必殺ウィンドウクラス定義
class CUltWindow : public CObject
{
public:

	CUltWindow(int nPriority = 7);
	~CUltWindow();

	// オーバーライドされた関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CObjectCircleGauge2D *GetGauge();	// ゲージ取得
	static CUltWindow *Create(D3DXVECTOR3 pos, bool bJoin);
private:
	
	bool m_bJoin;	// 参加してるか
	CObject2D *m_pOnOffSign[2];			// オンオフサイン
	CObject2D *m_pUltText;					// 必殺テキスト
	CObject2D *m_pWindowShape;				// ウィンドウの型
	CObject2D *m_pWindowShapeLid;			// ウィンドウの型の蓋
	CObjectCircleGauge2D *m_pCircleGauge2D;	// 円ゲージのポインタ
	CMultiNumber *m_pUltNumber;				// 必殺の数字
};



#endif