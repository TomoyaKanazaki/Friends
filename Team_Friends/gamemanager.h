//=============================================================================
// 
//  �Q�[���}�l�[�W���w�b�_�[ [gamemanager.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_	// ��d�C���N���[�h�h�~

#include "main.h"
#include "constans.h"

//==========================================================================
// �O���錾
//==========================================================================

//==========================================================================
// �N���X��`
//==========================================================================
// �Q�[���}�l�[�W���N���X��`
class CGameManager
{
public:

	// �V�[���̎��
	enum SceneType
	{
		SCENE_MAIN = 0,			// ���C��
		SCENE_RUSH,				// ���b�V��
		SCENE_BOSS,				// �{�X
		SCENE_TRANSITIONWAIT,	// �J�ڑҋ@
		SCENE_TRANSITION,		// �J��
		SCENE_MAX
	};

	CGameManager();
	~CGameManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void SetType(SceneType type);	// �V�[���̎�ސݒ�
	SceneType GetType(void);		// �V�[���̎�ގ擾
	void SetEnableRush(void) { m_bEndRush = true; }		// ���b�V���̏I���t���O��L���ɂ���
	bool IsRushEnd(void) { return m_bEndRush; }			// �I���̃t���O�擾
	void SetEnableControll(bool bControll) { m_bControll = bControll; }		// ����t���O��؂�ւ�����
	bool IsControll(void) { return m_bControll; }			// ����̃t���O�擾
	static CGameManager *Create(void);

private:

	// �����o�֐�

	// �����o�ϐ�
	SceneType m_SceneType;	// �V�[���̎��
	bool m_bEndRush;		// ���b�V�����I��������
	bool m_bControll;		// ����ł��邩
};



#endif