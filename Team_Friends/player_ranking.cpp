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
#include "union_armtoarm.h"
#include "union_bodytoarm.h"
#include "union_bodytoleg.h"
#include "union_legtoarm.h"

//==========================================
//  �萔��` : �������
//==========================================
namespace
{
	const char* CHARAFILE[CPlayerRanking::MAX] =
	{
		"data\\TEXT\\multicharacter\\ArmtoArm.txt", // ���̃t�@�C���p�X
		"data\\TEXT\\multicharacter\\ArmtoArm.txt", // ���̃t�@�C���p�X
		"data\\TEXT\\multicharacter\\ArmtoArm.txt", // ���̃t�@�C���p�X
		"data\\TEXT\\multicharacter\\ArmtoArm.txt", // ���̃t�@�C���p�X
	};
}

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CPlayerRanking::CPlayerRanking(int nPriority) : CPlayerUnion(nPriority)
{
	// �l�̃N���A

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
HRESULT CPlayerRanking::Init(void)
{
	// ��ނ̐ݒ�
	SetType(TYPE_PLAYER);

	m_state = STATE_NONE;	// ���


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

	// �ߋ��̈ʒu�ۑ�
	SetOldPosition(GetPosition());

	// ���[�V�����X�V
	/*if (m_pMotion != NULL)
	{
		m_pMotion->Update();
	}*/


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
CPlayerRanking* CPlayerRanking::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL type)
{
	// �����p�̃I�u�W�F�N�g
	CPlayerRanking *pPlayer = NULL;

	if (pPlayer == NULL)
	{// NULL��������

	 // �������̊m��
		switch (type)
		{
		case TYPE_BODYtoLEG:
			pPlayer = DEBUG_NEW CUnion_BodytoLega;
			break;

		case TYPE_BODYtoARM:
			pPlayer = DEBUG_NEW CUnion_BodytoArma;
			break;

		case TYPE_LEGtoARM:
 			pPlayer = DEBUG_NEW CUnion_LegtoArma;
			break;

		case TYPE_ARMtoARM:
			pPlayer = DEBUG_NEW CUnion_ArntoArma;
			break;

		default:
			return NULL;
			break;
		}

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
