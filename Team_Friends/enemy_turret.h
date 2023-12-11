//=============================================================================
// 
//  中ボス(砲台) [enemy_turret.h]
//  Author : 髙田佳依
// 
//=============================================================================

#ifndef _ENEMYTURRET_H_
#define _ENEMYTURRET_H_	// 二重インクルード防止

#include "enemy.h"

//==========================================================================
// 前方宣言
//==========================================================================
class CLimitArea;
class CBulletPoint;
class CBullet;

//==========================================================================
// クラス定義
//==========================================================================
// ボスクラス定義
class CEnemyTurret : public CEnemy
{
public:

	CEnemyTurret(int nPriority = mylib_const::ENEMY_PRIORITY);
	~CEnemyTurret();

	// オーバーライドされた関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Kill(void) override;

	void SetTargetPosition(D3DXVECTOR3 pos);	// 目標の位置設定

	//=============================
	// 列挙型定義
	//=============================
	//モーション列挙
	enum MOTION
	{
		MOTION_DEF = 0,			// ニュートラルモーション
		MOTION_CHARGE_BEAM,		// ビームチャージモーション
		MOTION_BEAM,			// ビームモーション
		MOTION_CHARGE_MORTAR,	// タックルチャージモーション
		MOTION_MORTAR,			// タックルモーション
		MOTION_KNOCKBACK,		// やられモーション
		MOTION_FADEOUT,			// 帰還モーション
		MOTION_SPAWN,			// 出現モーション
	};

	// 行動列挙
	enum ACTION
	{
		ACTION_BEAM,			// ビーム攻撃
		ACTION_MORTAR,			// 迫撃攻撃
		ACTION_WAIT,			// 待機
		ACTION_SPAWN,			// 出現行動
		ACTION_MAX
	};

	// 行動分岐
	enum eActionBranch
	{
		ACTBRANCH_BEAM_CHARGE,		// ビーム攻撃(溜め)
		ACTBRANCH_BEAM_SHOT,		// ビーム攻撃(発射)
		ACTBRANCH_MORTAR_CHARGE,	// 迫撃攻撃(溜め)
		ACTBRANCH_MORTAR_SHOT,		// 迫撃攻撃(発射)
	};

private:

	//=============================
	// 関数リスト
	//=============================
	typedef void(CEnemyTurret::*ACT_FUNC)(void);
	static ACT_FUNC m_ActFuncList[];

	//=============================
	// メンバ関数
	//=============================
	// 行動関数
	void ActionSet(void) override;		// 行動の設定
	void DrawingAction(void);			// 行動抽選
	void UpdateAction(void) override;	// 行動更新
	void ActWait(void);				// 待機
	void ActAttackBeam(void);		// 遠隔攻撃
	void ActAttackMortar(void);		// 迫撃攻撃
	void Spawn(void) override;		// スポーン

	// 行動内関数
	void ChargeBeam(void);		// ビームチャージ
	void AttackBeam(void);		// ビーム攻撃
	void ChargeMortar(void);	// 迫撃チャージ
	void AttackMortar(void);	// 迫撃攻撃

	// その他関数
	void MotionSet(void) override;	// モーションの設定
	void RotationTarget(void);		// ターゲットの方を向く
	void SetTargetPlayer(void);		// どのプレイヤーのターゲット

	void SummonArea(void);		// エリア生成
	void DeleteShadow(void);		// 影消し

	//=============================
	// メンバ変数
	//=============================
	ACTION m_Action;						// 行動
	eActionBranch m_ActionBranch;			// 行動分岐
	eActionBranch m_MakeForActionBranch;	// 行動する為の行動
	D3DXVECTOR3 m_TargetPosition;	// 目標の位置
	float m_fActTime;				// 行動カウンター
	float m_fRotLock;			//向き保存
	CLimitArea *m_pLimitArea;	//ボス範囲
	bool m_bArea;				//エリア展開フラグ
	CBulletPoint *m_pBulletPoint[mylib_const::MAX_PLAYER];			// 影の情報
	CBullet *m_pBullet[mylib_const::MAX_PLAYER];			// 弾の情報
};

#endif