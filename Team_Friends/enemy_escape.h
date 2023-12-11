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
		ACTION_TURN, // ��������s��
		ACTION_ESCAPE, // �����s��
		ACTION_FADE, // ���ōs��
		MAX
	};

	// �����o�ϐ�
	ACTION m_Act; //�s�����
	float m_fCntWalk; // �����]��
	float m_fCntFind; // �����J�E���^�[
	float m_fCntEscape; // �����J�E���^�[
	float m_fRot; // ���������Ƃ��`

	// �����o�֐�
	void MotionSet(void) override;		// ���[�V�����̐ݒ�
	void UpdateAction(void) override;	// �s���X�V
	void Move(void) override; // �ړ�
	void RotationPlayer(void) override; // �v���C���[������
	void RandTurn(void); // �����_���ȕ����]��
	void Turn(void); // ��������
	void ActionSet(void); // �s���̐ݒ�
	void Escape(void); // ����

	// �����o�ϐ�
	D3DXVECTOR3 m_rotParts;	// �p�[�c��]�p

};

#endif
