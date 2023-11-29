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

//==========================================
//  �萔��`
//==========================================
namespace
{
	const float SEARCH_LENGTH = 400.0f;
	const float ATTACK_LENGTH = 200.0f;
	const float MOVE_SPEED = 0.01f;
	const float MOVE_X = 2.0f;
	const float MOVE_Z = 2.0f;
}

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemyTackle::CEnemyTackle(int nPriority) :
	m_Act(ACTION_ROAMING),
	m_fMoveCount(0.0f)
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

	// �s�����Ƃ̍s��
	switch (m_Act)
	{
	case CEnemyTackle::ACTION_ROAMING:

		// �ړ�
		Move();

		break;

	case CEnemyTackle::ACTION_ATTACK:

		// �v���C���[������
		RotationPlayer();

		// �U��
		Attack();

		break;

	default:
		break;
	}

	// �s����Ԃ̍X�V
	ActionSet();

	// ���[�V�����̍X�V
	MotionSet();
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

		if (m_sMotionFrag.bMove == true && m_sMotionFrag.bKnockback == false)
		{// �ړ����Ă�����
			// �U�����Ă��Ȃ�
			m_sMotionFrag.bATK = false;

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
	if (CalcLenPlayer(ATTACK_LENGTH))
	{
		// �U���t���O�𗧂Ă�
		if (m_Act != ACTION_ATTACK)
		{
			m_sMotionFrag.bATK = true;
		}

		// �������߂��ƍU����ԂɂȂ�
		m_Act = ACTION_ATTACK;
	}
	else // ��L�ȊO�Ȃ�ҋ@���
	{
		m_Act = ACTION_ROAMING;
	}
}

//==========================================
//  �ړ�
//==========================================
void CEnemyTackle::Move(void)
{
	// �ړ��t���O�𗧂Ă�
	m_sMotionFrag.bMove = true;

	// �ړ��J�E���^�[�����Z
	m_fMoveCount += MOVE_SPEED;

	// �ړ��ʂ�K�p
	D3DXVECTOR3 move = GetMove();
	move.x = sinf(m_fMoveCount) * MOVE_X;
	move.z = cosf(m_fMoveCount) * MOVE_Z;
	SetMove(move);

	// �����]��
	MoveRotation();
}

//==========================================
//  �ړ���������������
//==========================================
void CEnemyTackle::MoveRotation(void)
{
	// �K�v�Ȓl���擾
	D3DXVECTOR3 rot = GetRotation();
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 posDest = pos + move;
	D3DXVECTOR3 posDiff = posDest - pos;

	// �������Z�o
	float fRot = atan2f(-posDiff.x, -posDiff.z);

	//�p�x�̐��K��
	RotNormalize(fRot);

	//�p�x�̕␳������
	rot.y = fRot;

	// �����ݒ�
	SetRotation(rot);
}

//==========================================
//  �U��
//==========================================
void CEnemyTackle::Attack(void)
{
	// �U������
	CEnemy::StateAttack();

	// ���[�V�����̏��擾
	CMotion::Info aInfo = m_pMotion->GetInfo(m_pMotion->GetType());

	// �U�����̑����擾
	int nNumAttackInfo = aInfo.nNumAttackInfo;

	bool bAtkWait = true;	// �U���ҋ@��
	for (int nCntAttack = 0; nCntAttack < nNumAttackInfo; nCntAttack++)
	{
		if (aInfo.AttackInfo[nCntAttack] == NULL)
		{// NULL��������
			continue;
		}

		// ���[�V�����J�E���^�[�擾
		if (m_pMotion->GetAllCount() > aInfo.AttackInfo[nCntAttack]->nMinCnt)
		{// �U�����蒆
			// �U�����蒆�ɂ���
			bAtkWait = false;
		}
	}

	if (bAtkWait == false)
	{// ���蒆�̎�
		return;
	}
}

//==========================================
//  �v���C���[����������
//==========================================
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
	rot.y += fRotDiff * 0.025f;

	// �p�x�̐��K��
	RotNormalize(rot.y);

	// �����ݒ�
	SetRotation(rot);

	// �ڕW�̌����ݒ�
	SetRotDest(fRotDest);
}

//==========================================
//  �v���C���[�Ƃ̋����𔻒�
//==========================================
bool CEnemyTackle::CalcLenPlayer(float fLen)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �v���C���[���
	CPlayer* pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(m_nTargetPlayerIndex);
	if (pPlayer == NULL)
	{
		return false;
	}

	// �v���C���[�̈ʒu�擾
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

	// ��_�Ԃ��q���x�N�g���̎Z�o
	D3DXVECTOR3 vecToPlayer = pos - posPlayer;

	// �x�N�g���̑傫����2����Z�o
	float fLength = vecToPlayer.x * vecToPlayer.x + vecToPlayer.z * vecToPlayer.z;

	// ���͈͓��̔���
	if (fLen * fLen >= fLength)
	{
		return true;
	}

	return false;
}
