//=============================================================================
// 
//  タイトル合体プレイヤー処理 [union_title.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "union_title.h"
#include "manager.h"
#include "camera.h"
#include "effect_startupeye.h"
#include "title.h"
#include "fade.h"
#include "3D_Effect.h"
#include "calculation.h"

//==========================================================================
//  コンストラクタ
//==========================================================================
CUnionTitle::CUnionTitle(int nPriority)
{
	// 変数のクリア
	m_bPressEnter = false;	// エンターの押下判定
}

//==========================================================================
//  デストラクタ
//==========================================================================
CUnionTitle::~CUnionTitle()
{

}

//==========================================================================
// 生成処理
//==========================================================================
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

//==========================================================================
// 初期化処理
//==========================================================================
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


	// 自身の情報を取得
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();
	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pObjChara[i] == NULL)
		{
			continue;
		}

		// 位置・向き設定
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

//==========================================================================
// 更新処理
//==========================================================================
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

		if (m_pMotion[i]->GetType() == MOTION_STARTUP && m_pMotion[i]->IsFinish())
		{
			// モード設定
			CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_DECIDE);
		}

		D3DXVECTOR3 pos = m_pObjChara[i]->GetPosition();

		// モーション更新
		m_pMotion[i]->Update();

		// 差分
		D3DXVECTOR3 posDiff = m_pObjChara[i]->GetPosition() - pos;
		SetPosition(GetPosition() + posDiff);

		// 攻撃処理
		Atack(i);
	}

	// 位置・向き設定
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();

	D3DXCOLOR col = D3DXCOLOR(1.0f, 0.2f, 0.7f, 1.0f);

	int nWidth = 10;
	float fWidthDistance = 200.0f;
	float fRadius = 1000.0f;
	for (int i = 0; i < nWidth; i++)
	{
		D3DXVECTOR3 spawnpos = pos;
		spawnpos.x = ((static_cast<float>(nWidth) * 0.5f) * fWidthDistance) - fWidthDistance * i;

		CEffect3D::Create(
			spawnpos,
			mylib_const::DEFAULT_VECTOR3,
			col,
			fRadius,
			2,
			CEffect3D::MOVEEFFECT_ADD,
			CEffect3D::TYPE_POINT);
	}

	D3DXVECTOR3 spawnpos = pos;
	spawnpos.x -= 400.0f;
	spawnpos.z -= 800.0f;

	CEffect3D::Create(
		spawnpos,
		mylib_const::DEFAULT_VECTOR3,
		col,
		fRadius,
		2,
		CEffect3D::MOVEEFFECT_ADD,
		CEffect3D::TYPE_POINT);

	spawnpos = pos;
	spawnpos.x += 400.0f;
	spawnpos.z -= 800.0f;
	CEffect3D::Create(
		spawnpos,
		mylib_const::DEFAULT_VECTOR3,
		col,
		fRadius,
		2,
		CEffect3D::MOVEEFFECT_ADD,
		CEffect3D::TYPE_POINT);

	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (m_pObjChara[i] == NULL)
		{
			continue;
		}

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
	D3DXVECTOR3 weponpos = m_pMotion[nIdx]->GetAttackPosition(m_apModel[ATKInfo.nCollisionNum], ATKInfo);

	// 種類別
	switch (m_pMotion[nIdx]->GetType())
	{
	case MOTION_STARTUP:
		CEffectStartupEye::Create(weponpos);

		// エンター押下判定ON
		CTitle::SetEnablePressEnter();
		break;
	}
}

//==========================================================================
// 攻撃判定中処理
//==========================================================================
void CUnionTitle::AttackInDicision(int nIdx, CMotion::AttackInfo ATKInfo)
{
	// 基底の攻撃判定中処理
	CPlayerUnion::AttackInDicision(nIdx, ATKInfo);

	// モーション情報取得
	int nMotionType = m_pMotion[nIdx]->GetType();
	D3DXVECTOR3 weponpos = m_pMotion[nIdx]->GetAttackPosition(m_apModel[ATKInfo.nCollisionNum], ATKInfo);

	// モーション別処理
	switch (nMotionType)
	{
	case MOTION_STARTUP:
		// 振動
		CManager::GetInstance()->GetCamera()->SetShake(30, 25.0f, 0.0f);
		break;
	}
}
