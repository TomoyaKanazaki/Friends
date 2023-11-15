//=============================================================================
// 
//  �Q�[������ [game.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "manager.h"
#include "game.h"
#include "renderer.h"
#include "calculation.h"
#include "debugproc.h"
#include "fade.h"
#include "camera.h"

#include "input.h"
#include "player.h"
#include "enemy.h"
#include "score.h"
#include "map.h"
#include "elevation.h"
#include "sound.h"
#include "edit_enemybase.h"
#include "bulletmanager.h"
#include "stage.h"
#include "gamemanager.h"

#include "enemymanager.h"
#include "player.h"
#include "enemybase.h"

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
CScore *CGame::m_pScore = NULL;					// �X�R�A�̃I�u�W�F�N�g
CBulletManager *CGame::m_pBulletManager = NULL;		// �e�}�l�[�W���̃I�u�W�F�N�g
CEditEnemyBase *CGame::m_pEditEnemyBase = NULL;		// �G�̋��_�G�f�B�^�[
CStage *CGame::m_pStage = NULL;						// �X�e�[�W�̃I�u�W�F�N�g
CGameManager *CGame::m_pGameManager = NULL;			// �Q�[���}�l�[�W���̃I�u�W�F�N�g
CGame::EEditType CGame::m_EditType = EDITTYPE_OFF;		// �G�f�B�b�g�̎��
CEnemyBase *CGame::m_pEnemyBase = NULL;	// �G�̋��_
CEnemyManager *CGame::m_pEnemyManager = NULL;	// �G�}�l�[�W���̃I�u�W�F�N�g
bool CGame::m_bEdit = false;				// �G�f�B�b�g�̔���

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CGame::CGame()
{
	// �l�̃N���A
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CGame::~CGame()
{

}

//==========================================================================
// ����������
//==========================================================================
HRESULT CGame::Init(void)
{
	// �G�f�B�b�g����OFF
	m_bEdit = false;

	// ����������
	if (FAILED(CScene::Init()))
	{// ���s�����ꍇ
		return E_FAIL;
	}

	//**********************************
	// �Q�[���}�l�[�W��
	//**********************************
	m_pGameManager = CGameManager::Create();

	//**********************************
	// �e�}�l�[�W��
	//**********************************
	m_pBulletManager = CBulletManager::Create();

	// �X�e�[�W
	m_pStage = CStage::Create("data\\TEXT\\stage_info.txt");

	CManager::GetInstance()->GetCamera()->Reset(CScene::MODE_GAME);

	// ����
	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CGame::Uninit(void)
{

	// �X�R�A�̔j��
	if (m_pScore != NULL)
	{// �������̊m�ۂ��o���Ă�����

		// �I������
		m_pScore->Uninit();

		// �������̊J��
		delete m_pScore;
		m_pScore = NULL;
	}

	if (m_pBulletManager != NULL)
	{
		// �I��������
		m_pBulletManager->Uninit();
		delete m_pBulletManager;
		m_pBulletManager = NULL;
	}

	if (m_pEditEnemyBase != NULL)
	{
		// �I��������
		m_pEditEnemyBase->Uninit();
		delete m_pEditEnemyBase;
		m_pEditEnemyBase = NULL;
	}

	// �X�e�[�W�̔j��
	if (m_pStage != NULL)
	{// �������̊m�ۂ��o���Ă�����

		// �I������
		m_pStage->Uninit();
		delete m_pStage;
		m_pStage = NULL;
	}

	if (m_pGameManager != NULL)
	{
		// �I������
		m_pGameManager->Uninit();
		delete m_pGameManager;
		m_pGameManager = NULL;
	}

	// �G�}�l�[�W��
	if (m_pEnemyManager != NULL)
	{
		m_pEnemyManager->Uninit();
		delete m_pEnemyManager;
		m_pEnemyManager = NULL;
	}

	// �G�̋��_
	if (m_pEnemyBase != NULL)
	{
		m_pEnemyBase->Uninit();
		delete m_pEnemyBase;
		m_pEnemyBase = NULL;
	}


	// �I������
	CScene::Uninit();
}

//==========================================================================
// �X�V����
//==========================================================================
void CGame::Update(void)
{
	// �Q�[���}�l�[�W��
	if (m_pGameManager != NULL)
	{
		// �X�V����
		m_pGameManager->Update();
	}

	CManager::GetInstance()->GetDebugProc()->Print(
		"���݂̃��[�h�F�y�Q�[���z\n"
		"�؂�ւ��F�y F �z\n\n");

	// �L�[�{�[�h���擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �Q�[���p�b�h���擾
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	if (GetEnemyManager() != NULL)
	{// �G�}�l�[�W���̍X�V����
		GetEnemyManager()->Update();
	}

	if (m_pEditEnemyBase != NULL)
	{// �G�̋��_�G�f�B�^�[�̍X�V����
		m_pEditEnemyBase->Update();
	}

	// �G�̋��_
	if (m_pEnemyBase != NULL)
	{
		m_pEnemyBase->Update();
	}

	// �X�e�[�W�̍X�V
	if (m_pStage != NULL)
	{
		m_pStage->Update();
	}

	// �V�[���̍X�V
	CScene::Update();

}

//==========================================================================
// �`�揈��
//==========================================================================
void CGame::Draw(void)
{

}

//==========================================================================
// �X�R�A�̎擾
//==========================================================================
CScore *CGame::GetScore(void)
{
	return m_pScore;
}

//==========================================================================
// �e�}�l�[�W���̎擾
//==========================================================================
CBulletManager *CGame::GetBulletManager(void)
{
	return m_pBulletManager;
}

//==========================================================================
// �X�e�[�W�̎擾
//==========================================================================
CStage *CGame::GetStage(void)
{
	return m_pStage;
}

//==========================================================================
// �Q�[���}�l�[�W���̎擾
//==========================================================================
CGameManager *CGame::GetGameManager(void)
{
	return m_pGameManager;
}


//==========================================================================
// �G�}�l�[�W���̎擾
//==========================================================================
CEnemyManager *CGame::GetEnemyManager(void)
{
	return m_pEnemyManager;
}

//==========================================================================
// �G�̋��_
//==========================================================================
CEnemyBase *CGame::GetEnemyBase(void)
{
	return m_pEnemyBase;
}

//==========================================================================
// ���Z�b�g����
//==========================================================================
void CGame::Reset(void)
{
	// �X�e�[�W�̔j��
	if (m_pStage != NULL)
	{// �������̊m�ۂ��o���Ă�����

		// �I������
		m_pStage->Release();
		delete m_pStage;
		m_pStage = NULL;
	}

	// �G�̋��_
	if (m_pEnemyBase != NULL)
	{
		m_pEnemyBase->Uninit();
		delete m_pEnemyBase;
		m_pEnemyBase = NULL;
	}

	// �G�}�l�[�W��
	if (m_pEnemyManager != NULL)
	{
		m_pEnemyManager->Kill();
	}

	// �X�e�[�W
	m_pStage = CStage::Create("data\\TEXT\\bossstage_info.txt");

	//**********************************
	// �G�̋��_
	//**********************************
	m_pEnemyBase = CEnemyBase::Create("data\\TEXT\\enemybase_boss.txt");
	if (m_pEnemyBase == NULL)
	{// NULL��������
		return;
	}
}

//==========================================================================
// �G�f�B�^�[���Z�b�g����
//==========================================================================
void CGame::EditReset(void)
{
	
	if (m_pEditEnemyBase != NULL)
	{
		// �I��������
		m_pEditEnemyBase->Release();
		m_pEditEnemyBase->Uninit();
		delete m_pEditEnemyBase;
		m_pEditEnemyBase = NULL;
	}

}
