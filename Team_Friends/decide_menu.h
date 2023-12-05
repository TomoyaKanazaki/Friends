//==========================================
// 
//  �l���I�����j���[(decide_menu.h)
//  Author : Tomoya Kanazaki
// 
//==========================================
#ifndef _DECIDE_MENU_H_
#define _DECIDE_MENU_H_
#include "object.h"

//==========================================
//  �O���錾
//==========================================
class CObject3D;

//==========================================
//  �N���X��`
//==========================================
class CDecideMenu : public CObject
{
public:

	// �񋓌^��`
	enum VTX
	{
		VTX_TEXT = 0,	// UI
		VTX_WALL, // ��
		VTX_MAX
	};

	// �񋓌^��`
	enum VTXSELECT
	{
		VTXSELECT_SELECT1P = 0,	// 1P
		VTXSELECT_SELECT2P,		// 2P
		VTXSELECT_SELECT3P,		// 3P
		VTXSELECT_SELECT4P,		// 4P
		VTXSELECT_MAX
	};

	// �����o�֐�
	CDecideMenu(int nPriority = 8);
	~CDecideMenu();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CDecideMenu* Create(void);

private:

	// �����o�֐�
	void UpdateSelect(int nCntSelect);	// �I�����̍X�V����
	void CreateUI(void); // UI�̐���
	void CreateSelect(void); // �I��Ώۂ̐���

	// �����o�ϐ�
	int m_nCntAlpha;		// �s�����x�̃J�E���^�[
	int m_nNowSelect;		// ���݂̑I����
	int m_nTexIdx[VTX_MAX];						// �e�N�X�`���̃C���f�b�N�X�ԍ�
	int m_nTexIdx_Select[VTXSELECT_MAX];						// �e�N�X�`���̃C���f�b�N�X�ԍ�
	CObject3D*m_pObj3D[VTX_MAX];					// �I�u�W�F�N�g2D�̃I�u�W�F�N�g
	CObject3D*m_pSelect3D[VTXSELECT_MAX];				// �I�����̃I�u�W�F�N�g
};

#endif
