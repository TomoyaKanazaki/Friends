//=============================================================================
// 
//  弾のマネージャ処理 [bulletmanager.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "debugproc.h"
#include "bulletmanager.h"
#include "calculation.h"
#include "manager.h"
#include "game.h"
#include "renderer.h"

//==========================================================================
// コンストラクタ
//==========================================================================
CBulletManager::CBulletManager()
{
	// 値のクリア
	m_nNumAll = 0;	// 総数リセット
	memset(&m_apBullet[0], NULL, sizeof(m_apBullet));	// 弾のオブジェクト
}

//==========================================================================
// デストラクタ
//==========================================================================
CBulletManager::~CBulletManager()
{

}

//==========================================================================
// 生成処理
//==========================================================================
CBulletManager *CBulletManager::Create(void)
{
	// 生成用のオブジェクト
	CBulletManager *pModel = NULL;

	if (pModel == NULL)
	{// NULLだったら

		// メモリの確保
		pModel = DEBUG_NEW CBulletManager;

		if (pModel != NULL)
		{// メモリの確保が出来ていたら

			// 初期化処理
			HRESULT hr = pModel->Init();
			if (FAILED(hr))
			{// 失敗していたら
				return NULL;
			}
		}

		return pModel;
	}

	return NULL;
}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CBulletManager::Init(void)
{
	// 総数リセット
	m_nNumAll = 0;

	return S_OK;
}

//==========================================================================
// 割り当て
//==========================================================================
int CBulletManager::Regist(CBullet *pBullet)
{
	int nIdx = 0;
	for (int nCntBullet = 0; nCntBullet < mylib_const::MAX_BULLET; nCntBullet++)
	{
		if (m_apBullet[nCntBullet] != NULL)
		{// 情報があったら
			continue;
		}

		// 弾情報割り当て
		m_apBullet[nCntBullet] = pBullet;

		nIdx = nCntBullet;

		// 総数加算
		m_nNumAll++;
		break;
	}

	return nIdx;
}

//==========================================================================
// 削除
//==========================================================================
void CBulletManager::Delete(int nIdx)
{
	// NULLにする
	m_apBullet[nIdx] = NULL;

	// 総数減算
	m_nNumAll--;
}

//==========================================================================
// 終了処理
//==========================================================================
void CBulletManager::Uninit(void)
{
	for (int nCntBullet = 0; nCntBullet < mylib_const::MAX_BULLET; nCntBullet++)
	{
		if (m_apBullet[nCntBullet] != NULL)
		{// 情報があったら
			m_apBullet[nCntBullet] = NULL;
		}
	}

	// 総数
	m_nNumAll = 0;
}

//==========================================================================
// 弾の総数取得
//==========================================================================
int CBulletManager::GetNumAll(void)
{
	return m_nNumAll;
}

//==========================================================================
// 弾のオブジェクト取得
//==========================================================================
CBullet **CBulletManager::GetBullet(void)
{
	return m_apBullet;
}
