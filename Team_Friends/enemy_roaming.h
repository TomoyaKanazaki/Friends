//==========================================
//
//  コピペ用の敵(enemy_roaming.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_ROAMING_H_
#define _ENEMY_ROSMING_H_
#include "enemy.h"

//==========================================
// クラス定義
//==========================================
class CEnemyRoaming : public CEnemy
{
public:

	// オーバーライドされた関数
	CEnemyRoaming(int nPriority = mylib_const::ENEMY_PRIORITY);
	~CEnemyRoaming();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Kill(void) override;

private:

	//モーション列挙
	enum MOTION
	{
		MOTION_DEF = 0,		// ニュートラルモーション
		MOTION_WALK,		// 移動モーション
		MOTION_ATK,			// 攻撃モーション
		MOTION_KNOCKBACK,	// やられモーション
		MOTION_FADEOUT,		// 帰還モーション
		MOTION_MAX
	};

	// 行動列挙
	enum ACTION
	{
		ACTION_ROAMING = 0, //徘徊行動
		ACTION_ATTACK, //攻撃行動
		MAX
	};

	// メンバ変数
	ACTION m_Act; //行動状態

	// メンバ関数
	void MotionSet(void) override;		// モーションの設定
	void UpdateAction(void) override;	// 行動更新
	void ActionSet(void) override; // 行動の設定
	void Move(void) override; // 移動
	void Attack(void); // 攻撃

};

#endif
