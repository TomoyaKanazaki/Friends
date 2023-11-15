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
//  前方宣言
//==========================================
class CLogo_Mech;
class CLogo_Meka;
class CLogo_Sqou;
class CLogo_Comp;

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

	//メンバ変数
	CLogo_Mech* m_pMech;
	CLogo_Meka* m_pMeka;
	CLogo_Sqou* m_pSqou;
	CLogo_Comp* m_pComp;

};

#endif
