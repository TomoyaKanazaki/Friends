//=============================================================================
// 
//  チュートリアルヘッダー [tutorial.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_	// 二重インクルード防止

#include "main.h"
#include "manager.h"

//==========================================================================
// 前方宣言
//==========================================================================
class CTutorialStep;
class CTutorialText;
class CTutorialPlayer;

//==========================================================================
// クラス定義
//==========================================================================
// チュートリアルクラス定義
class CTutorial : public CScene
{
public:

	CTutorial();
	~CTutorial();

	// オーバーライドされた関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	static bool IsMovingPlayer(void);		// プレイヤーが動いてる判定取得
	static void SetEnableMovingPlayer(void);		// プレイヤーが動いてる判定
	static void SetDisableMovingPlayer(void);		// プレイヤーが動いてる判定OFF
	static CTutorialStep *GetStep(void);	// ステップ取得
	CPlayer **GetPlayer(void);				// プレイヤーの取得
	CPlayer *GetPlayer(int nIdx);			// プレイヤーの取得

private:

	CTutorialPlayer *m_apPlayer[mylib_const::MAX_PLAYER];		// プレイヤーのオブジェクト
	static bool m_bMovingPlayer;	// プレイヤーが動いてる判定
	static CTutorialStep *m_pStep;	// ステップ
	CTutorialText *m_pText;			//テキスト
};

#endif