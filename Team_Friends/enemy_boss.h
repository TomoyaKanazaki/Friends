//=============================================================================
// 
//  �{�X�w�b�_�[ [enemy_boss.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _ENEMYBOSS_H_
#define _ENEMYBOSS_H_	// ��d�C���N���[�h�h�~

#include "enemy.h"

// �O���錾
class CHP_GaugeBoss;

//==========================================================================
// �N���X��`
//==========================================================================
// �{�X�N���X��`
class CEnemyBoss : public CEnemy
{
public:

	//=============================
	// �񋓌^��`
	//=============================
	//���[�V������
	enum MOTION
	{
		MOTION_DEF = 0,			// �j���[�g�������[�V����
		MOTION_WALK,			// �ړ����[�V����
		MOTION_DASH,			// �_�b�V���ړ����[�V����
		MOTION_GUARD,			// �K�[�h���[�V����
		MOTION_PUNCH,			// �p���`���[�V����
		MOTION_KICK,			// �L�b�N���[�V����
		MOTION_BEAM,			// �r�[�����[�V����
		MOTION_CHARGE_TACKLE,	// �^�b�N���`���[�W���[�V����
		MOTION_TACKLE,			// �^�b�N�����[�V����
		MOTION_KNOCKBACK,		// ���ꃂ�[�V����
		MOTION_FADEOUT,			// �A�҃��[�V����
	};

	// �s������
	enum eActionBranch
	{
		ACTBRANCH_CHASE_SLOW = 0,	// �����Ǐ]
		ACTBRANCH_CHASE_DASH,		// �_�b�V���Ǐ]
		ACTBRANCH_PROXIMITY_PUNCH,	// �ߐڍU��(�p���`)
		ACTBRANCH_PROXIMITY_KICK,	// �ߐڍU��(�L�b�N)
		ACTBRANCH_REMOTE_BEAM,		// �������U��(�r�[��)
		ACTBRANCH_ASSAULT_CHARGE,	// �ˌ��U��(����)
		ACTBRANCH_ASSAULT_TACKLE,	// �ˌ��U��(�^�b�N��)
	};

	// �s����
	enum ACTION
	{
		ACTION_CHASE = 0,		// �Ǐ]
		ACTION_PROXIMITY,		// �ߐڍU��
		ACTION_REMOTE,			// ���u�U��
		ACTION_ASSAULT,			// �ˌ��U��
		ACTION_WAIT,			// �ҋ@
		ACTION_GUARD,			// �K�[�h
		ACTION_SELFEXPLOSION,	// ����
		ACTION_MAX
	};

	CEnemyBoss(int nPriority = mylib_const::ENEMY_PRIORITY);
	~CEnemyBoss();

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Kill(void) override;

	void SetAction(ACTION action) { m_Action = action; }	// �A�N�V�����ݒ�
	void SetTargetPosition(D3DXVECTOR3 pos);	// �ڕW�̈ʒu�ݒ�

private:


	//=============================
	// �֐����X�g
	//=============================
	typedef void(CEnemyBoss::*ACT_FUNC)(void);
	static ACT_FUNC m_ActFuncList[];	// �s���֐����X�g

	//=============================
	// �����o�֐�
	//=============================
	// �s���֐�
	void ActionSet(void) override;		// �s���̐ݒ�
	void DrawingAction(void);			// �s�����I
	void UpdateAction(void) override;	// �s���X�V
	void ActChase(void);				// �ǂ��|��
	void ActAttackProximity(void);		// �ߐڍU��
	void ActAttackRemote(void);			// ���u�U��
	void ActAttackAssault(void);		// �ˌ��U��
	void ActWait(void);					// �ҋ@
	void ActGuard(void);				// �K�[�h
	void ActAttackExplosion(void);		// �����U��

	// �s�����֐�
	void ChaseSlow(void);		// �����ǂ��|��
	void ChaseDash(void);		// �_�b�V���ǂ��|��
	void AttackPunch(void);		// �p���`�U��
	void AttackKick(void);		// �L�b�N�U��
	void AttackBeam(void);		// �r�[���U��
	void ChargeTackle(void);	// �^�b�N���`���[�W
	void AttackTackle(void);	// �^�b�N���U��

	// ���̑��֐�
	void MotionSet(void) override;	// ���[�V�����̐ݒ�
	void RotationTarget(void);		// �^�[�Q�b�g�̕�������
	void AttackAction(int nModelNum, CMotion::AttackInfo ATKInfo) override;	// �U��������
	void AttackInDicision(CMotion::AttackInfo ATKInfo) override;			// �U�����蒆����

	//=============================
	// �����o�ϐ�
	//=============================
	ACTION m_Action;		// �s��
	eActionBranch m_ActionBranch;	// �s������
	eActionBranch m_MakeForActionBranch;	// �s������ׂ̍s��
	D3DXVECTOR3 m_TargetPosition;	// �ڕW�̈ʒu
	float m_fActTime;		// �s���J�E���^�[
	float m_fAssultLength;		// �ˌ�����
	float m_fAssultLengthDest;	// �ڕW�̓ˌ�����
	bool m_bCatchUp;	// �ǂ���������
	CHP_GaugeBoss *m_pBossHPGauge;	// �{�X��HP�Q�[�W
};



#endif