//=============================================================================
// 
//  ���K�͍��̃v���C���[�w�b�_�[ [player_smallunion.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _PLAYER_SMALLUNION_H_
#define _PLAYER_SMALLUNION_H_	// ��d�C���N���[�h�h�~

#include "player_union.h"

//==========================================================================
// �}�N����`
//==========================================================================

// �O���錾
class CShadow;
class CTargetPoint;
class CHP_GaugePlayer;

//==========================================================================
// �N���X��`
//==========================================================================
// �v���C���[�N���X��`
class CPlayerSmallUnion : public CPlayerUnion
{
public:

	CPlayerSmallUnion(int nPriority = mylib_const::DEF2D_PRIORITY);
	~CPlayerSmallUnion();


	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	bool Hit(const int nValue) override;	// �q�b�g����

protected:
	// �񋓌^��`
	enum MOTION
	{
		MOTION_DEF = 0,			// �j���[�g�������[�V����
		MOTION_WALK,			// �ړ����[�V����
		MOTION_ATK,				// �U��
		MOTION_CHARGE,			// �`���[�W
		MOTION_KNOCKBACK,		// ���ꃂ�[�V����
		MOTION_DEAD,			// ���S���[�V����
		MOTION_JUMP,			// �W�����v
		MOTION_FALL,			// ������
		MOTION_MAX
	};

	virtual void AttackAction(int nIdx, int nModelNum, CMotion::AttackInfo ATKInfo);	// �U��������
	virtual void ControllParts(void);	// �p�[�c�̃R���g���[������
	virtual void MotionSet(int nIdx);	// ���[�V�����̐ݒ�
	virtual HRESULT CreateParts(void) override;	// �p�[�c�̐ݒ�
private:

	// �����o�֐�
	void ControllBody(int nIdx);		// ������
	void ControllLeg(int nIdx);			// �r����
	void ControllRightArm(int nIdx);	// �E�r����
	void ControllLeftArm(int nIdx);		// ���r����

	static const char *m_apModelFile[mylib_const::MAX_PLAYER];	// ���f���̃t�@�C��
};



#endif