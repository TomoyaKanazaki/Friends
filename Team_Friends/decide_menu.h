//==========================================
// 
//  人数選択メニュー(decide_menu.h)
//  Author : Tomoya Kanazaki
// 
//==========================================
#ifndef _DECIDE_MENU_H_
#define _DECIDE_MENU_H_
#include "object.h"

//==========================================
//  前方宣言
//==========================================
class CObject3D;

//==========================================
//  クラス定義
//==========================================
class CDecideMenu : public CObject
{
public:

	// 列挙型定義
	enum VTX
	{
		VTX_TEXT = 0,	// UI
		VTX_WALL, // 壁
		VTX_MAX
	};

	// 列挙型定義
	enum VTXSELECT
	{
		VTXSELECT_SELECT1P = 0,	// 1P
		VTXSELECT_SELECT2P,		// 2P
		VTXSELECT_SELECT3P,		// 3P
		VTXSELECT_SELECT4P,		// 4P
		VTXSELECT_MAX
	};

	// メンバ関数
	CDecideMenu(int nPriority = 8);
	~CDecideMenu();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CDecideMenu* Create(void);

private:

	// メンバ関数
	void UpdateSelect(int nCntSelect);	// 選択肢の更新処理
	void CreateUI(void); // UIの生成
	void CreateSelect(void); // 選択対象の生成

	// メンバ変数
	int m_nCntAlpha;		// 不透明度のカウンター
	int m_nNowSelect;		// 現在の選択肢
	int m_nTexIdx[VTX_MAX];						// テクスチャのインデックス番号
	int m_nTexIdx_Select[VTXSELECT_MAX];						// テクスチャのインデックス番号
	CObject3D*m_pObj3D[VTX_MAX];					// オブジェクト2Dのオブジェクト
	CObject3D*m_pSelect3D[VTXSELECT_MAX];				// 選択肢のオブジェクト
};

#endif
