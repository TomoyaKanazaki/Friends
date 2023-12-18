//=============================================================================
// 
// �����蔻��I�u�W�F�N�g���� [collisionobject.cpp]
// Author : ���n�Ή�
// 
//=============================================================================
#include "collisionobject.h"
#include "renderer.h"
#include "texture.h"
#include "manager.h"
#include "game.h"
#include "enemy.h"
#include "enemymanager.h"
#include "player.h"
#include "calculation.h"

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
int CCollisionObject::m_nIdxTex = 0;	// �e�N�X�`���̃C���f�b�N�X�ԍ�

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CCollisionObject::CCollisionObject(int nPriority) : CObjectBillboard(nPriority)
{
	// �l�̃N���A
	m_fRadius = 0.0f;	// ���a
	m_nDamage = 0;		// �_���[�W
	m_nLife = 0;		// ����
	m_nMaxLife = 0;		// �ő����(�Œ�)
	m_MyTag = TAG_NONE;			// �����̃^�O
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CCollisionObject::~CCollisionObject()
{
	
}

//==========================================================================
// ��������
//==========================================================================
CCollisionObject *CCollisionObject::Create(void)
{
	// �����p�̃I�u�W�F�N�g
	CCollisionObject *pEffect = NULL;

	if (pEffect == NULL)
	{// NULL��������

		// �������̊m��
		pEffect = DEBUG_NEW CCollisionObject;

		if (pEffect != NULL)
		{// �������̊m�ۂ��o���Ă�����

			// ����������
			pEffect->Init();
		}

		return pEffect;
	}

	return NULL;
}

//==========================================================================
// ��������
//==========================================================================
CCollisionObject *CCollisionObject::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fRadius, const int nLife, const int nDamage, eMyTag tag)
{
	// �����p�̃I�u�W�F�N�g
	CCollisionObject *pEffect = NULL;

	if (pEffect == NULL)
	{// NULL��������

		// �������̊m��
		pEffect = DEBUG_NEW CCollisionObject;

		if (pEffect != NULL)
		{// �������̊m�ۂ��o���Ă�����

			pEffect->SetPosition(pos);
			pEffect->SetMove(move);
			pEffect->m_nDamage = nDamage;	// �_���[�W
			pEffect->m_MyTag = tag;			// ���
			pEffect->m_fRadius = fRadius;
			pEffect->SetSize(D3DXVECTOR2(fRadius, fRadius));
			pEffect->m_nLife = nLife;

			// ����������
			HRESULT hr = pEffect->Init();
			if (FAILED(hr))
			{
				return NULL;
			}
		}

		return pEffect;
	}

	return NULL;
}

//==================================================================================
// ����������
//==================================================================================
HRESULT CCollisionObject::Init(void)
{
	HRESULT hr;

	// �e��ϐ��̏�����
	m_nMaxLife = m_nLife;						// �ő����(�Œ�)

	// ��ނ̐ݒ�
	SetType(TYPE_EFFECT3D);

#if 0
	if (m_nIdxTex == 0)
	{
		m_nIdxTex = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\effect\\effect000.jpg");
	}

	// �e�N�X�`���̊��蓖��
	BindTexture(m_nIdxTex);
#endif

	// ����������
	hr = CObjectBillboard::Init();
	if (FAILED(hr))
	{// ���s�����Ƃ�
		Uninit();
		return E_FAIL;
	}

	SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	return S_OK;
}

//==================================================================================
// �I������
//==================================================================================
void CCollisionObject::Uninit(void)
{
	// �I������
	CObjectBillboard::Uninit();
}

//==================================================================================
// �X�V����
//==================================================================================
void CCollisionObject::Update(void)
{

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// �ʒu�X�V
	pos += move;

	// �ʒu�ݒ�
	SetPosition(pos);

	// �ړ��ʐݒ�
	SetMove(move);

	// �����̍X�V
	m_nLife--;

	// �T�C�Y�ݒ�
	SetSize(D3DXVECTOR2(m_fRadius, m_fRadius));

	if (m_nLife <= 0)
	{// �������s������
		Uninit();
		return;
	}

	switch (m_MyTag)
	{
	case CCollisionObject::TAG_PLAYER:
		CollisionEnemy();
		break;

	case CCollisionObject::TAG_ENEMY:
		CollisionPlayer();
		break;
	}

	// ���_���W�̐ݒ�
	SetVtx();

}

//==================================================================================
// �G�Ƃ̓����蔻��
//==================================================================================
void CCollisionObject::CollisionEnemy(void)
{
	// �G�擾
	CEnemyManager *pEnemyManager = CGame::GetEnemyManager();
	if (pEnemyManager == NULL)
	{
		return;
	}

	// �G�擾
	CEnemy **ppEnemy = pEnemyManager->GetEnemy();

	// �����擾
	int nNumAll = pEnemyManager->GetNumAll();
	int i = -1, nCntEnemy = 0;

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

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

		if (SphereRange(pos, TargetPos, m_fRadius, fTargetRadius))
		{// ���̔���

			if (ppEnemy[i]->Hit(m_nDamage) == true)
			{// �������Ă���

			}
		}

		// �G�̐����Z
		nCntEnemy++;
	}
}

//==================================================================================
// �v���C���[�Ƃ̓����蔻��
//==================================================================================
void CCollisionObject::CollisionPlayer(void)
{

	// �����̏��擾
	D3DXVECTOR3 pos = GetPosition();

	// �v���C���[�̎擾
	for (int nCntPlayer = 0; nCntPlayer < mylib_const::MAX_PLAYER; nCntPlayer++)
	{
		CPlayer *pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(nCntPlayer);
		if (pPlayer == NULL)
		{
			continue;
		}

		// �v���C���[���擾
		D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();
		float PlayerRadius = pPlayer->GetRadius();
		CPlayer::STATE PlayerState = (CPlayer::STATE)pPlayer->GetState();

		// ���̔���
		if (SphereRange(pos, PlayerPos, m_fRadius, PlayerRadius) &&
			PlayerState != CPlayer::STATE_DEAD &&
			PlayerState != CPlayer::STATE_DMG &&
			PlayerState != CPlayer::STATE_KNOCKBACK &&
			PlayerState != CPlayer::STATE_INVINCIBLE)
		{
			// �q�b�g����
			if (pPlayer->Hit(m_nDamage) == false)
			{// ����łȂ�������

			}
		}
	}
}

//==================================================================================
// �`�揈��
//==================================================================================
void CCollisionObject::Draw(void)
{
	return;
#ifdef _DEBUG
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);	//��ɕ`�悷��

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �`�揈��
	CObjectBillboard::Draw();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
#endif
}
