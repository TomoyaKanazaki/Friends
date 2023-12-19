//=============================================================================
// 
//  �A�C�e���}�l�[�W���w�b�_�[ [itemmanager.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _ITEMMANAGER_H_
#define _ITEMMANAGER_H_	// ��d�C���N���[�h�h�~

#include "item.h"

// �O���錾
class CItem;

//==========================================================================
// �N���X��`
//==========================================================================
// �A�C�e���̃}�l�[�W���N���X��`
class CItemManager
{
public:

	CItemManager();
	~CItemManager();

	HRESULT Init(void);
	void Uninit(void);

	void Regist(CItem *pItem);			// ���蓖��
	void Delete(CItem *pItem);			// �폜
	void KillAll(void);					// �S�č폜
	int GetNumAll(void);				// �A�C�e���̑����擾
	std::list<CItem*> GetList(void);	// �A�C�e���̃��X�g�擾
	static CItemManager *Create(void);

private:

	int m_nNumAll;		// �A�C�e���̑���
	std::list<CItem*> m_ItemList;	// �A�C�e���̃��X�g

};



#endif