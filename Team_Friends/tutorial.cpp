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
#include "enemybase.h"

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
CTutorialStep *CTutorial::m_pStep = nullptr;	// �X�e�b�v
bool CTutorial::m_bMovingPlayer = false;	// �v���C���[�������Ă锻��

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
	m_pEnemyManager = nullptr;
	m_pEnemyBase = nullptr;
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
	// �v���C���[
	//**********************************
#if _DEBUG		
	//�f�o�b�O�p�l��
	int nNumPlayer = 4;

	CManager::GetInstance()->SetNumPlayer(nNumPlayer);
	for (int i = 0; i < nNumPlayer; i++)
#else
	for (int nCntPlayer = 0; nCntPlayer < CManager::GetInstance()->GetNumPlayer(); nCntPlayer++)
#endif
	{
		m_apPlayer[i] = (CTutorialPlayer*)CManager::GetInstance()->GetScene()->GetPlayer(i);

		if (m_apPlayer[i] == nullptr)
		{
			m_apPlayer[i] = (CTutorialPlayer*)CTutorialPlayer::Create(i);
		}

		m_apPlayer[i]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 100.0f));
		m_apPlayer[i]->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
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

	// �G�̋��_
	if (m_pEnemyBase != NULL)
	{
		m_pEnemyBase->Uninit();
		delete m_pEnemyBase;
		m_pEnemyBase = NULL;
	}

	if (m_pEnemyManager != nullptr)
	{// NULL��������
		m_pEnemyManager->Kill();
		m_pEnemyManager = nullptr;
	}

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
		//�X�e�b�v�X�V�t���O
		m_pStep->IsUpdate();
	}

	if (m_pEnemyBase != nullptr)
	{
		m_pEnemyBase->Update();
	}

	if (m_pEnemyManager != nullptr)
	{// NULL��������

		if (m_pEnemyManager->GetNumAll() == 0)
		{

		}
	}


	//�ŏI���̃X�e�b�v�ɍX�V���Ă�
	ResetScene();
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
