//==========================================
//
//  タイトルの合体ロボ(union_title.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "union_title.h"
#include "manager.h"
#include "debugproc.h"
#include "input.h"

//==========================================
//  コンストラクタ
//==========================================
CUnionTitle::CUnionTitle(int nPriority)
{
	// 変数のクリア
	m_bPressEnter = false;	// エンターの押下判定
}

//==========================================
//  デストラクタ
//==========================================
CUnionTitle::~CUnionTitle()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CUnionTitle::Init(void)
{
	// 種類の設定
	SetType(TYPE_PLAYER);

	m_state = STATE_NONE;	// 状態

	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		m_nPartsIdx[i] = -1;
	}

	// キャラ作成
	CreateParts();

	// プレイヤーインデックス毎のテクスチャ設定
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		BindByPlayerIdxTexture(i, i);
	}

	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pObjChara[i] == NULL)
		{
			continue;
		}

		// 自身の情報を取得
		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 rot = GetRotation();

		m_pObjChara[i]->SetPosition(pos);
		m_pObjChara[i]->SetRotation(rot);
	}

	return S_OK;
}

//==========================================================================
// パーツの設定
//==========================================================================
HRESULT CUnionTitle::CreateParts(void)
{
	// 複数キャラ読み込み
	ReadMultiCharacter("data\\TEXT\\multicharacter\\SuperUnion_title.txt");

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CUnionTitle::Uninit(void)
{
	CPlayerUnion::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CUnionTitle::Update(void)
{
	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pMotion[i] == NULL)
		{
			continue;
		}

		// モーションの設定処理
		if (m_bPressEnter)
		{
			m_pMotion[i]->Set(MOTION_STARTUP);
		}
		else
		{
			m_pMotion[i]->Set(MOTION_DEF);
		}

		D3DXVECTOR3 pos = m_pObjChara[i]->GetPosition();

		// モーション更新
		m_pMotion[i]->Update();

		D3DXVECTOR3 posDiff = m_pObjChara[i]->GetPosition() - pos;

		//if (i == 0)
		{
			SetPosition(GetPosition() + posDiff);
		}
	}

	// 位置・向き設定
	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pObjChara[i] == NULL)
		{
			continue;
		}

		// 自身の情報を取得
		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 rot = GetRotation();

		m_pObjChara[i]->SetPosition(pos);
		m_pObjChara[i]->SetRotation(rot);
	}
}

//==========================================================================
// 攻撃時処理
//==========================================================================
void CUnionTitle::AttackAction(int nIdx, int nModelNum, CMotion::AttackInfo ATKInfo)
{
	// 武器の位置
	D3DXVECTOR3 weponpos = m_pMotion[nIdx]->GetAttackPosition(m_pObjChara[nIdx]->GetModel(), ATKInfo);

	// 種類別
	switch (m_pMotion[nIdx]->GetType())
	{
	case MOTION_ATK:
		break;
	}
}

//==========================================
//  描画処理
//==========================================
void CUnionTitle::Draw(void)
{
	CPlayerUnion::Draw();
}

//==========================================
//  生成処理
//==========================================
CUnionTitle* CUnionTitle::Create(D3DXVECTOR3 pos)
{
	// インスタンス生成
	CUnionTitle* pUnion = DEBUG_NEW CUnionTitle;

	// 値を保存
	pUnion->SetPosition(pos);

	// 初期化処理
	pUnion->Init();

	return pUnion;
}
