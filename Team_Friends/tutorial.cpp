//=============================================================================
// 
//  �`���[�g���A������ [tutorial.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "tutorial.h"
#include "input.h"
#include "fade.h"
#include "renderer.h"
#include "calculation.h"
#include "debugproc.h"
#include "player.h"
#include "sound.h"
#include "tutorialstep.h"
#include "tutorialtext.h"
#include "tutorialplayer.h"
#include "compactcore.h"
#include "enemymanager.h"
#include "tutorialmanager.h"
#include "enemybase.h"
#include "bulletmanager.h"
#include "limitereamanager.h"
#include "limitarea.h"
#include "stage.h"
#include "camera.h"

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
CTutorialStep *CTutorial::m_pStep = nullptr;					// �X�e�b�v
bool CTutorial::m_bMovingPlayer = false;						// �v���C���[�������Ă锻��
CTutorialManager *CTutorial::m_pTutorialManager = nullptr;			// �`���[�g���A���}�l�[�W���̃I�u�W�F�N�g
CEnemyManager *CTutorial::m_pEnemyManager = nullptr;				// �G�}�l�[�W���[
CEnemyBase *CTutorial::m_pEnemyBase = nullptr;						// �G���_
CBulletManager *CTutorial::m_pBulletManager = nullptr;				// �e�}�l�[�W���̃I�u�W�F�N�g
CLimitAreaManager *CTutorial::m_pLimitEreaManager = nullptr;		// �G���A�����}�l�[�W���̃I�u�W�F�N�g
CLimitArea *CTutorial::m_pLimitArea = nullptr;						// �G���A�����̃I�u�W�F�N�g
CStage *CTutorial::m_pStage = nullptr;								// �X�e�[�W�̃I�u�W�F�N�g

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CTutorial::CTutorial()
{
	// �l�̃N���A
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		m_apPlayer[i] = nullptr;	// �v���C���[�̃I�u�W�F�N�g
	}

	m_pText = nullptr;
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CTutorial::~CTutorial()
{

}

//==========================================================================
// ����������
//==========================================================================
HRESULT CTutorial::Init(void)
{
	// �e��ϐ��̏�����

	// ����������
	if (FAILED(CScene::Init()))
	{// ���s�����ꍇ
		return E_FAIL;
	}

	// BGM�Đ�
	CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_BGM_GAME);

	//**********************************
	// �X�e�b�v
	//**********************************
	m_pStep = CTutorialStep::Create();

	if (m_pStep == nullptr)
	{// NULL��������
		return E_FAIL;
	}
	
	//**********************************
	// �e�L�X�g
	//**********************************
	m_pText = CTutorialText::Create();

	if (m_pText == nullptr)
	{// NULL��������
		return E_FAIL;
	}

	//**********************************
	// �`���[�g���A���}�l�[�W���̋��_
	//**********************************
	m_pTutorialManager = CTutorialManager::Create();

	if (m_pTutorialManager == nullptr)
	{
		return E_FAIL;
	}

	//**********************************
	// �G���A�����}�l�[�W��
	//**********************************
	m_pLimitEreaManager = CLimitAreaManager::Create();

	if (m_pLimitEreaManager == nullptr)
	{// NULL��������
		return E_FAIL;
	}

	//**********************************
	// �G�̋��_
	//**********************************
	m_pEnemyBase = CEnemyBase::Create("data\\TEXT\\enemydata\\base.txt");

	if (m_pEnemyBase == nullptr)
	{
		return E_FAIL;
	}

	//**********************************
	// �G�}�l�[�W��
	//**********************************
	m_pEnemyManager = CEnemyManager::Create("data\\TEXT\\enemydata\\manager.txt");

	if (m_pEnemyManager == nullptr)
	{// NULL��������
		return E_FAIL;
	}

	//**********************************
	// �e�}�l�[�W��
	//**********************************
	m_pBulletManager = CBulletManager::Create();

	if (m_pBulletManager == nullptr)
	{// NULL��������
		return E_FAIL;
	}

	//**********************************
	// �X�e�[�W(�n��)
	//**********************************
	m_pStage = CStage::Create("data\\TEXT\\stage\\info.txt");

	if (m_pStage == nullptr)
	{// NULL��������
		return E_FAIL;
	}

	CManager::GetInstance()->GetCamera()->Reset(CScene::MODE_TUTORIAL);

	//**********************************
	// �G���A����
	//**********************************
	CLimitArea::sLimitEreaInfo info;
	info.fMaxX = 13000.0f;
	info.fMaxZ = 1200.0f;
	info.fMinX = -1200.0f;
	info.fMinZ = -1200.0f;
	m_pLimitArea = CLimitArea::Create(info);

	if (m_pLimitArea == nullptr)
	{// NULL��������
		return E_FAIL;
	}
	m_pLimitArea->SetEnableDisp(false);

	//**********************************
	// �v���C���[
	//**********************************
//#if _DEBUG		
//	//�f�o�b�O�p�l��
//	int nNumPlayer = 4;
//
//	CManager::GetInstance()->SetNumPlayer(nNumPlayer);
//	for (int i = 0; i < nNumPlayer; i++)
//#else
//	for (int nCntPlayer = 0; nCntPlayer < CManager::GetInstance()->GetNumPlayer(); nCntPlayer++)
//#endif
//	{
//		m_apPlayer[nCntPlayer] = (CTutorialPlayer*)CManager::G[etInstance()->GetScene()->GetPlayer(nCntPlayer);
//
//		if (m_apPlayer[nCntPlayer] == nullptr)
//		{
//			m_apPlayer[nCntPlayer] = (CTutorialPlayer*)CTutorialPlayer::Create(nCntPlayer);
//		}
//
//		m_apPlayer[nCntPlayer]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 100.0f));
//		m_apPlayer[nCntPlayer]->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
//	}

//	CManager::GetInstance()->SetNumPlayer(nNumPlayer);
//	for (int i = 0; i < nNumPlayer; i++)
//#else
//	for (int nCntPlayer = 0; nCntPlayer < CManager::GetInstance()->GetNumPlayer(); nCntPlayer++)
//#endif
	{
		//m_apPlayer[i] = (CTutorialPlayer*)CManager::GetInstance()->GetScene()->GetPlayer(i);

		//if (m_apPlayer[i] == nullptr)
		//{
		//	m_apPlayer[i] = (CTutorialPlayer*)CTutorialPlayer::Create(i);
		//}

		//m_apPlayer[i]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 100.0f));
		//m_apPlayer[i]->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	}

	// ����
	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CTutorial::Uninit(void)
{
	// �v���C���[�̔j��
	for (int i = 0; i < CManager::GetInstance()->GetNumPlayer(); i++)
	{
		m_apPlayer[i] = (CTutorialPlayer*)CManager::GetInstance()->GetScene()->GetPlayer(i);

		if (m_apPlayer[i] == nullptr)
		{
			continue;
		}

		m_apPlayer[i]->Kill();
		m_apPlayer[i] = nullptr;
	}

	// �X�e�b�v�̔j��
	if (m_pStep != nullptr)
	{// �������̊m�ۂ��o���Ă�����

		m_pStep->Uninit();
		delete m_pStep;
		m_pStep = nullptr;
	}

	// �e�L�X�g�̔j��
	if (m_pText != nullptr)
	{// �������̊m�ۂ��o���Ă�����
		m_pText = nullptr;
	}

	//=======================
	// �Q�[�����p
	if (m_pTutorialManager != nullptr)
	{
		m_pTutorialManager->Uninit();
		delete m_pTutorialManager;
		m_pTutorialManager = nullptr;
	}

	if (m_pBulletManager != nullptr)
	{
		// �I��������
		m_pBulletManager->Uninit();
		delete m_pBulletManager;
		m_pBulletManager = nullptr;
	}

	if (m_pLimitEreaManager != nullptr)
	{
		// �I��������
		m_pLimitEreaManager->Uninit();
		delete m_pLimitEreaManager;
		m_pLimitEreaManager = nullptr;
	}

	// �X�e�[�W�̔j��
	if (m_pStage != nullptr)
	{// �������̊m�ۂ��o���Ă�����

	 // �I������
		m_pStage->Uninit();
		delete m_pStage;
		m_pStage = nullptr;
	}

	// �G�}�l�[�W��
	if (m_pEnemyManager != nullptr)
	{
		m_pEnemyManager->Uninit();
		delete m_pEnemyManager;
		m_pEnemyManager = nullptr;
	}

	// �G�̋��_
	if (m_pEnemyBase != nullptr)
	{
		m_pEnemyBase->Uninit();
		delete m_pEnemyBase;
		m_pEnemyBase = nullptr;
	}
	//=======================

	// �I������
	CScene::Uninit();
}

//==========================================================================
// �X�V����
//==========================================================================
void CTutorial::Update(void)
{
	// �L�[�{�[�h���擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �Q�[���p�b�h���擾
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	//�`���[�g���A���}�l�[�W��
	if (m_pTutorialManager == nullptr)
	{
		m_pTutorialManager->Update();
	}

	if (m_pStep->IsEndAll() &&
		(pInputKeyboard->GetTrigger(DIK_BACKSPACE) || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_START, 0) == true))
	{
		// ���[�h�ݒ�
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_GAME);
	}

	// �X�e�b�v�̔j��
	if (m_pText != nullptr)
	{// �������̊m�ۂ��o���Ă�����
		m_pText->Update();
	}

	// �G�}�l�[�W���̍X�V����
	//GetEnemyManager()->Update();

	if (pInputKeyboard->GetTrigger(DIK_L))
	{
		m_pStep->SetStep(m_pStep->GetNowStep());
		// ���[�h�ݒ�
		m_pStep->AddStep();
	}

	// �X�e�b�v�̍X�V����
	if (m_pStep != nullptr)
	{// nullptr����Ȃ�������
		m_pStep->Update();
	}

	if (m_pEnemyManager != nullptr)
	{// NULL��������

		if (m_pEnemyManager->GetNumAll() == 0)
		{
			//�G�����Ȃ��X�e�b�v��
			if (m_pStep->GetNowStep() == CTutorialStep::STEP_MOVE)
			{
				return;
			}

			if (m_pEnemyBase != nullptr)
			{
				m_pEnemyBase->CreatePos(1, 1, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
			}
		}

		////�ŏI���̃X�e�b�v�ɍX�V���Ă�
		//ResetScene();
	}

	if (GetEnemyManager() != NULL)
	{// �G�}�l�[�W���̍X�V����
		GetEnemyManager()->Update();
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

	CScene::Update();
}

//==========================================================================
// �`�揈��
//==========================================================================
void CTutorial::Draw(void)
{
	// �X�e�b�v�̔j��
	if (m_pText != nullptr)
	{// �������̊m�ۂ��o���Ă�����
		m_pText->Draw();
	}
}

//==========================================================================
// �v���C���[�������Ă锻��
//==========================================================================
void CTutorial::SetEnableMovingPlayer(void)
{
	m_bMovingPlayer = true;
}

//==========================================================================
// �v���C���[�������Ă锻��OFF
//==========================================================================
void CTutorial::SetDisableMovingPlayer(void)
{
	m_bMovingPlayer = false;
}

//==========================================================================
// �v���C���[�������Ă锻��擾
//==========================================================================
bool CTutorial::IsMovingPlayer(void)
{
	return m_bMovingPlayer;
}

//==========================================================================
// �X�e�b�v�擾
//==========================================================================
CTutorialStep *CTutorial::GetStep(void)
{
	return m_pStep;
}

//==========================================================================
// �v���C���[�̎擾
//==========================================================================
CPlayer **CTutorial::GetPlayer(void)
{
	return (CPlayer**)(&m_apPlayer[0]);
}

//==========================================================================
// �v���C���[�̎擾
//==========================================================================
CPlayer *CTutorial::GetPlayer(int nIdx)
{
	return (CPlayer*)(m_apPlayer[nIdx]);
}

//==========================================================================
// �e�X�e�b�v�J�n���̒ǉ��v�f
//==========================================================================
void CTutorial::StepInitContent()
{
	CTutorialStep::STEP step = m_pStep->GetNowStep();

	if (!m_pStep->IsUpdate())
	{//�X�V����Ă��Ȃ�����
		return;
	}

	//�e�X�e�b�v�̏����v�f
	switch (step)
	{
	case CTutorialStep::STEP_WAIT:
		break;

	case CTutorialStep::STEP_MOVE:			//�ړ�
		break;

	case CTutorialStep::STEP_ATTACK:		//�U��
		break;

	case CTutorialStep::STEP_POWERUP:		//����
		break;

	case CTutorialStep::STEP_UNDER_UNION:		//�ȈՍ���-����
		CCompactCore::Create(D3DXVECTOR3(500.0f, 400.0f, 0.0f));
		break;

	case CTutorialStep::STEP_UNDER_FREE:		//�ȈՍ���-���R
		break;

	case CTutorialStep::STEP_UNION_FREE:		//����-���R
		break;

	case CTutorialStep::STEP_MAX:
		break;

	default:
		break;
	}
}

//==========================================================================
// �e�}�l�[�W���̎擾
//==========================================================================
CTutorialManager *CTutorial::GetTutorialManager(void)
{
	return m_pTutorialManager;
}

//==========================================================================
// �e�}�l�[�W���̎擾
//==========================================================================
CBulletManager *CTutorial::GetBulletManager(void)
{
	return m_pBulletManager;
}

//==========================================================================
// �G���A�����}�l�[�W���}�l�[�W���̎擾
//==========================================================================
CLimitAreaManager *CTutorial::GetLimitEreaManager(void)
{
	return m_pLimitEreaManager;
}

//==========================================================================
// �X�e�[�W�̎擾
//==========================================================================
CStage *CTutorial::GetStage(void)
{
	return m_pStage;
}

//==========================================================================
// �G�}�l�[�W���̎擾
//==========================================================================
CEnemyManager *CTutorial::GetEnemyManager(void)
{
	return m_pEnemyManager;
}

//==========================================================================
// �G�̋��_
//==========================================================================
CEnemyBase *CTutorial::GetEnemyBase(void)
{
	return m_pEnemyBase;
}

//==========================================================================
// ���Z�b�g����
//==========================================================================
void CTutorial::Reset(void)
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

	// �G���A����
	if (m_pLimitArea != NULL)
	{
		m_pLimitArea->Uninit();
		m_pLimitArea = NULL;
	}

	// �X�e�[�W
	m_pStage = CStage::Create("data\\TEXT\\stage\\boss_info.txt");

	//**********************************
	// �G�̋��_
	//**********************************
	m_pEnemyBase = CEnemyBase::Create("data\\TEXT\\enemydata\\base_boss.txt");
	if (m_pEnemyBase == NULL)
	{// NULL��������
		return;
	}

	/*if (m_pLimitArea == NULL)
	{
	CLimitArea::sLimitEreaInfo info;
	info.fMaxX = 8200.0f, info.fMaxZ = 785.0f, info.fMinX = -785.0f, info.fMinZ = -785.0f;
	m_pLimitArea = CLimitArea::Create(info);
	}*/
}
