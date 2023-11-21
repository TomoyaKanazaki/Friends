//=============================================================================
// 
// �����蔻��I�u�W�F�N�g���� [collisionobject.cpp]
// Author : ���n�Ή�
// 
//=============================================================================
#include "collisionobject.h"
#include "renderer.h"
#include "texture.h"
#include "manager.h"

//==========================================================================
// �}�N����`
//==========================================================================

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CCollisionObject::CCollisionObject(int nPriority) : CObjectBillboard(nPriority)
{
	// �l�̃N���A
	m_fRadius = 0.0f;							// ���a
	m_nLife = 0;								// ����
	m_nMaxLife = 0;								// �ő����(�Œ�)
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CCollisionObject::~CCollisionObject()
{
	
}

//==========================================================================
// ��������
//==========================================================================
CCollisionObject *CCollisionObject::Create(void)
{
	// �����p�̃I�u�W�F�N�g
	CCollisionObject *pEffect = NULL;

	if (pEffect == NULL)
	{// NULL��������

		// �������̊m��
		pEffect = DEBUG_NEW CCollisionObject;

		if (pEffect != NULL)
		{// �������̊m�ۂ��o���Ă�����

			// ����������
			pEffect->Init();
		}

		return pEffect;
	}

	return NULL;
}

//==========================================================================
// ��������
//==========================================================================
CCollisionObject *CCollisionObject::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fRadius, const int nLife)
{
	// �����p�̃I�u�W�F�N�g
	CCollisionObject *pEffect = NULL;

	if (pEffect == NULL)
	{// NULL��������

		// �������̊m��
		pEffect = DEBUG_NEW CCollisionObject;

		if (pEffect != NULL)
		{// �������̊m�ۂ��o���Ă�����

			pEffect->SetPosition(pos);
			pEffect->SetMove(move);
			pEffect->m_fRadius = fRadius;
			pEffect->SetSize(D3DXVECTOR2(fRadius, fRadius));
			pEffect->m_nLife = nLife;

			// ����������
			HRESULT hr = pEffect->Init();
			if (FAILED(hr))
			{
				return NULL;
			}
		}

		return pEffect;
	}

	return NULL;
}

//==================================================================================
// �G�t�F�N�g�̏���������
//==================================================================================
HRESULT CCollisionObject::Init(void)
{
	HRESULT hr;

	// �e��ϐ��̏�����
	m_nMaxLife = m_nLife;						// �ő����(�Œ�)

	// ��ނ̐ݒ�
	SetType(TYPE_EFFECT3D);

	// ����������
	hr = CObjectBillboard::Init();
	if (FAILED(hr))
	{// ���s�����Ƃ�
		Uninit();
		return E_FAIL;
	}

	return S_OK;
}

//==================================================================================
// �G�t�F�N�g�̏I������
//==================================================================================
void CCollisionObject::Uninit(void)
{
	// �I������
	CObjectBillboard::Uninit();
}

//==================================================================================
// �G�t�F�N�g�̍X�V����
//==================================================================================
void CCollisionObject::Update(void)
{

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// �ʒu�X�V
	pos += move;

	// �ʒu�ݒ�
	SetPosition(pos);

	// �ړ��ʐݒ�
	SetMove(move);

	// �����̍X�V
	m_nLife--;

	// �T�C�Y�ݒ�
	SetSize(D3DXVECTOR2(m_fRadius, m_fRadius));

	if (m_nLife <= 0)
	{// �������s������
		Uninit();
		return;
	}

	// ���_���W�̐ݒ�
	SetVtx();

}

//==================================================================================
// �G�t�F�N�g�̕`�揈��
//==================================================================================
void CCollisionObject::Draw(void)
{
#ifdef _DEBUG
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);	//��ɕ`�悷��

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �`�揈��
	CObjectBillboard::Draw();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
#endif
}

//==========================================================================
// ���_���ݒ菈��
//==========================================================================
void CCollisionObject::SetVtx(void)
{
	// ���_�ݒ�
	CObjectBillboard::SetVtx();
}

