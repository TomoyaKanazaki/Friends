//=============================================================================
// 
//  �v���C���[���� [player_title.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "game.h"
#include "player_ranking.h"
#include "manager.h"
#include "debugproc.h"
#include "input.h"
#include "model.h"
#include "motion.h"
#include "objectChara.h"
#include "shadow.h"
#include "player_union.h"

//==========================================
//  �萔��` : �������
//==========================================
namespace
{
	const char* CHARAFILE[CPlayerRanking::MAX] =
	{
		//"data\\TEXT\\multicharacter\\BodytoLeg.txt", // ���̃t�@�C���p�X
		//"data\\TEXT\\multicharacter\\BodytoArm.txt", // ���̃t�@�C���p�X
		//"data\\TEXT\\multicharacter\\LegtoArm.txt", // ���̃t�@�C���p�X
		"data\\TEXT\\multicharacter\\ArmtoArm.txt", // ���̃t�@�C���p�X
		"data\\TEXT\\multicharacter\\ArmtoArm.txt", // ���̃t�@�C���p�X
		"data\\TEXT\\multicharacter\\ArmtoArm.txt", // ���̃t�@�C���p�X
		"data\\TEXT\\multicharacter\\ArmtoArm.txt", // ���̃t�@�C���p�X
	};
}

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CPlayerRanking::CPlayerRanking(int nPriority)
{
	// �l�̃N���A
	m_nMovePtaCnt = 0;
	m_nSpinCnt = 0;
	m_bRight = false;
	m_bLeft = false;
}

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CPlayerRanking::CPlayerRanking(MODEL nType, int nPriority)
{
	// �l�̃N���A
	m_nType = nType;
	m_nMovePtaCnt = 0;
	m_nSpinCnt = 0;
	m_bRight = false;
	m_bLeft = false;
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CPlayerRanking::~CPlayerRanking()
{

}
//==========================================================================
// ����������
//==========================================================================
HRESULT CPlayerRanking::Init()
{
	// ��ނ̐ݒ�
	SetType(TYPE_PLAYER);

	// �L�����쐬
	CreateParts();


	//// ���[�V�����̐�������
	//m_pMotion = CMotion::Create(CHARAFILE[BODYtoLEG]);

	//// �I�u�W�F�N�g�L�����N�^�[�̏��擾
	//CObjectChara *pObjChar = GetObjectChara();

	//// ���[�V�����̐ݒ�
	//m_pMotion->SetModel(pObjChar->GetModel(), pObjChar->GetNumModel(), CObjectChara::GetObjectChara());

	// ���f���̍����ւ�
	/*switch (m_nModelType)
	{
	case PLAYER_BODY:
		SetEvolusion(CGameManager::STATUS_LIFE);
		break;

	case PLAYER_ARM:
		SetEvolusion(CGameManager::STATUS_POWER);
		break;

	case PLAYER_LEG:
		SetEvolusion(CGameManager::STATUS_SPEED);
		break;

	default:
		break;
	}*/

	// �|�[�Y�̃��Z�b�g
	//m_pMotion->ResetPose(MOTION_DEF);
	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CPlayerRanking::Uninit(void)
{
	// �I������
	CPlayerUnion::Uninit();
}

//==========================================================================
// �X�V����
//==========================================================================
void CPlayerRanking::Update(void)
{
	if (IsDeath() == true)
	{
		return;
	}

	CPlayerUnion::Update();

	// �ߋ��̈ʒu�ۑ�
	SetOldPosition(GetPosition());

	switch (m_nType)
	{
	case CPlayerRanking::BODYtoLEG:
		ARMtoARMMove();
		break;

	case CPlayerRanking::BODYtoARM:
		ARMtoARMMove();
		break;

	case CPlayerRanking::LEGtoARM:
		ARMtoARMMove();
		break;

	case CPlayerRanking::ARMtoARM:
		ARMtoARMMove();
		break;

	default:
		return;
	}
}

//==========================================================================
// �`�揈��
//==========================================================================
void CPlayerRanking::Draw(void)
{
	// �`�揈��
	CPlayerUnion::Draw();
}

//==========================================
//  �������� : �������
//==========================================
CPlayerUnion* CPlayerRanking::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL type)
{
	// �����p�̃I�u�W�F�N�g
	CPlayerUnion *pPlayer = NULL;

	if (pPlayer == NULL)
	{// NULL��������
	 
		pPlayer = DEBUG_NEW CPlayerRanking(type);

		if (pPlayer != NULL)
		{// �������̊m�ۂ��o���Ă�����

		 // �v���C���[�C���f�b�N�X�ԍ�
		 //pPlayer->m_nMyPlayerIdx = nIdx;

		 // ����������
			pPlayer->Init();

			// �l��ۑ�
			pPlayer->SetPosition(pos);
			pPlayer->SetRotation(rot);
		}

	}

	return pPlayer;
}

//==========================================================================
// �p�[�c�̐ݒ�
//==========================================================================
HRESULT CPlayerRanking::CreateParts(void)
{

	// �����L�����ǂݍ���
	ReadMultiCharacter(CHARAFILE[m_nType]);

	return S_OK;
}

//==========================================================================
// �p�[�c�̐ݒ�
//==========================================================================
void CPlayerRanking::ARMtoARMMove(void)
{
	m_nMovePtaCnt++;

	m_bOldLeft = m_bLeft;

	D3DXVECTOR3 pos = GetPosition();

	pos.x -= sinf(GetRotation().y) * 5;
	pos.z -= cosf(GetRotation().y) * 5;

	SetPosition(pos);

	D3DXVECTOR3 rot = GetRotation();

	if (m_nMovePtaCnt >= 60 * 5 && m_nSpinCnt < 3)
	{
		rot.y -= 0.04f;

		//
		if (rot.y <= -D3DX_PI / 2 && m_bRight == true)
		{
			rot.y = -D3DX_PI / 2;
			m_nCntSwitch = 0;
			m_bRight = false;
		}

		else if (rot.y <= D3DX_PI / 2 && m_bLeft == true)
		{
			rot.y = D3DX_PI / 2;
			m_nCntSwitch = 0;
			m_bLeft = false;
		}


		//
		if (rot.y >= D3DX_PI)
		{
			rot.y = -D3DX_PI;
		}

		else if (rot.y <= -D3DX_PI)
		{
			rot.y = D3DX_PI;
			m_bRight = true;
			m_bLeft = true;
		}

		if (m_bLeft == false && m_bOldLeft== true)
		{
			m_nSpinCnt++;
		}
	}

	SetRotation(rot);

	// �ړ����ɂ���
	for (int i = 0; i < PARTS_MAX; i++)
	{
		m_sMotionFrag[i].bMove = true;

		if (m_pMotion[i] == NULL)
		{
			continue;
		}
	}
}
