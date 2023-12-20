//==========================================
//
//  �s�k���b�Z�[�W(message_lose.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MESSAGE_LOSE_H_
#define _MESSAGE_LOSE_H_
#include "object3D.h"

//==========================================
//  �N���X��`
//==========================================
class CMessageLose : public CObject3D
{
public:

	//�����o�֐�
	CMessageLose();
	~CMessageLose();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// �ÓI�����o�֐�
	static CMessageLose* Create();

private:

	// �����o�֐�
	void Move(); //�ړ�

	// �����o�ϐ�
	float m_fSec; // �o�ߎ���
	bool m_bMove; // �ړ������t���O

};

#endif
