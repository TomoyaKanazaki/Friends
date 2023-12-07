//==========================================
//
//  �M�K���g�G�b�W(enemy_riot.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_RIOT_H_
#define _ENEMY_RIOT_H_
#include "enemy.h"

//==========================================
//  �N���X��`
//==========================================
class CEnemyRiot : public CEnemy
{
public:

	// �I�[�o�[���C�h���ꂽ�֐�
	CEnemyRiot(int nPriority = mylib_const::ENEMY_PRIORITY);
	~CEnemyRiot();

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
		MOTION_SPAWN,		// �o�����[�V����
		MOTION_MAX
	};

	// �s����
	enum ACTION
	{
		ACTION_DEF = 0, // �ҋ@�s��
		ACTION_MOVE, // �ړ��s��
		ACTION_ATTACK, // �ʏ�U���s��
		ACTION_TACKLE, // �ːi�U���s��
		ACTION_AXIS, // �����킹�s��
		ACTION_SPAWN, // �o���s��
		MAX
	};

	// �����o�ϐ�
	ACTION m_Act; //�s�����
	float m_fWaitTime; // �ҋ@����
	int m_nCntAction; // �A���s����

	// �����o�֐�
	void Spawn(void) override;			// �X�|�[��
	void MotionSet(void) override;		// ���[�V�����̐ݒ�
	void ActionSet(void) override; // �s���̐ݒ�
	void Move(void) override; // �ړ�
	void Attack(void); // �U��

};

#endif
