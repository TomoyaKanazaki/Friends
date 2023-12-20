//=============================================================================
// 
//  ����(3D)�w�b�_�[ [number_3D.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _NUMBER_3D_H_
#define _NUMBER_3D_H_	// ��d�C���N���[�h�h�~

#include "number.h"
#include "object3D.h"

//==========================================================================
// �O���錾
//==========================================================================
class CObject3D;

//==========================================================================
// �N���X��`
//==========================================================================
// �w�i�N���X��`
class CNumber3D : public CNumber
{
public:

	CNumber3D(int nPriority = 6);
	~CNumber3D();

	// �����o�֐�
	HRESULT Init(int nPriority) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;	// �J������

	void SetPosition(const D3DXVECTOR3 pos) override;	// �ʒu�ݒ�
	D3DXVECTOR3 GetPosition(void) const override;		// �ʒu�擾
	void SetMove(const D3DXVECTOR3 move) override;		// �ړ��ʐݒ�
	D3DXVECTOR3 GetMove(void) const override;			// �ړ��ʎ擾
	void SetRotation(const D3DXVECTOR3 rot) override;	// �����ݒ�
	D3DXVECTOR3 GetRotation(void) const override;		// �����擾

	void SetColor(const D3DXCOLOR col) override;			// �F�ݒ�
	D3DXCOLOR GetColor(void) const override;				// �F�擾
	void SetSize3D(const D3DXVECTOR3 size) override;		// �T�C�Y�̐ݒ�
	D3DXVECTOR3 GetSize3D(void) const override;			// �T�C�Y�̎擾
	void SetTex(D3DXVECTOR2 *tex) override;				// �e�N�X�`�����W�̐ݒ�
	D3DXVECTOR2 *GetTex(void) override;					// �e�N�X�`�����W�̎擾

	void SetVtx(void) override;
	void BindTexture(int nIdx) override;
	void SetType(const CObject::TYPE type) override;
	CObject3D *GetObject3D(void) override;

private:
	CObject3D *m_aObject3D;				// �I�u�W�F�N�g3D�̃I�u�W�F�N�g
	bool m_bAddAlpha;
};

#endif