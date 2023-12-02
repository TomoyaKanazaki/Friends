//=============================================================================
// 
//  ビーム処理 [beam.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "beam.h"
#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "calculation.h"
#include "3D_effect.h"

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================

//==========================================================================
// コンストラクタ
//==========================================================================
CBeam::CBeam(int nPriority) : CObject(nPriority)
{
	m_fRadius = 0.0f;	// 半径
	m_fLength = 0.0f;	// 長さ
	m_nLife = 0;		// 寿命
	m_nDisity = 0;		// 密度
	m_col = mylib_const::DEFAULT_COLOR;	// 色
}

//==========================================================================
// デストラクタ
//==========================================================================
CBeam::~CBeam()
{
	
}

//==========================================================================
// 生成処理
//==========================================================================
CBeam *CBeam::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXCOLOR col, const float fRadius, const float fLength, const int nLife, const int nDisity)
{
	// 生成用のオブジェクト
	CBeam *pBallast = NULL;

	if (pBallast == NULL)
	{// NULLだったら

		// メモリの確保
		pBallast = DEBUG_NEW CBeam;

		if (pBallast != NULL)
		{// メモリの確保が出来ていたら

			pBallast->m_fRadius = fRadius;	// 半径
			pBallast->m_fLength = fLength;	// 長さ
			pBallast->m_nLife = nLife;		// 寿命
			pBallast->SetPosition(pos);		// 位置
			pBallast->SetMove(move);		// 移動量
			pBallast->m_col = col;			// 色
			pBallast->m_nDisity = nDisity;	// 密度

			// 初期化処理
			HRESULT hr = pBallast->Init();
			if (FAILED(hr))
			{
				return NULL;
			}
		}

		return pBallast;
	}

	return NULL;
}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CBeam::Init(void)
{
	// 種類の設定
	SetType(TYPE_OBJECT3D);

	// 位置取得
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 vecmove = move - mylib_const::DEFAULT_VECTOR3;

	// ベクトルを正規化
	D3DXVec3Normalize(&vecmove, &vecmove);

	float fDistance = m_fLength / (float)m_nDisity;
	float fLen = 0.0f;
	for (int nCntBallast = 0; nCntBallast < m_nDisity; nCntBallast++)
	{
		// 生成処理
		CEffect3D::Create(
			pos + vecmove * fLen,
			move,
			m_col,
			m_fRadius,
			m_nLife,
			CEffect3D::MOVEEFFECT_SUB,
			CEffect3D::TYPE_NORMAL,
			0.0f);

		// 距離加算
		fLen += fDistance;
	}

	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CBeam::Uninit(void)
{
	// 情報削除
	Release();
}

//==========================================================================
// 更新処理
//==========================================================================
void CBeam::Update(void)
{
	
}

//==========================================================================
// 描画処理
//==========================================================================
void CBeam::Draw(void)
{
	
}
