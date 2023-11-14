//=============================================================================
// 
//  小規模合体プレイヤーヘッダー [player_smallunion.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _PLAYER_SMALLUNION_H_
#define _PLAYER_SMALLUNION_H_	// 二重インクルード防止

#include "player_union.h"

//==========================================================================
// マクロ定義
//==========================================================================

// 前方宣言
class CShadow;
class CTargetPoint;
class CHP_GaugePlayer;

//==========================================================================
// クラス定義
//==========================================================================
// プレイヤークラス定義
class CPlayerSmallUnion : public CPlayerUnion
{
public:

	CPlayerSmallUnion(int nPriority = mylib_const::DEF2D_PRIORITY);
	~CPlayerSmallUnion();


	// オーバーライドされた関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	bool Hit(const int nValue) override;	// ヒット処理

protected:
	// 列挙型定義
	enum MOTION
	{
		MOTION_DEF = 0,			// ニュートラルモーション
		MOTION_WALK,			// 移動モーション
		MOTION_ATK,				// 攻撃
		MOTION_CHARGE,			// チャージ
		MOTION_KNOCKBACK,		// やられモーション
		MOTION_DEAD,			// 死亡モーション
		MOTION_JUMP,			// ジャンプ
		MOTION_FALL,			// 落下中
		MOTION_MAX
	};

	virtual void AttackAction(int nIdx, int nModelNum, CMotion::AttackInfo ATKInfo);	// 攻撃時処理
	virtual void ControllParts(void);	// パーツのコントロール処理
	virtual void MotionSet(int nIdx);	// モーションの設定
	virtual HRESULT CreateParts(void) override;	// パーツの設定
private:

	// メンバ関数
	void ControllBody(int nIdx);		// 胴操作
	void ControllLeg(int nIdx);			// 脚操作
	void ControllRightArm(int nIdx);	// 右腕操作
	void ControllLeftArm(int nIdx);		// 左腕操作

	static const char *m_apModelFile[mylib_const::MAX_PLAYER];	// モデルのファイル
};



#endif