//=============================================================================
// 
//  �^�C�g���̎a���w�b�_�[ [titleslash_endress.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _TITLESLASHENDRESS_H_
#define _TITLESLASHENDRESS_H_	// ��d�C���N���[�h�h�~

#include "main.h"
#include "object.h"

//==========================================================================
// �O���錾
//==========================================================================
class CObject2D;

//==========================================================================
// �}�N����`
//==========================================================================

//==========================================================================
// �N���X��`
//==========================================================================
// �^�C�g���̎a���N���X��`
class CTitleSlashEndress : public CObject
{
public:

	CTitleSlashEndress(int nPriority = 8);
	~CTitleSlashEndress();

	static CTitleSlashEndress *Create(void);

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	// �񋓌^��`
	enum VTX
	{
		VTX_LOGOALPHA1 = 0,		// �����ȃ��S
		VTX_LOGOALPHA2,			// �����ȃ��S
		VTX_LOGOPERFECTALPHA,	// �����ł̃��S
		VTX_LOGO_MAX
	};

	// �����o�֐�
	void UpdateLogo(int nCntSelect);	// ���S�̍X�V����
	void UpdateSlash();
	void UpdateSlashAlpha(int nCntSelect);

	// �����o�ϐ�
	int m_nLife;					// ����
	int m_nTexIdx[VTX_LOGO_MAX];						// �e�N�X�`���̃C���f�b�N�X�ԍ�
	D3DXVECTOR2 m_DestSize;		// �ڕW�̃T�C�Y
	CObject2D *m_pObj2D[VTX_LOGO_MAX];					// �I�u�W�F�N�g2D�̃I�u�W�F�N�g
	static const char *m_apTextureFile[VTX_LOGO_MAX];	// �e�N�X�`���̃t�@�C��
};



#endif