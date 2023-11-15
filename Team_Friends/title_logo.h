//==========================================
//
//  �^�C�g�����S�Ǘ��N���X(title_logo.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TITLE_LOGO_H_
#define _TITLE_LOGO_H_
#include "object.h"

//==========================================
//  �O���錾
//==========================================
class CLogo_Mech;
class CLogo_Meka;
class CLogo_Sqou;
class CLogo_Comp;

//==========================================
//  �N���X��`
//==========================================
class CTitleLogo : public CObject
{
public:

	//�����o�֐�
	CTitleLogo();
	~CTitleLogo();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CTitleLogo* Create();

private:

	//�����o�ϐ�
	CLogo_Mech* m_pMech;
	CLogo_Meka* m_pMeka;
	CLogo_Sqou* m_pSqou;
	CLogo_Comp* m_pComp;

};

#endif
