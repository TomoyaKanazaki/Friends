//=============================================================================
// 
//  メッシュウォールヘッダー [meshwall.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _MESHWALL_H_
#define _MESHWALL_H_	// 二重インクルード防止

#include "object3DMesh.h"

//==========================================================================
// クラス定義
//==========================================================================
// メッシュフィールドクラス定義
class CMeshWall : public CObject3DMesh
{
public:

	CMeshWall(int nPriority = 1);
	~CMeshWall();

	// オーバーライドされた関数
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void SetVtx(void);

	static CMeshWall *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidthLen, float fHeightLen, int nWidth = 1, int nHeight = 1, int nPriority = 1, const char *aFileName = NULL);
	virtual CMeshWall *GetMyObject(void);
protected:

private:
	int m_nTexIdx;	// テクスチャのインデックス番号
};



#endif