//=============================================================================
// 
//  弾の着弾地点 [bullet_point.cpp]
//  Author : 髙田佳依
// 
//=============================================================================
#include "bullet_point.h"
#include "texture.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "elevation.h"

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================
int CBulletPoint::m_nNumAll = 0;						// 影の総数

//==========================================================================
// コンストラクタ
//==========================================================================
CBulletPoint::CBulletPoint(int nPriority) : CObject3D(nPriority)
{
	m_pObject = NULL;	// オブジェクトのポインタ
	m_nNumAll = 0;		// 総数
	m_nTexIdx = 0;		// テクスチャのインデックス番号

	// 総数加算
	m_nNumAll++;
}

//==========================================================================
// デストラクタ
//==========================================================================
CBulletPoint::~CBulletPoint()
{
	
}

//==========================================================================
// 生成処理
//==========================================================================
CBulletPoint *CBulletPoint::Create(void)
{
	// 生成用のオブジェクト
	CBulletPoint *pShadow = NULL;

	if (pShadow == NULL)
	{// NULLだったら

		// メモリの確保
		pShadow = DEBUG_NEW CBulletPoint;

		//if (pShadow->GetID() < 0)
		//{// メモリ確保に失敗していたら

		//	delete pShadow;
		//	return NULL;
		//}

		if (pShadow != NULL)
		{// メモリの確保が出来ていたら

			// 初期化処理
			pShadow->Init();
		}

		return pShadow;
	}

	return NULL;
}

//==========================================================================
// 生成処理(オーバーロード)
//==========================================================================
CBulletPoint *CBulletPoint::Create(D3DXVECTOR3 pos, float size)
{
	// 生成用のオブジェクト
	CBulletPoint *pShadow = NULL;

	if (pShadow == NULL)
	{// NULLだったら

		// メモリの確保
		pShadow = DEBUG_NEW CBulletPoint;

		//if (pShadow->GetID() < 0)
		//{// メモリ確保に失敗していたら

		//	delete pShadow;
		//	return NULL;
		//}

		if (pShadow != NULL)
		{// メモリの確保が出来ていたら

			// 位置割り当て
			pShadow->SetPosition(pos);
			pShadow->SetSize(D3DXVECTOR3(size, 0.0f, size));	// サイズ

			// 初期化処理
			pShadow->Init();
		}
		return pShadow;
	}

	return NULL;
}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CBulletPoint::Init(void)
{
	HRESULT hr;

	// 各種変数の初期化
	SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));	// 色

	// 種類の設定
	SetType(TYPE_SHADOW);

	D3DXVECTOR3 pos = GetPosition();
	SetPosition(D3DXVECTOR3(pos.x, pos.y + 1.0f, pos.z));

	// 初期化処理
	hr = CObject3D::Init();

	if (FAILED(hr))
	{// 失敗したとき

		return E_FAIL;
	}

	// テクスチャの割り当て
	m_nTexIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\caution\\target.png");

	// テクスチャの割り当て
	BindTexture(m_nTexIdx);

	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CBulletPoint::Uninit(void)
{
	// 終了処理
	CObject3D::Uninit();

	// 総数減算
	m_nNumAll--;
}

//==========================================================================
// 更新処理
//==========================================================================
void CBulletPoint::Update(void)
{
	// 死亡の判定
	if (IsDeath() == true)
	{// 死亡フラグが立っていたら
		return;
	}

	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// 高さ取得
	bool bLand = false;
	pos.y = CGame::GetElevation()->GetHeight(pos, bLand);

	// 位置設定
	SetPosition(pos);

	// 頂点情報設定
	CObject3D::SetVtx();
}

//==========================================================================
// 描画処理
//==========================================================================
void CBulletPoint::Draw(void)
{
	// 描画処理
	CObject3D::Draw();
}

//==========================================================================
// 総数取得
//==========================================================================
int CBulletPoint::GetNumAll(void)
{
	return m_nNumAll;
}
