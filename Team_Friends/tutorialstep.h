//=============================================================================
// 
//  チュートリアルステップヘッダー [tutorialstep.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _TUTORIALSTEP_H_
#define _TUTORIALSTEP_H_	// 二重インクルード防止

//==========================================================================
// 前方宣言
//==========================================================================

//==========================================================================
// クラス定義
//==========================================================================
// チュートリアルステップクラス定義
class CTutorialStep
{
public:
	// 列挙型定義
	enum STEP
	{
		STEP_WAIT = 0,
		STEP_MOVE,		//移動
		STEP_ATTACK,		//攻撃
		STEP_POWERUP,		//強化
		STEP_UNDER_UNION,		//簡易合体-合体
		STEP_UNDER_FREE,		//簡易合体-自由
		STEP_UNION_ITEM,		//合体-アイテム取得
		STEP_UNION_FREE,		//合体-自由
		STEP_MAX
	};

	enum STEPFRAG
	{
		STEPFRAG_MOVE,		//移動
		STEPFRAG_ATTACK,		//攻撃
		STEPFRAG_POWERUP,		//強化
		STEPFRAG_UNDER_UNION,		//簡易合体-合体
		STEPFRAG_UNDER_FREE,		//簡易合体-自由
		STEPFRAG_UNION_ITEM,		//合体-アイテム取得
		STEPFRAG_UNION_FREE,		//合体-自由
		STEPFRAG_MAX
	};

	CTutorialStep();
	~CTutorialStep();

	static CTutorialStep *Create(void);	// 生成処理

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void AddStep(void);	// ステップを進める
	void SetStep(STEP step);	// ステップの設定処理
	STEP GetNowStep(void);	// 現在のステップ取得
	bool IsEndStep(void);	// ステップ終了の判定取得
	void SetDisableOKSign(void);	// OKサインのフラグOFFにする
	bool IsEndAll(void);	// 全ステップ終了の判定取得

private:

	int m_nCntWait;			// 待機のカウンター
	int m_nCntSpeedUP;		// スピードアップのカウンター
	int m_nCntSpeedDOWN;	// スピードダウンのカウンター
	int m_nCntImpactWave;	// 円形波の回数
	int m_nCntDirectWave;	// 直線波の回数
	bool m_bEndStep;		// ステップの終了判定
	bool m_bSetOK;			// OKの設定判定
	STEP m_step;			// 現在のステップ
};

#endif