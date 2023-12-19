//=============================================================================
// 
//  �e�̒��e�n�_ [bullet_point.cpp]
//  Author : ���c����
// 
//=============================================================================
#include "bullet_point.h"
#include "texture.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "elevation.h"

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
int CBulletPoint::m_nNumAll = 0;						// �e�̑���

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CBulletPoint::CBulletPoint(int nPriority) : CObject3D(nPriority)
{
	m_pObject = NULL;	// �I�u�W�F�N�g�̃|�C���^
	m_nNumAll = 0;		// ����
	m_nTexIdx = 0;		// �e�N�X�`���̃C���f�b�N�X�ԍ�

	// �������Z
	m_nNumAll++;
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CBulletPoint::~CBulletPoint()
{
	
}

//==========================================================================
// ��������
//==========================================================================
CBulletPoint *CBulletPoint::Create(void)
{
	// �����p�̃I�u�W�F�N�g
	CBulletPoint *pShadow = NULL;

	if (pShadow == NULL)
	{// NULL��������

		// �������̊m��
		pShadow = DEBUG_NEW CBulletPoint;

		//if (pShadow->GetID() < 0)
		//{// �������m�ۂɎ��s���Ă�����

		//	delete pShadow;
		//	return NULL;
		//}

		if (pShadow != NULL)
		{// �������̊m�ۂ��o���Ă�����

			// ����������
			pShadow->Init();
		}

		return pShadow;
	}

	return NULL;
}

//==========================================================================
// ��������(�I�[�o�[���[�h)
//==========================================================================
CBulletPoint *CBulletPoint::Create(D3DXVECTOR3 pos, float size)
{
	// �����p�̃I�u�W�F�N�g
	CBulletPoint *pShadow = NULL;

	if (pShadow == NULL)
	{// NULL��������

		// �������̊m��
		pShadow = DEBUG_NEW CBulletPoint;

		//if (pShadow->GetID() < 0)
		//{// �������m�ۂɎ��s���Ă�����

		//	delete pShadow;
		//	return NULL;
		//}

		if (pShadow != NULL)
		{// �������̊m�ۂ��o���Ă�����

			// �ʒu���蓖��
			pShadow->SetPosition(pos);
			pShadow->SetSize(D3DXVECTOR3(size, 0.0f, size));	// �T�C�Y

			// ����������
			pShadow->Init();
		}
		return pShadow;
	}

	return NULL;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CBulletPoint::Init(void)
{
	HRESULT hr;

	// �e��ϐ��̏�����
	SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));	// �F

	// ��ނ̐ݒ�
	SetType(TYPE_SHADOW);

	D3DXVECTOR3 pos = GetPosition();
	SetPosition(D3DXVECTOR3(pos.x, pos.y + 1.0f, pos.z));

	// ����������
	hr = CObject3D::Init();

	if (FAILED(hr))
	{// ���s�����Ƃ�

		return E_FAIL;
	}

	// �e�N�X�`���̊��蓖��
	m_nTexIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\caution\\target.png");

	// �e�N�X�`���̊��蓖��
	BindTexture(m_nTexIdx);

	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CBulletPoint::Uninit(void)
{
	// �I������
	CObject3D::Uninit();

	// �������Z
	m_nNumAll--;
}

//==========================================================================
// �X�V����
//==========================================================================
void CBulletPoint::Update(void)
{
	// ���S�̔���
	if (IsDeath() == true)
	{// ���S�t���O�������Ă�����
		return;
	}

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �����擾
	bool bLand = false;
	pos.y = CGame::GetElevation()->GetHeight(pos, bLand);

	// �ʒu�ݒ�
	SetPosition(pos);

	// ���_���ݒ�
	CObject3D::SetVtx();
}

//==========================================================================
// �`�揈��
//==========================================================================
void CBulletPoint::Draw(void)
{
	// �`�揈��
	CObject3D::Draw();
}

//==========================================================================
// �����擾
//==========================================================================
int CBulletPoint::GetNumAll(void)
{
	return m_nNumAll;
}
