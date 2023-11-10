//=============================================================================
// 
//  �v���C���[���� [player_union.cpp]
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

// �h����
#include "tutorialplayer.h"

//==========================================================================
// �}�N����`
//==========================================================================
#define CHARAFILE		"data\\TEXT\\motion_set_player.txt"
#define JUMP			(20.0f * 1.5f)	// �W�����v�͏����l
#define MAX_LIFE		(100)			// �̗�
#define TARGET_LEN		(400.0f)		// �ڕW�܂ł̋���
#define WALK_INT		(30)			// ���s�̎���
#define INVINCIBLE_INT	(2)				// ���G�̊Ԋu
#define INVINCIBLE_TIME	(90)			// ���G�̎���
#define CONFUSIONTIME	(60 * 2)		// ��������
#define DEADTIME		(120)
#define FADEOUTTIME		(60)
#define RADIUS	(250.0f)

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
const char *CPlayerUnion::m_apModelFile[mylib_const::MAX_PLAYER] =	// ���f���̃t�@�C��
{
	"data\\TEXT\\player_union\\motion_body.txt",
	"data\\TEXT\\player_union\\motion_leg.txt",
	"data\\TEXT\\player_union\\motion_RArm.txt",
	"data\\TEXT\\player_union\\motion_LArm.txt",
};

bool CPlayerUnion::m_bAllLandInjectionTable = false;	// �S���̎ˏo�䒅�n����
bool CPlayerUnion::m_bLandInjectionTable[mylib_const::MAX_PLAYER] = {};	// �ˏo��̒��n����

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CPlayerUnion::CPlayerUnion(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	// ���L�ϐ�
	m_bJump = false;				// �W�����v�����ǂ���
	m_bLandOld = false;			// �ߋ��̒��n���
	m_bHitStage = false;			// �X�e�[�W�̓����蔻��
	m_bLandField = false;			// �t�B�[���h�̒��n����
	m_bHitWall = false;			// �ǂ̓����蔻��
	m_nCntWalk = 0;				// ���s�J�E���^�[
	m_state = STATE_NONE;			// ���

	memset(&m_pMotion[0], NULL, sizeof(m_pMotion));	// �p�[�c���̃��[�V�����|�C���^
	memset(&m_sMotionFrag[0], false, sizeof(m_sMotionFrag));	// ���[�V�����̃t���O
	memset(&m_sAllCharaMotironFrag, false, sizeof(m_sAllCharaMotironFrag));	// ���[�V�����̃t���O

	// �v���C�x�[�g�ϐ�
	memset(&m_pObjChara[0], NULL, sizeof(m_pObjChara));	// �p�[�c���̃I�u�W�F�N�g�L�����N�^�[�|�C���^

	m_Oldstate = STATE_NONE;			// �O��̏��
	m_mMatcol = mylib_const::DEFAULT_COLOR;		// �}�e���A���̐F
	m_posKnokBack = mylib_const::DEFAULT_VECTOR3;	// �m�b�N�o�b�N�̈ʒu
	m_KnokBackMove = mylib_const::DEFAULT_VECTOR3;	// �m�b�N�o�b�N�̈ړ���
	m_nCntState = 0;			// ��ԑJ�ڃJ�E���^�[
	m_nTexIdx = 0;				// �e�N�X�`���̃C���f�b�N�X�ԍ�
	m_nIdxXFile = 0;			// X�t�@�C���̃C���f�b�N�X�ԍ�
	m_nMyPlayerIdx = 0;			// �v���C���[�C���f�b�N�X�ԍ�
	m_fRotDest = 0.0f;
	m_pShadow = NULL;			// �e�̏��
	m_pTargetP = NULL;	// �ڕW�̒n�_
	m_pHPGauge = NULL;	// HP�Q�[�W�̏��
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
CPlayerUnion *CPlayerUnion::Create(void)
{
	// �����p�̃I�u�W�F�N�g
	CPlayerUnion *pPlayer = NULL;

	if (pPlayer == NULL)
	{// NULL��������

		// �������̊m��
		switch (CManager::GetInstance()->GetMode())
		{
		case CScene::MODE_GAME:
			pPlayer = DEBUG_NEW CPlayerUnion;
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

	m_state = STATE_NONE;	// ���
	m_nCntState = 0;		// ��ԑJ�ڃJ�E���^�[
	m_bLandOld = true;		// �O��̒��n���
	m_bAllLandInjectionTable = false;	// �S���̎ˏo�䒅�n����
	memset(&m_bLandInjectionTable[0], false, sizeof(m_bLandInjectionTable));	// �ˏo��̒��n����

	// �L�����쐬

	HRESULT hr;
	CObjectChara *pObjChar = NULL;


	//**********************************
	// ����
	//**********************************
	m_pObjChara[PARTS_BODY] = CObjectChara::Create(m_apModelFile[PARTS_BODY]);
	if (m_pObjChara[PARTS_BODY] == NULL)
	{// ���s���Ă�����
		return E_FAIL;
	}

	// ���[�V�����̐�������
	m_pMotion[PARTS_BODY] = CMotion::Create(m_apModelFile[PARTS_BODY]);

	// �I�u�W�F�N�g�L�����N�^�[�̏��擾
	pObjChar = m_pObjChara[PARTS_BODY]->GetObjectChara();

	// ���[�V�����̐ݒ�
	m_pMotion[PARTS_BODY]->SetModel(pObjChar->GetModel(), pObjChar->GetNumModel(), pObjChar);

	// �|�[�Y�̃��Z�b�g
	m_pMotion[PARTS_BODY]->ResetPose(MOTION_DEF);


	//**********************************
	// �r
	//**********************************
	m_pObjChara[PARTS_LEG] = CObjectChara::Create(m_apModelFile[PARTS_LEG]);
	if (m_pObjChara[PARTS_LEG] == NULL)
	{// ���s���Ă�����
		return E_FAIL;
	}

	// ���[�V�����̐�������
	m_pMotion[PARTS_LEG] = CMotion::Create(m_apModelFile[PARTS_LEG]);

	// �I�u�W�F�N�g�L�����N�^�[�̏��擾
	pObjChar = m_pObjChara[PARTS_LEG]->GetObjectChara();

	// ���[�V�����̐ݒ�
	m_pMotion[PARTS_LEG]->SetModel(pObjChar->GetModel(), pObjChar->GetNumModel(), pObjChar);

	// �|�[�Y�̃��Z�b�g
	m_pMotion[PARTS_LEG]->ResetPose(MOTION_DEF);


	//**********************************
	// �E�r
	//**********************************
	m_pObjChara[PARTS_R_ARM] = CObjectChara::Create(m_apModelFile[PARTS_R_ARM]);
	if (m_pObjChara[PARTS_R_ARM] == NULL)
	{// ���s���Ă�����
		return E_FAIL;
	}

	// ���[�V�����̐�������
	m_pMotion[PARTS_R_ARM] = CMotion::Create(m_apModelFile[PARTS_R_ARM]);

	// �I�u�W�F�N�g�L�����N�^�[�̏��擾
	pObjChar = m_pObjChara[PARTS_R_ARM]->GetObjectChara();

	// ���[�V�����̐ݒ�
	m_pMotion[PARTS_R_ARM]->SetModel(pObjChar->GetModel(), pObjChar->GetNumModel(), pObjChar);

	// �|�[�Y�̃��Z�b�g
	m_pMotion[PARTS_R_ARM]->ResetPose(MOTION_DEF);


	//**********************************
	// ���r
	//**********************************
	m_pObjChara[PARTS_L_ARM] = CObjectChara::Create(m_apModelFile[PARTS_L_ARM]);
	if (m_pObjChara[PARTS_L_ARM] == NULL)
	{// ���s���Ă�����
		return E_FAIL;
	}

	// ���[�V�����̐�������
	m_pMotion[PARTS_L_ARM] = CMotion::Create(m_apModelFile[PARTS_L_ARM]);

	// �I�u�W�F�N�g�L�����N�^�[�̏��擾
	pObjChar = m_pObjChara[PARTS_L_ARM]->GetObjectChara();

	// ���[�V�����̐ݒ�
	m_pMotion[PARTS_L_ARM]->SetModel(pObjChar->GetModel(), pObjChar->GetNumModel(), pObjChar);

	// �|�[�Y�̃��Z�b�g
	m_pMotion[PARTS_L_ARM]->ResetPose(MOTION_DEF);


	// ���r�̌��_��̂ɂ���
	m_pObjChara[PARTS_L_ARM]->GetModel()[0]->SetParent(m_pObjChara[PARTS_BODY]->GetModel()[1]);
	m_pObjChara[PARTS_R_ARM]->GetModel()[0]->SetParent(m_pObjChara[PARTS_BODY]->GetModel()[1]);
	m_pObjChara[PARTS_LEG]->GetModel()[0]->SetParent(m_pObjChara[PARTS_BODY]->GetModel()[0]);
	m_pObjChara[PARTS_LEG]->GetModel()[3]->SetParent(m_pObjChara[PARTS_BODY]->GetModel()[0]);


	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �̗̓Q�[�W
	m_pHPGauge = CHP_GaugePlayer::Create(D3DXVECTOR3(250.0f, 600.0f, 0.0f), 50);

	// �e�̐���
	m_pShadow = CShadow::Create(pos, 50.0f);
	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CPlayerUnion::Uninit(void)
{
	if (m_pMotion[PARTS_BODY] != NULL)
	{
		m_pMotion[PARTS_BODY]->Uninit();
		delete m_pMotion[PARTS_BODY];
		m_pMotion[PARTS_BODY] = NULL;
	}
	if (m_pMotion[PARTS_LEG] != NULL)
	{
		m_pMotion[PARTS_LEG]->Uninit();
		delete m_pMotion[PARTS_LEG];
		m_pMotion[PARTS_LEG] = NULL;
	}
	if (m_pMotion[PARTS_R_ARM] != NULL)
	{
		m_pMotion[PARTS_R_ARM]->Uninit();
		delete m_pMotion[PARTS_R_ARM];
		m_pMotion[PARTS_R_ARM] = NULL;
	}
	if (m_pMotion[PARTS_L_ARM] != NULL)
	{
		m_pMotion[PARTS_L_ARM]->Uninit();
		delete m_pMotion[PARTS_L_ARM];
		m_pMotion[PARTS_L_ARM] = NULL;
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
	if (CGame::GetEnemyManager()->GetState() == CEnemyManager::STATE_COMBOANIM)
	{
		return;
	}

	// �ߋ��̈ʒu�ۑ�
	SetOldPosition(GetPosition());

	// ����
	Controll();

	for (int i = 0; i < PARTS_MAX; i++)
	{
		m_sMotionFrag[i] = m_sAllCharaMotironFrag;

		// ���[�V�����̐ݒ菈��
		MotionSet(i);
	}
	memset(&m_sAllCharaMotironFrag, false, sizeof(m_sAllCharaMotironFrag));


	// ���[�V�����X�V
	if (m_pMotion[PARTS_BODY] != NULL)
	{
		m_pMotion[PARTS_BODY]->Update();
	}
	if (m_pMotion[PARTS_LEG] != NULL)
	{
		m_pMotion[PARTS_LEG]->Update();
	}
	if (m_pMotion[PARTS_R_ARM] != NULL)
	{
		m_pMotion[PARTS_R_ARM]->Update();
	}
	if (m_pMotion[PARTS_L_ARM] != NULL)
	{
		m_pMotion[PARTS_L_ARM]->Update();
	}

	// ���_���ݒ�
	SetVtx();

	// �U������
	Atack();

	// ��ԍX�V
	UpdateState();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// �����擾
	D3DXVECTOR3 rot = GetRotation();

	m_pObjChara[PARTS_BODY]->SetPosition(pos);		// ����
	m_pObjChara[PARTS_LEG]->SetPosition(pos);		// �r
	m_pObjChara[PARTS_R_ARM]->SetPosition(pos);	// �E�r
	m_pObjChara[PARTS_L_ARM]->SetPosition(pos);	// ���r

	m_pObjChara[PARTS_BODY]->SetRotation(rot);		// ����
	m_pObjChara[PARTS_LEG]->SetRotation(rot);		// �r
	m_pObjChara[PARTS_R_ARM]->SetRotation(rot);	// �E�r
	m_pObjChara[PARTS_L_ARM]->SetRotation(rot);	// ���r

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

	// �f�o�b�O�\��
	CManager::GetInstance()->GetDebugProc()->Print(
		"------------------[�v���C���[�̑���]------------------\n"
		"�ʒu�F�yX�F%f, Y�F%f, Z�F%f�z �yW / A / S / D�z\n"
		"�����F�yX�F%f, Y�F%f, Z�F%f�z �yZ / C�z\n"
		"�ړ��ʁF�yX�F%f, Y�F%f, Z�F%f�z\n"
		"�̗́F�y%d�z\n", pos.x, pos.y, pos.z, rot.x, rot.y, rot.y, move.x, move.y, move.z, 50);
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

	// �J�����̏��擾
	CCamera *pCamera = CManager::GetInstance()->GetScene()->GetMultiCamera(m_nMyPlayerIdx);

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

	// �ړ��ʎ擾
	float fMove = 2.5f;

	// �o�ߎ��Ԏ擾
	float fCurrentTime = CManager::GetInstance()->DeltaTime();

	if (CGame::GetGameManager()->IsControll())
	{// �s���ł���Ƃ�

		if (m_state != STATE_DEAD &&
			m_state != STATE_FADEOUT)
		{// �ړ��\���[�V�����̎�

			if (pInputKeyboard->GetPress(DIK_A) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).x < 0)
			{//���L�[�������ꂽ,���ړ�

				// �ړ����ɂ���
				m_sAllCharaMotironFrag.bMove = true;

				if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y > 0)
				{//A+W,����ړ�

					move.x += sinf(-D3DX_PI * 0.25f + Camerarot.y) * fMove;
					move.z += cosf(-D3DX_PI * 0.25f + Camerarot.y) * fMove;
					m_fRotDest = D3DX_PI * 0.75f + Camerarot.y;
				}
				else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y < 0)
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
			else if (pInputKeyboard->GetPress(DIK_D) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).x > 0)
			{//D�L�[�������ꂽ,�E�ړ�

				// �ړ����ɂ���
				m_sAllCharaMotironFrag.bMove = true;

				if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y > 0)
				{//D+W,�E��ړ�

					move.x += sinf(D3DX_PI * 0.25f + Camerarot.y) * fMove;
					move.z += cosf(D3DX_PI * 0.25f + Camerarot.y) * fMove;
					m_fRotDest = -D3DX_PI * 0.75f + Camerarot.y;
				}
				else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y < 0)
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
			else if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y > 0)
			{//W�������ꂽ�A��ړ�

				// �ړ����ɂ���
				m_sAllCharaMotironFrag.bMove = true;
				move.x += sinf(D3DX_PI * 0.0f + Camerarot.y) * fMove;
				move.z += cosf(D3DX_PI * 0.0f + Camerarot.y) * fMove;
				m_fRotDest = D3DX_PI * 1.0f + Camerarot.y;
			}
			else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y < 0)
			{//S�������ꂽ�A���ړ�

				// �ړ����ɂ���
				m_sAllCharaMotironFrag.bMove = true;
				move.x += sinf(D3DX_PI * 1.0f + Camerarot.y) * fMove;
				move.z += cosf(D3DX_PI * 1.0f + Camerarot.y) * fMove;
				m_fRotDest = D3DX_PI * 0.0f + Camerarot.y;
			}
			else
			{
				// �ړ������ǂ���
				m_sAllCharaMotironFrag.bMove = false;
			}

			if (m_bJump == false &&
				(pInputKeyboard->GetTrigger(DIK_SPACE) == true || pInputGamepad->GetTrigger(CInputGamepad::BUTTON_LB, m_nMyPlayerIdx)))
			{//SPACE�������ꂽ,�W�����v

				m_bJump = true;
				m_sAllCharaMotironFrag.bJump = true;
				move.y += 17.0f;

				// �T�E���h�Đ�
				CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_JUMP);
			}
		}
	}

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
		(bLandStage == false || bMove == true || m_bLandField == true || m_bJump == true || m_sAllCharaMotironFrag.bKnockBack == true || m_sAllCharaMotironFrag.bDead == true))
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
	//SetRotDest(m_fRotDest);

	if (CGame::GetGameManager()->IsControll())
	{// �s���ł���Ƃ�

		if (m_sAllCharaMotironFrag.bATK == false &&
			(pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, m_nMyPlayerIdx) || pInputKeyboard->GetTrigger(DIK_RETURN)))
		{// �U��

			// �U������ON
			m_sAllCharaMotironFrag.bJump = false;
			m_sAllCharaMotironFrag.bATK = true;
		}
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

	if (m_pMotion[nIdx]->IsFinish() == true)
	{// �I�����Ă�����

		// ���݂̎�ގ擾
		int nType = m_pMotion[nIdx]->GetType();
		int nOldType = m_pMotion[nIdx]->GetOldType();

		if (m_sMotionFrag[nIdx].bMove == true && m_sMotionFrag[nIdx].bATK == false && m_sMotionFrag[nIdx].bKnockBack == false && m_sMotionFrag[nIdx].bDead == false && m_bJump == false)
		{// �ړ����Ă�����


			// �ړ����[�V����
			m_pMotion[nIdx]->Set(MOTION_WALK);
		}
		else if (m_sMotionFrag[nIdx].bJump == true && m_sMotionFrag[nIdx].bATK == false && m_sMotionFrag[nIdx].bKnockBack == false && m_sMotionFrag[nIdx].bDead == false)
		{// �W�����v��

			// �W�����v�̃t���OOFF
			m_sMotionFrag[nIdx].bJump = false;

			// �W�����v���[�V����
			m_pMotion[nIdx]->Set(MOTION_JUMP);
		}
		else if (m_bJump == true && m_sMotionFrag[nIdx].bJump == false && m_sMotionFrag[nIdx].bATK == false && m_sMotionFrag[nIdx].bKnockBack == false && m_sMotionFrag[nIdx].bDead == false)
		{// �W�����v��&&�W�����v���[�V�������I����Ă鎞

			// �������[�V����
			m_pMotion[nIdx]->Set(MOTION_FALL);
		}
		else if (m_sMotionFrag[nIdx].bKnockBack == true)
		{// ���ꒆ��������

			// ���ꃂ�[�V����
			m_pMotion[nIdx]->Set(MOTION_KNOCKBACK);
		}
		else if (m_sMotionFrag[nIdx].bDead == true)
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
void CPlayerUnion::Atack(void)
{
	if (m_pMotion[PARTS_BODY] == NULL)
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
	CMotion::Info aInfo = m_pMotion[PARTS_BODY]->GetInfo(m_pMotion[PARTS_BODY]->GetType());

	// �U�����̑����擾
	int nNumAttackInfo = aInfo.nNumAttackInfo;

	for (int nCntAttack = 0; nCntAttack < nNumAttackInfo; nCntAttack++)
	{
		if (aInfo.AttackInfo[nCntAttack] == NULL)
		{// NULL��������
			continue;
		}

		if (m_pMotion[PARTS_BODY]->GetAllCount() == aInfo.AttackInfo[nCntAttack]->nInpactCnt)
		{// �Ռ��̃J�E���g�Ɠ����Ƃ�

			// ����̈ʒu
			D3DXVECTOR3 weponpos = m_pMotion[PARTS_BODY]->GetAttackPosition(m_pObjChara[PARTS_BODY]->GetModel(), *aInfo.AttackInfo[nCntAttack]);

			// ��ޕ�
			switch (m_pMotion[PARTS_BODY]->GetType())
			{
			case MOTION_ATK:
			case MOTION_ATK2:
				//// �p�[�e�B�N������
				//my_particle::Create(weponpos, my_particle::TYPE_SUPERATTACK);

				//// �`���[�W�J�E���g���Z�b�g
				////CGame::GetPowerGauge()->SetChargeCount(0);

				//// �Ռ��g����
				//CImpactWave::Create
				//(
				//	D3DXVECTOR3(pos.x, pos.y + 80.0f, pos.z),	// �ʒu
				//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// ����
				//	D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),			// �F
				//	100.0f,										// ��
				//	20.0f,										// ����
				//	20,											// ����
				//	28.0f,										// ���̈ړ���
				//	CImpactWave::TYPE_BLACK2,					// �e�N�X�`���^�C�v
				//	true										// ���Z�������邩
				//);

				//CImpactWave::Create
				//(
				//	D3DXVECTOR3(pos.x, pos.y + 150.0f, pos.z),	// �ʒu
				//	D3DXVECTOR3(0.0f, 0.0f, D3DX_PI),				// ����
				//	D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f),			// �F
				//	180.0f,										// ��
				//	150.0f,										// ����
				//	14,											// ����
				//	4.0f,										// ���̈ړ���
				//	CImpactWave::TYPE_GIZAWHITE,				// �e�N�X�`���^�C�v
				//	false										// ���Z�������邩
				//);

				// �U��
				//CManager::GetInstance()->GetCamera()->SetShake(20, 10.0f, 0.0f);

				// �a������
				//CSlash::Create
				//(
				//	D3DXVECTOR3(pos.x, pos.y + 50.0f, pos.z),	// �ʒu
				//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ����
				//	D3DXVECTOR3(m_fAtkStickRot, D3DX_PI + fRotY, 0.0f),		// ����
				//	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	// �F
				//	200.0f,								// ��
				//	50.0f,								// ���S����̊Ԋu
				//	10,									// ����
				//	40.0f,								// ���̈ړ���
				//	CImpactWave::TYPE_PURPLE4,			// �e�N�X�`���̎��
				//	true,								// ���Z�������邩�ǂ���
				//	GetMoveAngle()
				//);

				// ���s���Đ�
				CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_SWING);
				break;
			}
		}

		// ���[�V�����J�E���^�[�擾
		if (m_pMotion[PARTS_BODY]->GetAllCount() > aInfo.AttackInfo[nCntAttack]->nMinCnt && m_pMotion[PARTS_BODY]->GetAllCount() < aInfo.AttackInfo[nCntAttack]->nMaxCnt)
		{// �U�����蒆

			// ����̈ʒu
			D3DXVECTOR3 weponpos = m_pMotion[PARTS_BODY]->GetAttackPosition(m_pObjChara[PARTS_BODY]->GetModel(), *aInfo.AttackInfo[nCntAttack]);

			CEffect3D::Create(weponpos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), aInfo.AttackInfo[nCntAttack]->fRangeSize, 10, CEffect3D::MOVEEFFECT_NONE, CEffect3D::TYPE_NORMAL);

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

					if (ppEnemy[i]->Hit(aInfo.AttackInfo[nCntAttack]->nDamage) == true)
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
				float fRadius = pList->GetObjectChara()->RADIUS;

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
		"���[�V�����J�E���^�[�F%d\n", m_pMotion[PARTS_BODY]->GetAllCount());
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

				if ((m_sAllCharaMotironFrag.bKnockBack || m_bJump == true) && GetPosition().y >= fHeight)
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
				m_sAllCharaMotironFrag.bJump = false;
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

			if ((m_sAllCharaMotironFrag.bKnockBack || m_bJump == true) && GetPosition().y >= fHeight)
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
			m_sAllCharaMotironFrag.bJump = false;

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

	// ��
	float fLen = CGame::GetElevation()->GetWidthLen();
	int nBlock = CGame::GetElevation()->GetWidthBlock();
	nBlock /= 2;
	if (pos.x + RADIUS >= fLen * nBlock) { pos.x = fLen * nBlock - RADIUS; }
	if (pos.x - RADIUS <= -fLen * nBlock) { pos.x = -fLen * nBlock + RADIUS; }
	if (pos.z + RADIUS >= fLen * nBlock) { pos.z = fLen * nBlock - RADIUS; }
	if (pos.z - RADIUS <= -fLen * nBlock) { pos.z = -fLen * nBlock + RADIUS; }

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
			m_sAllCharaMotironFrag.bKnockBack = true;

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
		m_sAllCharaMotironFrag.bKnockBack = true;

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
		m_sAllCharaMotironFrag.bKnockBack = false;
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
		m_sAllCharaMotironFrag.bKnockBack = false;
		m_sAllCharaMotironFrag.bDead = true;
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
		m_sAllCharaMotironFrag.bKnockBack = false;
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


	// �ʒu�ݒ�
	SetPosition(pos);

	// �ړ��ʐݒ�
	SetMove(move);

	// �����ݒ�
	SetRotation(rot);
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

	m_pObjChara[PARTS_BODY]->Draw();		// ����
	m_pObjChara[PARTS_LEG]->Draw();		// �r
	m_pObjChara[PARTS_R_ARM]->Draw();	// �E�r
	m_pObjChara[PARTS_L_ARM]->Draw();	// ���r

	// HP�Q�[�W
	if (m_pHPGauge != NULL)
	{
		m_pHPGauge->Draw();
	}
}

//==========================================================================
// ��Ԏ擾
//==========================================================================
int CPlayerUnion::GetState(void)
{
	return m_state;
}