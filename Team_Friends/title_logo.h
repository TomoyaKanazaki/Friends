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

	// ���S�̍X�V��ԗ�
	enum STATE
	{
		DEFAULT = 0, //�A���t�@�x�b�g�݂̂�������
		WAKE, //�J�^�J�i���N���オ��
		FLASH, //������_�ł���
		COMPLETE, //�����I�I
		STARTUP, // �N��
		MAX, //����
		NONE //NULLLLLLLLL
	};

	//�����o�֐�
	CTitleLogo();
	~CTitleLogo();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	bool GetComplete() { return m_bComplete; }

	void SetState(STATE state);	// ��Ԑݒ�

	//�ÓI�����o�֐�
	static CTitleLogo* Create();

private:

	//�����o�ϐ�
	CLogo_Mech* m_pMech;
	CLogo_Meka* m_pMeka;
	CLogo_Sqou* m_pSqou;
	CLogo_Comp* m_pComp;
	STATE m_State;
	bool m_bComplete;

	//�����o�֐�
	void UpdateState();

};

#endif
