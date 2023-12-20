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
#include "number.h"

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
	const float LAMP_POS_Y = 280.0f; // �����v��Y���W
	const float LAMP_POS_Z = 200.0f; // �����v��Z���W
	const float LENGTH_SELECT = 192.0f; // �����v��k�Ԋu
	const float SCALE_SELECT = 0.15f; // �I�����̔{��
	const float PLAYER_SPEED = 5.0f; // �v���C���[�̈ړ���
	const float PLAYER_TARGET = 500.0f; // �v���C���[�̍��W
	const float TEX_U = 0.1f; // U�̕���
	const float NUMBER_UI_POS_X = -140.5f; // ������UI��X���W
	const float NUMBER_UI_POS_Y = 415.0f; // ������UI��Y���W
	const float NUMBER_UI_POS_Z = 200.0f; // ������UI��Z���W
	const float NUMBER_UI_SCALE = 0.15f; // ������UI�̔{��

	const float ELECBORAD_UI_POS_X = 10.0f; // �d���f����UI��X���W
	const float ELECBORAD_UI_POS_Y = -10.0f; // ������UI����ɓd���f����UI��Y���W
	const float ELECBORAD_UI_SCALE = 0.35f; // �d���f����UI�̔{��


	const char* m_apTextureFile_Number = "data\\TEXTURE\\number\\degital_01.png";
	const char* m_apTextureFile_Elecborad = "data\\TEXTURE\\number\\gowait.png";

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
	memset(&m_pNumber3D[0], NULL, sizeof(m_pNumber3D)); // �I�u�W�F�N�g2D�̃I�u�W�F�N�g
	memset(&m_pElecboard3D[0], NULL, sizeof(m_pElecboard3D)); // �I�u�W�F�N�g2D�̃I�u�W�F�N�g
	memset(&m_pObj3D[0], NULL, sizeof(m_pObj3D)); // �I�u�W�F�N�g2D�̃I�u�W�F�N�g
	memset(&m_pSelectX[0], NULL, sizeof(m_pSelectX)); // �I�����̃I�u�W�F�N�g
	m_pDecideDoor = nullptr;	// �h�A�̃I�u�W�F�N�g
	m_nTexIdx_Select = 0;

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

	CreateNumber();

	CreateElecboard();

	// �h�A����
	m_pDecideDoor = CDecideDoor::Create();

	for (int nCnt = 0; nCnt < VTX_MAX; nCnt++)
	{
		SetValue(m_nNowSelect + 1);
	}

	return S_OK;
}

//==========================================================================
//  �I������
//==========================================================================
void CDecideMenu::Uninit(void)
{
	for (int nCntSelect = 0; nCntSelect < VTX_MAX; nCntSelect++)
	{
		if (m_pNumber3D[nCntSelect] != NULL)
		{// NULL����Ȃ�������

		 // �I������
			m_pNumber3D[nCntSelect]->Uninit();
			delete m_pNumber3D[nCntSelect];
			m_pNumber3D[nCntSelect] = NULL;
		}
	}

	for (int nCntSelect = 0; nCntSelect < VTX_MAX; nCntSelect++)
	{
		if (m_pElecboard3D[nCntSelect] != NULL)
		{// NULL����Ȃ�������

		 // �I������
			m_pElecboard3D[nCntSelect] = NULL;
		}
	}

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
		if (m_pNumber3D[nCntSelect] == NULL)
		{// NULL��������
			continue;
		}

		// �l�̐ݒ菈��
		for (int nCnt = 0; nCnt < VTX_MAX; nCnt++)
		{
			SetValue(m_nNowSelect + 1);
		}

		// ���_���ݒ�
		m_pNumber3D[nCntSelect]->SetVtx();
	}

	for (int nCntSelect = 0; nCntSelect < VTX_MAX; nCntSelect++)
	{
		if (m_pElecboard3D[nCntSelect] == NULL)
		{// NULL��������
			continue;
		}

		// ���_���ݒ�
		m_pElecboard3D[nCntSelect]->SetVtx();
	}

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
	if ((pInputGamepad->GetStickSelect(CInputGamepad::STICK_X) == false && pInputGamepad->GetStickMoveL(0).y < 0) ||
		(pInputKeyboard->GetTrigger(DIK_S) == true || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_LEFT, 0)))
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
	else if (pInputGamepad->GetStickSelect(CInputGamepad::STICK_X) == false && pInputGamepad->GetStickMoveL(0).y > 0 ||
		(pInputKeyboard->GetTrigger(DIK_W) == true || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_RIGHT, 0)))
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
	pos.z -= 30.0f;

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
		pos.y += LAMP_POS_Y;
		pos.z += LAMP_POS_Z;
		m_pSelectX[nCntSelect]->SetPosition(pos);

		// �F�ݒ�
		m_pSelectX[nCntSelect]->SetColor(mylib_const::DEFAULT_COLOR);
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

		pos.y -= LAMP_POS_Y;
		
		// �����ʒu��␳
		pos.z = PLAYER_TARGET;

		// ����
		m_apPlayer[nCnt] = CPlayerTitle::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
}

//==========================================================================
//  �I��Ώۂ̐���
//==========================================================================
void CDecideMenu::CreateNumber(void)
{

	for (int nCntSelect = 0; nCntSelect < VTX_MAX; nCntSelect++)
	{
		// ��������
		m_pNumber3D[nCntSelect] = CNumber::Create(CNumber::OBJECTTYPE_3D, 8);

		switch (nCntSelect)
		{
		case VTX_TEXT:

			// �e�N�X�`���̊��蓖��
			m_nTexIdx_Number = CManager::GetInstance()->GetTexture()->Regist(m_apTextureFile_Number);

			m_pNumber3D[nCntSelect]->BindTexture(m_nTexIdx_Number);

			m_pNumber3D[nCntSelect]->SetSize3D(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx_Number).x / 10 * NUMBER_UI_SCALE,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx_Number).y * NUMBER_UI_SCALE,
				0.0f));

		default:
			break;
		}

		// �ʒu�ݒ�
		D3DXVECTOR3 pos = POS_SELECT;
		pos.x += NUMBER_UI_POS_X;
		pos.y += NUMBER_UI_POS_Y;
		pos.z += NUMBER_UI_POS_Z;
		m_pNumber3D[nCntSelect]->SetPosition(pos);

		// �F�ݒ�
		m_pNumber3D[nCntSelect]->SetColor(mylib_const::DEFAULT_COLOR);

		// ��ނ̐ݒ�
		m_pNumber3D[nCntSelect]->SetType(TYPE_OBJECT3D);
	}
}

//==========================================================================
//  �I��Ώۂ̐���
//==========================================================================
void CDecideMenu::CreateElecboard(void)
{

	for (int nCntSelect = 0; nCntSelect < VTX_UI_MAX; nCntSelect++)
	{
		// ��������
		m_pElecboard3D[nCntSelect] = CObject3D::Create(8);

		// �e�N�X�`���̊��蓖��
		m_nTexIdx_Elecborad[nCntSelect] = CManager::GetInstance()->GetTexture()->Regist(m_apTextureFile_Elecborad);

		m_pElecboard3D[nCntSelect]->BindTexture(m_nTexIdx_Elecborad[nCntSelect]);

		switch (nCntSelect)
		{
		case VTX_UI_ELECBORAD:
			m_pElecboard3D[nCntSelect]->SetSize(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx_Elecborad[nCntSelect]).x * ELECBORAD_UI_SCALE,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx_Elecborad[nCntSelect]).y * ELECBORAD_UI_SCALE,
				0.0f));

		default:
			break;
		}

		// �ʒu�ݒ�
		D3DXVECTOR3 pos = POS_SELECT;
		pos.x += ELECBORAD_UI_POS_X;
		pos.y += NUMBER_UI_POS_Y + ELECBORAD_UI_POS_Y;
		pos.z += NUMBER_UI_POS_Z;
		m_pElecboard3D[nCntSelect]->SetPosition(pos);

		// �F�ݒ�
		m_pElecboard3D[nCntSelect]->SetColor(mylib_const::DEFAULT_COLOR);

		// ��ނ̐ݒ�
		m_pElecboard3D[nCntSelect]->SetType(TYPE_OBJECT3D);
	}
}

//==========================================================================
//  �I��Ώۂ̐���
//==========================================================================
void CDecideMenu::SetValue(int nNowPlayer)
{
	for (int nCntSelect = 0; nCntSelect < VTX_MAX; nCntSelect++)
	{
		// �e�N�X�`���|�C���^�擾
		D3DXVECTOR2 *pTex = m_pNumber3D[nCntSelect]->GetTex();

		// �e�N�X�`�����W�̐ݒ�
		pTex[0] = D3DXVECTOR2(nNowPlayer * TEX_U, 0.0f);
		pTex[1] = D3DXVECTOR2(nNowPlayer * TEX_U + TEX_U, 0.0f);
		pTex[2] = D3DXVECTOR2(nNowPlayer * TEX_U, 1.0f);
		pTex[3] = D3DXVECTOR2(nNowPlayer * TEX_U + TEX_U, 1.0f);

		// ���_�ݒ�
		m_pNumber3D[nCntSelect]->SetVtx();
	}
}

//==========================================================================
//  �v���C���[�̐���
//==========================================================================
CPlayerTitle *CDecideMenu::GetPlayerTitle(int Cnt)
{
	return m_apPlayer[Cnt];
}
