//==========================================
// 
//  �l���I�����j���[(decide_menu.h)
//  Author : ���{ ����
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

	void SetSelect(int nSelect);	// �I�����ݒ�

	// �ÓI�����o�֐�
	static CDecideDoor* Create(void);

private:

	// �����o�ϐ�
	int m_nNowSelect;				// ���݂̑I����
	int m_nOldSelect;				// �ЂƂO�̑I����
	int m_n[MODELSELECT_MAX];		// �Q�[�g�̊J�P�\�J�E���g
	float m_nGate[MODELSELECT_MAX];					// �Q�[�g�̊J�J�E���g
	CObjectX *m_pObjX[VTX_MAX];						// �I�u�W�F�N�g2D�̃I�u�W�F�N�g
	CObjectX *m_pSelectX[MODELSELECT_MAX];			// �I�����̃I�u�W�F�N�g
};

#endif
