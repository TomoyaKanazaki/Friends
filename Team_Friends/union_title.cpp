//=============================================================================
// 
//  �^�C�g�����̃v���C���[���� [union_title.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "union_title.h"
#include "manager.h"
#include "camera.h"
#include "effect_startupeye.h"
#include "title.h"
#include "fade.h"
#include "3D_Effect.h"
#include "calculation.h"

//==========================================================================
//  �R���X�g���N�^
//==========================================================================
CUnionTitle::CUnionTitle(int nPriority)
{
	// �ϐ��̃N���A
	m_bPressEnter = false;	// �G���^�[�̉�������
}

//==========================================================================
//  �f�X�g���N�^
//==========================================================================
CUnionTitle::~CUnionTitle()
{

}

//==========================================================================
// ��������
//==========================================================================
CUnionTitle* CUnionTitle::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CUnionTitle* pUnion = DEBUG_NEW CUnionTitle;

	// �l��ۑ�
	pUnion->SetPosition(pos);

	// ����������
	pUnion->Init();

	return pUnion;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CUnionTitle::Init(void)
{
	// ��ނ̐ݒ�
	SetType(TYPE_PLAYER);

	m_state = STATE_NONE;	// ���

	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		m_nPartsIdx[i] = -1;
	}

	// �L�����쐬
	CreateParts();

	// �v���C���[�C���f�b�N�X���̃e�N�X�`���ݒ�
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		BindByPlayerIdxTexture(i, i);
	}


	// ���g�̏����擾
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();
	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pObjChara[i] == NULL)
		{
			continue;
		}

		// �ʒu�E�����ݒ�
		m_pObjChara[i]->SetPosition(pos);
		m_pObjChara[i]->SetRotation(rot);
	}

	return S_OK;
}

//==========================================================================
// �p�[�c�̐ݒ�
//==========================================================================
HRESULT CUnionTitle::CreateParts(void)
{
	// �����L�����ǂݍ���
	ReadMultiCharacter("data\\TEXT\\multicharacter\\SuperUnion_title.txt");

	return S_OK;
}

//==========================================================================
// �X�V����
//==========================================================================
void CUnionTitle::Update(void)
{
	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pMotion[i] == NULL)
		{
			continue;
		}

		// ���[�V�����̐ݒ菈��
		if (m_bPressEnter)
		{
			m_pMotion[i]->Set(MOTION_STARTUP);
		}
		else
		{
			m_pMotion[i]->Set(MOTION_DEF);
		}

		if (m_pMotion[i]->GetType() == MOTION_STARTUP && m_pMotion[i]->IsFinish())
		{
			// ���[�h�ݒ�
			CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_DECIDE);
		}

		D3DXVECTOR3 pos = m_pObjChara[i]->GetPosition();

		// ���[�V�����X�V
		m_pMotion[i]->Update();

		// ����
		D3DXVECTOR3 posDiff = m_pObjChara[i]->GetPosition() - pos;
		SetPosition(GetPosition() + posDiff);

		// �U������
		Atack(i);
	}

	// �ʒu�E�����ݒ�
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();

	D3DXCOLOR col = D3DXCOLOR(1.0f, 0.2f, 0.7f, 1.0f);

	int nWidth = 10;
	float fWidthDistance = 200.0f;
	float fRadius = 1000.0f;
	for (int i = 0; i < nWidth; i++)
	{
		D3DXVECTOR3 spawnpos = pos;
		spawnpos.x = ((static_cast<float>(nWidth) * 0.5f) * fWidthDistance) - fWidthDistance * i;

		CEffect3D::Create(
			spawnpos,
			mylib_const::DEFAULT_VECTOR3,
			col,
			fRadius,
			2,
			CEffect3D::MOVEEFFECT_ADD,
			CEffect3D::TYPE_POINT);
	}

	D3DXVECTOR3 spawnpos = pos;
	spawnpos.x -= 400.0f;
	spawnpos.z -= 800.0f;

	CEffect3D::Create(
		spawnpos,
		mylib_const::DEFAULT_VECTOR3,
		col,
		fRadius,
		2,
		CEffect3D::MOVEEFFECT_ADD,
		CEffect3D::TYPE_POINT);

	spawnpos = pos;
	spawnpos.x += 400.0f;
	spawnpos.z -= 800.0f;
	CEffect3D::Create(
		spawnpos,
		mylib_const::DEFAULT_VECTOR3,
		col,
		fRadius,
		2,
		CEffect3D::MOVEEFFECT_ADD,
		CEffect3D::TYPE_POINT);

	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pObjChara[i] == NULL)
		{
			continue;
		}

		m_pObjChara[i]->SetPosition(pos);
		m_pObjChara[i]->SetRotation(rot);
	}
}

//==========================================================================
// �U��������
//==========================================================================
void CUnionTitle::AttackAction(int nIdx, int nModelNum, CMotion::AttackInfo ATKInfo)
{
	// ����̈ʒu
	D3DXVECTOR3 weponpos = m_pMotion[nIdx]->GetAttackPosition(m_apModel[ATKInfo.nCollisionNum], ATKInfo);

	// ��ޕ�
	switch (m_pMotion[nIdx]->GetType())
	{
	case MOTION_STARTUP:
		CEffectStartupEye::Create(weponpos);

		// �G���^�[��������ON
		CTitle::SetEnablePressEnter();
		break;
	}
}

//==========================================================================
// �U�����蒆����
//==========================================================================
void CUnionTitle::AttackInDicision(int nIdx, CMotion::AttackInfo ATKInfo)
{
	// ���̍U�����蒆����
	CPlayerUnion::AttackInDicision(nIdx, ATKInfo);

	// ���[�V�������擾
	int nMotionType = m_pMotion[nIdx]->GetType();
	D3DXVECTOR3 weponpos = m_pMotion[nIdx]->GetAttackPosition(m_apModel[ATKInfo.nCollisionNum], ATKInfo);

	// ���[�V�����ʏ���
	switch (nMotionType)
	{
	case MOTION_STARTUP:
		// �U��
		CManager::GetInstance()->GetCamera()->SetShake(30, 25.0f, 0.0f);
		break;
	}
}
