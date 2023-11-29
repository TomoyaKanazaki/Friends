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
		// モーションの設定処理
		MotionSet(i);
	}

	// モーション更新
	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pMotion[i] == NULL)
		{
			continue;
		}
		m_pMotion[i]->Update();
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

	// 初期化処理
	pUnion->Init();

	// 値を保存
	pUnion->SetPosition(pos);

	return pUnion;
}
