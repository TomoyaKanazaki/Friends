//=============================================================================
// 
// ステータスアップ処理 [statusup.h]
// Author : 相馬靜雅
// 
//=============================================================================

#ifndef _STATUSUP_H_
#define _STATUSUP_H_		// 二重インクルード防止のマクロを定義する

#include "objectBillboard.h"
#include "gamemanager.h"

//==========================================================================
// クラス定義
//==========================================================================
// ステータスアップクラス定義
class CStatusUp : public CObjectBillboard
{
public:

	CStatusUp(int nPriority = mylib_const::PRIORITY_ZSORT);
	~CStatusUp();

	//  オーバーライドされた関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CStatusUp *Create(const D3DXVECTOR3 pos, CGameManager::eStatus type);
	static void LoadTexture(void);	// テクスチャ読み込み

private:

	// メンバ関数
	void UpdateMove(void);	// 移動処理

	// メンバ関数
	int m_nLife;	// 寿命
	CGameManager::eStatus m_type;	// 種類
	static int m_nTexIdx[CGameManager::STATUS_MAX];	// テクスチャのインデックス番号
};

#endif