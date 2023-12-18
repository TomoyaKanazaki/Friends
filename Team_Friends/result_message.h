//==========================================
//
//  ���U���g���b�Z�[�W(result_message.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _RESULT_MESSAGE_H_
#define _RESULT_MESSAGE_H_
#include "logo.h"

//==========================================
//  �N���X��`
//==========================================
class CResultMessage : public CLogo
{
public:

	//�����o�֐�
	CResultMessage();
	~CResultMessage();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CResultMessage* Create(bool bClear);

private:

};

#endif
