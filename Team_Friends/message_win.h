//==========================================
//
//  勝利メッセージ(message_win.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MESSAGE_WIN_H_
#define _MESSAGE_WIN_H_
#include "result_message.h"

//==========================================
//  クラス定義
//==========================================
class CMessageWin : public CResultMessage
{
public:

	//メンバ関数
	CMessageWin();
	~CMessageWin();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

};

#endif
