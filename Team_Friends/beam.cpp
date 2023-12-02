//=============================================================================
// 
//  �r�[������ [beam.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "beam.h"
#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "calculation.h"
#include "3D_effect.h"

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CBeam::CBeam(int nPriority) : CObject(nPriority)
{
	m_fRadius = 0.0f;	// ���a
	m_fLength = 0.0f;	// ����
	m_nLife = 0;		// ����
	m_nDisity = 0;		// ���x
	m_col = mylib_const::DEFAULT_COLOR;	// �F
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CBeam::~CBeam()
{
	
}

//==========================================================================
// ��������
//==========================================================================
CBeam *CBeam::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXCOLOR col, const float fRadius, const float fLength, const int nLife, const int nDisity)
{
	// �����p�̃I�u�W�F�N�g
	CBeam *pBallast = NULL;

	if (pBallast == NULL)
	{// NULL��������

		// �������̊m��
		pBallast = DEBUG_NEW CBeam;

		if (pBallast != NULL)
		{// �������̊m�ۂ��o���Ă�����

			pBallast->m_fRadius = fRadius;	// ���a
			pBallast->m_fLength = fLength;	// ����
			pBallast->m_nLife = nLife;		// ����
			pBallast->SetPosition(pos);		// �ʒu
			pBallast->SetMove(move);		// �ړ���
			pBallast->m_col = col;			// �F
			pBallast->m_nDisity = nDisity;	// ���x

			// ����������
			HRESULT hr = pBallast->Init();
			if (FAILED(hr))
			{
				return NULL;
			}
		}

		return pBallast;
	}

	return NULL;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CBeam::Init(void)
{
	// ��ނ̐ݒ�
	SetType(TYPE_OBJECT3D);

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 vecmove = move - mylib_const::DEFAULT_VECTOR3;

	// �x�N�g���𐳋K��
	D3DXVec3Normalize(&vecmove, &vecmove);

	float fDistance = m_fLength / (float)m_nDisity;
	float fLen = 0.0f;
	for (int nCntBallast = 0; nCntBallast < m_nDisity; nCntBallast++)
	{
		// ��������
		CEffect3D::Create(
			pos + vecmove * fLen,
			move,
			m_col,
			m_fRadius,
			m_nLife,
			CEffect3D::MOVEEFFECT_SUB,
			CEffect3D::TYPE_NORMAL,
			0.0f);

		// �������Z
		fLen += fDistance;
	}

	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CBeam::Uninit(void)
{
	// ���폜
	Release();
}

//==========================================================================
// �X�V����
//==========================================================================
void CBeam::Update(void)
{
	
}

//==========================================================================
// �`�揈��
//==========================================================================
void CBeam::Draw(void)
{
	
}
