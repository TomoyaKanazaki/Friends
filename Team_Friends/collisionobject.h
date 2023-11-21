//=============================================================================
// 
// 当たり判定オブジェクト処理 [collisionobject.h]
// Author : 相馬靜雅
// 
//=============================================================================

#ifndef _COLLISIONOBJECT_H_
#define _COLLISIONOBJECT_H_		// 二重インクルード防止のマクロを定義する

#include "objectBillboard.h"

//==========================================================================
// クラス定義
//==========================================================================
// 当たり判定オブジェクトクラス定義
class CCollisionObject : public CObjectBillboard
{
public:

	CCollisionObject(int nPriority = 5);
	~CCollisionObject();

	static CCollisionObject *Create(void);
	static CCollisionObject *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fRadius, const int nLife);

	//  オーバーライドされた関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetVtx(void);

	static int GetNumAll(void);	// 総数取得

private:

	// メンバ変数
	float m_fRadius;		// 半径
	int m_nLife;			// 寿命
	int m_nMaxLife;			// 最大寿命(固定)
	int m_nParentIdx;		// 親のインデックス番号
};

#endif