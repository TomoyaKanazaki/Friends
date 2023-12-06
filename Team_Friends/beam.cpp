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
#include "camera.h"
#include "particle.h"
#include "ballast.h"

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CBeam::CBeam(int nPriority) : CObject(nPriority)
{
	m_fRadius = 0.0f;	// ���a
	m_fLength = 0.0f;	// ����
	m_nDisity = 0;		// ���x
	m_nDamage = 0;		// �_���[�W
	m_color = mylib_const::DEFAULT_COLOR;	// �F
	m_pEffect.clear();	// �G�t�F�N�g�̃I�u�W�F�N�g
	m_Tag = CCollisionObject::TAG_NONE;	// �^�O
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
CBeam *CBeam::Create(
	const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXCOLOR col,
	const float fRadius, const float fLength, const int nLife,
	const int nDisity, const int nDamage, CCollisionObject::eMyTag TagType)
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
			pBallast->m_color = col;		// �F
			pBallast->m_nDisity = nDisity;	// ���x
			pBallast->m_nDamage = nDamage;	// �_���[�W
			pBallast->m_Tag = TagType;		// �^�O

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
		CEffect3D *pEffect = CEffect3D::Create(
			pos + vecmove * fLen,
			move,
			m_color,
			m_fRadius,
			m_nLife,
			CEffect3D::MOVEEFFECT_SUB,
			CEffect3D::TYPE_NORMAL,
			0.0f);

		// �G�t�F�N�g�ǉ�
		m_pEffect.push_back(pEffect);

		// �����蔻��I�u�W�F�N�g����
		CCollisionObject::Create(pos + vecmove * fLen, move, m_fRadius, m_nLife, m_nDamage, m_Tag);

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
	// �v�f�S�폜
	m_pEffect.clear();

	// ���폜
	Release();
}

//==========================================================================
// �X�V����
//==========================================================================
void CBeam::Update(void)
{
	// �������Z
	m_nLife--;

	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}

	for (int i = 0; i < static_cast<int>(m_pEffect.size()); i++)
	{
		if (m_pEffect[i] == nullptr)
		{
			continue;
		}

		// �ʒu�擾
		D3DXVECTOR3 pos = m_pEffect[i]->GetPosition();

		if (CGame::GetElevation()->IsHit(pos) == true)
		{
			// �U��
			CManager::GetInstance()->GetCamera()->SetShake(6, 4.0f, 0.0f);

			// ���I
			CBallast::Create(pos, D3DXVECTOR3(2.0f, 6.0f, 2.0f), 1, 1.0f, CBallast::TYPE_STONE);

			// �r�[���q�b�g�p�[�e�B�N��
			my_particle::Create(pos, my_particle::TYPE_BEAMHIT_FIELD);

			m_pEffect[i]->Uninit();
			m_pEffect[i] = nullptr;

			// ���n�������̂��폜
			m_pEffect.erase(m_pEffect.begin() + i);
		}
	}
}

//==========================================================================
// �`�揈��
//==========================================================================
void CBeam::Draw(void)
{
	
}
