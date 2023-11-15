//==========================================
//
//  ���J�j�I���̃��S(logo_mekanion.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "logo_mekanion.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
// �ÓI�����o�ϐ��錾
//==========================================
const char* CLogo_Meka::m_pTextureFile = "data\\TEXTURE\\title\\title_01.png";

//==========================================
//  �R���X�g���N�^
//==========================================
CLogo_Meka::CLogo_Meka()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CLogo_Meka::~CLogo_Meka()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CLogo_Meka::Init(void)
{
	//����������
	HRESULT hr = CObject3D::Init();

	//�^�C�v�̐ݒ�
	SetType(TYPE_OBJECT3D);

	//�T�C�Y��ݒ�
	SetSize(D3DXVECTOR3(24.0f, 6.0f, 0.0f));

	//�e�N�X�`���̊��蓖��
	this->BindTexture(CManager::GetInstance()->GetTexture()->Regist(m_pTextureFile));

	return hr;
}

//==========================================
//  �I������
//==========================================
void CLogo_Meka::Uninit(void)
{
	//�I��
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CLogo_Meka::Update(void)
{
	//�X�V
	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CLogo_Meka::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�`��
	CObject3D::Draw();

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  ��������
//==========================================
CLogo_Meka* CLogo_Meka::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CLogo_Meka* pLogo = DEBUG_NEW CLogo_Meka;

	//����������
	pLogo->Init();

	//�l��ݒ�
	pLogo->SetPosition(pos);
	pLogo->SetRotation(rot);

	return pLogo;
}
