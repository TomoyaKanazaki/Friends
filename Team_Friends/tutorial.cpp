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

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
CTutorialStep *CTutorial::m_pStep = NULL;	// �X�e�b�v
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

	//**********************************
	// �e�L�X�g
	//**********************************
	CTutorialText *pText = CTutorialText::Create();

	//**********************************
	// �v���C���[
	//**********************************
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		m_apPlayer[i] = (CTutorialPlayer*)CManager::GetInstance()->GetScene()->GetPlayer(i);

		if (m_apPlayer[i] == nullptr)
		{
			m_apPlayer[i] = (CTutorialPlayer*)CTutorialPlayer::Create(i);
		}

		m_apPlayer[i]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -1000.0f));
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
	if (m_pStep != NULL)
	{// �������̊m�ۂ��o���Ă�����

		m_pStep->Uninit();
		delete m_pStep;
		m_pStep = NULL;
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

	if (/*m_pStep->GetNowStep() >= CTutorialStep::STEP_MAX - 1 &&*/
		(pInputKeyboard->GetTrigger(DIK_BACKSPACE) || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_START, 0) == true))
	{
		// ���[�h�ݒ�
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_GAME);
	}

	// �G�}�l�[�W���̍X�V����
	//GetEnemyManager()->Update();

	// �X�e�b�v�̍X�V����
	if (m_pStep != NULL)
	{// NULL����Ȃ�������
		m_pStep->Update();
	}
}

//==========================================================================
// �`�揈��
//==========================================================================
void CTutorial::Draw(void)
{

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
void CTutorial::SetDesableMovingPlayer(void)
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
