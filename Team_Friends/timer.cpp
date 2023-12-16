//=============================================================================
// 
//  �^�C�}�[���� [timer.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "timer.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"
#include "object2D.h"
#include "multinumber.h"
#include "fade.h"
#include "debugproc.h"
#include "calculation.h"

//==========================================================================
// �}�N����`
//==========================================================================
namespace
{
	const char* TEXTURE = "data\\TEXTURE\\number_blackclover_01.png";	// �e�N�X�`���̃t�@�C��
	const float TEX_U = 0.1f;			// U�̕���
	const float WIDTH = 50.0f;			// ����
	const float HEIGHT = 50.0f;			// �c��
	const float DIS_X = 50.0f;			// �Ԋu
	const int MAX_VALUE = 999999;		// �l�̍ő�l
	const int NUM_TIMER = 2;			// ����
	const int MAX_TIME = (60 * 99) * 1000;		// �^�C�}�[�̍ő吔
	const int START_TIME = 60 * 30;		// �^�C�}�[�̏����l
}

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CTimer::CTimer(int nPriority)
{
	// �l�̃N���A
	m_pMinutes = nullptr;		// ���̃I�u�W�F�N�g
	m_pSeconds = nullptr;		// �b�̃I�u�W�F�N�g
	m_pMilliSeconds = nullptr;	// �~���b�̃I�u�W�F�N�g
	m_fTime = 0.0f;				// ����
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CTimer::~CTimer()
{

}

//==========================================================================
// ��������
//==========================================================================
CTimer *CTimer::Create(void)
{
	// �����p�̃I�u�W�F�N�g
	CTimer *pScore = NULL;

	if (pScore == NULL)
	{// NULL��������

		// �������̊m��
		pScore = DEBUG_NEW CTimer;

		if (pScore != NULL)
		{// �������̊m�ۂ��o���Ă�����

			// ����������
			pScore->Init(mylib_const::DEFAULT_VECTOR3);
		}

		return pScore;
	}

	return NULL;
}

//==========================================================================
// ��������
//==========================================================================
CTimer *CTimer::Create(D3DXVECTOR3 pos)
{
	// �����p�̃I�u�W�F�N�g
	CTimer *pScore = NULL;

	if (pScore == NULL)
	{// NULL��������

		// �������̊m��
		pScore = DEBUG_NEW CTimer;

		if (pScore != NULL)
		{// �������̊m�ۂ��o���Ă�����

			// ����������
			pScore->Init(pos);
		}

		return pScore;
	}

	return NULL;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CTimer::Init(D3DXVECTOR3 pos)
{
	m_fTime = START_TIME * 1000.0f;	// ����

	// ��������
	D3DXVECTOR3 spawnpos = pos;
	m_pMinutes = CMultiNumber::Create(spawnpos, D3DXVECTOR2(WIDTH, HEIGHT), NUM_TIMER, CNumber::OBJECTTYPE_2D, TEXTURE, false);

	spawnpos.x += (WIDTH * NUM_TIMER) * 1.3f;
	m_pSeconds = CMultiNumber::Create(spawnpos, D3DXVECTOR2(WIDTH, HEIGHT), NUM_TIMER, CNumber::OBJECTTYPE_2D, TEXTURE, false);

	spawnpos.x += (WIDTH * NUM_TIMER) * 1.3f;
	m_pMilliSeconds = CMultiNumber::Create(spawnpos, D3DXVECTOR2(WIDTH, HEIGHT), NUM_TIMER, CNumber::OBJECTTYPE_2D, TEXTURE, false);

	// �l�̐ݒ菈��
	m_pMinutes->SetValue();
	m_pSeconds->SetValue();
	m_pMilliSeconds->SetValue();

	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CTimer::Uninit(void)
{
	// �����̃I�u�W�F�N�g�̏I������
	if (m_pMinutes != NULL)
	{
		m_pMinutes->Uninit();
		delete m_pMinutes;
		m_pMinutes = NULL;
	}
	if (m_pSeconds != NULL)
	{
		m_pSeconds->Uninit();
		delete m_pSeconds;
		m_pSeconds = NULL;
	}
	if (m_pMilliSeconds != NULL)
	{
		m_pMilliSeconds->Uninit();
		delete m_pMilliSeconds;
		m_pMilliSeconds = NULL;
	}
}

//==========================================================================
// �X�V����
//==========================================================================
void CTimer::Update(void)
{
	// ���Ԍ��Z
	m_fTime -= CManager::GetInstance()->GetDeltaTime() * 1000.0f;
	ValueNormalize(m_fTime, static_cast<float>(MAX_TIME), 0.0f);

	// ���A�b�A�~���b�̌v�Z
	int minutes = static_cast<int>(m_fTime) / (60 * 1000);
	int seconds = (static_cast<int>(m_fTime) % (60 * 1000)) / 1000;
	int milliseconds = static_cast<int>(m_fTime) % 1000;

	// �l�̐ݒ菈��
	if (m_pMinutes != NULL)
	{
		m_pMinutes->SetValue(minutes);
	}
	if (m_pSeconds != NULL)
	{
		m_pSeconds->SetValue(seconds);
	}
	if (m_pMilliSeconds != NULL)
	{
		m_pMilliSeconds->SetValue(milliseconds);
	}
	// �f�o�b�O�\��
	CManager::GetInstance()->GetDebugProc()->Print(
		"------------------[���ԁF%d���A%d�b�A%d]------------------\n", minutes, seconds, milliseconds);
}

//==========================================================================
// �`�揈��
//==========================================================================
void CTimer::Draw(void)
{

}
