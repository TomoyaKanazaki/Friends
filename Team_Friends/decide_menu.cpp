//==========================================================================
// 
//  �l���I�����j���[(decide_menu.cpp)
//  Author : ���{ ����
// 
//==========================================================================
#include "decide_menu.h"
#include "decide_door.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "object2D.h"
#include "objectX.h"
#include "calculation.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "debugproc.h"
#include "fog.h"
#include "player_title.h"
#include "3D_effect.h"

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
CPlayerTitle *CDecideMenu::m_apPlayer[VTXSELECT_MAX] = {};					// �}�l�[�W���̃I�u�W�F�N�g

//==========================================================================
//  �萔��`
//==========================================================================
namespace
{
	const D3DXVECTOR3 POS_UI = D3DXVECTOR3(0.0f, 1000.0f, 0.0f); // UI�̈ʒu
	const int ALPHATIME = 60; // �s�����x�X�V�̎���
	const D3DXVECTOR3 POS_SELECT = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // �I�����̊�ʒu
	const float UI_POS_Y = 280.0f; // �I�����̊�ʒu
	const float UI_POS_Z = 200.0f; // �I�����̊�ʒu
	const float LENGTH_SELECT = 192.0f; // �I�����̊�ʒu
	const float SCALE_SELECT = 0.15f; // �I�����̔{��
	const float PLAYER_SPEED = 5.0f; // �v���C���[�̈ړ���
	const float PLAYER_TARGET = 500.0f; // �v���C���[�̍��W

	// �e�N�X�`���̃t�@�C��
	const char* m_apModelFile_Select = "data\\MODEL\\gate\\gate_lamp.x";
}

//==========================================================================
//  �R���X�g���N�^
//==========================================================================
CDecideMenu::CDecideMenu(int nPriority) : CObject(nPriority),
	m_nCntAlpha(0),
	m_nNowSelect(0)
{
	memset(&m_pObj3D[0], NULL, sizeof(m_pObj3D)); // �I�u�W�F�N�g2D�̃I�u�W�F�N�g
	memset(&m_pSelectX[0], NULL, sizeof(m_pSelectX)); // �I�����̃I�u�W�F�N�g
	memset(&m_nTexIdx[0], 0, sizeof(m_nTexIdx)); // �e�N�X�`���̃C���f�b�N�X�ԍ�
	memset(&m_nTexIdx_Select[0], 0, sizeof(m_nTexIdx_Select)); // �e�N�X�`���̃C���f�b�N�X�ԍ�
	memset(&KeepSize[0], 0, sizeof(KeepSize)); // �e�N�X�`���̃C���f�b�N�X�ԍ�
	m_pDecideDoor = nullptr;	// �h�A�̃I�u�W�F�N�g

	// �v���C���[�|�C���^�̏�����
	for (int nCnt = 0; nCnt < VTXSELECT_MAX; ++nCnt)
	{
		m_apPlayer[nCnt] = nullptr;
	}
}

//==========================================================================
//  �f�X�g���N�^
//==========================================================================
CDecideMenu::~CDecideMenu()
{

}

//==========================================================================
//  ����������
//==========================================================================
HRESULT CDecideMenu::Init(void)
{
	// ��ނ̐ݒ�
	SetType(TYPE_OBJECT3D);

	// �I��Ώۂ̐���
	CreateSelect();

	// �v���C���[�̐���
	CretePlayer();

	// �h�A����
	m_pDecideDoor = CDecideDoor::Create();

	return S_OK;
}

//==========================================================================
//  �I������
//==========================================================================
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
		if (m_pSelectX[nCntSelect] != NULL)
		{// NULL����Ȃ�������

			// �I������
			m_pSelectX[nCntSelect] = NULL;
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

//==========================================================================
//  �X�V����
//==========================================================================
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
		if (m_pSelectX[nCntSelect] == NULL)
		{// NULL��������
			continue;
		}

		// �I�����̍X�V����
		UpdateSelect(nCntSelect);

		// ���_���ݒ�
		m_pSelectX[nCntSelect]->SetVtx();
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

		// �I�����ݒ�
		if (m_pDecideDoor != nullptr)
		{
			m_pDecideDoor->SetSelect(m_nNowSelect);
		}

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

		// �I�����ݒ�
		if (m_pDecideDoor != nullptr)
		{
			m_pDecideDoor->SetSelect(m_nNowSelect);
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, 0))
	{// ���肪�����ꂽ
		CManager::GetInstance()->SetNumPlayer(m_nNowSelect + 1);

		// �Q�[���ɑJ�ڂ���
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_GAME);

		return;
	}

	// �ړ�
	for (int nCnt = 0; nCnt < VTXSELECT_MAX; ++nCnt)
	{
		if (nCnt <= m_nNowSelect)
		{
			if (m_apPlayer[nCnt]->GetPosition().z != 0.0f)
			{
				Go(nCnt);
			}
		}
		else
		{
			if (m_apPlayer[nCnt]->GetPosition().z != PLAYER_TARGET)
			{
				Back(nCnt);
			}
		}
	}

	// �f�o�b�O�\��
	CManager::GetInstance()->GetDebugProc()->Print
	(
		"�I��l�� : %d\n\n", m_nNowSelect + 1
	);

#ifdef _DEBUG
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_LSHIFT))
	{
		Go(0);
	}
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RSHIFT))
	{
		Back(0);
	}
#endif
}

//==========================================================================
//  �`�揈��
//==========================================================================
void CDecideMenu::Draw(void)
{

}

//==========================================================================
//  �O�ɐi�ޏ���
//==========================================================================
void CDecideMenu::Go(int nIdx)
{
	// �l���擾
	D3DXVECTOR3 move = m_apPlayer[nIdx]->GetMove();

	// �l����
	move.z = -PLAYER_SPEED;

	// �l��K�p
	m_apPlayer[nIdx]->SetMove(move);
}

//==========================================================================
//  ���ɉ����鏈��
//==========================================================================
void CDecideMenu::Back(int nIdx)
{
	// �l���擾
	D3DXVECTOR3 move = m_apPlayer[nIdx]->GetMove();

	// �l����
	move.z = PLAYER_SPEED;

	// �l��K�p
	m_apPlayer[nIdx]->SetMove(move);

	// �ړI�n��ݒ�
	m_apPlayer[nIdx]->SetTarget(PLAYER_TARGET);
}

//==========================================================================
//  ��������
//==========================================================================
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

//==========================================================================
//  �I�����̍X�V����
//==========================================================================
void CDecideMenu::UpdateSelect(int nCntSelect)
{
	// �F
	D3DXCOLOR col = mylib_const::DEFAULT_COLOR;

	if (m_nNowSelect >= nCntSelect)
	{
		col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	}
	else
	{
		col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}

	D3DXVECTOR3 pos = m_pSelectX[nCntSelect]->GetPosition();
	pos.z -= 20.0f;

	for (int i = 0; i < 4; i++)
	{
		CEffect3D::Create(
			pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			col, 200.0f, 2, CEffect3D::MOVEEFFECT_NONE, CEffect3D::TYPE_POINT);
	}
}

//==========================================================================
//  �I��Ώۂ̐���
//==========================================================================
void CDecideMenu::CreateSelect(void)
{
	// �e�N�X�`���̃I�u�W�F�N�g�擾
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	for (int nCntSelect = 0; nCntSelect < VTXSELECT_MAX; nCntSelect++)
	{
		// ��������
		m_pSelectX[nCntSelect] = CObjectX::Create(m_apModelFile_Select);

		// ��ނ̐ݒ�
		m_pSelectX[nCntSelect]->SetType(TYPE_OBJECTX);

		// �ʒu�ݒ�
		D3DXVECTOR3 pos = POS_SELECT;
		pos.x -= 1.5f * LENGTH_SELECT;
		pos.x += LENGTH_SELECT * nCntSelect;
		pos.y += UI_POS_Y;
		pos.z += UI_POS_Z;
		m_pSelectX[nCntSelect]->SetPosition(pos);

		// �F�ݒ�
		/*if (nCntSelect <= m_nNowSelect)
		{*/
		m_pSelectX[nCntSelect]->SetColor(mylib_const::DEFAULT_COLOR);
		/*}

		else
		{
			m_pSelect3D[nCntSelect]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}*/
	}
}

//==========================================================================
//  �v���C���[�̐���
//==========================================================================
void CDecideMenu::CretePlayer(void)
{
	// �v���C���[�̐���
	for (int nCnt = 0; nCnt < VTXSELECT_MAX; ++nCnt)
	{
		// UI�̈ʒu���擾����
		D3DXVECTOR3 pos = m_pSelectX[nCnt]->GetPosition();

		pos.y -= UI_POS_Y;
		
		// �����ʒu��␳
		pos.z = PLAYER_TARGET;

		// ����
		m_apPlayer[nCnt] = CPlayerTitle::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
}

//==========================================================================
//  �v���C���[�̐���
//==========================================================================
CPlayerTitle *CDecideMenu::GetPlayerTitle(int Cnt)
{
	return m_apPlayer[Cnt];
}
