//=============================================================================
// 
//  �r���{�[�h�w�b�_�[ [objectBillboard.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _OBJECTBILLBOARD_H_
#define _OBJECTBILLBOARD_H_	// ��d�C���N���[�h�h�~

#include "main.h"
#include "object.h"
#include "constans.h"

//==========================================================================
// �N���X��`
//==========================================================================
// �r���{�[�h�N���X��`
class CObjectBillboard : public CObject
{
public:

	CObjectBillboard(int nPriority = 7);
	~CObjectBillboard();

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	virtual void SetVtx(void);
	void BindTexture(int nIdx);

	void SetWorldMtx(const D3DXMATRIX mtx);		// �}�g���b�N�X�ݒ�
	D3DXMATRIX GetWorldMtx(void) const;			// �}�g���b�N�X�擾
	void SetPosition(const D3DXVECTOR3 pos);	// �ʒu�ݒ�
	D3DXVECTOR3 GetPosition(void) const;		// �ʒu�擾
	void SetOldPosition(const D3DXVECTOR3 posOld);	// �O��̈ʒu�ݒ�
	D3DXVECTOR3 GetOldPosition(void) const;		// �O��̈ʒu�擾
	void SetRotation(const D3DXVECTOR3 rot);	// �����ݒ�
	D3DXVECTOR3 GetRotation(void) const;		// �����擾
	void SetMove(const D3DXVECTOR3 move);		// �ړ��ʐݒ�
	D3DXVECTOR3 GetMove(void) const;			// �ړ��ʎ擾
	void SetColor(const D3DXCOLOR col);			// �F�ݒ�
	D3DXCOLOR GetColor(void) const;				// �F�擾
	void SetSize(const D3DXVECTOR2 size);		// �T�C�Y�̐ݒ�
	D3DXVECTOR2 GetSize(void) const;			// �T�C�Y�̎擾
	void SetTex(D3DXVECTOR2 *tex);				// �e�N�X�`�����W�̐ݒ�
	D3DXVECTOR2 *GetTex(void);					// �e�N�X�`�����W�̎擾

	static CObjectBillboard *Create();
	static CObjectBillboard *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	CObjectBillboard *GetObjectBillBoard(void);
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) const;
protected:

private:
	D3DXMATRIX	m_mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_posOld;	// �O��̈ʒu
	D3DXVECTOR3 m_move;		// �ړ���
	D3DXVECTOR3 m_rot;		// ����
	D3DXCOLOR m_col;		// �F
	D3DXVECTOR2 m_fSize;	// �T�C�Y
	D3DXVECTOR2 m_fTex[32];	// �e�N�X�`�����W
	int m_nTexIdx;			// �e�N�X�`���̃C���f�b�N�X�ԍ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@
};



#endif