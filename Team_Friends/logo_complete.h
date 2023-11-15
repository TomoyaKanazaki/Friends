//==========================================
//
//  �������S(logo_complete.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _LOGO_COMPLETE_H_
#define _LOGO_COMPLETE_H_
#include "object3D.h"

//==========================================
//  �N���X��`
//==========================================
class CLogo_Comp : public CObject3D
{
public:

	//�����o�֐�
	CLogo_Comp();
	~CLogo_Comp();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CLogo_Comp* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

	//�ÓI�����o�ϐ�
	static const char* m_pTextureFile; //�e�N�X�`���̃t�@�C��
};

#endif
