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

	void SetTargetPosition(D3DXVECTOR3 pos);	// 目標の位置設定
private:

	//=============================
	// 列挙型定義
	//=============================
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

	//=============================
	// 関数リスト
	//=============================
	typedef void(CEnemyBoss::*ACT_FUNC)(void);
	static ACT_FUNC m_ActFuncList[];

	//=============================
	// メンバ関数
	//=============================
	// 行動関数
	void UpdateAction(void) override;	// 行動更新
	void ActChase(void);		// 追い掛け
	void ActAttack(void);		// 攻撃
	void ActCharge(void);		// チャージ

	// 行動内関数
	void ChaseSlow(void);		// 歩き追い掛け
	void ChaseDash(void);		// ダッシュ追い掛け
	void AttackPunch(void);		// パンチ攻撃
	void AttackKick(void);		// キック攻撃
	void AttackTackle(void);	// タックル攻撃
	void ChargeBeam(void);		// ビームチャージ
	void ChargeTackle(void);	// タックルチャージ

	// その他関数
	void Move(void);			// 移動
	void RotationTarget(void);	// ターゲットの方を向く

	//=============================
	// メンバ変数
	//=============================
	ACTION m_Act;		// 行動
	D3DXVECTOR3 m_TargetPosition;	// 目標の位置
	float m_fActTime;	// 行動カウンター
};



#endif