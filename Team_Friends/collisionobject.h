//=============================================================================
// 
// �����蔻��I�u�W�F�N�g���� [collisionobject.h]
// Author : ���n�Ή�
// 
//=============================================================================

#ifndef _COLLISIONOBJECT_H_
#define _COLLISIONOBJECT_H_		// ��d�C���N���[�h�h�~�̃}�N�����`����

#include "objectBillboard.h"

//==========================================================================
// �N���X��`
//==========================================================================
// �����蔻��I�u�W�F�N�g�N���X��`
class CCollisionObject : public CObjectBillboard
{
public:

	CCollisionObject(int nPriority = 5);
	~CCollisionObject();

	static CCollisionObject *Create(void);
	static CCollisionObject *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fRadius, const int nLife);

	//  �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetVtx(void);

	static int GetNumAll(void);	// �����擾

private:

	// �����o�ϐ�
	float m_fRadius;		// ���a
	int m_nLife;			// ����
	int m_nMaxLife;			// �ő����(�Œ�)
	int m_nParentIdx;		// �e�̃C���f�b�N�X�ԍ�
};

#endif