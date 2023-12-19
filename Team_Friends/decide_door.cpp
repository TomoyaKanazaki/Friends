//==========================================
// 
//  �l���I�����j���[(decide_menu.cpp)
//  Author : Tomoya Kanazaki
// 
//==========================================
#include "decide_door.h"
#include "decide_menu.h"
#include "manager.h"
#include "renderer.h"
#include "calculation.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "debugproc.h"
#include "objectX.h"
#include "player_title.h"

//==========================================
//  �O���錾
//==========================================
class CPlayerTitle;

//==========================================
//  �萔��`
//==========================================
namespace
{
	const int GATE_TARGET = 300;	// �s�����x�X�V�̎���
	const int GATE_GRACE = 1;		// �v���C���[�̍��W
	const int GATE_FIXED = 30;		// �I�����̔{��
	const float FRAME_POS_Z = 250.0f;		// �I�����̊�ʒu
	const float LENGTH_SELECT = 197.5f;		// �I�����̊�ʒu
	const float PLAYER_SPEED = 5.0f;		// �v���C���[�̈ړ���
	const char *m_apModelFile_fream = "data\\MODEL\\gate\\gate_frame.x";
	const char *m_apModelFile_door = "data\\MODEL\\gate\\gate_door.x";
}

//==========================================
//  �R���X�g���N�^
//==========================================
CDecideDoor::CDecideDoor(int nPriority) : CObject(nPriority),
m_nNowSelect(0),
m_nOldSelect(0)
{
	memset(&m_pSelectX[0], NULL, sizeof(m_pSelectX)); // �I�����̃I�u�W�F�N�g
	memset(&m_n[0], 0, sizeof(m_n)); // �Q�[�g�̊J�P�\�J�E���g
	memset(&m_nGate[0], 0, sizeof(m_nGate)); // �Q�[�g�̊J�J�E���g
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
	//CreateSelect();

	m_pObjX[VTX_FREAM] = CObjectX::Create(m_apModelFile_fream, D3DXVECTOR3(0.0f, 0.0f, FRAME_POS_Z));
	m_pObjX[VTX_FREAM]->SetType(CObject::TYPE_OBJECTX);

	for (int nCnt = 0; nCnt < MODELSELECT_MAX; nCnt++)
	{
		// �ʒu�ݒ�
		float posX = 0.0f;
		posX -= 1.5f * LENGTH_SELECT;
		posX += LENGTH_SELECT * nCnt;

		m_pSelectX[nCnt] = CObjectX::Create(m_apModelFile_door, D3DXVECTOR3(posX, 0.0f, FRAME_POS_Z));
		m_pSelectX[nCnt]->SetType(CObject::TYPE_OBJECTX);

		if (nCnt <= m_nNowSelect)
		{
			m_nGate[nCnt] = 0;
		}

		else
		{
			m_nGate[nCnt] = 60;
		}
	}

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CDecideDoor::Uninit(void)
{
	for (int nCntSelect = 0; nCntSelect < VTX_MAX; nCntSelect++)
	{
		if (m_pObjX[nCntSelect] != NULL)
		{// NULL����Ȃ�������

		 // �I������
			m_pObjX[nCntSelect] = NULL;
		}
	}

	for (int nCntSelect = 0; nCntSelect < MODELSELECT_MAX; nCntSelect++)
	{
		if (m_pSelectX[nCntSelect] != NULL)
		{// NULL����Ȃ�������

		 // �I������
			m_pSelectX[nCntSelect] = NULL;
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
	if (CManager::GetInstance()->GetFade()->GetState() != CFade::STATE_NONE)
	{// �t�F�[�h���͔�����
		return;
	}

	// �Q�[�g�̊J������̕ϐ�
	int nOpAndClo = 0;

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

		// ���݂̑I������ۑ�
		m_nOldSelect = m_nNowSelect;

		// �p�^�[��No.���X�V
		m_nNowSelect = (m_nNowSelect + (MODELSELECT_MAX - 1)) % MODELSELECT_MAX;


		// �ЂƂO�̑I���������݂̑I������菭�Ȃ�
		if (m_nOldSelect <= m_nNowSelect)
		{
			// �Q�[�g�̊J���������
			nOpAndClo = m_nNowSelect - m_nOldSelect;

			for (int nCnt = nOpAndClo; nCnt > 0; --nCnt)
			{
				// �Q�[�g�̊J�J�E���g�𐳋K��
				m_nGate[nCnt] = GATE_FIXED - m_nGate[nCnt];
			}
		}

		else
		{
			// �Q�[�g�̊J���������
			nOpAndClo = m_nOldSelect - m_nNowSelect;

			for (int nCnt = 0; nCnt < nOpAndClo; ++nCnt)
			{
				// �Q�[�g�̊J�J�E���g�𐳋K��
				m_nGate[m_nOldSelect + nCnt] = GATE_FIXED - m_nGate[m_nOldSelect + nCnt];
			}
		}
	}
	else if (pInputGamepad->GetStickSelect(CInputGamepad::STICK_X) == false && pInputGamepad->GetStickMoveL(0).x > 0 ||
		(pInputKeyboard->GetTrigger(DIK_D) == true || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_RIGHT, 0)))
	{// �E

	 // ���X�e�B�b�N�̔����n��
		pInputGamepad->SetEnableStickSelect(true, CInputGamepad::STICK_X);

		// ���݂̑I������ۑ�
		m_nOldSelect = m_nNowSelect;

		// �p�^�[��No.���X�V
		m_nNowSelect = (m_nNowSelect + 1) % MODELSELECT_MAX;


		// �ЂƂO�̑I���������݂̑I������葽��
		if (m_nOldSelect >= m_nNowSelect)
		{
			// �Q�[�g�̊J���������
			nOpAndClo = m_nOldSelect - m_nNowSelect;

			for (int nCnt = nOpAndClo; nCnt > 0; --nCnt)
			{
				// �Q�[�g�̊J�J�E���g�𐳋K��
				m_nGate[nCnt] = GATE_FIXED - m_nGate[nCnt];
			}
		}

		else
		{
			// �Q�[�g�̊J���������
			nOpAndClo = m_nNowSelect - m_nOldSelect;

			for (int nCnt = 0; nCnt < nOpAndClo; ++nCnt)
			{
				// �Q�[�g�̊J�J�E���g�𐳋K��
				m_nGate[m_nNowSelect + nCnt] = GATE_FIXED - m_nGate[m_nNowSelect + nCnt];
			}
		}
	}


	// �ړ�
	for (int nCnt = 0; nCnt < MODELSELECT_MAX; ++nCnt)
	{
		if (nCnt <= m_nNowSelect)
		{
			m_nGate[nCnt]++;

			// �����ŊJ����
			float posY = EasingLinear(0.0f, GATE_TARGET, m_nGate[nCnt] / GATE_FIXED);

			// �ʒu��ݒ�
			m_pSelectX[nCnt]->SetPosition(D3DXVECTOR3(m_pSelectX[nCnt]->GetPosition().x,
				posY,
				m_pSelectX[nCnt]->GetPosition().z));

			m_n[nCnt] = 0;
		}

		else
		{
			// �I����ʂ̃v���C���[���擾
			CPlayerTitle *p = CDecideMenu::GetPlayerTitle(nCnt);

			// �v���C���[�̈ʒu�����ʒu�ȏゾ�����瑦�߂�
			if (p->GetPosition().z >= FRAME_POS_Z)
			{
				m_n[nCnt] = 60 * GATE_GRACE;
			}

			// �߂�܂ŗP�\��������
			m_n[nCnt]++;

			if (m_n[nCnt] >= 60 * GATE_GRACE)
			{
				m_nGate[nCnt]++;

				// �����ŕ߂�
				float posY = EasingLinear(GATE_TARGET, 0.0f, m_nGate[nCnt] / GATE_FIXED);

				// �ʒu��ݒ�
				m_pSelectX[nCnt]->SetPosition(D3DXVECTOR3(m_pSelectX[nCnt]->GetPosition().x,
					posY,
					m_pSelectX[nCnt]->GetPosition().z));

				// �P�\�J�E���g���Œ�
				m_n[nCnt] = 60 * GATE_GRACE;
			}
		}

		// �J�J�E���g�����ȏ�
		if (m_nGate[nCnt] >= GATE_FIXED)
		{
			// �J�J�E���g���Œ�
			m_nGate[nCnt] = GATE_FIXED;
		}
	}
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