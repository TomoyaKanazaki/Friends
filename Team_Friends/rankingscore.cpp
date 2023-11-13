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
#include "number.h"
#include "calculation.h"
#include "ranking.h"
#include "rankingmanager.h"
#include "sound.h"

//==========================================================================
// �}�N����`
//==========================================================================
#define RANKINGFILE			"data\\BIN\\ranking.bin"
#define NUMBERTEXTURE		"data\\TEXTURE\\number_blackclover_01.png"	// �e�N�X�`���̃t�@�C��
#define TEX_U				(0.1f)				// U�̕���
#define BASE_WIDTH			(40.0f)		// ����
#define BASE_HEIGHT			(50.0f)		// �c��
#define BASE_DIS_X			(50.0f)		// �Ԋu
#define DIS_X				(50.0f)				// �Ԋu
#define POSY_BASE			(330.0f)			// Y�ʒu
#define BASETEXT_POSX		(180.0f)			// X�ʒu
#define TEXT_MOVETIME		(50)				// �ړ�����
#define INIT_POSX			(1600.0f)			// �����ʒu

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
const char *CRankingScore::m_apTextureFile[VTX_MAX] =		// �e�N�X�`���̃t�@�C��
{
	"data\\TEXTURE\\rankingnum_01.png",
	"data\\TEXTURE\\rankinglogo_02.png",
};

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CRankingScore::CRankingScore(int nPriority)
{
	// �l�̃N���A
	m_nNumRanking = 0;				// �����L���O��
	memset(&m_nScore[0], NULL, sizeof(m_nScore));	// �X�R�A
	m_nNowScore = 0;				// ����̃X�R�A
	memset(&m_pObj2D[0], NULL, sizeof(m_pObj2D));	// �I�u�W�F�N�g2D�̃I�u�W�F�N�g
	memset(&m_nTexIdx[0], 0, sizeof(m_nTexIdx));	// �e�N�X�`���̃C���f�b�N�X�ԍ�
	m_nTexIdxNumber = 0;			// �����e�N�X�`���̃C���f�b�N�X�ԍ�
	m_nIdxNewRecord = 0;			// �j���[���R�[�h�̃C���f�b�N�X�ԍ�
	m_nCntNewRecord = 0;			// �j���[���R�[�h�̃J�E���^�[
	memset(&m_fPosDestX[0], 0, sizeof(m_fPosDestX));	// �ڕW�̈ʒu
	m_bNewRecord = false;			// �j���[���R�[�h�̃t���O
	memset(&m_bArrival[0], NULL, sizeof(m_bArrival));	// ��������
	memset(&m_pScore[0], NULL, sizeof(m_pScore));	// �����̃I�u�W�F�N�g
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

	for (int nCntVtx = 0; nCntVtx < VTX_MAX; nCntVtx++)
	{
		// ��������
		m_pObj2D[nCntVtx] = CObject2D::Create(7);

		// �e�N�X�`���̊��蓖��
		m_nTexIdx[nCntVtx] = CManager::GetInstance()->GetTexture()->Regist(m_apTextureFile[nCntVtx]);

		// �e�N�X�`���̊��蓖��
		m_pObj2D[nCntVtx]->GetObject2D()->BindTexture(m_nTexIdx[nCntVtx]);

		// �e��ϐ��̏�����
		switch (nCntVtx)
		{
		case VTX_LOGO:
			m_pObj2D[nCntVtx]->GetObject2D()->SetSize(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx[nCntVtx]) * 0.3f);	// �T�C�Y
			m_pObj2D[nCntVtx]->GetObject2D()->SetPosition(D3DXVECTOR3(m_pObj2D[nCntVtx]->GetSize().x, 60.0f, 0.0f));	// �ʒu
			break;

		case VTX_NUM:
			m_pObj2D[nCntVtx]->GetObject2D()->SetSize(CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx[nCntVtx]) * 0.5f);	// �T�C�Y
			m_pObj2D[nCntVtx]->GetObject2D()->SetPosition(D3DXVECTOR3(m_pObj2D[nCntVtx]->GetSize().x, 360.0f, 0.0f));	// �ʒu
			break;

		default:
			break;
		}

		// ��ނ̐ݒ�
		m_pObj2D[nCntVtx]->GetObject2D()->SetType(CObject::TYPE_SCORE);
	}

	for (int nCntRanking = 0; nCntRanking < RANKINGNUM; nCntRanking++)
	{
		// �ڕW�̈ʒu
		m_fPosDestX[nCntRanking] = m_pObj2D[VTX_LOGO]->GetSize().x + 400.0f;

		for (int nCntScore = 0; nCntScore < RANKINGSCORE_DIGIT; nCntScore++)
		{
			// ��������
			m_pScore[nCntRanking][nCntScore] = CNumber::Create(CNumber::OBJECTTYPE_2D);

			// �e��ϐ��̏�����
			m_pScore[nCntRanking][nCntScore]->GetObject2D()->SetSize(D3DXVECTOR2(BASE_WIDTH, BASE_HEIGHT));	// �T�C�Y
			m_pScore[nCntRanking][nCntScore]->GetObject2D()->SetPosition(D3DXVECTOR3(INIT_POSX + nCntScore * BASE_DIS_X, nCntRanking * 120.0f + 170.0f, 0.0f));	// �ʒu

			// ��ނ̐ݒ�
			m_pScore[nCntRanking][nCntScore]->GetObject2D()->SetType(CObject::TYPE_SCORE);

			// �e�N�X�`���̊��蓖��
			m_nTexIdxNumber = CManager::GetInstance()->GetTexture()->Regist(NUMBERTEXTURE);

			// �e�N�X�`���̊��蓖��
			m_pScore[nCntRanking][nCntScore]->GetObject2D()->BindTexture(m_nTexIdxNumber);
		}
	}

	// �����L���O�ǂݍ���
	Load();

	if (CManager::GetInstance()->GetOldMode() == CScene::MODE_RESULT)
	{
		// ����̃X�R�A�擾
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
	for (int nCntVtx = 0; nCntVtx < VTX_MAX; nCntVtx++)
	{
		if (m_pObj2D[nCntVtx] != NULL)
		{// �������̊m�ۂ�����Ă�����

			// �I������
			m_pObj2D[nCntVtx]->Uninit();
			m_pObj2D[nCntVtx] = NULL;
		}
	}

	for (int nCntRanking = 0; nCntRanking < RANKINGNUM; nCntRanking++)
	{
		for (int nCntScore = 0; nCntScore < RANKINGSCORE_DIGIT; nCntScore++)
		{
			// �I������
			if (m_pScore[nCntRanking][nCntScore] != NULL)
			{// �������̊m�ۂ�����Ă�����

				// �I������
				m_pScore[nCntRanking][nCntScore]->Uninit();
				delete m_pScore[nCntRanking][nCntScore];
				m_pScore[nCntRanking][nCntScore] = NULL;
			}
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
	for (int nCntRanking = 0; nCntRanking < RANKINGNUM; nCntRanking++)
	{
		if (m_bArrival[nCntRanking] == false &&
			(nCntRanking == 0 || m_bArrival[nCntRanking - 1] == true))
		{
			// �ړ�����
			Moving(nCntRanking);
		}

		// �l�̐ݒ菈��
		SetValue(nCntRanking);
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
void CRankingScore::Moving(int nCntRanking)
{
	for (int nCntScore = 0; nCntScore < RANKINGSCORE_DIGIT; nCntScore++)
	{
		// �ʒu�擾
		D3DXVECTOR3 pos = m_pScore[nCntRanking][nCntScore]->GetObject2D()->GetPosition();

		if (pos.x == INIT_POSX)
		{
			
		}

		// �F�擾
		D3DXCOLOR col = m_pScore[nCntRanking][nCntScore]->GetObject2D()->GetColor();

		float fDest = m_fPosDestX[nCntRanking] + nCntScore * BASE_DIS_X;

		// �ڕW�̈ʒu�֕␳
		if (fDest < pos.x)
		{
			pos.x += (fDest - (INIT_POSX + nCntScore * BASE_DIS_X)) / (float)TEXT_MOVETIME;
			col.a += 1.0f / (float)TEXT_MOVETIME;
		}

		if (fDest >= pos.x)
		{// �ڕW�ŌŒ�
			pos.x = fDest;
			col.a = 1.0f;
			m_bArrival[nCntRanking] = true;

			if (nCntRanking == RANKINGNUM - 1 &&
				nCntScore == RANKINGSCORE_DIGIT - 1)
			{
				CRanking::SetEnableArrival();
			}

			// �T�E���h�Đ�
			CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_RANKINGSCORE);
		}

		// �ʒu�ݒ�
		m_pScore[nCntRanking][nCntScore]->GetObject2D()->SetPosition(pos);

		// �F�ݒ�
		m_pScore[nCntRanking][nCntScore]->GetObject2D()->SetColor(col);
	}
}

//==========================================================================
// �j���[���R�[�h�̍X�V����
//==========================================================================
void CRankingScore::UpdateNewRecord(void)
{
	for (int nCntScore = 0; nCntScore < RANKINGSCORE_DIGIT; nCntScore++)
	{
		// �ʒu�擾
		D3DXVECTOR3 pos = m_pScore[m_nIdxNewRecord][nCntScore]->GetObject2D()->GetPosition();

		// �T�C�Y�擾
		D3DXVECTOR2 size = m_pScore[m_nIdxNewRecord][nCntScore]->GetObject2D()->GetSize();

		// �F�擾
		D3DXCOLOR col = m_pScore[m_nIdxNewRecord][nCntScore]->GetObject2D()->GetColor();

		// �Ȑ��␳
		CuadricCurveComp(col.a, 180, 0.3f, 1.0f, m_nCntNewRecord);

		// �ʒu�ݒ�
		m_pScore[m_nIdxNewRecord][nCntScore]->GetObject2D()->SetPosition(pos);

		// �T�C�Y�ݒ�
		m_pScore[m_nIdxNewRecord][nCntScore]->GetObject2D()->SetSize(size);

		// �F�ݒ�
		m_pScore[m_nIdxNewRecord][nCntScore]->GetObject2D()->SetColor(col);
	}
}

//==========================================================================
// �S�Ă̓����ݒ�
//==========================================================================
void CRankingScore::SetAllArrival(void)
{

	for (int nCntScore = 0; nCntScore < RANKINGSCORE_DIGIT; nCntScore++)
	{
		m_bArrival[nCntScore] = true;	// ��������
	}

	for (int nCntRanking = 0; nCntRanking < RANKINGNUM; nCntRanking++)
	{
		for (int nCntScore = 0; nCntScore < RANKINGSCORE_DIGIT; nCntScore++)
		{
			// �ʒu�擾
			D3DXVECTOR3 pos = m_pScore[nCntRanking][nCntScore]->GetObject2D()->GetPosition();

			if (pos.x == INIT_POSX)
			{
				// �T�E���h�Đ�
				CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_NUMBERMOVE);
			}

			// �F�擾
			D3DXCOLOR col = m_pScore[nCntRanking][nCntScore]->GetObject2D()->GetColor();

			// �ړ�
			float fDest = m_fPosDestX[nCntRanking] + nCntScore * BASE_DIS_X;
			pos.x = fDest;

			// �s�����x�ݒ�
			col.a = 1.0f;

			// �ʒu�ݒ�
			m_pScore[nCntRanking][nCntScore]->GetObject2D()->SetPosition(pos);

			// �F�ݒ�
			m_pScore[nCntRanking][nCntScore]->GetObject2D()->SetColor(col);
		}
	}

}

//==========================================================================
// �l�̐ݒ菈��
//==========================================================================
void CRankingScore::SetValue(int nCntRanking)
{
	int aTexU[RANKINGSCORE_DIGIT];
	int nDigit = 1;		// aTexU�v�Z�p

	// �v�Z�p����o��
	for (int nCntDigit = 0; nCntDigit < RANKINGSCORE_DIGIT; nCntDigit++)
	{
		nDigit *= 10;
	}

	// �e�N�X�`�����W�ɑ������
	for (int nCntTex = 0; nCntTex < RANKINGSCORE_DIGIT; nCntTex++)
	{// �������ݒ�

		aTexU[nCntTex] = m_nScore[nCntRanking] % nDigit / (nDigit / 10);
		nDigit /= 10;
	}

	for (int nCntScore = 0; nCntScore < RANKINGSCORE_DIGIT; nCntScore++)
	{
		if (m_pScore[nCntRanking][nCntScore] != NULL)
		{// NULL����Ȃ�������

			D3DXVECTOR2 *pTex = m_pScore[nCntRanking][nCntScore]->GetObject2D()->GetTex();

			// �e�N�X�`�����W�̐ݒ�
			pTex[0] = D3DXVECTOR2(aTexU[nCntScore] * TEX_U, 0.0f);
			pTex[1] = D3DXVECTOR2(aTexU[nCntScore] * TEX_U + TEX_U, 0.0f);
			pTex[2] = D3DXVECTOR2(aTexU[nCntScore] * TEX_U, 1.0f);
			pTex[3] = D3DXVECTOR2(aTexU[nCntScore] * TEX_U + TEX_U, 1.0f);

			// ���_�ݒ�
			m_pScore[nCntRanking][nCntScore]->GetObject2D()->SetVtx();
		}
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
	}

	// �����L���O�ő�l��������̂�������������
	if (m_nScore[m_nNumRanking - 1] < m_nNowScore)
	{// ����ւ�

		m_nScore[m_nNumRanking - 1] = m_nNowScore;	// �ŏ��l�ƍ���̃f�[�^����ւ�
		m_bNewRecord = true;	// �t���OON
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
			m_nScore[nCount] = 150000 - nCount * 25000;
		}

		// �Z�[�u
		Save();
	}
}