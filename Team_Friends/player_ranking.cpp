//=============================================================================
// 
//  プレイヤー処理 [player_title.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "game.h"
#include "player_ranking.h"
#include "manager.h"
#include "calculation.h"
#include "debugproc.h"
#include "input.h"
#include "model.h"
#include "motion.h"
#include "objectChara.h"
#include "shadow.h"
#include "player_union.h"
#include "ranking.h"

//==========================================
//  定数定義 : 金崎朋弥
//==========================================
namespace
{
	const char* CHARAFILE[CPlayerRanking::MAX] =
	{
		"data\\TEXT\\multicharacter\\BodytoLeg.txt", // 合体ファイルパス
		"data\\TEXT\\multicharacter\\BodytoArm.txt", // 合体ファイルパス
		"data\\TEXT\\multicharacter\\LegtoArm.txt", // 合体ファイルパス
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
	m_nStopCnt = 0;
	m_bRight = false;
	m_bLeft = false;
	m_bAtkMotion = false;
	m_bReMove = false;
	m_nTypeMove = PTN_NONE;
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
	m_nStopCnt = 0;
	m_bRight = false;
	m_bLeft = false;
	m_bAtkMotion = false;
	m_bReMove = false;
	m_nTypeMove = PTN_NONE;
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

	int i = Random(PTN_01, PTN_MAX);

	switch (i)
	{
	case PTN_01:
		m_nTypeMove = PTN_01;
		break;

	case PTN_02:
		m_nTypeMove = PTN_02;
		break;

	default:
		return S_OK;
	}


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

	switch (m_nTypeMove)
	{
	case PTN_01:
		MovePtn01();
		break;

	case PTN_02:
		MovePtn02();
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
// 背景キャラの行動パターン1
//==========================================================================
void CPlayerRanking::MovePtn01(void)
{
	m_nMovePtaCnt++;

	m_bOldLeft = m_bLeft;

	D3DXVECTOR3 pos = GetPosition();

	pos.x -= sinf(GetRotation().y) * 5;
	pos.z -= cosf(GetRotation().y) * 5;

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

	SetPosition(pos);
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

//==========================================================================
// 背景キャラの行動パターン2
//==========================================================================
void CPlayerRanking::MovePtn02(void)
{
	m_nMovePtaCnt++;

	D3DXVECTOR3 pos = GetPosition();

	D3DXVECTOR3 rot = GetRotation();

	// 左を向き始めるまで定位置で止める
	if (m_nMovePtaCnt >= 60 * 5 && m_bReMove == false)
	{
		// 攻撃モーション後に止まる秒数
		if (m_nStopCnt <= 60 * 2)
		{
			rot.y -= 0.01f;

			// 正面を向く
			if (rot.y <= 0.0f)
			{
				rot.y = 0.0f;

				// 攻撃モーション
				for (int i = 0; i < PARTS_MAX; i++)
				{
					// 一回だけ
					if (m_sMotionFrag[i].bATK == true || m_bAtkMotion == true)
					{
						m_sMotionFrag[i].bATK = false;
						m_bAtkMotion = true;
					}

					else
					{
						m_sMotionFrag[i].bATK = true;
					}

					if (m_pMotion[i] == NULL)
					{
						continue;
					}
				}

				// 攻撃モーションを終えた
				if (m_bAtkMotion == true)
				{
					m_nStopCnt++;
				}
			}
		}

		else
		{
			rot.y += 0.01f;

			// 左を向く
			if (rot.y >= D3DX_PI / 2)
			{
				rot.y = D3DX_PI / 2;
				m_bReMove = true;
			}
		}

		// 移動モーションをやめる
		for (int i = 0; i < PARTS_MAX; i++)
		{
			m_sMotionFrag[i].bMove = false;

			if (m_pMotion[i] == NULL)
			{
				continue;
			}
		}
	}

	else
	{
		pos.x -= sinf(GetRotation().y) * 5;
		pos.z -= cosf(GetRotation().y) * 5;

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

	SetPosition(pos);
	SetRotation(rot);
	
}
