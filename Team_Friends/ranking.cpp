//=============================================================================
// 
//  �����L���O���� [ranking.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "renderer.h"
#include "calculation.h"
#include "debugproc.h"
#include "rankingscore.h"
#include "enemymanager.h"
#include "objectX.h"
#include "player_union.h"

//==========================================================================
// �}�N����`
//==========================================================================
#define PLAYER_CREATE_POSX				(1200.0f)		// �X�|�[��X���W
#define PLAYER_CREATE_POSY				(240.0f)		// �X�|�[��Y���W
#define PLAYER_DELETE_POSX				(-1200.0f)		// �f�X�|�[��X���W

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
int CRanking::m_nRandStage = 0;	// �X�e�[�W�̃����_���C���f�b�N�X�ԍ�
CRankingScore *CRanking::m_pRankingScore = NULL;	// �����L���O�X�R�A�̃I�u�W�F�N�g
CPlayerUnion *CRanking::m_pPlayerUnion = NULL;	//
bool CRanking::m_bAllArrival = false;		// �S�ē�����������
const char *CRanking::m_apModelFile = "data\\MODEL\\ranking_00.x";	// ���f���̃t�@�C��

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CRanking::CRanking()
{
	m_pRankingScore = NULL;	// �����L���O�X�R�A�̃I�u�W�F�N�g
	m_nCntSwitch = 0;		// �؂�ւ��̃J�E���^�[
	m_nCnt = 0;				// 
	m_bAllArrival = false;	// �S�ē�����������
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CRanking::~CRanking()
{

}

//==========================================================================
// ����������
//==========================================================================
HRESULT CRanking::Init(void)
{
	// �X�e�[�W�̃����_���C���f�b�N�X�ԍ�
	m_nRandStage = Random(1, 3);

	// ����������
	if (FAILED(CScene::Init()))
	{// ���s�����ꍇ
		return E_FAIL;
	}

	// ��������
	CObjectX *p = CObjectX::Create(m_apModelFile, D3DXVECTOR3(0.0f, 410.0f, 0.0f));
	p->SetType(CObject::TYPE_OBJECTX);

	// ���̃L�����̐���
	UniCharCreate(D3DXVECTOR3(PLAYER_CREATE_POSX, PLAYER_CREATE_POSY, 1300.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	// �����L���O�̃X�R�A����
	m_pRankingScore = CRankingScore::Create();

	// ����
	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CRanking::Uninit(void)
{
	// �����L���O�X�R�A�̃I�u�W�F�N�g
	m_pRankingScore = NULL;

	// �I������
	CScene::Uninit();
}

//==========================================================================
// �X�V����
//==========================================================================
void CRanking::Update(void)
{
	CManager::GetInstance()->GetDebugProc()->Print(
		"���݂̃��[�h�F�y�����L���O�z\n"
		"�؂�ւ��F�y F �z\n\n");

	// �L�[�{�[�h���擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �Q�[���p�b�h���擾
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	// �؂�ւ��̃J�E���^�[���Z
	m_nCntSwitch++;

	if (m_bAllArrival == true)
	{
		m_nCnt++;

		if (m_nCnt >= 60 * 2)
		{
			// ���[�h�ݒ�
			CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RANKING);

			m_nCnt = 60 * 2;
		}
	}

	// ���̃L�����̐���
	if (m_pPlayerUnion->GetPosition().x <= PLAYER_DELETE_POSX)
	{
		m_pPlayerUnion->Kill();
		m_pPlayerUnion->Uninit();
		UniCharCreate(D3DXVECTOR3(PLAYER_CREATE_POSX, PLAYER_CREATE_POSY, 1300.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));
	}	

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, 0) == true)
	{
		m_bAllArrival = true;
		m_nCnt = 60 * 2;
	}
}

//==========================================================================
// �`�揈��
//==========================================================================
void CRanking::Draw(void)
{

}

//==========================================================================
// �����ݒ�ON
//==========================================================================
void CRanking::SetEnableArrival(void)
{
	m_bAllArrival = true;
}

//==========================================================================
//���̃L�����̐���
//==========================================================================
void CRanking::UniCharCreate(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int i = Random(0, CPlayerRanking::MAX - 1);

	switch (i)
	{
	case CPlayerRanking::BODYtoLEG:
		m_nType = CPlayerRanking::BODYtoLEG;
		break;

	case CPlayerRanking::BODYtoARM:
		m_nType = CPlayerRanking::BODYtoARM;
		break;

	case CPlayerRanking::LEGtoARM:
		m_nType = CPlayerRanking::LEGtoARM;
		break;

	case CPlayerRanking::ARMtoARM:
		m_nType = CPlayerRanking::ARMtoARM;
		break;

	default:
		return;
	}

	m_pPlayerUnion = CPlayerRanking::Create(pos, rot, m_nType);
}

//==========================================================================
// �����ݒ�ON
//==========================================================================
CPlayerUnion *CRanking::GetPlayerUnion(void)
{
	return m_pPlayerUnion;
}
