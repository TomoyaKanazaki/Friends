//==========================================
// 
//  �l���I�����j���[(decide_menu.cpp)
//  Author : Tomoya Kanazaki
// 
//==========================================
#include "decide_menu.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "object2D.h"
#include "calculation.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "debugproc.h"
#include "fog.h"
#include "player_title.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 POS_UI = D3DXVECTOR3(0.0f, 1000.0f, 0.0f); // UI�̈ʒu
	const D3DXVECTOR3 POS_WALL = D3DXVECTOR3(0.0f, 0.0f, 100.0f); // �ǂ̈ʒu
	const D3DXCOLOR COLOR_WALL = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f); // �ǂ̐F
	const float SIZE_WALL = 1.0f; // �ǂ̃T�C�Y�{��
	const int ALPHATIME = 60; // �s�����x�X�V�̎���
	const D3DXVECTOR3 POS_SELECT = D3DXVECTOR3(0.0f, 30.0f, 0.0f); // �I�����̊�ʒu
	const float LENGTH_SELECT = 150.0f; // �I�����̊�ʒu
	const float SCALE_SELECT = 0.15f; // �I�����̔{��

	// �e�N�X�`���̃t�@�C��
	const char* m_apTextureFile[CDecideMenu::VTX_MAX] =
	{
		"data\\TEXTURE\\decideplayer_text.png",
		"data\\TEXTURE\\cyberwall_02.png"
	};

	// �e�N�X�`���̃t�@�C��
	const char* m_apTextureFile_Select[CDecideMenu::VTXSELECT_MAX] =
	{
		"data\\TEXTURE\\decideplayer_select01.png",
		"data\\TEXTURE\\decideplayer_select02.png",
		"data\\TEXTURE\\decideplayer_select03.png",
		"data\\TEXTURE\\decideplayer_select04.png",
	};
}

//==========================================
//  �R���X�g���N�^
//==========================================
CDecideMenu::CDecideMenu(int nPriority) : CObject(nPriority),
	m_nCntAlpha(0),
	m_nNowSelect(0)
{
	memset(&m_pObj3D[0], NULL, sizeof(m_pObj3D)); // �I�u�W�F�N�g2D�̃I�u�W�F�N�g
	memset(&m_pSelect3D[0], NULL, sizeof(m_pSelect3D)); // �I�����̃I�u�W�F�N�g
	memset(&m_nTexIdx[0], 0, sizeof(m_nTexIdx)); // �e�N�X�`���̃C���f�b�N�X�ԍ�
	memset(&m_nTexIdx_Select[0], 0, sizeof(m_nTexIdx_Select)); // �e�N�X�`���̃C���f�b�N�X�ԍ�

	// �v���C���[�|�C���^�̏�����
	for (int nCnt = 0; nCnt < VTXSELECT_MAX; ++nCnt)
	{
		m_apPlayer[nCnt] = nullptr;
	}
}

//==========================================
//  �f�X�g���N�^
//==========================================
CDecideMenu::~CDecideMenu()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CDecideMenu::Init(void)
{
	// ��ނ̐ݒ�
	SetType(TYPE_OBJECT3D);

	// UI�̐���
	//CreateUI();

	// �I��Ώۂ̐���
	CreateSelect();

	// �v���C���[�̐���
	CretePlayer();

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CDecideMenu::Uninit(void)
{
	for (int nCntSelect = 0; nCntSelect < VTX_MAX; nCntSelect++)
	{
		if (m_pObj3D[nCntSelect] != NULL)
		{// NULL����Ȃ�������

			// �I������
			m_pObj3D[nCntSelect] = NULL;
		}
	}

	for (int nCntSelect = 0; nCntSelect < VTXSELECT_MAX; nCntSelect++)
	{
		if (m_pSelect3D[nCntSelect] != NULL)
		{// NULL����Ȃ�������

			// �I������
			m_pSelect3D[nCntSelect] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < VTXSELECT_MAX; ++nCnt)
	{
		if (m_apPlayer[nCnt] != nullptr)
		{
			m_apPlayer[nCnt] = nullptr;
		}
	}

	// ���폜
	Release();
}

//==========================================
//  �X�V����
//==========================================
void CDecideMenu::Update(void)
{
	for (int nCntSelect = 0; nCntSelect < VTX_MAX; nCntSelect++)
	{
		if (m_pObj3D[nCntSelect] == NULL)
		{// NULL��������
			continue;
		}

		// ���_���ݒ�
		m_pObj3D[nCntSelect]->SetVtx();
	}

	for (int nCntSelect = 0; nCntSelect < VTXSELECT_MAX; nCntSelect++)
	{
		if (m_pSelect3D[nCntSelect] == NULL)
		{// NULL��������
			continue;
		}

		// �I�����̍X�V����
		UpdateSelect(nCntSelect);

		// ���_���ݒ�
		m_pSelect3D[nCntSelect]->SetVtx();
	}

	if (CManager::GetInstance()->GetFade()->GetState() != CFade::STATE_NONE)
	{// �t�F�[�h���͔�����
		return;
	}


	// �L�[�{�[�h���擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �Q�[���p�b�h���擾
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	// ���݂̑I�����X�V
	if ((pInputGamepad->GetStickSelect(CInputGamepad::STICK_X) == false && pInputGamepad->GetStickMoveL(0).x < 0) ||
		(pInputKeyboard->GetTrigger(DIK_A) == true || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_LEFT, 0)))
	{// ��

		// ���X�e�B�b�N�̔����n��
		pInputGamepad->SetEnableStickSelect(true, CInputGamepad::STICK_X);

		// �p�^�[��No.���X�V
		m_nNowSelect = (m_nNowSelect + (VTXSELECT_MAX - 1)) % VTXSELECT_MAX;

		// �T�E���h�Đ�
		CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_CURSOR);

		// �J�E���^�[���Z�b�g
		m_nCntAlpha = 0;
	}
	else if (pInputGamepad->GetStickSelect(CInputGamepad::STICK_X) == false && pInputGamepad->GetStickMoveL(0).x > 0 ||
		(pInputKeyboard->GetTrigger(DIK_D) == true || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_RIGHT, 0)))
	{// �E

		// ���X�e�B�b�N�̔����n��
		pInputGamepad->SetEnableStickSelect(true, CInputGamepad::STICK_X);

		// �p�^�[��No.���X�V
		m_nNowSelect = (m_nNowSelect + 1) % VTXSELECT_MAX;

		// �T�E���h�Đ�
		CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_CURSOR);

		// �J�E���^�[���Z�b�g
		m_nCntAlpha = 0;
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, 0))
	{// ���肪�����ꂽ
		CManager::GetInstance()->SetNumPlayer(m_nNowSelect + 1);

		// �Q�[���ɑJ�ڂ���
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_GAME);

		return;
	}

	// �f�o�b�O�\��
	CManager::GetInstance()->GetDebugProc()->Print
	(
		"�I��l�� : %d\n\n", m_nNowSelect + 1
	);

#ifdef _DEBUG
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_LSHIFT))
	{
		Go(VTXSELECT_SELECT1P);
	}
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RSHIFT))
	{
		Back(VTXSELECT_SELECT1P);
	}
#endif
}

//==========================================
//  �`�揈��
//==========================================
void CDecideMenu::Draw(void)
{

}

//==========================================
//  ��������
//==========================================
CDecideMenu* CDecideMenu::Create(void)
{
	// �����p�̃I�u�W�F�N�g
	CDecideMenu* pTitleScreen = NULL;

	if (pTitleScreen == NULL)
	{// NULL��������

		// �������̊m��
		pTitleScreen = DEBUG_NEW CDecideMenu;

		if (pTitleScreen != NULL)
		{// �������̊m�ۂ��o���Ă�����

			// ����������
			pTitleScreen->Init();
		}

		return pTitleScreen;
	}

	return NULL;
}

//==========================================
//  �I�����̍X�V����
//==========================================
void CDecideMenu::UpdateSelect(int nCntSelect)
{
	// �F�擾
	D3DXCOLOR col = m_pSelect3D[nCntSelect]->GetColor();

	// �s�����x�X�V
	if (m_nNowSelect == nCntSelect)
	{
		CuadricCurveComp(col.a, ALPHATIME, 0.3f, 1.0f, m_nCntAlpha);
	}
	else
	{
		col.a = 1.0f;
	}

	// �F�ݒ�
	m_pSelect3D[nCntSelect]->SetColor(col);
}

//==========================================
//  UI�̐���
//==========================================
void CDecideMenu::CreateUI(void)
{
	// �e�N�X�`���̃I�u�W�F�N�g�擾
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	for (int nCntSelect = 0; nCntSelect < VTX_MAX; nCntSelect++)
	{
		// ��������
		switch (nCntSelect)
		{
		case VTX_TEXT:
			m_pObj3D[nCntSelect] = CObject3D::Create(8);
			break;
		case VTX_WALL:
			m_pObj3D[nCntSelect] = CObject3D::Create(7);
			break;
		}

		// ��ނ̐ݒ�
		m_pObj3D[nCntSelect]->SetType(TYPE_OBJECT3D);

		// �e�N�X�`���̊��蓖��
		m_nTexIdx[nCntSelect] = pTexture->Regist(m_apTextureFile[nCntSelect]);

		// �e�N�X�`���̊��蓖��
		m_pObj3D[nCntSelect]->BindTexture(m_nTexIdx[nCntSelect]);

		// �T�C�Y�擾
		D3DXVECTOR3 size = pTexture->GetImageSize(m_nTexIdx[nCntSelect]);

		// �e��ϐ��̏�����
		switch (nCntSelect)
		{
		case VTX_TEXT:
			size.z = 0.0f;
			m_pObj3D[nCntSelect]->SetSize(size * 0.4f);	// �T�C�Y
			m_pObj3D[nCntSelect]->SetPosition(POS_UI);	// �ʒu
			m_pObj3D[nCntSelect]->SetColor(mylib_const::DEFAULT_COLOR);	// �F
			break;
		case VTX_WALL:
			size.z = 0.0f;
			m_pObj3D[nCntSelect]->SetSize(size * SIZE_WALL);	// �T�C�Y
			m_pObj3D[nCntSelect]->SetPosition(POS_WALL);	// �ʒu
			m_pObj3D[nCntSelect]->SetColor(COLOR_WALL);	// �F
			break;
		}
	}
}

//==========================================
//  �I��Ώۂ̐���
//==========================================
void CDecideMenu::CreateSelect(void)
{
	// �e�N�X�`���̃I�u�W�F�N�g�擾
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	for (int nCntSelect = 0; nCntSelect < VTXSELECT_MAX; nCntSelect++)
	{
		// ��������
		m_pSelect3D[nCntSelect] = CObject3D::Create(8);

		// ��ނ̐ݒ�
		m_pSelect3D[nCntSelect]->SetType(TYPE_OBJECT3D);

		// �e�N�X�`���̊��蓖��
		m_nTexIdx_Select[nCntSelect] = pTexture->Regist(m_apTextureFile_Select[nCntSelect]);

		// �e�N�X�`���̊��蓖��
		m_pSelect3D[nCntSelect]->BindTexture(m_nTexIdx_Select[nCntSelect]);

		// �T�C�Y�ݒ�
		D3DXVECTOR3 size = pTexture->GetImageSize(m_nTexIdx_Select[nCntSelect]) * SCALE_SELECT;
		size.z = 0.0f;
		m_pSelect3D[nCntSelect]->SetSize(size); // �T�C�Y

		// �ʒu�ݒ�
		D3DXVECTOR3 pos = POS_SELECT;
		pos.x -= 1.5f * LENGTH_SELECT;
		pos.x += LENGTH_SELECT * nCntSelect;
		m_pSelect3D[nCntSelect]->SetPosition(pos);

		// �F�ݒ�
		m_pSelect3D[nCntSelect]->SetColor(mylib_const::DEFAULT_COLOR);
	}
}

//==========================================
//  �v���C���[�̐���
//==========================================
void CDecideMenu::CretePlayer(void)
{
	// �v���C���[�̐���
	m_apPlayer[VTXSELECT_SELECT1P] = CPlayerTitle::Create(m_pSelect3D[VTXSELECT_SELECT1P]->GetPosition(), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_apPlayer[VTXSELECT_SELECT2P] = CPlayerTitle::Create(m_pSelect3D[VTXSELECT_SELECT2P]->GetPosition(), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_apPlayer[VTXSELECT_SELECT3P] = CPlayerTitle::Create(m_pSelect3D[VTXSELECT_SELECT3P]->GetPosition(), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_apPlayer[VTXSELECT_SELECT4P] = CPlayerTitle::Create(m_pSelect3D[VTXSELECT_SELECT4P]->GetPosition(), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//==========================================
//  �i��
//==========================================
void CDecideMenu::Go(int Idx)
{
	m_apPlayer[Idx]->SetTarget(m_pSelect3D[Idx]->GetPosition() + D3DXVECTOR3(0.0f, 0.0f, 300.0f), m_pSelect3D[Idx]->GetPosition());
}

//==========================================
//  �߂�
//==========================================
void CDecideMenu::Back(int Idx)
{
	m_apPlayer[Idx]->SetTarget(m_pSelect3D[Idx]->GetPosition(), m_pSelect3D[Idx]->GetPosition() + D3DXVECTOR3(0.0f, 0.0f, 300.0f));
}
