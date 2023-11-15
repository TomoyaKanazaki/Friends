//==========================================
//
//  �������S(logo_complete.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "logo_complete.h"
#include "manager.h"
#include "texture.h"

//==========================================
// �ÓI�����o�ϐ��錾
//==========================================
const char* CLogo_Comp::m_pTextureFile = "data\\TEXTURE\\title\\title_03.png";

//==========================================
//  �R���X�g���N�^
//==========================================
CLogo_Comp::CLogo_Comp()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CLogo_Comp::~CLogo_Comp()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CLogo_Comp::Init(void)
{
	//����������
	HRESULT hr = CObject3D::Init();

	//�^�C�v�̐ݒ�
	SetType(TYPE_OBJECT3D);

	//�T�C�Y��ݒ�
	SetSize(D3DXVECTOR3(3200.0f, 800.0f, 0.0f));

	//�e�N�X�`���̊��蓖��
	this->BindTexture(CManager::GetInstance()->GetTexture()->Regist(m_pTextureFile));

	return hr;
}

//==========================================
//  �I������
//==========================================
void CLogo_Comp::Uninit(void)
{
	//�I��
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CLogo_Comp::Update(void)
{
	//�p�x���擾
	D3DXVECTOR3 rot = GetRotation();
	rot.x += 0.02f;
	rot.y += 0.02f;
	rot.z += 0.02f;

	//�p�x���X�V
	SetRotation(rot);

	//�X�V
	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CLogo_Comp::Draw(void)
{
	//�`��
	CObject3D::Draw();
}

//==========================================
//  ��������
//==========================================
CLogo_Comp* CLogo_Comp::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CLogo_Comp *pLogo = DEBUG_NEW CLogo_Comp;

	//����������
	pLogo->Init();

	//�l��ݒ�
	pLogo->SetPosition(pos);
	pLogo->SetRotation(rot);

	return pLogo;
}