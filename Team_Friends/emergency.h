//=============================================================================
// 
//  警報ヘッダー [emergency.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _EMERGENCY_H_
#define _EMERGENCY_H_	// 二重インクルード防止

#include "object.h"

//==========================================================================
// 前方宣言
//==========================================================================
class CMultiNumber;

//==========================================================================
// クラス定義
//==========================================================================
// 警報クラス定義
class CEmergency : public CObject
{
public:

	CEmergency(int nPriority = 7);
	~CEmergency();

	// オーバーライドされた関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEmergency *Create(void);
private:

	// 状態列挙
	enum eState
	{
		STATE_EMERGENCY = 0,	// 警報
		STATE_WINDOW,			// ウィンドウ
		STATE_MISSION,			// ミッション
		STATE_END,
		STATE_MAX
	};
	
	// 関数リスト
	typedef void(CEmergency::*STATE_FUNC)(void);
	static STATE_FUNC m_StateFuncList[];	// 状態関数リスト

	// メンバ関数
	void UpdateEmergency(void);	// 警報の更新
	void UpdateWindow(void);	// ウィンドウの更新
	void UpdateMission(void);	// ミッションの更新
	void UpdateEnd(void);		// 終了

	// メンバ変数
	eState m_satate;	// 状態
	bool m_bEndEmergency;			// 警報が終わったか
	float m_fTime;					// 警報時間
	CObject2D *m_pEmergencyFlash;	// 警報時点滅
	CObject2D *m_pEmergencyText;	// 警報テキスト
	CObject2D *m_pMissionText;		// ミッションテキスト
	CObject2D *m_pWindow;			// ウィンドウ
	CObject2D *m_pWarningFrame[2];	// 警告のフレーム
};



#endif