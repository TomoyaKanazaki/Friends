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
		// ���[�V�����̐ݒ菈��
		MotionSet(i);
	}

	// ���[�V�����X�V
	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pMotion[i] == NULL)
		{
			continue;
		}
		m_pMotion[i]->Update();
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

	// ����������
	pUnion->Init();

	// �l��ۑ�
	pUnion->SetPosition(pos);

	return pUnion;
}
