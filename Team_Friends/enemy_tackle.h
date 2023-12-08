//==========================================
//
//  突撃敵(enemy_tackle.h)
//  Author : Kai Takada
//
//==========================================
#ifndef _ENEMY_TACKLE_H_
#define _ENEMY_TACKLE_H_
#include "enemy.h"

//==========================================
//  クラス定義
//==========================================
class CEnemyTackle : public CEnemy
{
public:

	// オーバーライドされた関数
	CEnemyTackle(int nPriority = mylib_const::ENEMY_PRIORITY);
	~CEnemyTackle();

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
		MOTION_READY,		// 準備モーション
		MOTION_AFTER,		// 硬直モーション
		MOTION_MAX
	};

	// 行動列挙
	enum ACTION
	{
		ACTION_ROAMING = 0,	//徘徊行動
		ACTION_READY,		//準備行動
		ACTION_ATTACK,		//攻撃行動
		ACTION_AFTER,		//攻撃硬直
		MAX
	};

	// メンバ変数
	ACTION m_Act;			// 行動状態
	float m_fActionCount;	// 移動カウンター
	D3DXVECTOR3 m_moveLock;	// 固定移動量
	float m_fRotLock;		// 向き保存
	float m_fEmissionTime;	// 発生物のタイマー
	int m_nAttack;			// 攻撃力

	// メンバ関数
	void MotionSet(void) override;		// モーションの設定
	void UpdateAction(void) override;	// 行動更新
	void ActionSet(void) override; // 行動の設定
	void Attack(void); // 攻撃
	void SetMoveRotation(void); // 向きから移動量を設定する処理
	bool SearchPlayer(float fLen); // プレイヤーとの距離判定
	void FixRotation(void); // 指定方向を向く
	void Roaming(void); // 徘徊
	void RotationPlayer(void) override;		// プレイヤーを向く処理

};

#endif
