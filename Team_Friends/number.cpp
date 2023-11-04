//=============================================================================
// 
//  �������� [number.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "number.h"
#include "manager.h"
#include "renderer.h"
#include "object2D.h"
#include "objectBillboard.h"

//==========================================================================
// �}�N����`
//==========================================================================
#define WIDTH			(640.0f)					// ����
#define HEIGHT			(360.0f)					// �c��
#define SCROLL_SPEED	(-0.005f)					// �X�N���[�����x

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CNumber::CNumber(int nPriority)
{
	// �l�̃N���A
	m_objType = OBJECTTYPE_2D;	// �I�u�W�F�N�g�̎��
	m_aObject2D = NULL;			// �I�u�W�F�N�g2D�̃I�u�W�F�N�g
	m_pObjBillboard = NULL;		// �I�u�W�F�N�g�r���{�[�h�̃I�u�W�F�N�g
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CNumber::~CNumber()
{

}

//==========================================================================
// ��������
//==========================================================================
CNumber *CNumber::Create(EObjectType objtype)
{
	// �����p�̃I�u�W�F�N�g
	CNumber *pNumber = NULL;

	if (pNumber == NULL)
	{// NULL��������

		// �������̊m��
		pNumber = DEBUG_NEW CNumber;

		if (pNumber != NULL)
		{// �������̊m�ۂ��o���Ă�����

			// �I�u�W�F�N�g�̎��
			pNumber->m_objType = objtype;

			// ����������
			pNumber->Init();
		}
		else
		{
			delete pNumber;
			pNumber = NULL;
		}

		return pNumber;
	}

	return NULL;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CNumber::Init(void)
{
	// ��������
	switch (m_objType)
	{
	case CNumber::OBJECTTYPE_2D:
		m_aObject2D = CObject2D::Create(7);
		break;

	case CNumber::OBJECTTYPE_BILLBOARD:
		m_pObjBillboard = CObjectBillboard::Create();
		break;

	default:
		return E_FAIL;
		break;
	}

	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CNumber::Uninit(void)
{
	// �I������
	if (m_aObject2D != NULL)
	{// NULL����Ȃ�������
		m_aObject2D = NULL;
	}

	// �I������
	if (m_pObjBillboard != NULL)
	{// NULL����Ȃ�������
		m_pObjBillboard = NULL;
	}
}

//==========================================================================
// �������
//==========================================================================
void CNumber::Release(void)
{
	if (m_aObject2D != NULL)
	{// NULL����Ȃ�������
		m_aObject2D->Uninit();
		m_aObject2D = NULL;
	}

	// �I������
	if (m_pObjBillboard != NULL)
	{// NULL����Ȃ�������
		m_pObjBillboard->Uninit();
		m_pObjBillboard = NULL;
	}
}

//==========================================================================
// �X�V����
//==========================================================================
void CNumber::Update(void)
{
	// �X�V����
	if (m_aObject2D != NULL)
	{
		m_aObject2D->Update();
	}

	// �X�V����
	if (m_pObjBillboard != NULL)
	{// NULL����Ȃ�������
		m_pObjBillboard->Update();
	}
}

//==========================================================================
// �`�揈��
//==========================================================================
void CNumber::Draw(void)
{
	// �`�揈��
	if (m_aObject2D != NULL)
	{
		m_aObject2D->Draw();
	}

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	if (m_pObjBillboard != NULL)
	{// NULL����Ȃ�������
		m_pObjBillboard->Draw();
	}

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// ���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================================================
// �I�u�W�F�N�g2D�I�u�W�F�N�g�̎擾
//==========================================================================
CObject2D *CNumber::GetMyObject(void)
{
	return m_aObject2D;
}

//==========================================================================
// �I�u�W�F�N�g�r���{�[�h�I�u�W�F�N�g�̎擾
//==========================================================================
CObjectBillboard *CNumber::GetMyObjectBillboard(void)
{
	return m_pObjBillboard;
}