//=============================================================================
// 
//  �^�C�g������ [title.cpp]
//  Author : ���n�Ή�
//  Added by �������
// 
//=============================================================================
#include "title.h"
#include "input.h"
#include "fade.h"
#include "renderer.h"
#include "calculation.h"
#include "debugproc.h"
#include "sound.h"
#include "title_logo.h"
#include "fog.h"
#include "player_title.h"
#include "union_title.h"
#include "enemy.h"
#include "3D_Effect.h"

//==========================================
//  �萔��` ����
//==========================================
namespace
{
	const D3DXCOLOR TARGET_COLOR = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	const float START_LENGTH = 300.0f; // ��������
	const float END_LENGTH = 2000.0f; // �ڕW����
	const float FUNCTION = 0.02f; //�{��
	const float SWITCH_TIME = 140.0f;

	//���f���̔z�u�ʒu
	const D3DXVECTOR3 CENTER	= D3DXVECTOR3(0.0f, 0.0f, -2000.0f);
	const D3DXVECTOR3 IN_LEFT	= D3DXVECTOR3(-160.0f, 0.0f, -2900.0f);
	const D3DXVECTOR3 IN_RIGHT	= D3DXVECTOR3(160.0f, 0.0f, -2900.0f);
	const D3DXVECTOR3 OUT_LEFT	= D3DXVECTOR3(-300.0f, 0.0f, -3000.0f);
	const D3DXVECTOR3 OUT_RIGHT	= D3DXVECTOR3(300.0f, 0.0f, -3000.0f);
}
bool CTitle::m_bPressEnter = false;	// �G���^�[��������

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CTitle::CTitle() :
m_col(D3DXCOLOR(0.0f, 0.0, 0.0f, 1.0f)),
m_fLength(START_LENGTH)
{
	// �l�̃N���A
	m_fCnt = 0.0f;		// �؂�ւ��̃J�E���^�[
	m_pLogo = nullptr;
	m_nCntEmission = 0;	// �������J�E���^�[
	m_pUnionTitle = nullptr;	// �^�C�g���̍��̃v���C���[�I�u�W�F�N�g
	m_bPressEnter = false;		// �G���^�[��������
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CTitle::~CTitle()
{

}

//==========================================================================
// ����������
//==========================================================================
HRESULT CTitle::Init(void)
{
	// ���胊�Z�b�g
	m_bPressEnter = false;

	//�v���C���[�������Z�b�g
	CManager::GetInstance()->SetNumPlayer(0);

	// BGM�Đ�
	CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_BGM_TITLE);

	// ����������
	if (FAILED(CScene::Init()))
	{// ���s�����ꍇ
		return E_FAIL;
	}

	//�^�C�g�����S�̕\��
	if (m_pLogo == nullptr)
	{
		m_pLogo = CTitleLogo::Create();
	}

	// ����������
	Fog::Set(true);

	// �t�H�O�̒l��ݒ肷��
	Fog::SetStart(START_LENGTH);
	Fog::SetEnd(m_fLength);
	Fog::SetCol(m_col);

	// �v���C���[��u���Ă݂�
	m_pUnionTitle = CUnionTitle::Create(CENTER);
	CPlayerTitle::Create(IN_RIGHT, D3DXVECTOR3(0.0f, 0.0f, 0.0f), CPlayerTitle::PLAYER_ARM);
	CPlayerTitle::Create(IN_LEFT, D3DXVECTOR3(0.0f, 0.0f, 0.0f), CPlayerTitle::PLAYER_ARM);
	CPlayerTitle::Create(OUT_RIGHT, D3DXVECTOR3(0.0f, 0.0f, 0.0f), CPlayerTitle::PLAYER_LEG);
	CPlayerTitle::Create(OUT_LEFT, D3DXVECTOR3(0.0f, 0.0f, 0.0f), CPlayerTitle::PLAYER_BODY);

	// �i����ݒ�ナ�Z�b�g
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		CManager::GetInstance()->SetByPlayerPartsType(i, -1);
	}

	// ����
	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CTitle::Uninit(void)
{
	//���𕥂�
	Fog::Set(false);

	// �^�C�g�����S��j��
	if (m_pLogo != nullptr)
	{
		m_pLogo = nullptr;
	}

	// ���̃v���C���[��null
	m_pUnionTitle = nullptr;

	// �I������
	CScene::Uninit();
}

//==========================================================================
// �X�V����
//==========================================================================
void CTitle::Update(void)
{
	CManager::GetInstance()->GetDebugProc()->Print(
		"���݂̃��[�h�F�y�^�C�g���z\n"
		"�؂�ւ��F�y F �z\n\n");

	// �L�[�{�[�h���擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �Q�[���p�b�h���擾
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	if (CManager::GetInstance()->GetFade()->GetState() != CFade::STATE_NONE)
	{// �t�F�[�h���͔�����
		return;
	}

	//�^�C�g�����S���������Ă��Ȃ��Ƃ��͔�����
	if (m_pLogo == nullptr || !m_pLogo->GetComplete())
	{
		return;
	}

	//�t�H�O������
	WhiteOut();

	// �������̃C���^�[�o��
	int nIntervalEmission = 16;
	int nLife = 360;
	if (m_bPressEnter)
	{
		nIntervalEmission = 4;
		nLife = 90;
	}

	m_nCntEmission = (m_nCntEmission + 1) % nIntervalEmission;	// �������J�E���^�[

	if (m_nCntEmission == 0)
	{
		int nWidth = 20;
		float fWidthDistance = 100.0f;
		for (int i = 0; i < nWidth; i++)
		{
			D3DXVECTOR3 pos = CENTER;
			pos.x = ((static_cast<float>(nWidth) * 0.5f) * fWidthDistance) - fWidthDistance * i;
			pos.y = CENTER.y + 50.0f;
			pos.z += 400.0f + Random(-50, 50);

			D3DXVECTOR3 posDest = pos;
			posDest.z -= 1800.0f;
			posDest.y = 0.0f;
			posDest.x += Random(-20, 20) * 10.0f;

			float fColRand = Random(-20, 20) * 0.01f;
			CEffect3D *pEffect = CEffect3D::Create(
				pos,
				mylib_const::DEFAULT_VECTOR3,
				D3DXCOLOR(0.6f + fColRand, 0.6f + fColRand, 0.6f + fColRand, 1.0f),
				150.0f + (float)Random(-5, 5) * 10.0f,
				nLife,
				CEffect3D::MOVEEFFECT_ADD,
				CEffect3D::TYPE_SMOKEBLACK);

			// �ڕW�̈ʒu�ݒ�
			pEffect->SetPositionDest(posDest);
			pEffect->SetRotation(D3DXVECTOR3(0.0f, GetRandomCircleValue(), 0.0f));
		}
	}

	// �؂�ւ��̃J�E���^�[���Z
	m_fCnt += CManager::GetInstance()->GetDeltaTime();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, 0) == true)
	{
#if 1
		if (m_pUnionTitle != nullptr)
		{
			m_pUnionTitle->SetEnablePressEnter();
		}
#else
		// ���[�h�ݒ�
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_DECIDE);
#endif
	}

	if (m_fCnt >= SWITCH_TIME)
	{// �����J��
		// ���[�h�ݒ�
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RANKING);
	}
}

//==========================================================================
// �`�揈��
//==========================================================================
void CTitle::Draw(void)
{

}

//==========================================
//  �t�H�O����������
//==========================================
void CTitle::WhiteOut()
{
	// �ڕW�����܂ň����L�΂�
	m_fLength += (END_LENGTH - m_fLength) * FUNCTION;

	// �ڕW�F�܂ŕ␳����
	m_col += (TARGET_COLOR - m_col) * FUNCTION;

	// ������K�p����
	Fog::SetEnd(m_fLength);

	// �F��K�p����
	Fog::SetCol(m_col);

#ifdef _DEBUG
	// �L�[�{�[�h���擾
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	if (pInputKeyboard->GetTrigger(DIK_1))
	{
		// fog����
		Fog::Set(false);
	}
	if (pInputKeyboard->GetTrigger(DIK_2))
	{
		// fog����
		Fog::Set(true);
	}

	if (pInputKeyboard->GetTrigger(DIK_3))
	{
		// ���[�h�ݒ�
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_DECIDE);
	}

	if (pInputKeyboard->GetTrigger(DIK_4))
	{// �����J��
		// ���[�h�ݒ�
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RANKING);
	}
#endif
}
