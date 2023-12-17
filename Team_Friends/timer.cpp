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
#include "game.h"
#include "gamemanager.h"

//==========================================================================
// �萔��`
//==========================================================================
namespace
{
	const char* TEXTURE = "data\\TEXTURE\\number\\degital_01.png";	// �e�N�X�`���̃t�@�C��
	const char* TEXTURE_WINDOW = "data\\TEXTURE\\timerwindow.png";		// �E�B���h�E�e�N�X�`���̃t�@�C��
	const D3DXVECTOR3 DEST_POSITION = D3DXVECTOR3(1100.0f, 100.0f, 0.0f);
	const float START_RATIO = 4.5;			// ��������
	const float DEST_RATIO_WINDOW = 0.1f;	// �ڕW�̃E�B���h�E����
	const float WIDTH = 25.0f;			// ����
	const float HEIGHT = 25.0f;			// �c��
	const float DIS_RATIO_Y = 0.3f;			// Y�̊Ԋu
	const int NUM_TIMER = 2;			// ����
	const int MAX_TIME = 60 * 99;		// �^�C�}�[�̍ő吔
	const int START_TIME = 60 * 30;		// �^�C�}�[�̏����l
	const float TIME_APPEARANCE = 0.7f;	// �o������
	const float TIME_ADDLITTLE = 2.0f;	// �������Z����
	const float TIME_ADJUSTMENT = 0.5f;	// ��������
}

//==========================================================================
// �֐����X�g
//==========================================================================
CTimer::STATE_FUNC CTimer::m_StateFuncList[] =
{
	&CTimer::StateWait,			// �ҋ@
	&CTimer::StatAppearance,	// �o��
	&CTimer::StatAddLittle,		// �������Z
	&CTimer::StateAdjustment,	// ����
};

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CTimer::CTimer(int nPriority)
{
	// �l�̃N���A
	m_state = STATE_WAIT;		// ���
	m_fStateTime = 0.0f;		// ��Ԏ���
	m_fTime = 0.0f;				// ����
	m_pos = mylib_const::DEFAULT_VECTOR3;	// �ʒu
	m_posOrigin = mylib_const::DEFAULT_VECTOR3;	// ���̈ʒu
	m_pTimerWindow = nullptr;	// �^�C�}�[�̃E�B���h�E
	m_pMinutes = nullptr;		// ���̃I�u�W�F�N�g
	m_pSeconds = nullptr;		// �b�̃I�u�W�F�N�g
	m_pMilliSeconds = nullptr;	// �~���b�̃I�u�W�F�N�g
	m_bAddTime = false;			// �^�C�}�[���Z�̃t���O
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

	// �e��ϐ�������
	m_pos = pos;
	m_posOrigin = m_pos;	// ���̈ʒu
	m_fTime = START_TIME * 1000.0f;	// ����
	m_state = STATE_WAIT;			// ���
	m_bAddTime = false;			// �^�C�}�[���Z�̃t���O
	D3DXCOLOR setcolor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	// �E�B���h�E�̐���
	m_pTimerWindow = CObject2D::Create(8);
	m_pTimerWindow->SetType(CObject::TYPE_OBJECT2D);

	int nIdxTex = CManager::GetInstance()->GetTexture()->Regist(TEXTURE_WINDOW);
	m_pTimerWindow->BindTexture(nIdxTex);
	m_pTimerWindow->SetSize(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f) * 0.8f);
	m_pTimerWindow->SetSizeOrigin(m_pTimerWindow->GetSize());
	m_pTimerWindow->SetColor(setcolor);
	m_pTimerWindow->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	m_pTimerWindow->SetOriginPosition(m_pTimerWindow->GetPosition());

	// ��������
	D3DXVECTOR3 spawnpos = m_pos;
	spawnpos.y += m_pTimerWindow->GetSize().y * DIS_RATIO_Y;

	spawnpos.x -= (WIDTH  * START_RATIO * NUM_TIMER) * 1.3f;
	m_pMinutes = CMultiNumber::Create(spawnpos, D3DXVECTOR2(WIDTH, HEIGHT) * START_RATIO, NUM_TIMER, CNumber::OBJECTTYPE_2D, TEXTURE, false);
	m_pMinutes->SetSizeOrigin(m_pMinutes->GetSize());

	spawnpos.x += (WIDTH * START_RATIO * NUM_TIMER) * 1.3f;
	m_pSeconds = CMultiNumber::Create(spawnpos, D3DXVECTOR2(WIDTH, HEIGHT) * START_RATIO, NUM_TIMER, CNumber::OBJECTTYPE_2D, TEXTURE, false);
	m_pSeconds->SetSizeOrigin(m_pSeconds->GetSize());

	spawnpos.x += (WIDTH * START_RATIO * NUM_TIMER) * 1.3f;
	m_pMilliSeconds = CMultiNumber::Create(spawnpos, D3DXVECTOR2(WIDTH, HEIGHT) * START_RATIO, NUM_TIMER, CNumber::OBJECTTYPE_2D, TEXTURE, false);
	m_pMilliSeconds->SetSizeOrigin(m_pMilliSeconds->GetSize());

	// �l�̐ݒ菈��
	m_pMinutes->SetValue();
	m_pSeconds->SetValue();
	m_pMilliSeconds->SetValue();

	// �F�ݒ�
	m_pMinutes->SetColor(setcolor);
	m_pSeconds->SetColor(setcolor);
	m_pMilliSeconds->SetColor(setcolor);


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
	// ��ԕʏ���
	(this->*(m_StateFuncList[m_state]))();

	if (!m_bAddTime)
	{
		return;
	}

	// ���Ԍ��Z
	m_fTime -= CManager::GetInstance()->GetDeltaTime() * 1000.0f;
	ValueNormalize(m_fTime, static_cast<float>(MAX_TIME * 1000), 0.0f);

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
// �ҋ@���
//==========================================================================
void CTimer::StateWait(void)
{
	// ���ԃ��Z�b�g
	m_fStateTime = 0.0f;
}

//==========================================================================
// �o�����
//==========================================================================
void CTimer::StatAppearance(void)
{
	// ���ԉ��Z
	m_fStateTime += CManager::GetInstance()->GetDeltaTime();

	D3DXCOLOR windowcolor = m_pTimerWindow->GetColor();
	windowcolor.a = EasingLinear(0.0f, 1.0f, m_fStateTime / TIME_APPEARANCE);
	m_pTimerWindow->SetColor(windowcolor);
	m_pMinutes->SetColor(windowcolor);
	m_pSeconds->SetColor(windowcolor);
	m_pMilliSeconds->SetColor(windowcolor);

	if (m_fStateTime >= TIME_APPEARANCE)
	{
		// ��ԑJ��
		m_state = STATE_ADD_LITTLE;
		m_fStateTime = 0.0f;

		// �^�C�}�[��i�߂�
		m_bAddTime = true;
	}
}

//==========================================================================
// �������Z���
//==========================================================================
void CTimer::StatAddLittle(void)
{
	// ���ԉ��Z
	m_fStateTime += CManager::GetInstance()->GetDeltaTime();

	if (m_fStateTime >= TIME_ADDLITTLE)
	{
		// ��ԑJ��
		m_state = STATE_ADJ;
		m_fStateTime = 0.0f;
		CGame::GetGameManager()->SetType(CGameManager::SCENE_MAIN);
	}
}

//==========================================================================
// �������
//==========================================================================
void CTimer::StateAdjustment(void)
{
	// ���ԉ��Z
	m_fStateTime += CManager::GetInstance()->GetDeltaTime();

	m_pos.x = EasingLinear(m_posOrigin.x, DEST_POSITION.x, m_fStateTime / TIME_ADJUSTMENT);
	m_pos.y = EasingLinear(m_posOrigin.y, DEST_POSITION.y, m_fStateTime / TIME_ADJUSTMENT);

	D3DXVECTOR3 setpos = m_pos;
	setpos.y += m_pTimerWindow->GetSize().y * DIS_RATIO_Y;

	D3DXVECTOR2 numbersize = m_pMinutes->GetSize();

	// �T�C�Y�␳
	numbersize.x = EasingLinear(m_pMinutes->GetSizeOrigin().x, WIDTH, m_fStateTime / TIME_ADJUSTMENT);
	numbersize.y = EasingLinear(m_pMinutes->GetSizeOrigin().y, HEIGHT, m_fStateTime / TIME_ADJUSTMENT);

	setpos.x -= (numbersize.x * NUM_TIMER) * 1.3f;
	m_pMinutes->SetPosition(setpos);

	setpos.x += (numbersize.x * NUM_TIMER) * 1.3f;
	m_pSeconds->SetPosition(setpos);

	setpos.x += (numbersize.x * NUM_TIMER) * 1.3f;
	m_pMilliSeconds->SetPosition(setpos);

	m_pMinutes->SetSize(numbersize);
	m_pSeconds->SetSize(numbersize);
	m_pMilliSeconds->SetSize(numbersize);


	D3DXVECTOR2 windowsize = m_pTimerWindow->GetSize();

	CTexture *pTex = CManager::GetInstance()->GetTexture();
	windowsize.x = EasingLinear(m_pTimerWindow->GetSizeOrigin().x, pTex->GetImageSize(m_pTimerWindow->GetIdxTexture()).x * DEST_RATIO_WINDOW, m_fStateTime / TIME_ADJUSTMENT);
	windowsize.y = EasingLinear(m_pTimerWindow->GetSizeOrigin().y, pTex->GetImageSize(m_pTimerWindow->GetIdxTexture()).y * DEST_RATIO_WINDOW, m_fStateTime / TIME_ADJUSTMENT);
	m_pTimerWindow->SetSize(windowsize);
	
	
	D3DXVECTOR3 windowpos = m_pTimerWindow->GetPosition();
	windowpos.x = EasingLinear(m_pTimerWindow->GetOriginPosition().x, DEST_POSITION.x, m_fStateTime / TIME_ADJUSTMENT);
	windowpos.y = EasingLinear(m_pTimerWindow->GetOriginPosition().y, DEST_POSITION.y, m_fStateTime / TIME_ADJUSTMENT);
	m_pTimerWindow->SetPosition(windowpos);

	if (m_fStateTime >= TIME_ADJUSTMENT)
	{
		// ��ԑJ��
		m_state = STATE_WAIT;
		m_fStateTime = 0.0f;
	}
}

//==========================================================================
// �`�揈��
//==========================================================================
void CTimer::Draw(void)
{

}
