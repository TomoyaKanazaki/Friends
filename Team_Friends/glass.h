//==========================================
//
//  �Ђъ���|���S��(glass.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _GLASS_H_
#define _GLASS_H_
#include "object2D.h"

//==========================================
//  �N���X��`
//==========================================
class CGlass : public CObject2D
{
public:

	// �����o�֐�
	CGlass();
	~CGlass();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// �ÓI�����o�֐�
	static CGlass* Create();

};

#endif
