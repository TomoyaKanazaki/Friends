//=============================================================================
// 
//  �^�C�g������ [title.cpp]
//  Author : ���n�Ή�
//  Added by �������
// 
//=============================================================================
#include "title.h"
#include "input.h"
#include "fade.h"
#include "renderer.h"
#include "calculation.h"
#include "debugproc.h"
#include "sound.h"
#include "title_logo.h"
#include "fog_title.h"

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CTitle::CTitle()
{
	// �l�̃N���A
	m_nCntSwitch = 0;		// �؂�ւ��̃J�E���^�[
	m_pLogo = nullptr;
	m_pFog = nullptr;
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CTitle::~CTitle()
{

}

//==========================================================================
// ����������
//==========================================================================
HRESULT CTitle::Init(void)
{
	// BGM�Đ�
	CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_BGM_TITLE);

	// ����������
	if (FAILED(CScene::Init()))
	{// ���s�����ꍇ
		return E_FAIL;
	}

	//�^�C�g�����S�̕\��
	if (m_pLogo == nullptr)
	{
		m_pLogo = CTitleLogo::Create();
	}

	//�t�H�O�𐶐�
	if (m_pFog == nullptr)
	{
		m_pFog = DEBUG_NEW CFog_Title;
		m_pFog->Init();
	}

	// ����
	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CTitle::Uninit(void)
{
	//�t�H�O��j��
	if (m_pFog != nullptr)
	{
		m_pFog->Uninit();
		m_pFog = nullptr;
	}

	// �^�C�g�����S��j��
	if (m_pLogo != nullptr)
	{
		m_pLogo = nullptr;
	}

	// �I������
	CScene::Uninit();
}

//==========================================================================
// �X�V����
//==========================================================================
void CTitle::Update(void)
{
	CManager::GetInstance()->GetDebugProc()->Print(
		"���݂̃��[�h�F�y�^�C�g���z\n"
		"�؂�ւ��F�y F �z\n\n");

	// �L�[�{�[�h���擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �Q�[���p�b�h���擾
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	// �؂�ւ��̃J�E���^�[���Z
	m_nCntSwitch++;

	if (CManager::GetInstance()->GetFade()->GetState() != CFade::STATE_NONE)
	{// �t�F�[�h���͔�����
		return;
	}

	if (m_nCntSwitch <= 120)
	{
		return;
	}

	//�^�C�g�����S���������Ă��Ȃ��Ƃ��͔�����
	if (!m_pLogo->GetComplete())
	{
		return;
	}

	//�t�H�O�̍X�V
	if (m_pFog != nullptr)
	{
		m_pFog->Update();
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, 0) == true)
	{
		// ���[�h�ݒ�
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_DECIDEPLAYER);
	}

	if (m_nCntSwitch >= 60 * 40)
	{// �����J��

		// ���[�h�ݒ�
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RANKING);
	}
}

//==========================================================================
// �`�揈��
//==========================================================================
void CTitle::Draw(void)
{

}
