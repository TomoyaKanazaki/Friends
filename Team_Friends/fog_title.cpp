//==========================================
//
//  �^�C�g���ł̃t�H�O�̏���(fog_title.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "fog_title.h"
#include "fog.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXCOLOR TARGET_COLOR = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	const float START_LENGTH = 100.0f; // ��������
	const float END_LENGTH = 10000.0f; // �ڕW����
	const float FUNCTION = 0.01f; //�{��
}

//==========================================
//  �R���X�g���N�^
//==========================================
CFog_Title::CFog_Title()
{
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_fLength = START_LENGTH;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CFog_Title::~CFog_Title()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CFog_Title::Init()
{
	//����������
	Fog::Set(true);

	//�t�H�O�̒l��ݒ肷��
	Fog::SetStart(START_LENGTH);
	Fog::SetEnd(m_fLength);
	Fog::SetCol(m_col);
	
	//�^�C�v�ݒ�
	SetType(CObject::TYPE_NONE);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CFog_Title::Uninit()
{
	//���𕥂�
	Fog::Set(false);

	//���g��j������
	Release();
}

//==========================================
//  �X�V����
//==========================================
void CFog_Title::Update()
{
	// �ڕW�����܂ň����L�΂�
	m_fLength += (END_LENGTH - m_fLength) * FUNCTION;

	// �ڕW�F�܂ŕ␳����
	m_col += (TARGET_COLOR - m_col) * FUNCTION;

	// ������K�p����
	Fog::SetEnd(m_fLength);

	// �F��K�p����
	Fog::SetCol(m_col);
}

//==========================================
//  �`�揈��
//==========================================
void CFog_Title::Draw()
{

}
