//=============================================================================
// 
//  �G���A�������� [limitarea.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "limitarea.h"
#include "limitereamanager.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "calculation.h"
#include "debugproc.h"
#include "player.h"
#include "game.h"


//==========================================================================
// �����l�[���X�y�[�X
//==========================================================================
namespace
{
	const char* TEXTURE_DEFAULT = "data\\TEXTURE\\cyberwall_03.png";	// �f�t�H���g�e�N�X�`��
	const float MAX_ALPHA = 0.3f;	// �ő�s�����x
	const float TIME_APPEARANCE = 0.5f;	// �o������
	const float TIME_FADEOUT = 0.5f;	// �t�F�[�h�A�E�g����
}

//==========================================================================
// �֐����X�g
//==========================================================================
CLimitArea::STATE_FUNC CLimitArea::m_StateFuncList[] =
{
	&CLimitArea::StateNone,			// �ʏ�
	&CLimitArea::StateAppearance,	// �o�����
	&CLimitArea::StateFadeout,		// �t�F�[�h�A�E�g
};

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CLimitArea::CLimitArea(int nPriority) : CObject(nPriority)
{
	m_state = STATE_NONE;			// ���
	m_fTimeState = 0.0f;			// ��ԃJ�E���^�[
	m_nIdxEreaManager = 0;			// �G���A�����}�l�[�W���̃C���f�b�N�X�ԍ�
	memset(&m_pMeshWall[0], NULL, sizeof(m_pMeshWall));			// ���b�V���E�H�[���̃I�u�W�F�N�g
	memset(&m_sLimitEreaInfo, NULL, sizeof(m_sLimitEreaInfo));	// �G���A�������
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CLimitArea::~CLimitArea()
{

}

//==========================================================================
// ��������
//==========================================================================
CLimitArea *CLimitArea::Create(sLimitEreaInfo info)
{
	// �����p�̃I�u�W�F�N�g
	CLimitArea *pObjMeshField = NULL;

	if (pObjMeshField == NULL)
	{// NULL��������

		// �������̊m��
		pObjMeshField = DEBUG_NEW CLimitArea;

		if (pObjMeshField != NULL)
		{// �������̊m�ۂ��o���Ă�����

			// �G���A�������
			pObjMeshField->m_sLimitEreaInfo = info;

			// ����������
			pObjMeshField->Init();
		}

		return pObjMeshField;
	}

	return NULL;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CLimitArea::Init(void)
{

	// ��ސݒ�
	SetType(TYPE_ELEVATION);

	// ���蓖��
	m_nIdxEreaManager = CGame::GetLimitEreaManager()->Regist(this);

	// �e��ϐ�������
	D3DXVECTOR3 WallPos[mylib_const::SHAPE_LIMITEREA];
	float fWidthLen[mylib_const::SHAPE_LIMITEREA];

	// ��
	WallPos[0] = D3DXVECTOR3(
		(m_sLimitEreaInfo.fMinX + m_sLimitEreaInfo.fMaxX) * 0.5f,
		0.0f,
		m_sLimitEreaInfo.fMaxZ);
	fWidthLen[0] = GetPosLength(D3DXVECTOR3(m_sLimitEreaInfo.fMinX, 0.0f, 0.0f), D3DXVECTOR3(m_sLimitEreaInfo.fMaxX, 0.0f, 0.0f));

	// �E
	WallPos[1] = D3DXVECTOR3(
		m_sLimitEreaInfo.fMinX,
		0.0f,
		(m_sLimitEreaInfo.fMinZ + m_sLimitEreaInfo.fMaxZ) * 0.5f);
	fWidthLen[1] = GetPosLength(D3DXVECTOR3(m_sLimitEreaInfo.fMinZ, 0.0f, 0.0f), D3DXVECTOR3(m_sLimitEreaInfo.fMaxZ, 0.0f, 0.0f));

	// ��O
	WallPos[2] = D3DXVECTOR3(
		(m_sLimitEreaInfo.fMinX + m_sLimitEreaInfo.fMaxX) * 0.5f,
		0.0f,
		m_sLimitEreaInfo.fMinZ);
	fWidthLen[2] = GetPosLength(D3DXVECTOR3(m_sLimitEreaInfo.fMinX, 0.0f, 0.0f), D3DXVECTOR3(m_sLimitEreaInfo.fMaxX, 0.0f, 0.0f));

	// ��
	WallPos[3] = D3DXVECTOR3(
		m_sLimitEreaInfo.fMaxX,
		0.0f,
		(m_sLimitEreaInfo.fMinZ + m_sLimitEreaInfo.fMaxZ) * 0.5f);
	fWidthLen[3] = GetPosLength(D3DXVECTOR3(m_sLimitEreaInfo.fMinZ, 0.0f, 0.0f), D3DXVECTOR3(m_sLimitEreaInfo.fMaxZ, 0.0f, 0.0f));

	float fRot = (D3DX_PI * 2.0f) / (float)mylib_const::SHAPE_LIMITEREA;
	int nBlock = 4;
	for (int i = 0; i < mylib_const::SHAPE_LIMITEREA; i++)
	{
		m_pMeshWall[i] = CMeshWall::Create(WallPos[i], D3DXVECTOR3(0.0f, D3DX_PI + fRot * i, 0.0f), fWidthLen[i] / (float)nBlock, fWidthLen[i] / (float)nBlock, nBlock, 1, 7, TEXTURE_DEFAULT);
		m_pMeshWall[i]->SetType(CObject::TYPE_NONE);
	}

	// �o�����
	m_state = STATE_APPEARANCE;

	return E_FAIL;
}

//==========================================================================
// �I������
//==========================================================================
void CLimitArea::Uninit(void)
{
	// �폜
	if (CManager::GetInstance()->GetMode() == CScene::MODE_GAME && CGame::GetLimitEreaManager() != NULL)
	{// �e�}�l�[�W���̍폜
		CGame::GetLimitEreaManager()->Delete(m_nIdxEreaManager);
	}

	for (int i = 0; i < mylib_const::SHAPE_LIMITEREA; i++)
	{
		if (m_pMeshWall[i] == NULL)
		{
			continue;
		}
		m_pMeshWall[i]->Uninit();
		delete m_pMeshWall[i];
		m_pMeshWall[i] = NULL;
	}

	// �������
	CObject::Release();
}

//==========================================================================
// �폜����
//==========================================================================
void CLimitArea::Kill(void)
{
	// �폜
	if (CManager::GetInstance()->GetMode() == CScene::MODE_GAME && CGame::GetLimitEreaManager() != NULL)
	{// �e�}�l�[�W���̍폜
		CGame::GetLimitEreaManager()->Delete(m_nIdxEreaManager);
	}

	for (int i = 0; i < mylib_const::SHAPE_LIMITEREA; i++)
	{
		if (m_pMeshWall[i] == NULL)
		{
			continue;
		}
		m_pMeshWall[i]->Uninit();
		m_pMeshWall[i] = NULL;
	}

	// �������
	CObject::Release();
}

//==========================================================================
// �X�V����
//==========================================================================
void CLimitArea::Update(void)
{
	// ��ԍX�V
	(this->*(m_StateFuncList[m_state]))();

	for (int i = 0; i < mylib_const::SHAPE_LIMITEREA; i++)
	{
		if (m_pMeshWall[i] == NULL)
		{
			continue;
		}

		// ��U�����
		//UpdateColor(i);
		m_pMeshWall[i]->Update();
	}
}

//==========================================================================
// �ʏ���
//==========================================================================
void CLimitArea::StateNone(void)
{
	// ��ԃJ�E���^�[���Z�b�g
	m_fTimeState = 0.0f;
}

//==========================================================================
// �o�����
//==========================================================================
void CLimitArea::StateAppearance(void)
{
	// ��ԃJ�E���^�[���Z
	m_fTimeState += CManager::GetInstance()->GetDeltaTime();

	// �s�����x
	float fAlpha =  MAX_ALPHA * (m_fTimeState / TIME_APPEARANCE);

	for (int i = 0; i < mylib_const::SHAPE_LIMITEREA; i++)
	{
		if (m_pMeshWall[i] == NULL)
		{
			continue;
		}

		// ���_�J���[�擾
		D3DXCOLOR *pVtxCol = m_pMeshWall[i]->GetVtxCol();
		D3DXCOLOR newcolor = D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha);

		// �S�Ă̗v�f����������
		std::fill(pVtxCol, pVtxCol + m_pMeshWall[i]->GetNumVertex(), newcolor);
	}

	if (m_fTimeState >= TIME_APPEARANCE)
	{// �K��l�𒴂�����o����ԉ���
		m_state = STATE_NONE;
	}

}

//==========================================================================
// �t�F�[�h�A�E�g���
//==========================================================================
void CLimitArea::StateFadeout(void)
{
	// ��ԃJ�E���^�[���Z
	m_fTimeState += CManager::GetInstance()->GetDeltaTime();

	// �s�����x
	float fAlpha = MAX_ALPHA - (m_fTimeState / TIME_FADEOUT);

	for (int i = 0; i < mylib_const::SHAPE_LIMITEREA; i++)
	{
		if (m_pMeshWall[i] == NULL)
		{
			continue;
		}

		// ���_�J���[�擾
		D3DXCOLOR *pVtxCol = m_pMeshWall[i]->GetVtxCol();
		D3DXCOLOR newcolor = D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha);

		// �S�Ă̗v�f����������
		std::fill(pVtxCol, pVtxCol + m_pMeshWall[i]->GetNumVertex(), newcolor);
	}

	if (m_fTimeState >= TIME_FADEOUT)
	{// �폜

		// �폜
		Kill();
		return;
	}
}

//==========================================================================
// �F�X�V
//==========================================================================
void CLimitArea::UpdateColor(int nIdx)
{
	CPlayer *pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(0);
	if (pPlayer == NULL)
	{
		return;
	}
	D3DXVECTOR3 pos = pPlayer->GetPosition();

	// ���_���
	D3DXCOLOR *pVtxCol = m_pMeshWall[nIdx]->GetVtxCol();
	D3DXVECTOR3 *pVtxPos = m_pMeshWall[nIdx]->GetVtxPos();

	// �t�B�[���h�̈ʒu
	D3DXVECTOR3 posfield = m_pMeshWall[nIdx]->GetPosition();

	// �����擾
	float fWidthLen = m_pMeshWall[nIdx]->GetWidthLen();
	float fHeightLen = m_pMeshWall[nIdx]->GetHeightLen();

	// �ő�̒���
	float fMaxWidthLen = fWidthLen * m_pMeshWall[nIdx]->GetWidthBlock();
	float fMaxHeightLen = -fWidthLen * m_pMeshWall[nIdx]->GetHeightBlock();

	// �u���b�N
	int nWidthBlock = m_pMeshWall[nIdx]->GetWidthBlock();
	int nHeightBlock = m_pMeshWall[nIdx]->GetHeightBlock();

	// ���肷�钸�_�̌v�Z
	int nCntWidth = 0;
	int nCntHeight = 0;
	int nWidthPoint = ((pos.x - posfield.x) - fMaxWidthLen * 0.5f) / fWidthLen + nWidthBlock;
	int nHeightPoint = nHeightBlock - ((pos.z - posfield.z) - fMaxHeightLen * 0.5f) / fHeightLen;

	int naWidthPoint[mylib_const::MAX_PLAYER] = {};
	int naHeightPoint[mylib_const::MAX_PLAYER] = {};

	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		CPlayer *pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(i);
		if (pPlayer == NULL)
		{
			continue;
		}
		D3DXVECTOR3 pos = pPlayer->GetPosition();
		naWidthPoint[i] = ((pos.x - posfield.x) - fMaxWidthLen * 0.5f) / fWidthLen + nWidthBlock;
		naHeightPoint[i] = nHeightBlock - ((pos.z - posfield.z) - fMaxHeightLen * 0.5f) / fHeightLen;
	}


#if 0
	for (int nCntH = 0; nCntH < 2; nCntH++)
	{
		for (int nCntW = 0; nCntW < 2; nCntW++)
		{
			// �����_
			nCntWidth = nWidthPoint + (nCntW - 1);
			nCntHeight = nHeightPoint + (nCntH - 1);

			if (nCntWidth < 0 || nWidthBlock < nCntWidth)
			{// �͈͊O�Ő擪
				continue;
			}

			if (nCntHeight < 0 || nHeightBlock < nCntHeight)
			{// �͈͊O�Ő擪
				continue;
			}

			// ����̒��_
			int nNowPoint = (nCntWidth + 1) + (nCntHeight * (nWidthBlock + 1));
			pVtxCol[nNowPoint] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		}
	}
#else
	for (int nCntH = 0; nCntH < nHeightBlock + 1; nCntH++)
	{
		for (int nCntW = 0; nCntW < nWidthBlock + 1; nCntW++)
		{
			// ����̒��_
			int nNowPoint = nCntW + (nCntH * (nWidthBlock + 1));

			for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
			{
				if (naWidthPoint[i] == nNowPoint ||
					naHeightPoint[i] == nNowPoint)
				{

					pVtxCol[nNowPoint] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
					break;
				}
				else
				{
					pVtxCol[nNowPoint] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
				}
			}

			// ��ŏ���
			pVtxCol[nNowPoint] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
		}
	}
#endif

}

//==========================================================================
// �`�揈��
//==========================================================================
void CLimitArea::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �w�ʂ̃J�����O�Ȃ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// �`�揈��
	for (int i = 0; i < mylib_const::SHAPE_LIMITEREA; i++)
	{
		if (m_pMeshWall[i] == NULL)
		{
			continue;
		}

		m_pMeshWall[i]->Draw();
	}

	// ���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// �J�����O�f�t�H���g
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//==========================================================================
// ���擾
//==========================================================================
CLimitArea::sLimitEreaInfo CLimitArea::GetLimitEreaInfo(void)
{
	return m_sLimitEreaInfo;
}

//==========================================================================
// ��Ԏ擾
//==========================================================================
CLimitArea::STATE CLimitArea::GetState(void)
{
	return m_state;
}

//==========================================================================
// ��Ԏ擾
//==========================================================================
void CLimitArea::SetState(STATE state)
{
	m_state = state;
}