//==========================================================================
// 
//  �l���I�����j���[(decide_menu.h)
//  Author : ���{ ����
// 
//==========================================================================
#ifndef _DECIDE_MENU_H_
#define _DECIDE_MENU_H_
#include "object.h"

//==========================================================================
//  �O���錾
//==========================================================================
class CObject3D;
class CPlayerTitle;
class CDecideDoor;
class CNumber;

//==========================================================================
//  �N���X��`
//==========================================================================
class CDecideMenu : public CObject
{
public:

	// �񋓌^��`
	enum VTX
	{
		VTX_TEXT = 0,	// UI
		VTX_MAX
	};

	// �񋓌^��`
	enum VTX_UI
	{
		VTX_UI_ELECBORAD = 0,	// UI
		VTX_UI_MAX
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
	void Go(int nIdx); // �O�ɐi�ޏ���
	void Back(int nIdx); // ���ɉ����鏈��

	// �ÓI�����o�֐�
	static CDecideMenu* Create(void);
	static CPlayerTitle *GetPlayerTitle(int Cnt); // �v���C���[�̃|�C���^�z��

private:

	// �����o�֐�
	void UpdateSelect(int nCntSelect);	// �I�����̍X�V����
	void CreateSelect(void); // �I��Ώۂ̐���
	void CretePlayer(void); // �v���C���[�̐���
	void CreateNumber(void); // UI�̐���
	void CreateElecboard(void); // UI�̐���

	void SetValue(int nNowPlayer);

	// �����o�ϐ�
	int m_nCntAlpha;		// �s�����x�̃J�E���^�[
	int m_nNowSelect;		// ���݂̑I����
	int m_nTexIdx_Number;						// �e�N�X�`���̃C���f�b�N�X�ԍ�
	int m_nTexIdx_Elecborad[VTX_UI_MAX];		// �e�N�X�`���̃C���f�b�N�X�ԍ�
	int m_nTexIdx_Select;						// �e�N�X�`���̃C���f�b�N�X�ԍ�
	CNumber*m_pNumber3D[VTX_MAX];					// ������UI�̃I�u�W�F�N�g
	CObject3D*m_pElecboard3D[VTX_MAX];					// �d���f����UI�̃I�u�W�F�N�g
	CObject3D*m_pObj3D[VTX_MAX];					// �I�u�W�F�N�g2D�̃I�u�W�F�N�g
	CObjectX*m_pSelectX[VTXSELECT_MAX];				// �I�����̃I�u�W�F�N�g
	CDecideDoor *m_pDecideDoor;	// �h�A�̃I�u�W�F�N�g
	static CPlayerTitle *m_apPlayer[VTXSELECT_MAX]; // �v���C���[�̃|�C���^�z��
};

#endif
