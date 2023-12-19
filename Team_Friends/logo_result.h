//==========================================
//
//  リザルトロゴ(logo_result.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _LOGO_RESULT_H_
#define _LOGO_RESULT_H_
#include "logo.h"

//==========================================
//  クラス定義
//==========================================
class CLogoResult : public CLogo
{
public:

	//メンバ関数
	CLogoResult();
	~CLogoResult();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CLogoResult* Create(void);

private:

};

#endif
