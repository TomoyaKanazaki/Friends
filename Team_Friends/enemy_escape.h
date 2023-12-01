//==========================================
//
//  ���^���X���C��(enemy_escape.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_ESCAPE_H_
#define _ENEMY_ESCAPE_H_
#include "enemy.h"

//==========================================
//  �N���X��`
//==========================================
class CEnemyEscape : public CEnemy
{
public:

	// �I�[�o�[���C�h���ꂽ�֐�
	CEnemyEscape(int nPriority = mylib_const::ENEMY_PRIORITY);
	~CEnemyEscape();

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
		ACTION_ROAMING = 0, // �p�j�s��
		ACTION_FIND, // �����s��
		ACTION_ESCAPE, // �����s��
		ACTION_FADE, // ���ōs��
		MAX
	};

	// �����o�ϐ�
	ACTION m_Act; //�s�����
	float m_fMoveCount; // �ړ��J�E���^�[
	float m_fCntFind; // �����J�E���^�[
	float m_fCntEscape; // �����J�E���^�[

	// �����o�֐�
	void UpdateAction(void) override;	// �s���X�V
	void ActionSet(void); // �s���̐ݒ�
	void Move(void); // �ړ�
	void Escape(void); // ����
	void MoveRotation(void); // �ړ�����������
	void RotationPlayer(void); // �v���C���[����������
	bool CalcLenPlayer(float fLen); // �v���C���[�Ƃ̋�������
};

#endif
