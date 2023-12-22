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
#include "pause.h"

#include "input.h"
#include "player.h"
#include "enemy.h"
#include "score.h"
#include "timer.h"
#include "map.h"
#include "elevation.h"
#include "sound.h"
#include "edit_enemybase.h"
#include "bulletmanager.h"
#include "itemmanager.h"
#include "stage.h"
#include "compactcore.h"
#include "statuswindow.h"
#include "ultwindow.h"
#include "emergency.h"

#include "enemymanager.h"
#include "player.h"
#include "player_union.h"
#include "enemybase.h"
#include "limitarea.h"
#include "limitereamanager.h"

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
CScore *CGame::m_pScore = NULL;					// �X�R�A�̃I�u�W�F�N�g
CTimer *CGame::m_pTimer = NULL;						// �^�C�}�[�̃I�u�W�F�N�g
CBulletManager *CGame::m_pBulletManager = NULL;		// �e�}�l�[�W���̃I�u�W�F�N�g
CItemManager *CGame::m_pItemManager = nullptr;			// �A�C�e���}�l�[�W���̃I�u�W�F�N�g
CLimitAreaManager *CGame::m_pLimitEreaManager = NULL;	// �G���A�����}�l�[�W���̃I�u�W�F�N�g
CLimitArea *CGame::m_pLimitArea = NULL;					// �G���A�����̃I�u�W�F�N�g
CEditEnemyBase *CGame::m_pEditEnemyBase = NULL;		// �G�̋��_�G�f�B�^�[
CStage *CGame::m_pStage = NULL;						// �X�e�[�W�̃I�u�W�F�N�g
CGameManager *CGame::m_pGameManager = NULL;			// �Q�[���}�l�[�W���̃I�u�W�F�N�g
CGame::EEditType CGame::m_EditType = EDITTYPE_OFF;		// �G�f�B�b�g�̎��
CEnemyBase *CGame::m_pEnemyBase = NULL;	// �G�̋��_
CEnemyManager *CGame::m_pEnemyManager = NULL;	// �G�}�l�[�W���̃I�u�W�F�N�g
CStatusWindow *CGame::m_pStatusWindow[mylib_const::MAX_PLAYER] = {};	// �X�e�[�^�X�E�B���h�E�̃I�u�W�F�N�g
CUltWindow *CGame::m_pUltWindow[mylib_const::MAX_PLAYER] = {};			// �K�E�̃E�B���h�E
bool CGame::m_bEdit = false;				// �G�f�B�b�g�̔���
bool CGame::m_clear = false;				// �N���A����

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
	m_clear = false;

	// BGM�Đ�
	CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_BGM_GAME);

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
	// �G���A�����}�l�[�W��
	//**********************************
	m_pLimitEreaManager = CLimitAreaManager::Create();

	//**********************************
	// �G�̋��_
	//**********************************
	m_pEnemyBase = CEnemyBase::Create("data\\TEXT\\enemydata\\base.txt");
	if (m_pEnemyBase == NULL)
	{// NULL��������
		return E_FAIL;
	}

	//**********************************
	// �G�}�l�[�W��
	//**********************************
	m_pEnemyManager = CEnemyManager::Create("data\\TEXT\\enemydata\\manager.txt");
	if (m_pEnemyManager == NULL)
	{// NULL��������
		return E_FAIL;
	}

	//**********************************
	// �v���C���[
	//**********************************
	for (int nCntPlayer = 0; nCntPlayer < CManager::GetInstance()->GetNumPlayer(); nCntPlayer++)
	{
		CPlayer *pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(nCntPlayer);
		if (pPlayer != NULL)
		{
			pPlayer->SetPosition(D3DXVECTOR3(-500.0f + nCntPlayer * 50.0f, 5000.0f, 0.0f));
			pPlayer->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}

	for (int nCntPlayer = 0; nCntPlayer < mylib_const::MAX_PLAYER; nCntPlayer++)
	{
		bool bJoin = true;
		if (CManager::GetInstance()->GetNumPlayer() <= nCntPlayer)
		{
			bJoin = false;
		}
		m_pStatusWindow[nCntPlayer] = CStatusWindow::Create(D3DXVECTOR3(160.0f + nCntPlayer * 320.0f, 600.0f, 0.0f), bJoin);
	}

	//**********************************
	// �e�}�l�[�W��
	//**********************************
	m_pBulletManager = CBulletManager::Create();


	//**********************************
	// �A�C�e���}�l�[�W��
	//**********************************
	m_pItemManager = CItemManager::Create();


	// �X�e�[�W
	m_pStage = CStage::Create("data\\TEXT\\stage\\info.txt");

	// �X�R�A�̐�������
	//m_pScore = CScore::Create(D3DXVECTOR3(1000.0f, 50.0f, 0.0f));

	CManager::GetInstance()->GetCamera()->Reset(CScene::MODE_GAME);

	// BGM�Đ�
	CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_BGM_GAME);

	// �ȈՍ��̃R�A
	//CCompactCore::Create(D3DXVECTOR3(500.0f, 400.0f, 0.0f));

	CLimitArea::sLimitEreaInfo info;
	info.fMaxX = 13000.0f;
	info.fMaxZ = 1200.0f;
	info.fMinX = -1200.0f;
	info.fMinZ = -1200.0f;
	m_pLimitArea = CLimitArea::Create(info);
	m_pLimitArea->SetEnableDisp(false);
	//CMeshWall::Create(D3DXVECTOR3(0.0f, 0.0f, 1500.0f), mylib_const::DEFAULT_VECTOR3, 200.0f, 200.0f, 8, 1);

	// �i����ݒ�ナ�Z�b�g
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		CManager::GetInstance()->SetByPlayerPartsType(i, -1);
	}

	// �^�C�}�[
	m_pTimer = CTimer::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f));

	CEmergency::Create();

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

	// �^�C�}�[�̔j��
	if (m_pTimer != NULL)
	{
		// �I������
		m_pTimer->Uninit();
		delete m_pTimer;
		m_pTimer = NULL;
	}

	if (m_pBulletManager != NULL)
	{
		// �I��������
		m_pBulletManager->Uninit();
		delete m_pBulletManager;
		m_pBulletManager = NULL;
	}

	if (m_pItemManager != NULL)
	{
		// �I��������
		m_pItemManager->Uninit();
		delete m_pItemManager;
		m_pItemManager = NULL;
	}

	if (m_pLimitEreaManager != NULL)
	{
		// �I��������
		m_pLimitEreaManager->Uninit();
		delete m_pLimitEreaManager;
		m_pLimitEreaManager = NULL;
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

#ifdef _DEBUG
	// �N���A����؂�ւ�
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_V))
	{
		m_clear = !m_clear;
	}
	CManager::GetInstance()->GetDebugProc()->Print
	(
		"���I���� : "
	);
	if (m_clear)
	{
		CManager::GetInstance()->GetDebugProc()->Print
		(
			"����\n\n"
		);
	}
	else
	{
		CManager::GetInstance()->GetDebugProc()->Print
		(
			"���s\n\n"
		);
	}
#endif

	// �L�[�{�[�h���擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �Q�[���p�b�h���擾
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

#if 1
	if (m_pScore != NULL &&
		CManager::GetInstance()->GetEdit() == NULL &&
		m_pEnemyManager != NULL &&
		GetEnemyManager()->GetState() != CEnemyManager::STATE_COMBOANIM)
	{
		// �X�R�A�̍X�V����
		m_pScore->Update();
	}
#endif

#if _DEBUG
	if (pInputKeyboard->GetTrigger(DIK_F4))
	{// F4�ŃG�f�B�b�g�؂�ւ�

		// �؂�ւ�
		m_EditType = (EEditType)(((int)m_EditType + 1) % (int)EDITTYPE_MAX);	// �Ǐ]�̎��

		// ���Z�b�g
		EditReset();

		// �G�f�B�b�g����ON
		m_bEdit = true;

		switch (m_EditType)
		{
		case CGame::EDITTYPE_OFF:	// �S���I�t
			// �G�f�B�b�g����OFF
			m_bEdit = false;
			break;

		case EDITTYPE_ENEMYBASE:
			if (m_pEditEnemyBase == NULL)
			{// NULL��������

				// �G�f�B�b�g�̐�������
				m_pEditEnemyBase = CEditEnemyBase::Create();
			}
			break;

		}
	}
#endif

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


	// �^�C�}�[�X�V
	if (m_pTimer != NULL &&
		!CManager::GetInstance()->GetPause()->IsPause())
	{
		m_pTimer->Update();
	}

#if _DEBUG

	if (pInputKeyboard->GetTrigger(DIK_F))
	{
		// ���[�h�ݒ�
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RESULT);
	}

	if (pInputKeyboard->GetTrigger(DIK_I))
	{
		CCompactCore::Create(D3DXVECTOR3(500.0f, 200.0f, 0.0f));
	}

#endif

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
// �G���A�����}�l�[�W���}�l�[�W���̎擾
//==========================================================================
CLimitAreaManager *CGame::GetLimitEreaManager(void)
{
	return m_pLimitEreaManager;
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
// �A�C�e���}�l�[�W���̎擾
//==========================================================================
CItemManager *CGame::GetItemManager(void)
{
	return m_pItemManager;
}

//==========================================================================
// �G�̋��_
//==========================================================================
CEnemyBase *CGame::GetEnemyBase(void)
{
	return m_pEnemyBase;
}

//==========================================================================
// �X�e�[�^�X�E�B���h�E
//==========================================================================
CStatusWindow *CGame::GetStatusWindow(int nIdx)
{
	return m_pStatusWindow[nIdx];
}

//==========================================================================
// �K�E�̃E�B���h�E�擾
//==========================================================================
CUltWindow *CGame::GetUltWindow(int nIdx)
{
	return m_pUltWindow[nIdx];
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

	// �A�C�e���}�l�[�W��
	if (m_pItemManager != NULL)
	{
		m_pItemManager->KillAll();
	}

	// �G���A����
	if (m_pLimitArea != NULL)
	{
		m_pLimitArea->Uninit();
		m_pLimitArea = NULL;
	}

	// �X�e�[�W
	m_pStage = CStage::Create("data\\TEXT\\stage\\boss_info.txt");

	// �X�e�[�^�X�E�B���h�E
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		if (m_pStatusWindow[i] == nullptr)
		{
			continue;
		}
		m_pStatusWindow[i]->Kill();
		m_pStatusWindow[i] = nullptr;
	}

	//**********************************
	// �G�̋��_
	//**********************************
	m_pEnemyBase = CEnemyBase::Create("data\\TEXT\\enemydata\\base_boss.txt");
	if (m_pEnemyBase == NULL)
	{// NULL��������
		return;
	}

	// �K�E�Q�[�W
	for (int nCntPlayer = 0; nCntPlayer < mylib_const::MAX_PLAYER; nCntPlayer++)
	{
		bool bJoin = true;
		if (CManager::GetInstance()->GetNumPlayer() <= nCntPlayer)
		{
			bJoin = false;
		}
		m_pUltWindow[nCntPlayer] = CUltWindow::Create(D3DXVECTOR3(160.0f + nCntPlayer * 320.0f, 600.0f, 0.0f), bJoin);
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
