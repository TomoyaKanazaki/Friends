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

};

#endif
