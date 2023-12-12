//==========================================
//
//  タイトルロゴ管理クラス(title_logo.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TITLE_LOGO_H_
#define _TITLE_LOGO_H_
#include "object.h"

//==========================================
//  前方宣言
//==========================================
class CLogo_Mech;
class CLogo_Meka;
class CLogo_Sqou;
class CLogo_Comp;

//==========================================
//  クラス定義
//==========================================
class CTitleLogo : public CObject
{
public:

	// ロゴの更新状態列挙
	enum STATE
	{
		DEFAULT = 0, //アルファベットのみがある状態
		WAKE, //カタカナが起き上がる
		FLASH, //戦隊が点滅する
		COMPLETE, //完成！！
		STARTUP, // 起動
		MAX, //総数
		NONE //NULLLLLLLLL
	};

	//メンバ関数
	CTitleLogo();
	~CTitleLogo();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	bool GetComplete() { return m_bComplete; }

	void SetState(STATE state);	// 状態設定

	//静的メンバ関数
	static CTitleLogo* Create();

private:

	//メンバ変数
	CLogo_Mech* m_pMech;
	CLogo_Meka* m_pMeka;
	CLogo_Sqou* m_pSqou;
	CLogo_Comp* m_pComp;
	STATE m_State;
	bool m_bComplete;

	//メンバ関数
	void UpdateState();

};

#endif
