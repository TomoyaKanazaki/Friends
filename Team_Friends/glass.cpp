//==========================================
//
//  �Ђъ���|���S��(glass.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "glass.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const char* TEX_PASS = "data\\TEXTURE\\result\\glass.jpg"; // �e�N�X�`���p�X
}

//==========================================
//  �R���X�g���N�^
//==========================================
CGlass::CGlass() : CObject2D(8)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CGlass::~CGlass()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CGlass::Init(void)
{
	// ������
	HRESULT hr = CObject2D::Init();

	// ��ނ̐ݒ�
	CObject::SetType(CObject::TYPE_EFFECT2D);

	// �e�N�X�`���̊��蓖��
	BindTexture(CManager::GetInstance()->GetTexture()->Regist(TEX_PASS));

	// �ʒu�̐ݒ�
	SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	// �T�C�Y�̐ݒ�
	SetSize(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f));

	// �l��Ԃ�
	return hr;
}

//==========================================
//  �I������
//==========================================
void CGlass::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CGlass::Update(void)
{
	// �X�V
	CObject2D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CGlass::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDev = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �A���t�@�e�X�g��L���ɂ���
	pDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDev->SetRenderState(D3DRS_ALPHAREF, 0);

	// �`�揈��
	CObject2D::Draw();

	// ���u�����f�B���O�����ɖ߂�
	pDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �A���t�@�e�X�g��L���ɂ���
	pDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDev->SetRenderState(D3DRS_ALPHAREF, 0);
}

//==========================================
//  ��������
//==========================================
CGlass* CGlass::Create()
{
	// �C���X�^���X����
	CGlass* pGlass = DEBUG_NEW CGlass;

	// NULL�`�F�b�N
	if (pGlass == nullptr) { return nullptr; }

	// ����������
	pGlass->Init();

	// �l��Ԃ�
	return pGlass;
}
