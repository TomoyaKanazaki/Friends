//==========================================
//
//  �R�s�y�p�̓G(enemy_roaming.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_ROAMING_H_
#define _ENEMY_ROSMING_H_
#include "enemy.h"

//==========================================
// �N���X��`
//==========================================
class CEnemyRoaming : public CEnemy
{
public:

	// �I�[�o�[���C�h���ꂽ�֐�
	CEnemyRoaming(int nPriority = mylib_const::ENEMY_PRIORITY);
	~CEnemyRoaming();

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
		ACTION_ROAMING = 0, //�p�j�s��
		ACTION_ATTACK, //�U���s��
		MAX
	};

	// �����o�ϐ�
	ACTION m_Act; //�s�����

	// �����o�֐�
	void MotionSet(void) override;		// ���[�V�����̐ݒ�
	void UpdateAction(void) override;	// �s���X�V
	void ActionSet(void) override; // �s���̐ݒ�
	void Move(void) override; // �ړ�
	void Attack(void); // �U��

};

#endif
