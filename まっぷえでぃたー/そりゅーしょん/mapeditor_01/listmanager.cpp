//==========================================================================
//
// リストマネージャの処理[listmanager.cpp]
// Author：相馬靜雅
//
//==========================================================================
#include "listmanager.h"
#include "list.h"

//==========================================================================
// マクロ定義
//==========================================================================

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================

//==========================================================================
// コンストラクタ
//==========================================================================
CListManager::CListManager()
{
	// 値のクリア
	m_pTop = NULL;	// 先頭のオブジェクトへのポインタ
	m_pCur = NULL;	// 最後尾のオブジェクトへのポインタ
	m_nNumAll = 0;	// 総数
}

//==========================================================================
// デストラクタ
//==========================================================================
CListManager::~CListManager()
{

}

//==========================================================================
// 生成処理
//==========================================================================
CListManager *CListManager::Create(void)
{
	// 生成用のオブジェクト
	CListManager *pListManager = NULL;

	if (pListManager == NULL)
	{// NULLだったら

		// メモリの確保
		pListManager = DEBUG_NEW CListManager;
		return pListManager;
	}

	return NULL;
}

//==========================================================================
// 全ての開放処理
//==========================================================================
void CListManager::ReleaseAll(void)
{

}

//==========================================================================
// オブジェクト追加
//==========================================================================
void CListManager::Push(CList *pObj)
{
	if (m_pCur != NULL)
	{// 最後尾が存在していたら

		m_pCur->SetNext(pObj);		// 最後尾の次に自分自身を代入

		pObj->SetPrev(m_pCur);		// 自分の前を最後尾にする
		pObj->SetNext(NULL);		// 自分の次をNULLにする

		m_pCur = pObj;				// 最後尾を自分自身に更新
	}
	else
	{// 最後尾が無かったら

		m_pCur = pObj;	// 最後尾を自分自身に更新

		pObj->SetPrev(NULL);	// 自分の前をNULLにする
		pObj->SetNext(NULL);	// 自分の次をNULLにする
	}

	if (m_pTop == NULL)
	{// 先頭に何もなかったら

		m_pTop = pObj;	// 先頭に自分自身のポインタを渡す
	}
}

//==========================================================================
// オブジェクトを取り出す
//==========================================================================
void CListManager::Pop(CList *pObj)
{
	// オブジェクトを保存
	CList *pObject = pObj;
	CList *pObjNext = pObject->GetNext();
	CList *pObjPrev = pObject->GetPrev();

	if (pObject == NULL)
	{// NULLだったら
		return;
	}

	// 前のオブジェクトと次のオブジェクトを繋ぐ
	if (pObjNext == NULL)
	{// 自分が最後尾の時

		if (pObjPrev != NULL)
		{// 前のオブジェクトがあれば

			// 前のオブジェクトの次をNULLにする
			pObjPrev->SetNext(NULL);

			// 最後尾を自分の前のオブジェクトにする
			m_pCur = pObjPrev;
		}
		else
		{// 前のオブジェクトがない時

			// 最後尾をNULLにする
			m_pCur = NULL;
		}
	}
	else
	{// 最後尾じゃないとき

		if (pObjPrev != NULL)
		{// 自分が先頭じゃない時

			// 前のオブジェクトの次を, 自分の次にする
			pObjPrev->SetNext(pObject->GetNext());
		}

	}

	if (pObjPrev == NULL)
	{// 自分が先頭の時

		if (pObjNext != NULL)
		{// 次のオブジェクトがある時

			// 次のオブジェクトの前をNULLにする
			pObjNext->SetPrev(NULL);

			// 先頭を自分の次のオブジェクトにする
			m_pTop = pObjNext;
		}
		else
		{// 次のオブジェクトがない時

			// 先頭をNULLにする
			m_pTop = NULL;
		}
	}
	else
	{// 先頭じゃないとき

		if (pObjNext != NULL)
		{// 自分が最後尾じゃない時

			// 次のオブジェクトの前を, 自分の前にする
			pObjNext->SetPrev(pObject->GetPrev());
		}
	}

	// メモリの開放
	pObject->Release();
	pObject = NULL;

	// 総数を減らす
	m_nNumAll--;
}

//==========================================================================
// 先頭のオブジェクト取得
//==========================================================================
CList *CListManager::GetTop(void)
{
	return m_pTop;
}
