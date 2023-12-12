//=============================================================================
// 
//  プレイヤー処理 [player_title.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "game.h"
#include "player_title.h"
#include "manager.h"
#include "debugproc.h"
#include "input.h"
#include "model.h"
#include "motion.h"
#include "objectChara.h"
#include "shadow.h"
#include "calculation.h"
#include "3D_effect.h"

//==========================================
//  定数定義 : 金崎朋弥
//==========================================
namespace
{
	// ファイルパス
	const char* CHARAFILE =
	{
		"data\\TEXT\\character\\player\\motion_player.txt"
	};

	const float MOVE_SPEED = 1.8f; // 移動量倍率
}

//==========================================
//  静的メンバ変数宣言
//==========================================
int CPlayerTitle::m_nIdx = 0;

//==========================================================================
// コンストラクタ
//==========================================================================
CPlayerTitle::CPlayerTitle(int nPriority) : CPlayer(nPriority),
m_nModelType(NONE),
m_posTarget(0.0f),
m_bMove(false)
{
	// 値のクリア
	
	// インデックスを記録
	m_nMyPlayerIdx = m_nIdx;

	// インデックスを加算
	++m_nIdx;
}

//==========================================================================
// デストラクタ
//==========================================================================
CPlayerTitle::~CPlayerTitle()
{
	// インデックスを減算
	--m_nIdx;
}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CPlayerTitle::Init(void)
{
	// 種類の設定
	SetType(TYPE_PLAYER);

	m_state = STATE_NONE;	// 状態

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
	
	// モデルの差し替え
	switch (m_nModelType)
	{
	case PLAYER_BODY:
		SetEvolusion(CGameManager::STATUS_LIFE, true);
		break;

	case PLAYER_ARM:
		SetEvolusion(CGameManager::STATUS_POWER, true);
		break;

	case PLAYER_LEG:
		SetEvolusion(CGameManager::STATUS_SPEED, true);
		break;

	default:
		break;
	}

	// テクスチャを設定
	BindByPlayerIdxTexture();

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

	// 動き出す処理
	if (m_bMove)
	{
		if (m_nModelType == PLAYER_ARM) // 腕は飛び上がる
		{
			Fly();
		}
		else // その他は走り出す
		{
			Forward();
		}

		// 位置を更新
		D3DXVECTOR3 pos = GetPosition();
		pos += GetMove();
		SetPosition(pos);

		// 炎を呼び出す
		Fire();
	}

	// シーンを取得
	if (CManager::GetInstance()->GetScene()->GetMode() == CScene::MODE_DECIDE)
	{
		// 移動処理
		Move();
	}

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

//==========================================
//  生成処理 : 金崎朋弥
//==========================================
CPlayerTitle* CPlayerTitle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL type)
{
	// インスタンス生成
	CPlayerTitle* pPlayer = DEBUG_NEW CPlayerTitle;

	//モデルを設定
	pPlayer->m_nModelType = (int)type;

	// 初期化処理
	pPlayer->Init();

	// 値を保存
	pPlayer->SetTarget(pos.z);
	pPlayer->SetPosition(pos);
	pPlayer->SetRotation(rot);

	return pPlayer;
}

//==========================================
//  回転
//==========================================
void CPlayerTitle::Rotation(void)
{
	// 移動モーションにする
	m_pMotion->Set(CPlayer::MOTION_WALK);

	// 移動方向を算出
	D3DXVECTOR3 move = -GetMove();
	D3DXVECTOR3 rotTarget = GetRotation();
	rotTarget.y = atan2f(move.x, move.z);

	// 角度の正規化
	RotNormalize(rotTarget);

	// 目的の方向と現在の方向の佐分を算出
	D3DXVECTOR3 rot = GetRotation();
	D3DXVECTOR3 rotdiff = rotTarget - rot;

	// 角度の正規化
	RotNormalize(rotdiff);

	// 方向転換速度を補正
	rotdiff *= 0.1f;

	// 角度を加算
	rot += rotdiff;

	// 移動方向を適用
	SetRotation(rot);
}

//==========================================
//  移動する処理
//==========================================
void CPlayerTitle::Move(void)
{
	// 値の取得
	D3DXVECTOR3 pos = GetPosition(); // 位置
	D3DXVECTOR3 move = GetMove(); // 移動量

	// 移動制限
	if (pos.z > m_posTarget) // 移動量制限
	{
		// 停止
		pos.z = m_posTarget;
		move.z = 0.0f;

		// 待機モーションにする
		m_pMotion->Set(CPlayer::MOTION_DEF);
	}
	else if (pos.z < 0.0f) // 移動量制限
	{
		// 停止
		pos.z = 0.0f;
		move.z = 0.0f;

		// 待機モーションにする
		m_pMotion->Set(CPlayer::MOTION_DEF);
	}

	// あたいってばさいきょーね！
	pos += move;

	// 動いてるときは向きを変える
	if (move.z != 0.0f)
	{
		// 回転処理
		Rotation();
	}

	// 値の適用
	SetPosition(pos);
	SetMove(move);
}

//==========================================
//  飛び上がる
//==========================================
void CPlayerTitle::Fly(void)
{
	// 角度の取得
	D3DXVECTOR3 rot = GetRotation();

	// 移動量を取得
	float fMove = GetVelocity();
	D3DXVECTOR3 move = GetMove();

	// 移動量を分解する
	move.y = fMove * MOVE_SPEED;

	// 移動量を適用する
	SetMove(move);
}

//==========================================
//  走り出す
//==========================================
void CPlayerTitle::Forward(void)
{
	// 移動モーションにする
	m_pMotion->Set(CPlayer::MOTION_WALK);

	// 角度の取得
	D3DXVECTOR3 rot = GetRotation();

	// 移動量を取得
	float fMove = GetVelocity();
	D3DXVECTOR3 move = GetMove();

	// 移動量を分解する
	move.x = -sinf(rot.y) * fMove * MOVE_SPEED;
	move.z = -cosf(rot.y) * fMove * MOVE_SPEED;

	// 移動量を適用する
	SetMove(move);
}

//==========================================
//  エフェクトを呼び出す
//==========================================
void CPlayerTitle::Fire(void)
{
	// 向きを取得
	D3DXVECTOR3 rot = GetRotation();

	// モーションの情報取得
	CMotion::Info aInfo = m_pMotion->GetInfo(MOTION_WALK);

	// 攻撃情報の総数取得
	int nNumAttackInfo = aInfo.nNumAttackInfo;

	CEffect3D* pEffect = NULL;
	// 武器の位置
	for (int nCntAttack = 0; nCntAttack < nNumAttackInfo; nCntAttack++)
	{
		D3DXVECTOR3 weponpos = m_pMotion->GetAttackPosition(GetModel(), *aInfo.AttackInfo[nCntAttack]);

		D3DXVECTOR3 ModelRot = GetModel()[aInfo.AttackInfo[nCntAttack]->nCollisionNum]->GetRotation();
		ModelRot.x = GetModel()[0]->GetRotation().z;

		// 炎
		float fMove = 5.5f + Random(-20, 20) * 0.1f;
		float fRot = Random(-20, 20) * 0.01f;

		pEffect = CEffect3D::Create(
			weponpos,
			D3DXVECTOR3(
				sinf(ModelRot.x) * (sinf(D3DX_PI + rot.y + fRot) * fMove),
				cosf(D3DX_PI + ModelRot.x) * fMove,
				sinf(ModelRot.x) * (cosf(D3DX_PI + rot.y + fRot) * fMove)),
			D3DXCOLOR(1.0f + Random(-10, 0) * 0.01f, 0.0f, 0.0f, 1.0f),
			40.0f + (float)Random(-10, 10),
			15,
			CEffect3D::MOVEEFFECT_ADD,
			CEffect3D::TYPE_SMOKE);

		if (pEffect != NULL)
		{
			// セットアップ位置設定
			pEffect->SetUp(aInfo.AttackInfo[nCntAttack]->Offset, GetModel()[aInfo.AttackInfo[nCntAttack]->nCollisionNum]->GetPtrWorldMtx(), CObject::GetObject(), SetEffectParent(pEffect));
		}

		fRot = Random(-20, 20) * 0.01f;
		// 炎
		pEffect = CEffect3D::Create(
			weponpos,
			D3DXVECTOR3(
				sinf(ModelRot.x) * (sinf(D3DX_PI + rot.y + fRot) * fMove),
				cosf(D3DX_PI + ModelRot.x) * fMove,
				sinf(ModelRot.x) * (cosf(D3DX_PI + rot.y + fRot) * fMove)),
			D3DXCOLOR(0.8f + Random(-10, 0) * 0.01f, 0.5f + Random(-10, 0) * 0.01f, 0.0f, 1.0f),
			25.0f + (float)Random(-5, 5),
			15,
			CEffect3D::MOVEEFFECT_ADD,
			CEffect3D::TYPE_SMOKE);
		if (pEffect != NULL)
		{
			// セットアップ位置設定
			pEffect->SetUp(aInfo.AttackInfo[nCntAttack]->Offset, GetModel()[aInfo.AttackInfo[nCntAttack]->nCollisionNum]->GetPtrWorldMtx(), CObject::GetObject(), SetEffectParent(pEffect));
		}
	}
}
