//========================================
// 
// リストの処理
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ list.cpp ]]]
//========================================
#include "../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CListクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
// Author:RIKU NISHIMURA
//========================================
CList::CList(void) {
	m_pPrev   = NULL;
	m_pNext   = NULL;
	m_bDelete = false;
}

//========================================
// デストラクタ
// Author:RIKU NISHIMURA
//========================================
CList::~CList(void) {

}

//========================================
// 解放処理
// Author:RIKU NISHIMURA
//========================================
void CList::Release(void) {
	m_bDelete = true;
}