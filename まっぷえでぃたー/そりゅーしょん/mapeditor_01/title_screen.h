//=============================================================================
// 
//  �^�C�g����ʃw�b�_�[ [title_screen.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _TITLESCREEN_H_
#define _TITLESCREEN_H_	// ��d�C���N���[�h�h�~

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
// �w�i�N���X��`
class CTitleScreen : public CObject
{
public:

	CTitleScreen(int nPriority = 8);
	~CTitleScreen();

	static CTitleScreen *Create(void);

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	// �񋓌^��`
	enum VTX
	{
		VTX_BLACK = 0,	// ��
		VTX_LOGO,		// �^�C�g�����S
		VTX_LOGOALPHA1,		// �����ȃ��S
		VTX_LOGOALPHA2,		// �����ȃ��S
		VTX_LOGOPERFECT,	// �����ł̃��S
		VTX_LOGOPERFECTALPHA,	// �����ł̃��S
		VTX_LOGO_MAX
	};

	// �񋓌^��`
	enum VTXSELECT
	{
		VTXSELECT_SELECTSTART = 0,		// �X�^�[�g
		VTXSELECT_MAX
	};

	// �����o�֐�
	void UpdateLogo(int nCntSelect);	// ���S�̍X�V����
	void UpdateSelect(int nCntSelect);	// �I�����̍X�V����
	void UpdateSlash();
	void UpdateSlashAlpha(int nCntSelect);

	// �����o�ϐ�
	int m_nCntAlpha;		// �s�����x�̃J�E���^�[
	int m_nCntLogo;		// ���S�ړ��̃J�E���g
	int m_nTexIdx[VTX_LOGO_MAX];						// �e�N�X�`���̃C���f�b�N�X�ԍ�
	int m_nTexIdx_Select[VTXSELECT_MAX];						// �e�N�X�`���̃C���f�b�N�X�ԍ�
	CObject2D *m_pObj2D[VTX_LOGO_MAX];					// �I�u�W�F�N�g2D�̃I�u�W�F�N�g
	CObject2D *m_pSelect2D[VTXSELECT_MAX];				// �I�����̃I�u�W�F�N�g
	static const char *m_apTextureFile[VTX_LOGO_MAX];	// �e�N�X�`���̃t�@�C��
	static const char *m_apTextureFile_Select[VTXSELECT_MAX];	// �e�N�X�`���̃t�@�C��
	bool m_bStick;		// �X�e�B�b�N�̔���
};



#endif