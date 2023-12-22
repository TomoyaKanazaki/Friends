//=============================================================================
// 
//  必殺のカットイン処理 [ultcutin.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "ultcutin.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"
#include "sound.h"
#include "instantfade.h"
#include "game.h"
#include "player_union.h"
#include "enemy_boss.h"
#include "enemymanager.h"
#include "calculation.h"

//==========================================================================
// 定数定義
//==========================================================================
namespace
{
	const char* TEXTURE = "data\\TEXTURE\\anim\\cutin.png";
}

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================
int CUltCutin::m_nTexIdx = 0;	// テクスチャのインデックス番号

//==========================================================================
// コンストラクタ
//==========================================================================
CUltCutin::CUltCutin(int nPriority) : CObject2D_Anim(nPriority)
{
	// 値のクリア
}

//==========================================================================
// デストラクタ
//==========================================================================
CUltCutin::~CUltCutin()
{
	
}

//==========================================================================
// テクスチャ読み込み
//==========================================================================
void CUltCutin::LoadTexture(void)
{
	// テクスチャの読み込み
	m_nTexIdx = CManager::GetInstance()->GetTexture()->Regist(TEXTURE);
}

//==========================================================================
// 生成処理
//==========================================================================
CUltCutin *CUltCutin::Create(void)
{
	// 生成用のオブジェクト
	CUltCutin *pExplosion = nullptr;

	if (pExplosion == nullptr)
	{// nullptrだったら

		// メモリの確保
		pExplosion = DEBUG_NEW CUltCutin;

		if (pExplosion != nullptr)
		{// メモリの確保が出来ていたら

			// 初期化処理
			pExplosion->Init();
		}

		return pExplosion;
	}

	return nullptr;
}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CUltCutin::Init(void)
{

	// 種類の設定
	SetType(TYPE_OBJECT2D);

	// テクスチャの割り当て
	if (m_nTexIdx == 0)
	{
		m_nTexIdx = CManager::GetInstance()->GetTexture()->Regist(TEXTURE);
	}

	// テクスチャの割り当て
	BindTexture(m_nTexIdx);

	// 位置割り当て
	SetPosition(D3DXVECTOR3(640.0f, 360.0f, 0.0f));

	// サイズ設定
	SetSize(D3DXVECTOR2(640.0f, 360.0f));

	// 初期化処理
	CObject2D_Anim::Init(12, 4, 1, true);

	CManager::GetInstance()->GetInstantFade()->SetFade(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 24);

	SetEnableHitstopMove();

	return S_OK;
}

//==========================================================================
// 更新処理
//==========================================================================
void CUltCutin::Update(void)
{
	// フェードの状態取得
	CInstantFade::STATE fadestate = CManager::GetInstance()->GetInstantFade()->GetState();
	if (fadestate == CInstantFade::STATE_FADECOMPLETION)
	{// 完了した時

		if (CGame::GetEnemyManager() != nullptr && CGame::GetEnemyManager()->GetBoss() != nullptr)
		{
			CEnemyBoss *pEnemyBoss = CGame::GetEnemyManager()->GetBoss();
			CPlayerUnion *pPlayerUnion = CManager::GetInstance()->GetScene()->GetPlayerUnion();
			if (pEnemyBoss != nullptr && pPlayerUnion != nullptr)
			{
				D3DXVECTOR3 targetPosition = mylib_const::DEFAULT_VECTOR3;
				D3DXVECTOR3 unionPosition = pPlayerUnion->GetPosition();
				D3DXVECTOR3 unionRotation = pPlayerUnion->GetRotation();

				// 目標値割り出し
				targetPosition.x = sinf(D3DX_PI + unionRotation.y) * 1000.0f;
				targetPosition.z = cosf(D3DX_PI + unionRotation.y) * 1000.0f;

				// プレイヤーの位置加算
				targetPosition += unionPosition;
				targetPosition.y = 0.0f;

				pEnemyBoss->SetPosition(targetPosition);

				// プレイヤーに対して正面向ける
				D3DXVECTOR3 bossRotation = pEnemyBoss->GetRotation();
				bossRotation.y += D3DX_PI;
				RotNormalize(bossRotation);

				pEnemyBoss->SetRotation(bossRotation);
			}
		}

	}

	// 更新処理
	CObject2D_Anim::Update();
}

//==========================================================================
// 描画処理
//==========================================================================
void CUltCutin::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// 描画処理
	CObject2D_Anim::Draw();

	// アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}
