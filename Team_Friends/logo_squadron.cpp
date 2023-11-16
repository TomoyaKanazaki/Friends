//==========================================
//
//  ����̃��S(logo_squadron.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "logo_squadron.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CLogo_Sqou::CLogo_Sqou()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CLogo_Sqou::~CLogo_Sqou()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CLogo_Sqou::Init(void)
{
	//����������
	HRESULT hr = CLogo::Init();

	//�e�N�X�`���̊��蓖��
	this->BindTexture(CManager::GetInstance()->GetTexture()->Regist(m_apTextureFile[2]));

	return hr;
}

//==========================================
//  �I������
//==========================================
void CLogo_Sqou::Uninit(void)
{
	//�I��
	CLogo::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CLogo_Sqou::Update(void)
{
	//�X�V
	CLogo::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CLogo_Sqou::Draw(void)
{
	//�`��
	CLogo::Draw();
}

//==========================================
//  ��������
//==========================================
CLogo_Sqou* CLogo_Sqou::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CLogo_Sqou* pLogo = DEBUG_NEW CLogo_Sqou;

	//����������
	pLogo->Init();

	//�l��ݒ�
	pLogo->SetPosition(pos);
	pLogo->SetRotation(rot);

	return pLogo;
}
