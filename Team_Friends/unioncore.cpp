//=============================================================================
// 
//  合体のコア処理 [unioncore.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "unioncore.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"
#include "3D_effect.h"
#include "particle.h"
#include "calculation.h"
#include "scene.h"

//==========================================================================
// 無名名前空間
//==========================================================================
namespace
{
	const char* MODELFILE = "data\\MODEL\\compactcore_01.x";
}

//==========================================================================
// コンストラクタ
//==========================================================================
CUnionCore::CUnionCore(int nPriority) : CObjectX(nPriority)
{
	// 値のクリア
	m_nCntEmission = 0;		// 発生物のカウンター
	m_setupPosition = mylib_const::DEFAULT_VECTOR3;	// セットアップ位置
	m_pMtxParent = nullptr;	// 親マトリックスのポインタ
	m_bSetUp = false;		// セットアップ判定
}

//==========================================================================
// デストラクタ
//==========================================================================
CUnionCore::~CUnionCore()
{
	
}

//==========================================================================
// 生成処理
//==========================================================================
CUnionCore *CUnionCore::Create(const D3DXVECTOR3 pos)
{
	// 生成用のオブジェクト
	CUnionCore *pBullet = NULL;

	if (pBullet == NULL)
	{// NULLだったら

		// メモリの確保
		pBullet = DEBUG_NEW CUnionCore;

		if (pBullet != NULL)
		{// メモリの確保が出来ていたら

			// 位置割り当て
			pBullet->SetPosition(pos);

			// 初期化処理
			pBullet->Init();
		}

		return pBullet;
	}

	return NULL;
}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CUnionCore::Init(void)
{
	HRESULT hr;

	// 初期化処理
	hr = CObjectX::Init(MODELFILE);
	if (FAILED(hr))
	{// 失敗したとき
		return E_FAIL;
	}

	// 種類の設定
	CObject::SetType(TYPE_OBJECTX);

	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CUnionCore::Uninit(void)
{
	// 終了処理
	CObjectX::Uninit();
}

//==========================================================================
// 更新処理
//==========================================================================
void CUnionCore::Update(void)
{
	if (m_bSetUp)
	{
		D3DXMATRIX mtxTrans, mtxWorld;	// 計算用マトリックス宣言

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxWorld);

		// 位置を反映する
		D3DXMatrixTranslation(&mtxTrans, m_setupPosition.x, m_setupPosition.y, m_setupPosition.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

		// 自分に親のワールドマトリックスを掛ける
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, m_pMtxParent);

		SetPosition(WorldMtxChangeToPosition(mtxWorld));
	}

	// 発生物カウンター加算
	m_nCntEmission = (m_nCntEmission + 1) % 3;

	if (m_nCntEmission == 0)
	{
		D3DXVECTOR3 pos = GetPosition();
		float fMove = 2.5f + Random(-20, 20) * 0.1f;
		float fMoveY = 25.0f + Random(-30, 30) * 0.1f;
		float fRot = GetRandomCircleValue();

		CEffect3D::Create(
			pos,
			D3DXVECTOR3(
				sinf(D3DX_PI + fRot) * fMove,
				fMoveY,
				cosf(D3DX_PI + fRot) * fMove),
			D3DXCOLOR(
				0.2f + Random(-10, 10) * 0.01f,
				0.2f + Random(-10, 10) * 0.01f,
				0.9f + Random(-10, 10) * 0.01f,
				1.0f),
			180.0f + (float)Random(-20, 20),
			15,
			CEffect3D::MOVEEFFECT_SUPERSUB,
			CEffect3D::TYPE_SMOKE);

		D3DXVECTOR3 RandPos = mylib_const::DEFAULT_VECTOR3;
		RandPos.x = Random(-5, 5) * 10.0f;
		RandPos.y = Random(-5, 5) * 10.0f;
		RandPos.z = Random(-5, 5) * 10.0f;

		CEffect3D *pEffect = CEffect3D::Create(
			pos + RandPos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.2f, 0.2f, 0.9f, 1.0f),
			150.0f + (float)Random(-50, 50), 6,
			CEffect3D::MOVEEFFECT_ADD,
			CEffect3D::TYPE_THUNDER);
		pEffect->SetRotation(D3DXVECTOR3(0.0f, 0.0f, GetRandomCircleValue()));
	}
}

//==================================================================================
// セットアップ
//==================================================================================
void CUnionCore::SetUp(D3DXVECTOR3 setup, D3DXMATRIX *pMtxParent)
{
	// 親マトリックスのポインタ
	m_pMtxParent = pMtxParent;

	// セットアップ位置
	m_setupPosition = setup;

	m_bSetUp = true;
}

//==========================================================================
// 描画処理
//==========================================================================
void CUnionCore::Draw(void)
{
	// 描画
	CObjectX::Draw();
}

