//=============================================================================
// 
//  �`���[�g���A���v���C���[���� [tutorialplayer.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "tutorial.h"
#include "tutorialplayer.h"
#include "tutorialstep.h"
#include "camera.h"
#include "manager.h"
#include "debugproc.h"
#include "renderer.h"
#include "input.h"
#include "motion.h"
#include "sound.h"
#include "particle.h"
#include "scene.h"
#include "calculation.h"
#include "model.h"
#include "3D_effect.h"
#include "shadow.h"

//==========================================================================
// �}�N����`
//==========================================================================

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CTutorialPlayer::CTutorialPlayer(int nPriority) : CPlayer(nPriority)
{
	// �l�̃N���A
	
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CTutorialPlayer::~CTutorialPlayer()
{

}

//==========================================================================
// ����������
//==========================================================================
HRESULT CTutorialPlayer::Init(void)
{
	// �e�̏���������
	CPlayer::Init();

	return S_OK;
}

//==========================================================================
// ���[�h�ʏI������
//==========================================================================
void CTutorialPlayer::UninitByMode(void)
{
	CScene *pScene = CManager::GetInstance()->GetScene();

	if (pScene != nullptr)
	{
		CPlayer **ppPlayer = pScene->GetPlayer();

		// �v���C���[��NULL
		*ppPlayer = nullptr;
	}
}

//==========================================================================
// �X�V����
//==========================================================================
void CTutorialPlayer::Update(void)
{
	// ���S�̔���
	if (IsDeath() == true)
	{// ���S�t���O�������Ă�����
		return;
	}

	// �e�̍X�V����(enemymanager���̊֌W�ŕs�g�p)
	//CPlayer::Update();

	Controll();

	// ���S�̔���
	if (IsDeath() == true)
	{// ���S�t���O�������Ă�����
		return;
	}

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

	//// �R���{���o���͔�����
	//if (CTutorial::GetEnemyManager()->GetState() == CEnemyManager::STATE_COMBOANIM)
	//{
	//	return;
	//}

	// �ߋ��̈ʒu�ۑ�
	SetOldPosition(GetPosition());

	// ���[�V�����̐ݒ菈��
	//MotionSet();

	// ���[�V�����X�V
	if (m_pMotion != nullptr)
	{
		m_pMotion->Update(GetStatus().fSpeedBuff);
	}

	//// �U������
	//Atack();

	//// ��ԍX�V
	//UpdateState();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 posCenter = GetCenterPosition();

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// �����擾
	D3DXVECTOR3 rot = GetRotation();

	//// �Ǐ]�ڕW�̏��ݒ�
	//if (m_nChaseTopIdx == m_nMyPlayerIdx)
	//{
	//	// �J�����̏��擾
	//	CCamera *pCamera = CManager::GetInstance()->GetCamera();
	//	pCamera->SetTargetPosition(pos);
	//	pCamera->SetTargetRotation(rot);
	//}

	// �e�̈ʒu�X�V
	if (m_pShadow != nullptr)
	{
		m_pShadow->SetPosition(D3DXVECTOR3(pos.x, m_pShadow->GetPosition().y, pos.z));
	}

	// ���[�V�����̏��擾
	if (m_pMotion != nullptr)
	{
		CMotion::Info aInfo = m_pMotion->GetInfo(MOTION_WALK);

		// �U�����̑����擾
		int nNumAttackInfo = aInfo.nNumAttackInfo;

		int nCntEffect = 0;
		int nNumEffect = GetEffectParentNum();
		for (int i = 0; i < mylib_const::MAX_OBJ; i++)
		{
			CEffect3D *pEffect = GetEffectParent(i);
			if (pEffect == nullptr)
			{// nullptr��������
				continue;
			}

			// �G�t�F�N�g�̈ʒu�X�V
			pEffect->UpdatePosition(GetRotation());
			nCntEffect++;
			if (nNumEffect <= nCntEffect)
			{
				break;
			}
		}
	}

	// �X�e�b�v���Ƃ̍X�V
	UpdateByStep();

#if 1
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
// �X�e�b�v���Ƃ̍X�V����
//==========================================================================
void CTutorialPlayer::UpdateByStep(void)
{
	// �X�e�b�v�̐ݒ�
	CTutorial::GetStep()->SetStep(CTutorialStep::STEP_WAIT);
}

//==========================================================================
// ���쏈��
//==========================================================================
void CTutorialPlayer::Controll(void)
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
	float fMove = GetVelocity() * GetStatus().fSpeedBuff;

	// �o�ߎ��Ԏ擾
	float fCurrentTime = CManager::GetInstance()->GetDeltaTime();

	// �X�e�b�v��i�߂�
	//CTutorial::GetStep()->SetStep(CTutorialStep::STEP_WAIT);

	if (true)
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
		m_state != STATE_RELEASEUNION &&
		CManager::GetInstance()->GetByPlayerPartsType(m_nMyPlayerIdx) != CGameManager::STATUS_SPEED)
	{// �ړ���
		m_nCntWalk = (m_nCntWalk + 1) % 4;

		if (m_nCntWalk == 0)
		{
			// ���[�V�����̏��擾
			CMotion::Info aInfo = m_pMotion->GetInfo(MOTION_WALK);

			// �U�����̑����擾
			int nNumAttackInfo = aInfo.nNumAttackInfo;

			CEffect3D *pEffect = nullptr;
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

				if (pEffect != nullptr)
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
				if (pEffect != nullptr)
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
	//m_bLandInjectionTable[m_nMyPlayerIdx] = false;

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

	if (m_state != STATE_DEAD &&
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
			/*m_nCntInputAtk = INTERVAL_ATK;*/
		}
	}


//#if _DEBUG
//	static CGameManager::eStatus s_statusType;
//	if (pInputKeyboard->GetTrigger(DIK_RIGHT) == true)
//	{// ���L�[�������ꂽ,���ړ�
//		s_statusType = (CGameManager::eStatus)(((int)s_statusType + 1) % (int)CGameManager::STATUS_MAX);
//		SetEvolusion(s_statusType, true);
//	}
//
//	if (pInputKeyboard->GetPress(DIK_UP) == true)
//	{// SPACE�������ꂽ,�W�����v
//
//	 // �A�C�e���h���b�v
//		CItem::Create(D3DXVECTOR3(pos.x, pos.y + 100.0f, pos.z), D3DXVECTOR3(0.0f, Random(-31, 31) * 0.1f, 0.0f));
//	}
//#endif
//
//	if (pInputKeyboard->GetTrigger(DIK_LEFT) == true)
//	{
//		CCollisionObject::Create(GetPosition(), mylib_const::DEFAULT_VECTOR3, 10000.0f, 3, 10000, CCollisionObject::TAG_PLAYER);
//	}
}