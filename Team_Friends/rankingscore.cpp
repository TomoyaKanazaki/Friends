//=============================================================================
// 
//  �����L���O�X�R�A���� [rankingscore.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "rankingscore.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"
#include "object2D.h"
#include "multinumber.h"
#include "calculation.h"
#include "ranking.h"
#include "rankingmanager.h"
#include "sound.h"
#include "input.h"

//==========================================================================
// �}�N����`
//==========================================================================
#define RANKINGFILE			"data\\BIN\\ranking.bin"
#define NUMBERTEXTURE		"data\\TEXTURE\\number_blackclover_01.png"	// �e�N�X�`���̃t�@�C��
#define TEX_U				(0.1f)				// U�̕���
#define BASE_WIDTH			(0.8f)		// ����
#define BASE_HEIGHT			(1.0f)		// �c��
#define BASE_DIS_X			(0.0f)		// �Ԋu
#define DIS_Y				(2.0f)				// �Ԋu
#define POSY_BASE			(330.0f)			// Y�ʒu
#define BASETEXT_POSX		(180.0f)			// X�ʒu
#define TEXT_MOVETIME		(50000)				// �ړ�����
#define INIT_POSX			(1600.0f)			// �����ʒu
#define INIT_POSY			(943.0f)			// �����ʒu
#define INIT_POS_A			(-1)			// �����ʒu
#define INIT_POS_B			(3.5f)			// �����ʒu

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
const char *CRankingScore::m_apTexture3DFile[VTX3D_MAX] =		// �e�N�X�`���̃t�@�C��
{
	"data\\TEXTURE\\rankingnum_01.png",
	"data\\TEXTURE\\ranking_virtual_window_00.png",
	"data\\TEXTURE\\ranking_virtual_window_01.png",
	"data\\TEXTURE\\ranking_shadow_00.png",
	"data\\TEXTURE\\rankinglogo_02.png",
};

const char *CRankingScore::m_apTexture3D_WinFile =		// �e�N�X�`���̃t�@�C��
{
	"data\\TEXTURE\\ranking_virtual_window_03.png",
};

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CRankingScore::CRankingScore(int nPriority)
{
	// �l�̃N���A
	m_nNumRanking = 0;				// �����L���O��
	memset(&m_nScore[0], 0, sizeof(m_nScore));	// �X�R�A
	memset(&m_nRank[0], 0, sizeof(m_nRank));	// �X�R�A
	m_nNowScore = 0;		// ����̃X�R�A
	m_nTexIdxNumber = 0;			// �����e�N�X�`���̃C���f�b�N�X�ԍ�
	m_nIdxNewRecord = 0;	// �e�N�X�`���̃C���f�b�N�X�ԍ�
	m_nCntNewRecord = 0;			// �j���[���R�[�h�̃J�E���^�[
	m_nCnt = 0;
	memset(&m_fPosDestY[0], 0, sizeof(m_fPosDestY));	// �ڕW�̈ʒu
	m_bNewRecord = 0;	// �I�u�W�F�N�g2D�̃I�u�W�F�N�g
	memset(&m_bArrival[0], NULL, sizeof(m_bArrival));	// ��������
	memset(&m_pScore[0], NULL, sizeof(m_pScore));	// �����̃I�u�W�F�N�g
	memset(&m_pRank[0], NULL, sizeof(m_pRank));	// �����̃I�u�W�F�N�g
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CRankingScore::~CRankingScore()
{

}

//==========================================================================
// ��������
//==========================================================================
CRankingScore *CRankingScore::Create(void)
{
	// �����p�̃I�u�W�F�N�g
	CRankingScore *pScore = NULL;

	if (pScore == NULL)
	{// NULL��������

	 // �������̊m��
		pScore = DEBUG_NEW CRankingScore;

		if (pScore != NULL)
		{// �������̊m�ۂ��o���Ă�����

		 // ����������
			pScore->Init();
		}

		return pScore;
	}

	return NULL;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CRankingScore::Init(void)
{
	// ��ސݒ�
	SetType(CObject::TYPE_SCORE);

	for (int nCntVtx = 0; nCntVtx < VTX3D_MAX; nCntVtx++)
	{
		// ��������
		m_pObj3D[nCntVtx] = CObject3D::Create(6);

		// �e�N�X�`���̊��蓖��
		m_nTexIdx3D[nCntVtx] = CManager::GetInstance()->GetTexture()->Regist(m_apTexture3DFile[nCntVtx]);

		// �e�N�X�`���̊��蓖��
		m_pObj3D[nCntVtx]->GetObject3D()->BindTexture(m_nTexIdx3D[nCntVtx]);

		// �e��ϐ��̏�����
		switch (nCntVtx)
		{
		case VTX_LOGO:
			m_pObj3D[nCntVtx]->GetObject3D()->SetSize(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).x * 0.003f,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).y * 0.003f,
				0.0f));	// �T�C�Y

			m_pObj3D[nCntVtx]->GetObject3D()->SetPosition(D3DXVECTOR3(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetSize().x + 63.0f - cosf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * 6.5f,
				m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetSize().y + INIT_POSY + 5.0f,
				-150.0f + sinf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * 6.5f));	// �ʒu

			m_pObj3D[nCntVtx]->GetObject3D()->SetRotation(D3DXVECTOR3(0.0f, 0.5f, 0.0f));	// ����
			break;



		case VTX_NUM:
			m_pObj3D[nCntVtx]->GetObject3D()->SetSize(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).x * 0.5f,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).y * 0.5f,
				0.0f));	// �T�C�Y

			m_pObj3D[nCntVtx]->SetPosition(D3DXVECTOR3(m_pObj3D[nCntVtx]->GetSize().x, 360.0f, 0.0f));	// �ʒu
			break;



		case VTX3D_VIRTUAL_WINDOW_00:
			m_pObj3D[nCntVtx]->GetObject3D()->SetSize(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).x * 0.13f,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).y * 0.13f,
				0.0f));	// �T�C�Y

			m_pObj3D[nCntVtx]->GetObject3D()->SetPosition(D3DXVECTOR3(m_pObj3D[nCntVtx]->GetSize().x + 63.0f, m_pObj3D[nCntVtx]->GetSize().y + INIT_POSY, -150.0f));	// �ʒu
			m_pObj3D[nCntVtx]->GetObject3D()->SetRotation(D3DXVECTOR3(0.0f, 0.5f, 0.0f));	// ����
			break;



		case VTX3D_VIRTUAL_WINDOW_01:
			m_pObj3D[nCntVtx]->GetObject3D()->SetSize(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).x * 0.13f,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).y * 0.13f,
				0.0f));	// �T�C�Y

			m_pObj3D[nCntVtx]->GetObject3D()->SetPosition(D3DXVECTOR3(m_pObj3D[nCntVtx]->GetSize().x + 63.0f, m_pObj3D[nCntVtx]->GetSize().y + INIT_POSY, -150.0f));	// �ʒu
			m_pObj3D[nCntVtx]->GetObject3D()->SetRotation(D3DXVECTOR3(0.0f, 0.5f, 0.0f));	// ����
			break;



		case VTX3D_SHADOE_00:
			m_pObj3D[nCntVtx]->GetObject3D()->SetSize(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).x * 0.14f,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D[nCntVtx]).y * 0.14f,
				0.0f));	// �T�C�Y

			m_pObj3D[nCntVtx]->GetObject3D()->SetPosition(D3DXVECTOR3(m_pObj3D[nCntVtx]->GetSize().x + 66.0f, m_pObj3D[nCntVtx]->GetSize().y + INIT_POSY - 9.0f, -143.0f));	// �ʒu
			m_pObj3D[nCntVtx]->GetObject3D()->SetRotation(D3DXVECTOR3(D3DX_PI / 2, 0.5f, 0.0f));	// ����
			break;

		default:
			break;
		}

		// ��ނ̐ݒ�
		m_pObj3D[nCntVtx]->GetObject3D()->SetType(CObject::TYPE_OBJECT3D);
	}

	for (int nCntVtx = 0; nCntVtx < WINDOW_WHITE_NUM; nCntVtx++)
	{
		// ��������
		m_pObj3D_Win[nCntVtx] = CObject3D::Create(6);

		// �e�N�X�`���̊��蓖��
		m_nTexIdx3D_Win = CManager::GetInstance()->GetTexture()->Regist(m_apTexture3D_WinFile);

		// �e�N�X�`���̊��蓖��
		m_pObj3D_Win[nCntVtx]->GetObject3D()->BindTexture(m_nTexIdx3D_Win);

		switch (nCntVtx)
		{
		case 0:
			m_pObj3D_Win[nCntVtx]->GetObject3D()->SetSize(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D_Win).x * 0.12f,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D_Win).y * 0.12f,
				0.0f));	// �T�C�Y

			m_pObj3D_Win[nCntVtx]->GetObject3D()->SetPosition(D3DXVECTOR3(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetSize().x + 63.0f - cosf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * 6.5f,
				m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetSize().y + INIT_POSY + 1.5f,
				-150.0f + sinf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * 6.5f));	// �ʒu

			break;



		case 1:
			m_pObj3D_Win[nCntVtx]->GetObject3D()->SetSize(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D_Win).x * 0.08f,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D_Win).y * 0.08f,
				0.0f));	// �T�C�Y

			m_pObj3D_Win[nCntVtx]->GetObject3D()->SetPosition(D3DXVECTOR3(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetSize().x + 63.0f - cosf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * 4.6f,
				m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetSize().y + INIT_POSY + 0.2f,
				-150.0f + sinf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * 4.6f));	// �ʒu
			break;



		case 2:
			m_pObj3D_Win[nCntVtx]->GetObject3D()->SetSize(D3DXVECTOR3(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D_Win).x * 0.1f,
				CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx3D_Win).y * 0.1f,
				0.0f));	// �T�C�Y

			m_pObj3D_Win[nCntVtx]->GetObject3D()->SetPosition(D3DXVECTOR3(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetSize().x + 63.0f - cosf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * 5.6f,
				m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetSize().y + INIT_POSY - 1.6f,
				-150.0f + sinf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * 5.6f));	// �ʒu
			break;

		default:
			break;
		}

		m_pObj3D_Win[nCntVtx]->GetObject3D()->SetRotation(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation());	// ����

		// ��ނ̐ݒ�
		m_pObj3D_Win[nCntVtx]->GetObject3D()->SetType(CObject::TYPE_OBJECT3D);
	}

	for (int nCntRanking = 0; nCntRanking < RANKINGNUM; nCntRanking++)
	{
		// ��������
		m_pScore[nCntRanking] = CMultiNumber::Create(D3DXVECTOR3(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetSize().x + 63.0f - cosf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * INIT_POS_A,
			-nCntRanking * DIS_Y + INIT_POSY + 10.0f,
			-150.0f + sinf(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation().y) * INIT_POS_A),
			D3DXVECTOR2(BASE_WIDTH, BASE_HEIGHT),
			RANKINGSCORE_DIGIT,
			CNumber::OBJECTTYPE_3D,
			true,
			7);

		m_pScore[nCntRanking]->SetRotation(m_pObj3D[VTX3D_VIRTUAL_WINDOW_00]->GetRotation());
		m_pScore[nCntRanking]->SetPosition(m_pScore[nCntRanking]->GetPosition());

		if (nCntRanking >= RANKING_DISPLAY_NUM)
		{
			m_pScore[nCntRanking]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}

		// �ڕW�̈ʒu
		m_fPosDestY[nCntRanking] = INIT_POSY + 11.0f + RANKINGNUM * DIS_Y;


		m_pRank[nCntRanking] = CMultiNumber::Create(D3DXVECTOR3(m_pScore[nCntRanking]->GetPosition().x - cosf(m_pScore[nCntRanking]->GetRotation().y) * INIT_POS_B,
			m_pScore[nCntRanking]->GetPosition().y,
			m_pScore[nCntRanking]->GetPosition().z + sinf(m_pScore[nCntRanking]->GetRotation().y) * INIT_POS_B),
			D3DXVECTOR2(BASE_WIDTH, BASE_HEIGHT),
			RANKINGRANK_DIGIT,
			CNumber::OBJECTTYPE_3D,
			true,
			7);

		m_pRank[nCntRanking]->SetRotation(m_pScore[nCntRanking]->GetRotation());
		m_pRank[nCntRanking]->SetPosition(m_pRank[nCntRanking]->GetPosition());

		if (nCntRanking >= RANKING_DISPLAY_NUM)
		{
			m_pRank[nCntRanking]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}

	// �����L���O�ǂݍ���
	Load();

	for (int nCntRanking = 1; nCntRanking <= m_nNumRanking; nCntRanking++)
	{
		m_nRank[nCntRanking - 1] = nCntRanking;
	}

	if (CManager::GetInstance()->GetOldMode() == CScene::MODE_RESULT)
	{
		m_nNowScore = CManager::GetInstance()->GetRankingManager()->GetNowScore();

		// �\�[�g����
		Sort();

		// �Z�[�u����
		Save();
	}

	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CRankingScore::Uninit(void)
{
	// �I������
	for (int nCntVtx = 0; nCntVtx < VTX3D_MAX; nCntVtx++)
	{
		if (m_pObj3D[nCntVtx] != NULL)
		{// �������̊m�ۂ�����Ă�����

		 // �I������
			m_pObj3D[nCntVtx]->Uninit();
			m_pObj3D[nCntVtx] = NULL;
		}
	}

	for (int nCntRanking = 0; nCntRanking < RANKINGNUM; nCntRanking++)
	{
		// �I������
		if (m_pScore[nCntRanking] != NULL)
		{// �������̊m�ۂ�����Ă�����

		 // �I������
			m_pScore[nCntRanking]->Uninit();
			delete m_pScore[nCntRanking];
			m_pScore[nCntRanking] = NULL;
		}
	}

	for (int nCntRanking = 0; nCntRanking < RANKINGNUM; nCntRanking++)
	{
		// �I������
		if (m_pRank[nCntRanking] != NULL)
		{// �������̊m�ۂ�����Ă�����

		 // �I������
			m_pRank[nCntRanking]->Uninit();
			delete m_pRank[nCntRanking];
			m_pRank[nCntRanking] = NULL;
		}
	}

	// ���폜
	Release();
}

//==========================================================================
// �X�V����
//==========================================================================
void CRankingScore::Update(void)
{
	// �L�[�{�[�h���擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �Q�[���p�b�h���擾
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	m_nCnt++;

	if (m_nCnt >= 60 * 2)
	{
		// �ړ�����
		MovingScore();

		MovingRank();

		m_nCnt = 60 * 2;
	}

	// �l�̐ݒ菈��
	for (int nCntRanking = 0; nCntRanking < RANKINGNUM; nCntRanking++)
	{
		m_pScore[nCntRanking]->SetValue(m_nScore[nCntRanking]);

		m_pScore[nCntRanking]->Update();

		m_pRank[nCntRanking]->SetValue(m_nRank[nCntRanking]);

		m_pRank[nCntRanking]->Update();
	}

	if (m_bNewRecord == true)
	{// �L�^�X�V���Ă�����

	 // �j���[���R�[�h�̍X�V����
		UpdateNewRecord();
	}
}

//==========================================================================
// �ړ�����
//==========================================================================
void CRankingScore::MovingScore(void)
{
	for (int nCntRanking = 0; nCntRanking < RANKINGNUM; nCntRanking++)
	{
		// �ʒu�擾
		D3DXVECTOR3 pos = m_pScore[nCntRanking]->GetPosition();

		if (pos.y >= INIT_POSY + 11.2f)
		{
			D3DXCOLOR col = m_pScore[nCntRanking]->GetColor();

			col.a -= 0.05f;

			m_pScore[nCntRanking]->SetColor(col);
		}

		else if (pos.y >= INIT_POSY + 9.0f - ((RANKING_DISPLAY_NUM - 1) * DIS_Y) && pos.y < INIT_POSY + 9.0f)
		{
			D3DXCOLOR col = m_pScore[nCntRanking]->GetColor();

			col.a += 0.05f;

			if (col.a >= 1.0f)
			{
				col.a = 1.0f;
			}

			m_pScore[nCntRanking]->SetColor(col);
		}

		float fDest = m_fPosDestY[nCntRanking] - nCntRanking * DIS_Y;


		// �ڕW�̈ʒu�֕␳
		if (fDest > pos.y)
		{
			pos.y += (fDest - (nCntRanking * DIS_Y)) / (float)TEXT_MOVETIME;
		}

		if (fDest < pos.y)
		{// �ڕW�ŌŒ�
			pos.y = m_fPosDestY[nCntRanking] + nCntRanking * DIS_Y;
			m_bArrival[nCntRanking] = true;

			if (nCntRanking == RANKINGNUM - 1)
			{
				CRanking::SetEnableArrival();
			}

			//// �T�E���h�Đ�
			//CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_RANKINGSCORE);
		}

		// �ʒu�ݒ�
		m_pScore[nCntRanking]->SetPosition(pos);
	}
}

//==========================================================================
// �ړ�����
//==========================================================================
void CRankingScore::MovingRank(void)
{
	for (int nCntRanking = 0; nCntRanking < RANKINGNUM; nCntRanking++)
	{
		// �ʒu�擾
		D3DXVECTOR3 pos = m_pRank[nCntRanking]->GetPosition();

		if (pos.y >= INIT_POSY + 11.2f)
		{
			D3DXCOLOR col = m_pRank[nCntRanking]->GetColor();

			col.a -= 0.05f;

			m_pRank[nCntRanking]->SetColor(col);
		}

		else if (pos.y >= INIT_POSY + 9.0f - ((RANKING_DISPLAY_NUM - 1) * DIS_Y) && pos.y < INIT_POSY + 9.0f)
		{
			D3DXCOLOR col = m_pRank[nCntRanking]->GetColor();

			col.a += 0.05f;

			if (col.a >= 1.0f)
			{
				col.a = 1.0f;
			}

			m_pRank[nCntRanking]->SetColor(col);
		}

		float fDest = m_fPosDestY[nCntRanking] - nCntRanking * DIS_Y;


		// �ڕW�̈ʒu�֕␳
		if (fDest > pos.y)
		{
			pos.y += (fDest - (nCntRanking * DIS_Y)) / (float)TEXT_MOVETIME;
		}

		if (fDest < pos.y)
		{// �ڕW�ŌŒ�
			pos.y = m_fPosDestY[nCntRanking] + nCntRanking * DIS_Y;
			m_bArrival[nCntRanking] = true;

			if (nCntRanking == RANKINGNUM - 1)
			{
				CRanking::SetEnableArrival();
			}

			//// �T�E���h�Đ�
			//CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_RANKINGSCORE);
		}

		// �ʒu�ݒ�
		m_pRank[nCntRanking]->SetPosition(pos);
	}
}

//==========================================================================
// �j���[���R�[�h�̍X�V����
//==========================================================================
void CRankingScore::UpdateNewRecord(void)
{

	// �ʒu�擾
	D3DXVECTOR3 pos = m_pScore[m_nIdxNewRecord]->GetPosition();

	// �F�擾
	D3DXCOLOR col = m_pScore[m_nIdxNewRecord]->GetColor();

	// �Ȑ��␳
	CuadricCurveComp(col.a, 180, 0.3f, 1.0f, m_nCntNewRecord);

	// �ʒu�ݒ�
	m_pScore[m_nIdxNewRecord]->SetPosition(pos);

	// �F�ݒ�
	m_pScore[m_nIdxNewRecord]->SetColor(col);
}

//==========================================================================
// �S�Ă̓����ݒ�
//==========================================================================
void CRankingScore::SetAllArrival(void)
{

	for (int nCntRanking = 0; nCntRanking < RANKINGNUM; nCntRanking++)
	{
		m_bArrival[nCntRanking] = true;	// ��������
	}

	for (int nCntRanking = 0; nCntRanking < RANKINGNUM; nCntRanking++)
	{
		// �ʒu�擾
		D3DXVECTOR3 pos = m_pScore[nCntRanking]->GetPosition();

		if (pos.x == INIT_POSX)
		{
			// �T�E���h�Đ�
			CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_NUMBERMOVE);
		}

		// �F�擾
		D3DXCOLOR col = m_pScore[nCntRanking]->GetColor();

		// �ړ�
		float fDest = m_fPosDestY[nCntRanking] + nCntRanking * DIS_Y;
		pos.x = fDest;

		// �s�����x�ݒ�
		col.a = 1.0f;

		// �ʒu�ݒ�
		m_pScore[nCntRanking]->SetPosition(pos);

		// �F�ݒ�
		m_pScore[nCntRanking]->SetColor(col);
	}

}


//==========================================================================
// �`�揈��
//==========================================================================
void CRankingScore::Draw(void)
{

}

//==============================================================
// �\�[�g����
//==============================================================
void CRankingScore::Sort(void)
{
	// �~������

	for (int nCntData = 0; nCntData < m_nNumRanking - 1; nCntData++)
	{
		for (int nCntSort = nCntData + 1; nCntSort < m_nNumRanking; nCntSort++)
		{
			if (m_nScore[nCntData] < m_nScore[nCntSort])
			{// �v�f1���v�f2���傫��������

				int nTemp = m_nScore[nCntData];
				m_nScore[nCntData] = m_nScore[nCntSort];
				m_nScore[nCntSort] = nTemp;
			}

		}

		// �����L���O�ő�l��������̂�������������
		if (m_nScore[m_nNumRanking - 1] < m_nNowScore)
		{// ����ւ�

			m_nScore[m_nNumRanking - 1] = m_nNowScore;	// �ŏ��l�ƍ���̃f�[�^����ւ�
			m_bNewRecord = true;	// �t���OON
		}
	}



	// �~������
	for (int nCntData = 0; nCntData < m_nNumRanking - 1; nCntData++)
	{
		for (int nCntSort = nCntData + 1; nCntSort < m_nNumRanking; nCntSort++)
		{
			if (m_nScore[nCntData] < m_nScore[nCntSort])
			{// �v�f1���v�f2���傫��������

				int nTemp = m_nScore[nCntData];
				m_nScore[nCntData] = m_nScore[nCntSort];
				m_nScore[nCntSort] = nTemp;
			}
		}


		if (m_bNewRecord == true)
		{// �j���[���R�[�h�̎�

			for (int nCount = RANKINGNUM; nCount > 0; nCount--)
			{// �v�f�ԍ��L�����Ĕ�����

				if (m_nScore[nCount - 1] == m_nNowScore)
				{
					m_nIdxNewRecord = nCount - 1;
					break;
				}
			}
		}
	}
}

//==============================================================
// �Z�[�u����
//==============================================================
void CRankingScore::Save(void)
{
	FILE *pFile;

	// �t�@�C�����J��
	pFile = fopen(RANKINGFILE, "wb");

	if (pFile != NULL)
	{// �t�@�C�����J�����ꍇ

	 // �t�@�C���ɐ��l�������o��
		fwrite(&m_nNumRanking, sizeof(int), 1, pFile);

		fwrite(&m_nScore[0], sizeof(int), m_nNumRanking, pFile);

		// �t�@�C�������
		fclose(pFile);
	}
}

//==============================================================
// ���[�h����
//==============================================================
void CRankingScore::Load(void)
{
	FILE *pFile;

	// �t�@�C�����J��
	pFile = fopen(RANKINGFILE, "rb");

	if (pFile != NULL)
	{// �t�@�C�����J�����ꍇ
	 // �t�@�C���ɐ��l��ǂݍ���
		fread(&m_nNumRanking, sizeof(int), 1, pFile);

		fread(&m_nScore[0], sizeof(int), m_nNumRanking, pFile);

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{// �t�@�C�����J���Ȃ������ꍇ

		m_nNumRanking = RANKINGNUM;

		for (int nCount = 0; nCount < m_nNumRanking; nCount++)
		{// �S���[��
			m_nScore[nCount] = 150000 - nCount * 5000;
		}

		// �Z�[�u
		Save();
	}
}