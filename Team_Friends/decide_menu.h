//==========================================================================
// 
//  人数選択メニュー(decide_menu.h)
//  Author : 橋本 賢太
// 
//==========================================================================
#ifndef _DECIDE_MENU_H_
#define _DECIDE_MENU_H_
#include "object.h"

//==========================================================================
//  前方宣言
//==========================================================================
class CObject3D;
class CPlayerTitle;
class CDecideDoor;
class CNumber;

//==========================================================================
//  クラス定義
//==========================================================================
class CDecideMenu : public CObject
{
public:

	// 列挙型定義
	enum VTX
	{
		VTX_TEXT = 0,	// UI
		VTX_MAX
	};

	// 列挙型定義
	enum VTX_UI
	{
		VTX_UI_ELECBORAD = 0,	// UI
		VTX_UI_MAX
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
	void Go(int nIdx); // 前に進む処理
	void Back(int nIdx); // 後ろに下がる処理

	// 静的メンバ関数
	static CDecideMenu* Create(void);
	static CPlayerTitle *GetPlayerTitle(int Cnt); // プレイヤーのポインタ配列

private:

	// メンバ関数
	void UpdateSelect(int nCntSelect);	// 選択肢の更新処理
	void CreateSelect(void); // 選択対象の生成
	void CretePlayer(void); // プレイヤーの生成
	void CreateNumber(void); // UIの生成
	void CreateElecboard(void); // UIの生成

	void SetValue(int nNowPlayer);

	// メンバ変数
	int m_nCntAlpha;		// 不透明度のカウンター
	int m_nNowSelect;		// 現在の選択肢
	int m_nTexIdx_Number;						// テクスチャのインデックス番号
	int m_nTexIdx_Elecborad[VTX_UI_MAX];		// テクスチャのインデックス番号
	int m_nTexIdx_Select;						// テクスチャのインデックス番号
	CNumber*m_pNumber3D[VTX_MAX];					// 数字のUIのオブジェクト
	CObject3D*m_pElecboard3D[VTX_MAX];					// 電光掲示板のUIのオブジェクト
	CObject3D*m_pObj3D[VTX_MAX];					// オブジェクト2Dのオブジェクト
	CObjectX*m_pSelectX[VTXSELECT_MAX];				// 選択肢のオブジェクト
	CDecideDoor *m_pDecideDoor;	// ドアのオブジェクト
	static CPlayerTitle *m_apPlayer[VTXSELECT_MAX]; // プレイヤーのポインタ配列
};

#endif
