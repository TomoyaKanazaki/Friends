//=============================================================================
// 
//  �N�����̖ڃG�t�F�N�g���� [effect_startupeye.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "effect_startupeye.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"
#include "sound.h"
#include "3D_Effect.h"

//==========================================================================
// �萔��`
//==========================================================================
namespace
{
	const char* TEXTURE = "data\\TEXTURE\\anim\\effect_eye.png";
}

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
int CEffectStartupEye::m_nTexIdx = 0;	// �e�N�X�`���̃C���f�b�N�X�ԍ�

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CEffectStartupEye::CEffectStartupEye(int nPriority) : CObjectBillboardAnim(nPriority)
{
	// �l�̃N���A
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CEffectStartupEye::~CEffectStartupEye()
{
	
}

//==========================================================================
// �e�N�X�`���ǂݍ���
//==========================================================================
void CEffectStartupEye::LoadTexture(void)
{
	// �e�N�X�`���̓ǂݍ���
	m_nTexIdx = CManager::GetInstance()->GetTexture()->Regist(TEXTURE);
}

//==========================================================================
// ��������
//==========================================================================
CEffectStartupEye *CEffectStartupEye::Create(const D3DXVECTOR3 pos)
{
	// �����p�̃I�u�W�F�N�g
	CEffectStartupEye *pExplosion = NULL;

	if (pExplosion == NULL)
	{// NULL��������

		// �������̊m��
		pExplosion = DEBUG_NEW CEffectStartupEye;

		if (pExplosion != NULL)
		{// �������̊m�ۂ��o���Ă�����

			// �ʒu���蓖��
			pExplosion->SetPosition(pos);

			// ����������
			pExplosion->Init();
		}

		return pExplosion;
	}

	return NULL;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CEffectStartupEye::Init(void)
{

	// ��ނ̐ݒ�
	SetType(TYPE_OBJECTBILLBOARD);

	// �e�N�X�`���̊��蓖��
	if (m_nTexIdx == 0)
	{
		m_nTexIdx = CManager::GetInstance()->GetTexture()->Regist(TEXTURE);
	}

	// �e�N�X�`���̊��蓖��
	BindTexture(m_nTexIdx);

	// �T�C�Y�ݒ�
	SetSize(D3DXVECTOR2(512.0f, 288.0f) * 0.2f);


	// ����������
	CObjectBillboardAnim::Init(20, 3, 1);

	return S_OK;
}

//==========================================================================
// �X�V����
//==========================================================================
void CEffectStartupEye::Update(void)
{
	for (int i = 0; i < 2; i++)
	{
		D3DXVECTOR3 pos = GetPosition();
		pos.x = (256.0f * 0.2f) - i * (512.0f * 0.2f);

		CEffect3D *pEffect = CEffect3D::Create(
			pos,
			mylib_const::DEFAULT_VECTOR3,
			D3DXCOLOR(1.0f, 0.2f, 0.7f, 1.0f),
			450.0f,
			2,
			CEffect3D::MOVEEFFECT_SUB,
			CEffect3D::TYPE_POINT);
	}

	// �X�V����
	CObjectBillboardAnim::Update();
}

//==========================================================================
// �`�揈��
//==========================================================================
void CEffectStartupEye::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//// ���u�����f�B���O�����Z�����ɐݒ�
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �`�揈��
	CObjectBillboardAnim::Draw();

	//// ���u�����f�B���O�����ɖ߂�
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// ���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
