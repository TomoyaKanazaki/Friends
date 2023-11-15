//=============================================================================
// 
// �^�C�g���a������ [titleslash.h]
// Author : ���n�Ή�
// 
//=============================================================================

#ifndef _TITLESLASH_H_
#define _TITLESLASH_H_		// ��d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"
#include "object2D.h"

//==========================================================================
// �N���X��`
//==========================================================================
// �^�C�g���a���N���X��`
class CTitleSlash : public CObject2D
{
public:

	CTitleSlash(int nPriority = 8);
	~CTitleSlash();

	static CTitleSlash *Create(const D3DXVECTOR3 pos);
	
	//  �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetVtx(void);

private:

	float m_fMaxWidth;		// �ő�̉���
	int m_nLife;			// ����
	int m_nMaxLife;			// �ő����(�Œ�)
	int m_nTexIdx;			// �e�N�X�`���̃C���f�b�N�X�ԍ�
};

#endif