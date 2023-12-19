//=============================================================================
// 
//  アイテムマネージャヘッダー [itemmanager.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _ITEMMANAGER_H_
#define _ITEMMANAGER_H_	// 二重インクルード防止

#include "item.h"

// 前方宣言
class CItem;

//==========================================================================
// クラス定義
//==========================================================================
// アイテムのマネージャクラス定義
class CItemManager
{
public:

	CItemManager();
	~CItemManager();

	HRESULT Init(void);
	void Uninit(void);

	void Regist(CItem *pItem);			// 割り当て
	void Delete(CItem *pItem);			// 削除
	void KillAll(void);					// 全て削除
	int GetNumAll(void);				// アイテムの総数取得
	std::list<CItem*> GetList(void);	// アイテムのリスト取得
	static CItemManager *Create(void);

private:

	int m_nNumAll;		// アイテムの総数
	std::list<CItem*> m_ItemList;	// アイテムのリスト

};



#endif