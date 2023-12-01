//==========================================
//
//  メタルスライム(enemy_escape.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_ESCAPE_H_
#define _ENEMY_ESCAPE_H_
#include "enemy.h"

//==========================================
//  クラス定義
//==========================================
class CEnemyEscape : public CEnemy
{
public:

	// オーバーライドされた関数
	CEnemyEscape(int nPriority = mylib_const::ENEMY_PRIORITY);
	~CEnemyEscape();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Kill(void) override;
	void MotionSet(void) override;		// モーションの設定

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
		ACTION_FIND, // 発見行動
		ACTION_ESCAPE, // 逃走行動
		ACTION_FADE, // 消滅行動
		MAX
	};

	// メンバ変数
	ACTION m_Act; //行動状態
	float m_fMoveCount; // 移動カウンター
	float m_fCntFind; // 発見カウンター
	float m_fCntEscape; // 逃走カウンター

	// メンバ関数
	void UpdateAction(void) override;	// 行動更新
	void ActionSet(void); // 行動の設定
	void Move(void); // 移動
	void Escape(void); // 逃走
	void MoveRotation(void); // 移動方向を向く
	void RotationPlayer(void); // プレイヤーを向く処理
	bool CalcLenPlayer(float fLen); // プレイヤーとの距離判定
};

#endif
