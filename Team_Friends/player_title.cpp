//=============================================================================
// 
//  �v���C���[���� [player_title.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "game.h"
#include "player_title.h"
#include "manager.h"
#include "debugproc.h"
#include "input.h"
#include "model.h"
#include "motion.h"
#include "objectChara.h"
#include "shadow.h"
#include "calculation.h"

//==========================================
//  �萔��` : �������
//==========================================
namespace
{
	// �t�@�C���p�X
	const char* CHARAFILE =
	{
		"data\\TEXT\\character\\player\\motion_player.txt"
	};

	const float DeadZone = 1.0f; // �ړI�n�Ƃ̌덷�͈�
}

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
int CPlayerTitle::m_nIdx = 0;

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CPlayerTitle::CPlayerTitle(int nPriority) : CPlayer(nPriority),
m_nModelType(NONE),
m_fSec(0.0f),
m_posTarget(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
	// �l�̃N���A
	
	// �C���f�b�N�X���L�^
	m_nMyPlayerIdx = m_nIdx;

	// �C���f�b�N�X�����Z
	++m_nIdx;
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CPlayerTitle::~CPlayerTitle()
{
	// �C���f�b�N�X�����Z
	--m_nIdx;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CPlayerTitle::Init(void)
{
	// ��ނ̐ݒ�
	SetType(TYPE_PLAYER);

	m_state = STATE_NONE;	// ���

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
	
	// ���f���̍����ւ�
	switch (m_nModelType)
	{
	case PLAYER_BODY:
		SetEvolusion(CGameManager::STATUS_LIFE, true);
		break;

	case PLAYER_ARM:
		SetEvolusion(CGameManager::STATUS_POWER, true);
		break;

	case PLAYER_LEG:
		SetEvolusion(CGameManager::STATUS_SPEED, true);
		break;

	default:
		break;
	}

	// �e�N�X�`����ݒ�
	BindByPlayerIdxTexture();

	// �|�[�Y�̃��Z�b�g
	m_pMotion->ResetPose(MOTION_DEF);

	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CPlayerTitle::Uninit(void)
{
	// �I������
	CPlayer::Uninit();
}

//==========================================================================
// �X�V����
//==========================================================================
void CPlayerTitle::Update(void)
{
	if (IsDeath() == true)
	{
		return;
	}

	// �ߋ��̈ʒu�ۑ�
	SetOldPosition(GetPosition());

	// ��]����
	Rotation();

	// �ړ�����
	Move();

	// ���[�V�����X�V
	if (m_pMotion != NULL)
	{
		m_pMotion->Update();
	}

	// �e�̈ʒu�X�V
	if (m_pShadow != NULL)
	{
		// �ʒu�擾
		D3DXVECTOR3 pos = GetPosition();

		m_pShadow->SetPosition(D3DXVECTOR3(pos.x, m_pShadow->GetPosition().y, pos.z));
	}

}

//==========================================================================
// �`�揈��
//==========================================================================
void CPlayerTitle::Draw(void)
{
	// �`�揈��
	CPlayer::Draw();
}

//==========================================
//  �ړI�n�̐ݒ�
//==========================================
void CPlayerTitle::SetTarget(const D3DXVECTOR3 start, const D3DXVECTOR3 end)
{
	// �ړI�n��ݒ�
	m_posTarget = end;

	// ���Ԃ����Z�b�g
	m_fSec = 0.0f;

	// �����n�_��ۑ�
	m_posDef = start;
}

//==========================================
//  �������� : �������
//==========================================
CPlayerTitle* CPlayerTitle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL type)
{
	// �C���X�^���X����
	CPlayerTitle* pPlayer = DEBUG_NEW CPlayerTitle;

	//���f����ݒ�
	pPlayer->m_nModelType = (int)type;

	// ����������
	pPlayer->Init();

	// �l��ۑ�
	pPlayer->SetPosition(pos);
	pPlayer->SetRotation(rot);
	pPlayer->SetTarget(pPlayer->GetPosition(), pPlayer->GetPosition());

	return pPlayer;
}

//==========================================
//  ��]
//==========================================
void CPlayerTitle::Rotation(void)
{
	// �ʒu�̎擾
	D3DXVECTOR3 diff = m_posTarget - GetPosition(); // �ړI�Ƃ̍���

	// �ړI�n�ւ̓��B�𔻒�
	if (fabsf(diff.x) <= DeadZone && fabsf(diff.y) <= DeadZone && fabsf(diff.z) <= DeadZone)
	{ // ���B���Ă����ꍇ

		// �ҋ@���[�V�����ɂ���
		m_pMotion->Set(CPlayer::MOTION_DEF);

		return;
	}

	// �ړ����[�V�����ɂ���
	m_pMotion->Set(CPlayer::MOTION_WALK);

	// �ړ��������Z�o
	D3DXVECTOR3 rotTarget = GetRotation();
	rotTarget.y = atan2f(diff.x, diff.z);

	// �p�x�̐��K��
	RotNormalize(rotTarget);

	// �ړI�̕����ƌ��݂̕����̍������Z�o
	D3DXVECTOR3 rot = GetRotation();
	D3DXVECTOR3 rotdiff = rotTarget - rot;

	// �p�x�̐��K��
	RotNormalize(rotdiff);

	// �����]�����x��␳
	rotdiff *= 0.1f;

	// �p�x�����Z
	rot += rotdiff;

	// �ړ�������K�p
	SetRotation(rot);
}

//==========================================
//  �ړ�
//==========================================
void CPlayerTitle::Move(void)
{
	// �ʒu�̎擾
	D3DXVECTOR3 diff = m_posTarget - GetPosition(); // �ړI�Ƃ̍���

	// �ړI�n�ւ̓��B�𔻒�
	if (fabsf(diff.x) <= DeadZone && fabsf(diff.y) <= DeadZone && fabsf(diff.z) <= DeadZone)
	{ // ���B���Ă����ꍇ
		return;
	}

	// ����̈ړ��ʂ��擾
	m_fSec += CManager::GetInstance()->GetDeltaTime();
	float velocity = EasingLinear(m_posDef.z, m_posTarget.z, m_fSec);

	// �ړ��ʂ�K�p
	if (m_posTarget.z == 300.0f)
	{
		SetPosition(m_posDef + D3DXVECTOR3(0.0f, 0.0f, velocity));
	}
	else
	{
		SetPosition(m_posDef - D3DXVECTOR3(0.0f, 0.0f, velocity));
	}

	CManager::GetInstance()->GetDebugProc()->Print("���ݒl : %f\n", GetPosition().z);
	CManager::GetInstance()->GetDebugProc()->Print("�����l : %f\n", m_posDef.z);
	CManager::GetInstance()->GetDebugProc()->Print("�ړI�l : %f\n", m_posTarget.z);
	CManager::GetInstance()->GetDebugProc()->Print("�ړ��l : %f\n", velocity);
}
