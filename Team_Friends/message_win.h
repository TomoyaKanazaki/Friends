//==========================================
//
//  �������b�Z�[�W(message_win.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MESSAGE_WIN_H_
#define _MESSAGE_WIN_H_
#include "result_message.h"

//==========================================
//  �N���X��`
//==========================================
class CMessageWin : public CResultMessage
{
public:

	//�����o�֐�
	CMessageWin();
	~CMessageWin();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

};

#endif
