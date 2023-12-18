//=============================================================================
// 
//  �`���[�g���A���e�L�X�g�w�b�_�[ [tutorialtext.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _TUTORIALTEXT_H_
#define _TUTORIALTEXT_H_	// ��d�C���N���[�h�h�~

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
class CTutorialText : public CObject
{
public:

	CTutorialText(int nPriority = 7);
	~CTutorialText();

	static CTutorialText *Create(void);

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetVtx(void);
private:
	// �񋓌^��`
	enum VTX
	{
		VTX_WINDOW = 0,	// �g
		VTX_TEXT,		// �e�L�X�g
		VTX_SKIP,		// �X�L�b�v
		VTX_MAX
	};

	enum TEX
	{
		TEX_WINDOW = 0,	// �g
		TEX_TEXT_WAIT,		// �e�L�X�g
		TEX_TEXT_SPEEDUP,		// �e�L�X�g
		TEX_TEXT_SPEEDDOWN,		// �e�L�X�g
		TEX_TEXT_IMPACTWAVE,		// �e�L�X�g
		TEX_TEXT_DIRECTWAVE,	// �e�L�X�g
		TEX_TEXT_END,	// �e�L�X�g
		TEX_SKIP,
		TEX_MAX
	};

	// �����o�֐�
	void SetVtx(int nCntSelect);

	// �����o�ϐ�
	int m_nCntMoving;	// �ړ����Ă�J�E���^�[
	int m_nTexIdx[TEX_MAX];							// �e�N�X�`���̃C���f�b�N�X�ԍ�
	CObject2D *m_pObj2D[VTX_MAX];					// �I�u�W�F�N�g2D�̃I�u�W�F�N�g
	static const char *m_apTextureFile[TEX_MAX];	// �e�N�X�`���̃t�@�C��
};

#endif