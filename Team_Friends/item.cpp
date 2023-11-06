//=============================================================================
// 
//  �A�C�e������ [item.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "item.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"
#include "explosion.h"
#include "3D_effect.h"
#include "sound.h"
#include "particle.h"
#include "calculation.h"
#include "game.h"
#include "player.h"
#include "impactwave.h"
#include "scene.h"

//==========================================================================
// �}�N����`
//==========================================================================
#define WIDTH			(30.0f)							// ����
#define HEIGHT			(30.0f)							// �c��
#define MOVE_SPEED		(15.0f)							// �ړ����x
#define ANIM_SPEED		(4)								// �ǂݍ��݊Ԋu
#define MAX_PATTERN_U	(1)								// U�̕�����
#define MAX_PATTERN_V	(1)								// V�̕�����
#define MAX_PATTERN		(MAX_PATTERN_U)					// �A�j���[�V�����p�^�[���̍ő吔
#define MOVE_U			(1.0f / (float)MAX_PATTERN_U)	// U���W�ړ���
#define MOVE_V			(1.0f / (float)MAX_PATTERN_V)	// V���W�ړ���

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
const char *CItem::m_apModelFile[TYPE_MAX] =	// �e�N�X�`���̃t�@�C��
{
	"data\\MODEL\\item.x",
};
int CItem::m_nNumAll = 0;		// �A�C�e���̑���

//==========================================================================
// �֐��|�C���^
//==========================================================================
CItem::STATE_FUNC CItem::m_FuncList[] =
{
	&CItem::StateNone,
	&CItem::StateDamage,
};

CItem::COLLISION_FUNC CItem::m_CollisionFuncList[] =	// �����蔻��̃��X�g
{
	&CItem::CollisionPlayer,	// �v���C���[�Ƃ̔���
};

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CItem::CItem(int nPriority) : CObjectX(nPriority), m_nLifeMax(1)
{
	// �l�̃N���A
	m_state = STATE_NONE;			// ���
	m_nCntState = 0;			// ��ԑJ�ڃJ�E���^�[
	m_nLife = 0;
	m_nIdxBulletManager = 0;			// �A�C�e���}�l�[�W���̃C���f�b�N�X�ԍ�
	m_nCntEmission = 0;	// �������̃J�E���^�[

	// �e�N�X�`���f�[�^�̔z�񕪌J��Ԃ�
	m_nModelIdx = 0;		// �e�N�X�`���̃C���f�b�N�X�ԍ�

	// �������Z
	m_nNumAll++;
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CItem::~CItem()
{
	
}

//==========================================================================
// ��������
//==========================================================================
CItem *CItem::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	// �����p�̃I�u�W�F�N�g
	CItem *pBullet = NULL;

	if (pBullet == NULL)
	{// NULL��������

		// �������̊m��
		pBullet = DEBUG_NEW CItem;

		if (pBullet != NULL)
		{// �������̊m�ۂ��o���Ă�����

			// �ʒu���蓖��
			pBullet->SetPosition(pos);

			// �ʒu���蓖��
			pBullet->SetRotation(rot);

			// ����������
			pBullet->Init();
		}

		return pBullet;
	}

	return NULL;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CItem::Init(void)
{
	HRESULT hr;

	// �e��ϐ��̏�����
	m_nLifeMax = 60 * 5;
	m_nLife = m_nLifeMax;	// ����
	SetColor(D3DXCOLOR(0.3f, 0.3f, 1.0f, 1.0f));

	// ���f���̊��蓖��
	CScene *pScene = CManager::GetInstance()->GetScene();
	m_nModelIdx = pScene->GetXLoad()->XLoad(m_apModelFile[m_type]);

	// ���f���̊��蓖��
	BindXData(m_nModelIdx);

	// ��ނ̐ݒ�
	CObject::SetType(TYPE_BULLET);

	// ����������
	hr = CObjectX::Init();
	if (FAILED(hr))
	{// ���s�����Ƃ�
		return E_FAIL;
	}

	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CItem::Uninit(void)
{
	//// �폜
	//if (CManager::GetInstance()->GetMode() == CScene::MODE_GAME && CGame::GetBulletManager() != NULL)
	//{// �A�C�e���}�l�[�W���̍폜
	//	CGame::GetBulletManager()->Delete(m_nIdxBulletManager);
	//}

	// �I������
	CObjectX::Uninit();

	// �������Z
	m_nNumAll--;
}

//==========================================================================
// �X�V����
//==========================================================================
void CItem::Update(void)
{
	// �ʒu�X�V
	UpdatePos();

	// ��ԕʏ���
	(this->*(m_FuncList[m_state]))();

	// �����蔻�菈��
	(this->*(m_CollisionFuncList[m_type]))();

	if (IsDeath() == true)
	{// ���S�t���O�������Ă�����
		return;
	}

	// �������Z
	m_nLife--;

	if (m_nLife <= 0)
	{// �������s������

		// �����̐���
		CExplosion::Create(GetPosition());
		
		Uninit();
		return;
	}

	// ���_���ݒ�
	SetVtx();
}

//==========================================================================
// �ړ�����
//==========================================================================
void CItem::UpdatePos(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// �����擾
	D3DXVECTOR3 rot = GetRotation();

	// �ʒu�X�V
	pos += move;

	// �ʒu�ݒ�
	SetPosition(pos);

	// �ړ��ʐݒ�
	SetMove(move);

	// �����ݒ�
	SetRotation(rot);
}

//==========================================================================
// �ʏ��ԏ���
//==========================================================================
void CItem::StateNone(void)
{
	// ��ԑJ�ڃJ�E���^�[���Z
	m_nCntState--;
	if (m_nCntState <= 0)
	{
		m_nCntState = 0;
		m_state = STATE_NONE;
	}
}

//==========================================================================
// �_���[�W��ԏ���
//==========================================================================
void CItem::StateDamage(void)
{
	// ��ԑJ�ڃJ�E���^�[���Z
	m_nCntState--;
	if (m_nCntState <= 0)
	{
		m_nCntState = 0;
		m_state = STATE_NONE;
	}
}

//==========================================================================
// �v���C���[�Ƃ̔���
//==========================================================================
void CItem::CollisionPlayer(void)
{
	// �v���C���[���擾
	CPlayer *pPlayer = CManager::GetInstance()->GetScene()->GetPlayer();
	if (pPlayer == NULL)
	{// NULL��������
		return;
	}

	// �v���C���[�̏��擾
	D3DXVECTOR3 PlayerPosition = pPlayer->GetCenterPosition();
	D3DXVECTOR3 PlayerRotation = pPlayer->GetRotation();
	float fPlayerRadius = pPlayer->GetRadius();

	// ���擾
	D3DXVECTOR3 pos = GetPosition();
	float fRadius = GetVtxMax().x;

	if (SphereRange(pos, PlayerPosition, fRadius, fPlayerRadius))
	{// �������Ă�����

		// �I������
		Uninit();
		return;
	}

}

//==========================================================================
// �v���C���[�A�C�e���̍X�V
//==========================================================================
void CItem::UpdateTypePlayer(void)
{

}

//==========================================================================
// �`�揈��
//==========================================================================
void CItem::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);	//��ɕ`�悷��

	// �r���{�[�h�̕`��
	CObjectX::Draw();

	// Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//==========================================================================
// ���_���ݒ菈��
//==========================================================================
void CItem::SetVtx(void)
{
	// ���_�ݒ�
	CObjectX::SetVtx();
}

//==========================================================================
// ��Ԑݒ�
//==========================================================================
void CItem::SetState(STATE state, int nCntState)
{
	m_state = state;			// ���
	m_nCntState = nCntState;	// ��ԑJ�ڃJ�E���^�[
}

//==========================================================================
// ��Ԏ擾
//==========================================================================
CItem::STATE CItem::GetState(void)
{
	return m_state;
}

//==========================================================================
// ��ސݒ�
//==========================================================================
void CItem::SetType(TYPE type)
{
	m_type = type;

	// ���f���̊��蓖��
	CScene *pScene = CManager::GetInstance()->GetScene();
	m_nModelIdx = pScene->GetXLoad()->XLoad(m_apModelFile[m_type]);

	// ���f���̊��蓖��
	BindXData(m_nModelIdx);
}

//==========================================================================
// ��ގ擾
//==========================================================================
CItem::TYPE CItem::GetType(void)
{
	return m_type;
}

//==========================================================================
// �����擾
//==========================================================================
int CItem::GetNumAll(void)
{
	return m_nNumAll;
}
