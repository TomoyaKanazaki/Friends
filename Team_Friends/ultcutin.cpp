//=============================================================================
// 
//  �K�E�̃J�b�g�C������ [ultcutin.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "ultcutin.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"
#include "sound.h"
#include "instantfade.h"
#include "game.h"
#include "player_union.h"
#include "enemy_boss.h"
#include "enemymanager.h"
#include "calculation.h"

//==========================================================================
// �萔��`
//==========================================================================
namespace
{
	const char* TEXTURE = "data\\TEXTURE\\anim\\cutin.png";
}

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
int CUltCutin::m_nTexIdx = 0;	// �e�N�X�`���̃C���f�b�N�X�ԍ�

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CUltCutin::CUltCutin(int nPriority) : CObject2D_Anim(nPriority)
{
	// �l�̃N���A
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CUltCutin::~CUltCutin()
{
	
}

//==========================================================================
// �e�N�X�`���ǂݍ���
//==========================================================================
void CUltCutin::LoadTexture(void)
{
	// �e�N�X�`���̓ǂݍ���
	m_nTexIdx = CManager::GetInstance()->GetTexture()->Regist(TEXTURE);
}

//==========================================================================
// ��������
//==========================================================================
CUltCutin *CUltCutin::Create(void)
{
	// �����p�̃I�u�W�F�N�g
	CUltCutin *pExplosion = nullptr;

	if (pExplosion == nullptr)
	{// nullptr��������

		// �������̊m��
		pExplosion = DEBUG_NEW CUltCutin;

		if (pExplosion != nullptr)
		{// �������̊m�ۂ��o���Ă�����

			// ����������
			pExplosion->Init();
		}

		return pExplosion;
	}

	return nullptr;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CUltCutin::Init(void)
{

	// ��ނ̐ݒ�
	SetType(TYPE_OBJECT2D);

	// �e�N�X�`���̊��蓖��
	if (m_nTexIdx == 0)
	{
		m_nTexIdx = CManager::GetInstance()->GetTexture()->Regist(TEXTURE);
	}

	// �e�N�X�`���̊��蓖��
	BindTexture(m_nTexIdx);

	// �ʒu���蓖��
	SetPosition(D3DXVECTOR3(640.0f, 360.0f, 0.0f));

	// �T�C�Y�ݒ�
	SetSize(D3DXVECTOR2(640.0f, 360.0f));

	// ����������
	CObject2D_Anim::Init(12, 4, 1, true);

	CManager::GetInstance()->GetInstantFade()->SetFade(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 24);

	SetEnableHitstopMove();

	return S_OK;
}

//==========================================================================
// �X�V����
//==========================================================================
void CUltCutin::Update(void)
{
	// �t�F�[�h�̏�Ԏ擾
	CInstantFade::STATE fadestate = CManager::GetInstance()->GetInstantFade()->GetState();
	if (fadestate == CInstantFade::STATE_FADECOMPLETION)
	{// ����������

		if (CGame::GetEnemyManager() != nullptr && CGame::GetEnemyManager()->GetBoss() != nullptr)
		{
			CEnemyBoss *pEnemyBoss = CGame::GetEnemyManager()->GetBoss();
			CPlayerUnion *pPlayerUnion = CManager::GetInstance()->GetScene()->GetPlayerUnion();
			if (pEnemyBoss != nullptr && pPlayerUnion != nullptr)
			{
				D3DXVECTOR3 targetPosition = mylib_const::DEFAULT_VECTOR3;
				D3DXVECTOR3 unionPosition = pPlayerUnion->GetPosition();
				D3DXVECTOR3 unionRotation = pPlayerUnion->GetRotation();

				// �ڕW�l����o��
				targetPosition.x = sinf(D3DX_PI + unionRotation.y) * 1000.0f;
				targetPosition.z = cosf(D3DX_PI + unionRotation.y) * 1000.0f;

				// �v���C���[�̈ʒu���Z
				targetPosition += unionPosition;
				targetPosition.y = 0.0f;

				pEnemyBoss->SetPosition(targetPosition);

				// �v���C���[�ɑ΂��Đ��ʌ�����
				D3DXVECTOR3 bossRotation = pEnemyBoss->GetRotation();
				bossRotation.y += D3DX_PI;
				RotNormalize(bossRotation);

				pEnemyBoss->SetRotation(bossRotation);
			}
		}

	}

	// �X�V����
	CObject2D_Anim::Update();
}

//==========================================================================
// �`�揈��
//==========================================================================
void CUltCutin::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// �`�揈��
	CObject2D_Anim::Draw();

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}
