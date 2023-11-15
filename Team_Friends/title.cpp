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
#include "fog.h"
#include "title_logo.h"

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CTitle::CTitle()
{
	// �l�̃N���A
	m_nCntSwitch = 0;		// �؂�ւ��̃J�E���^�[
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

	//����������
	Fog::Set(true);

	//�t�H�O�̒l��ݒ肷��
	Fog::SetStart(100.0f);
	Fog::SetEnd(100.0f);
	Fog::SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	//�^�C�g�����S�̕\��
	CTitleLogo::Create();

	// ����
	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CTitle::Uninit(void)
{
	//���𕥂�
	Fog::Set(false);

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

#ifdef _DEBUG
	if (pInputKeyboard->GetPress(DIK_UP))
	{
		float fLength = Fog::GetEnd();
		Fog::SetEnd(fLength + 30.0f);
	}
	if (pInputKeyboard->GetPress(DIK_DOWN))
	{
		float fLength = Fog::GetEnd();
		Fog::SetEnd(fLength - 30.0f);
	}
	if (pInputKeyboard->GetTrigger(DIK_LEFT))
	{
		Fog::SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	}
	if (pInputKeyboard->GetTrigger(DIK_RIGHT))
	{
		Fog::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
#endif
}

//==========================================================================
// �`�揈��
//==========================================================================
void CTitle::Draw(void)
{

}
