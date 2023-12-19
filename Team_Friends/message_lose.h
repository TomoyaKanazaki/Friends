//==========================================
//
//  敗北メッセージ(message_lose.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MESSAGE_LOSE_H_
#define _MESSAGE_LOSE_H_
#include "result_message.h"

//==========================================
//  クラス定義
//==========================================
class CMessageLose : public CResultMessage
{
public:

	//メンバ関数
	CMessageLose();
	~CMessageLose();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
};

#endif
