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

class CTutorialManager;
class CEnemyManager;
class CEnemyBase;
class CBulletManager;
class CStage;
class CLimitArea;
class CLimitAreaManager;

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
	
	static void Reset(void);
	
	static CTutorialManager *GetTutorialManager(void);
	static CEnemyManager *GetEnemyManager(void);
	static CEnemyBase *GetEnemyBase(void);		// �G�̋��_
	static CBulletManager *GetBulletManager(void);
	static CLimitAreaManager *GetLimitEreaManager(void);
	static CStage *GetStage(void);

private:

	CTutorialPlayer *m_apPlayer[mylib_const::MAX_PLAYER];		// �v���C���[�̃I�u�W�F�N�g
	static bool m_bMovingPlayer;	// �v���C���[�������Ă锻��
	static CTutorialStep *m_pStep;	// �X�e�b�v
	CTutorialText *m_pText;			//�e�L�X�g

	static CEnemyManager *m_pEnemyManager;	//�G�}�l�[�W���[
	static CEnemyBase *m_pEnemyBase;	//�G���_
	static CTutorialManager *m_pTutorialManager;		// �`���[�g���A���}�l�[�W���̃I�u�W�F�N�g
	static CBulletManager *m_pBulletManager;		// �e�}�l�[�W���̃I�u�W�F�N�g
	static CLimitAreaManager *m_pLimitEreaManager;	// �G���A�����}�l�[�W���̃I�u�W�F�N�g
	static CLimitArea *m_pLimitArea;				// �G���A�����̃I�u�W�F�N�g
	static CStage *m_pStage;						// �X�e�[�W�̃I�u�W�F�N�g

};

#endif