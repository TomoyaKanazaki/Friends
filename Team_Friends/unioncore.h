//=============================================================================
// 
//  ���̂̃R�A�w�b�_�[ [unioncore.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _UNIONCORE_H_
#define _UNIONCORE_H_	// ��d�C���N���[�h�h�~

#include "objectX.h"

//==========================================================================
// �N���X��`
//==========================================================================
// ���̂̃R�A�N���X��`
class CUnionCore : public CObjectX
{
public:

	CUnionCore(int nPriority = 6);
	~CUnionCore();

	// �I�[�o�[���C�h���ꂽ�֐�
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void SetUp(D3DXVECTOR3 setup, D3DXMATRIX *pMtxParent);
	static CUnionCore *Create(const D3DXVECTOR3 pos);

private:
	
	int m_nCntEmission;			// �������̃J�E���^�[
	D3DXVECTOR3 m_setupPosition;	// �Z�b�g�A�b�v�ʒu
	D3DXMATRIX *m_pMtxParent;	// �e�}�g���b�N�X�̃|�C���^
	bool m_bSetUp;				// �Z�b�g�A�b�v����
};


#endif