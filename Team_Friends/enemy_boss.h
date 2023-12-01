//=============================================================================
// 
//  �{�X�w�b�_�[ [enemy_boss.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _ENEMYBOSS_H_
#define _ENEMYBOSS_H_	// ��d�C���N���[�h�h�~

#include "main.h"
#include "enemy.h"

// �O���錾

//==========================================================================
// �N���X��`
//==========================================================================
// �{�X�N���X��`
class CEnemyBoss : public CEnemy
{
public:

	CEnemyBoss(int nPriority = mylib_const::ENEMY_PRIORITY);
	~CEnemyBoss();

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Kill(void) override;
	void MotionSet(void) override;		// ���[�V�����̐ݒ�

protected:

private:

	//���[�V������
	typedef enum
	{
		MOTION_DEF = 0,		// �j���[�g�������[�V����
		MOTION_WALK,		// �ړ����[�V����
		MOTION_ATK,			// �U�����[�V����
		MOTION_KNOCKBACK,	// ���ꃂ�[�V����
		MOTION_FADEOUT,		// �A�҃��[�V����
	}MOTION;

	// �s����
	enum ACTION
	{
		ACTION_CHASE = 0,		// �Ǐ]
		ACTION_CHASE_DASH,		// �_�b�V���Ǐ]
		ACTION_PUNCH,			// �p���`
		ACTION_KICK,			// �L�b�N
		ACTION_BEAM,			// �r�[��
		ACTION_CHARGE_BEAM,		// �`���[�W�r�[��
		ACTION_TACKLE,			// �^�b�N��
		ACTION_CHARGE_TACKLE,	// �`���[�W�^�b�N��
		ACTION_SELFEXPLOSION,	// ����
		ACTION_MAX
	};

	// �����o�֐�
	void Move(void); // �ړ�

	// �����o�ϐ�
	ACTION m_Act;		// �s��
	float m_fActTime;	// �s���J�E���^�[

	// �֐����X�g
	typedef void(CEnemyBoss::*ACT_FUNC)(void);
	static ACT_FUNC m_ActFuncList[];
};



#endif