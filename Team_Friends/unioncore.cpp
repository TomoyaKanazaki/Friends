//=============================================================================
// 
//  ���̂̃R�A���� [unioncore.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "unioncore.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"
#include "3D_effect.h"
#include "particle.h"
#include "calculation.h"
#include "scene.h"

//==========================================================================
// �������O���
//==========================================================================
namespace
{
	const char* MODELFILE = "data\\MODEL\\compactcore_01.x";
}

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CUnionCore::CUnionCore(int nPriority) : CObjectX(nPriority)
{
	// �l�̃N���A
	m_nCntEmission = 0;		// �������̃J�E���^�[
	m_setupPosition = mylib_const::DEFAULT_VECTOR3;	// �Z�b�g�A�b�v�ʒu
	m_pMtxParent = nullptr;	// �e�}�g���b�N�X�̃|�C���^
	m_bSetUp = false;		// �Z�b�g�A�b�v����
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CUnionCore::~CUnionCore()
{
	
}

//==========================================================================
// ��������
//==========================================================================
CUnionCore *CUnionCore::Create(const D3DXVECTOR3 pos)
{
	// �����p�̃I�u�W�F�N�g
	CUnionCore *pBullet = NULL;

	if (pBullet == NULL)
	{// NULL��������

		// �������̊m��
		pBullet = DEBUG_NEW CUnionCore;

		if (pBullet != NULL)
		{// �������̊m�ۂ��o���Ă�����

			// �ʒu���蓖��
			pBullet->SetPosition(pos);

			// ����������
			pBullet->Init();
		}

		return pBullet;
	}

	return NULL;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CUnionCore::Init(void)
{
	HRESULT hr;

	// ����������
	hr = CObjectX::Init(MODELFILE);
	if (FAILED(hr))
	{// ���s�����Ƃ�
		return E_FAIL;
	}

	// ��ނ̐ݒ�
	CObject::SetType(TYPE_OBJECTX);

	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CUnionCore::Uninit(void)
{
	// �I������
	CObjectX::Uninit();
}

//==========================================================================
// �X�V����
//==========================================================================
void CUnionCore::Update(void)
{
	if (m_bSetUp)
	{
		D3DXMATRIX mtxTrans, mtxWorld;	// �v�Z�p�}�g���b�N�X�錾

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		// �ʒu�𔽉f����
		D3DXMatrixTranslation(&mtxTrans, m_setupPosition.x, m_setupPosition.y, m_setupPosition.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

		// �����ɐe�̃��[���h�}�g���b�N�X���|����
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, m_pMtxParent);

		SetPosition(WorldMtxChangeToPosition(mtxWorld));
	}

	// �������J�E���^�[���Z
	m_nCntEmission = (m_nCntEmission + 1) % 3;

	if (m_nCntEmission == 0)
	{
		D3DXVECTOR3 pos = GetPosition();
		float fMove = 2.5f + Random(-20, 20) * 0.1f;
		float fMoveY = 25.0f + Random(-30, 30) * 0.1f;
		float fRot = GetRandomCircleValue();

		CEffect3D::Create(
			pos,
			D3DXVECTOR3(
				sinf(D3DX_PI + fRot) * fMove,
				fMoveY,
				cosf(D3DX_PI + fRot) * fMove),
			D3DXCOLOR(
				0.2f + Random(-10, 10) * 0.01f,
				0.2f + Random(-10, 10) * 0.01f,
				0.9f + Random(-10, 10) * 0.01f,
				1.0f),
			180.0f + (float)Random(-20, 20),
			15,
			CEffect3D::MOVEEFFECT_SUPERSUB,
			CEffect3D::TYPE_SMOKE);

		D3DXVECTOR3 RandPos = mylib_const::DEFAULT_VECTOR3;
		RandPos.x = Random(-5, 5) * 10.0f;
		RandPos.y = Random(-5, 5) * 10.0f;
		RandPos.z = Random(-5, 5) * 10.0f;

		CEffect3D *pEffect = CEffect3D::Create(
			pos + RandPos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.2f, 0.2f, 0.9f, 1.0f),
			150.0f + (float)Random(-50, 50), 6,
			CEffect3D::MOVEEFFECT_ADD,
			CEffect3D::TYPE_THUNDER);
		pEffect->SetRotation(D3DXVECTOR3(0.0f, 0.0f, GetRandomCircleValue()));
	}
}

//==================================================================================
// �Z�b�g�A�b�v
//==================================================================================
void CUnionCore::SetUp(D3DXVECTOR3 setup, D3DXMATRIX *pMtxParent)
{
	// �e�}�g���b�N�X�̃|�C���^
	m_pMtxParent = pMtxParent;

	// �Z�b�g�A�b�v�ʒu
	m_setupPosition = setup;

	m_bSetUp = true;
}

//==========================================================================
// �`�揈��
//==========================================================================
void CUnionCore::Draw(void)
{
	// �`��
	CObjectX::Draw();
}

