//==========================================
//
//  �ˌ��G(enemy_tackle.h)
//  Author : Kai Takada
//
//==========================================
#ifndef _ENEMY_TACKLE_H_
#define _ENEMY_TACKLE_H_
#include "enemy.h"

//==========================================
//  �N���X��`
//==========================================
class CEnemyTackle : public CEnemy
{
public:

	// �I�[�o�[���C�h���ꂽ�֐�
	CEnemyTackle(int nPriority = mylib_const::ENEMY_PRIORITY);
	~CEnemyTackle();

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
		MOTION_READY,		// �������[�V����
		MOTION_AFTER,		// �d�����[�V����
		MOTION_MAX
	};

	// �s����
	enum ACTION
	{
		ACTION_ROAMING = 0,	//�p�j�s��
		ACTION_READY,		//�����s��
		ACTION_ATTACK,		//�U���s��
		ACTION_AFTER,		//�U���d��
		MAX
	};

	// �����o�ϐ�
	ACTION m_Act;			// �s�����
	float m_fActionCount;	// �ړ��J�E���^�[
	D3DXVECTOR3 m_moveLock;	// �Œ�ړ���
	float m_fRotLock;		// �����ۑ�
	float m_fEmissionTime;	// �������̃^�C�}�[
	int m_nAttack;			// �U����

	// �����o�֐�
	void MotionSet(void) override;		// ���[�V�����̐ݒ�
	void UpdateAction(void) override;	// �s���X�V
	void ActionSet(void) override; // �s���̐ݒ�
	void Attack(void); // �U��
	void SetMoveRotation(void); // ��������ړ��ʂ�ݒ肷�鏈��
	bool SearchPlayer(float fLen); // �v���C���[�Ƃ̋�������
	void FixRotation(void); // �w�����������
	void Roaming(void); // �p�j
	void RotationPlayer(void) override;		// �v���C���[����������

};

#endif
