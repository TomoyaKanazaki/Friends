//==========================================
//
//  メカニオンのロゴ(logo_mekanion.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MEKANION_H_
#define _MEKANION_H_
#include "object3D.h"

//==========================================
//  クラス定義
//==========================================
class CLogo_Meka : public CObject3D
{
public:

	//メンバ関数
	CLogo_Meka();
	~CLogo_Meka();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CLogo_Meka* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

	//静的メンバ変数
	static const char* m_pTextureFile[2]; //テクスチャのファイル
};

#endif
