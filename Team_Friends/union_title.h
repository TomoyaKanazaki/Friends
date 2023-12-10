//==========================================
//
//  タイトルの合体ロボ(union_title.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _UNION_TITLE_H_
#define _UNION_TITLE_H_
#include "player_union.h"

//==========================================
//  クラス定義
//==========================================
class CUnionTitle : public CPlayerUnion
{
public:

	CUnionTitle(int nPriority = mylib_const::PRIORITY_DEF2D);
	~CUnionTitle();

	// オーバーライドされた関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	HRESULT CreateParts(void) override;	// パーツの設定

	//静的メンバ関数
	static CUnionTitle* Create(D3DXVECTOR3 pos);

	// その他関数
	void SetEnablePressEnter(void) { m_bPressEnter = true; }	// エンター押下判定有効
	bool IsPressEnter(void) { return m_bPressEnter; }			// エンター押下判定取得
private:

	// 列挙型定義
	enum MOTION
	{
		MOTION_DEF = 0,	// ニュートラルモーション
		MOTION_STARTUP,	// 起動モーション
		MOTION_MAX
	};

	// メンバ関数
	void AttackAction(int nIdx, int nModelNum, CMotion::AttackInfo ATKInfo) override;	// 攻撃時処理

	// メンバ変数
	bool m_bPressEnter;	// エンターの押下判定
};

#endif
