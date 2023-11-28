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
//  �N���X��`
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
	void MotionSet(void) override;		// ���[�V�����̐ݒ�

	// �����o�֐�
	void SetDefaultPos(const D3DXVECTOR3 pos);

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
	D3DXVECTOR3 m_posDefault; //�����ʒu
	float m_fMoveCount; // �ړ��J�E���^�[

	// �����o�֐�
	void ActionSet(void); // �s���̐ݒ�
	void Move(void); // �ړ�
	void MoveRotation(void); // �ړ�����������
	void Attack(void); // �U��
	void RotationPlayer(void); // �v���C���[����������
	bool CalcLenPlayer(float fLen); // �v���C���[�Ƃ̋�������

};

#endif
