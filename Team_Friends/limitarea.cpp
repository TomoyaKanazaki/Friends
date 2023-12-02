//=============================================================================
// 
//  エリア制限処理 [limitarea.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "limitarea.h"
#include "limitereamanager.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "calculation.h"
#include "debugproc.h"
#include "player.h"
#include "game.h"


//==========================================================================
// 無名ネームスペース
//==========================================================================
namespace
{
	const char* TEXTURE_DEFAULT = "data\\TEXTURE\\cyberwall_03.png";	// デフォルトテクスチャ
	const float MAX_ALPHA = 0.3f;	// 最大不透明度
	const float TIME_APPEARANCE = 0.5f;	// 出現時間
	const float TIME_FADEOUT = 0.5f;	// フェードアウト時間
}

//==========================================================================
// 関数リスト
//==========================================================================
CLimitArea::STATE_FUNC CLimitArea::m_StateFuncList[] =
{
	&CLimitArea::StateNone,			// 通常
	&CLimitArea::StateAppearance,	// 出現状態
	&CLimitArea::StateFadeout,		// フェードアウト
};

//==========================================================================
// コンストラクタ
//==========================================================================
CLimitArea::CLimitArea(int nPriority) : CObject(nPriority)
{
	m_state = STATE_NONE;			// 状態
	m_fTimeState = 0.0f;			// 状態カウンター
	m_nIdxEreaManager = 0;			// エリア制限マネージャのインデックス番号
	memset(&m_pMeshWall[0], NULL, sizeof(m_pMeshWall));			// メッシュウォールのオブジェクト
	memset(&m_sLimitEreaInfo, NULL, sizeof(m_sLimitEreaInfo));	// エリア制限情報
}

//==========================================================================
// デストラクタ
//==========================================================================
CLimitArea::~CLimitArea()
{

}

//==========================================================================
// 生成処理
//==========================================================================
CLimitArea *CLimitArea::Create(sLimitEreaInfo info)
{
	// 生成用のオブジェクト
	CLimitArea *pObjMeshField = NULL;

	if (pObjMeshField == NULL)
	{// NULLだったら

		// メモリの確保
		pObjMeshField = DEBUG_NEW CLimitArea;

		if (pObjMeshField != NULL)
		{// メモリの確保が出来ていたら

			// エリア制限情報
			pObjMeshField->m_sLimitEreaInfo = info;

			// 初期化処理
			pObjMeshField->Init();
		}

		return pObjMeshField;
	}

	return NULL;
}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CLimitArea::Init(void)
{

	// 種類設定
	SetType(TYPE_ELEVATION);

	// 割り当て
	m_nIdxEreaManager = CGame::GetLimitEreaManager()->Regist(this);

	// 各種変数初期化
	D3DXVECTOR3 WallPos[mylib_const::SHAPE_LIMITEREA];
	float fWidthLen[mylib_const::SHAPE_LIMITEREA];

	// 奥
	WallPos[0] = D3DXVECTOR3(
		(m_sLimitEreaInfo.fMinX + m_sLimitEreaInfo.fMaxX) * 0.5f,
		0.0f,
		m_sLimitEreaInfo.fMaxZ);
	fWidthLen[0] = GetPosLength(D3DXVECTOR3(m_sLimitEreaInfo.fMinX, 0.0f, 0.0f), D3DXVECTOR3(m_sLimitEreaInfo.fMaxX, 0.0f, 0.0f));

	// 右
	WallPos[1] = D3DXVECTOR3(
		m_sLimitEreaInfo.fMinX,
		0.0f,
		(m_sLimitEreaInfo.fMinZ + m_sLimitEreaInfo.fMaxZ) * 0.5f);
	fWidthLen[1] = GetPosLength(D3DXVECTOR3(m_sLimitEreaInfo.fMinZ, 0.0f, 0.0f), D3DXVECTOR3(m_sLimitEreaInfo.fMaxZ, 0.0f, 0.0f));

	// 手前
	WallPos[2] = D3DXVECTOR3(
		(m_sLimitEreaInfo.fMinX + m_sLimitEreaInfo.fMaxX) * 0.5f,
		0.0f,
		m_sLimitEreaInfo.fMinZ);
	fWidthLen[2] = GetPosLength(D3DXVECTOR3(m_sLimitEreaInfo.fMinX, 0.0f, 0.0f), D3DXVECTOR3(m_sLimitEreaInfo.fMaxX, 0.0f, 0.0f));

	// 左
	WallPos[3] = D3DXVECTOR3(
		m_sLimitEreaInfo.fMaxX,
		0.0f,
		(m_sLimitEreaInfo.fMinZ + m_sLimitEreaInfo.fMaxZ) * 0.5f);
	fWidthLen[3] = GetPosLength(D3DXVECTOR3(m_sLimitEreaInfo.fMinZ, 0.0f, 0.0f), D3DXVECTOR3(m_sLimitEreaInfo.fMaxZ, 0.0f, 0.0f));

	float fRot = (D3DX_PI * 2.0f) / (float)mylib_const::SHAPE_LIMITEREA;
	int nBlock = 4;
	for (int i = 0; i < mylib_const::SHAPE_LIMITEREA; i++)
	{
		m_pMeshWall[i] = CMeshWall::Create(WallPos[i], D3DXVECTOR3(0.0f, D3DX_PI + fRot * i, 0.0f), fWidthLen[i] / (float)nBlock, fWidthLen[i] / (float)nBlock, nBlock, 1, 7, TEXTURE_DEFAULT);
		m_pMeshWall[i]->SetType(CObject::TYPE_NONE);
	}

	// 出現状態
	m_state = STATE_APPEARANCE;

	return E_FAIL;
}

//==========================================================================
// 終了処理
//==========================================================================
void CLimitArea::Uninit(void)
{
	// 削除
	if (CManager::GetInstance()->GetMode() == CScene::MODE_GAME && CGame::GetLimitEreaManager() != NULL)
	{// 弾マネージャの削除
		CGame::GetLimitEreaManager()->Delete(m_nIdxEreaManager);
	}

	for (int i = 0; i < mylib_const::SHAPE_LIMITEREA; i++)
	{
		if (m_pMeshWall[i] == NULL)
		{
			continue;
		}
		m_pMeshWall[i]->Uninit();
		delete m_pMeshWall[i];
		m_pMeshWall[i] = NULL;
	}

	// 解放処理
	CObject::Release();
}

//==========================================================================
// 削除処理
//==========================================================================
void CLimitArea::Kill(void)
{
	// 削除
	if (CManager::GetInstance()->GetMode() == CScene::MODE_GAME && CGame::GetLimitEreaManager() != NULL)
	{// 弾マネージャの削除
		CGame::GetLimitEreaManager()->Delete(m_nIdxEreaManager);
	}

	for (int i = 0; i < mylib_const::SHAPE_LIMITEREA; i++)
	{
		if (m_pMeshWall[i] == NULL)
		{
			continue;
		}
		m_pMeshWall[i]->Uninit();
		m_pMeshWall[i] = NULL;
	}

	// 解放処理
	CObject::Release();
}

//==========================================================================
// 更新処理
//==========================================================================
void CLimitArea::Update(void)
{
	// 状態更新
	(this->*(m_StateFuncList[m_state]))();

	for (int i = 0; i < mylib_const::SHAPE_LIMITEREA; i++)
	{
		if (m_pMeshWall[i] == NULL)
		{
			continue;
		}

		// 一旦いらね
		//UpdateColor(i);
		m_pMeshWall[i]->Update();
	}
}

//==========================================================================
// 通常状態
//==========================================================================
void CLimitArea::StateNone(void)
{
	// 状態カウンターリセット
	m_fTimeState = 0.0f;
}

//==========================================================================
// 出現状態
//==========================================================================
void CLimitArea::StateAppearance(void)
{
	// 状態カウンター加算
	m_fTimeState += CManager::GetInstance()->GetDeltaTime();

	// 不透明度
	float fAlpha =  MAX_ALPHA * (m_fTimeState / TIME_APPEARANCE);

	for (int i = 0; i < mylib_const::SHAPE_LIMITEREA; i++)
	{
		if (m_pMeshWall[i] == NULL)
		{
			continue;
		}

		// 頂点カラー取得
		D3DXCOLOR *pVtxCol = m_pMeshWall[i]->GetVtxCol();
		D3DXCOLOR newcolor = D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha);

		// 全ての要素を書き換え
		std::fill(pVtxCol, pVtxCol + m_pMeshWall[i]->GetNumVertex(), newcolor);
	}

	if (m_fTimeState >= TIME_APPEARANCE)
	{// 規定値を超えたら出現状態解除
		m_state = STATE_NONE;
	}

}

//==========================================================================
// フェードアウト状態
//==========================================================================
void CLimitArea::StateFadeout(void)
{
	// 状態カウンター加算
	m_fTimeState += CManager::GetInstance()->GetDeltaTime();

	// 不透明度
	float fAlpha = MAX_ALPHA - (m_fTimeState / TIME_FADEOUT);

	for (int i = 0; i < mylib_const::SHAPE_LIMITEREA; i++)
	{
		if (m_pMeshWall[i] == NULL)
		{
			continue;
		}

		// 頂点カラー取得
		D3DXCOLOR *pVtxCol = m_pMeshWall[i]->GetVtxCol();
		D3DXCOLOR newcolor = D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha);

		// 全ての要素を書き換え
		std::fill(pVtxCol, pVtxCol + m_pMeshWall[i]->GetNumVertex(), newcolor);
	}

	if (m_fTimeState >= TIME_FADEOUT)
	{// 削除

		// 削除
		Kill();
		return;
	}
}

//==========================================================================
// 色更新
//==========================================================================
void CLimitArea::UpdateColor(int nIdx)
{
	CPlayer *pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(0);
	if (pPlayer == NULL)
	{
		return;
	}
	D3DXVECTOR3 pos = pPlayer->GetPosition();

	// 頂点情報
	D3DXCOLOR *pVtxCol = m_pMeshWall[nIdx]->GetVtxCol();
	D3DXVECTOR3 *pVtxPos = m_pMeshWall[nIdx]->GetVtxPos();

	// フィールドの位置
	D3DXVECTOR3 posfield = m_pMeshWall[nIdx]->GetPosition();

	// 長さ取得
	float fWidthLen = m_pMeshWall[nIdx]->GetWidthLen();
	float fHeightLen = m_pMeshWall[nIdx]->GetHeightLen();

	// 最大の長さ
	float fMaxWidthLen = fWidthLen * m_pMeshWall[nIdx]->GetWidthBlock();
	float fMaxHeightLen = -fWidthLen * m_pMeshWall[nIdx]->GetHeightBlock();

	// ブロック
	int nWidthBlock = m_pMeshWall[nIdx]->GetWidthBlock();
	int nHeightBlock = m_pMeshWall[nIdx]->GetHeightBlock();

	// 判定する頂点の計算
	int nCntWidth = 0;
	int nCntHeight = 0;
	int nWidthPoint = ((pos.x - posfield.x) - fMaxWidthLen * 0.5f) / fWidthLen + nWidthBlock;
	int nHeightPoint = nHeightBlock - ((pos.z - posfield.z) - fMaxHeightLen * 0.5f) / fHeightLen;

	int naWidthPoint[mylib_const::MAX_PLAYER] = {};
	int naHeightPoint[mylib_const::MAX_PLAYER] = {};

	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		CPlayer *pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(i);
		if (pPlayer == NULL)
		{
			continue;
		}
		D3DXVECTOR3 pos = pPlayer->GetPosition();
		naWidthPoint[i] = ((pos.x - posfield.x) - fMaxWidthLen * 0.5f) / fWidthLen + nWidthBlock;
		naHeightPoint[i] = nHeightBlock - ((pos.z - posfield.z) - fMaxHeightLen * 0.5f) / fHeightLen;
	}


#if 0
	for (int nCntH = 0; nCntH < 2; nCntH++)
	{
		for (int nCntW = 0; nCntW < 2; nCntW++)
		{
			// 横頂点
			nCntWidth = nWidthPoint + (nCntW - 1);
			nCntHeight = nHeightPoint + (nCntH - 1);

			if (nCntWidth < 0 || nWidthBlock < nCntWidth)
			{// 範囲外で先頭
				continue;
			}

			if (nCntHeight < 0 || nHeightBlock < nCntHeight)
			{// 範囲外で先頭
				continue;
			}

			// 今回の頂点
			int nNowPoint = (nCntWidth + 1) + (nCntHeight * (nWidthBlock + 1));
			pVtxCol[nNowPoint] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		}
	}
#else
	for (int nCntH = 0; nCntH < nHeightBlock + 1; nCntH++)
	{
		for (int nCntW = 0; nCntW < nWidthBlock + 1; nCntW++)
		{
			// 今回の頂点
			int nNowPoint = nCntW + (nCntH * (nWidthBlock + 1));

			for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
			{
				if (naWidthPoint[i] == nNowPoint ||
					naHeightPoint[i] == nNowPoint)
				{

					pVtxCol[nNowPoint] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
					break;
				}
				else
				{
					pVtxCol[nNowPoint] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
				}
			}

			// 後で消す
			pVtxCol[nNowPoint] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
		}
	}
#endif

}

//==========================================================================
// 描画処理
//==========================================================================
void CLimitArea::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 背面のカリングなし
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 描画処理
	for (int i = 0; i < mylib_const::SHAPE_LIMITEREA; i++)
	{
		if (m_pMeshWall[i] == NULL)
		{
			continue;
		}

		m_pMeshWall[i]->Draw();
	}

	// ライティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// カリングデフォルト
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//==========================================================================
// 情報取得
//==========================================================================
CLimitArea::sLimitEreaInfo CLimitArea::GetLimitEreaInfo(void)
{
	return m_sLimitEreaInfo;
}

//==========================================================================
// 状態取得
//==========================================================================
CLimitArea::STATE CLimitArea::GetState(void)
{
	return m_state;
}

//==========================================================================
// 状態取得
//==========================================================================
void CLimitArea::SetState(STATE state)
{
	m_state = state;
}