//=============================================================================
// 
//  �x�񏈗� [emergency.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "emergency.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"
#include "object2D.h"
#include "calculation.h"
#include "game.h"
#include "gamemanager.h"
#include "input.h"
#include "fade.h"

//==========================================================================
// �萔��`
//==========================================================================
namespace
{
	const float TIME_EMERGENCY = 4.0f;				// �x�񎞊�
	const int NUM_FLASH = 3;						// �_�ŉ�
	const float TIME_SPAWN_MISSIONWINDOW = 0.2f;	// �~�b�V�����E�B���h�E�̏o������
	const float TIME_SPAWN_MISSIONTEXT = 0.5f;		// �~�b�V�����e�L�X�g�̏o������
	const float DEST_POSITION_SCROLLTEXT = -500.0f;	// �ړI�̃X�N���[���ʒu
	const char* TEXTURE_EMERGENCY = "data\\TEXTURE\\emergency\\emaergency_01.png";	// �x��̃e�N�X�`��
	const char* TEXTURE_MISSION = "data\\TEXTURE\\emergency\\mission_01.png";			// �~�b�V�����̃e�N�X�`��
	const char* TEXTURE_WINDOW = "data\\TEXTURE\\emergency\\window_02.png";			// �E�B���h�E�̃e�N�X�`��
	const char* TEXTURE_FRAME = "data\\TEXTURE\\emergency\\warning_02.png";			// �t���[���̃e�N�X�`��
}

//==========================================================================
// �֐����X�g
//==========================================================================
CEmergency::STATE_FUNC CEmergency::m_StateFuncList[] =
{
	&CEmergency::UpdateEmergency,	// �x��
	&CEmergency::UpdateWindow,		// �E�B���h�E
	&CEmergency::UpdateMission,		// �~�b�V����
	&CEmergency::UpdateEnd,	// �I��
};

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CEmergency::CEmergency(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_satate = STATE_EMERGENCY;	// ���
	m_bEndEmergency = false;	// �x�񂪏I�������
	m_fTime = 0.0f;				// �x�񎞊�
	m_pEmergencyFlash = nullptr;// �x�񎞓_��
	m_pEmergencyText = nullptr;	// �x��e�L�X�g
	m_pMissionText = nullptr;	// �~�b�V�����e�L�X�g
	m_pWindow = nullptr;		// �E�B���h�E
	memset(&m_pWarningFrame[0], NULL, sizeof(m_pWarningFrame));	// �x���̃t���[��
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CEmergency::~CEmergency()
{

}

//==========================================================================
// ��������
//==========================================================================
CEmergency *CEmergency::Create(void)
{
	// �����p�̃I�u�W�F�N�g
	CEmergency *pScore = nullptr;

	if (pScore == nullptr)
	{// nullptr��������

		// �������̊m��
		pScore = DEBUG_NEW CEmergency;

		if (pScore != nullptr)
		{// �������̊m�ۂ��o���Ă�����

			// ����������
			pScore->Init();
		}

		return pScore;
	}

	return nullptr;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CEmergency::Init(void)
{
	// ��ސݒ�
	SetType(CObject::TYPE_OBJECT2D);

	// �e�N�X�`���̃I�u�W�F�N�g�擾
	CTexture *pTexture = CManager::GetInstance()->GetTexture();
	int nIdxTex = 0;

	//==========================
	// �x�񎞓_��
	//==========================
	m_pEmergencyFlash = CObject2D::Create(7);
	m_pEmergencyFlash->SetType(CObject::TYPE_OBJECT2D);
	m_pEmergencyFlash->SetSize(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f));
	m_pEmergencyFlash->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f));
	m_pEmergencyFlash->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	//==========================
	// �x��e�L�X�g
	//==========================
	m_pEmergencyText = CObject2D::Create(7);
	m_pEmergencyText->SetType(CObject::TYPE_OBJECT2D);

	nIdxTex = pTexture->Regist(TEXTURE_EMERGENCY);
	m_pEmergencyText->BindTexture(nIdxTex);
	m_pEmergencyText->SetSize(pTexture->GetImageSize(nIdxTex) * 1.0f);
	m_pEmergencyText->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + m_pEmergencyText->GetSize().x, SCREEN_HEIGHT * 0.5f, 0.0f));
	m_pEmergencyText->SetOriginPosition(m_pEmergencyText->GetPosition());

	//==========================
	// �E�B���h�E
	//==========================
	m_pWindow = CObject2D::Create(7);
	m_pWindow->SetType(CObject::TYPE_OBJECT2D);

	nIdxTex = pTexture->Regist(TEXTURE_WINDOW);
	m_pWindow->BindTexture(nIdxTex);
	m_pWindow->SetSize(pTexture->GetImageSize(nIdxTex) * 0.5f);
	m_pWindow->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_pWindow->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	//==========================
	// �~�b�V�����e�L�X�g
	//==========================
	m_pMissionText = CObject2D::Create(7);
	m_pMissionText->SetType(CObject::TYPE_OBJECT2D);

	nIdxTex = pTexture->Regist(TEXTURE_MISSION);
	m_pMissionText->BindTexture(nIdxTex);
	m_pMissionText->SetSize(pTexture->GetImageSize(nIdxTex) * 5.0f);
	m_pMissionText->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_pMissionText->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	//==========================
	// �x���̃t���[��
	//==========================
	for (int i = 0; i < 2; i++)
	{
		m_pWarningFrame[i] = CObject2D::Create(7);
		m_pWarningFrame[i]->SetType(CObject::TYPE_OBJECT2D);

		nIdxTex = pTexture->Regist(TEXTURE_FRAME);
		m_pWarningFrame[i]->BindTexture(nIdxTex);
		m_pWarningFrame[i]->SetSize(pTexture->GetImageSize(nIdxTex) * 1.0f);
		m_pWarningFrame[i]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		float fAdjSize = -60.0f;

		if (i == 0)
		{
			m_pWarningFrame[i]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT - (m_pWarningFrame[i]->GetSize().y + fAdjSize), 0.0f));
		}
		else
		{
			m_pWarningFrame[i]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, m_pWarningFrame[i]->GetSize().y + fAdjSize, 0.0f));
		}
	}

	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CEmergency::Uninit(void)
{
	// ���폜
	Release();
}

//==========================================================================
// �X�V����
//==========================================================================
void CEmergency::Update(void)
{
	if (CManager::GetInstance()->GetFade()->GetState() != CFade::STATE_NONE)
	{
		return;
	}

	for (int i = 0; i < 2; i++)
	{
		if (m_pWarningFrame[i] == nullptr)
		{
			continue;
		}

		D3DXVECTOR2 *pTex = m_pWarningFrame[i]->GetTex();
		float fMove = 0.001f - 0.002f * i;

		for (int nTex = 0; nTex < 4; nTex++)
		{
			pTex[nTex].x += fMove;
		}
	}

	// ��ԕʏ���
	(this->*(m_StateFuncList[m_satate]))();
}

//==========================================================================
// �x��̍X�V
//==========================================================================
void CEmergency::UpdateEmergency(void)
{
	// ���ԉ��Z
	m_fTime += CManager::GetInstance()->GetDeltaTime();

	// �ʒu�擾
	D3DXVECTOR3 textpos = m_pEmergencyText->GetPosition();
	textpos.x = EasingLinear(m_pEmergencyText->GetOriginPosition().x, DEST_POSITION_SCROLLTEXT, m_fTime / TIME_EMERGENCY);
	m_pEmergencyText->SetPosition(textpos);

	// �_�ŏ���
	D3DXCOLOR flashcolor = m_pEmergencyFlash->GetColor();
	flashcolor.a = 0.5f * sinf(D3DX_PI * (m_fTime / (TIME_EMERGENCY / static_cast<float>(NUM_FLASH))) * 2.0f);
	float fAlpha = 0.2f * sinf(D3DX_PI * (m_fTime / (TIME_EMERGENCY * 0.3f))) + 0.8f;
	m_pEmergencyFlash->SetColor(flashcolor);
	m_pEmergencyText->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha));

	if (m_fTime >= TIME_EMERGENCY)
	{
		// �I������
		m_pEmergencyText->Uninit();
		m_pEmergencyText = nullptr;

		m_pEmergencyFlash->Uninit();
		m_pEmergencyFlash = nullptr;

		// ��ԑJ��
		m_satate = STATE_WINDOW;
		m_fTime = 0.0f;
	}

}

//==========================================================================
// �E�B���h�E�̍X�V
//==========================================================================
void CEmergency::UpdateWindow(void)
{
	// ���ԉ��Z
	m_fTime += CManager::GetInstance()->GetDeltaTime();

	D3DXCOLOR windowcolor = m_pWindow->GetColor();
	windowcolor.a = EasingLinear(0.0f, 1.0f, m_fTime / TIME_SPAWN_MISSIONWINDOW);
	m_pWindow->SetColor(windowcolor);

	for (int i = 0; i < 2; i++)
	{
		m_pWarningFrame[i]->SetColor(windowcolor);
	}

	if (m_fTime >= TIME_SPAWN_MISSIONWINDOW)
	{
		// ��ԑJ��
		m_satate = STATE_MISSION;
		m_fTime = 0.0f;
		m_pMissionText->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

//==========================================================================
// �~�b�V�����̍X�V
//==========================================================================
void CEmergency::UpdateMission(void)
{
	// ���ԉ��Z
	m_fTime += CManager::GetInstance()->GetDeltaTime();

	// �e�N�X�`���̃I�u�W�F�N�g�擾
	CTexture *pTexture = CManager::GetInstance()->GetTexture();
	D3DXVECTOR2 imagesize = pTexture->GetImageSize(m_pMissionText->GetIdxTexture()) * 0.5f;

	// �T�C�Y�X�V
	D3DXVECTOR2 size = m_pMissionText->GetSize();
	InertiaCorrection(size.x, imagesize.x, 0.25f);
	InertiaCorrection(size.y, imagesize.y, 0.25f);
	m_pMissionText->SetSize(size);

	if (m_fTime >= TIME_SPAWN_MISSIONTEXT)
	{
		// ��ԑJ��
		m_satate = STATE_END;
		m_fTime = 0.0f;
	}
}

//==========================================================================
// �I��
//==========================================================================
void CEmergency::UpdateEnd(void)
{
	// �L�[�{�[�h���擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �Q�[���p�b�h���擾
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, 0))
	{
		// �I������
		m_pWindow->Uninit();
		m_pWindow = nullptr;
		m_pMissionText->Uninit();
		m_pMissionText = nullptr;

		for (int i = 0; i < 2; i++)
		{
			m_pWarningFrame[i]->Uninit();
			m_pWarningFrame[i] = nullptr;
		}

		Uninit();

		CGame::GetGameManager()->SetType(CGameManager::SCENE_MAIN);
	}
}

//==========================================================================
// �`�揈��
//==========================================================================
void CEmergency::Draw(void)
{

}
