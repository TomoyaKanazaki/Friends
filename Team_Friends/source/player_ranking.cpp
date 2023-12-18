//=============================================================================
// 
//  �v���C���[���� [player_title.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "game.h"
#include "player_ranking.h"
#include "manager.h"
#include "calculation.h"
#include "debugproc.h"
#include "input.h"
#include "model.h"
#include "motion.h"
#include "objectChara.h"
#include "shadow.h"
#include "player_union.h"
#include "ranking.h"

//==========================================
//  �萔��` : �������
//==========================================
namespace
{
	const char* CHARAFILE[CPlayerRanking::MAX] =
	{
		"data\\TEXT\\multicharacter\\BodytoLeg.txt", // ���̃t�@�C���p�X
		"data\\TEXT\\multicharacter\\BodytoArm.txt", // ���̃t�@�C���p�X
		"data\\TEXT\\multicharacter\\LegtoArm.txt", // ���̃t�@�C���p�X
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
	m_nStopCnt = 0;
	m_bRight = false;
	m_bLeft = false;
	m_bAtkMotion = false;
	m_bReMove = false;
	m_nTypeMove = PTN_NONE;
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
	m_nStopCnt = 0;
	m_bRight = false;
	m_bLeft = false;
	m_bAtkMotion = false;
	m_bReMove = false;
	m_nTypeMove = PTN_NONE;
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

	int i = Random(PTN_01, PTN_MAX);

	switch (i)
	{
	case PTN_01:
		m_nTypeMove = PTN_01;
		break;

	case PTN_02:
		m_nTypeMove = PTN_02;
		break;

	default:
		return S_OK;
	}


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

	switch (m_nTypeMove)
	{
	case PTN_01:
		MovePtn01();
		break;

	case PTN_02:
		MovePtn02();
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
// �w�i�L�����̍s���p�^�[��1
//==========================================================================
void CPlayerRanking::MovePtn01(void)
{
	m_nMovePtaCnt++;

	m_bOldLeft = m_bLeft;

	D3DXVECTOR3 pos = GetPosition();

	pos.x -= sinf(GetRotation().y) * 5;
	pos.z -= cosf(GetRotation().y) * 5;

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

	SetPosition(pos);
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

//==========================================================================
// �w�i�L�����̍s���p�^�[��2
//==========================================================================
void CPlayerRanking::MovePtn02(void)
{
	m_nMovePtaCnt++;

	D3DXVECTOR3 pos = GetPosition();

	D3DXVECTOR3 rot = GetRotation();

	// ���������n�߂�܂Œ�ʒu�Ŏ~�߂�
	if (m_nMovePtaCnt >= 60 * 5 && m_bReMove == false)
	{
		// �U�����[�V������Ɏ~�܂�b��
		if (m_nStopCnt <= 60 * 2)
		{
			rot.y -= 0.01f;

			// ���ʂ�����
			if (rot.y <= 0.0f)
			{
				rot.y = 0.0f;

				// �U�����[�V����
				for (int i = 0; i < PARTS_MAX; i++)
				{
					// ��񂾂�
					if (m_sMotionFrag[i].bATK == true || m_bAtkMotion == true)
					{
						m_sMotionFrag[i].bATK = false;
						m_bAtkMotion = true;
					}

					else
					{
						m_sMotionFrag[i].bATK = true;
					}

					if (m_pMotion[i] == NULL)
					{
						continue;
					}
				}

				// �U�����[�V�������I����
				if (m_bAtkMotion == true)
				{
					m_nStopCnt++;
				}
			}
		}

		else
		{
			rot.y += 0.01f;

			// ��������
			if (rot.y >= D3DX_PI / 2)
			{
				rot.y = D3DX_PI / 2;
				m_bReMove = true;
			}
		}

		// �ړ����[�V��������߂�
		for (int i = 0; i < PARTS_MAX; i++)
		{
			m_sMotionFrag[i].bMove = false;

			if (m_pMotion[i] == NULL)
			{
				continue;
			}
		}
	}

	else
	{
		pos.x -= sinf(GetRotation().y) * 5;
		pos.z -= cosf(GetRotation().y) * 5;

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

	SetPosition(pos);
	SetRotation(rot);
	
}
