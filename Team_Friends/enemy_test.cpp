//==========================================
//
//  �R�s�y�p�̓G(enemy_test.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_test.h"
#include "player.h"
#include "manager.h"
#include "debugproc.h"
#include "calculation.h"

//==========================================
//  �G�ɂ��Ă̐���
//==========================================
/*
	�����̃t�@�C���ɋL�q����Ă���R�[�h�͓G�𓮂����Œ���ł��B�����Ȃ��ł��������B��

	1.[ enemydata ]�t�H���_����[ manager.txt ]�Ɏg�p���������f���̃e�L�X�g�t�@�C����ǉ�����
	2.[ enemy.h ]��TYPE�񋓂ɐV�����^�C�v��ǉ�����
	3.[ enemydata ]�t�H���_����[ base.txt ]�Œǉ������^�C�v���Ăяo��
	4.���s�����炢��I�I�I
*/

//==========================================
//  �萔��`
//==========================================
namespace
{
	const float SEARCH_LENGTH = 500.0f;
	const float ATTACK_LENGTH = 50.0f;
	const float SPIN_ROTATION = 0.03f;
}

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemyTest::CEnemyTest(int nPriority) :
	m_Act(ACTION_DEF),
	m_posDefault(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemyTest::~CEnemyTest()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemyTest::Init(void)
{
	//����������
	CEnemy::Init();

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CEnemyTest::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemyTest::Update(void)
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
	case CEnemyTest::ACTION_RETURN:

		// �����ʒu������
		RotationDefault();

		break;

	case CEnemyTest::ACTION_ATTACK:

		// �v���C���[������
		RotationPlayer();

		break;

	case CEnemyTest::ACTION_SEARCH:

		// ���邭�邷��
		SpinRotation();

		break;

	case CEnemyTest::ACTION_CHASE:

		// �v���C���[������
		RotationPlayer();

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
void CEnemyTest::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//==========================================
//  �E��
//==========================================
void CEnemyTest::Kill(void)
{
	// ���S����
	CEnemy::Kill();
}

//==========================================
//  ���[�V�����Z�b�g
//==========================================
void CEnemyTest::MotionSet(void)
{
	if (m_pMotion->IsFinish() == true)
	{// �I�����Ă�����

		// ���݂̎�ގ擾
		int nType = m_pMotion->GetType();

		if (m_sMotionFrag.bMove == true && m_sMotionFrag.bKnockback == false)
		{// �ړ����Ă�����

			m_sMotionFrag.bMove = false;	// �ړ�����OFF

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
//  �����ʒu�̐ݒ�
//==========================================
void CEnemyTest::SetDefaultPos(const D3DXVECTOR3 pos)
{
	//���l��ݒ�
	m_posDefault = pos;
}

//==========================================
//  �s���ݒ�
//==========================================
void CEnemyTest::ActionSet(void)
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
	else if (CalcLenPlayer(SEARCH_LENGTH))
	{
		// �������߂��ƒǐՏ�ԂɂȂ�
		m_Act = ACTION_CHASE;
	}
	else if(CalcLenDefault())
	{
		// �v���C���[���߂��ɂ��Ȃ������猳�̈ʒu�ɋA��
		m_Act = ACTION_RETURN;
	}
	else // ��L�ȊO�Ȃ�ҋ@���
	{
		m_Act = ACTION_DEF;
	}
}

//==========================================
//  ���̏�ŉ�]���鏈��
//==========================================
void CEnemyTest::SpinRotation(void)
{
	// �p�x���擾
	D3DXVECTOR3 rot = GetRotation();

	// �ڕW�Ƃ̍���
	float fRotDiff = rot.y + SPIN_ROTATION;

	//�p�x�̐��K��
	RotNormalize(fRotDiff);

	//�p�x�̕␳������
	rot.y += fRotDiff * 0.025f;

	// �p�x�̐��K��
	RotNormalize(rot.y);

	// �����ݒ�
	SetRotation(rot);
}

//==========================================
//  �����ʒu����������
//==========================================
void CEnemyTest::RotationDefault(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();

	// �ڕW�̊p�x�����߂�
	float fRotDest = atan2f((pos.x - m_posDefault.x), (pos.z - m_posDefault.z));

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
//  �����ʒu�ɖ߂鏈��
//==========================================
bool CEnemyTest::CalcLenDefault(void)
{
	// ��_�Ԃ��q���x�N�g���̎Z�o
	D3DXVECTOR3 vecToPlayer = GetPosition() - m_posDefault;

	// �x�N�g���̑傫����2����Z�o
	float fLength = vecToPlayer.x * vecToPlayer.x + vecToPlayer.z * vecToPlayer.z;

	// ���͈͓��̔���
	if (SEARCH_LENGTH * SEARCH_LENGTH >= fLength)
	{
		return false;
	}

	return true;
}

//==========================================
//  �v���C���[����������
//==========================================
void CEnemyTest::RotationPlayer(void)
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
bool CEnemyTest::CalcLenPlayer(float fLen)
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
