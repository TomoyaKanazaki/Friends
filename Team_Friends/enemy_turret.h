//==========================================
//
//  砲台中ボス敵(enemy_turret.h)
//  Author : Kai Takada
//
//==========================================
#ifndef _ENEMY_TURRET_H_
#define _ENEMY_TURRET_H_
#include "enemy.h"

//==========================================
//  クラス定義
//==========================================
class CEnemyTurret: public CEnemy
{
public:

	// オーバーライドされた関数
	CEnemyTurret(int nPriority = mylib_const::ENEMY_PRIORITY);
	~CEnemyTurret();

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
		MOTION_DEF = 0,			// ニュートラルモーション
		MOTION_KNOCKBACK,		// ダメージモーション
		MOTION_FADEOUT,			// 撃破モーション
		MOTION_ATK_MORTAR,		// 攻撃モーション(迫撃)
		MOTION_READY_MORTAR,	// 準備モーション(迫撃)
		MOTION_AFTER_MORTAR,	// 硬直モーション(迫撃)
		MOTION_ATK_BEAM,		// 攻撃モーション(ビーム)
		MOTION_READY_BEAM,		// 準備モーション(ビーム)
		MOTION_AFTER_BEAM,		// 硬直モーション(ビーム)
		MOTION_MAX
	};

	// 行動列挙
	enum ACTION
	{
		ACTION_ROAMING = 0,	//徘徊行動
		ACTION_READY,		//準備行動
		ACTION_ATTACK,		//攻撃行動
		ACTION_AFTER,		//攻撃硬直
		ACTION_MAX
	};

	// 攻撃列挙
	enum ATTACK
	{
		ATTACK_NONE = 0,	//攻撃と無関係
		ATTACK_BEAM= 0,		//ビーム
		ATTACK_MORTAR,		//迫撃砲
		ATTACK_MAX
	};

	// メンバ変数
	ACTION m_Act;	//行動状態
	ATTACK m_Atk;	//攻撃状態
	float m_fActionCount;	// 移動カウンター
	D3DXVECTOR3 m_moveLock;	//固定移動量
	float m_fRotLock;	//向き保存

	// メンバ関数
	void UpdateAction(void) override;	// 行動更新
	void ActionSet(void); // 行動の設定
	void Move(void); // 移動
	void MoveRotation(void); // 移動方向を向く
	void Attack(void); // 攻撃
	void RotationPlayer(void); // プレイヤーを向く処理
	void SetMoveRotation(void); // 向きから移動量を設定する処理
	bool SearchPlayer(float fLen); // プレイヤーとの距離判定
	void FixRotation(void); // 指定方向を向く
};

#endif
