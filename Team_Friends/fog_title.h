//==========================================
//
//  �^�C�g���ł̃t�H�O�̏���(fog_title.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _FOG_TITLE_H_
#define _FOG_TITLE_H_
#include "object.h"

//==========================================
//  �N���X��`
//==========================================
class CFog_Title : public CObject
{
public:

	//�����o�ϐ�
	CFog_Title();
	~CFog_Title();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	//�ÓI�����o�֐�
	static CFog_Title* Create();

private:

	// �����o�ϐ�
	D3DXCOLOR m_col;
	float m_fLength;

};

#endif
