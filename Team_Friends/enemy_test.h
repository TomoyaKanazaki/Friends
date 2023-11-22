//==========================================
//
//  �R�s�y�p�̓G(enemy_test.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_TEST_H_
#define _ENEMY_TEST_H_
#include "enemy.h"

//==========================================
//  �N���X��`
//==========================================
class CEnemyTest : public CEnemy
{
public:

	// �I�[�o�[���C�h���ꂽ�֐�
	CEnemyTest(int nPriority = mylib_const::ENEMY_PRIORITY);
	~CEnemyTest();

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
		ACTION_DEF = 0, //�ҋ@�s��
		ACTION_RETURN, //�A�ҍs��
		ACTION_ATTACK, //�U���s��
		ACTION_SEARCH, //���G�s��
		ACTION_CHASE, //�ǐՍs��
		MAX
	};

	// �����o�ϐ�
	ACTION m_Act; //�s�����
	D3DXVECTOR3 m_posDefault; //�����ʒu

	// �����o�֐�
	void ActionSet(void); // �s���̐ݒ�
	bool CalcLenDefault(void); //�����ʒu�ɖ߂鏈��
	void RotationPlayer(void); // �v���C���[����������
	bool CalcLenPlayer(float fLen); // �v���C���[�Ƃ̋�������

};

#endif
