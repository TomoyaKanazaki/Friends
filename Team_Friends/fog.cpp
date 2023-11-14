//==========================================
//
//  �t�H�O���Ǘ����閼�O���(fog.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "fog.h"
#include "manager.h"
#include "renderer.h"

//==========================================
//  �ϐ��錾
//==========================================
namespace
{
	bool m_bUse = true;
	float m_fStart;
	float m_fEnd;
	D3DXCOLOR m_col;
}

//==========================================
//  �g�p��Ԃ̐ݒ�
//==========================================
void Fog::Set(bool bUse)
{
	m_bUse = bUse;
}

//==========================================
//  �`�揈��
//==========================================
void Fog::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	if (m_bUse)
	{
		//����L����
		pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

		//���̐F��ݒ�
		pDevice->SetRenderState(D3DRS_FOGCOLOR, m_col);

		//���̏�Ԃ�ݒ�
		pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);
		pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);

		//���̔����͈͂�ݒ�
		pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&m_fStart));
		pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&m_fEnd));
	}
	else
	{
		//���𖳌���
		pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
	}
}

//==========================================
//  �F�̐ݒ�
//==========================================
void Fog::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//==========================================
//  �ő勗���̐ݒ�
//==========================================
void Fog::SetStart(float fStart)
{
	m_fStart = fStart;
}

//==========================================
//  �Œ዗���̐ݒ�
//==========================================
void Fog::SetEnd(float fEnd)
{
	m_fEnd = fEnd;
}

//==========================================
//  �F�̎擾
//==========================================
D3DXCOLOR Fog::GetCol(void)
{
	return m_col;
}

//==========================================
//  �ő勗���̎擾
//==========================================
float Fog::GetStart(void)
{
	return m_fStart;
}

//==========================================
//  �Œ዗���̎擾
//==========================================
float Fog::GetEnd(void)
{
	return m_fEnd;
}
