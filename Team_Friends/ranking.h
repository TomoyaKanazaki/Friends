//=============================================================================
// 
//  �����L���O�w�b�_�[ [ranking.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _RANKING_H_
#define _RANKING_H_	// ��d�C���N���[�h�h�~

#include "main.h"
#include "manager.h"
#include "player_ranking.h"

//==========================================================================
// �O���錾
//==========================================================================
class CRankingScore;

//==========================================================================
// �N���X��`
//==========================================================================
// �����L���O�N���X��`
class CRanking : public CScene
{
public:

	CRanking();
	~CRanking();

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetEnableArrival(void);
	static int GetRandStage(void) { return m_nRandStage; }

	static CPlayerUnion *GetPlayerUnion(void);		// ���̃v���C���[�̃I�u�W�F�N�g

private:
	void UniCharCreate(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//���̃L�����̐���

	int m_nCntSwitch;		// �؂�ւ��̃J�E���^�[
	int m_nCntUniCharCre;		// ���̃L�����̐����J�E���^�[
	int m_nCntUniCharDel;		// ���̃L�����̐����J�E���^�[
	static bool m_bAllArrival;		// �S�ē�����������
	static int m_nRandStage;		// �X�e�[�W�̃����_���C���f�b�N�X�ԍ�
	static CRankingScore *m_pRankingScore;		// �����L���O�X�R�A�̃I�u�W�F�N�g
	static CPlayerUnion *m_pPlayerUnion;		// ���̃v���C���[�̃I�u�W�F�N�g

	static const char *m_apModelFile;		// ���f���̃t�@�C��

	CPlayerRanking::MODEL m_nType;
};



#endif