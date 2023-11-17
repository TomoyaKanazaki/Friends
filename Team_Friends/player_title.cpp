//=============================================================================
// 
//  プレイヤー処理 [player_title.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "game.h"
#include "player_title.h"
#include "player.h"
#include "camera.h"
#include "manager.h"
#include "debugproc.h"
#include "renderer.h"
#include "input.h"
#include "enemy.h"
#include "calculation.h"
#include "score.h"
#include "texture.h"
#include "Xload.h"
#include "model.h"
#include "motion.h"
#include "hp_gauge.h"
#include "objectChara.h"
#include "elevation.h"
#include "shadow.h"
#include "particle.h"
#include "3D_Effect.h"
#include "ballast.h"
#include "impactwave.h"
#include "sound.h"
#include "enemymanager.h"
#include "bullet.h"
#include "stage.h"
#include "objectX.h"
#include "gamemanager.h"
#include "instantfade.h"
#include "hp_gauge_player.h"
#include "fade.h"
#include "listmanager.h"
#include "item.h"
#include "injectiontable.h"

//==========================================================================
// マクロ定義
//==========================================================================
#define CHARAFILE		"data\\TEXT\\motion_player.txt"

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================

//==========================================================================
// コンストラクタ
//==========================================================================
CPlayerTitle::CPlayerTitle(int nPriority) : CPlayer(nPriority)
{
	// 値のクリア
	
}

//==========================================================================
// デストラクタ
//==========================================================================
CPlayerTitle::~CPlayerTitle()
{

}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CPlayerTitle::Init(void)
{
	// 種類の設定
	SetType(TYPE_PLAYER);

	m_state = STATE_NONE;	// 状態
	m_bLandOld = true;		// 前回の着地状態

	// キャラ作成
	HRESULT hr = SetCharacter(CHARAFILE);

	if (FAILED(hr))
	{// 失敗していたら
		return E_FAIL;
	}

	// モーションの生成処理
	m_pMotion = CMotion::Create(CHARAFILE);

	// オブジェクトキャラクターの情報取得
	CObjectChara *pObjChar = GetObjectChara();

	// モーションの設定
	m_pMotion->SetModel(pObjChar->GetModel(), pObjChar->GetNumModel(), CObjectChara::GetObjectChara());

	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// 影の生成
	m_pShadow = CShadow::Create(pos, 50.0f);

	// ポーズのリセット
	m_pMotion->ResetPose(MOTION_DEF);
	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CPlayerTitle::Uninit(void)
{
	// 終了処理
	CPlayer::Uninit();
}

//==========================================================================
// 更新処理
//==========================================================================
void CPlayerTitle::Update(void)
{
	if (IsDeath() == true)
	{
		return;
	}

	// 過去の位置保存
	SetOldPosition(GetPosition());

	// モーション更新
	if (m_pMotion != NULL)
	{
		m_pMotion->Update();
	}

	// 影の位置更新
	if (m_pShadow != NULL)
	{
		// 位置取得
		D3DXVECTOR3 pos = GetPosition();

		m_pShadow->SetPosition(D3DXVECTOR3(pos.x, m_pShadow->GetPosition().y, pos.z));
	}

}

//==========================================================================
// 描画処理
//==========================================================================
void CPlayerTitle::Draw(void)
{
	// 描画処理
	CPlayer::Draw();
}
