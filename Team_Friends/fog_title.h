//==========================================
//
//  タイトルでのフォグの処理(fog_title.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _FOG_TITLE_H_
#define _FOG_TITLE_H_
#include "object.h"

//==========================================
//  クラス定義
//==========================================
class CFog_Title : public CObject
{
public:

	//メンバ変数
	CFog_Title();
	~CFog_Title();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	//静的メンバ関数
	static CFog_Title* Create();

private:

	// メンバ変数
	D3DXCOLOR m_col;
	float m_fLength;

};

#endif
