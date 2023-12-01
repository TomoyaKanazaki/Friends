//=============================================================================
// 
//  �����L���O�X�R�A�w�b�_�[ [rankingscore.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _RANKINGSCORE_H_
#define _RANKINGSCORE_H_	// ��d�C���N���[�h�h�~

#include "main.h"
#include "object.h"

//==========================================================================
// �}�N����`
//==========================================================================
#define RANKINGSCORE_DIGIT	(6)	// ����
#define RANKINGNUM	(20)	// ����
#define RANKING_DISPLAY_NUM	(5)	// ����

//==========================================================================
// �O���錾
//==========================================================================
class CMultiNumber;

//==========================================================================
// �N���X��`
//==========================================================================
// �����L���O�X�R�A�N���X��`
class CRankingScore : public CObject
{
public:

	CRankingScore(int nPriority = 7);
	~CRankingScore();

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetAllArrival(void);	// �S�Ă̓����ݒ�
	void UpdateNewRecord(void);	// �j���[���R�[�h�̍X�V����
	void SetValue(void);	// �l�̐ݒ菈��
	void Moving(void);	// �ړ�����
	static CRankingScore *Create(void);
private:

	enum VTX3D
	{
		VTX_NUM = 0,		// ���U���g���S
		VTX3D_VIRTUAL_WINDOW_00,
		VTX3D_VIRTUAL_WINDOW_01,
		VTX3D_SHADOE_00,
		VTX_LOGO,
		VTX3D_MAX
	};

	void Load(void);	// ���[�h
	void Save(void);	// �Z�[�u
	void Sort(void);	// �\�[�g
	
	int m_nNumRanking;				// �����L���O��
	int m_nScore[RANKINGNUM];		// �X�R�A
	int m_nNowScore;		// ����̃X�R�A
	int m_nTexIdx3D[VTX3D_MAX];					// �e�N�X�`���̃C���f�b�N�X�ԍ�
	int m_nTexIdxNumber;			// �����e�N�X�`���̃C���f�b�N�X�ԍ�
	int m_nIdxNewRecord;			// �j���[���R�[�h�̃C���f�b�N�X�ԍ�
	int m_nCntNewRecord;			// �j���[���R�[�h�̃J�E���^�[
	float m_fPosDestX[RANKINGNUM];	// �ڕW�̈ʒu
	bool m_bNewRecord;				// �j���[���R�[�h�̃t���O
	bool m_bArrival[RANKINGNUM];	// ��������
	CObject3D *m_pObj3D[VTX3D_MAX];	// �I�u�W�F�N�g2D�̃I�u�W�F�N�g
	CMultiNumber *m_pScore[RANKINGNUM];			// �����̃I�u�W�F�N�g
	static const char *m_apTexture3DFile[VTX3D_MAX];	// �e�N�X�`���̃t�@�C��
};



#endif