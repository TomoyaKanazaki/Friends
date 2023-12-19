//==========================================
// 
//  人数選択メニュー(decide_menu.cpp)
//  Author : 橋本 賢太
// 
//==========================================
#include "decide_door.h"
#include "decide_menu.h"
#include "manager.h"
#include "renderer.h"
#include "calculation.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "debugproc.h"
#include "objectX.h"
#include "player_title.h"

//==========================================
//  前方宣言
//==========================================
class CPlayerTitle;

//==========================================
//  定数定義
//==========================================
namespace
{
	const int GATE_TARGET = 300;	// 不透明度更新の時間
	const int GATE_GRACE = 1;		// プレイヤーの座標
	const int GATE_FIXED = 30;		// 選択肢の倍率
	const float FRAME_POS_Z = 250.0f;		// 選択肢の基準位置
	const float LENGTH_SELECT = 197.5f;		// 選択肢の基準位置
	const float PLAYER_SPEED = 5.0f;		// プレイヤーの移動量
	const char *m_apModelFile_fream = "data\\MODEL\\gate\\gate_frame.x";
	const char *m_apModelFile_door = "data\\MODEL\\gate\\gate_door.x";
}

//==========================================
//  コンストラクタ
//==========================================
CDecideDoor::CDecideDoor(int nPriority) : CObject(nPriority),
m_nNowSelect(0),
m_nOldSelect(0)
{
	memset(&m_pSelectX[0], NULL, sizeof(m_pSelectX)); // 選択肢のオブジェクト
	memset(&m_n[0], 0, sizeof(m_n)); // ゲートの開閉猶予カウント
	memset(&m_nGate[0], 0, sizeof(m_nGate)); // ゲートの開閉カウント
}

//==========================================
//  デストラクタ
//==========================================
CDecideDoor::~CDecideDoor()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CDecideDoor::Init(void)
{
	// 種類の設定
	SetType(TYPE_OBJECT3D);

	m_pObjX[VTX_FREAM] = CObjectX::Create(m_apModelFile_fream, D3DXVECTOR3(0.0f, 0.0f, FRAME_POS_Z));
	m_pObjX[VTX_FREAM]->SetType(CObject::TYPE_OBJECTX);

	for (int nCnt = 0; nCnt < MODELSELECT_MAX; nCnt++)
	{
		// 位置設定
		float posX = 0.0f;
		posX -= 1.5f * LENGTH_SELECT;
		posX += LENGTH_SELECT * nCnt;

		m_pSelectX[nCnt] = CObjectX::Create(m_apModelFile_door, D3DXVECTOR3(posX, 0.0f, FRAME_POS_Z));
		m_pSelectX[nCnt]->SetType(CObject::TYPE_OBJECTX);

		if (nCnt <= m_nNowSelect)
		{
			m_nGate[nCnt] = 0;
		}

		else
		{
			m_nGate[nCnt] = 60;
		}
	}

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CDecideDoor::Uninit(void)
{
	for (int nCntSelect = 0; nCntSelect < VTX_MAX; nCntSelect++)
	{
		if (m_pObjX[nCntSelect] != NULL)
		{// NULLじゃなかったら

		 // 終了処理
			m_pObjX[nCntSelect] = NULL;
		}
	}

	for (int nCntSelect = 0; nCntSelect < MODELSELECT_MAX; nCntSelect++)
	{
		if (m_pSelectX[nCntSelect] != NULL)
		{// NULLじゃなかったら

		 // 終了処理
			m_pSelectX[nCntSelect] = NULL;
		}
	}

	// 情報削除
	Release();
}

//==========================================
//  更新処理
//==========================================
void CDecideDoor::Update(void)
{
	
	// 移動
	for (int nCnt = 0; nCnt < MODELSELECT_MAX; ++nCnt)
	{
		if (nCnt <= m_nNowSelect)
		{
			m_nGate[nCnt]++;

			// 等速で開ける
			float posY = EasingLinear(0.0f, GATE_TARGET, m_nGate[nCnt] / GATE_FIXED);

			// 位置を設定
			m_pSelectX[nCnt]->SetPosition(D3DXVECTOR3(m_pSelectX[nCnt]->GetPosition().x,
				posY,
				m_pSelectX[nCnt]->GetPosition().z));

			m_n[nCnt] = 0;
		}
		else
		{
			// 選択画面のプレイヤーを取得
			CPlayerTitle *p = CDecideMenu::GetPlayerTitle(nCnt);

			// プレイヤーの位置が一定位置以上だったら即閉める
			if (p->GetPosition().z >= FRAME_POS_Z)
			{
				m_n[nCnt] = 60 * GATE_GRACE;
			}

			// 閉めるまで猶予を持たす
			m_n[nCnt]++;

			if (m_n[nCnt] >= 60 * GATE_GRACE)
			{
				m_nGate[nCnt]++;

				// 等速で閉める
				float posY = EasingLinear(GATE_TARGET, 0.0f, m_nGate[nCnt] / GATE_FIXED);

				// 位置を設定
				m_pSelectX[nCnt]->SetPosition(D3DXVECTOR3(m_pSelectX[nCnt]->GetPosition().x,
					posY,
					m_pSelectX[nCnt]->GetPosition().z));

				// 猶予カウントを固定
				m_n[nCnt] = 60 * GATE_GRACE;
			}
		}

		// 開閉カウントが一定以上
		if (m_nGate[nCnt] >= GATE_FIXED)
		{
			// 開閉カウントを固定
			m_nGate[nCnt] = GATE_FIXED;
		}
	}
}

//==========================================================================
// 選択肢設定
//==========================================================================
void CDecideDoor::SetSelect(int nSelect)
{

	// 現在の選択肢を保存
	m_nOldSelect = m_nNowSelect;

	// パターンNo.を更新
	m_nNowSelect = nSelect;

	int nOpAndClo;
	if ((m_nNowSelect + 1) % MODELSELECT_MAX == m_nOldSelect)
	{
		// ひとつ前の選択肢が現在の選択肢より少ない
		if (m_nOldSelect <= m_nNowSelect)
		{
			// ゲートの開閉する個数を代入
			nOpAndClo = m_nNowSelect - m_nOldSelect;

			for (int nCnt = nOpAndClo; nCnt > 0; --nCnt)
			{
				// ゲートの開閉カウントを正規化
				m_nGate[nCnt] = GATE_FIXED - m_nGate[nCnt];
			}
		}

		else
		{
			// ゲートの開閉する個数を代入
			nOpAndClo = m_nOldSelect - m_nNowSelect;

			for (int nCnt = 0; nCnt < nOpAndClo; ++nCnt)
			{
				// ゲートの開閉カウントを正規化
				m_nGate[m_nOldSelect + nCnt] = GATE_FIXED - m_nGate[m_nOldSelect + nCnt];
			}
		}
	}
	else
	{
		// ひとつ前の選択肢が現在の選択肢より多い
		if (m_nOldSelect >= m_nNowSelect)
		{
			// ゲートの開閉する個数を代入
			nOpAndClo = m_nOldSelect - m_nNowSelect;

			for (int nCnt = nOpAndClo; nCnt > 0; --nCnt)
			{
				// ゲートの開閉カウントを正規化
				m_nGate[nCnt] = GATE_FIXED - m_nGate[nCnt];
			}
		}

		else
		{
			// ゲートの開閉する個数を代入
			nOpAndClo = m_nNowSelect - m_nOldSelect;

			for (int nCnt = 0; nCnt < nOpAndClo; ++nCnt)
			{
				// ゲートの開閉カウントを正規化
				m_nGate[m_nNowSelect + nCnt] = GATE_FIXED - m_nGate[m_nNowSelect + nCnt];
			}
		}
	}
}

//==========================================
//  描画処理
//==========================================
void CDecideDoor::Draw(void)
{

}

//==========================================
//  生成処理
//==========================================
CDecideDoor* CDecideDoor::Create(void)
{
	// 生成用のオブジェクト
	CDecideDoor* pTitleScreen = NULL;

	if (pTitleScreen == NULL)
	{// NULLだったら

	 // メモリの確保
		pTitleScreen = DEBUG_NEW CDecideDoor;

		if (pTitleScreen != NULL)
		{// メモリの確保が出来ていたら

		 // 初期化処理
			pTitleScreen->Init();
		}

		return pTitleScreen;
	}

	return NULL;
}