//=============================================================================
// 
//  ボスヘッダー [enemy_boss.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _ENEMYBOSS_H_
#define _ENEMYBOSS_H_	// 二重インクルード防止

#include "main.h"
#include "enemy.h"

// 前方宣言

//==========================================================================
// クラス定義
//==========================================================================
// ボスクラス定義
class CEnemyBoss : public CEnemy
{
public:

	CEnemyBoss(int nPriority = mylib_const::ENEMY_PRIORITY);
	~CEnemyBoss();

	// オーバーライドされた関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Kill(void) override;
	void MotionSet(void) override;		// モーションの設定

protected:

private:

	//モーション列挙
	typedef enum
	{
		MOTION_DEF = 0,		// ニュートラルモーション
		MOTION_WALK,		// 移動モーション
		MOTION_ATK,			// 攻撃モーション
		MOTION_KNOCKBACK,	// やられモーション
		MOTION_FADEOUT,		// 帰還モーション
	}MOTION;

	// 行動列挙
	enum ACTION
	{
		ACTION_CHASE = 0,		// 追従
		ACTION_CHASE_DASH,		// ダッシュ追従
		ACTION_PUNCH,			// パンチ
		ACTION_KICK,			// キック
		ACTION_BEAM,			// ビーム
		ACTION_CHARGE_BEAM,		// チャージビーム
		ACTION_TACKLE,			// タックル
		ACTION_CHARGE_TACKLE,	// チャージタックル
		ACTION_SELFEXPLOSION,	// 自爆
		ACTION_MAX
	};

	// メンバ関数
	void Move(void); // 移動

	// メンバ変数
	ACTION m_Act;		// 行動
	float m_fActTime;	// 行動カウンター

	// 関数リスト
	typedef void(CEnemyBoss::*ACT_FUNC)(void);
	static ACT_FUNC m_ActFuncList[];
};



#endif