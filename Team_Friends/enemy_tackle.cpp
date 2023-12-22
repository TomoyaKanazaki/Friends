//==========================================
//
//  �ˌ��G(enemy_tackle.cpp)
//  Author : Kai Takada
//
//==========================================
#include "enemy_tackle.h"
#include "player.h"
#include "manager.h"
#include "debugproc.h"
#include "calculation.h"
#include "hp_gauge.h"
#include "bullet.h"
#include "collisionobject.h"
#include "model.h"
#include "particle.h"
#include "3D_Effect.h"
#include "game.h"
#include "tutorial.h"
#include "tutorialmanager.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const float SEARCH_LENGTH = 400.0f;		//���G����
	const float ATTACK_LENGTH = 200.0f;		//�U������
	const float MOVE_SPEED = 1.0f;			//�p�j�����x
	const float ATTACK_SPEED = 10.0f;		//�ˌ����x
	const float ATTACK_TIME = 1.0f;			//�ˌ�����
	const float SEARCH_ROT = 0.785f;		//���ʂ���̍��G�͈�(�v�Z�ɕύX)
	const float AFTER_FIXROT = 0.07f;		//�d�����̕����C�����x
	const float FIXROT_GRACE = 0.5f;		//�����C���܂ł̗P�\
	const float ROAM_CHANGE_ROT = 3.0f;		//�p�j���̕����]���^�C�~���O
	const float TIME_ROMINGSMOKE = (1.0f / (60.0f / (float)4));	// �p�j���̉�
	const float TIME_TACKLEFIRE = (1.0f / (60.0f / (float)1));	// �^�b�N�����̉�
	const int ATTACK = 1;		//�U����
	const int FIXROT = 16;		//�����]���̕Е���
}

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemyTackle::CEnemyTackle(int nPriority) :
	m_Act(ACTION_ROAMING),
	m_fActionCount(0.0f),
	m_moveLock(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_fRotLock(0.0f),
	m_fEmissionTime(0.0f),
	m_nAttack(0)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemyTackle::~CEnemyTackle()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemyTackle::Init(void)
{
	//����������
	CEnemy::Init();

	// HP�̐ݒ�
	m_pHPGauge = CHP_Gauge::Create(100.0f, GetLifeOrigin());

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CEnemyTackle::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemyTackle::Update(void)
{
	// ���S�̔���
	if (IsDeath() == true)
	{// ���S�t���O�������Ă�����
		return;
	}

	// �X�V����
	CEnemy::Update();

	if (IsDeath() == true)
	{// ���S�t���O�������Ă�����
		return;
	}

	if (CManager::GetInstance()->GetScene()->GetMode() == CScene::MODE_TUTORIAL)
	{
		if (!CTutorial::GetTutorialManager()->IsControll())
		{// �s���ł���Ƃ�
			return;
		}
	}
	else
	{
		if (!CGame::GetGameManager()->IsControll())
		{// �s���ł���Ƃ�
			return;
		}
	}

	// �������̃^�C�}�[���Z
	m_fEmissionTime += CManager::GetInstance()->GetDeltaTime();

	// ���[�V�����̏��擾
	if (m_pMotion != NULL)
	{
		CMotion::Info aInfo = m_pMotion->GetInfo(0);

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
			pEffect->UpdatePosition(GetRotation());
			nCntEffect++;
			if (nNumEffect <= nCntEffect)
			{
				break;
			}
		}
	}
}

//==========================================
// �s���X�V
//==========================================
void CEnemyTackle::UpdateAction(void)
{
	if (m_state == STATE_DEAD ||
		m_state == STATE_FADEOUT)
	{
		return;
	}

	D3DXVECTOR3 pos = GetPosition();

	// �s�����Ƃ̍s��
	switch (m_Act)
	{
	case CEnemyTackle::ACTION_ROAMING:

		//�ړ�
		Roaming();

		break;

	case CEnemyTackle::ACTION_READY:

		// �ړ��ʂ�ݒ�
		RotationPlayer();

		break;

	case CEnemyTackle::ACTION_ATTACK:

#if _DEBUG
		my_particle::Create(pos, my_particle::TYPE_CHECK);
#endif

		// �U��
		Attack();

		break;

	case CEnemyTackle::ACTION_AFTER:

		if (m_fActionCount > FIXROT_GRACE)
		{//�P�\���߂���������]��
			FixRotation();
		}

		break;

	default:
		break;
	}

	// �J�E���^�[�����Z
	m_fActionCount += CManager::GetInstance()->GetDeltaTime();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemyTackle::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//==========================================
//  �E��
//==========================================
void CEnemyTackle::Kill(void)
{
	// ���S����
	CEnemy::Kill();
}

//==========================================
//  ���[�V�����Z�b�g
//==========================================
void CEnemyTackle::MotionSet(void)
{
	if (m_pMotion->IsFinish() == true)
	{// �I�����Ă�����

		// ���݂̎�ގ擾
		int nType = m_pMotion->GetType();

		if (m_sMotionFrag.bMove == true && m_sMotionFrag.bKnockback == false && m_sMotionFrag.bATK == false)
		{// �ړ����Ă�����

			// �ړ����[�V����
			m_pMotion->Set(MOTION_WALK);
		}
		else if (m_sMotionFrag.bKnockback == true)
		{// ���ꒆ��������

			// ���ꃂ�[�V����
			m_pMotion->Set(MOTION_KNOCKBACK);
		}
		else if (m_sMotionFrag.bATK == true)
		{// �U�����Ă�����

			m_sMotionFrag.bATK = false;		// �U������OFF

			// �U�����[�V����
			m_pMotion->Set(MOTION_ATK);
		}
		else
		{
			// �j���[�g�������[�V����
			m_pMotion->Set(MOTION_DEF);
		}
	}
}

//==========================================
//  �s���ݒ�
//==========================================
void CEnemyTackle::ActionSet(void)
{
	switch (m_Act)
	{
	case CEnemyTackle::ACTION_ROAMING:

		if (SearchPlayer(SEARCH_LENGTH))
		{// ���G

		 // �������߂��ƍU����ԂɂȂ�
			m_Act = ACTION_READY;
			m_fActionCount = 0.0f;
			m_pMotion->Set(MOTION_READY);
		}

		break;

	case CEnemyTackle::ACTION_READY:

		if (m_pMotion->IsFinish() == true)
		{//���[�V�������I�������(�I���Ȃ�)
			m_Act = ACTION_ATTACK;
			m_fActionCount = 0.0f;
			m_pMotion->Set(MOTION_ATK);
		}

		break;

	case CEnemyTackle::ACTION_ATTACK:
		
		if (m_fActionCount >= ATTACK_TIME)
		{
			m_Act = ACTION_AFTER;
			m_fActionCount = 0.0f;
			m_moveLock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		
		break;

	case CEnemyTackle::ACTION_AFTER:

		if (m_pMotion->IsFinish() == true)
		{//���[�V�������I�������(�I���Ȃ�)
			m_Act = ACTION_ROAMING;
			m_fActionCount = 0.0f;
			m_pMotion->Set(MOTION_AFTER);
		}

		break;

	default:
		break;
	}
}

//==========================================
//  �U��
//==========================================
void CEnemyTackle::Attack(void)
{
	m_sMotionFrag.bATK = true;

	// �U�����[�V�����ݒ�
	m_pMotion->Set(MOTION_ATK);

	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 pos = GetPosition();//���Q�[�����

	if (m_fEmissionTime >= TIME_TACKLEFIRE)
	{
		m_fEmissionTime = 0.0f;
	}

	if (m_fEmissionTime == 0.0f)
	{
		// ���[�V�����̏��擾
		CMotion::Info aInfo = m_pMotion->GetInfo(0);
		D3DXVECTOR3 rot = GetRotation();

		// �U�����̑����擾
		int nNumAttackInfo = aInfo.nNumAttackInfo;

		CEffect3D *pEffect = NULL;
		// ����̈ʒu
		for (int nCntAttack = 0; nCntAttack < nNumAttackInfo; nCntAttack++)
		{
			D3DXVECTOR3 weponpos = m_pMotion->GetAttackPosition(GetModel(), *aInfo.AttackInfo[nCntAttack]);

			// ��
			float fMove = 7.5f + Random(-20, 20) * 0.1f;
			fMove *= -1;
			float fRot = Random(-20, 20) * 0.01f;

			pEffect = CEffect3D::Create(
				weponpos,
				D3DXVECTOR3(
					sinf(D3DX_PI + rot.y + fRot) * fMove,
					Random(-10, 10) * 0.1f,
					cosf(D3DX_PI + rot.y + fRot) * fMove),
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
					sinf(D3DX_PI + rot.y + fRot) * fMove,
					Random(-10, 10) * 0.1f,
					cosf(D3DX_PI + rot.y + fRot) * fMove),
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

	if (m_moveLock == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		m_sMotionFrag.bATK = true;

		// �v���C���[���
		CPlayer* pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(m_nTargetPlayerIndex);
		if (pPlayer == NULL)
		{
			return;
		}

		// ���擾
		D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 rot = GetRotation();

		//�U������A����

		// �v���C���[���玩�g�Ɍ������x�N�g�����Z�o
		D3DXVECTOR3 vecToPlayer = posPlayer - pos;

		// �x�N�g���̐��K��
		vecToPlayer.y = 0.0f;
		D3DXVec3Normalize(&vecToPlayer, &vecToPlayer);
		vecToPlayer *= ATTACK_SPEED;

		//�p�x�𔽓]
		m_fRotLock = GetRotation().y + D3DX_PI;
		RotNormalize(m_fRotLock);
		SetRotDest(m_fRotLock);

		// �ړ��ʂ̐ݒ�
		move.x = sinf(rot.y + D3DX_PI) * ATTACK_SPEED;
		move.z = cosf(rot.y + D3DX_PI) * ATTACK_SPEED;
		SetMove(move);

		m_moveLock = move;

		return;
	}

	m_moveLock.y = move.y;
	SetMove(m_moveLock);
}

//==========================================
//�@��������ړ��ʂ�ݒ�
//==========================================
void CEnemyTackle::SetMoveRotation(void)
{
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 rot = GetRotation();

	// �ړ����x�擾
	float fMove = GetVelocity();

	move.x = sinf(rot.y) * fMove * ATTACK_SPEED;
	move.z = cosf(rot.y) * fMove * ATTACK_SPEED;
	SetMove(move);
}

//==========================================
//  �v���C���[��T������
//==========================================
bool CEnemyTackle::SearchPlayer(float fLen)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();
	D3DXVECTOR3 posL = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���G��̍��_
	D3DXVECTOR3 posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���G��̉E�_

	float fRot = SEARCH_ROT;

	posL.x = pos.x + sinf(rot.y + fRot) * SEARCH_LENGTH;
	posL.z = pos.z + cosf(rot.y + fRot) * SEARCH_LENGTH;
	posR.x = pos.x + sinf(rot.y + -fRot) * SEARCH_LENGTH;
	posR.z = pos.z + cosf(rot.y + -fRot) * SEARCH_LENGTH;

	// �v���C���[���
	CPlayer* pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(m_nTargetPlayerIndex);
	if (pPlayer == NULL)
	{
		return false;
	}

	// �v���C���[�̈ʒu�擾
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

	// ���͈͓��̔���
	if (CollisionFan(pos, posL, posR, posPlayer, fRot))
	{
		return true;
	}

	return false;
}

//==========================================
// �w������Ɍ���
//==========================================
void CEnemyTackle::FixRotation(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();
	float fRotDest = GetRotDest();

	// �ڕW�Ƃ̍���
	float fRotDiff = fRotDest - rot.y;

	//�p�x�̐��K��
	RotNormalize(fRotDiff);

	//�p�x�̕␳������
	rot.y += fRotDiff * AFTER_FIXROT;

	// �p�x�̐��K��
	RotNormalize(rot.y);

	// �����ݒ�
	SetRotation(rot);
}

//==========================================
// �p�j
//==========================================
void CEnemyTackle::Roaming(void)
{
	D3DXVECTOR3 rot = GetRotation();
	float fRotDest = GetRotDest();
	D3DXVECTOR3 move = GetMove();

	//���J�E���g�Ń����_����rot�ύX
	if (int(m_fActionCount * 100) % int(ROAM_CHANGE_ROT * 100) == 0)
	{
		float fRotDiff = (Random(-FIXROT, FIXROT) / 1.0f);
		RotNormalize(fRotDiff);
		rot.y += fRotDiff;
		RotNormalize(rot.y);
		SetRotDest(rot.y);

		m_fActionCount = 0.0f;
	}

	if (rot.y - fRotDest > -0.1f && rot.y - fRotDest < 0.1f)
	{//���炩���������ڕW������������
		//�ړ�
		move.x = sinf(rot.y + D3DX_PI) * MOVE_SPEED;
		move.z = cosf(rot.y + D3DX_PI) * MOVE_SPEED;
		SetMove(move);
	}
	else
	{
		FixRotation();
	}

	if (m_fEmissionTime >= TIME_ROMINGSMOKE)
	{
		m_fEmissionTime = 0.0f;
	}
	if (m_fEmissionTime == 0.0f)
	{
		// ���[�V�����̏��擾
		CMotion::Info aInfo = m_pMotion->GetInfo(0);
		D3DXVECTOR3 rot = GetRotation();

		// �U�����̑����擾
		int nNumAttackInfo = aInfo.nNumAttackInfo;

		CEffect3D *pEffect = NULL;
		// ����̈ʒu
		for (int nCntAttack = 0; nCntAttack < nNumAttackInfo; nCntAttack++)
		{
			D3DXVECTOR3 weponpos = m_pMotion->GetAttackPosition(GetModel(), *aInfo.AttackInfo[nCntAttack]);

			// ��
			float fMove = 5.5f + Random(-20, 20) * 0.1f;
			fMove *= -1;
			float fRot = Random(-20, 20) * 0.01f;

			pEffect = CEffect3D::Create(
				weponpos,
				D3DXVECTOR3(
					sinf(D3DX_PI + rot.y + fRot) * fMove,
					Random(-10, 10) * 0.1f,
					cosf(D3DX_PI + rot.y + fRot) * fMove),
				D3DXCOLOR(0.4f + Random(-10, 0) * 0.01f, 0.4f + Random(-10, 0) * 0.01f, 0.4f + Random(-10, 0) * 0.01f, 1.0f),
				30.0f + (float)Random(-10, 10),
				15,
				CEffect3D::MOVEEFFECT_ADD,
				CEffect3D::TYPE_SMOKEBLACK);

			if (pEffect != NULL)
			{
				// �Z�b�g�A�b�v�ʒu�ݒ�
				pEffect->SetUp(aInfo.AttackInfo[nCntAttack]->Offset, GetModel()[aInfo.AttackInfo[nCntAttack]->nCollisionNum]->GetPtrWorldMtx(), CObject::GetObject(), SetEffectParent(pEffect));
			}
		}
	}
}

//==========================================================================
// �v���C���[����������
//==========================================================================
void CEnemyTackle::RotationPlayer(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();

	// �v���C���[���
	CPlayer* pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(m_nTargetPlayerIndex);
	if (pPlayer == NULL)
	{
		return;
	}

	// �v���C���[�̈ʒu�擾
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

	// �ڕW�̊p�x�����߂�
	float fRotDest = atan2f((pos.x - posPlayer.x), (pos.z - posPlayer.z));

	// �ڕW�Ƃ̍���
	float fRotDiff = fRotDest - rot.y;

	//�p�x�̐��K��
	RotNormalize(fRotDiff);

	//�p�x�̕␳������
	if (fabsf(fRotDiff) > 0.1f)
	{
		rot.y += fRotDiff * 0.05f;
	}
	else
	{
		rot.y += fRotDiff * 1.0f;
	}

	// �p�x�̐��K��
	RotNormalize(rot.y);

	// �����ݒ�
	SetRotation(rot);

	// �ڕW�̌����ݒ�
	SetRotDest(fRotDest);
}
