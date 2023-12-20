//==========================================
//
//  ���S�̃N���X(logo.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "logo.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
// �ÓI�����o�ϐ��錾
//==========================================
const char* CLogo::m_apTextureFile[] =
{
	"data\\TEXTURE\\title\\title_00.png", // 0
	"data\\TEXTURE\\title\\title_01.png", // 1
	"data\\TEXTURE\\title\\title_02.png", // 2
	"data\\TEXTURE\\title\\title_03.png", // 3
	"data\\TEXTURE\\title\\title_11.png", // 4
	"data\\TEXTURE\\result\\lose.png", // 5
	"data\\TEXTURE\\result\\win.png" // 6
};

//==========================================
//  �R���X�g���N�^
//==========================================
CLogo::CLogo()
{
	m_bComplete = false;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CLogo::~CLogo()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CLogo::Init(void)
{
	//����������
	HRESULT hr = CObject3D::Init();

	//�^�C�v�̐ݒ�
	SetType(TYPE_OBJECT3D);

	//�T�C�Y��ݒ�
	SetSize(D3DXVECTOR3(24.0f, 6.0f, 0.0f));

	return hr;
}

//==========================================
//  �I������
//==========================================
void CLogo::Uninit(void)
{
	//�I��
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CLogo::Update(void)
{
	//�X�V
	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CLogo::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//�`��
	CObject3D::Draw();

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
