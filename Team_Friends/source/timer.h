//=============================================================================
// 
//  �^�C�}�[�w�b�_�[ [timer.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _TIMER_H_
#define _TIMER_H_	// ��d�C���N���[�h�h�~

#include "main.h"

//==========================================================================
// �O���錾
//==========================================================================
class CMultiNumber;
class CObject2D;

//==========================================================================
// �N���X��`
//==========================================================================
// �^�C�}�[�N���X��`
class CTimer
{
public:

	enum eState
	{
		STATE_WAIT = 0,		// �ҋ@
		STATE_APPEARANCE,	// �o��
		STATE_ADD_LITTLE,	// �������Z
		STATE_ADJ,			// ����
		STATE_MAX
	};

	CTimer(int nPriority = 6);
	~CTimer();

	static CTimer *Create(void);
	static CTimer *Create(D3DXVECTOR3 pos);

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CTimer::eState GetState(void) { return m_state; }
	void SetState(eState state) { m_state = state; }

private:

	// �֐����X�g
	typedef void(CTimer::*STATE_FUNC)(void);
	static STATE_FUNC m_StateFuncList[];	// ��Ԋ֐����X�g

	// �����o�֐�
	void StateWait(void);
	void StatAppearance(void);
	void StatAddLittle(void);
	void StateAdjustment(void);

	// �����o�ϐ�
	eState m_state;					// ���
	float m_fStateTime;				// ��Ԏ���
	float m_fTime;					// ����
	D3DXVECTOR3 m_pos;				// �ʒu
	D3DXVECTOR3 m_posOrigin;		// ���̈ʒu
	CObject2D *m_pTimerWindow;		// �^�C�}�[�̃E�B���h�E
	CMultiNumber *m_pMinutes;		// ���̃I�u�W�F�N�g
	CMultiNumber *m_pSeconds;		// �b�̃I�u�W�F�N�g
	CMultiNumber *m_pMilliSeconds;	// �~���b�̃I�u�W�F�N�g
	bool m_bAddTime;	// �^�C�}�[���Z�̃t���O
};



#endif