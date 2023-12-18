//==========================================
// 
//  人数選択メニュー(decide_menu.h)
//  Author : Tomoya Kanazaki
// 
//==========================================
#ifndef _DECIDE_DOOR_H_
#define _DECIDE_DOOR_H_
#include "object.h"

//==========================================
//  前方宣言
//==========================================
class CObject3D;
class CPlayerTitle;

//==========================================
//  クラス定義
//==========================================
class CDecideDoor : public CObject
{
public:

	// 列挙型定義
	enum MODEL
	{
		VTX_FREAM = 0,	// 枠
		VTX_MAX
	};

	// 列挙型定義
	enum MODELSELECT
	{
		MODELSELECT_DOOR_1 = 0,	// 1P
		MODELSELECT_DOOR_2,		// 2P
		MODELSELECT_DOOR_3,		// 3P
		MODELSELECT_DOOR_4,		// 4P
		MODELSELECT_MAX
	};

	// メンバ関数
	CDecideDoor(int nPriority = 8);
	~CDecideDoor();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

						 // 静的メンバ関数
	static CDecideDoor* Create(void);

private:

	// メンバ関数
	void UpdateSelect(int nCntSelect);	// 選択肢の更新処理
	void CreateSelect(void); // 選択対象の生成

							// メンバ変数
	int m_nNowSelect;		// 現在の選択肢
	int m_nTexIdx_Select[MODELSELECT_MAX];						// テクスチャのインデックス番号
	CObjectX *m_pObjX[VTX_MAX];							// オブジェクト2Dのオブジェクト
	CObjectX *m_pSelectX[MODELSELECT_MAX];				// 選択肢のオブジェクト
};

#endif
