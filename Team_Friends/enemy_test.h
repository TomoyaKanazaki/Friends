//==========================================
//
//  コピペ用の敵(enemy_test.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_TEST_H_
#define _ENEMY_TEST_H_
#include "enemy.h"

//==========================================
//  クラス定義
//==========================================
class CEnemyTest : public CEnemy
{
public:

	// オーバーライドされた関数
	CEnemyTest(int nPriority = mylib_const::ENEMY_PRIORITY);
	~CEnemyTest();

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
		ACTION_DEF = 0, //待機行動
		ACTION_RETURN, //帰還行動
		ACTION_ATTACK, //攻撃行動
		ACTION_SEARCH, //索敵行動
		ACTION_CHASE, //追跡行動
		MAX
	};

	// メンバ変数
	ACTION m_Act; //行動状態
	D3DXVECTOR3 m_posDefault; //初期位置

	// メンバ関数
	void ActionSet(void); // 行動の設定
	bool CalcLenDefault(void); //初期位置に戻る処理
	void RotationPlayer(void); // プレイヤーを向く処理
	bool CalcLenPlayer(float fLen); // プレイヤーとの距離判定

};

#endif
