//=============================================================================
// 
//  ���U���g���� [result.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "result.h"
#include "input.h"
#include "fade.h"
#include "renderer.h"
#include "calculation.h"
#include "debugproc.h"
#include "player.h"
#include "sound.h"
#include "resultscore.h"
#include "fog.h"
#include "game.h"
#include "union_title.h"
#include "message_lose.h"

//==========================================
//  �萔��` ����
//==========================================
namespace
{
	const D3DXCOLOR WIN_COLOR = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	const D3DXCOLOR LOSE_COLOR = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	const float START_LENGTH = 300.0f; // ��������
	const float END_LENGTH = 2000.0f; // �ڕW����

	//���f���̔z�u�ʒu
	const D3DXVECTOR3 CENTER = D3DXVECTOR3(0.0f, 0.0f, -2000.0f);
}

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
CResultScore *CResult::m_pResultScore = NULL;	// ���U���g�X�N���[���̃I�u�W�F�N�g
bool CResult::m_bAllArrival = false;		// �S�ē�����������

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CResult::CResult() :
	m_fLength(END_LENGTH),
	m_col(LOSE_COLOR),
	m_clear(false)
{
	// �l�̃N���A
	m_bAllArrival = false;	// �S�ē�����������
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CResult::~CResult()
{

}

//==========================================================================
// ����������
//==========================================================================
HRESULT CResult::Init(void)
{
	//�v���C���[�������Z�b�g
	CManager::GetInstance()->SetNumPlayer(0);

	// �N���A����̎擾
	m_clear = CGame::IsClearFrag();

	// ����������
	if (FAILED(CScene::Init()))
	{// ���s�����ꍇ
		return E_FAIL;
	}

	// BGM�Đ�
	CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_BGM_RESULT);

	// ���b�Z�[�W�𐶐�
	if (CGame::IsClearFrag())
	{

	}
	else
	{
		CMessageLose::Create();
		m_col = LOSE_COLOR;
	}

	// ����������
	Fog::Set(true);

	// �t�H�O�̒l��ݒ肷��
	Fog::SetStart(START_LENGTH);
	Fog::SetEnd(m_fLength);
	Fog::SetCol(m_col);

	// ���U���g���
	m_pResultScore = CResultScore::Create();

	// ����
	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CResult::Uninit(void)
{
	m_pResultScore = NULL;

	// �I������
	CScene::Uninit();
}

//==========================================================================
// �X�V����
//==========================================================================
void CResult::Update(void)
{
	if (m_clear)
	{
		CManager::GetInstance()->GetDebugProc()->Print(
			"���݂̃��[�h�F�y ���U���g : ���� �z\n\n");
	}
	else
	{
		CManager::GetInstance()->GetDebugProc()->Print(
			"���݂̃��[�h�F�y ���U���g : ���s �z\n\n");
	}

	// �L�[�{�[�h���擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �Q�[���p�b�h���擾
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	// ��ʑJ��
	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, 0) == true)
	{
		if (m_bAllArrival == true)
		{
			// ���[�h�ݒ�
			CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_TITLE);
		}

		if (CManager::GetInstance()->GetFade()->GetState() == CFade::STATE_NONE)
		{
			// �S�Ă̓�������
			if (m_pResultScore != NULL)
			{
				m_pResultScore->SetAllArrival();
			}
			m_bAllArrival = true;
		}
	}
}

//==========================================================================
// �`�揈��
//==========================================================================
void CResult::Draw(void)
{

}

//==========================================================================
// ���U���g�X�N���[���̏��擾
//==========================================================================
CResultScore *CResult::GetResultScore(void)
{
	return m_pResultScore;
}

//==========================================================================
// �����ݒ�ON
//==========================================================================
void CResult::SetEnableArrival(void)
{
	m_bAllArrival = true;
}
