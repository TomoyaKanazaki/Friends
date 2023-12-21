//=============================================================================
// 
//  必殺のカットインヘッダー [ultcutin.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _ULTCUNTIN_H_
#define _ULTCUNTIN_H_	// 二重インクルード防止

#include "object2D_Anim.h"

//==========================================================================
// クラス定義
//==========================================================================
// 必殺のカットインクラス定義
class CUltCutin : public CObject2D_Anim
{
public:

	CUltCutin(int nPriority = 8);
	~CUltCutin();

	// オーバーライドされた関数
	HRESULT Init(void) override;
	void Update(void) override;
	void Draw(void) override;

	static CUltCutin *Create(void);	// 生成処理
	static void LoadTexture(void);	// テクスチャ読み込み
private:

	// メンバ変数
	static int m_nTexIdx;	// テクスチャのインデックス番号
};



#endif