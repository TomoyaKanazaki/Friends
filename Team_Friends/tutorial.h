//=============================================================================
// 
//  �`���[�g���A���w�b�_�[ [tutorial.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_	// ��d�C���N���[�h�h�~

#include "main.h"
#include "manager.h"

//==========================================================================
// �O���錾
//==========================================================================
class CTutorialStep;
class CTutorialText;
class CTutorialPlayer;
class CEnemyManager;
class CEnemyBase;

//==========================================================================
// �N���X��`
//==========================================================================
// �`���[�g���A���N���X��`
class CTutorial : public CScene
{
public:

	CTutorial();
	~CTutorial();

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	static bool IsMovingPlayer(void);		// �v���C���[�������Ă锻��擾
	static void SetEnableMovingPlayer(void);		// �v���C���[�������Ă锻��
	static void SetDisableMovingPlayer(void);		// �v���C���[�������Ă锻��OFF
	static CTutorialStep *GetStep(void);	// �X�e�b�v�擾
	CPlayer **GetPlayer(void);				// �v���C���[�̎擾
	CPlayer *GetPlayer(int nIdx);			// �v���C���[�̎擾
	void StepInitContent();					// �e�X�e�b�v�J�n���̒ǉ��v�f

private:

	CTutorialPlayer *m_apPlayer[mylib_const::MAX_PLAYER];		// �v���C���[�̃I�u�W�F�N�g
	static bool m_bMovingPlayer;	// �v���C���[�������Ă锻��
	static CTutorialStep *m_pStep;	// �X�e�b�v
	CTutorialText *m_pText;			//�e�L�X�g
	CEnemyManager *m_pEnemyManager;	//�G�}�l�[�W���[
	CEnemyBase *m_pEnemyBase;	//�G���_
};

#endif