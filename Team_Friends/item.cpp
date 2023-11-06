//=============================================================================
// 
//  アイテム処理 [item.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "item.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"
#include "explosion.h"
#include "3D_effect.h"
#include "sound.h"
#include "particle.h"
#include "calculation.h"
#include "game.h"
#include "player.h"
#include "impactwave.h"
#include "scene.h"

//==========================================================================
// マクロ定義
//==========================================================================
#define WIDTH			(30.0f)							// 横幅
#define HEIGHT			(30.0f)							// 縦幅
#define MOVE_SPEED		(15.0f)							// 移動速度
#define ANIM_SPEED		(4)								// 読み込み間隔
#define MAX_PATTERN_U	(1)								// Uの分割数
#define MAX_PATTERN_V	(1)								// Vの分割数
#define MAX_PATTERN		(MAX_PATTERN_U)					// アニメーションパターンの最大数
#define MOVE_U			(1.0f / (float)MAX_PATTERN_U)	// U座標移動量
#define MOVE_V			(1.0f / (float)MAX_PATTERN_V)	// V座標移動量

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================
const char *CItem::m_apModelFile[TYPE_MAX] =	// テクスチャのファイル
{
	"data\\MODEL\\item.x",
};
int CItem::m_nNumAll = 0;		// アイテムの総数

//==========================================================================
// 関数ポインタ
//==========================================================================
CItem::STATE_FUNC CItem::m_FuncList[] =
{
	&CItem::StateNone,
	&CItem::StateDamage,
};

CItem::COLLISION_FUNC CItem::m_CollisionFuncList[] =	// 当たり判定のリスト
{
	&CItem::CollisionPlayer,	// プレイヤーとの判定
};

//==========================================================================
// コンストラクタ
//==========================================================================
CItem::CItem(int nPriority) : CObjectX(nPriority), m_nLifeMax(1)
{
	// 値のクリア
	m_state = STATE_NONE;			// 状態
	m_nCntState = 0;			// 状態遷移カウンター
	m_nLife = 0;
	m_nIdxBulletManager = 0;			// アイテムマネージャのインデックス番号
	m_nCntEmission = 0;	// 発生物のカウンター

	// テクスチャデータの配列分繰り返す
	m_nModelIdx = 0;		// テクスチャのインデックス番号

	// 総数加算
	m_nNumAll++;
}

//==========================================================================
// デストラクタ
//==========================================================================
CItem::~CItem()
{
	
}

//==========================================================================
// 生成処理
//==========================================================================
CItem *CItem::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	// 生成用のオブジェクト
	CItem *pBullet = NULL;

	if (pBullet == NULL)
	{// NULLだったら

		// メモリの確保
		pBullet = DEBUG_NEW CItem;

		if (pBullet != NULL)
		{// メモリの確保が出来ていたら

			// 位置割り当て
			pBullet->SetPosition(pos);

			// 位置割り当て
			pBullet->SetRotation(rot);

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
HRESULT CItem::Init(void)
{
	HRESULT hr;

	// 各種変数の初期化
	m_nLifeMax = 60 * 5;
	m_nLife = m_nLifeMax;	// 寿命
	SetColor(D3DXCOLOR(0.3f, 0.3f, 1.0f, 1.0f));

	// モデルの割り当て
	CScene *pScene = CManager::GetInstance()->GetScene();
	m_nModelIdx = pScene->GetXLoad()->XLoad(m_apModelFile[m_type]);

	// モデルの割り当て
	BindXData(m_nModelIdx);

	// 種類の設定
	CObject::SetType(TYPE_BULLET);

	// 初期化処理
	hr = CObjectX::Init();
	if (FAILED(hr))
	{// 失敗したとき
		return E_FAIL;
	}

	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CItem::Uninit(void)
{
	//// 削除
	//if (CManager::GetInstance()->GetMode() == CScene::MODE_GAME && CGame::GetBulletManager() != NULL)
	//{// アイテムマネージャの削除
	//	CGame::GetBulletManager()->Delete(m_nIdxBulletManager);
	//}

	// 終了処理
	CObjectX::Uninit();

	// 総数減算
	m_nNumAll--;
}

//==========================================================================
// 更新処理
//==========================================================================
void CItem::Update(void)
{
	// 位置更新
	UpdatePos();

	// 状態別処理
	(this->*(m_FuncList[m_state]))();

	// 当たり判定処理
	(this->*(m_CollisionFuncList[m_type]))();

	if (IsDeath() == true)
	{// 死亡フラグが立っていたら
		return;
	}

	// 寿命減算
	m_nLife--;

	if (m_nLife <= 0)
	{// 寿命が尽きたら

		// 爆発の生成
		CExplosion::Create(GetPosition());
		
		Uninit();
		return;
	}

	// 頂点情報設定
	SetVtx();
}

//==========================================================================
// 移動処理
//==========================================================================
void CItem::UpdatePos(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// 移動量取得
	D3DXVECTOR3 move = GetMove();

	// 向き取得
	D3DXVECTOR3 rot = GetRotation();

	// 位置更新
	pos += move;

	// 位置設定
	SetPosition(pos);

	// 移動量設定
	SetMove(move);

	// 向き設定
	SetRotation(rot);
}

//==========================================================================
// 通常状態処理
//==========================================================================
void CItem::StateNone(void)
{
	// 状態遷移カウンター減算
	m_nCntState--;
	if (m_nCntState <= 0)
	{
		m_nCntState = 0;
		m_state = STATE_NONE;
	}
}

//==========================================================================
// ダメージ状態処理
//==========================================================================
void CItem::StateDamage(void)
{
	// 状態遷移カウンター減算
	m_nCntState--;
	if (m_nCntState <= 0)
	{
		m_nCntState = 0;
		m_state = STATE_NONE;
	}
}

//==========================================================================
// プレイヤーとの判定
//==========================================================================
void CItem::CollisionPlayer(void)
{
	// プレイヤー情報取得
	CPlayer *pPlayer = CManager::GetInstance()->GetScene()->GetPlayer();
	if (pPlayer == NULL)
	{// NULLだったら
		return;
	}

	// プレイヤーの情報取得
	D3DXVECTOR3 PlayerPosition = pPlayer->GetCenterPosition();
	D3DXVECTOR3 PlayerRotation = pPlayer->GetRotation();
	float fPlayerRadius = pPlayer->GetRadius();

	// 情報取得
	D3DXVECTOR3 pos = GetPosition();
	float fRadius = GetVtxMax().x;

	if (SphereRange(pos, PlayerPosition, fRadius, fPlayerRadius))
	{// 当たっていたら

		// 終了処理
		Uninit();
		return;
	}

}

//==========================================================================
// プレイヤーアイテムの更新
//==========================================================================
void CItem::UpdateTypePlayer(void)
{

}

//==========================================================================
// 描画処理
//==========================================================================
void CItem::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// Zテストを無効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);	//常に描画する

	// ビルボードの描画
	CObjectX::Draw();

	// Zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//==========================================================================
// 頂点情報設定処理
//==========================================================================
void CItem::SetVtx(void)
{
	// 頂点設定
	CObjectX::SetVtx();
}

//==========================================================================
// 状態設定
//==========================================================================
void CItem::SetState(STATE state, int nCntState)
{
	m_state = state;			// 状態
	m_nCntState = nCntState;	// 状態遷移カウンター
}

//==========================================================================
// 状態取得
//==========================================================================
CItem::STATE CItem::GetState(void)
{
	return m_state;
}

//==========================================================================
// 種類設定
//==========================================================================
void CItem::SetType(TYPE type)
{
	m_type = type;

	// モデルの割り当て
	CScene *pScene = CManager::GetInstance()->GetScene();
	m_nModelIdx = pScene->GetXLoad()->XLoad(m_apModelFile[m_type]);

	// モデルの割り当て
	BindXData(m_nModelIdx);
}

//==========================================================================
// 種類取得
//==========================================================================
CItem::TYPE CItem::GetType(void)
{
	return m_type;
}

//==========================================================================
// 総数取得
//==========================================================================
int CItem::GetNumAll(void)
{
	return m_nNumAll;
}
