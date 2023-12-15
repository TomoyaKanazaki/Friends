//==========================================
// 
//  �l���I�����j���[(decide_menu.cpp)
//  Author : Tomoya Kanazaki
// 
//==========================================
#include "decide_door.h"
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
	const int ALPHATIME = 60; // �s�����x�X�V�̎���
	const D3DXVECTOR3 POS_SELECT = D3DXVECTOR3(0.0f, 30.0f, 0.0f); // �I�����̊�ʒu
	const float LENGTH_SELECT = 150.0f; // �I�����̊�ʒu
	const float SCALE_SELECT = 0.15f; // �I�����̔{��
	const float PLAYER_SPEED = 5.0f; // �v���C���[�̈ړ���
	const float PLAYER_TARGET = 500.0f; // �v���C���[�̍��W
	const char *m_apModelFile_fream = "data\\MODEL\\gate\\gate_frame.x";
	const char *m_apModelFile_door = "data\\MODEL\\gate\\gate_door.x";
}

//==========================================
//  �R���X�g���N�^
//==========================================
CDecideDoor::CDecideDoor(int nPriority) : CObject(nPriority),
m_nNowSelect(0)
{
	memset(&m_pObjX[0], NULL, sizeof(m_pObjX)); // �I�u�W�F�N�g2D�̃I�u�W�F�N�g
	memset(&m_pSelectX[0], NULL, sizeof(m_pSelectX)); // �I�����̃I�u�W�F�N�g
	memset(&m_nTexIdx_Select[0], 0, sizeof(m_nTexIdx_Select)); // �e�N�X�`���̃C���f�b�N�X�ԍ�
}

//==========================================
//  �f�X�g���N�^
//==========================================
CDecideDoor::~CDecideDoor()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CDecideDoor::Init(void)
{
	// ��ނ̐ݒ�
	SetType(TYPE_OBJECT3D);

	// �I��Ώۂ̐���
	CreateSelect();

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CDecideDoor::Uninit(void)
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

	// ���폜
	Release();
}

//==========================================
//  �X�V����
//==========================================
void CDecideDoor::Update(void)
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
		Go(0);
	}
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RSHIFT))
	{
		Back(0);
	}
#endif
}

//==========================================
//  �`�揈��
//==========================================
void CDecideDoor::Draw(void)
{

}

//==========================================
//  ��������
//==========================================
CDecideDoor* CDecideDoor::Create(void)
{
	// �����p�̃I�u�W�F�N�g
	CDecideDoor* pTitleScreen = NULL;

	if (pTitleScreen == NULL)
	{// NULL��������

	 // �������̊m��
		pTitleScreen = DEBUG_NEW CDecideDoor;

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
void CDecideDoor::UpdateSelect(int nCntSelect)
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
//  �I��Ώۂ̐���
//==========================================
void CDecideDoor::CreateSelect(void)
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