//=============================================================================
// 
//  {X(Cä) [enemy_turret.h]
//  Author : ûücÀË
// 
//=============================================================================

#ifndef _ENEMYTURRET_H_
#define _ENEMYTURRET_H_	// ñdCN[hh~

#include "enemy.h"

//==========================================================================
// Oûé¾
//==========================================================================
class CLimitArea;
class CShadow;
class CBullet;

//==========================================================================
// NXè`
//==========================================================================
// {XNXè`
class CEnemyTurret : public CEnemy
{
public:

	CEnemyTurret(int nPriority = mylib_const::ENEMY_PRIORITY);
	~CEnemyTurret();

	// I[o[Ch³ê½Ö
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Kill(void) override;

	void SetTargetPosition(D3DXVECTOR3 pos);	// ÚWÌÊuÝè

	//=============================
	// ñ^è`
	//=============================
	//[Vñ
	enum MOTION
	{
		MOTION_DEF = 0,			// j[g[V
		MOTION_CHARGE_BEAM,		// r[`[W[V
		MOTION_BEAM,			// r[[V
		MOTION_CHARGE_MORTAR,	// ^bN`[W[V
		MOTION_MORTAR,			// ^bN[V
		MOTION_KNOCKBACK,		// âçê[V
		MOTION_FADEOUT,			// AÒ[V
		MOTION_SPAWN,			// o»[V
	};

	// s®ñ
	enum ACTION
	{
		ACTION_BEAM,			// r[U
		ACTION_MORTAR,			// U
		ACTION_WAIT,			// Ò@
		ACTION_SPAWN,			// o»s®
		ACTION_MAX
	};

	// s®ªò
	enum eActionBranch
	{
		ACTBRANCH_BEAM_CHARGE,		// r[U(­ß)
		ACTBRANCH_BEAM_SHOT,		// r[U(­Ë)
		ACTBRANCH_MORTAR_CHARGE,	// U(­ß)
		ACTBRANCH_MORTAR_SHOT,		// U(­Ë)
	};

private:

	//=============================
	// ÖXg
	//=============================
	typedef void(CEnemyTurret::*ACT_FUNC)(void);
	static ACT_FUNC m_ActFuncList[];

	//=============================
	// oÖ
	//=============================
	// s®Ö
	void ActionSet(void) override;		// s®ÌÝè
	void DrawingAction(void);			// s®I
	void UpdateAction(void) override;	// s®XV
	void ActWait(void);				// Ò@
	void ActAttackBeam(void);		// uU
	void ActAttackMortar(void);		// U
	void Spawn(void) override;		// X|[

	// s®àÖ
	void ChargeBeam(void);		// r[`[W
	void AttackBeam(void);		// r[U
	void ChargeMortar(void);	// `[W
	void AttackMortar(void);	// U

	// »Ì¼Ö
	void MotionSet(void) override;	// [VÌÝè
	void RotationTarget(void);		// ^[QbgÌûðü­
	void SetTargetPlayer(void);		// ÇÌvC[Ì^[Qbg

	void SummonArea(void);		// GA¶¬
	void DeleteShadow(void);		// eÁµ

	//=============================
	// oÏ
	//=============================
	ACTION m_Action;						// s®
	eActionBranch m_ActionBranch;			// s®ªò
	eActionBranch m_MakeForActionBranch;	// s®·é×Ìs®
	D3DXVECTOR3 m_TargetPosition;	// ÚWÌÊu
	float m_fActTime;				// s®JE^[
	float m_fRotLock;			//ü«Û¶
	CLimitArea *m_pLimitArea;	//{XÍÍ
	bool m_bArea;				//GAWJtO
	CShadow *m_pShadow[mylib_const::MAX_PLAYER];			// eÌîñ
	CBullet *pBullet;		//e»èpÌep
};

#endif