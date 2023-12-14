//=============================================================================
// 
//  ���̃v���C���[���� [player_union.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "game.h"
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
#include "motion.h"
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
#include "gamemanager.h"
#include "instantfade.h"
#include "hp_gauge_player.h"
#include "fade.h"
#include "listmanager.h"
#include "item.h"
#include "injectiontable.h"
#include "enemy_boss.h"
#include "beam.h"

// �h����
#include "union_bodytoleg.h"
#include "union_bodytoarm.h"
#include "union_armtoarm.h"
#include "union_legtoarm.h"

//==========================================================================
// �萔��`
//==========================================================================
namespace
{
	char* TEXTURE_INITPLAYER[mylib_const::MAX_PLAYER][mylib_const::MAX_PLAYER] =	// �����v���C���[�̃e�N�X�`��
	{
		{// ��
			"data\\TEXTURE\\union\\SuperUnion\\Head\\union_head_UV_Red.jpg",
			"data\\TEXTURE\\union\\SuperUnion\\Head\\union_head_UV_Blue.jpg",
			"data\\TEXTURE\\union\\SuperUnion\\Head\\union_head_UV_Green.jpg",
			"data\\TEXTURE\\union\\SuperUnion\\Head\\union_head_UV_Yellow.jpg",
		},
		{// �r
			"data\\TEXTURE\\union\\SuperUnion\\Feet\\union_feet_UV_Red.jpg",
			"data\\TEXTURE\\union\\SuperUnion\\Feet\\union_feet_UV_Blue.jpg",
			"data\\TEXTURE\\union\\SuperUnion\\Feet\\union_feet_UV_Green.jpg",
			"data\\TEXTURE\\union\\SuperUnion\\Feet\\union_feet_UV_Yellow.jpg",
		},
		{// �r
			"data\\TEXTURE\\union\\SuperUnion\\Arm\\union_arm_UV_Red.jpg",
			"data\\TEXTURE\\union\\SuperUnion\\Arm\\union_arm_UV_Blue.jpg",
			"data\\TEXTURE\\union\\SuperUnion\\Arm\\union_arm_UV_Green.jpg",
			"data\\TEXTURE\\union\\SuperUnion\\Arm\\union_arm_UV_Yellow.jpg",
		},
		{// �r
			"data\\TEXTURE\\union\\SuperUnion\\Arm\\union_arm_UV_Red.jpg",
			"data\\TEXTURE\\union\\SuperUnion\\Arm\\union_arm_UV_Blue.jpg",
			"data\\TEXTURE\\union\\SuperUnion\\Arm\\union_arm_UV_Green.jpg",
			"data\\TEXTURE\\union\\SuperUnion\\Arm\\union_arm_UV_Yellow.jpg",
		}
	};
}
#define JUMP			(20.0f * 1.5f)	// �W�����v�͏����l
#define MAX_LIFE		(100)			// �̗�
#define TARGET_LEN		(400.0f)		// �ڕW�܂ł̋���
#define WALK_INT		(30)			// ���s�̎���
#define INVINCIBLE_INT	(2)				// ���G�̊Ԋu
#define INVINCIBLE_TIME	(90)			// ���G�̎���
#define CONFUSIONTIME	(60 * 2)		// ��������
#define DEADTIME		(120)
#define FADEOUTTIME		(60)
#define RADIUS			(250.0f)

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
bool CPlayerUnion::m_bAllLandInjectionTable = false;	// �S���̎ˏo�䒅�n����
bool CPlayerUnion::m_bLandInjectionTable[mylib_const::MAX_PLAYER] = {};	// �ˏo��̒��n����


//==========================================================================
// �֐��|�C���^
//==========================================================================
CPlayerUnion::ULT_FUNC CPlayerUnion::m_UltFuncList[] =
{
	&CPlayerUnion::UltBeam,	// �r�[��
};

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CPlayerUnion::CPlayerUnion(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	// ���L�ϐ�
	m_bJump = false;			// �W�����v�����ǂ���
	m_bLandOld = false;			// �ߋ��̒��n���
	m_bHitStage = false;		// �X�e�[�W�̓����蔻��
	m_bLandField = false;		// �t�B�[���h�̒��n����
	m_bHitWall = false;			// �ǂ̓����蔻��
	m_bKnockBack = false;		// �m�b�N�o�b�N�����ǂ���
	m_bDead = false;			// ���S�����ǂ���
	m_nUnionLife = 0;			// ���̎���
	m_nCntWalk = 0;				// ���s�J�E���^�[
	m_nCntInputAtk = 0;			// �U���̓��̓J�E���^�[
	m_state = STATE_NONE;		// ���
	memset(&m_pMotion[0], NULL, sizeof(m_pMotion));	// �p�[�c���̃��[�V�����|�C���^
	memset(&m_sMotionFrag[0], false, sizeof(m_sMotionFrag));	// ���[�V�����̃t���O

	// �v���C�x�[�g�ϐ�
	memset(&m_pObjChara[0], NULL, sizeof(m_pObjChara));	// �p�[�c���̃I�u�W�F�N�g�L�����N�^�[�|�C���^

	m_Oldstate = STATE_NONE;			// �O��̏��
	m_mMatcol = mylib_const::DEFAULT_COLOR;		// �}�e���A���̐F
	m_posKnokBack = mylib_const::DEFAULT_VECTOR3;	// �m�b�N�o�b�N�̈ʒu
	m_KnokBackMove = mylib_const::DEFAULT_VECTOR3;	// �m�b�N�o�b�N�̈ړ���
	m_nCntState = 0;			// ��ԑJ�ڃJ�E���^�[
	m_nTexIdx = 0;				// �e�N�X�`���̃C���f�b�N�X�ԍ�
	m_nIdxXFile = 0;			// X�t�@�C���̃C���f�b�N�X�ԍ�
	memset(&m_nPartsIdx[0], 0, sizeof(m_nPartsIdx));	// �v���C���[���̃p�[�c�C���f�b�N�X�ԍ�
	m_nMyPlayerIdx = 0;			// �v���C���[�C���f�b�N�X�ԍ�
	m_nControllMoveIdx = 0;		// �ړ����삷���̃C���f�b�N�X�ԍ�
	m_fRotDest = 0.0f;
	m_pShadow = NULL;			// �e�̏��
	m_pTargetP = NULL;			// �ڕW�̒n�_
	m_pHPGauge = NULL;			// HP�Q�[�W�̏��
	m_UltType = ULT_BEAM;		// �K�E�Z�̎��
	m_UltBranch = ULTBRANCH_CHARGE_BEAM;	// �K�E�Z�̕���
	memset(&m_apModel[0], NULL, sizeof(m_apModel));	// ���f��(�p�[�c)�̃|�C���^
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CPlayerUnion::~CPlayerUnion()
{

}

//==========================================================================
// ��������
//==========================================================================
CPlayerUnion *CPlayerUnion::Create(eType type)
{
	// �����p�̃I�u�W�F�N�g
	CPlayerUnion *pPlayer = NULL;

	if (pPlayer == NULL)
	{// NULL��������

		// �������̊m��
		switch (type)
		{
		case TYPE_ALL:
			pPlayer = DEBUG_NEW CPlayerUnion;
			break;

		case TYPE_BODYtoLEG:
			pPlayer = DEBUG_NEW CUnion_BodytoLeg;
			break;

		case TYPE_BODYtoARM:
			pPlayer = DEBUG_NEW CUnion_BodytoArm;
			break;

		case TYPE_LEGtoARM:
			pPlayer = DEBUG_NEW CUnion_LegtoArm;
			break;

		case TYPE_ARMtoARM:
			pPlayer = DEBUG_NEW CUnion_ArntoArm;
			break;

		default:
			return NULL;
			break;
		}

		if (pPlayer != NULL)
		{// �������̊m�ۂ��o���Ă�����

			// �v���C���[�C���f�b�N�X�ԍ�
			//pPlayer->m_nMyPlayerIdx = nIdx;

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
HRESULT CPlayerUnion::Init(void)
{
	// ��ނ̐ݒ�
	SetType(TYPE_PLAYER);

	m_state = STATE_APPEARANCE;	// ���
	m_nCntState = 0;		// ��ԑJ�ڃJ�E���^�[
	m_bLandOld = true;		// �O��̒��n���
	m_bAllLandInjectionTable = false;	// �S���̎ˏo�䒅�n����
	memset(&m_bLandInjectionTable[0], false, sizeof(m_bLandInjectionTable));	// �ˏo��̒��n����
	m_nUnionLife = 0;		// ���̎���

	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		m_nPartsIdx[i] = -1;
	}

	// �L�����쐬
	CreateParts();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �̗̓Q�[�W
	m_pHPGauge = CHP_GaugePlayer::Create(D3DXVECTOR3(250.0f, 600.0f, 0.0f), 50);

	// �e�̐���
	m_pShadow = CShadow::Create(pos, 50.0f);

	SetPosition(D3DXVECTOR3(-600.0f, 500.0f, 0.0f));

	return S_OK;
}

//==========================================================================
// �p�[�c�̐ݒ�
//==========================================================================
HRESULT CPlayerUnion::CreateParts(void)
{
	// �����L�����ǂݍ���
	ReadMultiCharacter("data\\TEXT\\multicharacter\\SuperUnion.txt");

	// �v���C���[�C���f�b�N�X���̃e�N�X�`���ݒ�
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		BindByPlayerIdxTexture(i, CManager::GetInstance()->GetByPlayerPartsType(i));
	}
	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CPlayerUnion::Uninit(void)
{
	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pMotion[i] != NULL)
		{
			m_pMotion[i]->Uninit();
			delete m_pMotion[i];
			m_pMotion[i] = NULL;
		}
	}

	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pObjChara[i] != NULL)
		{
			m_pObjChara[i] = NULL;
		}
	}

	// HP�Q�[�W������
	if (m_pHPGauge != NULL)
	{
		m_pHPGauge->Uninit();
		m_pHPGauge = NULL;
	}

	// �e������
	if (m_pShadow != NULL)
	{
		//m_pShadow->Uninit();
		m_pShadow = NULL;
	}

	// �I������
	CObject::Release();

	// ���[�h�ʏI������
	UninitByMode();
}

//==========================================================================
// ���[�h�ʏI������
//==========================================================================
void  CPlayerUnion::UninitByMode(void)
{
	//CScene *pScene = CManager::GetInstance()->GetScene();
	//if (pScene != NULL)
	//{
	//	// �v���C���[��NULL
	//	CManager::GetInstance()->GetScene()->UninitPlayer(m_nMyPlayerIdx);
	//}
}

//==========================================================================
// �I������
//==========================================================================
void CPlayerUnion::Kill(void)
{

	my_particle::Create(GetPosition(), my_particle::TYPE_ENEMY_FADE);

	// HP�Q�[�W������
	if (m_pHPGauge != NULL)
	{
		m_pHPGauge->Kill();
		m_pHPGauge = NULL;
	}

	// �e������
	if (m_pShadow != NULL)
	{
		m_pShadow->Uninit();
		m_pShadow = NULL;
	}

	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pObjChara[i] != NULL)
		{
			m_pObjChara[i]->Uninit();
			m_pObjChara[i] = NULL;
		}
	}
}

//==========================================================================
// �X�V����
//==========================================================================
void CPlayerUnion::Update(void)
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
	if (CManager::GetInstance()->GetScene()->GetMode() != CScene::MODE_RANKING)
	{
		if (CGame::GetEnemyManager()->GetState() == CEnemyManager::STATE_COMBOANIM)
		{
			return;
		}
	}

	// �ߋ��̈ʒu�ۑ�
	SetOldPosition(GetPosition());

	// ����
	if (CManager::GetInstance()->GetScene()->GetMode() != CScene::MODE_RANKING)
	{
		Controll();
	}

	for (int i = 0; i < PARTS_MAX; i++)
	{
		// ���[�V�����̐ݒ菈��
		MotionSet(i);
	}

	// ���[�V�����X�V
	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pMotion[i] == NULL)
		{
			continue;
		}
		D3DXVECTOR3 pos = m_pObjChara[i]->GetPosition();

		// ���[�V�����X�V
		m_pMotion[i]->Update();

		// ����
		D3DXVECTOR3 posDiff = m_pObjChara[i]->GetPosition() - pos;
		SetPosition(GetPosition() + posDiff);

		// �U������
		Atack(i);
	}

	// ��ԍX�V
	UpdateState();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	if (CGame::GetEnemyManager() != NULL && CGame::GetEnemyManager()->GetBoss() != NULL)
	{
		CEnemyBoss *pEnemyBoss = CGame::GetEnemyManager()->GetBoss();
		if (pEnemyBoss != NULL)
		{
			pEnemyBoss->SetTargetPosition(pos);
		}
	}

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// �����擾
	D3DXVECTOR3 rot = GetRotation();

	// �ʒu�E�����ݒ�
	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pObjChara[i] == NULL)
		{
			continue;
		}

		m_pObjChara[i]->SetPosition(pos);
		m_pObjChara[i]->SetRotation(rot);
	}

	// �e�̈ʒu�X�V
	if (m_pShadow != NULL)
	{
		m_pShadow->SetPosition(D3DXVECTOR3(pos.x, m_pShadow->GetPosition().y, pos.z));
	}

	// HP�Q�[�W�̈ʒu�X�V
	if (m_pHPGauge != NULL)
	{
		m_pHPGauge->Update();
		m_pHPGauge->SetLife(50);
	}

}

//==========================================================================
// ���쏈��
//==========================================================================
void CPlayerUnion::Controll(void)
{

	// �L�[�{�[�h���擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �Q�[���p�b�h���擾
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 newPosition = GetPosition();
	D3DXVECTOR3 sakiPos = GetPosition();

	// �����擾
	D3DXVECTOR3 rot = GetRotation();

	// �o�ߎ��Ԏ擾
	float fCurrentTime = CManager::GetInstance()->GetDeltaTime();

	if (CGame::GetGameManager()->IsControll())
	{// �s���ł���Ƃ�

		// �p�[�c�̃R���g���[������
		ControllParts();
	}

#if _DEBUG

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		m_state = STATE_ULT;	// ���
		m_UltBranch = ULTBRANCH_CHARGE_BEAM;
	}
#endif

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// �ړ��ʉ��Z
	newPosition.x += move.x;
	newPosition.z += move.z;

	sakiPos.x = newPosition.x + sinf(D3DX_PI + rot.y) * RADIUS;
	sakiPos.z = newPosition.z + cosf(D3DX_PI + rot.y) * RADIUS;

	// �p�x�̐��K��
	RotNormalize(m_fRotDest);

	// ���݂ƖڕW�̍��������߂�
	float fRotDiff = m_fRotDest - rot.y;

	// �p�x�̐��K��
	RotNormalize(fRotDiff);

	// �p�x�̕␳������
	rot.y += fRotDiff * 0.15f;

	// �p�x�̐��K��
	RotNormalize(rot.y);

	// �d�͏���
	if (m_state != STATE_KNOCKBACK && m_state != STATE_DMG && m_state != STATE_DEAD && m_state != STATE_FADEOUT)
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
		(bLandStage == false || bMove == true || m_bLandField == true || m_bJump == true || m_bKnockBack == true || m_bDead == true))
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


	// �J�����̏��擾
	CCamera *pCamera = CManager::GetInstance()->GetCamera();
	pCamera->SetTargetPosition(pos);
	pCamera->SetTargetRotation(rot);

	// �ڕW�̌����ݒ�
	//SetRotDest(m_fRotDest);

}

//==========================================================================
// �p�[�c�̃R���g���[������(�o�[�`����)
//==========================================================================
void CPlayerUnion::ControllParts(void)
{
	// �e���ʂ̑���	
	for (int i = 0; i < PARTS_MAX; i++)
	{
		int nPartsIdx = CManager::GetInstance()->GetByPlayerPartsType(i);
		switch (nPartsIdx)
		{
		case PARTS_BODY:
			ControllBody(nPartsIdx);
			break;

		case PARTS_LEG:
			ControllLeg(nPartsIdx);
			break;

		case PARTS_L_ARM:
			ControllLeftArm(nPartsIdx);
			break;

		case PARTS_R_ARM:
			ControllRightArm(nPartsIdx);
			break;
		}
	}
}

//==========================================================================
// ������
//==========================================================================
void CPlayerUnion::ControllBody(int nIdx)
{
	// �Q�[���p�b�h���擾
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

}

//==========================================================================
// �r����
//==========================================================================
void CPlayerUnion::ControllLeg(int nIdx)
{
	// �Q�[���p�b�h���擾
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	// �J�����̏��擾
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	// �J�����̌����擾
	D3DXVECTOR3 Camerarot = pCamera->GetRotation();

	// �ړ��ʎ擾
	float fMove = 2.5f;

	int nLeftArmIdx = CManager::GetInstance()->GetByPlayerPartsType(PARTS_L_ARM);
	int nRightArmIdx = CManager::GetInstance()->GetByPlayerPartsType(PARTS_R_ARM);

	if (m_state == STATE_DEAD ||
		m_state == STATE_FADEOUT)
	{
		return;
	}

	if (CGame::GetGameManager()->IsControll() &&
		m_pMotion[nIdx]->IsGetMove(m_pMotion[nIdx]->GetType()))
	{// �s���ł���Ƃ�

		// �ړ�����
		if (ControllMove(nIdx))
		{
			// �ړ����ɂ���
			for (int i = 0; i < PARTS_MAX; i++)
			{
				m_sMotionFrag[i].bMove = true;
				if (m_sMotionFrag[nRightArmIdx].bCharge == true)
				{
					m_sMotionFrag[nRightArmIdx].bMove = false;
				}
				if (m_sMotionFrag[nLeftArmIdx].bCharge == true)
				{
					m_sMotionFrag[nLeftArmIdx].bMove = false;
				}
			}
		}
		else
		{
			for (int i = 0; i < PARTS_MAX; i++)
			{
				m_sMotionFrag[i].bMove = false;
			}
		}


		// �ړ��ʎ擾
		D3DXVECTOR3 move = GetMove();

		// �W�����v
#if 0
		if (m_bJump == false &&
			pInputGamepad->GetTrigger(CInputGamepad::BUTTON_LB, nIdx))
		{//SPACE�������ꂽ,�W�����v

			m_bJump = true;
			move.y += 17.0f;

			// �W�����v���ɂ���
			for (int i = 0; i < PARTS_MAX; i++)
			{
				m_sMotionFrag[i].bJump = true;
				if (m_sMotionFrag[nRightArmIdx].bCharge == true)
				{
					m_sMotionFrag[nRightArmIdx].bJump = false;
				}
				if (m_sMotionFrag[nLeftArmIdx].bCharge == true)
				{
					m_sMotionFrag[nLeftArmIdx].bJump = false;
				}
			}

			// �T�E���h�Đ�
			CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_JUMP);
		}
#endif

		// �ړ��ʐݒ�
		SetMove(move);
	}
	else
	{
		for (int i = 0; i < PARTS_MAX; i++)
		{
			m_sMotionFrag[i].bMove = false;
		}

		// ��]����
		ControllRotation(nIdx);
	}

}

//==========================================================================
// �E�r����
//==========================================================================
void CPlayerUnion::ControllRightArm(int nIdx)
{
	// �Q�[���p�b�h���擾
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();
	
	if ((pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, nIdx)))
	{// �U��

		// �`���[�W����
		m_sMotionFrag[nIdx].bCharge = true;
	}

	if (m_sMotionFrag[nIdx].bCharge == true &&
		pInputGamepad->GetRelease(CInputGamepad::BUTTON_A, nIdx))
	{// �`���[�W���ɍU���{�^���𗣂�����

		// �U����
		m_sMotionFrag[nIdx].bCharge = false;
		m_sMotionFrag[nIdx].bATK = true;
	}
}

//==========================================================================
// ���r����
//==========================================================================
void CPlayerUnion::ControllLeftArm(int nIdx)
{
	// �Q�[���p�b�h���擾
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();
	
	if ((pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, nIdx)))
	{// �U��

		// �`���[�W����
		m_sMotionFrag[nIdx].bCharge = true;
	}

	if (m_sMotionFrag[nIdx].bCharge == true &&
		pInputGamepad->GetRelease(CInputGamepad::BUTTON_A, nIdx))
	{// �`���[�W���ɍU���{�^���𗣂�����

		// �U����
		m_sMotionFrag[nIdx].bCharge = false;
		m_sMotionFrag[nIdx].bATK = true;
	}
}

//==========================================================================
// �ړ�����
//==========================================================================
bool CPlayerUnion::ControllMove(int nIdx)
{

	// �L�[�{�[�h���擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �Q�[���p�b�h���擾
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// �J�����̏��擾
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	// �J�����̌����擾
	D3DXVECTOR3 Camerarot = pCamera->GetRotation();

	// �ړ��ʎ擾
	float fMove = 0.5f;

	bool bMove = true;

	if (pInputKeyboard->GetPress(DIK_A) == true || pInputGamepad->GetStickMoveL(nIdx).x < 0)
	{//���L�[�������ꂽ,���ړ�

		if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(nIdx).y > 0)
		{//A+W,����ړ�

			move.x += sinf(-D3DX_PI * 0.25f + Camerarot.y) * fMove;
			move.z += cosf(-D3DX_PI * 0.25f + Camerarot.y) * fMove;
			m_fRotDest = D3DX_PI * 0.75f + Camerarot.y;
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(nIdx).y < 0)
		{//A+S,�����ړ�

			move.x += sinf(-D3DX_PI * 0.75f + Camerarot.y) * fMove;
			move.z += cosf(-D3DX_PI * 0.75f + Camerarot.y) * fMove;
			m_fRotDest = D3DX_PI * 0.25f + Camerarot.y;
		}
		else
		{//A,���ړ�

			move.x += sinf(-D3DX_PI * 0.5f + Camerarot.y) * fMove;
			move.z += cosf(-D3DX_PI * 0.5f + Camerarot.y) * fMove;
			m_fRotDest = D3DX_PI * 0.5f + Camerarot.y;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true || pInputGamepad->GetStickMoveL(nIdx).x > 0)
	{//D�L�[�������ꂽ,�E�ړ�

		if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(nIdx).y > 0)
		{//D+W,�E��ړ�

			move.x += sinf(D3DX_PI * 0.25f + Camerarot.y) * fMove;
			move.z += cosf(D3DX_PI * 0.25f + Camerarot.y) * fMove;
			m_fRotDest = -D3DX_PI * 0.75f + Camerarot.y;
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(nIdx).y < 0)
		{//D+S,�E���ړ�

			move.x += sinf(D3DX_PI * 0.75f + Camerarot.y) * fMove;
			move.z += cosf(D3DX_PI * 0.75f + Camerarot.y) * fMove;
			m_fRotDest = -D3DX_PI * 0.25f + Camerarot.y;
		}
		else
		{//D,�E�ړ�

			move.x += sinf(D3DX_PI * 0.5f + Camerarot.y) * fMove;
			move.z += cosf(D3DX_PI * 0.5f + Camerarot.y) * fMove;
			m_fRotDest = -D3DX_PI * 0.5f + Camerarot.y;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(nIdx).y > 0)
	{//W�������ꂽ�A��ړ�

		move.x += sinf(D3DX_PI * 0.0f + Camerarot.y) * fMove;
		move.z += cosf(D3DX_PI * 0.0f + Camerarot.y) * fMove;
		m_fRotDest = D3DX_PI * 1.0f + Camerarot.y;
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(nIdx).y < 0)
	{//S�������ꂽ�A���ړ�

		move.x += sinf(D3DX_PI * 1.0f + Camerarot.y) * fMove;
		move.z += cosf(D3DX_PI * 1.0f + Camerarot.y) * fMove;
		m_fRotDest = D3DX_PI * 0.0f + Camerarot.y;
	}
	else
	{
		bMove = false;
	}

	// �ړ��ʐݒ�
	SetMove(move);

	return bMove;
}

//==========================================================================
// ��]����
//==========================================================================
void CPlayerUnion::ControllRotation(int nIdx)
{
	// �L�[�{�[�h���擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �Q�[���p�b�h���擾
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	// �J�����̏��擾
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	// �J�����̌����擾
	D3DXVECTOR3 Camerarot = pCamera->GetRotation();

	if (pInputKeyboard->GetPress(DIK_A) == true || pInputGamepad->GetStickMoveL(nIdx).x < 0)
	{//���L�[�������ꂽ,���ړ�

		if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(nIdx).y > 0)
		{//A+W,����ړ�
			m_fRotDest = D3DX_PI * 0.75f + Camerarot.y;
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(nIdx).y < 0)
		{//A+S,�����ړ�
			m_fRotDest = D3DX_PI * 0.25f + Camerarot.y;
		}
		else
		{//A,���ړ�
			m_fRotDest = D3DX_PI * 0.5f + Camerarot.y;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true || pInputGamepad->GetStickMoveL(nIdx).x > 0)
	{//D�L�[�������ꂽ,�E�ړ�

		if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(nIdx).y > 0)
		{//D+W,�E��ړ�
			m_fRotDest = -D3DX_PI * 0.75f + Camerarot.y;
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(nIdx).y < 0)
		{//D+S,�E���ړ�
			m_fRotDest = -D3DX_PI * 0.25f + Camerarot.y;
		}
		else
		{//D,�E�ړ�
			m_fRotDest = -D3DX_PI * 0.5f + Camerarot.y;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(nIdx).y > 0)
	{//W�������ꂽ�A��ړ�
		m_fRotDest = D3DX_PI * 1.0f + Camerarot.y;
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(nIdx).y < 0)
	{//S�������ꂽ�A���ړ�
		m_fRotDest = D3DX_PI * 0.0f + Camerarot.y;
	}
}

//==========================================================================
// ���[�V�����̐ݒ�
//==========================================================================
void CPlayerUnion::MotionSet(int nIdx)
{
	if (m_pMotion[nIdx] == NULL)
	{// ���[�V������NULL��������
		return;
	}

	if (m_state == STATE_ULT)
	{
		return;
	}

	if (m_pMotion[nIdx]->IsFinish() == true)
	{// �I�����Ă�����

		// ���݂̎�ގ擾
		int nType = m_pMotion[nIdx]->GetType();
		int nOldType = m_pMotion[nIdx]->GetOldType();

		if (m_sMotionFrag[nIdx].bMove == true &&
			m_sMotionFrag[nIdx].bATK == false &&
			m_bKnockBack == false &&
			m_bDead == false &&
			m_sMotionFrag[nIdx].bCharge == false &&
			m_bJump == false)
		{// �ړ����Ă�����

			// �ړ����[�V����
			m_pMotion[nIdx]->Set(MOTION_WALK);
			if (nIdx == PARTS_R_ARM || nIdx == PARTS_L_ARM)
			{// �r�p�[�c
				m_pMotion[nIdx]->SetNowPattern(m_pMotion[PARTS_BODY]->GetNowPattern());
				m_pMotion[nIdx]->SetFrameCount(m_pMotion[PARTS_BODY]->GetFrameCount());
			}
		}
		else if (m_sMotionFrag[nIdx].bJump == true &&
			m_sMotionFrag[nIdx].bATK == false &&
			m_sMotionFrag[nIdx].bCharge == false &&
			m_bKnockBack == false &&
			m_bDead == false)
		{// �W�����v��

			// �W�����v�̃t���OOFF
			m_sMotionFrag[nIdx].bJump = false;

			// �W�����v���[�V����
			m_pMotion[nIdx]->Set(MOTION_JUMP);
		}
		else if (m_bJump == true &&
			m_sMotionFrag[nIdx].bJump == false &&
			m_sMotionFrag[nIdx].bATK == false &&
			m_sMotionFrag[nIdx].bCharge == false &&
			m_bKnockBack == false &&
			m_bDead == false)
		{// �W�����v��&&�W�����v���[�V�������I����Ă鎞

			// �������[�V����
			m_pMotion[nIdx]->Set(MOTION_FALL);
		}
		else if (m_sMotionFrag[nIdx].bCharge == true)
		{// �`���[�W����������

			// �`���[�W���[�V����
			m_pMotion[nIdx]->Set(MOTION_CHARGE);
		}
		else if (m_bKnockBack == true)
		{// ���ꒆ��������

			// ���ꃂ�[�V����
			m_pMotion[nIdx]->Set(MOTION_KNOCKBACK);
		}
		else if (m_bDead == true)
		{// ���S����������

			// ���ꃂ�[�V����
			m_pMotion[nIdx]->Set(MOTION_DEAD);
		}
		else if (m_sMotionFrag[nIdx].bATK == true)
		{// �U�����Ă�����

			m_sMotionFrag[nIdx].bATK = false;		// �U������OFF
			m_pMotion[nIdx]->Set(MOTION_ATK, true);
		}
		else
		{
			// �j���[�g�������[�V����
			m_pMotion[nIdx]->Set(MOTION_DEF);
		}
	}
}

//==========================================================================
// �U��
//==========================================================================
void CPlayerUnion::Atack(int nIdx)
{
	if (m_pMotion[nIdx] == NULL)
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
	CMotion::Info aInfo = m_pMotion[nIdx]->GetInfo(m_pMotion[nIdx]->GetType());

	// �U�����̑����擾
	int nNumAttackInfo = aInfo.nNumAttackInfo;

	for (int nCntAttack = 0; nCntAttack < nNumAttackInfo; nCntAttack++)
	{
		if (aInfo.AttackInfo[nCntAttack] == NULL)
		{// NULL��������
			continue;
		}

		// �U�����ۑ�
		CMotion::AttackInfo atkInfo = *aInfo.AttackInfo[nCntAttack];

		if (atkInfo.bOnlyOneTime && nIdx != 0)
		{// 1�x������������ꍇ
			return;
		}

		if (m_pMotion[nIdx]->GetAllCount() == aInfo.AttackInfo[nCntAttack]->nInpactCnt)
		{// �Ռ��̃J�E���g�Ɠ����Ƃ�

			// �U��������
			AttackAction(nIdx, atkInfo.nCollisionNum, atkInfo);
		}

		// ���[�V�����J�E���^�[�擾
		if (m_pMotion[nIdx]->GetAllCount() > atkInfo.nMinCnt && m_pMotion[nIdx]->GetAllCount() < atkInfo.nMaxCnt)
		{// �U�����蒆
			
			// �U�����蒆����
			AttackInDicision(nIdx, atkInfo);
		}
	}

	CManager::GetInstance()->GetDebugProc()->Print(
		"���[�V�����J�E���^�[�F%d\n", m_pMotion[PARTS_BODY]->GetAllCount());
}

//==========================================================================
// �U��������
//==========================================================================
void CPlayerUnion::AttackAction(int nIdx, int nModelNum, CMotion::AttackInfo ATKInfo)
{

	// ����̈ʒu
	D3DXVECTOR3 weponpos = m_pMotion[nIdx]->GetAttackPosition(m_apModel[ATKInfo.nCollisionNum], ATKInfo);

	// �����擾
	D3DXVECTOR3 rot = GetRotation();

	// ��ޕ�
	switch (m_pMotion[nIdx]->GetType())
	{
	case MOTION_ATK:
	{
		float fMove = 0.5f;
		CBeam::Create(
			weponpos,							// �ʒu
			D3DXVECTOR3(
				sinf(D3DX_PI + rot.y) * fMove,
				cosf(D3DX_PI * 0.5f) * fMove,
				cosf(D3DX_PI + rot.y) * fMove),	// �ړ���
			mylib_const::PLAYERBEAM_COLOR,		// �F
			200.0f,		// ���a
			14000.0f,		// ����
			200,			// ����
			180,			// ���x
			1,	// �_���[�W
			CCollisionObject::TAG_PLAYER,	// �^�O
			CBeam::TYPE_RESIDUAL
		);
		// �U��
		CManager::GetInstance()->GetCamera()->SetShake(36, 50.0f, 0.0f);
	}
		break;

	case MOTION_WALK:
		
		my_particle::Create(weponpos, my_particle::TYPE_UNIONWALK);

		// �U��
		CManager::GetInstance()->GetCamera()->SetShake(12, 20.0f, 0.0f);
		break;
	}
}

//==========================================================================
// �U�����蒆����
//==========================================================================
void CPlayerUnion::AttackInDicision(int nIdx, CMotion::AttackInfo ATKInfo)
{
	// ����̈ʒu
	D3DXVECTOR3 weponpos = m_pMotion[nIdx]->GetAttackPosition(m_apModel[ATKInfo.nCollisionNum], ATKInfo);

	// �����擾
	D3DXVECTOR3 rot = GetRotation();

	// ���[�V�����J�E���^�[�擾
	float fAllCount = m_pMotion[nIdx]->GetAllCount();

	// ��ޕ�
	switch (m_pMotion[nIdx]->GetType())
	{
	case MOTION_CHARGE:
		my_particle::Create(weponpos, my_particle::TYPE_ATTACK_BODY);
		break;

	case MOTION_ATK:
		if ((int)fAllCount % 1 == 0)
		{
			//float fMove = 50.0f;
			//CBeam::Create(
			//	weponpos,							// �ʒu
			//	D3DXVECTOR3(
			//		sinf(D3DX_PI + rot.y) * fMove,
			//		cosf(D3DX_PI * 0.5f) * fMove,
			//		cosf(D3DX_PI + rot.y) * fMove),	// �ړ���
			//	mylib_const::PLAYERBEAM_COLOR,		// �F
			//	200.0f,		// ���a
			//	1000.0f,		// ����
			//	60,			// ����
			//	12,			// ���x
			//	1,	// �_���[�W
			//	CCollisionObject::TAG_PLAYER,	// �^�O
			//	CBeam::TYPE_RESIDUAL
			//);
		}
		break;
	}

	if (ATKInfo.fRangeSize == 0.0f)
	{
		return;
	}

#if _DEBUG
	CEffect3D::Create(weponpos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), ATKInfo.fRangeSize, 10, CEffect3D::MOVEEFFECT_NONE, CEffect3D::TYPE_NORMAL);
#endif

	// �G�擾
	CEnemyManager *pEnemyManager = CGame::GetEnemyManager();
	if (pEnemyManager == NULL)
	{
		return;
	}

	CEnemy **ppEnemy = pEnemyManager->GetEnemy();

	// �����擾
	int nNumAll = pEnemyManager->GetNumAll();
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

		if (SphereRange(weponpos, TargetPos, ATKInfo.fRangeSize, fTargetRadius))
		{// ���̔���

			if (ppEnemy[i]->Hit(ATKInfo.nDamage) == true)
			{// �������Ă���

			}
		}

		// �G�̐����Z
		nCntEnemy++;
	}
}

//==========================================================================
// �����蔻��
//==========================================================================
bool CPlayerUnion::Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &move)
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

				if ((m_bKnockBack == true || m_bJump == true) && GetPosition().y >= fHeight)
				{
					m_bLandOld = true;
				}

				if (m_bJump == true)
				{// �W�����v����������
					m_pMotion[PARTS_BODY]->ToggleFinish(true);
				}

				// �W�����v�g�p�\�ɂ���
				m_bJump = false;
				move.y = 0.0f;
				bNowLand = true;

				for (int i = 0; i < PARTS_MAX; i++)
				{
					m_sMotionFrag[i].bJump = false;
				}
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

			if ((m_bKnockBack || m_bJump == true) && GetPosition().y >= fHeight)
			{
				m_bLandOld = true;
			}

			if (m_bJump == true)
			{// �W�����v����������
				m_pMotion[PARTS_BODY]->ToggleFinish(true);
			}

			// �W�����v�g�p�\�ɂ���
			m_bJump = false;
			move.y = 0.0f;
			bNowLand = true;
			
			for (int i = 0; i < PARTS_MAX; i++)
			{
				m_sMotionFrag[i].bJump = false;
			}

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





	// �ʒu�擾
	D3DXVECTOR3 posOld = GetPosition();

	//// ��
	//float fLen = CGame::GetElevation()->GetWidthLen();
	//int nBlock = CGame::GetElevation()->GetWidthBlock();
	//nBlock /= 2;
	//if (pos.x + RADIUS >= fLen * nBlock) { pos.x = fLen * nBlock - RADIUS; }
	//if (pos.x - RADIUS <= -fLen * nBlock) { pos.x = -fLen * nBlock + RADIUS; }
	//if (pos.z + RADIUS >= fLen * nBlock) { pos.z = fLen * nBlock - RADIUS; }
	//if (pos.z - RADIUS <= -fLen * nBlock) { pos.z = -fLen * nBlock + RADIUS; }

	// �����ݒ�
	SetRotation(rot);

	return bNowLand;
}

//==========================================================================
// �q�b�g����
//==========================================================================
bool CPlayerUnion::Hit(const int nValue)
{
	// �̗͎擾
	int nLife = 50;

	//if (nLife <= 0)
	//{
	//	// ����
	//	return true;
	//}

	if (m_state != STATE_DMG && m_state != STATE_KNOCKBACK && m_state != STATE_INVINCIBLE && m_state != STATE_DEAD && m_state != STATE_FADEOUT)
	{// �_���[�W��t��Ԃ̎�

		// �̗͌��炷
		nLife -= nValue;


		// �Q�[���p�b�h���擾
		CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();
		pInputGamepad->SetVibration(CInputGamepad::VIBRATION_STATE_DMG, 0);

		m_KnokBackMove.y += 18.0f;
		m_bHitStage = false;

		// �̗͐ݒ�
		//SetLife(nLife);

		if (nLife <= 0)
		{// �̗͂��Ȃ��Ȃ�����

			// �����
			m_state = STATE_DEAD;

			m_KnokBackMove.y = 8.0f;

			// �J�ڃJ�E���^�[�ݒ�
			m_nCntState = DEADTIME;

			// �̗͐ݒ�
			//SetLife(0);

			// �m�b�N�o�b�N����ɂ���
			m_bKnockBack = true;

			// ���ꃂ�[�V����
			m_pMotion[PARTS_BODY]->Set(MOTION_KNOCKBACK);

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
		m_bKnockBack = true;

		// ���ꃂ�[�V����
		m_pMotion[PARTS_BODY]->Set(MOTION_KNOCKBACK);

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
// ��ԍX�V����
//==========================================================================
void CPlayerUnion::UpdateState(void)
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

	case STATE_APPEARANCE:
		Appearance();
		break;

	case STATE_ULT:
		Ultimate();
		break;
	}
}

//==========================================================================
// ���G
//==========================================================================
void CPlayerUnion::Invincible(void)
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
void CPlayerUnion::Damage(void)
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
		m_bKnockBack = false;
		m_pMotion[PARTS_BODY]->ToggleFinish(true);


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
void CPlayerUnion::Dead(void)
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
		m_bKnockBack = false;
		m_bDead = true;
		//m_pMotion->ToggleFinish(true);

		// �Ԃ��|�ꃂ�[�V����
		m_pMotion[PARTS_BODY]->Set(MOTION_DEAD);

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
void CPlayerUnion::FadeOut(void)
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
void CPlayerUnion::KnockBack(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// �����擾
	D3DXVECTOR3 rot = GetRotation();

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
		m_bKnockBack = false;
		//m_pMotion[PARTS_BODY]->ToggleFinish(true);

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
}

//==========================================================================
// �o��
//==========================================================================
void CPlayerUnion::Appearance(void)
{
	int nType = m_pMotion[0]->GetType();
	if (nType == MOTION_APPEARANCE && m_pMotion[0]->IsFinish() == true)
	{// �o�ꉉ�o���I����Ă���
		m_nCntState = 0;
		m_state = STATE_NONE;
	}

	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pMotion[i] == NULL)
		{
			continue;
		}
		// �o�ꃂ�[�V�����ݒ�
		m_pMotion[i]->Set(MOTION_APPEARANCE);
	}
}

//==========================================================================
// �K�E�Z
//==========================================================================
void CPlayerUnion::Ultimate(void)
{
	// ��ԕʏ���
	(this->*(m_UltFuncList[m_UltType]))();
}

//==========================================================================
// �K�E�F�r�[��
//==========================================================================
void CPlayerUnion::UltBeam(void)
{
	switch (m_UltBranch)
	{
	case CPlayerUnion::ULTBRANCH_CHARGE_BEAM:
		UltChargeBeam();
		break;

	case CPlayerUnion::ULTBRANCH_ATTACK_BEAM:
		UltAttackBeam();
		break;

	default:
		m_UltBranch = ULTBRANCH_CHARGE_BEAM;
		break;
	}
}

//==========================================================================
// �r�[���`���[�W
//==========================================================================
void CPlayerUnion::UltChargeBeam(void)
{

	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		if (m_pMotion[i] == NULL)
		{
			continue;
		}

		int nType = m_pMotion[i]->GetType();
		if (nType == MOTION_CHARGE && m_pMotion[i]->IsFinish() == true)
		{// �`���[�W���I����Ă���

			// �ҋ@�s��
			m_UltBranch = ULTBRANCH_ATTACK_BEAM;

			// �K�E�r�[�����[�V�����ݒ�
			m_pMotion[i]->Set(MOTION_ATK);
			return;
		}

		if (nType != MOTION_CHARGE)
		{
			// �`���[�W���[�V�����ݒ�
			m_pMotion[i]->Set(MOTION_CHARGE);
		}
	}
}

//==========================================================================
// �r�[���U��
//==========================================================================
void CPlayerUnion::UltAttackBeam(void)
{
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		if (m_pMotion[i] == NULL)
		{
			continue;
		}

		int nType = m_pMotion[i]->GetType();
		if (nType == MOTION_ATK && m_pMotion[i]->IsFinish() == true)
		{// �`���[�W���I����Ă���

			// �Ȃɂ��Ȃ����
			m_state = STATE_NONE;

			// �K�E�r�[�����[�V�����ݒ�
			m_pMotion[i]->Set(MOTION_DEF);
			return;
		}

		if (nType != MOTION_ATK)
		{
			// �r�[�����[�V�����ݒ�
			m_pMotion[i]->Set(MOTION_ATK);
		}
	}
}

//==========================================================================
// �`�揈��
//==========================================================================
void CPlayerUnion::Draw(void)
{

	/*if (m_state == STATE_DMG)
	{
		CObjectChara::Draw(m_mMatcol);
	}
	else if (m_state == STATE_INVINCIBLE || m_state == STATE_FADEOUT)
	{
		CObjectChara::Draw(m_mMatcol.a);
	}
	else
	{
		CObjectChara::Draw();
	}*/

	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pObjChara[i] == NULL)
		{
			continue;
		}

		// �U������
		//m_pObjChara[i]->Draw();		// ����
	}

	// HP�Q�[�W
	if (m_pHPGauge != NULL)
	{
		m_pHPGauge->Draw();
	}
}


//==========================================================================
// �v���C���[�C���f�b�N�X���̃e�N�X�`���ݒ�
//==========================================================================
void CPlayerUnion::BindByPlayerIdxTexture(int nIdx, int nPartsIdx)
{
	// �t�@�C���C���f�b�N�X�ԍ��擾
	int nIdxXFile = m_pObjChara[nIdx]->GetIdxFile();
	CObjectChara::Load LoadData = m_pObjChara[nIdx]->GetLoadData(nIdxXFile);

	// ���f���擾
	CModel **ppModel = m_pObjChara[nIdx]->GetModel();

	// �����e�N�X�`��
	int nIdxTex = CManager::GetInstance()->GetTexture()->Regist(TEXTURE_INITPLAYER[nIdx][nPartsIdx]);
	for (int i = 0; i < m_pObjChara[nIdx]->GetNumModel(); i++)
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

}

//==========================================================================
// �����L�����N�^�[�ǂݍ���
//==========================================================================
void CPlayerUnion::ReadMultiCharacter(const char *pTextFile)
{
	FILE *pFile = NULL;	// �t�@�C���|�C���^��錾

	// �t�@�C�����J��
	pFile = fopen(pTextFile, "r");

	if (pFile == NULL)
	{//�t�@�C�����J�����ꍇ
		return;
	}

	char aComment[MAX_COMMENT];	// �R�����g

	std::string CharacterFile[mylib_const::MAX_PLAYER];
	std::string MotionFile;
	int nCntFileName = 0;
	int nNumParts = 0;
	int nCntModel = 0;

	while (1)
	{// END_SCRIPT������܂ŌJ��Ԃ�

		// ������̓ǂݍ���
		fscanf(pFile, "%s", &aComment[0]);

		// �p�[�c���̐ݒ�
		if (strcmp(aComment, "NUM_PARTS") == 0)
		{// NUM_PARTS��������

			fscanf(pFile, "%s", &aComment[0]);	// =�̕�
			fscanf(pFile, "%d", &nNumParts);	// �p�[�c��
		}

		// ���[�V�����t�@�C����
		if (strcmp(aComment, "MOTION_FILENAME") == 0)
		{// MOTION_FILENAME��������

			fscanf(pFile, "%s", &aComment[0]);	// =�̕�
			fscanf(pFile, "%s", &aComment[0]);	// �t�@�C����

			// �t�@�C�����ۑ�
			MotionFile = aComment;

			// �Z�b�g�A�b�v���
			while (nCntFileName != nNumParts)
			{// ���f���̐����ǂݍ��ނ܂ŌJ��Ԃ�

				// ������̓ǂݍ���
				fscanf(pFile, "%s", &aComment[0]);

				// �Z�b�g�A�b�v�̐ݒ�
				if (strcmp(aComment, "SETUP_FILENAME") == 0)
				{// SETUP_FILENAME��������

					fscanf(pFile, "%s", &aComment[0]);	// =�̕�
					fscanf(pFile, "%s", &aComment[0]);	// �t�@�C����

					// �t�@�C�����ۑ�
					CharacterFile[nCntFileName] = aComment;


					//**********************************
					// �L�����N�^�[����
					//**********************************
					m_pObjChara[nCntFileName] = CObjectChara::Create(CharacterFile[nCntFileName]);
					if (m_pObjChara[nCntFileName] == NULL)
					{// ���s���Ă�����
						return;
					}
					m_pObjChara[nCntFileName]->SetType(CObject::TYPE_OBJECTX);

					// ���[�V�����̐�������
					m_pMotion[nCntFileName] = CMotion::Create(MotionFile);

					// �I�u�W�F�N�g�L�����N�^�[�̏��擾
					CObjectChara *pObjChar = m_pObjChara[nCntFileName]->GetObjectChara();

					// ���[�V�����̐ݒ�
					m_pMotion[nCntFileName]->SetModel(pObjChar->GetModel(), pObjChar->GetNumModel(), pObjChar);

					// �|�[�Y�̃��Z�b�g
					m_pMotion[nCntFileName]->ResetPose(MOTION_DEF);

					// ���f���R�s�[
					CModel **ppModel = pObjChar->GetModel();
					for (int i = 0; i < pObjChar->GetNumModel(); i++)
					{
						m_apModel[nCntModel] = ppModel[i];
						nCntModel++;
					}

					nCntFileName++;	// �t�@�C�������Z
				}
			}
		}

		// �e�p�[�c�̐ݒ�
		if (strcmp(aComment, "PARENTSET") == 0)
		{// �e�ݒ�̓ǂݍ��݂��J�n

			int nFileNumber = -1, nModelIdx = -1, nParentFileNumber = -1, nParentModelIdx = -1;

			while (strcmp(aComment, "END_PARENTSET") != 0)
			{// END_PARENTSET������܂ŌJ��Ԃ�

				fscanf(pFile, "%s", &aComment[0]);	//�m�F����

				if (strcmp(aComment, "FILENUMBER") == 0)
				{// FILENUMBER�Őݒ肷��L�����N�^�[�t�@�C���ԍ��ǂݍ���

					fscanf(pFile, "%s", &aComment[0]);	// =�̕�
					fscanf(pFile, "%d", &nFileNumber);	// �L�����N�^�[�t�@�C���ԍ�
				}

				if (strcmp(aComment, "MODELINDEX") == 0)
				{// MODELINDEX�Őݒ肷�郂�f���ԍ��ǂݍ���

					fscanf(pFile, "%s", &aComment[0]);	// =�̕�
					fscanf(pFile, "%d", &nModelIdx);	// �ݒ肷�郂�f���ԍ�
				}

				if (strcmp(aComment, "PARENT_FILENUMBER") == 0)
				{// PARENT_FILENUMBER�Őe�ɂ���L�����N�^�[�t�@�C���ԍ��ǂݍ���

					fscanf(pFile, "%s", &aComment[0]);	// =�̕�
					fscanf(pFile, "%d", &nParentFileNumber);	// �L�����N�^�[�t�@�C���ԍ�
				}

				if (strcmp(aComment, "PARENT_MODELINDEX") == 0)
				{// PARENT_MODELINDEX�Őe�ɂ��郂�f���ԍ��ǂݍ���

					fscanf(pFile, "%s", &aComment[0]);	// =�̕�
					fscanf(pFile, "%d", &nParentModelIdx);	// �ݒ肷�郂�f���ԍ�
				}
			}// END_PARENTSET�̂�����

			// ���_�ݒ�
			m_pObjChara[nFileNumber]->GetModel()[nModelIdx]->SetParent(m_pObjChara[nParentFileNumber]->GetModel()[nParentModelIdx]);
		}

		if (strcmp(aComment, "END_SCRIPT") == 0)
		{// �I�������Ń��[�v�𔲂���
			break;
		}
	}

	// �t�@�C�������
	fclose(pFile);

}

//==========================================================================
// �v���C���[���̃p�[�c�C���f�b�N�X�ԍ��ݒ�
//==========================================================================
void CPlayerUnion::SetPlayerByPartsIdx(int nPartsIdx, int nPlayerIdx)
{
	m_nPartsIdx[nPartsIdx] = nPlayerIdx;
	m_nInputSuperAtkIdx = nPlayerIdx;
}

//==========================================================================
// �ړ��̑��삷��C���f�b�N�X�ԍ��ݒ�
//==========================================================================
void CPlayerUnion::SetControllMoveIdx(int nIdx)
{
	m_nControllMoveIdx = nIdx;
}

//==========================================================================
// ��Ԏ擾
//==========================================================================
int CPlayerUnion::GetState(void)
{
	return m_state;
}