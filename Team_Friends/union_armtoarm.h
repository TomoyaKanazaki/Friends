//=============================================================================
// 
//  小規模合体プレイヤーヘッダー [union_armtoarm.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _UNION_ARMTOARM_H_
#define _UNION_ARMTOARM_H_	// 二重インクルード防止

#include "player_union.h"
#include "player_ranking.h"

// 前方宣言

//==========================================================================
// クラス定義
//==========================================================================
// プレイヤークラス定義
class CUnion_ArntoArm : public CPlayerUnion
{
public:

	CUnion_ArntoArm(int nPriority = mylib_const::PRIORITY_DEF2D);
	~CUnion_ArntoArm();

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
		MOTION_APPEARANCE,		// 出現
		MOTION_SUPERATK,		// 必殺技
		MOTION_MAX
	};

	virtual void AttackAction(int nIdx, int nModelNum, CMotion::AttackInfo ATKInfo);	// 攻撃時処理
	virtual void ControllParts(void);	// パーツのコントロール処理
	virtual void MotionSet(int nIdx);	// モーションの設定
	virtual HRESULT CreateParts(void) override;	// パーツの設定
private:

	// コンボ時ワザの種類
	enum eSPSkill
	{
		SKILL_MAX
	};

	// メンバ関数
	void ControllLeg(int nIdx);			// 脚操作
	void ControllATK(int nIdx, int nLoop);		// 攻撃操作
	void Appearance(void) override;	// 出現

	// メンバ変数
	bool m_bSuperATK;	// 必殺技の判定
};



#endif