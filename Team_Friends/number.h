//=============================================================================
// 
//  �����w�b�_�[ [number.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _NUMBER_H_
#define _NUMBER_H_	// ��d�C���N���[�h�h�~

#include "main.h"
#include "object2D.h"

//==========================================================================
// �O���錾
//==========================================================================
class CObject2D;
class CObjectBillboard;

//==========================================================================
// �N���X��`
//==========================================================================
// �w�i�N���X��`
class CNumber
{
public:

	// �񋓌^��`
	enum EObjectType
	{
		OBJECTTYPE_2D = 0,		// 2D
		OBJECTTYPE_BILLBOARD,	// �r���{�[�h
		OBJECTTYPE_MAX
	};

	CNumber(int nPriority = 6);
	~CNumber();

	static CNumber *Create(EObjectType objtype);

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Release(void);	// �J������
	CObject2D *GetMyObject(void);
	CObjectBillboard *GetMyObjectBillboard(void);

private:
	EObjectType m_objType;				// �I�u�W�F�N�g�̎��
	CObject2D *m_aObject2D;				// �I�u�W�F�N�g2D�̃I�u�W�F�N�g
	CObjectBillboard *m_pObjBillboard;	// �I�u�W�F�N�g�r���{�[�h�̃I�u�W�F�N�g
};

#endif