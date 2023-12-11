//=============================================================================
// 
//  ���{�X(�C��) [enemy_turret.h]
//  Author : ���c����
// 
//=============================================================================

#ifndef _ENEMYTURRET_H_
#define _ENEMYTURRET_H_	// ��d�C���N���[�h�h�~

#include "enemy.h"

//==========================================================================
// �O���錾
//==========================================================================
class CLimitArea;
class CBulletPoint;
class CBullet;

//==========================================================================
// �N���X��`
//==========================================================================
// �{�X�N���X��`
class CEnemyTurret : public CEnemy
{
public:

	CEnemyTurret(int nPriority = mylib_const::ENEMY_PRIORITY);
	~CEnemyTurret();

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Kill(void) override;

	void SetTargetPosition(D3DXVECTOR3 pos);	// �ڕW�̈ʒu�ݒ�

	//=============================
	// �񋓌^��`
	//=============================
	//���[�V������
	enum MOTION
	{
		MOTION_DEF = 0,			// �j���[�g�������[�V����
		MOTION_CHARGE_BEAM,		// �r�[���`���[�W���[�V����
		MOTION_BEAM,			// �r�[�����[�V����
		MOTION_CHARGE_MORTAR,	// �^�b�N���`���[�W���[�V����
		MOTION_MORTAR,			// �^�b�N�����[�V����
		MOTION_KNOCKBACK,		// ���ꃂ�[�V����
		MOTION_FADEOUT,			// �A�҃��[�V����
		MOTION_SPAWN,			// �o�����[�V����
	};

	// �s����
	enum ACTION
	{
		ACTION_BEAM,			// �r�[���U��
		ACTION_MORTAR,			// �����U��
		ACTION_WAIT,			// �ҋ@
		ACTION_SPAWN,			// �o���s��
		ACTION_MAX
	};

	// �s������
	enum eActionBranch
	{
		ACTBRANCH_BEAM_CHARGE,		// �r�[���U��(����)
		ACTBRANCH_BEAM_SHOT,		// �r�[���U��(����)
		ACTBRANCH_MORTAR_CHARGE,	// �����U��(����)
		ACTBRANCH_MORTAR_SHOT,		// �����U��(����)
	};

private:

	//=============================
	// �֐����X�g
	//=============================
	typedef void(CEnemyTurret::*ACT_FUNC)(void);
	static ACT_FUNC m_ActFuncList[];

	//=============================
	// �����o�֐�
	//=============================
	// �s���֐�
	void ActionSet(void) override;		// �s���̐ݒ�
	void DrawingAction(void);			// �s�����I
	void UpdateAction(void) override;	// �s���X�V
	void ActWait(void);				// �ҋ@
	void ActAttackBeam(void);		// ���u�U��
	void ActAttackMortar(void);		// �����U��
	void Spawn(void) override;		// �X�|�[��

	// �s�����֐�
	void ChargeBeam(void);		// �r�[���`���[�W
	void AttackBeam(void);		// �r�[���U��
	void ChargeMortar(void);	// �����`���[�W
	void AttackMortar(void);	// �����U��

	// ���̑��֐�
	void MotionSet(void) override;	// ���[�V�����̐ݒ�
	void RotationTarget(void);		// �^�[�Q�b�g�̕�������
	void SetTargetPlayer(void);		// �ǂ̃v���C���[�̃^�[�Q�b�g

	void SummonArea(void);		// �G���A����
	void DeleteShadow(void);		// �e����

	//=============================
	// �����o�ϐ�
	//=============================
	ACTION m_Action;						// �s��
	eActionBranch m_ActionBranch;			// �s������
	eActionBranch m_MakeForActionBranch;	// �s������ׂ̍s��
	D3DXVECTOR3 m_TargetPosition;	// �ڕW�̈ʒu
	float m_fActTime;				// �s���J�E���^�[
	float m_fRotLock;			//�����ۑ�
	CLimitArea *m_pLimitArea;	//�{�X�͈�
	bool m_bArea;				//�G���A�W�J�t���O
	CBulletPoint *m_pBulletPoint[mylib_const::MAX_PLAYER];			// �e�̏��
	CBullet *m_pBullet[mylib_const::MAX_PLAYER];			// �e�̏��
};

#endif