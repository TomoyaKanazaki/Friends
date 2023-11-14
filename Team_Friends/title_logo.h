//==========================================
//
//  タイトルロゴ管理クラス(title_logo.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TITLE_LOGO_H_
#define _TITLE_LOGO_H_
#include "object.h"

//==========================================
//  クラス定義
//==========================================
class CTitleLogo : public CObject
{
public:

	//メンバ関数
	CTitleLogo();
	~CTitleLogo();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CTitleLogo* Create();

private:

};

#endif
