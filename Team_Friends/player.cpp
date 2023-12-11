//=============================================================================
// 
//  �v���C���[���� [player.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "game.h"
#include "player.h"
#include "player_union.h"
#include "camera.h"
#include "manager.h"
#include "debugproc.h"
#include "renderer.h"
#include "input.h"
#include "enemy.h"
#include "calculation.h"
#include "score.h"
#include "texture.h"
#include "Xload.h"
#include "model.h"
#include "hp_gauge.h"
#include "objectChara.h"
#include "elevation.h"
#include "shadow.h"
#include "particle.h"
#include "3D_Effect.h"
#include "ballast.h"
#include "impactwave.h"
#include "sound.h"
#include "enemymanager.h"
#include "bullet.h"
#include "stage.h"
#include "objectX.h"
#include "instantfade.h"
#include "fade.h"
#include "listmanager.h"
#include "item.h"
#include "injectiontable.h"
#include "object_circlegauge2D.h"
#include "statuswindow.h"
#include "collisionobject.h"
#include "limitereamanager.h"
#include "beam.h"

// �h����
#include "tutorialplayer.h"

//==========================================================================
// �萔��`
//==========================================================================
namespace
{
	const char* CHARAFILE = "data\\TEXT\\character\\player\\motion_player.txt";	// �L�����N�^�[�t�@�C��
	const char* EVOLUSIONFILE[CGameManager::STATUS_MAX] =						// �i����̃t�@�C��
	{
		"data\\TEXT\\character\\player\\motion_pUPArm.txt",		// �Η�
		"data\\TEXT\\character\\player\\motion_pUPLeg.txt",		// �쓮��
		"data\\TEXT\\character\\player\\motion_pUPBody.txt",	// �ϋv
	};
	const char* TEXTURE_INITPLAYER[mylib_const::MAX_PLAYER][mylib_const::MAX_PLAYER] =	// �����v���C���[�̃e�N�X�`��
	{
		{// �����v���C���[
			"data\\TEXTURE\\player\\init\\init_UV.jpg",
			"data\\TEXTURE\\player\\init\\init_UV_Blue.jpg",
			"data\\TEXTURE\\player\\init\\init_UV_Green.jpg",
			"data\\TEXTURE\\player\\init\\init_UV_Yellow.jpg",
		},
		{// �ύX�^�O1(�r)
			"data\\TEXTURE\\player\\pUP_arm01\\arm_UV_Red.jpg",
			"data\\TEXTURE\\player\\pUP_arm01\\arm_UV_Blue.jpg",
			"data\\TEXTURE\\player\\pUP_arm01\\arm_UV_Green.jpg",
			"data\\TEXTURE\\player\\pUP_arm01\\arm_UV_Yellow.jpg",
		},
		{// �ύX�^�O2(�r)
			"data\\TEXTURE\\player\\pUP_leg01\\feet_UV_Red.jpg",
			"data\\TEXTURE\\player\\pUP_leg01\\feet_UV_Blue.jpg",
			"data\\TEXTURE\\player\\pUP_leg01\\feet_UV_Green.jpg",
			"data\\TEXTURE\\player\\pUP_leg01\\feet_UV_Yellow.jpg",
		},
		{// �ύX�^�O3(��)
			"data\\TEXTURE\\player\\pUP_body01\\body_UV_Red.jpg",
			"data\\TEXTURE\\player\\pUP_body01\\body_UV_Blue.jpg",
			"data\\TEXTURE\\player\\pUP_body01\\body_UV_Green.jpg",
			"data\\TEXTURE\\player\\pUP_body01\\body_UV_Yellow.jpg",
		}
	};
	const D3DXCOLOR EFFECTCOLOR[mylib_const::MAX_PLAYER] =	// �G�t�F�N�g�̐F
	{
		{ 0.9f, 0.1f, 0.1f, 1.0f },
		{ 0.1f, 0.1f, 0.9f, 1.0f },
		{ 0.1f, 0.9f, 0.1f, 1.0f },
		{ 0.9f, 0.6f, 0.1f, 1.0f },
	};
	const float JUMP = 20.0f * 1.5f;	// �W�����v�͏����l
	const int INVINCIBLE_INT = 2;		// ���G�̊Ԋu
	const int INVINCIBLE_TIME = 90;		// ���G�̎���
	const int DEADTIME = 120;			// ���S���̎���
	const int FADEOUTTIME = 60;			// �t�F�[�h�A�E�g�̎���
	const int MAX_ATKCOMBO = 2;			// �U���R���{�̍ő吔
	const int INTERVAL_ATK = 15;		// �U���̗P�\
	const int MAX_BUFFSTATUS = 100;		// �X�e�[�^�X�̃o�t�ő�l
}

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
bool CPlayer::m_bAllLandInjectionTable = false;						// �S���̎ˏo�䒅�n����
bool CPlayer::m_bLandInjectionTable[mylib_const::MAX_PLAYER] = {};	// �ˏo��̒��n����
int CPlayer::m_nChaseTopIdx = 0;	// �Ǐ]�̐擪�C���f�b�N�X�ԍ�

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CPlayer::CPlayer(int nPriority) : CObjectChara(nPriority)
{
	// �l�̃N���A
	// ���L�ϐ�
	m_bJump = false;					// �W�����v�����ǂ���
	m_bLandOld = false;					// �ߋ��̒��n���
	m_bHitStage = false;				// �X�e�[�W�̓����蔻��
	m_bLandField = false;				// �t�B�[���h�̒��n����
	m_bHitWall = false;					// �ǂ̓����蔻��
	m_nCntWalk = 0;						// ���s�J�E���^�[
	m_nCntInputAtk = 0;					// �U���̓��̓J�E���^�[
	m_nAtkLevel = 0;					// �U���̒i�K
	m_state = STATE_NONE;				// ���
	m_pMotion = NULL;					// ���[�V�����̏��
	m_sMotionFrag.bATK = false;			// ���[�V�����̃t���O
	m_sMotionFrag.bJump = false;		// ���[�V�����̃t���O
	m_sMotionFrag.bKnockBack = false;	// ���[�V�����̃t���O
	m_sMotionFrag.bDead = false;		// ���[�V�����̃t���O
	m_sMotionFrag.bMove = false;		// ���[�V�����̃t���O

	// �v���C�x�[�g�ϐ�
	memset(&m_sStatus, 0, sizeof(m_sStatus));		// �X�e�[�^�X���
	m_Oldstate = STATE_NONE;						// �O��̏��
	m_mMatcol = mylib_const::DEFAULT_COLOR;			// �}�e���A���̐F
	m_posKnokBack = mylib_const::DEFAULT_VECTOR3;	// �m�b�N�o�b�N�̈ʒu
	m_KnokBackMove = mylib_const::DEFAULT_VECTOR3;	// �m�b�N�o�b�N�̈ړ���
	m_nCntState = 0;								// ��ԑJ�ڃJ�E���^�[
	m_nEvolveType = 0;								// �i����̎��
	m_nNextEvolveType = 0;							// ���̐i����
	m_nMyPlayerIdx = 0;								// �v���C���[�C���f�b�N�X�ԍ�
	m_pShadow = NULL;								// �e�̏��
	m_pTargetP = NULL;								// �ڕW�̒n�_
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CPlayer::~CPlayer()
{

}

//==========================================================================
// ��������
//==========================================================================
CPlayer *CPlayer::Create(int nIdx)
{
	// �����p�̃I�u�W�F�N�g
	CPlayer *pPlayer = NULL;

	if (pPlayer == NULL)
	{// NULL��������

		// �������̊m��
		switch (CManager::GetInstance()->GetMode())
		{
		case CScene::MODE_GAME:
			pPlayer = DEBUG_NEW CPlayer;
			break;

		case CScene::MODE_TUTORIAL:
			pPlayer = DEBUG_NEW CTutorialPlayer;
			break;

		default:
			return NULL;
			break;
		}

		if (pPlayer != NULL)
		{// �������̊m�ۂ��o���Ă�����

			// �v���C���[�C���f�b�N�X�ԍ�
			pPlayer->m_nMyPlayerIdx = nIdx;

			// ����������
			pPlayer->Init();
		}

		return pPlayer;
	}

	return NULL;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CPlayer::Init(void)
{
	// ��ނ̐ݒ�
	SetType(TYPE_PLAYER);

	m_state = STATE_NONE;	// ���
	m_nCntState = 0;		// ��ԑJ�ڃJ�E���^�[
	m_bLandOld = true;		// �O��̒��n���
	m_bAllLandInjectionTable = false;	// �S���̎ˏo�䒅�n����
	memset(&m_bLandInjectionTable[0], false, sizeof(m_bLandInjectionTable));	// �ˏo��̒��n����
	m_nChaseTopIdx = 0;		// �Ǐ]�̐擪�C���f�b�N�X�ԍ�

	// �L�����쐬
	HRESULT hr = SetCharacter(CHARAFILE);

	if (FAILED(hr))
	{// ���s���Ă�����
		return E_FAIL;
	}

	// ���[�V�����̐�������
	m_pMotion = CMotion::Create(CHARAFILE);

	// �I�u�W�F�N�g�L�����N�^�[�̏��擾
	CObjectChara *pObjChar = GetObjectChara();

	// ���[�V�����̐ݒ�
	m_pMotion->SetModel(pObjChar->GetModel(), pObjChar->GetNumModel(), CObjectChara::GetObjectChara());

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �e�̐���
	m_pShadow = CShadow::Create(pos, 50.0f);

	// �|�[�Y�̃��Z�b�g
	m_pMotion->ResetPose(MOTION_DEF);

	//if (m_nMyPlayerIdx == 2 ||
	//	m_nMyPlayerIdx == 3)
	//{// ����
	//	SetEvolusion(CGameManager::STATUS_POWER);
	//}
	//if (m_nMyPlayerIdx == 0)
	//{// ��
	//	SetEvolusion(CGameManager::STATUS_LIFE);
	//}

	//if (m_nMyPlayerIdx == 1)
	//{// ��
	//	SetEvolusion(CGameManager::STATUS_SPEED);
	//}
	//SetEvolusion(CGameManager::STATUS_POWER);

	// �v���C���[���̃C���f�b�N�X�ǉ�
	BindByPlayerIdxTexture();

	// �o�t�v�Z
	m_sStatus.fPowerBuff = 1.0f;
	m_sStatus.fSpeedBuff = 1.0f;
	m_sStatus.fLifeBuff = 1.0f;
	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CPlayer::Uninit(void)
{
	if (m_pMotion != NULL)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = NULL;
	}

	// �e������
	if (m_pShadow != NULL)
	{
		//m_pShadow->Uninit();
		m_pShadow = NULL;
	}

	// �I������
	CObjectChara::Uninit();

	// ���[�h�ʏI������
	UninitByMode();
}

//==========================================================================
// ���[�h�ʏI������
//==========================================================================
void  CPlayer::UninitByMode(void)
{
	CScene *pScene = CManager::GetInstance()->GetScene();
	if (pScene != NULL)
	{
		// �v���C���[��NULL
		CManager::GetInstance()->GetScene()->UninitPlayer(m_nMyPlayerIdx);
	}
}

//==========================================================================
// �I������
//==========================================================================
void CPlayer::Kill(void)
{

	my_particle::Create(GetPosition(), my_particle::TYPE_ENEMY_FADE);

	// �e������
	if (m_pShadow != NULL)
	{
		m_pShadow->Uninit();
		m_pShadow = NULL;
	}
}

//==========================================================================
// �X�V����
//==========================================================================
void CPlayer::Update(void)
{
	if (IsDeath() == true)
	{
		return;
	}

	// �L�[�{�[�h���擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	if (pInputKeyboard->GetTrigger(DIK_F5) == true)
	{// F5�Ń��Z�b�g
		SetPosition(D3DXVECTOR3(0.0f, 0.0f, -1000.0f));
		SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	// �G�f�B�b�g���͔�����
	if (CGame::GetElevation()->IsEdit())
	{
		return;
	}

	// �G�f�B�b�g���͔�����
	if (CGame::GetEditType() != CGame::EDITTYPE_OFF)
	{
		return;
	}

	// �R���{���o���͔�����
	if (CGame::GetEnemyManager()->GetState() == CEnemyManager::STATE_COMBOANIM)
	{
		return;
	}

	// �ߋ��̈ʒu�ۑ�
	SetOldPosition(GetPosition());

	// ����
	Controll();

	// ���[�V�����̐ݒ菈��
	MotionSet();

	// ���[�V�����X�V
	if (m_pMotion != NULL)
	{
		m_pMotion->Update(m_sStatus.fSpeedBuff);
	}

	// �U������
	Atack();

	// ��ԍX�V
	UpdateState();

	// �Q�[�W�̊����X�V
	CStatusWindow *pStatusWindow = CGame::GetStatusWindow(m_nMyPlayerIdx);
	if (pStatusWindow != NULL)
	{
		pStatusWindow->GetGauge(CGameManager::STATUS_LIFE)->SetRateDest((float)GetLife() / (float)GetLifeOrigin());
	}

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 posCenter = GetCenterPosition();

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// �����擾
	D3DXVECTOR3 rot = GetRotation();

	// �Ǐ]�ڕW�̏��ݒ�
	if (m_nChaseTopIdx == m_nMyPlayerIdx)
	{
		// �J�����̏��擾
		CCamera *pCamera = CManager::GetInstance()->GetCamera();
		pCamera->SetTargetPosition(pos);
		pCamera->SetTargetRotation(rot);
	}

	// �e�̈ʒu�X�V
	if (m_pShadow != NULL)
	{
		m_pShadow->SetPosition(D3DXVECTOR3(pos.x, m_pShadow->GetPosition().y, pos.z));
	}

	// ���[�V�����̏��擾
	if (m_pMotion != NULL)
	{
		CMotion::Info aInfo = m_pMotion->GetInfo(MOTION_WALK);

		// �U�����̑����擾
		int nNumAttackInfo = aInfo.nNumAttackInfo;

		int nCntEffect = 0;
		int nNumEffect = GetEffectParentNum();
		for (int i = 0; i < mylib_const::MAX_OBJ; i++)
		{
			CEffect3D *pEffect = GetEffectParent(i);
			if (pEffect == NULL)
			{// NULL��������
				continue;
			}

			// �G�t�F�N�g�̈ʒu�X�V
			pEffect->UpdatePosition(GetModel()[aInfo.AttackInfo[0]->nCollisionNum]->GetWorldMtx(), GetRotation());
			nCntEffect++;
			if (nNumEffect <= nCntEffect)
			{
				break;
			}
		}
	}

#if 0
	// �f�o�b�O�\��
	CManager::GetInstance()->GetDebugProc()->Print(
		"------------------[�v���C���[�̑���]------------------\n"
		"�ʒu�F�yX�F%f, Y�F%f, Z�F%f�z�yX�F%f, Y�F%f, Z�F%f�z �yW / A / S / D�z\n"
		"�����F�yX�F%f, Y�F%f, Z�F%f�z �yZ / C�z\n"
		"�ړ��ʁF�yX�F%f, Y�F%f, Z�F%f�z\n"
		"�̗́F�y%d�z\n", pos.x, pos.y, pos.z, posCenter.x, posCenter.y, posCenter.z, rot.x, rot.y, rot.y, move.x, move.y, move.z, GetLife());
#endif

}

//==========================================================================
// ���쏈��
//==========================================================================
void CPlayer::Controll(void)
{

	// �L�[�{�[�h���擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �Q�[���p�b�h���擾
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	// �J�����̏��擾
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	// �J�����̌����擾
	D3DXVECTOR3 Camerarot = pCamera->GetRotation();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 newPosition = GetPosition();
	D3DXVECTOR3 sakiPos = GetPosition();

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// �����擾
	D3DXVECTOR3 rot = GetRotation();

	// �ڕW�̌����擾
	float fRotDest = GetRotDest();

	// ���݂̎�ގ擾
	int nMotionType = m_pMotion->GetType();

	// �ړ��ʎ擾
	float fMove = GetVelocity() * m_sStatus.fSpeedBuff;

	// �o�ߎ��Ԏ擾
	float fCurrentTime = CManager::GetInstance()->GetDeltaTime();

	if (CGame::GetGameManager()->IsControll())
	{// �s���ł���Ƃ�

		if (m_pMotion->IsGetMove(nMotionType) == 1 &&
			m_state != STATE_DEAD &&
			m_state != STATE_FADEOUT &&
			m_state != STATE_COMPACTUNION &&
			m_state != STATE_RELEASEUNION &&
			m_state != STATE_EVOLUSION)
		{// �ړ��\���[�V�����̎�

			if (pInputKeyboard->GetPress(DIK_A) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).x < 0)
			{//���L�[�������ꂽ,���ړ�

				// �ړ����ɂ���
				m_sMotionFrag.bMove = true;

				if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y > 0)
				{//A+W,����ړ�

					move.x += sinf(-D3DX_PI * 0.25f + Camerarot.y) * fMove;
					move.z += cosf(-D3DX_PI * 0.25f + Camerarot.y) * fMove;
					fRotDest = D3DX_PI * 0.75f + Camerarot.y;
				}
				else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y < 0)
				{//A+S,�����ړ�

					move.x += sinf(-D3DX_PI * 0.75f + Camerarot.y) * fMove;
					move.z += cosf(-D3DX_PI * 0.75f + Camerarot.y) * fMove;
					fRotDest = D3DX_PI * 0.25f + Camerarot.y;
				}
				else
				{//A,���ړ�

					move.x += sinf(-D3DX_PI * 0.5f + Camerarot.y) * fMove;
					move.z += cosf(-D3DX_PI * 0.5f + Camerarot.y) * fMove;
					fRotDest = D3DX_PI * 0.5f + Camerarot.y;
				}
			}
			else if (pInputKeyboard->GetPress(DIK_D) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).x > 0)
			{//D�L�[�������ꂽ,�E�ړ�

				// �ړ����ɂ���
				m_sMotionFrag.bMove = true;

				if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y > 0)
				{//D+W,�E��ړ�

					move.x += sinf(D3DX_PI * 0.25f + Camerarot.y) * fMove;
					move.z += cosf(D3DX_PI * 0.25f + Camerarot.y) * fMove;
					fRotDest = -D3DX_PI * 0.75f + Camerarot.y;
				}
				else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y < 0)
				{//D+S,�E���ړ�

					move.x += sinf(D3DX_PI * 0.75f + Camerarot.y) * fMove;
					move.z += cosf(D3DX_PI * 0.75f + Camerarot.y) * fMove;
					fRotDest = -D3DX_PI * 0.25f + Camerarot.y;
				}
				else
				{//D,�E�ړ�

					move.x += sinf(D3DX_PI * 0.5f + Camerarot.y) * fMove;
					move.z += cosf(D3DX_PI * 0.5f + Camerarot.y) * fMove;
					fRotDest = -D3DX_PI * 0.5f + Camerarot.y;
				}
			}
			else if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y > 0)
			{//W�������ꂽ�A��ړ�

				// �ړ����ɂ���
				m_sMotionFrag.bMove = true;
				move.x += sinf(D3DX_PI * 0.0f + Camerarot.y) * fMove;
				move.z += cosf(D3DX_PI * 0.0f + Camerarot.y) * fMove;
				fRotDest = D3DX_PI * 1.0f + Camerarot.y;
			}
			else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y < 0)
			{//S�������ꂽ�A���ړ�

				// �ړ����ɂ���
				m_sMotionFrag.bMove = true;
				move.x += sinf(D3DX_PI * 1.0f + Camerarot.y) * fMove;
				move.z += cosf(D3DX_PI * 1.0f + Camerarot.y) * fMove;
				fRotDest = D3DX_PI * 0.0f + Camerarot.y;
			}
			else
			{
				// �ړ������ǂ���
				m_sMotionFrag.bMove = false;
			}

		}
		else if (m_pMotion->IsGetMove(nMotionType) == 0 &&
			m_state != STATE_DEAD &&
			m_state != STATE_FADEOUT &&
			m_state != STATE_COMPACTUNION &&
			m_state != STATE_RELEASEUNION&&
			m_state != STATE_EVOLUSION)
		{
			if (pInputKeyboard->GetPress(DIK_A) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).x < 0)
			{//���L�[�������ꂽ,���ړ�

				if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y > 0)
				{//A+W,����ړ�
					fRotDest = D3DX_PI * 0.75f + Camerarot.y;
				}
				else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y < 0)
				{//A+S,�����ړ�
					fRotDest = D3DX_PI * 0.25f + Camerarot.y;
				}
				else
				{//A,���ړ�
					fRotDest = D3DX_PI * 0.5f + Camerarot.y;
				}
			}
			else if (pInputKeyboard->GetPress(DIK_D) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).x > 0)
			{//D�L�[�������ꂽ,�E�ړ�

				if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y > 0)
				{//D+W,�E��ړ�
					fRotDest = -D3DX_PI * 0.75f + Camerarot.y;
				}
				else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y < 0)
				{//D+S,�E���ړ�
					fRotDest = -D3DX_PI * 0.25f + Camerarot.y;
				}
				else
				{//D,�E�ړ�
					fRotDest = -D3DX_PI * 0.5f + Camerarot.y;
				}
			}
			else if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y > 0)
			{//W�������ꂽ�A��ړ�
				fRotDest = D3DX_PI * 1.0f + Camerarot.y;
			}
			else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y < 0)
			{//S�������ꂽ�A���ړ�
				fRotDest = D3DX_PI * 0.0f + Camerarot.y;
			}
		}
	}

	if (m_state != STATE_COMPACTUNION &&
		m_state != STATE_RELEASEUNION)
	{// �ړ���
		m_nCntWalk = (m_nCntWalk + 1) % 4;

		if (m_nCntWalk == 0)
		{
			// ���[�V�����̏��擾
			CMotion::Info aInfo = m_pMotion->GetInfo(MOTION_WALK);

			// �U�����̑����擾
			int nNumAttackInfo = aInfo.nNumAttackInfo;

			CEffect3D *pEffect = NULL;
			// ����̈ʒu
			for (int nCntAttack = 0; nCntAttack < nNumAttackInfo; nCntAttack++)
			{
				D3DXVECTOR3 weponpos = m_pMotion->GetAttackPosition(GetModel(), *aInfo.AttackInfo[nCntAttack]);

				D3DXVECTOR3 ModelRot = GetModel()[aInfo.AttackInfo[nCntAttack]->nCollisionNum]->GetRotation();
				ModelRot.x = GetModel()[0]->GetRotation().z;

				//D3DXVECTOR3 ModelRot = WorldMtxChangeToRotation(GetModel()[aInfo.AttackInfo[nCntAttack]->nCollisionNum]->GetWorldMtx());

				// ��
				float fMove = 5.5f + Random(-20, 20) * 0.1f;
				float fRot = Random(-20, 20) * 0.01f;

				pEffect = CEffect3D::Create(
					weponpos,
					D3DXVECTOR3(
						sinf(ModelRot.x) * (sinf(D3DX_PI + rot.y + fRot) * fMove),
						cosf(D3DX_PI + ModelRot.x) * fMove,
						sinf(ModelRot.x) * (cosf(D3DX_PI + rot.y + fRot) * fMove)),
					D3DXCOLOR(1.0f + Random(-10, 0) * 0.01f, 0.0f, 0.0f, 1.0f),
					40.0f + (float)Random(-10, 10),
					15,
					CEffect3D::MOVEEFFECT_ADD,
					CEffect3D::TYPE_SMOKE);

				if (pEffect != NULL)
				{
					// �Z�b�g�A�b�v�ʒu�ݒ�
					pEffect->SetUp(aInfo.AttackInfo[nCntAttack]->Offset, GetModel()[aInfo.AttackInfo[nCntAttack]->nCollisionNum]->GetPtrWorldMtx(), CObject::GetObject(), SetEffectParent(pEffect));
				}

				fRot = Random(-20, 20) * 0.01f;
				// ��
				pEffect = CEffect3D::Create(
					weponpos,
					D3DXVECTOR3(
						sinf(ModelRot.x) * (sinf(D3DX_PI + rot.y + fRot) * fMove),
						cosf(D3DX_PI + ModelRot.x) * fMove,
						sinf(ModelRot.x) * (cosf(D3DX_PI + rot.y + fRot) * fMove)),
					D3DXCOLOR(0.8f + Random(-10, 0) * 0.01f, 0.5f + Random(-10, 0) * 0.01f, 0.0f, 1.0f),
					25.0f + (float)Random(-5, 5),
					15,
					CEffect3D::MOVEEFFECT_ADD,
					CEffect3D::TYPE_SMOKE);
				if (pEffect != NULL)
				{
					// �Z�b�g�A�b�v�ʒu�ݒ�
					pEffect->SetUp(aInfo.AttackInfo[nCntAttack]->Offset, GetModel()[aInfo.AttackInfo[nCntAttack]->nCollisionNum]->GetPtrWorldMtx(), CObject::GetObject(), SetEffectParent(pEffect));
				}
			}
		}
	}

	// �ړ��ʉ��Z
	newPosition.x += move.x;
	newPosition.z += move.z;

	sakiPos.x = newPosition.x + sinf(D3DX_PI + rot.y) * GetRadius();
	sakiPos.z = newPosition.z + cosf(D3DX_PI + rot.y) * GetRadius();

	// �p�x�̐��K��
	RotNormalize(fRotDest);

	// ���݂ƖڕW�̍��������߂�
	float fRotDiff = fRotDest - rot.y;

	// �p�x�̐��K��
	RotNormalize(fRotDiff);

	// �p�x�̕␳������
	rot.y += fRotDiff * 0.15f;

	// �p�x�̐��K��
	RotNormalize(rot.y);

	// �d�͏���
	if (m_state != STATE_KNOCKBACK && m_state != STATE_DMG && m_state != STATE_DEAD && m_state != STATE_FADEOUT && m_state != STATE_COMPACTUNION)
	{
		move.y -= mylib_const::GRAVITY;

		// �ʒu�X�V
		newPosition.y += move.y;
		sakiPos.y = newPosition.y;
	}

	// �ˏo��̒��n����
	m_bLandInjectionTable[m_nMyPlayerIdx] = false;

	//**********************************
	// �����蔻��
	//**********************************
	bool bLandStage = Collision(sakiPos, move);

	bool bMove = false;
	if (m_bLandOld == false && bLandStage == true)
	{// �O��͒��n���Ă��Ȃ��āA����͒��n���Ă���ꍇ

		bMove = false;
	}

	if (m_bLandOld == true && bLandStage == true)
	{// �O�����������n���Ă���ꍇ
		bMove = true;
	}

	if (m_bHitWall == false && 
		(bLandStage == false || bMove == true || m_bLandField == true || m_bJump == true || m_sMotionFrag.bKnockBack == true || m_sMotionFrag.bDead == true))
	{
		pos.x = newPosition.x;
		pos.z = newPosition.z;
		pos.y = sakiPos.y;
		Collision(pos, move);

		// �O��͏���Ă����Ƃɂ���
		m_bLandOld = true;
	}
	else
	{
		D3DXVECTOR3 posOld = GetOldPosition();
		pos.x = posOld.x;
		pos.z = posOld.z;
		pos = posOld;
		move.x = 0.0f;
		pos.y -= mylib_const::GRAVITY * 7.0f;

		if (m_bJump == false)
		{
			m_bJump = true;
		}

		Collision(pos, move);
	}

	// �ʒu�X�V
	//pos.y += move.y;

	// �����␳
	if (m_state != STATE_KNOCKBACK && m_state != STATE_DMG && m_state != STATE_DEAD && m_state != STATE_FADEOUT)
	{
		move.x += (0.0f - move.x) * 0.25f;
		move.z += (0.0f - move.z) * 0.25f;
	}

	// �ʒu�ݒ�
	SetPosition(pos);

	// �ړ��ʐݒ�
	SetMove(move);

	// �����ݒ�
	SetRotation(rot);

	// �ڕW�̌����ݒ�
	SetRotDest(fRotDest);

	int nType = m_pMotion->GetType();
	if (nType != MOTION_ATK)
	{
		// �U���̓��̓J�E���^�[���Z
		m_nCntInputAtk--;
		if (m_nCntInputAtk <= 0)
		{
			m_nCntInputAtk = 0;
			m_nAtkLevel = 0;
		}
	}

	if (CGame::GetGameManager()->IsControll() &&
		m_state != STATE_DEAD &&
		m_state != STATE_FADEOUT &&
		m_state != STATE_COMPACTUNION)
	{// �s���ł���Ƃ�

		if (m_sMotionFrag.bATK == false && 
			(pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, m_nMyPlayerIdx) || pInputKeyboard->GetTrigger(DIK_RETURN)))
		{// �U��

			// �U������ON
			m_sMotionFrag.bJump = false;
			m_sMotionFrag.bATK = true;

			//if (m_nCntInputAtk >= 0)
			//{// �܂��P�\����������

			//	// �U���̒i�K���Z
			//	m_nAtkLevel++;
			//	ValueNormalize(m_nAtkLevel, MAX_ATKCOMBO, 0);
			//}

			// �U���̓��̓J�E���^�[���Z�b�g
			m_nCntInputAtk = INTERVAL_ATK;
		}
	}

#if _DEBUG
	static CGameManager::eStatus s_statusType;
	if (pInputKeyboard->GetTrigger(DIK_RIGHT) == true)
	{// ���L�[�������ꂽ,���ړ�
		s_statusType = (CGameManager::eStatus)(((int)s_statusType + 1) % (int)CGameManager::STATUS_MAX);
		SetEvolusion(s_statusType);
	}

	if (pInputKeyboard->GetPress(DIK_UP) == true)
	{// SPACE�������ꂽ,�W�����v

		// �A�C�e���h���b�v
		CItem::Create(D3DXVECTOR3(pos.x, pos.y + 100.0f, pos.z), D3DXVECTOR3(0.0f, Random(-31, 31) * 0.1f, 0.0f));
	}
#endif

	if (pInputKeyboard->GetTrigger(DIK_LEFT) == true)
	{
		CCollisionObject::Create(GetPosition(), mylib_const::DEFAULT_VECTOR3, 10000.0f, 3, 10000, CCollisionObject::TAG_PLAYER);
	}
}

//==========================================================================
// ���[�V�����̐ݒ�
//==========================================================================
void CPlayer::MotionSet(void)
{
	if (m_pMotion == NULL)
	{// ���[�V������NULL��������
		return;
	}

	if (m_pMotion->IsFinish() == true)
	{// �I�����Ă�����

		// ���݂̎�ގ擾
		int nType = m_pMotion->GetType();
		int nOldType = m_pMotion->GetOldType();

		if (m_sMotionFrag.bMove == true && m_sMotionFrag.bATK == false && m_sMotionFrag.bKnockBack == false && m_sMotionFrag.bDead == false && m_bJump == false)
		{// �ړ����Ă�����

			m_sMotionFrag.bMove = false;	// �ړ�����OFF

			// �ړ����[�V����
			m_pMotion->Set(MOTION_WALK);
		}
		else if (m_sMotionFrag.bJump == true && m_sMotionFrag.bATK == false && m_sMotionFrag.bKnockBack == false && m_sMotionFrag.bDead == false)
		{// �W�����v��

			// �W�����v�̃t���OOFF
			m_sMotionFrag.bJump = false;

			// �W�����v���[�V����
			m_pMotion->Set(MOTION_JUMP);
		}
		else if (m_bJump == true && m_sMotionFrag.bJump == false && m_sMotionFrag.bATK == false && m_sMotionFrag.bKnockBack == false && m_sMotionFrag.bDead == false)
		{// �W�����v��&&�W�����v���[�V�������I����Ă鎞

			// �������[�V����
			m_pMotion->Set(MOTION_FALL);
		}
		else if (m_sMotionFrag.bKnockBack == true)
		{// ���ꒆ��������

			// ���ꃂ�[�V����
			m_pMotion->Set(MOTION_KNOCKBACK);
		}
		else if (m_sMotionFrag.bDead == true)
		{// ���S����������

			// ���ꃂ�[�V����
			m_pMotion->Set(MOTION_DEAD);
		}
		else if (m_sMotionFrag.bATK == true)
		{// �U�����Ă�����

			m_sMotionFrag.bATK = false;		// �U������OFF

			//(MAX_ATKCOMBO - m_nCntInputAtk) - 1;
			m_pMotion->Set(MOTION_ATK + m_nAtkLevel, true);

			// �U���̒i�K���Z
			m_nAtkLevel++;
			if (m_nAtkLevel >= MAX_ATKCOMBO)
			{
				m_nAtkLevel = 0;
			}

		}
		else
		{
			// �j���[�g�������[�V����
			m_pMotion->Set(MOTION_DEF);
		}
	}
}

//==========================================================================
// �U��
//==========================================================================
void CPlayer::Atack(void)
{
	if (m_pMotion == NULL)
	{// ���[�V������NULL��������
		return;
	}

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �����擾
	D3DXVECTOR3 rot = GetRotation();

	// �J�����̏��擾
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	// �J�����̌����擾
	D3DXVECTOR3 Camerarot = pCamera->GetRotation();

	// ���[�V�����̏��擾
	CMotion::Info aInfo = m_pMotion->GetInfo(m_pMotion->GetType());

	// �U�����̑����擾
	int nNumAttackInfo = aInfo.nNumAttackInfo;

	for (int nCntAttack = 0; nCntAttack < nNumAttackInfo; nCntAttack++)
	{
		if (aInfo.AttackInfo[nCntAttack] == NULL)
		{// NULL��������
			continue;
		}

		if (m_pMotion->IsImpactFrame(*aInfo.AttackInfo[nCntAttack]))
		{// �Ռ��̃J�E���g�Ɠ����Ƃ�

			// ��ޕ�
			switch (m_pMotion->GetType())
			{
			case MOTION_ATK:
			case MOTION_ATK2:

				switch (CManager::GetInstance()->GetByPlayerPartsType(m_nMyPlayerIdx))
				{
				case CPlayerUnion::PARTS_BODY:
					AttackBody(*aInfo.AttackInfo[nCntAttack]);
					break;

				case CPlayerUnion::PARTS_R_ARM:
				case CPlayerUnion::PARTS_L_ARM:
					AttackArm(*aInfo.AttackInfo[nCntAttack]);
					break;

				case CPlayerUnion::PARTS_LEG:
					AttackLeg(*aInfo.AttackInfo[nCntAttack]);
					break;

				default:
					AttackNormal(*aInfo.AttackInfo[nCntAttack]);
					break;
				}

				// �X�C���O���Đ�
				CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_SWING);
				break;

			case MOTION_EVOLUTION:

				// �i�����
				switch ((m_nEvolveType - 1))
				{
				case CGameManager::STATUS_LIFE:
				case CGameManager::STATUS_POWER:
				case CGameManager::STATUS_SPEED:
					my_particle::Create(GetCenterPosition(), my_particle::TYPE_EVOLUSION_DECIDE);
					break;

				default:

					// �i����ύX
					m_nEvolveType = m_nNextEvolveType;

					// �p�[�c�ύX
					ChangeObject(m_nEvolveType);

					// ���[�V�����؂�ւ�
					ChangeMotion(EVOLUSIONFILE[static_cast<int>(m_nEvolveType) - 1]);

					// �v���C���[���̃C���f�b�N�X�ǉ�
					BindByPlayerIdxTexture();

					// �|�[�Y�̃��Z�b�g
					m_pMotion->ResetPose(MOTION_EVOLUTION);
					m_pMotion->Set(MOTION_EVOLUTION);
					break;
				}
				break;
			}
		}

		// ���[�V�����J�E���^�[�擾
		float fAllCount = m_pMotion->GetAllCount();
		if (fAllCount > aInfo.AttackInfo[nCntAttack]->nMinCnt && fAllCount < aInfo.AttackInfo[nCntAttack]->nMaxCnt)
		{// �U�����蒆
			
			// ����̈ʒu
			D3DXVECTOR3 weponpos = m_pMotion->GetAttackPosition(GetModel(), *aInfo.AttackInfo[nCntAttack]);

			CEffect3D *pEffect = NULL;

			switch (m_pMotion->GetType())
			{
			case MOTION_EVOLUTION:
			{
				D3DXVECTOR3 nor = (aInfo.AttackInfo[nCntAttack]->Offset);
				D3DXVec3Normalize(&nor, &nor);

				D3DXVECTOR3 move = D3DXVECTOR3(10.0f, 0.0f, 0.0f);

				// ��
				float fMove = 4.5f + Random(-10, 10) * 0.1f;
				float fRot = Random(-20, 20) * 0.01f;

				pEffect = CEffect3D::Create(
					weponpos,
					(fMove * nor),
					D3DXCOLOR(1.0f + Random(-10, 0) * 0.01f, 0.0f, 0.0f, 1.0f),
					20.0f + (float)Random(-10, 10),
					15,
					CEffect3D::MOVEEFFECT_ADD,
					CEffect3D::TYPE_SMOKE);

				if (pEffect != NULL)
				{
					// �Z�b�g�A�b�v�ʒu�ݒ�
					pEffect->SetUp(aInfo.AttackInfo[nCntAttack]->Offset, GetModel()[aInfo.AttackInfo[nCntAttack]->nCollisionNum]->GetPtrWorldMtx(), CObject::GetObject(), SetEffectParent(pEffect));
				}

				fRot = Random(-20, 20) * 0.01f;
				// ��
				pEffect = CEffect3D::Create(
					weponpos,
					(fMove * nor),
					D3DXCOLOR(0.8f + Random(-10, 0) * 0.01f, 0.5f + Random(-10, 0) * 0.01f, 0.0f, 1.0f),
					12.0f + (float)Random(-5, 5),
					15,
					CEffect3D::MOVEEFFECT_ADD,
					CEffect3D::TYPE_SMOKE);
				if (pEffect != NULL)
				{
					// �Z�b�g�A�b�v�ʒu�ݒ�
					pEffect->SetUp(aInfo.AttackInfo[nCntAttack]->Offset, GetModel()[aInfo.AttackInfo[nCntAttack]->nCollisionNum]->GetPtrWorldMtx(), CObject::GetObject(), SetEffectParent(pEffect));
				}

				if ((int)fAllCount % 8 == 0)
				{
					for (int i = 0; i < 1; i++)
					{
						int repeat = (int)(fAllCount / 8.0f);
						CEffect3D::Create(
							D3DXVECTOR3(GetCenterPosition().x, GetCenterPosition().y + 100.0f, GetCenterPosition().z - 200.0f),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							EFFECTCOLOR[m_nMyPlayerIdx],
							20.0f, 20, CEffect3D::MOVEEFFECT_ADD, CEffect3D::TYPE_NORMAL, repeat * 1.1f);
					}
				}
			}
				break;

			case MOTION_ATK:
			case MOTION_ATK2:
				// �i�����
				switch (CManager::GetInstance()->GetByPlayerPartsType(m_nMyPlayerIdx))
				{
				case CPlayerUnion::PARTS_BODY:
					my_particle::Create(weponpos, my_particle::TYPE_ATTACK_BODY);

					if ((int)fAllCount % 8 == 0)
					{
						for (int i = 0; i < 4; i++)
						{
							int repeat = (int)(fAllCount / 8.0f);
							CEffect3D::Create(
								weponpos,
								D3DXVECTOR3(0.0f, 0.0f, 0.0f),
								mylib_const::PLAYERBEAM_COLOR,
								20.0f, 16, CEffect3D::MOVEEFFECT_ADD, CEffect3D::TYPE_POINT, repeat * 4.0f);
						}
					}
					break;

				case CPlayerUnion::PARTS_R_ARM:
				case CPlayerUnion::PARTS_L_ARM:
					break;

				case CPlayerUnion::PARTS_LEG:
					break;

				default:
					break;
				}
				break;
			}

#if _DEBUG
			CEffect3D::Create(weponpos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), aInfo.AttackInfo[nCntAttack]->fRangeSize, 10, CEffect3D::MOVEEFFECT_NONE, CEffect3D::TYPE_NORMAL);
#endif

#if 1
			// �G�擾
			CEnemy **ppEnemy = CGame::GetEnemyManager()->GetEnemy();

			// �����擾
			int nNumAll = CGame::GetEnemyManager()->GetNumAll();
			int i = -1, nCntEnemy = 0;

			while (1)
			{
				if (nCntEnemy >= nNumAll)
				{// ������������I���
					break;
				}

				// �C���f�b�N�X���Z
				i++;
				if (ppEnemy[i] == NULL)
				{
					continue;
				}

				// �G�̈ʒu�擾
				D3DXVECTOR3 TargetPos = ppEnemy[i]->GetPosition();

				// ����T�C�Y�擾
				float fTargetRadius = ppEnemy[i]->GetRadius();

				if (SphereRange(weponpos, TargetPos, aInfo.AttackInfo[nCntAttack]->fRangeSize, fTargetRadius))
				{// ���̔���

					int nDamage = (int)((float)aInfo.AttackInfo[nCntAttack]->nDamage * m_sStatus.fPowerBuff);
					if (ppEnemy[i]->Hit(nDamage) == true)
					{// �������Ă���

					}
				}

				// �G�̐����Z
				nCntEnemy++;
			}
#else

			// �G�̃��X�g�擾
			CListManager *pEnemyList = CEnemy::GetEnemyList();

			pEnemyList->GetTop();

			// �擪��ۑ�
			CList *pList = pEnemyList->GetTop();

			while (pList != NULL)
			{// NULL������܂Ŗ������[�v

				// ���̃I�u�W�F�N�g���ꎞ�ۑ�
				CList *pListNext = pList->GetNext();

				// ���S�̔���
				if (pList->IsDeath() == true)
				{// ���S�t���O�������Ă�����

					// ���̃I�u�W�F�N�g����
					pList = pListNext;
					continue;
				}

				// �G�̈ʒu�擾
				D3DXMATRIX mtxOrigin = pList->GetObjectChara()->GetModel()[0]->GetWorldMtx();
				D3DXVECTOR3 TargetPos = D3DXVECTOR3(mtxOrigin._41, mtxOrigin._42, mtxOrigin._43);

				// ����T�C�Y�擾
				float fRadius = pList->GetObjectChara()->GetRadius();

				if (SphereRange(weponpos, TargetPos, aInfo.AttackInfo[nCntAttack]->fRangeSize, fRadius))
				{// ���̔���

					if (pList->Hit(aInfo.AttackInfo[nCntAttack]->nDamage) == true)
					{// ����ł���

						my_particle::Create(TargetPos, my_particle::TYPE_OFFSETTING);
					}
				}

				// ���̃I�u�W�F�N�g����
				pList = pListNext;
			}

#endif
		}
	}

	CManager::GetInstance()->GetDebugProc()->Print(
		"���[�V�����J�E���^�[�F%d\n", m_pMotion->GetAllCount());
}

//==========================================================================
// �ʏ�U��
//==========================================================================
void CPlayer::AttackNormal(CMotion::AttackInfo attackInfo)
{
	// �����擾
	D3DXVECTOR3 rot = GetRotation();
	D3DXVECTOR3 weponpos = m_pMotion->GetAttackPosition(GetModel(), attackInfo);

	// ����̈ʒu
	for (int i = 0; i < 4; i++)
	{
		// ��
		float fMove = 7.0f + Random(-2, 5);
		float fRot = Random(-20, 20) * 0.01f;
		float fRotMove = Random(-10, 10) * 0.01f;

		// ��
		CEffect3D *pEffect = CEffect3D::Create(
			weponpos,
			D3DXVECTOR3(
				sinf(D3DX_PI + rot.y + fRotMove) * fMove,
				fRotMove,
				cosf(D3DX_PI + rot.y + fRotMove) * fMove),
			D3DXCOLOR(1.0f + Random(-10, 0) * 0.01f, 0.0f, 0.0f, 1.0f),
			90.0f + (float)Random(-10, 10),
			15,
			CEffect3D::MOVEEFFECT_ADD,
			CEffect3D::TYPE_SMOKE);

		// ��
		CEffect3D::Create(
			weponpos,
			D3DXVECTOR3(
				sinf(D3DX_PI + rot.y + fRotMove) * fMove,
				fRotMove,
				cosf(D3DX_PI + rot.y + fRotMove) * fMove),
			D3DXCOLOR(0.8f + Random(-10, 0) * 0.01f, 0.5f + Random(-10, 0) * 0.01f, 0.0f, 1.0f),
			60.0f + (float)Random(-10, 10),
			15,
			CEffect3D::MOVEEFFECT_ADD,
			CEffect3D::TYPE_SMOKE);

		int nDamage = (int)((float)attackInfo.nDamage * m_sStatus.fPowerBuff);
		CCollisionObject::Create(pEffect->GetPosition(), pEffect->GetMove(), pEffect->GetSize().x, 15, nDamage, CCollisionObject::TAG_PLAYER);
	}
}

//==========================================================================
// �r�U��
//==========================================================================
void CPlayer::AttackArm(CMotion::AttackInfo attackInfo)
{

}

//==========================================================================
// �r�U��
//==========================================================================
void CPlayer::AttackLeg(CMotion::AttackInfo attackInfo)
{

}

//==========================================================================
// ���U��
//==========================================================================
void CPlayer::AttackBody(CMotion::AttackInfo attackInfo)
{
	// �����擾
	D3DXVECTOR3 rot = GetRotation();
	D3DXVECTOR3 weponpos = m_pMotion->GetAttackPosition(GetModel(), attackInfo);
	int nDamage = (int)((float)attackInfo.nDamage * m_sStatus.fPowerBuff);
	float fMove = 28.0f;
	D3DXCOLOR col = D3DXCOLOR(
		mylib_const::PLAYERBEAM_COLOR.r + Random(-100, 100) * 0.001f,
		mylib_const::PLAYERBEAM_COLOR.g + Random(-100, 100) * 0.001f,
		mylib_const::PLAYERBEAM_COLOR.b + Random(-100, 100) * 0.001f,	// �F
		1.0f);

	switch (m_pMotion->GetType())
	{
	case MOTION_ATK:
		CBeam::Create(
			weponpos,
			D3DXVECTOR3(
				sinf(D3DX_PI + rot.y) * fMove,	// �ʒu
				cosf(D3DX_PI * 0.65f) * fMove,
				cosf(D3DX_PI + rot.y) * fMove),	// �ړ���
			col,	// �F
			20.0f,	// ���a
			200.0f,	// ����
			15,		// ����
			18,		// ���x
			nDamage,	// �_���[�W
			CCollisionObject::TAG_PLAYER	// �^�O
		);
		break;

	case MOTION_ATK2:
		fMove = 32.0f;
		CBeam::Create(
			weponpos,
			D3DXVECTOR3(
				sinf(D3DX_PI + rot.y) * fMove,	// �ʒu
				cosf(D3DX_PI * 0.65f) * fMove,
				cosf(D3DX_PI + rot.y) * fMove),	// �ړ���
			col,		// �F
			25.0f,		// ���a
			200.0f,		// ����
			40,			// ����
			24,			// ���x
			nDamage,	// �_���[�W
			CCollisionObject::TAG_PLAYER	// �^�O
		);
		break;
	}

	col.a = 0.8f;
	// �Ռ��g����
	CImpactWave::Create
	(
		weponpos,	// �ʒu
		D3DXVECTOR3(D3DX_PI * 0.5f, D3DX_PI + rot.y, 0.0f),				// ����
		col,			// �F
		18.0f,						// ��
		8.0f,						// ����
		20.0f,						// ���S����̋���
		10,							// ����
		10.0f,						// ���̈ړ���
		CImpactWave::TYPE_PURPLE4,	// �e�N�X�`���^�C�v
		true						// ���Z�������邩
	);
}

//==========================================================================
// �����蔻��
//==========================================================================
bool CPlayer::Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &move)
{

	// �����擾
	D3DXVECTOR3 rot = GetRotation();

	// ���n�������ǂ���
	bool bLand = false;
	float fHeight = 0.0f;
	m_bLandField = false;
	m_bHitWall = false;			// �ǂ̓����蔻��

	// �����擾
	if (m_state != STATE_KNOCKBACK && m_state != STATE_DMG && m_state != STATE_DEAD && m_state != STATE_FADEOUT)
	{
		fHeight = CManager::GetInstance()->GetScene()->GetElevation()->GetHeight(pos, bLand);
	}
	else
	{
		fHeight = pos.y;
	}

	if (fHeight > pos.y)
	{// �n�ʂ̕���������荂��������

	 // �n�ʂ̍����ɕ␳
		pos.y = fHeight;
		m_bLandField = true;

		if (bLand == true)
		{// ���n���Ă���

		 // �W�����v�g�p�\�ɂ���
			m_bJump = false;
			move.y = 0.0f;
			m_bLandOld = true;
		}
	}


	// X�t�@�C���Ƃ̔���
	CStage *pStage = CGame::GetStage();
	if (pStage == NULL)
	{// NULL��������
		return false;
	}

	bool bNowLand = false;

	// �X�e�[�W�ɓ�����������
	m_bHitStage = false;
	for (int nCntStage = 0; nCntStage < pStage->GetNumAll(); nCntStage++)
	{
		// �I�u�W�F�N�g�擾
		CObjectX *pObjX = pStage->GetObj(nCntStage);

		if (pObjX == NULL)
		{// NULL��������
			continue;
		}

		// �����擾
		bool bLand = false;
		fHeight = pObjX->GetHeight(pos, bLand);

		if (bLand == true && fHeight > pos.y)
		{// �n�ʂ̕���������荂��������

		 // �n�ʂ̍����ɕ␳
			if (pos.y + 50.0f <= fHeight)
			{// �������ǂ���������
				m_bHitWall = true;
			}
			else
			{
				pos.y = fHeight;
			}

			m_bHitStage = true;
			m_bLandField = false;

			if (bLand == true)
			{// ���n���Ă���

				if ((m_sMotionFrag.bKnockBack || m_bJump == true) && GetPosition().y >= fHeight)
				{
					m_bLandOld = true;
				}

				if (m_bJump == true)
				{// �W�����v����������
					m_pMotion->ToggleFinish(true);
				}

				// �W�����v�g�p�\�ɂ���
				m_bJump = false;
				move.y = 0.0f;
				bNowLand = true;
				m_sMotionFrag.bJump = false;
			}
		}
	}

	// �I�u�W�F�N�g�擾
	CObjectX *pObjX = pStage->GetInjectionTable();

	// �����擾
	bLand = false;
	fHeight = pObjX->GetHeight(pos, bLand);

	if (bLand == true && fHeight > pos.y)
	{// �n�ʂ̕���������荂��������

		// �n�ʂ̍����ɕ␳
		if (pos.y + 50.0f <= fHeight)
		{// �������ǂ���������
			m_bHitWall = true;
		}
		else
		{
			pos.y = fHeight;
		}

		m_bHitStage = true;
		m_bLandField = false;

		if (bLand == true)
		{// ���n���Ă���

			if ((m_sMotionFrag.bKnockBack || m_bJump == true) && GetPosition().y >= fHeight)
			{
				m_bLandOld = true;
			}

			if (m_bJump == true)
			{// �W�����v����������
				m_pMotion->ToggleFinish(true);
			}

			// �W�����v�g�p�\�ɂ���
			m_bJump = false;
			move.y = 0.0f;
			bNowLand = true;
			m_sMotionFrag.bJump = false;

			// �ˏo��̒��n����
			m_bLandInjectionTable[m_nMyPlayerIdx] = true;

		}
	}

	int nLandNum = 0;
	for (int i = 0; i < CManager::GetInstance()->GetNumPlayer(); i++)
	{
		// �ˏo��̒��n�m�F
		if (m_bLandInjectionTable[i] == true)
		{
			nLandNum++;
		}
	}

	// �S�����n��Ԑݒ�
	if (nLandNum >= CManager::GetInstance()->GetNumPlayer())
	{
		m_bAllLandInjectionTable = true;
	}
	else
	{
		m_bAllLandInjectionTable = false;
	}

	if (CGame::GetGameManager()->GetType() == CGameManager::SCENE_MAINCLEAR &&
		pStage->GetInjectionTable()->GetState() != CInjectionTable::STATE_UP)
	{// �ʏ�N���A��������

		if (m_bAllLandInjectionTable == true)
		{// �S���ˏo��ɏ���Ă���

			// �`���[�W���
			pStage->GetInjectionTable()->SetState(CInjectionTable::STATE_CHARGE);
		}
		else
		{
			// ���Z�b�g
			pStage->GetInjectionTable()->SetState(CInjectionTable::STATE_NONE, 0);
		}
	}


	// �G���A�������擾
	CLimitAreaManager *pLimitManager = CGame::GetLimitEreaManager();
	CLimitArea **ppLimit = pLimitManager->GetLimitErea();

	// �����擾
	int nNumAll = pLimitManager->GetNumAll();
	int i = -1, nCntErea = 0;

	while (1)
	{
		if (nCntErea >= nNumAll)
		{// ������������I���
			break;
		}

		// �C���f�b�N�X���Z
		i++;
		if (ppLimit[i] == NULL)
		{
			continue;
		}
		CLimitArea::sLimitEreaInfo info = ppLimit[i]->GetLimitEreaInfo();

		// ��l�̕ǂ�K�p
		if (pos.x + GetRadius() >= info.fMaxX) { pos.x = info.fMaxX - GetRadius(); }
		if (pos.x - GetRadius() <= info.fMinX) { pos.x = info.fMinX + GetRadius(); }
		if (pos.z + GetRadius() >= info.fMaxZ) { pos.z = info.fMaxZ - GetRadius(); }
		if (pos.z - GetRadius() <= info.fMinZ) { pos.z = info.fMinZ + GetRadius(); }

		// �G���A�̐����Z
		nCntErea++;
	}

	// �����ݒ�
	SetRotation(rot);

	return bNowLand;
}

//==========================================================================
// �q�b�g����
//==========================================================================
bool CPlayer::Hit(const int nValue)
{
	// �̗͎擾
	int nLife = GetLife();

	//if (nLife <= 0)
	//{
	//	// ����
	//	return true;
	//}

	if (m_state != STATE_DMG &&
		m_state != STATE_KNOCKBACK &&
		m_state != STATE_INVINCIBLE &&
		m_state != STATE_DEAD &&
		m_state != STATE_FADEOUT &&
		m_state != STATE_COMPACTUNION &&
		m_state != STATE_RELEASEUNION)
	{// �_���[�W��t��Ԃ̎�

		// �̗͌��炷
		nLife -= nValue;


		// �Q�[���p�b�h���擾
		CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();
		pInputGamepad->SetVibration(CInputGamepad::VIBRATION_STATE_DMG, 0);

		m_KnokBackMove.y += 18.0f;
		m_bHitStage = false;

		// �̗͐ݒ�
		SetLife(nLife);

		if (nLife <= 0)
		{// �̗͂��Ȃ��Ȃ�����

			// �����
			m_state = STATE_DEAD;

			m_KnokBackMove.y = 8.0f;

			// �J�ڃJ�E���^�[�ݒ�
			m_nCntState = DEADTIME;

			// �̗͐ݒ�
			SetLife(0);

			// �m�b�N�o�b�N����ɂ���
			m_sMotionFrag.bKnockBack = true;

			// ���ꃂ�[�V����
			m_pMotion->Set(MOTION_KNOCKBACK);

			// �m�b�N�o�b�N�̈ʒu�X�V
			D3DXVECTOR3 pos = GetPosition();
			D3DXVECTOR3 rot = GetRotation();
			m_posKnokBack = pos;

			// �Ռ��g����
			CImpactWave::Create
			(
				D3DXVECTOR3(pos.x, pos.y + 80.0f, pos.z),	// �ʒu
				D3DXVECTOR3(D3DX_PI * 0.5f, D3DX_PI + rot.y, D3DX_PI),				// ����
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f),			// �F
				80.0f,										// ��
				80.0f,										// ����
				0.0f,										// ���S����̊Ԋu
				20,											// ����
				10.0f,										// ���̈ړ���
				CImpactWave::TYPE_GIZAWHITE,				// �e�N�X�`���^�C�v
				false										// ���Z�������邩
			);

			CManager::GetInstance()->SetEnableHitStop(18);

			// �U��
			CManager::GetInstance()->GetCamera()->SetShake(21, 30.0f, 0.0f);

			// ����
			return true;
		}

		// �ߋ��̏�ԕۑ�
		m_Oldstate = m_state;

		// �F�ݒ�
		m_mMatcol = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		// �_���[�W��Ԃɂ���
		m_state = STATE_DMG;

		// �J�ڃJ�E���^�[�ݒ�
		m_nCntState = 0;

		// �m�b�N�o�b�N�̈ʒu�X�V
		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 rot = GetRotation();
		m_posKnokBack = pos;

		// �m�b�N�o�b�N����ɂ���
		m_sMotionFrag.bKnockBack = true;

		// ���ꃂ�[�V����
		m_pMotion->Set(MOTION_KNOCKBACK);

		// �Ռ��g����
		CImpactWave::Create
		(
			D3DXVECTOR3(pos.x, pos.y + 80.0f, pos.z),	// �ʒu
			D3DXVECTOR3(D3DX_PI * 0.5f, D3DX_PI + rot.y, D3DX_PI),				// ����
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f),			// �F
			80.0f,										// ��
			80.0f,										// ����
			0.0f,										// ���S����̊Ԋu
			20,											// ����
			10.0f,										// ���̈ړ���
			CImpactWave::TYPE_GIZAWHITE,				// �e�N�X�`���^�C�v
			false										// ���Z�������邩
		);

		CManager::GetInstance()->SetEnableHitStop(12);

		// �U��
		CManager::GetInstance()->GetCamera()->SetShake(12, 25.0f, 0.0f);

		// �T�E���h�Đ�
		CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_PLAYERDMG);
	}

	// ����łȂ�
	return false;
}

//==========================================================================
// �X�e�[�^�X�t�^
//==========================================================================
bool CPlayer::GiveStatus(CGameManager::eStatus status)
{
	// �擾����
	bool bGet = false;

	// ����
	int nStatus = 0;
	switch (status)
	{
	case CGameManager::STATUS_POWER:
		if (m_sStatus.nPower < MAX_BUFFSTATUS)
		{
			m_sStatus.nPower++;
			bGet = true;
		}
		nStatus = m_sStatus.nPower;
		break;

	case CGameManager::STATUS_SPEED:
		if (m_sStatus.nSpeed < MAX_BUFFSTATUS)
		{
			m_sStatus.nSpeed++;
			bGet = true;
		}
		nStatus = m_sStatus.nSpeed;
		break;

	case CGameManager::STATUS_LIFE:
		if (m_sStatus.nLife < MAX_BUFFSTATUS)
		{
			m_sStatus.nLife++;
			bGet = true;
		}
		break;
	}

	// ����
	float fRate = (float)nStatus / (float)MAX_BUFFSTATUS;

	// �o�t�v�Z
	m_sStatus.fPowerBuff = 1.0f + ((float)m_sStatus.nPower * 0.01f);
	m_sStatus.fSpeedBuff = 1.0f + ((float)m_sStatus.nSpeed * 0.01f);
	m_sStatus.fLifeBuff = 1.0f + ((float)m_sStatus.nLife * 0.1f);

	if (status == CGameManager::STATUS_POWER || status == CGameManager::STATUS_SPEED)
	{
		// �X�e�[�^�X�E�B���h�E
		CStatusWindow *pStatusWindow = CGame::GetStatusWindow(m_nMyPlayerIdx);
		if (pStatusWindow != NULL)
		{
			// �Q�[�W�̊����X�V
			pStatusWindow->GetGauge(status)->SetRateDest(fRate);
		}
	}
	return bGet;
}

//==========================================================================
// �i���撊�I
//==========================================================================
void CPlayer::DrawingEvolusion(void)
{
	// �i����̃C���f�b�N�X�ԍ�
	int nIdxPowerLeft = 0, nIdxPowerRight = 0, nIdxSpeed = 0, nIdxLife = 0;

	// �v���C���[�̎擾
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		CPlayer *pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(i);
		if (pPlayer == NULL)
		{
			continue;
		}

	}
}

//==========================================================================
// �i����ݒ�
//==========================================================================
void CPlayer::SetEvolusion(CGameManager::eStatus statusType, bool bFast)
{
	// �v���C���[���̒S���p�[�c��ސݒ�
	switch (statusType)
	{
	case CGameManager::STATUS_POWER:
	{
		bool bR_Arm = false, bL_Arm = false;
		for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
		{
			int nPartsType = CManager::GetInstance()->GetByPlayerPartsType(i);
			if (nPartsType == CPlayerUnion::PARTS_R_ARM)
			{
				bR_Arm = true;
			}
			else if (nPartsType == CPlayerUnion::PARTS_L_ARM)
			{
				bL_Arm = true;
			}
		}

		// �r�̎g�p�󋵕ʐݒ�
		if (bR_Arm == false && bL_Arm == false)
		{
			CManager::GetInstance()->SetByPlayerPartsType(m_nMyPlayerIdx, CPlayerUnion::PARTS_R_ARM);
		}
		else if (bR_Arm == true && bL_Arm == false)
		{
			CManager::GetInstance()->SetByPlayerPartsType(m_nMyPlayerIdx, CPlayerUnion::PARTS_L_ARM);
		}
		else
		{
			CManager::GetInstance()->SetByPlayerPartsType(m_nMyPlayerIdx, CPlayerUnion::PARTS_R_ARM);
		}
	}
		break;

	case CGameManager::STATUS_SPEED:
		CManager::GetInstance()->SetByPlayerPartsType(m_nMyPlayerIdx, CPlayerUnion::PARTS_LEG);
		break;

	case CGameManager::STATUS_LIFE:
		CManager::GetInstance()->SetByPlayerPartsType(m_nMyPlayerIdx, CPlayerUnion::PARTS_BODY);
		break;
	}

	if (bFast)
	{
		// �i����̎��
		m_nEvolveType = (int)statusType + 1;

		// �p�[�c�ύX
		ChangeObject(m_nEvolveType);

		// ���[�V�����؂�ւ�
		ChangeMotion(EVOLUSIONFILE[(int)statusType]);

		// �v���C���[���̃C���f�b�N�X�ǉ�
		BindByPlayerIdxTexture();
	}
	else
	{
		// ���̐i����
		m_nNextEvolveType = (int)statusType + 1;

		// �i����Ԃɂ���
		m_state = STATE_EVOLUSION;

		// �i�����[�V�����ݒ�
		m_pMotion->Set(MOTION_EVOLUTION);

		// �ڕW�̌����ݒ�
		SetRotDest(0.0f);
	}
}

//==========================================================================
// �v���C���[�C���f�b�N�X���̃e�N�X�`���ݒ�
//==========================================================================
void CPlayer::BindByPlayerIdxTexture(void)
{
	// �t�@�C���C���f�b�N�X�ԍ��擾
	int nIdxXFile = GetIdxFile();
	CObjectChara::Load LoadData = GetLoadData(nIdxXFile);

	// ���f���擾
	CModel **ppModel = GetModel();

	// �����e�N�X�`��
	int nIdxTex = CManager::GetInstance()->GetTexture()->Regist(TEXTURE_INITPLAYER[0][m_nMyPlayerIdx]);
	for (int i = 0; i < GetNumModel(); i++)
	{
		if (ppModel[i] == NULL)
		{
			continue;
		}

		// X�t�@�C���̃f�[�^�擾
		CXLoad::SXFile *pXData = CScene::GetXLoad()->GetMyObject(ppModel[i]->GetIdxXFile());

		for (int nMat = 0; nMat < (int)pXData->dwNumMat; nMat++)
		{
			ppModel[i]->SetIdxTexture(nMat, nIdxTex);
		}
	}

	// ��ޕʃe�N�X�`���؂�ւ�
	for (int i = 0; i < LoadData.nNumModel; i++)
	{
		if (LoadData.LoadData[i].nSwitchType != m_nEvolveType)
		{// �ύX�̃^�O�ƈႤ����
			continue;
		}

		if (LoadData.LoadData[i].nIDSwitchModel < 0)
		{// �V�����p�[�c

			// �e�N�X�`���ǂݍ���
			int nIdxTex = CManager::GetInstance()->GetTexture()->Regist(TEXTURE_INITPLAYER[m_nEvolveType][m_nMyPlayerIdx]);

			// X�t�@�C���̃f�[�^�擾
			CXLoad::SXFile *pXData = CScene::GetXLoad()->GetMyObject(ppModel[i]->GetIdxXFile());

			for (int nMat = 0; nMat < (int)pXData->dwNumMat; nMat++)
			{
				ppModel[i]->SetIdxTexture(nMat, nIdxTex);
			}
		}
		else
		{// �؂�ւ��̏ꍇ

			if (ppModel[LoadData.LoadData[i].nIDSwitchModel] == NULL)
			{
				continue;
			}

			// �e�N�X�`���ǂݍ���
			int nIdxTex = CManager::GetInstance()->GetTexture()->Regist(TEXTURE_INITPLAYER[m_nEvolveType][m_nMyPlayerIdx]);

			// X�t�@�C���̃f�[�^�擾
			CXLoad::SXFile *pXData = CScene::GetXLoad()->GetMyObject(ppModel[LoadData.LoadData[i].nIDSwitchModel]->GetIdxXFile());

			for (int nMat = 0; nMat < (int)pXData->dwNumMat; nMat++)
			{
				ppModel[LoadData.LoadData[i].nIDSwitchModel]->SetIdxTexture(nMat, nIdxTex);
			}
		}
	}
}

//==========================================================================
// ���[�V�����t�@�C��
//==========================================================================
void CPlayer::ChangeMotion(const char* pMotionFile)
{
	if (m_pMotion != NULL)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = NULL;
	}

	// ���[�V�����̐�������
	m_pMotion = CMotion::Create(pMotionFile);

	// �I�u�W�F�N�g�L�����N�^�[�̏��擾
	CObjectChara *pObjChar = GetObjectChara();

	// ���[�V�����̐ݒ�
	m_pMotion->SetModel(pObjChar->GetModel(), pObjChar->GetNumModel(), CObjectChara::GetObjectChara());

	// �|�[�Y�̃��Z�b�g
	m_pMotion->ResetPose(MOTION_DEF);
}

//==========================================================================
// ��ԍX�V����
//==========================================================================
void CPlayer::UpdateState(void)
{
	switch (m_state)
	{
	case STATE_NONE:
		// �F�ݒ�
		m_mMatcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;

	case STATE_INVINCIBLE:
		Invincible();
		break;

	case STATE_DMG:
		Damage();
		break;

	case STATE_DEAD:
		Dead();
		break;

	case STATE_FADEOUT:
		FadeOut();
		break;

	case STATE_KNOCKBACK:
		KnockBack();
		break;

	case STATE_COMPACTUNION:
		StateCompactUnion();
		break;

	case STATE_RELEASEUNION:
		StateReleaseUnion();
		break;

	case STATE_EVOLUSION:
		StateEvolusion();
		break;
	}
}

//==========================================================================
// ���G
//==========================================================================
void CPlayer::Invincible(void)
{
	// ��ԑJ�ڃJ�E���^�[���Z
	m_nCntState--;

	if (m_nCntState % INVINCIBLE_INT == 0)
	{// �K��Ԋu
		
		// �F�ݒ�
		if (m_mMatcol.a == 1.0f)
		{
			m_mMatcol.a = 0.4f;
		}
		else
		{
			m_mMatcol.a = 1.0f;
		}
	}

	if (m_nCntState <= 0)
	{// �J�ڃJ�E���^�[��0�ɂȂ�����

		// �Ȃɂ��Ȃ���Ԃɂ���
		m_state = STATE_NONE;
		m_nCntState = 0;

		// �F�ݒ�
		m_mMatcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

}

//==========================================================================
// �_���[�W
//==========================================================================
void CPlayer::Damage(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// �����擾
	D3DXVECTOR3 rot = GetRotation();

	// ��ԑJ�ڃJ�E���^�[���Z
	m_nCntState++;

	// �F�ݒ�
	m_mMatcol = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	// �ʒu�X�V
	pos.y = (-0.4f * (float)(m_nCntState * m_nCntState) + m_KnokBackMove.y * (float)m_nCntState) + m_posKnokBack.y;
	pos.x += move.x;
	/*pos.x += move.x;
	pos.z += move.z;*/

	// �N���Ƃ̔���
	if ((CManager::GetInstance()->GetScene()->GetElevation()->IsHit(pos) || m_bHitStage) && m_nCntState >= 10)
	{// �n�ʂƓ������Ă�����
		m_state = STATE_INVINCIBLE;
		m_nCntState = INVINCIBLE_TIME;
		m_KnokBackMove.y = 0.0f;	// �ړ��ʃ[��
		m_bLandOld = true;

		// �F�ݒ�
		m_mMatcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �m�b�N�o�b�N�������
		m_sMotionFrag.bKnockBack = false;
		m_pMotion->ToggleFinish(true);


		// X�t�@�C���Ƃ̔���
		CStage *pStage = CGame::GetStage();
		if (pStage == NULL)
		{// NULL��������
			return;
		}

		// �X�e�[�W�ɓ�����������
		for (int nCntStage = 0; nCntStage < pStage->GetNumAll(); nCntStage++)
		{
			// �I�u�W�F�N�g�擾
			CObjectX *pObjX = pStage->GetObj(nCntStage);

			if (pObjX == NULL)
			{// NULL��������
				continue;
			}

			// �����擾
			bool bLand = false;
			pos.y = pObjX->GetHeight(pos, bLand);
		}


	}
	else if (m_nCntState >= 30)
	{// �J�ڃJ�E���^�[��30�ɂȂ�����

		// �m�b�N�o�b�N��Ԃɂ���
		m_state = STATE_KNOCKBACK;
	}


	// �ʒu�ݒ�
	SetPosition(pos);

	// �ړ��ʐݒ�
	SetMove(move);

	// �����ݒ�
	SetRotation(rot);
}

//==========================================================================
// ���S
//==========================================================================
void CPlayer::Dead(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// �ʒu�X�V
	if (m_nCntState > 0)
	{
		int nCnt = DEADTIME - m_nCntState;
		pos.y = (-0.1f * (float)(nCnt * nCnt) + m_KnokBackMove.y * (float)nCnt) + m_posKnokBack.y;
		pos.x += move.x;
	}

	// ��ԑJ�ڃJ�E���^�[���Z
	m_nCntState--;

	// �N���Ƃ̔���
	if ((CManager::GetInstance()->GetScene()->GetElevation()->IsHit(pos) || m_bHitStage) && m_nCntState >= 10)
	{// �n�ʂƓ������Ă�����

		//// �t�F�[�h��ݒ肷��
		//CManager::GetInstance()->GetInstantFade()->SetFade();

		//if (CManager::GetInstance()->GetInstantFade()->GetState() == CInstantFade::STATE_FADECOMPLETION)
		//{// �t�F�[�h����������



		//}

		m_state = STATE_FADEOUT;	// �t�F�[�h�A�E�g
		m_nCntState = FADEOUTTIME;
		m_KnokBackMove.y = 0.0f;	// �ړ��ʃ[��
		m_bLandOld = true;
		move.x = 0.0f;

		// �F�ݒ�
		m_mMatcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �m�b�N�o�b�N�������
		m_sMotionFrag.bKnockBack = false;
		m_sMotionFrag.bDead = true;
		//m_pMotion->ToggleFinish(true);

		// �Ԃ��|�ꃂ�[�V����
		m_pMotion->Set(MOTION_DEAD);

		// X�t�@�C���Ƃ̔���
		CStage *pStage = CGame::GetStage();
		if (pStage == NULL)
		{// NULL��������
			return;
		}

		// �X�e�[�W�ɓ�����������
		for (int nCntStage = 0; nCntStage < pStage->GetNumAll(); nCntStage++)
		{
			// �I�u�W�F�N�g�擾
			CObjectX *pObjX = pStage->GetObj(nCntStage);

			if (pObjX == NULL)
			{// NULL��������
				continue;
			}

			// �����擾
			bool bLand = false;
			pos.y = pObjX->GetHeight(pos, bLand);
		}
	}

	// �ʒu�ݒ�
	SetPosition(pos);

	// �ړ��ʐݒ�
	SetMove(move);
}

//==========================================================================
// �t�F�[�h�A�E�g
//==========================================================================
void CPlayer::FadeOut(void)
{

	// ��ԑJ�ڃJ�E���^�[���Z
	m_nCntState--;

	// �F�ݒ�
	m_mMatcol.a = (float)m_nCntState / (float)FADEOUTTIME;

	if (m_nCntState <= 0)
	{// �J�ڃJ�E���^�[��0�ɂȂ�����

		// ���[�h�ݒ�
		//CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RESULT);

		// ���S����
		Kill();

		// �I������
		Uninit();
		return;
	}
}

//==========================================================================
// �m�b�N�o�b�N
//==========================================================================
void CPlayer::KnockBack(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// �����擾
	D3DXVECTOR3 rot = GetRotation();

	// �ڕW�̌����擾
	float fRotDest = GetRotDest();

	// �ړ��ʎ擾
	float fMove = GetVelocity();

	// ���݂ƖڕW�̍���
	float fRotDiff = 0.0f;

	// �����̔���
	bool bLen = false;


	// ��ԑJ�ڃJ�E���^�[���Z
	m_nCntState++;

	// �ʒu�X�V
	pos.y = (-0.4f * (float)(m_nCntState * m_nCntState) + m_KnokBackMove.y * (float)m_nCntState) + m_posKnokBack.y;
	pos.x += move.x;
	/*pos.x += move.x;
	pos.z += move.z;*/

	// �N���Ƃ̔���
	if ((CManager::GetInstance()->GetScene()->GetElevation()->IsHit(pos) || m_bHitStage))
	{// �n�ʂƓ������Ă�����
		m_state = STATE_INVINCIBLE;
		m_nCntState = INVINCIBLE_TIME;
		m_KnokBackMove.y = 0.0f;	// �ړ��ʃ[��
		m_bLandOld = true;

		// �F�ݒ�
		m_mMatcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		
		// �m�b�N�o�b�N�������
		m_sMotionFrag.bKnockBack = false;
		m_pMotion->ToggleFinish(true);

		// X�t�@�C���Ƃ̔���
		CStage *pStage = CGame::GetStage();
		if (pStage == NULL)
		{// NULL��������
			return;
		}

		// �X�e�[�W�ɓ�����������
		for (int nCntStage = 0; nCntStage < pStage->GetNumAll(); nCntStage++)
		{
			// �I�u�W�F�N�g�擾
			CObjectX *pObjX = pStage->GetObj(nCntStage);

			if (pObjX == NULL)
			{// NULL��������
				continue;
			}

			// �����擾
			bool bLand = false;
			pos.y = pObjX->GetHeight(pos, bLand);
		}
	}


	// �ʒu�ݒ�
	SetPosition(pos);

	// �ړ��ʐݒ�
	SetMove(move);

	// �����ݒ�
	SetRotation(rot);

	// �ڕW�̌����ݒ�
	SetRotDest(fRotDest);
}

//==========================================================================
// �ȈՍ���
//==========================================================================
void CPlayer::StateCompactUnion(void)
{
	// �e������
	if (m_pShadow != NULL)
	{
		m_pShadow->Uninit();
		m_pShadow = NULL;
	}
}

//==========================================================================
// ���̉���
//==========================================================================
void CPlayer::StateReleaseUnion(void)
{
	// ��ԑJ�ڃJ�E���^�[���Z
	m_nCntState--;

	if (m_nCntState <= 0)
	{// �J�ڃJ�E���^�[��0�ɂȂ�����

		m_nCntState = 0;
		m_state = STATE_NONE;

		// �e�̐���
		if (m_pShadow == NULL)
		{
			m_pShadow = CShadow::Create(GetPosition(), 50.0f);
		}
		return;
	}
}

//==========================================================================
// �i��
//==========================================================================
void CPlayer::StateEvolusion(void)
{
	int nType = m_pMotion->GetType();
	if (nType == MOTION_EVOLUTION && m_pMotion->IsFinish() == true)
	{// �L�b�N�U�����I����Ă���

		// �ʏ��Ԃɂ���
		m_state = STATE_NONE;

		// �ҋ@���[�V�����ݒ�
		m_pMotion->Set(MOTION_DEF);
		return;
	}

	// �����擾
	D3DXVECTOR3 rot = GetRotation();

	// �ڕW�̌����擾
	float fRotDest = GetRotDest();

	// �␳
	rot.y += (fRotDest - rot.y) * 0.1f;

	// �����̐ݒ�
	RotNormalize(rot.y);
	SetRotation(rot);

	if (nType != MOTION_EVOLUTION)
	{
		// �i�����[�V�����ݒ�
		m_pMotion->Set(MOTION_EVOLUTION);
	}
}

//==========================================================================
// �`�揈��
//==========================================================================
void CPlayer::Draw(void)
{

	// �`�揈��
	if (m_state == STATE_DMG)
	{
		CObjectChara::Draw(m_mMatcol);
	}
	else if (m_state == STATE_INVINCIBLE || m_state == STATE_FADEOUT)
	{
		CObjectChara::Draw(m_mMatcol.a);
	}
	else if(m_state != STATE_COMPACTUNION)
	{
		CObjectChara::Draw();
	}
}

//==========================================================================
// ��Ԑݒ�
//==========================================================================
void CPlayer::SetState(STATE state, int nCntState)
{
	m_state = state;
	m_nCntState = nCntState;
}

//==========================================================================
// ��Ԏ擾
//==========================================================================
int CPlayer::GetState(void)
{
	return m_state;
}

//==========================================================================
// �X�e�[�^�X�擾
//==========================================================================
CPlayer::sStatus CPlayer::GetStatus(void)
{
	return m_sStatus;
}
