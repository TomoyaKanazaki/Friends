//=============================================================================
// 
//  �v���C���[�w�b�_�[ [player.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_	// ��d�C���N���[�h�h�~

#include "main.h"
#include "objectChara.h"

//==========================================================================
// �}�N����`
//==========================================================================
#define SLIDEMOVE		(2.05f)			// ��̈ړ���

// �O���錾
class CMotion;
class CShadow;
class CTargetPoint;
class CHP_GaugePlayer;

//==========================================================================
// �N���X��`
//==========================================================================
// �v���C���[�N���X��`
class CPlayer : public CObjectChara
{
public:

	// ��Ԓ�`
	typedef enum
	{
		STATE_NONE = 0,		// �Ȃɂ��Ȃ�
		STATE_INVINCIBLE,	// ���G
		STATE_DMG,			// �_���[�W
		STATE_KNOCKBACK,	// �m�b�N�o�b�N
		STATE_DEAD,			// ��
		STATE_FADEOUT,		// �t�F�[�h�A�E�g
		STATE_ATTACK,		// �U������
		STATE_MAX
	}STATE;

	CPlayer(int nPriority = mylib_const::DEF2D_PRIORITY);
	~CPlayer();


	// �I�[�o�[���C�h���ꂽ�֐�
	virtual HRESULT Init(void);
	void Uninit(void);
	virtual void Update(void);
	void Draw(void);
	bool Hit(const int nValue);	// �q�b�g����
	int GetState(void) override;

	static CPlayer *Create(int nIdx);	// ����
	void UninitByMode(void);
	void Kill(void);	// ���S����

protected:
	// �񋓌^��`
	enum MOTION
	{
		MOTION_DEF = 0,			// �j���[�g�������[�V����
		MOTION_WALK,			// �ړ����[�V����
		MOTION_ATK,				// �U��
		MOTION_ATK2,			// �U��(�h��)
		MOTION_KNOCKBACK,		// ���ꃂ�[�V����
		MOTION_DEAD,			// ���S���[�V����
		MOTION_JUMP,			// �W�����v
		MOTION_FALL,			// ������
		MOTION_MAX
	};

	// ���[�V�����̔���
	struct SMotionFrag
	{
		bool bJump;			// �W�����v�����ǂ���
		bool bATK;			// �U�������ǂ���
		bool bKnockBack;	// �m�b�N�o�b�N�����ǂ���
		bool bDead;			// ���S�����ǂ���
		bool bMove;			// �ړ������ǂ���
	};

	bool Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &move);	// �����蔻��

	bool m_bJump;				// �W�����v�����ǂ���
	bool m_bLandOld;			// �ߋ��̒��n���
	bool m_bHitStage;			// �X�e�[�W�̓����蔻��
	bool m_bLandField;			// �t�B�[���h�̒��n����
	bool m_bHitWall;			// �ǂ̓����蔻��
	int m_nMyPlayerIdx;			// �v���C���[�C���f�b�N�X�ԍ�
	int m_nCntWalk;				// ���s�J�E���^�[
	STATE m_state;			// ���
	CMotion *m_pMotion;		// ���[�V�����̏��
	SMotionFrag m_sMotionFrag;		// ���[�V�����̃t���O
private:

	// �����o�֐�
	void UpdateState(void);	// ��ԍX�V����
	void KnockBack(void);	// �m�b�N�o�b�N
	void Damage(void);		// �_���[�W
	void Dead(void);		// ���S
	void FadeOut(void);		// �t�F�[�h�A�E�g
	void Invincible(void);	// ���G
	virtual void Controll(void);	// ����
	void MotionSet(void);	// ���[�V�����̐ݒ�
	void Atack(void);		// �U��

	STATE m_Oldstate;			// �O��̏��
	D3DXCOLOR m_mMatcol;		// �}�e���A���̐F
	D3DXVECTOR3 m_posKnokBack;	// �m�b�N�o�b�N�̈ʒu
	D3DXVECTOR3 m_KnokBackMove;	// �m�b�N�o�b�N�̈ړ���
	int m_nCntState;			// ��ԑJ�ڃJ�E���^�[
	int m_nTexIdx;				// �e�N�X�`���̃C���f�b�N�X�ԍ�
	int m_nIdxXFile;			// X�t�@�C���̃C���f�b�N�X�ԍ�
	CShadow *m_pShadow;			// �e�̏��
	CTargetPoint *m_pTargetP;	// �ڕW�̒n�_
	CHP_GaugePlayer *m_pHPGauge;	// HP�Q�[�W�̏��
};



#endif