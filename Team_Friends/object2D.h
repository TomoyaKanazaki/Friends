//=============================================================================
// 
//  �I�u�W�F�N�g2D�w�b�_�[ [object2D.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_	// ��d�C���N���[�h�h�~

#include "main.h"
#include "object.h"

class CEnemy;

//==========================================================================
// �N���X��`
//==========================================================================
// �I�u�W�F�N�g2D�N���X��`
class CObject2D : public CObject
{
public:

	CObject2D(int nPriority = mylib_const::DEF2D_PRIORITY);
	~CObject2D();

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void);
	HRESULT Init(int nNumVertex);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Draw(int nNumVertex);
	virtual void SetVtx(void);
	virtual void SetVtx(int nNumVertex);
	void BindTexture(int nIdx);

	void SetColor(const D3DXCOLOR col);			// �F�ݒ�
	D3DXCOLOR GetColor(void) const;				// �F�擾
	void SetSize(const D3DXVECTOR2 size);		// �T�C�Y�̐ݒ�
	D3DXVECTOR2 GetSize(void) const;			// �T�C�Y�̎擾
	void SetTex(D3DXVECTOR2 *tex);				// �e�N�X�`�����W�̐ݒ�
	D3DXVECTOR2 *GetTex(void);					// �e�N�X�`�����W�̎擾
	void SetLength(const float fLength);		// �Ίp���̒����ݒ�
	float GetLength(void) const;				// �Ίp���̒����擾
	void SetAngle(const float fAngle);			// �Ίp���̌����ݒ�
	float GetAngle(void) const;					// �Ίp���̌����擾
	D3DXVECTOR3 *GetVtxPos(void);				// ���_���W�擾
	void SetVtxPos(D3DXVECTOR3 *pos);			// ���_���W�擾
	
	template<class T>T *GetTemplate(void);

	static CObject2D *Create();
	static CObject2D *Create(int nPriority);
	static CObject2D *Create(int nPriority, int nNumVtx);
	CObject2D *GetObject2D(void);
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) const;
protected:

private:
	D3DXCOLOR m_col;		// �F
	D3DXVECTOR2 m_fSize;	// �T�C�Y
	D3DXVECTOR2 m_fTex[32];		// �e�N�X�`�����W
	float m_fLength;		// �Ίp���̒���
	float m_fAngle;			// �Ίp���̌���
	D3DXVECTOR3 m_VtxPos[32];		// ���_���W
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@
	int m_nTexIdx;					// �e�N�X�`���̃C���f�b�N�X�ԍ�
};

#endif