//==========================================
//
//  ��������G(enemy_explosion.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_EXPLOSION_H_
#define _ENEMY_EXPLOSION_H_
#include "enemy.h"

//==========================================
//  �N���X��`
//==========================================
class CEnemyExplosion : public CEnemy
{
public:

	// �I�[�o�[���C�h���ꂽ�֐�
	CEnemyExplosion(int nPriority = mylib_const::ENEMY_PRIORITY);
	~CEnemyExplosion();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Kill(void) override;

private:

	//���[�V������
	enum MOTION
	{
		MOTION_DEF = 0,		// �j���[�g�������[�V����
		MOTION_WALK,		// �ړ����[�V����
		MOTION_ATK,			// �U�����[�V����
		MOTION_KNOCKBACK,	// ���ꃂ�[�V����
		MOTION_FADEOUT,		// �A�҃��[�V����
		MOTION_MAX
	};

	// �s����
	enum ACTION
	{
		ACTION_ROAMING = 0, // �p�j�s��
		ACTION_CHASE, // �ǐՍs��
		ACTION_COUNTDOWN, // �J�E���g�_�E���s��
		ACTION_EXPROSION, // �����s��
		ACTION_FADE, // ���ōs��
		MAX
	};

	// �����o�ϐ�
	ACTION m_Act; //�s�����
	float m_fCntWalk; // �����]��
	float m_fCntFind; // �����J�E���^�[
	float m_fCntEscape; // �����J�E���^�[
	float m_fRot; // ���������Ƃ��`
	float m_fCountDawn; // �����J�E���g�_�E��
	float m_fCol; // �}�e���A���J���[�ς���

	// �����o�֐�
	void MotionSet(void) override;		// ���[�V�����̐ݒ�
	void UpdateAction(void) override;	// �s���X�V
	void Move(void) override; // �ړ�
	void RandTurn(void); // �����_���ȕ����]��
	void ActionSet(void); // �s���̐ݒ�
	void Flash(void); // �_��

};

#endif
