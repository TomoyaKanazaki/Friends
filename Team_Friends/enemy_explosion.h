//==========================================
//
//  自爆する敵(enemy_explosion.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_EXPLOSION_H_
#define _ENEMY_EXPLOSION_H_
#include "enemy.h"

//==========================================
//  クラス定義
//==========================================
class CEnemyExplosion : public CEnemy
{
public:

	// オーバーライドされた関数
	CEnemyExplosion(int nPriority = mylib_const::ENEMY_PRIORITY);
	~CEnemyExplosion();

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
		ACTION_ROAMING = 0, // 徘徊行動
		ACTION_CHASE, // 追跡行動
		ACTION_COUNTDOWN, // カウントダウン行動
		ACTION_EXPROSION, // 自爆行動
		ACTION_FADE, // 消滅行動
		MAX
	};

	// メンバ変数
	ACTION m_Act; //行動状態
	float m_fCntWalk; // 方向転換
	float m_fCntFind; // 発見カウンター
	float m_fCntEscape; // 逃走カウンター
	float m_fRot; // 向きたいとこ～
	float m_fCountDawn; // 自爆カウントダウン
	float m_fCol; // マテリアルカラー変える

	// メンバ関数
	void MotionSet(void) override;		// モーションの設定
	void UpdateAction(void) override;	// 行動更新
	void Move(void) override; // 移動
	void RandTurn(void); // ランダムな方向転換
	void ActionSet(void); // 行動の設定
	void Flash(void); // 点滅

};

#endif
