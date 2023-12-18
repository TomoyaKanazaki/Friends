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
#include "texture.h"
#include "impactwave.h"

namespace
{
	const char* TEXTURE = "data\\TEXTURE\\effect\\effect000.jpg";
	const float RATIO_SUBSIZE = 0.3f;	// �T�C�Y�k���̊���
	const float TIME_LENGTH = 10;	// �����␳�̎���
}

int CBeam::m_nTexIdx = 0;		// �e�N�X�`���̃C���f�b�N�X�ԍ�

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CBeam::CBeam(int nPriority) : CObject(nPriority)
{
	m_fRadius = 0.0f;		// ���a
	m_fLength = 0.0f;		// ����
	m_fDestLength = 0.0f;	// �ڕW�̒���
	m_moveRatio = 0.0f;		// �ړ��̊���
	m_nDisity = 0;			// ���x
	m_nDamage = 0;			// �_���[�W
	m_color = mylib_const::DEFAULT_COLOR;	// �F
	m_pEffect.clear();	// �G�t�F�N�g�̃I�u�W�F�N�g
	m_pObjBillboard.clear();	// �r���{�[�h�̃I�u�W�F�N�g
	m_Tag = CCollisionObject::TAG_NONE;	// �^�O
	m_nLife = 0;	// ����
	m_nLifeOrigin = 0;	// ����
	m_nCntEmission = 0;	// �������̃J�E���^�[
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
	const int nDisity, const int nDamage, CCollisionObject::eMyTag TagType, eBeamType BeamType)
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
			pBallast->m_fDestLength = fLength;	// �ڕW�̒���
			pBallast->m_nLife = nLife;		// ����
			pBallast->SetPosition(pos);		// �ʒu
			pBallast->SetMove(move);		// �ړ���
			pBallast->m_color = col;		// �F
			pBallast->m_nDisity = nDisity;	// ���x
			pBallast->m_nDamage = nDamage;	// �_���[�W
			pBallast->m_Tag = TagType;		// �^�O
			pBallast->m_BeamType = BeamType;	// �r�[���̎��

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
// ���Z����������
//==========================================================================
void CBeam::SetDisableAddAlpha(void)
{
	for (int i = 0; i < static_cast<int>(m_pEffect.size()); i++)
	{
		if (m_pEffect[i] == nullptr)
		{
			continue;
		}

		m_pEffect[i]->SetDisableAddAlpha();
	}
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

	m_nLifeOrigin = m_nLife;

	// �x�N�g���𐳋K��
	D3DXVec3Normalize(&vecmove, &vecmove);

	if (m_BeamType == TYPE_RESIDUAL)
	{
		m_fLength = 0.0f;
	}

	float fDistance = m_fLength / (float)m_nDisity;
	float fLen = 0.0f;
	for (int nCntBallast = 0; nCntBallast < m_nDisity; nCntBallast++)
	{
		switch (m_BeamType)
		{
		case CBeam::TYPE_NORMAL:
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
		}
			break;

		case CBeam::TYPE_RESIDUAL:
		{
			// ��������
			CObjectBillboard *pEffect = CObjectBillboard::Create(pos + vecmove * fLen, mylib_const::DEFAULT_VECTOR3);
			pEffect->SetMove(move);
			pEffect->SetColor(m_color);
			pEffect->SetSize(D3DXVECTOR2(m_fRadius, m_fRadius));
			pEffect->SetSizeOrigin(D3DXVECTOR2(m_fRadius, m_fRadius));
			pEffect->SetType(CObject::TYPE_NONE);

			if (m_nTexIdx == 0)
			{
				m_nTexIdx = CManager::GetInstance()->GetTexture()->Regist(TEXTURE);
			}
			pEffect->BindTexture(m_nTexIdx);

			// �r���r�[�h�ǉ�
			m_pObjBillboard.push_back(pEffect);
		}
			break;
		}

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

	for (int i = 0; i < static_cast<int>(m_pObjBillboard.size()); i++)
	{
		if (m_pObjBillboard[i] == nullptr)
		{
			continue;
		}
		m_pObjBillboard[i]->Uninit();
		m_pObjBillboard[i] = nullptr;
	}

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

	switch (m_BeamType)
	{
	case CBeam::TYPE_NORMAL:
		UpdateEffect();
		break;

	case CBeam::TYPE_RESIDUAL:
		UpdateBillboard();
		break;
	}
	
}

//==========================================================================
// �G�t�F�N�g�̍X�V
//==========================================================================
void CBeam::UpdateEffect(void)
{
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
// �r���r�[�h�̍X�V
//==========================================================================
void CBeam::UpdateBillboard(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMove();
	pos += move;
	SetPosition(pos);

	float fAlpha = (float)m_nLife / (float)m_nLifeOrigin;
	float fSubRatio = (float)(m_nLife + (m_nLifeOrigin * (1.0f - RATIO_SUBSIZE))) / (float)m_nLifeOrigin;
	ValueNormalize(fSubRatio, 1.0f, 0.0f);

	// �v�f���J��Ԃ�
	int nCntBillboard = 0;

	// �����␳
	//InertiaCorrection(m_fLength, m_fDestLength, 0.25f);

	if (m_moveRatio < 1.0f)
	{
		m_moveRatio = (float)(m_nLifeOrigin - m_nLife) / TIME_LENGTH;
		m_fLength = EasingEaseOut(0.0f, m_fDestLength, m_moveRatio);
		ValueNormalize(m_moveRatio, 1.0f, 0.0f);

		// �������J�E���^�[���Z
		m_nCntEmission = (m_nCntEmission + 1) % 1;

		if (m_nCntEmission == 0)
		{
			// ��[�̈ʒu
			D3DXVECTOR3 spawnpos = pos + (move * m_fLength);
			float moverot = atan2f(move.x, move.z);

			// �Ռ��g����
			CImpactWave::Create
			(
				spawnpos,	// �ʒu
				D3DXVECTOR3(D3DX_PI * 0.5f, moverot, 0.0f),				// ����
				mylib_const::PLAYERBEAM_COLOR,			// �F
				50.0f,						// ��
				20.0f,						// ����
				60.0f,						// ���S����̋���
				15,							// ����
				40.0f,						// ���̈ړ���
				CImpactWave::TYPE_PURPLE4,	// �e�N�X�`���^�C�v
				true						// ���Z�������邩
			);
		}
	}

	float fDistance = m_fLength / (float)m_nDisity;
	float fLen = 0.0f;

	for (int i = static_cast<int>(m_pObjBillboard.size()) - 1; i >= 0; --i)
	{
		const auto& billboard = m_pObjBillboard[i];

		if (billboard == nullptr)
		{
			continue;
		}

		// �F
		D3DXCOLOR col = billboard->GetColor();
		col.a = fAlpha;
		billboard->SetColor(col);

		// �ʒu�擾
		D3DXVECTOR3 posbillboard = billboard->GetPosition();

		// �T�C�Y�擾
		D3DXVECTOR2 sizeorigin = billboard->GetSizeOrigin();

		// �ʒu�X�V
		posbillboard = pos + move * fLen;
		billboard->SetPosition(posbillboard);

		// �T�C�Y�ݒ�
		m_fRadius = sizeorigin.x * fSubRatio;
		billboard->SetSize(D3DXVECTOR2(m_fRadius, m_fRadius));

		// �������Z
		fLen += fDistance;

		if (CGame::GetElevation()->IsHit(pos) == true)
		{
			// �U��
			CManager::GetInstance()->GetCamera()->SetShake(6, 4.0f, 0.0f);

			// ���I
			CBallast::Create(pos, D3DXVECTOR3(2.0f, 6.0f, 2.0f), 1, 1.0f, CBallast::TYPE_STONE);

			// �r�[���q�b�g�p�[�e�B�N��
			my_particle::Create(pos, my_particle::TYPE_BEAMHIT_FIELD);

			billboard->Uninit();
			//billboard = nullptr;

			// ���n�������̂��폜
			m_pObjBillboard.erase(m_pObjBillboard.begin() + i);
			continue;
		}

		// �X�V
		billboard->Update();
	}
}

//==========================================================================
// �`�揈��
//==========================================================================
void CBeam::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ���X�g�R�s�[
	std::vector<CObjectBillboard*> pObjectSort = m_pObjBillboard;

	// Z�\�[�g
	std::sort(pObjectSort.begin(), pObjectSort.end(), ZSort);

	for (int i = 0; i < (int)pObjectSort.size(); i++)
	{
		if (pObjectSort[i] == nullptr)
		{
			continue;
		}
		pObjectSort[i]->Draw();
	}

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// ���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


}
