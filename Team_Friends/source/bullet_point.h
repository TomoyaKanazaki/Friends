//=============================================================================
// 
//  �e�̒��e�n�_ [bullet_point.h]
//  Author : ���c����
// 
//=============================================================================

#ifndef _BULLET_POINT_H_
#define _BULLET_POINT_H_	// ��d�C���N���[�h�h�~

#include "main.h"
#include "object3D.h"

//==========================================================================
// �N���X��`
//==========================================================================
class CBulletPoint : public CObject3D
{
public:
	CBulletPoint(int nPriority = 7);
	~CBulletPoint();

	static CBulletPoint *Create();
	static CBulletPoint *Create(D3DXVECTOR3 pos, float size = 100.0f);

	// �I�[�o�[���C�h���ꂽ�֐�����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static int GetNumAll(void);

private:

	CObject *m_pObject;		// �I�u�W�F�N�g�̃|�C���^
	static int m_nNumAll;	// ����
	int m_nTexIdx;			// �e�N�X�`���̃C���f�b�N�X�ԍ�
};

#endif