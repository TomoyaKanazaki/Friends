//==========================================
//
//  �^�C�g���̍��̃��{(union_title.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "union_title.h"
#include "manager.h"
#include "debugproc.h"
#include "input.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CUnionTitle::CUnionTitle(int nPriority)
{
	// �ϐ��̃N���A
	m_bPressEnter = false;	// �G���^�[�̉�������
}

//==========================================
//  �f�X�g���N�^
//==========================================
CUnionTitle::~CUnionTitle()
{

}

//==========================================
//  ����������
//==========================================
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

	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pObjChara[i] == NULL)
		{
			continue;
		}

		// ���g�̏����擾
		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 rot = GetRotation();

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

//==========================================
//  �I������
//==========================================
void CUnionTitle::Uninit(void)
{
	CPlayerUnion::Uninit();
}

//==========================================
//  �X�V����
//==========================================
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

		D3DXVECTOR3 pos = m_pObjChara[i]->GetPosition();

		// ���[�V�����X�V
		m_pMotion[i]->Update();

		D3DXVECTOR3 posDiff = m_pObjChara[i]->GetPosition() - pos;

		//if (i == 0)
		{
			SetPosition(GetPosition() + posDiff);
		}
	}

	// �ʒu�E�����ݒ�
	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pObjChara[i] == NULL)
		{
			continue;
		}

		// ���g�̏����擾
		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 rot = GetRotation();

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
	D3DXVECTOR3 weponpos = m_pMotion[nIdx]->GetAttackPosition(m_pObjChara[nIdx]->GetModel(), ATKInfo);

	// ��ޕ�
	switch (m_pMotion[nIdx]->GetType())
	{
	case MOTION_ATK:
		break;
	}
}

//==========================================
//  �`�揈��
//==========================================
void CUnionTitle::Draw(void)
{
	CPlayerUnion::Draw();
}

//==========================================
//  ��������
//==========================================
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
