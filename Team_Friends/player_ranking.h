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
		a,
		b,
		c,
		d,
		BODYtoLEG, //
		MAX,
	};

	CPlayerRanking(int nPriority = mylib_const::DEF2D_PRIORITY);
	~CPlayerRanking();

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// �ÓI�����o�֐�
	static CPlayerRanking* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL type);

private:

	//�����o�ϐ�
	int m_nModelType;

};

#endif
