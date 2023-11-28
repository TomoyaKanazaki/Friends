//=============================================================================
// 
//  プレイヤー処理 [player_title.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "game.h"
#include "player_ranking.h"
#include "manager.h"
#include "debugproc.h"
#include "input.h"
#include "model.h"
#include "motion.h"
#include "objectChara.h"
#include "shadow.h"
#include "union_armtoarm.h"
#include "union_bodytoarm.h"
#include "union_bodytoleg.h"
#include "union_legtoarm.h"

//==========================================
//  定数定義 : 金崎朋弥
//==========================================
namespace
{
	const char* CHARAFILE[CPlayerRanking::MAX] =
	{
		"data\\TEXT\\multicharacter\\ArmtoArm.txt", // 合体ファイルパス
		"data\\TEXT\\multicharacter\\ArmtoArm.txt", // 合体ファイルパス
		"data\\TEXT\\multicharacter\\ArmtoArm.txt", // 合体ファイルパス
		"data\\TEXT\\multicharacter\\ArmtoArm.txt", // 合体ファイルパス
	};
}

//==========================================================================
// コンストラクタ
//==========================================================================
CPlayerRanking::CPlayerRanking(int nPriority) : CPlayerUnion(nPriority)
{
	// 値のクリア

}

//==========================================================================
// デストラクタ
//==========================================================================
CPlayerRanking::~CPlayerRanking()
{

}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CPlayerRanking::Init(void)
{
	// 種類の設定
	SetType(TYPE_PLAYER);

	m_state = STATE_NONE;	// 状態


	//// モーションの生成処理
	//m_pMotion = CMotion::Create(CHARAFILE[BODYtoLEG]);

	//// オブジェクトキャラクターの情報取得
	//CObjectChara *pObjChar = GetObjectChara();

	//// モーションの設定
	//m_pMotion->SetModel(pObjChar->GetModel(), pObjChar->GetNumModel(), CObjectChara::GetObjectChara());

	// モデルの差し替え
	/*switch (m_nModelType)
	{
	case PLAYER_BODY:
		SetEvolusion(CGameManager::STATUS_LIFE);
		break;

	case PLAYER_ARM:
		SetEvolusion(CGameManager::STATUS_POWER);
		break;

	case PLAYER_LEG:
		SetEvolusion(CGameManager::STATUS_SPEED);
		break;

	default:
		break;
	}*/

	// ポーズのリセット
	//m_pMotion->ResetPose(MOTION_DEF);
	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CPlayerRanking::Uninit(void)
{
	// 終了処理
	CPlayerUnion::Uninit();
}

//==========================================================================
// 更新処理
//==========================================================================
void CPlayerRanking::Update(void)
{
	if (IsDeath() == true)
	{
		return;
	}

	// 過去の位置保存
	SetOldPosition(GetPosition());

	// モーション更新
	/*if (m_pMotion != NULL)
	{
		m_pMotion->Update();
	}*/


}

//==========================================================================
// 描画処理
//==========================================================================
void CPlayerRanking::Draw(void)
{
	// 描画処理
	CPlayerUnion::Draw();
}

//==========================================
//  生成処理 : 金崎朋弥
//==========================================
CPlayerRanking* CPlayerRanking::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL type)
{
	// 生成用のオブジェクト
	CPlayerRanking *pPlayer = NULL;

	if (pPlayer == NULL)
	{// NULLだったら

	 // メモリの確保
		switch (type)
		{
		case TYPE_BODYtoLEG:
			pPlayer = DEBUG_NEW CUnion_BodytoLega;
			break;

		case TYPE_BODYtoARM:
			pPlayer = DEBUG_NEW CUnion_BodytoArma;
			break;

		case TYPE_LEGtoARM:
 			pPlayer = DEBUG_NEW CUnion_LegtoArma;
			break;

		case TYPE_ARMtoARM:
			pPlayer = DEBUG_NEW CUnion_ArntoArma;
			break;

		default:
			return NULL;
			break;
		}

		if (pPlayer != NULL)
		{// メモリの確保が出来ていたら

		 // プレイヤーインデックス番号
		 //pPlayer->m_nMyPlayerIdx = nIdx;

		 // 初期化処理
			pPlayer->Init();

			// 値を保存
			pPlayer->SetPosition(pos);
			pPlayer->SetRotation(rot);
		}

	}

	return pPlayer;
}
