//==========================================
//
//  �C�䒆�{�X�G(enemy_turret.h)
//  Author : Kai Takada
//
//==========================================
#ifndef _ENEMY_TURRET_H_
#define _ENEMY_TURRET_H_
#include "enemy.h"

//==========================================
//  �N���X��`
//==========================================
class CEnemyTurret: public CEnemy
{
public:

	// �I�[�o�[���C�h���ꂽ�֐�
	CEnemyTurret(int nPriority = mylib_const::ENEMY_PRIORITY);
	~CEnemyTurret();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Kill(void) override;
	void MotionSet(void) override;		// ���[�V�����̐ݒ�

private:

	//���[�V������
	enum MOTION
	{
		MOTION_DEF = 0,			// �j���[�g�������[�V����
		MOTION_KNOCKBACK,		// �_���[�W���[�V����
		MOTION_FADEOUT,			// ���j���[�V����
		MOTION_ATK_MORTAR,		// �U�����[�V����(����)
		MOTION_READY_MORTAR,	// �������[�V����(����)
		MOTION_AFTER_MORTAR,	// �d�����[�V����(����)
		MOTION_ATK_BEAM,		// �U�����[�V����(�r�[��)
		MOTION_READY_BEAM,		// �������[�V����(�r�[��)
		MOTION_AFTER_BEAM,		// �d�����[�V����(�r�[��)
		MOTION_MAX
	};

	// �s����
	enum ACTION
	{
		ACTION_ROAMING = 0,	//�p�j�s��
		ACTION_READY,		//�����s��
		ACTION_ATTACK,		//�U���s��
		ACTION_AFTER,		//�U���d��
		ACTION_MAX
	};

	// �U����
	enum ATTACK
	{
		ATTACK_NONE = 0,	//�U���Ɩ��֌W
		ATTACK_BEAM= 0,		//�r�[��
		ATTACK_MORTAR,		//�����C
		ATTACK_MAX
	};

	// �����o�ϐ�
	ACTION m_Act;	//�s�����
	ATTACK m_Atk;	//�U�����
	float m_fActionCount;	// �ړ��J�E���^�[
	D3DXVECTOR3 m_moveLock;	//�Œ�ړ���
	float m_fRotLock;	//�����ۑ�

	// �����o�֐�
	void UpdateAction(void) override;	// �s���X�V
	void ActionSet(void); // �s���̐ݒ�
	void Move(void); // �ړ�
	void MoveRotation(void); // �ړ�����������
	void Attack(void); // �U��
	void RotationPlayer(void); // �v���C���[����������
	void SetMoveRotation(void); // ��������ړ��ʂ�ݒ肷�鏈��
	bool SearchPlayer(float fLen); // �v���C���[�Ƃ̋�������
	void FixRotation(void); // �w�����������
};

#endif
