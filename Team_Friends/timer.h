//=============================================================================
// 
//  タイマーヘッダー [timer.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _TIMER_H_
#define _TIMER_H_	// 二重インクルード防止

#include "main.h"

//==========================================================================
// 前方宣言
//==========================================================================
class CMultiNumber;

//==========================================================================
// クラス定義
//==========================================================================
// タイマークラス定義
class CTimer
{
public:

	CTimer(int nPriority = 6);
	~CTimer();

	static CTimer *Create(void);
	static CTimer *Create(D3DXVECTOR3 pos);

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Add(int nValue);

private:

	float m_fTime;					// 時間
	CMultiNumber *m_pMinutes;		// 分のオブジェクト
	CMultiNumber *m_pSeconds;		// 秒のオブジェクト
	CMultiNumber *m_pMilliSeconds;	// ミリ秒のオブジェクト
};



#endif