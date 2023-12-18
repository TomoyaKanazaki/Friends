//=============================================================================
// 
//  �x��w�b�_�[ [emergency.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _EMERGENCY_H_
#define _EMERGENCY_H_	// ��d�C���N���[�h�h�~

#include "object.h"

//==========================================================================
// �O���錾
//==========================================================================
class CMultiNumber;

//==========================================================================
// �N���X��`
//==========================================================================
// �x��N���X��`
class CEmergency : public CObject
{
public:

	CEmergency(int nPriority = 7);
	~CEmergency();

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEmergency *Create(void);
private:

	// ��ԗ�
	enum eState
	{
		STATE_EMERGENCY = 0,	// �x��
		STATE_WINDOW,			// �E�B���h�E
		STATE_MISSION,			// �~�b�V����
		STATE_END,
		STATE_MAX
	};
	
	// �֐����X�g
	typedef void(CEmergency::*STATE_FUNC)(void);
	static STATE_FUNC m_StateFuncList[];	// ��Ԋ֐����X�g

	// �����o�֐�
	void UpdateEmergency(void);	// �x��̍X�V
	void UpdateWindow(void);	// �E�B���h�E�̍X�V
	void UpdateMission(void);	// �~�b�V�����̍X�V
	void UpdateEnd(void);		// �I��

	// �����o�ϐ�
	eState m_satate;	// ���
	bool m_bEndEmergency;			// �x�񂪏I�������
	float m_fTime;					// �x�񎞊�
	CObject2D *m_pEmergencyFlash;	// �x�񎞓_��
	CObject2D *m_pEmergencyText;	// �x��e�L�X�g
	CObject2D *m_pMissionText;		// �~�b�V�����e�L�X�g
	CObject2D *m_pWindow;			// �E�B���h�E
	CObject2D *m_pWarningFrame[2];	// �x���̃t���[��
};



#endif