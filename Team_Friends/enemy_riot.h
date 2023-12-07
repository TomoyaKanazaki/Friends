//==========================================
//
//  ギガントエッジ(enemy_riot.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_RIOT_H_
#define _ENEMY_RIOT_H_
#include "enemy.h"

//==========================================
//  クラス定義
//==========================================
class CEnemyRiot : public CEnemy
{
public:

	// オーバーライドされた関数
	CEnemyRiot(int nPriority = mylib_const::ENEMY_PRIORITY);
	~CEnemyRiot();

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
		MOTION_SPAWN,		// 出現モーション
		MOTION_MAX
	};

	// 行動列挙
	enum ACTION
	{
		ACTION_DEF = 0, // 待機行動
		ACTION_MOVE, // 移動行動
		ACTION_ATTACK, // 通常攻撃行動
		ACTION_TACKLE, // 突進攻撃行動
		ACTION_AXIS, // 軸合わせ行動
		ACTION_SPAWN, // 出現行動
		MAX
	};

	// メンバ変数
	ACTION m_Act; //行動状態
	float m_fWaitTime; // 待機時間
	int m_nCntAction; // 連続行動回数

	// メンバ関数
	void Spawn(void) override;			// スポーン
	void MotionSet(void) override;		// モーションの設定
	void ActionSet(void) override; // 行動の設定
	void Move(void) override; // 移動
	void Attack(void); // 攻撃

};

#endif
