//=============================================================================
// 
//  �v���C���[�w�b�_�[ [player_title.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _PLAYER_TITLE_H_
#define _PLAYER_TITLE_H_	// ��d�C���N���[�h�h�~

#include "player.h"

//==========================================================================
// �}�N����`
//==========================================================================

//==========================================================================
// �N���X��`
//==========================================================================
// �v���C���[�N���X��`
class CPlayerTitle : public CPlayer
{
public:

	CPlayerTitle(int nPriority = mylib_const::DEF2D_PRIORITY);
	~CPlayerTitle();


	// �I�[�o�[���C�h���ꂽ�֐�
	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	void Draw(void) override;

protected:

private:

	// �����o�֐�

	// �����o�ϐ�
};



#endif