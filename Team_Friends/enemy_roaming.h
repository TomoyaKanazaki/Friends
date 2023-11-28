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
//  クラス定義
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
	void MotionSet(void) override;		// モーションの設定

	// メンバ関数
	void SetDefaultPos(const D3DXVECTOR3 pos);

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
	D3DXVECTOR3 m_posDefault; //初期位置
	float m_fMoveCount; // 移動カウンター

	// メンバ関数
	void ActionSet(void); // 行動の設定
	void Move(void); // 移動
	void MoveRotation(void); // 移動方向を向く
	void Attack(void); // 攻撃
	void RotationPlayer(void); // プレイヤーを向く処理
	bool CalcLenPlayer(float fLen); // プレイヤーとの距離判定

};

#endif
