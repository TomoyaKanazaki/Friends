//==========================================
//
//  ����̃��S(logo_squadron.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SQUADRON_H_
#define _SQUADRON_H_
#include "object3D.h"

//==========================================
//  �N���X��`
//==========================================
class CLogo_Sqou : public CObject3D
{
public:

	//�����o�֐�
	CLogo_Sqou();
	~CLogo_Sqou();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CLogo_Sqou* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

	//�ÓI�����o�ϐ�
	static const char* m_pTextureFile; //�e�N�X�`���̃t�@�C��
};

#endif
