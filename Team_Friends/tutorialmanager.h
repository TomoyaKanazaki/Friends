//=============================================================================
// 
//  �Q�[���}�l�[�W���w�b�_�[ [gamemanager.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _TUTORIALMANAGER_H_
#define _TUTORIALMANAGER_H_	// ��d�C���N���[�h�h�~

#include "constans.h"

//==========================================================================
// �N���X��`
//==========================================================================
// �Q�[���}�l�[�W���N���X��`
class CTutorialManager
{
public:

	// �V�[���̎��
	enum SceneType
	{
		SCENE_INTRO = 0,		// ����
		SCENE_MAIN,				// ���C��
		SCENE_MAINCLEAR,		// ���C���N���A
		SCENE_EVOLUSION,		// �i��
		SCENE_RUSH,				// ���b�V��
		SCENE_BOSS,				// �{�X
		SCENE_TRANSITIONWAIT,	// �J�ڑҋ@
		SCENE_TRANSITION,		// �J��
		SCENE_MAX
	};

	// �X�e�[�^�X����
	enum eStatus
	{
		STATUS_POWER = 0,	// �Η�
		STATUS_SPEED,		// �쓮��
		STATUS_LIFE,		// �ϋv
		STATUS_MAX
	};

	CTutorialManager();
	~CTutorialManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void SetType(SceneType type);	// �V�[���̎�ސݒ�
	SceneType GetType(void);		// �V�[���̎�ގ擾
	void SetEnableRush(void) { m_bEndRush = true; }		// ���b�V���̏I���t���O��L���ɂ���
	bool IsRushEnd(void) { return m_bEndRush; }			// �I���̃t���O�擾
	void SetEnableControll(bool bControll) { m_bControll = bControll; }		// ����t���O��؂�ւ�����
	bool IsControll(void) { return m_bControll; }				// ����̃t���O�擾
	bool IsEndNormalStage(void) { return m_bEndNormalStage; }	// �ʏ�X�e�[�W�̃A�I������
	void SetEnableEvolusion(void);								// �i���ݒ�L��
	bool IsSetEvolusion(void) { return m_bSetEvolusion; }		// �i���ݒ肵�Ă邩
	void AddNowStage(void);	// �X�e�[�W�̉��Z
	int GetNowStage(void);	// ���݂̃X�e�[�W�擾
	void SetNumStage(int nStage) { m_nNumStage = nStage; }	// �X�e�[�W�̑����ݒ�
	int GetNumStage(void) { return m_nNumStage; }			// �X�e�[�W�̑����擾

	static CTutorialManager *Create(void);	// ��������

private:

	// �����o�֐�
	void SetBoss(void);
	void SetEnemy(void);

	// �����o�ϐ�
	SceneType m_SceneType;	// �V�[���̎��
	bool m_bEndRush;		// ���b�V�����I��������
	bool m_bControll;		// ����ł��邩
	bool m_bEndNormalStage;	// �ʏ�X�e�[�W���I��������
	bool m_bSetEvolusion;	// �i���ݒ肵�Ă邩
	int m_nNowStage;		// ���݂̃X�e�[�W
	int m_nNumStage;		// �X�e�[�W�̑���
};



#endif