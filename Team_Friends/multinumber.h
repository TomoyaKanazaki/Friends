//=============================================================================
// 
//  �����w�b�_�[ [multinumber.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _MULTINUMBER_H_
#define _MULTINUMBER_H_	// ��d�C���N���[�h�h�~

#include "main.h"
#include "object2D.h"
#include "number.h"

//==========================================================================
// �O���錾
//==========================================================================
class CNumber;

//==========================================================================
// �N���X��`
//==========================================================================
// �w�i�N���X��`
class CMultiNumber
{
public:

	// �񂹎��
	enum AlignmentType
	{
		ALIGNMENT_RIGHT = 0,	// �E��
		ALIGNMENT_MAX
	};

	CMultiNumber(int nPriority = 8);
	~CMultiNumber();

	static CMultiNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nNum, CNumber::EObjectType objtype, bool bDigitDraw = false, int nPriority = 8);
	static CMultiNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nNum, CNumber::EObjectType objtype, const char *pTextureFile, bool bDigitDraw = false, int nPriority = 8);

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void AddNumber(int nValue);
	void SetValue(void);		// �l�̐ݒ菈��
	void SetValue(int nValue);	// �l�̐ݒ菈��(�I�[�o�[���[�h)
	int GetValue(void);			// �l�̎擾����
	void SetPosition(const D3DXVECTOR3 pos);	// �ʒu�ݒ�
	D3DXVECTOR3 GetPosition(void) const;		// �ʒu�擾
	void SetOriginPosition(const D3DXVECTOR3 pos);	// �ʒu�ݒ�
	D3DXVECTOR3 GetOriginPosition(void) const;		// �ʒu�擾
	void SetRotation(const D3DXVECTOR3 pos);	// �ʒu�ݒ�
	D3DXVECTOR3 GetRotation(void) const;		// �ʒu�擾
	void SetColor(const D3DXCOLOR col);			// �F�ݒ�
	D3DXCOLOR GetColor(void) const;				// �F�擾
	void Release(void);	// �J������
	void SetSize(const D3DXVECTOR2 size);		// �T�C�Y�ݒ�
	D3DXVECTOR2 GetSize(void) const;			// �T�C�Y�擾
	void SetSizeOrigin(const D3DXVECTOR2 size);		// �T�C�Y�ݒ�
	D3DXVECTOR2 GetSizeOrigin(void) const;			// �T�C�Y�擾

private:

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;				// �ʒu
	D3DXVECTOR3 m_posOrigin;				// �ʒu
	D3DXVECTOR3 m_rot;				// ����
	D3DXCOLOR m_col;				// �F
	D3DXVECTOR2 m_size;				// �����̃T�C�Y
	D3DXVECTOR2 m_sizeOrigin;				// �����̃T�C�Y
	int m_nNum;						// ����
	int m_nNumNumber;				// �����̐�
	int m_nTexIdx;					// �e�N�X�`���̃C���f�b�N�X�ԍ�
	int m_nPriority;				// �D�揇��
	bool m_bDigitDraw;				// �����`��
	CNumber **m_ppMultiNumber;		// �����̃I�u�W�F�N�g
	CNumber::EObjectType m_objType;	// �I�u�W�F�N�g�̎��

};

#endif