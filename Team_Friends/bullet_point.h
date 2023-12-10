//=============================================================================
// 
//  弾の着弾地点 [bullet_point.h]
//  Author : 髙田佳依
// 
//=============================================================================

#ifndef _BULLET_POINT_H_
#define _BULLET_POINT_H_	// 二重インクルード防止

#include "main.h"
#include "object3D.h"

//==========================================================================
// クラス定義
//==========================================================================
class CBulletPoint : public CObject3D
{
public:
	CBulletPoint(int nPriority = 7);
	~CBulletPoint();

	static CBulletPoint *Create();
	static CBulletPoint *Create(D3DXVECTOR3 pos, float size = 100.0f);

	// オーバーライドされた関数ああ
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static int GetNumAll(void);

private:

	CObject *m_pObject;		// オブジェクトのポインタ
	static int m_nNumAll;	// 総数
	int m_nTexIdx;			// テクスチャのインデックス番号
};

#endif