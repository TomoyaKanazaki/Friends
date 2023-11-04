//=============================================================================
// 
//  �G�̋��_�w�b�_�[ [enemybase.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _ENEMYBASE_H_
#define _ENEMYBASE_H_	// ��d�C���N���[�h�h�~

#include "main.h"
#include "constans.h"
#include "object.h"

//==========================================================================
// �O���錾
//==========================================================================
class CDebugPointNumber;

//==========================================================================
// �N���X��`
//==========================================================================
// �J�����̎��N���X��`
class CEnemyBase
{
public:

	// �\���̒�`
	struct sInfo
	{
		int nPattern;			// ���
		int nMapIdx;			// �}�b�v�C���f�b�N�X
		float fMapMoveValue;	// �}�b�v�̈ړ���
		float fSpawnPosY;		// �o���̍���
		int nRush;				// ���b�V���p���ǂ���
	};

	CEnemyBase();
	~CEnemyBase();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void CreatePos(int nPattern, int nMapIdx, float fMapMoveValue, int nRush, float PosY);	// �ʒu�쐬
	void DeletePos(int nIdx);					// �ʒu�폜
	HRESULT ReadText(const char *pFileName);	// �O���t�@�C���ǂݍ��ݏ���
	void Save(void);			// �O���t�@�C�������o������

	static CEnemyBase *Create(const char *pFileName);
	int GetAxisNum(void);			// �����擾
	D3DXVECTOR3 GetAxis(int nIdx);	// ���擾
	void SetSpawnPoint(int nIdx, int nMapIdx, float fMapMoveValue, float PosY);	// ���ݒ�
	sInfo GetChaseChangeInfo(int nIdx);	// �ύX�̏��擾
	static int GetNumAll(void) { return m_nNumAll; }	// �����擾
private:

	std::vector<sInfo> m_ChaseChangeInfo;		// �Ǐ]�ύX�̏��
	CObjectX *m_apObjX[mylib_const::MAX_CAMERAAXIS];	// �I�u�W�F�N�gX
	CDebugPointNumber *m_pMultiNumber[mylib_const::MAX_CAMERAAXIS];

	static int m_nNumAll;		// ����
};



#endif