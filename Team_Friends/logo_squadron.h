//==========================================
//
//  戦隊のロゴ(logo_squadron.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SQUADRON_H_
#define _SQUADRON_H_
#include "object3D.h"

//==========================================
//  クラス定義
//==========================================
class CLogo_Sqou : public CObject3D
{
public:

	//メンバ関数
	CLogo_Sqou();
	~CLogo_Sqou();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CLogo_Sqou* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

	//静的メンバ変数
	static const char* m_pTextureFile; //テクスチャのファイル
};

#endif
