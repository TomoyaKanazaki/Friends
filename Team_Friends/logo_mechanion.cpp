//==========================================
//
//  MECHANION�̃��S(logo_mechanion.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "logo_mechanion.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
// �ÓI�����o�ϐ��錾
//==========================================
const char* CLogo_Mech::m_pTextureFile = "data\\TEXTURE\\title\\title_00.png";

//==========================================
//  �R���X�g���N�^
//==========================================
CLogo_Mech::CLogo_Mech()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CLogo_Mech::~CLogo_Mech()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CLogo_Mech::Init(void)
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
void CLogo_Mech::Uninit(void)
{
	//�I��
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CLogo_Mech::Update(void)
{
	//�X�V
	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CLogo_Mech::Draw(void)
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
CLogo_Mech* CLogo_Mech::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CLogo_Mech* pLogo = DEBUG_NEW CLogo_Mech;

	//����������
	pLogo->Init();

	//�l��ݒ�
	pLogo->SetPosition(pos);
	pLogo->SetRotation(rot);

	return pLogo;
}
