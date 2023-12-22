//=============================================================================
// 
//  ���̃v���C���[�w�b�_�[ [player_union.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _PLAYER_UNION_H_
#define _PLAYER_UNION_H_	// ��d�C���N���[�h�h�~

#include "objectChara.h"
#include "motion.h"

//==========================================================================
// �}�N����`
//==========================================================================

// �O���錾
class CShadow;
class CTargetPoint;
class CHP_GaugePlayer;
class CUnionCore;

//==========================================================================
// �N���X��`
//==========================================================================
// ���̃v���C���[�N���X��`
class CPlayerUnion : public CObject
{
public:

	// ��Ԓ�`
	enum STATE
	{
		STATE_NONE = 0,		// �Ȃɂ��Ȃ�
		STATE_INVINCIBLE,	// ���G
		STATE_DMG,			// �_���[�W
		STATE_KNOCKBACK,	// �m�b�N�o�b�N
		STATE_DEAD,			// ��
		STATE_FADEOUT,		// �t�F�[�h�A�E�g
		STATE_ATTACK,		// �U������
		STATE_APPEARANCE,	// �o��
		STATE_ULT,			// �K�E�Z���
		STATE_MAX
	};

	// ���̎��
	enum eType
	{
		TYPE_ALL = 0,	// �S������
		TYPE_BODYtoLEG,	// ���~�r
		TYPE_BODYtoARM,	// ���~�r
		TYPE_LEGtoARM,	// �r�~�r
		TYPE_ARMtoARM,	// �r�~�r
		TYPE_MAX
	};

	enum eParts
	{
		PARTS_BODY = 0,
		PARTS_LEG,
		PARTS_R_ARM,
		PARTS_L_ARM,
		PARTS_MAX
	};

	CPlayerUnion(int nPriority = mylib_const::PRIORITY_DEF2D);
	~CPlayerUnion();

	// �I�[�o�[���C�h���ꂽ�֐�
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual bool Hit(const int nValue);	// �q�b�g����
	int GetState(void);

	static CPlayerUnion *Create(eType type);	// ����
	void UninitByMode(void);
	void Kill(void);	// ���S����
	void SetPlayerByPartsIdx(int nPartsIdx, int nPlayerIdx);	// �v���C���[���̃p�[�c�C���f�b�N�X�ԍ��ݒ�
	void SetControllMoveIdx(int nIdx);	// �ړ��̑��삷��C���f�b�N�X�ԍ��ݒ�

protected:

	// ���[�V�����̔���
	struct SMotionFrag
	{
		bool bJump;		// �W�����v��
		bool bATK;		// �U����
		bool bCharge;	// �`���[�W��
		bool bMove;		// �ړ���
		bool bUltEntry;	// �K�E�G���g���[
	};


	// ��ԏ���
	virtual void UpdateState(void);	// ��ԍX�V����
	virtual void KnockBack(void);	// �m�b�N�o�b�N
	virtual void Damage(void);		// �_���[�W
	virtual void Dead(void);		// ���S
	virtual void FadeOut(void);		// �t�F�[�h�A�E�g
	virtual void Invincible(void);	// ���G
	virtual void Appearance(void);	// �o��
	virtual void Ultimate(void);	// �K�E�Z

	void BindByPlayerIdxTexture(int nIdx, int nPartsIdx);	// �v���C���[�C���f�b�N�X���̃e�N�X�`���ݒ�
	void ReadMultiCharacter(const char *pTextFile);			// �����L�����N�^�[�ǂݍ���
	bool Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &move);	// �����蔻��
	virtual void AttackAction(int nIdx, int nModelNum, CMotion::AttackInfo ATKInfo, int nCntATK);	// �U��������
	virtual void AttackInDicision(int nIdx, CMotion::AttackInfo ATKInfo, int nCntATK);				// �U�����蒆����
	virtual void ControllParts(void);	// �p�[�c�̃R���g���[������
	virtual void MotionSet(int nIdx);	// ���[�V�����̐ݒ�
	virtual void Atack(int nIdx);		// �U��
	bool ControllMove(int nIdx);	// �ړ�����
	void ControllRotation(int nIdx);	// ��]����
	virtual HRESULT CreateParts(void);	// �p�[�c�̐ݒ�
	int GetModelIdxtFromPartsIdx(int nModelIdx);	// ���f���C���f�b�N�X����p�[�c�̃C���f�b�N�X�擾

	bool m_bJump;				// �W�����v�����ǂ���
	bool m_bLandOld;			// �ߋ��̒��n���
	bool m_bHitStage;			// �X�e�[�W�̓����蔻��
	bool m_bLandField;			// �t�B�[���h�̒��n����
	bool m_bHitWall;			// �ǂ̓����蔻��
	bool m_bKnockBack;			// �m�b�N�o�b�N�����ǂ���
	bool m_bDead;			// ���S�����ǂ���

	int m_nPartsIdx[mylib_const::MAX_PLAYER];	// �v���C���[���̃p�[�c�C���f�b�N�X�ԍ�
	int m_nMyPlayerIdx;			// �v���C���[�C���f�b�N�X�ԍ�
	int m_nControllMoveIdx;		// �ړ����삷���̃C���f�b�N�X�ԍ�
	int m_nCntWalk;				// ���s�J�E���^�[
	int m_nUnionLife;			// ���̎���
	int m_nCntInputAtk;			// �U���̓��̓J�E���^�[

	int m_nInputSuperAtkIdx;	// �K�E�Z���͂̃C���f�b�N�X
	int m_nIntervalAlternately;	// ���ݓ��͂̃C���^�[�o��
	int m_nCntInputSuperATK;	// �K�E�Z�̓��͉�

	D3DXCOLOR m_mMatcol;		// �}�e���A���̐F
	STATE m_Oldstate;			// �O��̏��
	STATE m_state;			// ���
	int m_nCntState;			// ��ԑJ�ڃJ�E���^�[
	D3DXVECTOR3 m_posKnokBack;	// �m�b�N�o�b�N�̈ʒu
	D3DXVECTOR3 m_KnokBackMove;	// �m�b�N�o�b�N�̈ړ���
	CMotion *m_pMotion[PARTS_MAX];			// �p�[�c���̃��[�V�����|�C���^
	SMotionFrag m_sMotionFrag[PARTS_MAX];	// ���[�V�����̃t���O
	CObjectChara *m_pObjChara[PARTS_MAX];	// �p�[�c���̃I�u�W�F�N�g�L�����N�^�[�|�C���^
	CModel *m_apModel[mylib_const::MAX_MODEL];	// ���f��(�p�[�c)�̃|�C���^
private:

	// �R���{�����U�̎��
	enum eSPSkill
	{
		SKILL_MAX
	};

	// �񋓌^��`
	enum MOTION
	{
		MOTION_DEF = 0,				// �j���[�g�������[�V����
		MOTION_WALK,				// �ړ����[�V����
		MOTION_BOOST,				// �u�[�X�g���[�V����
		MOTION_NORMAL_CHARGE,		// �ʏ�`���[�W
		MOTION_NORMAL_ATK,			// �ʏ�U��
		MOTION_ULT_BEAMCHARGE,		// �K�E�Z�r�[���`���[�W
		MOTION_ULT_BEAMATK,			// �K�E�Z�r�[���U��
		MOTION_ULT_BIGPUNCHCHARGE,	// �K�E�Z�f�J�p���`�`���[�W
		MOTION_ULT_BIGPUNCHATK,		// �K�E�Z�f�J�p���`�U��
		MOTION_ULT_RIDERKICKCHARGE,	// �K�E�Z���C�_�[�L�b�N�`���[�W
		MOTION_ULT_RIDERKICKATK,	// �K�E�Z���C�_�[�L�b�N�U��
		MOTION_ULT_BOOSTPUNCHCHARGE,	// �K�E�Z�u�[�X�g�p���`�`���[�W
		MOTION_ULT_BOOSTPUNCHATK,	// �K�E�Z�u�[�X�g�p���`�U��
		MOTION_ULT_RUSHCHARGE,		// �K�E�Z���b�V���`���[�W
		MOTION_ULT_RUSHATK,			// �K�E�Z���b�V���U��
		MOTION_KNOCKBACK,			// ���ꃂ�[�V����
		MOTION_DEAD,				// ���S���[�V����
		MOTION_APPEARANCE,			// �o��
		MOTION_MAX
	};

	enum eUltAttack
	{
		ULT_BEAM = 0,	// �r�[��
		ULT_BIGPUNCH,	// �r�b�O�p���`
		ULT_RIDERKICK,	// ���C�_�[�L�b�N
		ULT_BOOSTPUNCH,	// �u�[�X�g�p���`
		ULT_RUSH,		// ���b�V��
		ULT_MAX
	};

	enum eUltBranch
	{
		ULTBRANCH_CHARGE_BEAM = 0,		// �r�[���`���[�W
		ULTBRANCH_ATTACK_BEAM,			// �r�[���U��
		ULTBRANCH_CHARGE_BIGPUNCH,		// �f�J�p���`�`���[�W
		ULTBRANCH_ATTACK_BIGPUNCH,		// �f�J�p���`�U��
		ULTBRANCH_CHARGE_RIDERKICK,		// ���C�_�[�L�b�N�`���[�W
		ULTBRANCH_ATTACK_RIDERKICK,		// ���C�_�[�L�b�N�U��
		ULTBRANCH_CHARGE_BOOSTPUNCH,	// �u�[�X�g�p���`�`���[�W
		ULTBRANCH_ATTACK_BOOSTPUNCH,	// �u�[�X�g�p���`�U��
		ULTBRANCH_CHARGE_RUSH,			// ���b�V���`���[�W
		ULTBRANCH_ATTACK_RUSH,			// ���b�V���U��
		ULTBRANCH_MAX
	};

	//=============================
	// �֐����X�g
	//=============================
	typedef void(CPlayerUnion::*ULT_FUNC)(void);
	static ULT_FUNC m_UltFuncList[];	// �K�E�Z�̊֐����X�g

	// �K�E�Z�֐�
	void UltBeam(void);			// �r�[��
	void UltBigPunch(void);		// �f�J�p���`
	void UltRiderKick(void);	// ���C�_�[�L�b�N
	void UltBoostPunch(void);	// �u�[�X�g�p���`
	void UltRush(void);			// ���b�V��

	// �K�E����֐�
	void UltChargeBeam(void);		// �r�[���`���[�W
	void UltAttackBeam(void);		// �r�[���U��
	void UltChargeBigPunch(void);	// �f�J�p���`�`���[�W
	void UltAttackBigPunch(void);	// �f�J�p���`�U��
	void UltChargeRiderKick(void);	// ���C�_�[�L�b�N�`���[�W
	void UltAttackRiderKick(void);	// ���C�_�[�L�b�N�U��
	void UltChargeBoostPunch(void);	// �u�[�X�g�p���`�`���[�W
	void UltAttackBoostPunch(void);	// �u�[�X�g�p���`�U��
	void UltChargeRush(void);		// ���b�V���`���[�W
	void UltAttackRush(void);		// ���b�V���U��

	// �����o�֐�
	void Controll(void);		// ����
	void ControllBody(int nIdx, int nLoop);		// ������
	void ControllLeg(int nIdx, int nLoop);			// �r����
	void ControllRightArm(int nIdx, int nLoop);	// �E�r����
	void ControllLeftArm(int nIdx, int nLoop);		// ���r����
	void EntryUltimate(int nIdx, int nLoop);	// �K�E�G���g���[
	void UpdateEntry(void);	// �G���g���[�֘A�̍X�V
	void DrawingUlt(int nFirst, int nSecond);	// �E���g�撊�I

	// �����o�ϐ�
	int m_nTexIdx;				// �e�N�X�`���̃C���f�b�N�X�ԍ�
	int m_nIdxXFile;			// X�t�@�C���̃C���f�b�N�X�ԍ�
	float m_fRotDest;			// �ڕW�̌���
	CShadow *m_pShadow;			// �e�̏��
	CTargetPoint *m_pTargetP;	// �ڕW�̒n�_
	CHP_GaugePlayer *m_pHPGauge;	// HP�Q�[�W�̏��
	CUnionCore *m_pUnionCore;		// ���̌�R�A
	eUltAttack m_UltType;			// �K�E�Z�̎��
	eUltBranch m_UltBranch;			// �K�E�Z�̕���
	bool m_bUltBigArm;				// �E���g�Řr�f�J��������
	float m_fUltGaugeValue[mylib_const::MAX_PLAYER];		// �K�E�Q�[�W�̗�
	float m_fCooltimeBoost;	// �u�[�X�g�̃N�[���^�C��
	float m_fBoostTime;	// �u�[�X�g�̃^�C��
	std::vector<int> m_nModelIdx[mylib_const::MAX_PLAYER];	// �e�p�[�c���Ƃ̃��f���C���f�b�N�X�ԍ�
	static bool m_bAllLandInjectionTable;	// �S���̎ˏo�䒅�n����
	static bool m_bLandInjectionTable[mylib_const::MAX_PLAYER];	// �ˏo��̒��n����

};



#endif