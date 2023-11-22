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

	enum eMyTag
	{
		TAG_NONE = 0,	// �Ȃ�
		TAG_PLAYER ,	// �v���C���[
		TAG_ENEMY,		// �G
		TAG_MAX
	};

	CCollisionObject(int nPriority = 5);
	~CCollisionObject();

	static CCollisionObject *Create(void);
	static CCollisionObject *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fRadius, const int nLife, const int nDamage, eMyTag tag);

	//  �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	// �����o�֐�
	void CollisionEnemy(void);	// �G�Ƃ̓����蔻��
	void CollisionPlayer(void);	// �v���C���[�Ƃ̓����蔻��

	// �����o�ϐ�
	float m_fRadius;		// ���a
	int m_nDamage;			// �_���[�W
	int m_nLife;			// ����
	int m_nMaxLife;			// �ő����(�Œ�)
	eMyTag m_MyTag;			// �����̃^�O
	static int m_nIdxTex;	// �e�N�X�`���̃C���f�b�N�X�ԍ�
};

#endif