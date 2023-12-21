//=============================================================================
// 
//  �v���C���[�w�b�_�[ [enemy.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _ENEMY_H_
#define _ENEMY_H_	// ��d�C���N���[�h�h�~

#include "main.h"
#include "objectChara.h"
#include "motion.h"
#include "enemymanager.h"
#include "resultmanager.h"

// �O���錾
class CHP_Gauge;
class CShadow;
class CEffect3D;
class CEnemyFixedMoveManager;
class CList;

//==========================================================================
// �N���X��`
//==========================================================================
// �v���C���[�N���X��`
class CEnemy : public CObjectChara
{
public:
	// �G���
	enum TYPE
	{
		TYPE_BOSS = 0,	// �{�X
		TYPE_FLY,
		TYPE_ROAMING, // �p�j
		TYPE_ESCAPE, // ���^���X���C��
		TYPE_TACKLE, // �ˌ���
		TYPE_TURRET, // ���{�X(�E�B�X�s�[�E�b�Y)
		TYPE_RIOT, // ���{�X(�M�K���g�G�b�W)
		TYPE_EXPLOSION, // �N���[�p�[
		TYPE_MAX
	};

	// ��ԗ�
	enum STATE
	{
		STATE_NONE = 0,		// �Ȃɂ��Ȃ�
		STATE_SPAWNWAIT,	// �X�|�[���ҋ@
		STATE_SPAWN,		// �X�|�[��
		STATE_DMG,			// �_���[�W
		STATE_DEAD,			// ��
		STATE_FADEOUT,		// �t�F�[�h�A�E�g
		STATE_PLAYERCHASE,	// �v���C���[�ǂ��|��
		STATE_PARENTCHASE,	// �e�ǂ��|��
		STATE_ATTACK,		// �U��
		STATE_WAIT,			// �ҋ@
		STATE_BASECHANGE,	// ���_�؂�ւ�
		STATE_MAX
	};

	// �s���� : ����
	enum ACTION
	{
		ACTION_DEF = 0, //�ҋ@�s��
		ACTION_ATTACK, //�U���s��
		ACTION_SEARCH, //���G�s��
	};

	CEnemy(int nPriority = mylib_const::ENEMY_PRIORITY);
	virtual ~CEnemy();

	static CEnemy *Create(int nIdx, const char *pFileName, D3DXVECTOR3 pos, TYPE type = TYPE_BOSS);

	// �I�[�o�[���C�h���ꂽ�֐�
	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;
	int GetState(void) override;
	void SetState(STATE state);		// ��Ԑݒ�
	void SetState(STATE state, int nCntState);	// ��Ԑݒ�
	int GetCharaType(void) override;	// ��ގ擾
	virtual bool Hit(const int nValue);

	void SetSpawnPosition(D3DXVECTOR3 pos);	// �X�|�[���n�_�ݒ�
	D3DXVECTOR3 GetSpawnPosition(void);	// �X�|�[���n�_�擾

	HRESULT RoadText(const char *pFileName);
	virtual void Kill(void);	// �폜
	void SetParent(CEnemy *pParent);		// �e�̃|�C���^�ݒ�
	void SetOriginRotation(D3DXVECTOR3 rot);	// ���̌���
	CEnemy *GetEnemy(void);

protected:

	enum COLORTYPE
	{
		COLORTYPE_NORMAL = 0,	// �m�[�}��
		COLORTYPE_POISON= 7,	// �ŃL�m�R
		COLORTYPE_LUCKY,		// �΂�1UP
		COLORTYPE_CONFUSION,	// �����U��
		COLORTYPE_SWIFTFOOT,	// �r�͂₢
		COLORTYPE_TUTORIAL,		// �`���[�g���A��
		COLORTYPE_MAX
	};

	// ���_�ʒu�̎��
	enum eBaseType
	{
		BASETYPE_MAP = 0,	// �}�b�v�ɉ����Ă���
		BASETYPE_ORIGIN,	// �o���ʒu
		BASETYPE_MAX
	};

	// ���[�V�����̔���
	struct SMotionFrag
	{
		bool bJump;			// �W�����v�����ǂ���
		bool bATK;			// �U�������ǂ���
		bool bKnockback;	// �m�b�N�o�b�N�����ǂ���
		bool bMove;			// �ړ������ǂ���
		bool bCharge;		// �`���[�W�����ǂ���
	};

	// ����̍\���̒�`
	struct SFormationInfo
	{
		D3DXVECTOR3 pos;	// ����̈ʒu
		float fAngle;		// ����
		float fLength;		// ����
	};

	// �}�N����`
#define SPAWN_GRAVITY	(-0.25f)

	virtual void ProcessLanding(void);	// ���n������
	virtual void AttackAction(int nModelNum, CMotion::AttackInfo ATKInfo);	// �U��������
	virtual void AttackInDicision(CMotion::AttackInfo ATKInfo);				// �U�����蒆����
	virtual void ChaseMove(float fMove);	// �ǂ��|���ړ�
	virtual void RotationPlayer(void);		// �v���C���[����������
	virtual bool CalcLenPlayer(float fLen); // �v���C���[�Ƃ̋�������
	virtual void MoveRotation(void);		// �ړ�����������
	virtual void Move(void);				// �ړ�

	virtual void UpdateAction(void);		// �s���X�V
	virtual void ActionSet(void) = 0;		// �s���̐ݒ�

	// ��ԍX�V�n
	virtual void StateNone(void);			// �����Ȃ����
	virtual void SpawnWait(void);			// �X�|�[���ҋ@
	virtual void Spawn(void);				// �X�|�[��
	virtual void Damage(void);				// �_���[�W
	virtual void Dead(void);				// ���S
	virtual void FadeOut(void);				// �t�F�[�h�A�E�g
	virtual void PlayerChase(void);			// �v���C���[�Ǐ]
	virtual void ParentChase(void);			// �e�Ǐ]
	virtual void StateAttack(void);			// �U������
	virtual void TriggerChasePlayer(void);	// �v���C���[�Ǐ]ON�ɂ���g���K�[
	virtual void ChangeToAttackState(void);	// �U����Ԉڍs����
	virtual void StateWait(void);			// �ҋ@����
	virtual void ChangeBase(void);			// ���_�؂�ւ�

	STATE m_state;							// ���
	STATE m_Oldstate;						// �O��̏��
	int m_nCntState;						// ��ԑJ�ڃJ�E���^�[
	int m_nTargetPlayerIndex;				// �ǂ��|����v���C���[�̃C���f�b�N�X�ԍ�
	float m_fActCounter;						// �ړ��J�E���^�[
	D3DXVECTOR3 m_posOrigin;				// �ŏ��̈ʒu
	D3DXVECTOR3 m_posKnokBack;				// �m�b�N�o�b�N�̈ʒu
	SMotionFrag m_sMotionFrag;				// ���[�V�����̃t���O
	CHP_Gauge *m_pHPGauge;					// HP�Q�[�W�̏��
	CMotion *m_pMotion;						// ���[�V�����̏��
	COLORTYPE m_colorType;					// �F���Ƃ̎��
	CEnemy *m_pParent;		// �e�̃|�C���^
	D3DXCOLOR m_mMatcol;	// �}�e���A���̐F
private:

	typedef enum
	{
		MOTION_DEF = 0,		// �j���[�g�������[�V����
		MOTION_WALK,		// �ړ����[�V����
		MOTION_ATK,			// �U��
		MOTION_KNOCKBACK,	// ���ꃂ�[�V����
		MOTION_FADEOUT,		// �y�A��
		MOTION_MAX
	}MOTION;
	
	void UpdateState(void);					// ��ԍX�V����
	virtual void UpdateStateByType(void);	// ��ޕʏ�ԍX�V����
	virtual void UpdateByType(void);		// ��ޕʍX�V����
	void Collision(void);					// �����蔻��
	virtual void CollisionPlayer(void);		// �v���C���[�Ƃ̓����蔻��
	virtual void MotionSet(void) = 0;		// ���[�V�����̐ݒ�
	void RegistrChild(CEnemy *pChild);
	void ResetChild(CEnemy *pChild);
	void Atack(void);		// �U��
	void LimitArea(void); // ��l�̕ǔ���

	TYPE m_type;			// ���
	SFormationInfo m_sFormationInfo;	// ����̏��
	D3DXVECTOR3 m_rotOrigin;	// �ŏ��̌���
	int m_nTexIdx;			// �e�N�X�`���̃C���f�b�N�X�ԍ�
	int m_nNumChild;		// �q�̐�
	int m_nIdxManager;		// �}�l�[�W���̃C���f�b�N�X�ԍ�
	bool m_bAddScore;		// �X�R�A���Z���邩�̔���
	int m_nBallastEmission;	// ���I�̔����J�E���^�[
	CEnemy *m_pChild[mylib_const::MAX_ENEMY];	// �q�̃|�C���^
	CShadow *m_pShadow;			// �e�̏��
	CList *m_pList;				// ���X�g�̃I�u�W�F�N�g
};



#endif