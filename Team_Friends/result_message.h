//==========================================
//
//  リザルトメッセージ(result_message.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _RESULT_MESSAGE_H_
#define _RESULT_MESSAGE_H_
#include "logo.h"

//==========================================
//  クラス定義
//==========================================
class CResultMessage : public CLogo
{
public:

	//メンバ関数
	CResultMessage();
	~CResultMessage();

	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

	//静的メンバ関数
	static CResultMessage* Create(bool bClear);

private:

};

#endif
