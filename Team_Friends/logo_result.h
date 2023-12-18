//==========================================
//
//  ���U���g���S(logo_result.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _LOGO_RESULT_H_
#define _LOGO_RESULT_H_
#include "logo.h"

//==========================================
//  �N���X��`
//==========================================
class CLogoResult : public CLogo
{
public:

	//�����o�֐�
	CLogoResult();
	~CLogoResult();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CLogoResult* Create(void);

private:

};

#endif
