#pragma once
//=============================================================================
// 
//  �v���C���[�w�b�_�[ [player_title.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _PLAYER_RANKING_H_
#define _PLAYER_RANKING_H_	// ��d�C���N���[�h�h�~

#include "player_union.h"

//==========================================================================
// �N���X��`
//==========================================================================
// �v���C���[�N���X��`
class CPlayerRanking : public CPlayerUnion
{
public:

	//�^�C�v
	enum MODEL
	{
		BODYtoLEG,
		BODYtoARM,
		LEGtoARM,
		ARMtoARM, //
		MAX,
	};

	enum MOVE
	{
		PTN_NONE = 0,
		PTN_01,
		PTN_02,
		PTN_MAX,
	};

	CPlayerRanking(int nPriority = mylib_const::PRIORITY_DEF2D);
	CPlayerRanking(MODEL nType, int nPriority = mylib_const::PRIORITY_DEF2D);
	~CPlayerRanking();

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CPlayerUnion* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL type);
	virtual HRESULT CreateParts(void) override;

private:

	void MovePtn01(void);
	void MovePtn02(void);

	//�����o�ϐ�
	int m_nModelType;
	MODEL m_nType;
	MOVE m_nTypeMove;
	
	int m_nCntSwitch;		// �؂�ւ��̃J�E���^�[
	int m_nMovePtaCnt;
	int m_nSpinCnt;
	int m_nStopCnt;
	bool m_bRight;
	bool m_bLeft;
	bool m_bOldLeft;
	bool m_bAtkMotion;
	bool m_bReMove;

};

#endif
