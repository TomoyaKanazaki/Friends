//=============================================================================
// 
//  �Q�[���w�b�_�[ [game.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _GAME_H_
#define _GAME_H_	// ��d�C���N���[�h�h�~

#include "main.h"
#include "scene.h"
#include "gamemanager.h"

//==========================================================================
// �O���錾
//==========================================================================
class CPlayer;
class CScore;
class CTimer;
class CPowerGauge;
class CBulletManager;
class CEditEnemyBase;
class CStage;
class CHitScore;
class CStatusWindow;
class CUltWindow;
class CEnemyManager;
class CItemManager;
class CLimitArea;
class CLimitAreaManager;
class CPlayer;
class CEnemyBase;

//==========================================================================
// �N���X��`
//==========================================================================
// �Q�[���N���X��`
class CGame : public CScene
{
public:

	// �G�f�B�b�g�^�C�v
	enum EEditType
	{
		EDITTYPE_OFF = 0,			// �I�t
		EDITTYPE_ENEMYBASE,			// �G���_
		EDITTYPE_MAX
	};

	CGame();
	~CGame();

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void Reset(void);
	static EEditType GetEditType(void) { return m_EditType; }
	static CScore *GetScore(void);
	static CTimer *GetTimer(void) { return m_pTimer; }	// �^�C�}�[�擾
	static CEditEnemyBase *GetEditEnemyBase(void);
	static CBulletManager *GetBulletManager(void);
	static CItemManager *GetItemManager(void);
	static CLimitAreaManager *GetLimitEreaManager(void);
	static CStage *GetStage(void);
	static CGameManager *GetGameManager(void);
	static CStatusWindow *GetStatusWindow(int nIdx);
	static CUltWindow *GetUltWindow(int nIdx);		// �K�E�̃E�B���h�E�擾
	static bool IsClearFrag(void) { return m_clear; } // �N���A�t���O�̎擾

	static CEnemyManager *GetEnemyManager(void);
	static CEnemyBase *GetEnemyBase(void);		// �G�̋��_
	static bool IsEdit(void) { return m_bEdit; }	// �G�f�B�b�g�̔���

private:

	// �����o�֐�
	void EditReset(void);

	// �����o�ϐ�
	static CScore *m_pScore;						// �X�R�A�̃I�u�W�F�N�g
	static CTimer *m_pTimer;						// �^�C�}�[�̃I�u�W�F�N�g
	static CBulletManager *m_pBulletManager;		// �e�}�l�[�W���̃I�u�W�F�N�g
	static CItemManager *m_pItemManager;			// �A�C�e���}�l�[�W���̃I�u�W�F�N�g
	static CLimitAreaManager *m_pLimitEreaManager;	// �G���A�����}�l�[�W���̃I�u�W�F�N�g
	static CLimitArea *m_pLimitArea;				// �G���A�����̃I�u�W�F�N�g
	static CEditEnemyBase *m_pEditEnemyBase;		// �G�̋��_�G�f�B�^�[
	static CStage *m_pStage;						// �X�e�[�W�̃I�u�W�F�N�g
	static CGameManager *m_pGameManager;			// �Q�[���}�l�[�W���̃I�u�W�F�N�g
	static EEditType m_EditType;					// �G�f�B�b�g�̎��
	static CEnemyManager *m_pEnemyManager;			// �G�}�l�[�W���̃I�u�W�F�N�g
	static CEnemyBase *m_pEnemyBase;				// �G�̋��_
	static CStatusWindow *m_pStatusWindow[mylib_const::MAX_PLAYER];	// �X�e�[�^�X�E�B���h�E�̃I�u�W�F�N�g
	static CUltWindow *m_pUltWindow[mylib_const::MAX_PLAYER];		// �K�E�̃E�B���h�E
	static bool m_bEdit;				// �G�f�B�b�g�̔���
	static bool m_clear; // �N���A����

};



#endif