//=============================================================================
// 
//  �V�[������ [scene.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "scene.h"
#include "renderer.h"
#include "calculation.h"
#include "Xload.h"
#include "map.h"
#include "fade.h"
#include "elevation.h"
#include "player.h"
#include "camera.h"

// �J�ڐ�
#include "game.h"
#include "title.h"
#include "tutorial.h"
#include "result.h"
#include "ranking.h"

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
CXLoad *CScene::m_pXLoad = NULL;				// X�t�@�C���̃I�u�W�F�N�g
CElevation *CScene::m_pObject3DMesh = NULL;		// �I�u�W�F�N�g3D���b�V���̃I�u�W�F�N�g

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CScene::CScene()
{
	// �ϐ��̃N���A
	m_mode = MODE_TITLE;
	memset(&m_pPlayer[0], 0, sizeof(m_pPlayer));
	memset(&m_pMultiCamera[0], NULL, sizeof(m_pMultiCamera));	// �J�����̃I�u�W�F�N�g
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CScene::~CScene()
{

}

//==========================================================================
// ��������
//==========================================================================
CScene *CScene::Create(CScene::MODE mode)
{
	// �����p�̃I�u�W�F�N�g
	CScene *pScene = NULL;

	if (pScene == NULL)
	{// NULL��������

		// ��������
		switch (mode)
		{
		case CScene::MODE_TITLE:
			pScene = DEBUG_NEW CTitle;
			break;

		case CScene::MODE_TUTORIAL:
			pScene = DEBUG_NEW CTutorial;
			break;

		case CScene::MODE_GAME:
			pScene = DEBUG_NEW CGame;
			break;

		case CScene::MODE_RESULT:
			pScene = DEBUG_NEW CResult;
			break;

		case CScene::MODE_RANKING:
			pScene = DEBUG_NEW CRanking;
			break;
		}

		if (pScene != NULL)
		{// �������̊m�ۂ��o���Ă�����

			// ���[�h�̐ݒ�
			pScene->m_mode = mode;
		}

		return pScene;
	}

	return NULL;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CScene::Init(void)
{
	HRESULT hr;

	//**********************************
	// X�t�@�C��
	//**********************************
	if (m_pXLoad != NULL)
	{// �m�ۂ���Ă�����
		return E_FAIL;
	}

	// �������m��
	m_pXLoad = DEBUG_NEW CXLoad;

	if (m_pXLoad == NULL)
	{// �������̊m�ۂ��o���Ă��Ȃ�������
		return E_FAIL;
	}
	m_pXLoad->Init();

	//**********************************
	// �}�b�v�̐���
	//**********************************
	if (FAILED(map::Create("data\\TEXT\\edit_info.txt")))
	{// ���s�����ꍇ
		return E_FAIL;
	}

	//**********************************
	// �N���̒n��
	//**********************************
	m_pObject3DMesh = CElevation::Create("data\\TEXT\\elevation_field.txt");

	// ����������
	hr = m_pXLoad->Init();

	if (FAILED(hr))
	{// ���������������s�����ꍇ
		return E_FAIL;
	}

	// �L��������
	for (int nCntPlayer = 0; nCntPlayer < mylib_const::MAX_PLAYER; nCntPlayer++)
	{
		m_pPlayer[nCntPlayer] = CPlayer::Create(nCntPlayer);
	}

	//**********************************
	// �}���`�J����
	//**********************************
	int nNumPlayer = mylib_const::MAX_PLAYER;
	D3DXVECTOR2 size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (nNumPlayer >= 2)
	{
		size.x *= 0.5f;
	}
	if (nNumPlayer >= 3)
	{
		size.y *= 0.5f;
	}

	for (int i = 0, nCntWidth = 0, nCntHeight = 0; i < nNumPlayer; i++)
	{
		if (m_pMultiCamera[i] != NULL)
		{// �m�ۂ���Ă�����
			return E_FAIL;
		}

		// �������m��
		m_pMultiCamera[i] = DEBUG_NEW CCamera;

		if (m_pMultiCamera[i] != NULL)
		{// �������̊m�ۂ��o���Ă�����

			// ����������
			hr = m_pMultiCamera[i]->Init();
			if (FAILED(hr))
			{// ���������������s�����ꍇ
				return E_FAIL;
			}

			// �r���[�|�[�g�̐ݒ�
			m_pMultiCamera[i]->SetViewPort(D3DXVECTOR3(nCntWidth * size.x, nCntHeight * size.y, 0.0f), size);
			m_pMultiCamera[i]->SetPlayerChaseIndex(i);
		}

		// �X�N���[���̉����Z
		nCntWidth = (nCntWidth + 1) % 2;
		if (nCntWidth == 0)
		{
			// �X�N���[���̏c���Z
			nCntHeight++;
		}
	}

	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CScene::Uninit(void)
{
	// X�t�@�C���̔j��
	if (m_pXLoad != NULL)
	{// �������̊m�ۂ��o���Ă�����

		// �I������
		m_pXLoad->Uninit();

		// �������̊J��
		delete m_pXLoad;
		m_pXLoad = NULL;
	}

	// �v���C���[�̔j��
	for (int nCntPlayer = 0; nCntPlayer < mylib_const::MAX_PLAYER; nCntPlayer++)
	{
		if (m_pPlayer[nCntPlayer] != NULL)
		{// �������̊m�ۂ��o���Ă�����

			m_pPlayer[nCntPlayer]->Uninit();
			m_pPlayer[nCntPlayer] = NULL;
		}
	}

	// �J�����̔j��
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		if (m_pMultiCamera[i] != NULL)
		{// �������̊m�ۂ��o���Ă�����

			// �I������
			m_pMultiCamera[i]->Uninit();
			delete m_pMultiCamera[i];
			m_pMultiCamera[i] = NULL;
		}
	}

}

//==========================================================================
// �X�V����
//==========================================================================
void CScene::Update(void)
{
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		if (m_pMultiCamera[i] == NULL)
		{
			continue;
		}

		// �J�����̐ݒ�
		m_pMultiCamera[i]->Update();
	}
}

//==========================================================================
// �`�揈��
//==========================================================================
void CScene::Draw(void)
{
	
}

//==========================================================================
// �V�[���̃��Z�b�g
//==========================================================================
void CScene::ResetScene(void)
{
	// �}�b�v
	map::Release();

	//**********************************
	// �}�b�v�̐���
	//**********************************
	if (FAILED(map::Create("data\\TEXT\\edit_info_boss.txt")))
	{// ���s�����ꍇ
		return;
	}
}

//==========================================================================
// ���݂̃��[�h�擾
//==========================================================================
CScene::MODE CScene::GetMode(void)
{
	return m_mode;
}

//==========================================================================
// X�t�@�C���̎擾
//==========================================================================
CXLoad *CScene::GetXLoad(void)
{
	return m_pXLoad;
}

//==========================================================================
// 3D�I�u�W�F�N�g�̎擾
//==========================================================================
CElevation *CScene::GetElevation(void)
{
	return m_pObject3DMesh;
}

//==========================================================================
// �v���C���[�̎擾
//==========================================================================
CPlayer *CScene::GetPlayer(int nIdx)
{
	return m_pPlayer[nIdx];
}

//==========================================================================
// �}���`�J�����̎擾
//==========================================================================
CCamera **CScene::GetMultiCamera(void)
{
	return &m_pMultiCamera[0];
}

//==========================================================================
// �v���C���[�̏I��
//==========================================================================
void CScene::UninitPlayer(int nIdx)
{
	m_pPlayer[nIdx] = NULL;
}
