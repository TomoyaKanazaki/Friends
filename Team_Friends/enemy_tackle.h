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
	void MotionSet(void) override;		// ���[�V�����̐ݒ�

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
		ACTION_FIND, //�����s��
		ACTION_ATTACK, //�U���s��
		ACTION_AFTER, //�U���d��
		MAX
	};

	// �����o�ϐ�
	ACTION m_Act; //�s�����
	float m_fMoveCount; // �ړ��J�E���^�[
	float m_fAfterCount; // �d���J�E���^�[

	// �����o�֐�
	void ActionSet(void); // �s���̐ݒ�
	void Move(void); // �ړ�
	void MoveRotation(void); // �ړ�����������
	void Attack(void); // �U��
	void RotationPlayer(void); // �v���C���[����������
	bool CalcLenPlayer(float fLen); // �v���C���[�Ƃ̋�������

};

#endif
