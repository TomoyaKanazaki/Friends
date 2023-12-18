//==========================================
// 
//  �l���I�����j���[(decide_menu.h)
//  Author : Tomoya Kanazaki
// 
//==========================================
#ifndef _DECIDE_DOOR_H_
#define _DECIDE_DOOR_H_
#include "object.h"

//==========================================
//  �O���錾
//==========================================
class CObject3D;
class CPlayerTitle;

//==========================================
//  �N���X��`
//==========================================
class CDecideDoor : public CObject
{
public:

	// �񋓌^��`
	enum MODEL
	{
		VTX_FREAM = 0,	// �g
		VTX_MAX
	};

	// �񋓌^��`
	enum MODELSELECT
	{
		MODELSELECT_DOOR_1 = 0,	// 1P
		MODELSELECT_DOOR_2,		// 2P
		MODELSELECT_DOOR_3,		// 3P
		MODELSELECT_DOOR_4,		// 4P
		MODELSELECT_MAX
	};

	// �����o�֐�
	CDecideDoor(int nPriority = 8);
	~CDecideDoor();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

						 // �ÓI�����o�֐�
	static CDecideDoor* Create(void);

private:

	// �����o�֐�
	void UpdateSelect(int nCntSelect);	// �I�����̍X�V����
	void CreateSelect(void); // �I��Ώۂ̐���

							// �����o�ϐ�
	int m_nNowSelect;		// ���݂̑I����
	int m_nTexIdx_Select[MODELSELECT_MAX];						// �e�N�X�`���̃C���f�b�N�X�ԍ�
	CObjectX *m_pObjX[VTX_MAX];							// �I�u�W�F�N�g2D�̃I�u�W�F�N�g
	CObjectX *m_pSelectX[MODELSELECT_MAX];				// �I�����̃I�u�W�F�N�g
};

#endif
