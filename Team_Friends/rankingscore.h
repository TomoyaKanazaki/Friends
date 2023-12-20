//=============================================================================
// 
//  �����L���O�X�R�A�w�b�_�[ [rankingscore.h]
//  Author : ���{����
// 
//=============================================================================

#ifndef _RANKINGSCORE_H_
#define _RANKINGSCORE_H_	// ��d�C���N���[�h�h�~

#include "main.h"
#include "object.h"

//==========================================================================
// �}�N����`
//==========================================================================
#define RANKINGRANK_DIGIT	(2)	// ���ʌ���
#define RANKINGSCORE_DIGIT	(6)	// ����
#define RANKINGNUM	(20)	// ����
#define RANKING_DISPLAY_NUM	(5)	// �����\����
#define WINDOW_POPAPP_NUM	(12)	// 
#define POPAPP_TEX_NUM	(3)	// 

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
	void MovingScore(void);	// �ړ�����
	void MovingRank(void);	// �ړ�����
	void CreatePopApp(void);	// �ړ�����
	void ExpansionSize(int nCntWindow);	// �g�又��
	void ReductionSize(int nCntWindow);	// �k������
	static CRankingScore *Create(void);
private:

	enum VTX3D
	{
		VTX3D_VIRTUAL_WINDOW_00 = 0,
		VTX3D_VIRTUAL_WINDOW_01,
		VTX3D_SHADOE_00,
		VTX_LOGO,
		VTX_SCREEN,
		VTX3D_MAX
	};

	void Load(void);	// ���[�h
	void Save(void);	// �Z�[�u
	void Sort(void);	// �\�[�g

	void LoadPopAppInfo(void);	// ���[�h

	int m_nNumRanking;				// �����L���O��
	int m_nScore[RANKINGNUM];		// �X�R�A
	int m_nRank[RANKINGNUM];		// �X�R�A
	int m_nNowScore;		// ����̃X�R�A
	int m_nTexIdx3D[VTX3D_MAX];					// �e�N�X�`���̃C���f�b�N�X�ԍ�
	int m_nTexIdx3D_Win;					// �e�N�X�`���̃C���f�b�N�X�ԍ�
	int m_nTexIdxNumber;			// �����e�N�X�`���̃C���f�b�N�X�ԍ�
	int m_nIdxNewRecord;			// �j���[���R�[�h�̃C���f�b�N�X�ԍ�
	int m_nCntNewRecord;			// �j���[���R�[�h�̃J�E���^�[
	int m_nCnt;						// �n�߉��b���~�܂鏈��

	int m_nNumPA;					// �|�b�v�A�b�v�E�B���h�E�̐�
	int m_nCntCrePA;				// �����J�E���^�[
	int m_nCntDelPA[WINDOW_POPAPP_NUM];				// �폜�J�E���^�[
	int m_nCreSecPA;				// ��������b��
	int m_nDelSecPA[WINDOW_POPAPP_NUM];				// �폜����b��
	D3DXVECTOR3 m_nPASize[WINDOW_POPAPP_NUM];		// �|�b�v�A�b�v�E�B���h�E�̃T�C�Y
	D3DXVECTOR3 m_nPASizeKeep[WINDOW_POPAPP_NUM];	// �|�b�v�A�b�v�E�B���h�E�̃T�C�Y�̕ێ�
	float m_nPAMag[WINDOW_POPAPP_NUM];				// �|�b�v�A�b�v�E�B���h�E��XZ���W�̔{��
	float m_nPAHeight[WINDOW_POPAPP_NUM];			// �|�b�v�A�b�v�E�B���h�E�̍���

	float m_fPosDestY[RANKINGNUM];	// �ڕW�̈ʒu
	D3DXVECTOR3 m_fTexDest[WINDOW_POPAPP_NUM];	// �ڕW�̈ʒu

	bool m_bNewRecord;	// �j���[���R�[�h�̃t���O
	bool m_bArrival[RANKINGNUM];	// ��������
	bool m_b[WINDOW_POPAPP_NUM];	// �g�咆����
	bool m_bEnd;					// �X�R�A�I������

	CObject3D *m_pObj3D[VTX3D_MAX];	// �I�u�W�F�N�g3D�̃I�u�W�F�N�g
	CObject3D *m_pObj3D_Win[WINDOW_POPAPP_NUM];	// �I�u�W�F�N�g3D�̃I�u�W�F�N�g
	CMultiNumber *m_pScore[RANKINGNUM];			// �����̃I�u�W�F�N�g
	CMultiNumber *m_pRank[RANKINGNUM];			// ���ʂ̃I�u�W�F�N�g
	char *m_apTextureRank;						// �e�N�X�`���̃t�@�C��
	static const char *m_apTexture3DFile[VTX3D_MAX];	// �e�N�X�`���̃t�@�C��
	static const char *m_apTexture3D_WinFile[POPAPP_TEX_NUM];	// �|�b�v�A�b�v�e�N�X�`���̃t�@�C��
};



#endif