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
#include "collisionobject.h"
#include "camera.h"
#include "particle.h"
#include "ballast.h"

//==========================================================================
// 無名名前空間
//==========================================================================
namespace
{
	float radius;		// 半径
	float length;		// 長さ
	int disity;			// 密度
	int damage;			// ダメージ
	D3DXCOLOR color;	// 色
	std::vector<CEffect3D*> effect;	// エフェクトのオブジェクト
}

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================

//==========================================================================
// コンストラクタ
//==========================================================================
CBeam::CBeam(int nPriority) : CObject(nPriority)
{

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
CBeam *CBeam::Create(
	const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXCOLOR col,
	const float fRadius, const float fLength, const int nLife, const int nDisity, const int nDamage)
{
	// 生成用のオブジェクト
	CBeam *pBallast = NULL;

	if (pBallast == NULL)
	{// NULLだったら

		// メモリの確保
		pBallast = DEBUG_NEW CBeam;

		if (pBallast != NULL)
		{// メモリの確保が出来ていたら

			radius = fRadius;			// 半径
			length = fLength;			// 長さ
			pBallast->m_nLife = nLife;	// 寿命
			pBallast->SetPosition(pos);	// 位置
			pBallast->SetMove(move);	// 移動量
			color = col;				// 色
			disity = nDisity;			// 密度
			damage = nDamage;			// ダメージ

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

	float fDistance = length / (float)disity;
	float fLen = 0.0f;
	for (int nCntBallast = 0; nCntBallast < disity; nCntBallast++)
	{
		// 生成処理
		CEffect3D *pEffect = CEffect3D::Create(
			pos + vecmove * fLen,
			move,
			color,
			radius,
			m_nLife,
			CEffect3D::MOVEEFFECT_SUB,
			CEffect3D::TYPE_NORMAL,
			0.0f);

		// エフェクト追加
		effect.push_back(pEffect);

		// 当たり判定オブジェクト生成
		//CCollisionObject::Create(pos + vecmove * fLen, move, radius, life, damage, CCollisionObject::TAG_PLAYER);

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
	// 要素全削除
	effect.clear();

	// 情報削除
	Release();
}

//==========================================================================
// 更新処理
//==========================================================================
void CBeam::Update(void)
{
	// 寿命減算
	m_nLife--;

	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}

	for (int i = 0; i < static_cast<int>(effect.size()); i++)
	{
		if (effect[i] == nullptr)
		{
			continue;
		}

		// 位置取得
		D3DXVECTOR3 pos = effect[i]->GetPosition();

		if (CGame::GetElevation()->IsHit(pos) == true)
		{
			// 振動
			CManager::GetInstance()->GetCamera()->SetShake(6, 4.0f, 0.0f);

			// 瓦礫
			CBallast::Create(pos, D3DXVECTOR3(2.0f, 6.0f, 2.0f), 1, 1.0f, CBallast::TYPE_STONE);

			// ビームヒットパーティクル
			my_particle::Create(pos, my_particle::TYPE_BEAMHIT_FIELD);

			effect[i]->Uninit();
			effect[i] = nullptr;

			// 着地したものを削除
			effect.erase(effect.begin() + i);
		}
	}
}

//==========================================================================
// 描画処理
//==========================================================================
void CBeam::Draw(void)
{
	
}
