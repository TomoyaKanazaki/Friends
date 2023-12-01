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
#include "player_union.h"

//==========================================
//  定数定義 : 金崎朋弥
//==========================================
namespace
{
	const char* CHARAFILE[CPlayerRanking::MAX] =
	{
		//"data\\TEXT\\multicharacter\\BodytoLeg.txt", // 合体ファイルパス
		//"data\\TEXT\\multicharacter\\BodytoArm.txt", // 合体ファイルパス
		//"data\\TEXT\\multicharacter\\LegtoArm.txt", // 合体ファイルパス
		"data\\TEXT\\multicharacter\\ArmtoArm.txt", // 合体ファイルパス
		"data\\TEXT\\multicharacter\\ArmtoArm.txt", // 合体ファイルパス
		"data\\TEXT\\multicharacter\\ArmtoArm.txt", // 合体ファイルパス
		"data\\TEXT\\multicharacter\\ArmtoArm.txt", // 合体ファイルパス
	};
}

//==========================================================================
// コンストラクタ
//==========================================================================
CPlayerRanking::CPlayerRanking(int nPriority)
{
	// 値のクリア
	m_nMovePtaCnt = 0;
	m_nSpinCnt = 0;
	m_bRight = false;
	m_bLeft = false;
}

//==========================================================================
// コンストラクタ
//==========================================================================
CPlayerRanking::CPlayerRanking(MODEL nType, int nPriority)
{
	// 値のクリア
	m_nType = nType;
	m_nMovePtaCnt = 0;
	m_nSpinCnt = 0;
	m_bRight = false;
	m_bLeft = false;
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
HRESULT CPlayerRanking::Init()
{
	// 種類の設定
	SetType(TYPE_PLAYER);

	// キャラ作成
	CreateParts();


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

	CPlayerUnion::Update();

	// 過去の位置保存
	SetOldPosition(GetPosition());

	switch (m_nType)
	{
	case CPlayerRanking::BODYtoLEG:
		ARMtoARMMove();
		break;

	case CPlayerRanking::BODYtoARM:
		ARMtoARMMove();
		break;

	case CPlayerRanking::LEGtoARM:
		ARMtoARMMove();
		break;

	case CPlayerRanking::ARMtoARM:
		ARMtoARMMove();
		break;

	default:
		return;
	}
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
CPlayerUnion* CPlayerRanking::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL type)
{
	// 生成用のオブジェクト
	CPlayerUnion *pPlayer = NULL;

	if (pPlayer == NULL)
	{// NULLだったら
	 
		pPlayer = DEBUG_NEW CPlayerRanking(type);

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

//==========================================================================
// パーツの設定
//==========================================================================
HRESULT CPlayerRanking::CreateParts(void)
{

	// 複数キャラ読み込み
	ReadMultiCharacter(CHARAFILE[m_nType]);

	return S_OK;
}

//==========================================================================
// パーツの設定
//==========================================================================
void CPlayerRanking::ARMtoARMMove(void)
{
	m_nMovePtaCnt++;

	m_bOldLeft = m_bLeft;

	D3DXVECTOR3 pos = GetPosition();

	pos.x -= sinf(GetRotation().y) * 5;
	pos.z -= cosf(GetRotation().y) * 5;

	SetPosition(pos);

	D3DXVECTOR3 rot = GetRotation();

	if (m_nMovePtaCnt >= 60 * 5 && m_nSpinCnt < 3)
	{
		rot.y -= 0.04f;

		//
		if (rot.y <= -D3DX_PI / 2 && m_bRight == true)
		{
			rot.y = -D3DX_PI / 2;
			m_nCntSwitch = 0;
			m_bRight = false;
		}

		else if (rot.y <= D3DX_PI / 2 && m_bLeft == true)
		{
			rot.y = D3DX_PI / 2;
			m_nCntSwitch = 0;
			m_bLeft = false;
		}


		//
		if (rot.y >= D3DX_PI)
		{
			rot.y = -D3DX_PI;
		}

		else if (rot.y <= -D3DX_PI)
		{
			rot.y = D3DX_PI;
			m_bRight = true;
			m_bLeft = true;
		}

		if (m_bLeft == false && m_bOldLeft== true)
		{
			m_nSpinCnt++;
		}
	}

	SetRotation(rot);

	// 移動中にする
	for (int i = 0; i < PARTS_MAX; i++)
	{
		m_sMotionFrag[i].bMove = true;

		if (m_pMotion[i] == NULL)
		{
			continue;
		}
	}
}
