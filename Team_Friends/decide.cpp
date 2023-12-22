//==========================================
// 
//  �l���I������(decide.cpp)
//  Author : Tomoya Kanazaki
// 
//==========================================
#include "decide.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "debugproc.h"
#include "sound.h"
#include "decide_menu.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CDecide::CDecide()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CDecide::~CDecide()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CDecide::Init(void)
{
	// BGM�Đ�
	CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_BGM_SELECT_NUMBER);

	// ����������
	if (FAILED(CScene::Init()))
	{// ���s�����ꍇ
		return E_FAIL;
	}

	// �I�����j���[�̐���
	CDecideMenu::Create();

	// ����
	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CDecide::Uninit(void)
{
	// �I������
	CScene::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CDecide::Update(void)
{
	CManager::GetInstance()->GetDebugProc()->Print(
		"���݂̃��[�h�F�y�l�����߁z\n");

	// �L�[�{�[�h���擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �Q�[���p�b�h���擾
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	if (CManager::GetInstance()->GetFade()->GetState() != CFade::STATE_NONE)
	{// �t�F�[�h���͔�����
		return;
	}
}

//==========================================
//  �`�揈��
//==========================================
void CDecide::Draw(void)
{

}
