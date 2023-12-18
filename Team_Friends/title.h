//=============================================================================
// 
//  タイトルヘッダー [title.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _TITLE_H_
#define _TITLE_H_	// 二重インクルード防止

#include "main.h"
#include "manager.h"

//==========================================
//  前方宣言
//==========================================
class CTitleLogo;
class CUnionTitle;
class CPlayerTitle;

//==========================================================================
// クラス定義
//==========================================================================
// タイトルクラス定義
class CTitle : public CScene
{
public:

	CTitle();
	~CTitle();

	// オーバーライドされた関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetEnablePressEnter(void) { m_bPressEnter = true; }	// エンター押下判定有効
	static bool IsPressEnter(void) { return m_bPressEnter; }			// エンター押下判定取得

private:

	// メンバ関数
	void WhiteOut();

	// メンバ変数
	D3DXCOLOR m_col;
	float m_fLength;

	float m_fCnt;		// 切り替えのカウンター
	int m_nCntEmission;	// 発生物カウンター
	CTitleLogo *m_pLogo;
	CUnionTitle *m_pUnionTitle;	// タイトルの合体プレイヤーオブジェクト
	static bool m_bPressEnter;			// エンター押下判定
	CPlayerTitle* m_apPlayer[4]; // プレイヤーのポインタ配列

};



#endif