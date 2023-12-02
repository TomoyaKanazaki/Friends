//=============================================================================
// 
//  ビームヘッダー [beam.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _BEAM_H_
#define _BEAM_H_	// 二重インクルード防止

#include "object.h"

//==========================================================================
// 前方宣言
//==========================================================================
class CEffect3D;

namespace
{
	const int DENSITY_BEAM = 12;	// ビームの密度
}

//==========================================================================
// クラス定義
//==========================================================================
// ビームクラス定義
class CBeam : public CObject
{
public:

	CBeam(int nPriority = mylib_const::PRIORITY_DEFAULT);
	~CBeam();

	// オーバーライドされた関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	static CBeam *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXCOLOR col, const float fRadius, const float fLength, const int nLife, const int nDisity = DENSITY_BEAM);

private:

	float m_fRadius;	// 半径
	float m_fLength;	// 長さ
	int m_nLife;		// 寿命
	int m_nDisity;		// 密度
	D3DXCOLOR m_col;	// 色
};


#endif