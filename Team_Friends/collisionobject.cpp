//=============================================================================
// 
// 当たり判定オブジェクト処理 [collisionobject.cpp]
// Author : 相馬靜雅
// 
//=============================================================================
#include "collisionobject.h"
#include "renderer.h"
#include "texture.h"
#include "manager.h"

//==========================================================================
// マクロ定義
//==========================================================================

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================

//==========================================================================
// コンストラクタ
//==========================================================================
CCollisionObject::CCollisionObject(int nPriority) : CObjectBillboard(nPriority)
{
	// 値のクリア
	m_fRadius = 0.0f;							// 半径
	m_nLife = 0;								// 寿命
	m_nMaxLife = 0;								// 最大寿命(固定)
}

//==========================================================================
// デストラクタ
//==========================================================================
CCollisionObject::~CCollisionObject()
{
	
}

//==========================================================================
// 生成処理
//==========================================================================
CCollisionObject *CCollisionObject::Create(void)
{
	// 生成用のオブジェクト
	CCollisionObject *pEffect = NULL;

	if (pEffect == NULL)
	{// NULLだったら

		// メモリの確保
		pEffect = DEBUG_NEW CCollisionObject;

		if (pEffect != NULL)
		{// メモリの確保が出来ていたら

			// 初期化処理
			pEffect->Init();
		}

		return pEffect;
	}

	return NULL;
}

//==========================================================================
// 生成処理
//==========================================================================
CCollisionObject *CCollisionObject::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fRadius, const int nLife)
{
	// 生成用のオブジェクト
	CCollisionObject *pEffect = NULL;

	if (pEffect == NULL)
	{// NULLだったら

		// メモリの確保
		pEffect = DEBUG_NEW CCollisionObject;

		if (pEffect != NULL)
		{// メモリの確保が出来ていたら

			pEffect->SetPosition(pos);
			pEffect->SetMove(move);
			pEffect->m_fRadius = fRadius;
			pEffect->SetSize(D3DXVECTOR2(fRadius, fRadius));
			pEffect->m_nLife = nLife;

			// 初期化処理
			HRESULT hr = pEffect->Init();
			if (FAILED(hr))
			{
				return NULL;
			}
		}

		return pEffect;
	}

	return NULL;
}

//==================================================================================
// エフェクトの初期化処理
//==================================================================================
HRESULT CCollisionObject::Init(void)
{
	HRESULT hr;

	// 各種変数の初期化
	m_nMaxLife = m_nLife;						// 最大寿命(固定)

	// 種類の設定
	SetType(TYPE_EFFECT3D);

	// 初期化処理
	hr = CObjectBillboard::Init();
	if (FAILED(hr))
	{// 失敗したとき
		Uninit();
		return E_FAIL;
	}

	return S_OK;
}

//==================================================================================
// エフェクトの終了処理
//==================================================================================
void CCollisionObject::Uninit(void)
{
	// 終了処理
	CObjectBillboard::Uninit();
}

//==================================================================================
// エフェクトの更新処理
//==================================================================================
void CCollisionObject::Update(void)
{

	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// 移動量取得
	D3DXVECTOR3 move = GetMove();

	// 位置更新
	pos += move;

	// 位置設定
	SetPosition(pos);

	// 移動量設定
	SetMove(move);

	// 寿命の更新
	m_nLife--;

	// サイズ設定
	SetSize(D3DXVECTOR2(m_fRadius, m_fRadius));

	if (m_nLife <= 0)
	{// 寿命が尽きたら
		Uninit();
		return;
	}

	// 頂点座標の設定
	SetVtx();

}

//==================================================================================
// エフェクトの描画処理
//==================================================================================
void CCollisionObject::Draw(void)
{
#ifdef _DEBUG
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Zテストを無効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);	//常に描画する

	// アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 描画処理
	CObjectBillboard::Draw();

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// Zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ライティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
#endif
}

//==========================================================================
// 頂点情報設定処理
//==========================================================================
void CCollisionObject::SetVtx(void)
{
	// 頂点設定
	CObjectBillboard::SetVtx();
}

