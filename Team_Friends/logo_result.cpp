//==========================================
//
//  ���U���g���S(logo_result.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "logo_result.h"
#include "manager.h"
#include "texture.h"
#include "camera.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 DIFF_POS = D3DXVECTOR3(0.0f, 15.0f, 50.0f);
}

//==========================================
//  �R���X�g���N�^
//==========================================
CLogoResult::CLogoResult()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CLogoResult::~CLogoResult()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CLogoResult::Init(void)
{
	// ����������
	HRESULT hr = CLogo::Init();

	// �^�C�v�̐ݒ�
	SetType(CObject::TYPE_OBJECT3D);

	// �e�N�X�`���̊��蓖��
	BindTexture(CManager::GetInstance()->GetTexture()->Regist(m_apTextureFile[5]));

	//���S�̈ʒu��ݒ�
	SetPosition(CManager::GetInstance()->GetCamera()->GetPositionV() + DIFF_POS);

	return hr;
}

//==========================================
//  �I������
//==========================================
void CLogoResult::Uninit(void)
{
	CLogo::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CLogoResult::Update(void)
{
	CLogo::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CLogoResult::Draw(void)
{
	CLogo::Draw();
}

//==========================================
//  ��������
//==========================================
CLogoResult* CLogoResult::Create()
{
	// �C���X�^���X����
	CLogoResult* pLogo = DEBUG_NEW CLogoResult;

	// NULL�`�F�b�N
	if (pLogo == nullptr) { return nullptr; }

	// ����������
	pLogo->Init();

	// �l��Ԃ�
	return pLogo;
}
