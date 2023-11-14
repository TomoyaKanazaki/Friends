//=============================================================================
// 
//  �v���C���[���� [player_smallunion.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "game.h"
#include "player_smallunion.h"
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
#include "player_union.h"


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
#define RADIUS			(250.0f)

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
const char *CPlayerSmallUnion::m_apModelFile[mylib_const::MAX_PLAYER] =	// ���f���̃t�@�C��
{
	"data\\TEXT\\player_union\\motion_body.txt",
	"data\\TEXT\\player_union\\motion_leg.txt",
};

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CPlayerSmallUnion::CPlayerSmallUnion(int nPriority) : CPlayerUnion(nPriority)
{
	
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CPlayerSmallUnion::~CPlayerSmallUnion()
{

}

//==========================================================================
// ����������
//==========================================================================
HRESULT CPlayerSmallUnion::Init(void)
{
	// ������
	CPlayerUnion::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_PLAYER);

	m_state = STATE_NONE;	// ���

	SetPosition(D3DXVECTOR3(-600.0f, 0.0f, -1000.0f));
	return S_OK;
}


//==========================================================================
// �p�[�c�̐ݒ�
//==========================================================================
HRESULT CPlayerSmallUnion::CreateParts(void)
{
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


	// ���r�̌��_��̂ɂ���
	m_pObjChara[PARTS_LEG]->GetModel()[0]->SetParent(m_pObjChara[PARTS_BODY]->GetModel()[0]);
	m_pObjChara[PARTS_LEG]->GetModel()[3]->SetParent(m_pObjChara[PARTS_BODY]->GetModel()[0]);
	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CPlayerSmallUnion::Uninit(void)
{
	// �I������
	CPlayerUnion::Uninit();
}

//==========================================================================
// �X�V����
//==========================================================================
void CPlayerSmallUnion::Update(void)
{
	CPlayerUnion::Update();
}

//==========================================================================
// �p�[�c�̃R���g���[������
//==========================================================================
void CPlayerSmallUnion::ControllParts(void)
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
void CPlayerSmallUnion::ControllBody(int nIdx)
{
	// �Q�[���p�b�h���擾
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

}

//==========================================================================
// �r����
//==========================================================================
void CPlayerSmallUnion::ControllLeg(int nIdx)
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

	if (m_state != STATE_DEAD &&
		m_state != STATE_FADEOUT)
	{// �ړ��\���[�V�����̎�

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

		// �ړ��ʐݒ�
		SetMove(move);
	}

}

//==========================================================================
// �E�r����
//==========================================================================
void CPlayerSmallUnion::ControllRightArm(int nIdx)
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
void CPlayerSmallUnion::ControllLeftArm(int nIdx)
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
// ���[�V�����̐ݒ�
//==========================================================================
void CPlayerSmallUnion::MotionSet(int nIdx)
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

		if (m_sMotionFrag[nIdx].bMove == true &&
			m_sMotionFrag[nIdx].bATK == false &&
			m_bKnockBack == false &&
			m_bDead == false &&
			m_sMotionFrag[nIdx].bCharge == false &&
			m_bJump == false)
		{// �ړ����Ă�����


			// �ړ����[�V����
			m_pMotion[nIdx]->Set(MOTION_WALK);
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
// �U��������
//==========================================================================
void CPlayerSmallUnion::AttackAction(int nIdx, int nModelNum, CMotion::AttackInfo ATKInfo)
{

	// ����̈ʒu
	D3DXVECTOR3 weponpos = m_pMotion[nIdx]->GetAttackPosition(m_pObjChara[nIdx]->GetModel(), ATKInfo);

	// ��ޕ�
	switch (m_pMotion[nIdx]->GetType())
	{
	case MOTION_ATK:
		
		break;
	}
}

//==========================================================================
// �q�b�g����
//==========================================================================
bool CPlayerSmallUnion::Hit(const int nValue)
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
// �`�揈��
//==========================================================================
void CPlayerSmallUnion::Draw(void)
{
	// �`�揈��
	CPlayerUnion::Draw();
}