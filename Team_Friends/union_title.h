//==========================================
//
//  �^�C�g���̍��̃��{(union_title.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _UNION_TITLE_H_
#define _UNION_TITLE_H_
#include "player_union.h"

//==========================================
//  �N���X��`
//==========================================
class CUnionTitle : public CPlayerUnion
{
public:

	CUnionTitle(int nPriority = mylib_const::PRIORITY_DEF2D);
	~CUnionTitle();

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	HRESULT CreateParts(void) override;	// �p�[�c�̐ݒ�

	//�ÓI�����o�֐�
	static CUnionTitle* Create(D3DXVECTOR3 pos);

};

#endif
