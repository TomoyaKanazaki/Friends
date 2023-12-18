//=============================================================================
// 
//  合体のコアヘッダー [unioncore.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _UNIONCORE_H_
#define _UNIONCORE_H_	// 二重インクルード防止

#include "objectX.h"

//==========================================================================
// クラス定義
//==========================================================================
// 合体のコアクラス定義
class CUnionCore : public CObjectX
{
public:

	CUnionCore(int nPriority = 6);
	~CUnionCore();

	// オーバーライドされた関数
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void SetUp(D3DXVECTOR3 setup, D3DXMATRIX *pMtxParent);
	static CUnionCore *Create(const D3DXVECTOR3 pos);

private:
	
	int m_nCntEmission;			// 発生物のカウンター
	D3DXVECTOR3 m_setupPosition;	// セットアップ位置
	D3DXMATRIX *m_pMtxParent;	// 親マトリックスのポインタ
	bool m_bSetUp;				// セットアップ判定
};


#endif