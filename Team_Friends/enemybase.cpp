//=============================================================================
// 
//  �J�����̎����� [enemybase.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "debugproc.h"
#include "enemybase.h"
#include "calculation.h"
#include "game.h"
#include "gamemanager.h"
#include "3D_effect.h"
#include "debugpointnumber.h"
#include "objectX.h"
#include "enemymanager.h"
#include "manager.h"

//==========================================================================
// �}�N����`
//==========================================================================
#define MARKOBJ	"data\\MODEL\\koko.x"
#define FILE_ENEMYBASE	"data\\BIN\\enemybase.bin"

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
int CEnemyBase::m_nNumAll = 0;		// ����

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CEnemyBase::CEnemyBase()
{
	// �l�̃N���A
		memset(&m_pMultiNumber[0], NULL, sizeof(m_pMultiNumber));	// �I�u�W�F�N�gX
	memset(&m_apObjX[0], NULL, sizeof(m_apObjX));	// �I�u�W�F�N�gX
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CEnemyBase::~CEnemyBase()
{

}

//==========================================================================
// ��������
//==========================================================================
CEnemyBase *CEnemyBase::Create(const char *pFileName)
{
	// �����p�̃I�u�W�F�N�g
	CEnemyBase *pModel = NULL;

	if (pModel == NULL)
	{// NULL��������

		// �������̊m��
		pModel = DEBUG_NEW CEnemyBase;

		if (pModel != NULL)
		{// �������̊m�ۂ��o���Ă�����

			// ����������
			HRESULT hr = pModel->ReadText(pFileName);

			if (FAILED(hr))
			{// ���s���Ă�����
				return NULL;
			}

			// ����������
			hr = pModel->Init();
			if (FAILED(hr))
			{// ���s���Ă�����
				delete pModel;
				return NULL;
			}
		}

		return pModel;
	}

	return NULL;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CEnemyBase::Init(void)
{
	// �G�}�l�[�W���擾
	CEnemyManager *pEnemyManager = CGame::GetEnemyManager();

	// ��������
	for (int i = 0; i < m_nNumAll; i++)
	{
		// �f�o�b�O�p�����̐���
		m_pMultiNumber[i] = CDebugPointNumber::Create(i);

		if (m_ChaseChangeInfo[i].nRush == 0)
		{// ���b�V���p����Ȃ�������
			pEnemyManager->SetEnemy(
				D3DXVECTOR3(0.0f, m_ChaseChangeInfo[i].fSpawnPosY, 0.0f),
				mylib_const::DEFAULT_VECTOR3,
				m_ChaseChangeInfo[i].nPattern);
		}
	}

	return S_OK;
}

//==========================================================================
// �ʒu�쐬
//==========================================================================
void CEnemyBase::CreatePos(int nPattern, int nMapIdx, float fMapMoveValue, int nRush, float PosY)
{
	sInfo InitInfo;
	memset(&InitInfo, NULL, sizeof(InitInfo));

	// �ʒu����
	m_ChaseChangeInfo.push_back(InitInfo);
	m_ChaseChangeInfo[m_nNumAll].nPattern = nPattern;	// ���
	m_ChaseChangeInfo[m_nNumAll].nMapIdx = nMapIdx;
	m_ChaseChangeInfo[m_nNumAll].fMapMoveValue = fMapMoveValue;
	m_ChaseChangeInfo[m_nNumAll].fSpawnPosY = PosY;
	m_ChaseChangeInfo[m_nNumAll].nRush = nRush;

	// �ڈ󐶐�
	m_apObjX[m_nNumAll] = CObjectX::Create(MARKOBJ, mylib_const::DEFAULT_VECTOR3, mylib_const::DEFAULT_VECTOR3, false);	// �I�u�W�F�N�gX
	m_apObjX[m_nNumAll]->SetType(CObject::TYPE_BALLAST);
	m_apObjX[m_nNumAll]->SetPosition(D3DXVECTOR3(0.0f, PosY, 0.0f));

	// �������Z
	m_nNumAll++;

}

//==========================================================================
// �ʒu�폜
//==========================================================================
void CEnemyBase::DeletePos(int nIdx)
{
	// �\�[�g����
	CalSort(&m_ChaseChangeInfo[0], nIdx, m_nNumAll);

	// �ʒu����
	m_ChaseChangeInfo.pop_back();

	// �������Z
	m_nNumAll--;
}

//==========================================================================
// �I������
//==========================================================================
void CEnemyBase::Uninit(void)
{
	
}

//==========================================================================
// �X�V����
//==========================================================================
void CEnemyBase::Update(void)
{
#if _DEBUG

	for (int i = 0; i < m_nNumAll; i++)
	{
		if (m_apObjX[i] == NULL)
		{
			m_apObjX[i] = CObjectX::Create(MARKOBJ, mylib_const::DEFAULT_VECTOR3, mylib_const::DEFAULT_VECTOR3, false);	// �I�u�W�F�N�gX
			m_apObjX[i]->SetType(CObject::TYPE_BALLAST);
			//m_apObjX[i]->SetPositionD3DXVECTOR3(pos.x, m_apObjX[i]->GetPosition().y, pos.z);
		}

		// �}�b�v��񂩂�ʒu�擾
		D3DXVECTOR3 pos = mylib_const::DEFAULT_VECTOR3;

		m_apObjX[i]->SetPosition(D3DXVECTOR3(pos.x, m_ChaseChangeInfo[i].fSpawnPosY, pos.z));

		if (m_pMultiNumber[i] != NULL)
		{
			m_pMultiNumber[i]->SetPosition(D3DXVECTOR3(pos.x, m_ChaseChangeInfo[i].fSpawnPosY + 50.0f, pos.z));
		}
	}
#endif
}

//==========================================================================
// �e�L�X�g�ǂݍ��ݏ���
//==========================================================================
HRESULT CEnemyBase::ReadText(const char *pFileName)
{

	char aComment[MAX_COMMENT] = {};	// �R�����g�p

	FILE *pFile = NULL;	// �t�@�C���|�C���^��錾

	// �t�@�C�����J��
	pFile = fopen(pFileName, "r");

	if (pFile == NULL)
	{// �t�@�C�����J���Ȃ������ꍇ
		return E_FAIL;
	}

	// ���Z�b�g
	m_nNumAll = 0;

	while (1)
	{// END_SCRIPT������܂ŌJ��Ԃ�

		// ������̓ǂݍ���
		fscanf(pFile, "%s", &aComment[0]);

		if (strcmp(aComment, "BASESET") == 0)
		{// BASESET�œG���_�̓ǂݍ��݊J�n

			// �Ō���ɐ���
			sInfo InitInfo;
			memset(&InitInfo, NULL, sizeof(InitInfo));
			m_ChaseChangeInfo.push_back(InitInfo);

			while (strcmp(aComment, "END_BASESET") != 0)
			{// END_BASESET������܂ŌJ��Ԃ�

				fscanf(pFile, "%s", &aComment[0]);	// �m�F����

				if (strcmp(aComment, "PATTERN") == 0)
				{// PATTERN��������G�̎�ޓǂݍ���

					fscanf(pFile, "%s", &aComment[0]);	// =�̕�
					fscanf(pFile, "%d", &m_ChaseChangeInfo[m_nNumAll].nPattern);	// �L�����t�@�C���ԍ�
				}

				if (strcmp(aComment, "MAPIDX") == 0)
				{// MAPIDX��������}�b�v�C���f�b�N�X�ԍ��ǂݍ���

					fscanf(pFile, "%s", &aComment[0]);	// =�̕�
					fscanf(pFile, "%d", &m_ChaseChangeInfo[m_nNumAll].nMapIdx);	// �}�b�v�C���f�b�N�X�ԍ�
				}

				if (strcmp(aComment, "MAPMOVEVALUE") == 0)
				{// MAPMOVEVALUE��������}�b�v�ړ��ʓǂݍ���

					fscanf(pFile, "%s", &aComment[0]);	// =�̕�
					fscanf(pFile, "%f", &m_ChaseChangeInfo[m_nNumAll].fMapMoveValue);	// �}�b�v�ړ���
				}

				if (strcmp(aComment, "SPAWN_Y") == 0)
				{// SPAWN_Y��������o�������ǂݍ���

					fscanf(pFile, "%s", &aComment[0]);	// =�̕�
					fscanf(pFile, "%f", &m_ChaseChangeInfo[m_nNumAll].fSpawnPosY);	// �}�b�v�ړ���
				}

				if (strcmp(aComment, "RUSH") == 0)
				{// RUSH�������烉�b�V���p���ǂݍ���

					fscanf(pFile, "%s", &aComment[0]);	// =�̕�
					fscanf(pFile, "%d", &m_ChaseChangeInfo[m_nNumAll].nRush);	// ���b�V���p
				}

			}// END_BASESET�̂�����

			// �G�̋��_�����Z
			m_nNumAll++;
		}

		if (strcmp(&aComment[0], "END_SCRIPT") == 0)
		{// �I�������Ń��[�v�𔲂���

			break;
		}
	}

	return S_OK;
}

//==========================================================================
// �O���t�@�C�������o������
//==========================================================================
void CEnemyBase::Save(void)
{

	FILE *pFile = NULL;	// �t�@�C���|�C���^��錾

	// �t�@�C�����J��
	pFile = fopen("data\\TEXT\\enemybase.txt", "w");

	if (pFile == NULL)
	{// �t�@�C�����J���Ȃ������ꍇ
		return;
	}

	fprintf(pFile,
		"\n"
		"#==============================================================================\n"
		"# �G���_�̔z�u\n"
		"#==============================================================================\n");

	for (int i = 0; i < m_nNumAll; i++)
	{
		// �o��
		fprintf(pFile,
			"BASESET\n"
			"\tPATTERN = %d\n"
			"\tMAPIDX = %d\n"
			"\tMAPMOVEVALUE = %.2f\n"
			"\tSPAWN_Y = %.2f\n"
			"\tRUSH = %d\n"
			"END_BASESET\n\n",
			m_ChaseChangeInfo[i].nPattern,
			m_ChaseChangeInfo[i].nMapIdx,
			m_ChaseChangeInfo[i].fMapMoveValue,
			m_ChaseChangeInfo[i].fSpawnPosY,
			m_ChaseChangeInfo[i].nRush);
	}

	fprintf(pFile, "\nEND_SCRIPT		# ���̍s�͐�Ώ����Ȃ����ƁI");

	//�t�@�C�������
	fclose(pFile);
}

//==========================================================================
// �����擾
//==========================================================================
int CEnemyBase::GetAxisNum(void)
{
	return m_ChaseChangeInfo.size() - 1;
}

//==========================================================================
// ���擾
//==========================================================================
D3DXVECTOR3 CEnemyBase::GetAxis(int nIdx)
{
	if (nIdx < 0)
	{
		nIdx = 0;
	}

	D3DXVECTOR3 pos = mylib_const::DEFAULT_VECTOR3;

	if (nIdx >= (int)m_ChaseChangeInfo.size())
	{// �v�f���𒴂��Ă�����

		int nMaxIdx = (int)m_ChaseChangeInfo.size() - 1;
		return mylib_const::DEFAULT_VECTOR3;
	}

	// �}�b�v��񂩂�ʒu�擾
	pos = mylib_const::DEFAULT_VECTOR3;
	pos.y = m_ChaseChangeInfo[nIdx].fSpawnPosY;

	return pos;
}

//==========================================================================
// ���ݒ�
//==========================================================================
void CEnemyBase::SetSpawnPoint(int nIdx, int nMapIdx, float fMapMoveValue, float PosY)
{
	if (nIdx < 0)
	{
		return;
	}

	// ���n��
	m_ChaseChangeInfo[nIdx].nMapIdx = nMapIdx;
	m_ChaseChangeInfo[nIdx].fMapMoveValue = fMapMoveValue;
	m_ChaseChangeInfo[nIdx].fSpawnPosY = PosY;
}

//==========================================================================
// �ύX�̏��擾
//==========================================================================
CEnemyBase::sInfo CEnemyBase::GetChaseChangeInfo(int nIdx)
{
	sInfo InitInfo;
	memset(&InitInfo, NULL, sizeof(InitInfo));

	if (m_ChaseChangeInfo.size() <= 0 || (int)m_ChaseChangeInfo.size() <= nIdx)
	{// �T�C�Y����
		return InitInfo;
	}

	return m_ChaseChangeInfo[nIdx];
}
