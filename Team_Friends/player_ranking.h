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
		ARMtoARM = 0, //
		BODYtoLEG,
		BODYtoARM,
		LEGtoARM,
		MAX,
	};

	CPlayerRanking(int nPriority = mylib_const::DEF2D_PRIORITY);
	CPlayerRanking(MODEL nType, int nPriority = mylib_const::DEF2D_PRIORITY);
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

	void BODYtoLEGMove(void);
	void BODYtoARMMove(void);
	void LEGtoARMMove(void);
	void ARMtoARMMove(void);

	//�����o�ϐ�
	int m_nModelType;
	MODEL m_nType;

	int m_nCntSwitch;		// �؂�ւ��̃J�E���^�[
	int m_nMovePtaCnt;
	int m_nSpinCnt;
	bool m_bRight;
	bool m_bLeft;
	bool m_bOldLeft;

};

#endif
