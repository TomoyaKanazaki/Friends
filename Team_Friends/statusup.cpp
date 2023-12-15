//=============================================================================
// 
// ステータスアップ処理 [statusup.cpp]
// Author : 相馬靜雅
// 
//=============================================================================
#include "statusup.h"
#include "renderer.h"
#include "texture.h"
#include "manager.h"
#include "calculation.h"

//==========================================================================
// マクロ定義
//==========================================================================
namespace
{
	const char* TEXTURE[CGameManager::STATUS_MAX] =
	{
		"data\\TEXTURE\\status\\statusup_power.png",
		"data\\TEXTURE\\status\\statusup_speed.png",
		"data\\TEXTURE\\status\\statusup_life.png",
	};
	const int MAX_LIFE = 40;			// 寿命
	const int TIME_FADEOUT = 20;		// フェードアウト時間
	const float DISTANCE = 200.0f;		// 間隔
	const float DESTSIZE_RATIO = 0.07f;	// 目標のサイズ割合
}

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================
int CStatusUp::m_nTexIdx[CGameManager::STATUS_MAX] = {};	// テクスチャのインデックス番号

//==========================================================================
// コンストラクタ
//==========================================================================
CStatusUp::CStatusUp(int nPriority) : CObjectBillboard(nPriority)
{
	// 値のクリア
	m_nLife = 0;							// 寿命
	m_type = CGameManager::STATUS_POWER;	// 種類
}

//==========================================================================
// デストラクタ
//==========================================================================
CStatusUp::~CStatusUp()
{
	
}

//==========================================================================
// テクスチャ読み込み
//==========================================================================
void CStatusUp::LoadTexture(void)
{
	// テクスチャの読み込み
	for (int nCntTex = 0; nCntTex < CGameManager::STATUS_MAX; nCntTex++)
	{// テクスチャデータの配列分繰り返す
		m_nTexIdx[nCntTex] = CManager::GetInstance()->GetTexture()->Regist(TEXTURE[nCntTex]);
	}
}

//==========================================================================
// 生成処理
//==========================================================================
CStatusUp *CStatusUp::Create(const D3DXVECTOR3 pos, CGameManager::eStatus type)
{
	// 生成用のオブジェクト
	CStatusUp *pEffect = NULL;

	if (pEffect == NULL)
	{// NULLだったら

		// メモリの確保
		pEffect = DEBUG_NEW CStatusUp;

		if (pEffect != NULL)
		{// メモリの確保が出来ていたら

			// 種類
			pEffect->m_type = type;

			// 位置設定
			pEffect->SetPosition(pos);
			pEffect->SetOriginPosition(pos);

			// 初期化処理
			pEffect->Init();
		}

		return pEffect;
	}

	return NULL;
}

//==================================================================================
// 初期化処理
//==================================================================================
HRESULT CStatusUp::Init(void)
{
	HRESULT hr;

	// 種類の設定
	SetType(TYPE_OBJECTBILLBOARD);

	// テクスチャの割り当て
	if (m_nTexIdx[m_type] == 0)
	{
		m_nTexIdx[m_type] = CManager::GetInstance()->GetTexture()->Regist(TEXTURE[m_type]);
	}

	// テクスチャの割り当て
	BindTexture(m_nTexIdx[m_type]);

	// 初期化処理
	hr = CObjectBillboard::Init();
	if (FAILED(hr))
	{// 失敗したとき

		Uninit();
		return E_FAIL;
	}

	// サイズ設定
	SetSize(mylib_const::DEFAULT_VECTOR2);
	m_nLife = MAX_LIFE;	// 寿命

	return S_OK;
}

//==================================================================================
// 終了処理
//==================================================================================
void CStatusUp::Uninit(void)
{
	
	// 終了処理
	CObjectBillboard::Uninit();
}

//==================================================================================
// 更新処理
//==================================================================================
void CStatusUp::Update(void)
{
	// 過去の位置設定
	SetOldPosition(GetPosition());

	// 移動処理
	UpdateMove();

	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	// サイズ取得
	D3DXVECTOR2 size = GetSize();

	// 慣性補正
	InertiaCorrection(size.x, pTexture->GetImageSize(m_nTexIdx[m_type]).x * DESTSIZE_RATIO, 0.15f);
	InertiaCorrection(size.y, pTexture->GetImageSize(m_nTexIdx[m_type]).y * DESTSIZE_RATIO, 0.15f);

	// サイズ設定
	SetSize(size);

	// 寿命の更新
	m_nLife--;

	if (m_nLife <= 0)
	{// 寿命が尽きたら
		
		// 色取得
		D3DXCOLOR col = GetColor();

		// 不透明度の更新
		col.a = (float)(m_nLife + TIME_FADEOUT) / (float)TIME_FADEOUT;

		// 色設定
		SetColor(col);

		if (m_nLife <= -TIME_FADEOUT)
		{// 寿命が尽きたら

			// 削除
			Uninit();
			return;
		}
	}

	// 頂点座標の設定
	SetVtx();

}

//==================================================================================
// 移動処理
//==================================================================================
void CStatusUp::UpdateMove(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// 慣性補正
	InertiaCorrection(pos.y, GetOriginPosition().y + DISTANCE, 0.15f);

	// 位置設定
	SetPosition(pos);
}

//==================================================================================
// 描画処理
//==================================================================================
void CStatusUp::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 描画処理
	CObjectBillboard::Draw();

	// ライティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}