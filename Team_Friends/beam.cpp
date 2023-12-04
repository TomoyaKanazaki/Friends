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
#include "collisionobject.h"
#include "camera.h"
#include "particle.h"
#include "ballast.h"

//==========================================================================
// �������O���
//==========================================================================
namespace
{
	float radius;		// ���a
	float length;		// ����
	int disity;			// ���x
	int damage;			// �_���[�W
	D3DXCOLOR color;	// �F
	std::vector<CEffect3D*> effect;	// �G�t�F�N�g�̃I�u�W�F�N�g
}

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CBeam::CBeam(int nPriority) : CObject(nPriority)
{

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
	const float fRadius, const float fLength, const int nLife, const int nDisity, const int nDamage)
{
	// �����p�̃I�u�W�F�N�g
	CBeam *pBallast = NULL;

	if (pBallast == NULL)
	{// NULL��������

		// �������̊m��
		pBallast = DEBUG_NEW CBeam;

		if (pBallast != NULL)
		{// �������̊m�ۂ��o���Ă�����

			radius = fRadius;			// ���a
			length = fLength;			// ����
			pBallast->m_nLife = nLife;	// ����
			pBallast->SetPosition(pos);	// �ʒu
			pBallast->SetMove(move);	// �ړ���
			color = col;				// �F
			disity = nDisity;			// ���x
			damage = nDamage;			// �_���[�W

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

	float fDistance = length / (float)disity;
	float fLen = 0.0f;
	for (int nCntBallast = 0; nCntBallast < disity; nCntBallast++)
	{
		// ��������
		CEffect3D *pEffect = CEffect3D::Create(
			pos + vecmove * fLen,
			move,
			color,
			radius,
			m_nLife,
			CEffect3D::MOVEEFFECT_SUB,
			CEffect3D::TYPE_NORMAL,
			0.0f);

		// �G�t�F�N�g�ǉ�
		effect.push_back(pEffect);

		// �����蔻��I�u�W�F�N�g����
		//CCollisionObject::Create(pos + vecmove * fLen, move, radius, life, damage, CCollisionObject::TAG_PLAYER);

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
	effect.clear();

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

	for (int i = 0; i < static_cast<int>(effect.size()); i++)
	{
		if (effect[i] == nullptr)
		{
			continue;
		}

		// �ʒu�擾
		D3DXVECTOR3 pos = effect[i]->GetPosition();

		if (CGame::GetElevation()->IsHit(pos) == true)
		{
			// �U��
			CManager::GetInstance()->GetCamera()->SetShake(6, 4.0f, 0.0f);

			// ���I
			CBallast::Create(pos, D3DXVECTOR3(2.0f, 6.0f, 2.0f), 1, 1.0f, CBallast::TYPE_STONE);

			// �r�[���q�b�g�p�[�e�B�N��
			my_particle::Create(pos, my_particle::TYPE_BEAMHIT_FIELD);

			effect[i]->Uninit();
			effect[i] = nullptr;

			// ���n�������̂��폜
			effect.erase(effect.begin() + i);
		}
	}
}

//==========================================================================
// �`�揈��
//==========================================================================
void CBeam::Draw(void)
{
	
}
