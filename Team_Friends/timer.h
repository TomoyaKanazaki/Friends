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

//==========================================================================
// �N���X��`
//==========================================================================
// �^�C�}�[�N���X��`
class CTimer
{
public:

	CTimer(int nPriority = 6);
	~CTimer();

	static CTimer *Create(void);
	static CTimer *Create(D3DXVECTOR3 pos);

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Add(int nValue);

private:

	float m_fTime;					// ����
	CMultiNumber *m_pMinutes;		// ���̃I�u�W�F�N�g
	CMultiNumber *m_pSeconds;		// �b�̃I�u�W�F�N�g
	CMultiNumber *m_pMilliSeconds;	// �~���b�̃I�u�W�F�N�g
};



#endif