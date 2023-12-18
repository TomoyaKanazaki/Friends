//=============================================================================
// 
// �X�e�[�^�X�A�b�v���� [statusup.h]
// Author : ���n�Ή�
// 
//=============================================================================

#ifndef _STATUSUP_H_
#define _STATUSUP_H_		// ��d�C���N���[�h�h�~�̃}�N�����`����

#include "objectBillboard.h"
#include "gamemanager.h"

//==========================================================================
// �N���X��`
//==========================================================================
// �X�e�[�^�X�A�b�v�N���X��`
class CStatusUp : public CObjectBillboard
{
public:

	CStatusUp(int nPriority = mylib_const::PRIORITY_ZSORT);
	~CStatusUp();

	//  �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CStatusUp *Create(const D3DXVECTOR3 pos, CGameManager::eStatus type);
	static void LoadTexture(void);	// �e�N�X�`���ǂݍ���

private:

	// �����o�֐�
	void UpdateMove(void);	// �ړ�����

	// �����o�֐�
	int m_nLife;	// ����
	CGameManager::eStatus m_type;	// ���
	static int m_nTexIdx[CGameManager::STATUS_MAX];	// �e�N�X�`���̃C���f�b�N�X�ԍ�
};

#endif