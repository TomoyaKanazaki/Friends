//=============================================================================
// 
//  チュートリアルプレイヤー処理 [tutorialplayer.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "tutorial.h"
#include "tutorialplayer.h"
#include "tutorialstep.h"
#include "camera.h"
#include "manager.h"
#include "debugproc.h"
#include "renderer.h"
#include "input.h"
#include "motion.h"
#include "sound.h"
#include "particle.h"
#include "scene.h"
#include "calculation.h"
#include "model.h"
#include "3D_effect.h"
#include "shadow.h"

//==========================================================================
// マクロ定義
//==========================================================================

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================

//==========================================================================
// コンストラクタ
//==========================================================================
CTutorialPlayer::CTutorialPlayer(int nPriority) : CPlayer(nPriority)
{
	// 値のクリア
	
}

//==========================================================================
// デストラクタ
//==========================================================================
CTutorialPlayer::~CTutorialPlayer()
{

}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CTutorialPlayer::Init(void)
{
	// 親の初期化処理
	CPlayer::Init();

	return S_OK;
}

//==========================================================================
// モード別終了処理
//==========================================================================
void CTutorialPlayer::UninitByMode(void)
{
	CScene *pScene = CManager::GetInstance()->GetScene();

	if (pScene != nullptr)
	{
		CPlayer **ppPlayer = pScene->GetPlayer();

		// プレイヤーをNULL
		*ppPlayer = nullptr;
	}
}

//==========================================================================
// 更新処理
//==========================================================================
void CTutorialPlayer::Update(void)
{
	// 死亡の判定
	if (IsDeath() == true)
	{// 死亡フラグが立っていたら
		return;
	}

	// 親の更新処理(enemymanager等の関係で不使用)
	//CPlayer::Update();

	Controll();

	// 死亡の判定
	if (IsDeath() == true)
	{// 死亡フラグが立っていたら
		return;
	}

	if (IsDeath() == true)
	{
		return;
	}

	// キーボード情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	if (pInputKeyboard->GetTrigger(DIK_F5) == true)
	{// F5でリセット
		SetPosition(D3DXVECTOR3(0.0f, 0.0f, -1000.0f));
		SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	//// コンボ演出中は抜ける
	//if (CTutorial::GetEnemyManager()->GetState() == CEnemyManager::STATE_COMBOANIM)
	//{
	//	return;
	//}

	// 過去の位置保存
	SetOldPosition(GetPosition());

	// モーションの設定処理
	//MotionSet();

	// モーション更新
	if (m_pMotion != nullptr)
	{
		m_pMotion->Update(GetStatus().fSpeedBuff);
	}

	//// 攻撃処理
	//Atack();

	//// 状態更新
	//UpdateState();

	// 位置取得
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 posCenter = GetCenterPosition();

	// 移動量取得
	D3DXVECTOR3 move = GetMove();

	// 向き取得
	D3DXVECTOR3 rot = GetRotation();

	//// 追従目標の情報設定
	//if (m_nChaseTopIdx == m_nMyPlayerIdx)
	//{
	//	// カメラの情報取得
	//	CCamera *pCamera = CManager::GetInstance()->GetCamera();
	//	pCamera->SetTargetPosition(pos);
	//	pCamera->SetTargetRotation(rot);
	//}

	// 影の位置更新
	if (m_pShadow != nullptr)
	{
		m_pShadow->SetPosition(D3DXVECTOR3(pos.x, m_pShadow->GetPosition().y, pos.z));
	}

	// モーションの情報取得
	if (m_pMotion != nullptr)
	{
		CMotion::Info aInfo = m_pMotion->GetInfo(MOTION_WALK);

		// 攻撃情報の総数取得
		int nNumAttackInfo = aInfo.nNumAttackInfo;

		int nCntEffect = 0;
		int nNumEffect = GetEffectParentNum();
		for (int i = 0; i < mylib_const::MAX_OBJ; i++)
		{
			CEffect3D *pEffect = GetEffectParent(i);
			if (pEffect == nullptr)
			{// nullptrだったら
				continue;
			}

			// エフェクトの位置更新
			pEffect->UpdatePosition(GetRotation());
			nCntEffect++;
			if (nNumEffect <= nCntEffect)
			{
				break;
			}
		}
	}

	// ステップごとの更新
	UpdateByStep();

#if 1
	// デバッグ表示
	CManager::GetInstance()->GetDebugProc()->Print(
		"------------------[プレイヤーの操作]------------------\n"
		"位置：【X：%f, Y：%f, Z：%f】【X：%f, Y：%f, Z：%f】 【W / A / S / D】\n"
		"向き：【X：%f, Y：%f, Z：%f】 【Z / C】\n"
		"移動量：【X：%f, Y：%f, Z：%f】\n"
		"体力：【%d】\n", pos.x, pos.y, pos.z, posCenter.x, posCenter.y, posCenter.z, rot.x, rot.y, rot.y, move.x, move.y, move.z, GetLife());
#endif
}

//==========================================================================
// ステップごとの更新処理
//==========================================================================
void CTutorialPlayer::UpdateByStep(void)
{
	// ステップの設定
	CTutorial::GetStep()->SetStep(CTutorialStep::STEP_WAIT);
}

//==========================================================================
// 操作処理
//==========================================================================
void CTutorialPlayer::Controll(void)
{
	// キーボード情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// ゲームパッド情報取得
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	// カメラの情報取得
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	// カメラの向き取得
	D3DXVECTOR3 Camerarot = pCamera->GetRotation();

	// 位置取得
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 newPosition = GetPosition();
	D3DXVECTOR3 sakiPos = GetPosition();

	// 移動量取得
	D3DXVECTOR3 move = GetMove();

	// 向き取得
	D3DXVECTOR3 rot = GetRotation();

	// 目標の向き取得
	float fRotDest = GetRotDest();

	// 現在の種類取得
	int nMotionType = m_pMotion->GetType();

	// 移動量取得
	float fMove = GetVelocity() * GetStatus().fSpeedBuff;

	// 経過時間取得
	float fCurrentTime = CManager::GetInstance()->GetDeltaTime();

	// ステップを進める
	//CTutorial::GetStep()->SetStep(CTutorialStep::STEP_WAIT);

	if (true)
	{// 行動できるとき

		if (m_pMotion->IsGetMove(nMotionType) == 1 &&
			m_state != STATE_DEAD &&
			m_state != STATE_FADEOUT &&
			m_state != STATE_COMPACTUNION &&
			m_state != STATE_RELEASEUNION &&
			m_state != STATE_EVOLUSION)
		{// 移動可能モーションの時

			if (pInputKeyboard->GetPress(DIK_A) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).x < 0)
			{//←キーが押された,左移動

			 // 移動中にする
				m_sMotionFrag.bMove = true;

				if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y > 0)
				{//A+W,左上移動

					move.x += sinf(-D3DX_PI * 0.25f + Camerarot.y) * fMove;
					move.z += cosf(-D3DX_PI * 0.25f + Camerarot.y) * fMove;
					fRotDest = D3DX_PI * 0.75f + Camerarot.y;
				}
				else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y < 0)
				{//A+S,左下移動

					move.x += sinf(-D3DX_PI * 0.75f + Camerarot.y) * fMove;
					move.z += cosf(-D3DX_PI * 0.75f + Camerarot.y) * fMove;
					fRotDest = D3DX_PI * 0.25f + Camerarot.y;
				}
				else
				{//A,左移動

					move.x += sinf(-D3DX_PI * 0.5f + Camerarot.y) * fMove;
					move.z += cosf(-D3DX_PI * 0.5f + Camerarot.y) * fMove;
					fRotDest = D3DX_PI * 0.5f + Camerarot.y;
				}
			}
			else if (pInputKeyboard->GetPress(DIK_D) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).x > 0)
			{//Dキーが押された,右移動

			 // 移動中にする
				m_sMotionFrag.bMove = true;

				if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y > 0)
				{//D+W,右上移動

					move.x += sinf(D3DX_PI * 0.25f + Camerarot.y) * fMove;
					move.z += cosf(D3DX_PI * 0.25f + Camerarot.y) * fMove;
					fRotDest = -D3DX_PI * 0.75f + Camerarot.y;
				}
				else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y < 0)
				{//D+S,右下移動

					move.x += sinf(D3DX_PI * 0.75f + Camerarot.y) * fMove;
					move.z += cosf(D3DX_PI * 0.75f + Camerarot.y) * fMove;
					fRotDest = -D3DX_PI * 0.25f + Camerarot.y;
				}
				else
				{//D,右移動

					move.x += sinf(D3DX_PI * 0.5f + Camerarot.y) * fMove;
					move.z += cosf(D3DX_PI * 0.5f + Camerarot.y) * fMove;
					fRotDest = -D3DX_PI * 0.5f + Camerarot.y;
				}
			}
			else if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y > 0)
			{//Wが押された、上移動

			 // 移動中にする
				m_sMotionFrag.bMove = true;
				move.x += sinf(D3DX_PI * 0.0f + Camerarot.y) * fMove;
				move.z += cosf(D3DX_PI * 0.0f + Camerarot.y) * fMove;
				fRotDest = D3DX_PI * 1.0f + Camerarot.y;
			}
			else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y < 0)
			{//Sが押された、下移動

			 // 移動中にする
				m_sMotionFrag.bMove = true;
				move.x += sinf(D3DX_PI * 1.0f + Camerarot.y) * fMove;
				move.z += cosf(D3DX_PI * 1.0f + Camerarot.y) * fMove;
				fRotDest = D3DX_PI * 0.0f + Camerarot.y;
			}
			else
			{
				// 移動中かどうか
				m_sMotionFrag.bMove = false;
			}

		}
		else if (m_pMotion->IsGetMove(nMotionType) == 0 &&
			m_state != STATE_DEAD &&
			m_state != STATE_FADEOUT &&
			m_state != STATE_COMPACTUNION &&
			m_state != STATE_RELEASEUNION&&
			m_state != STATE_EVOLUSION)
		{
			if (pInputKeyboard->GetPress(DIK_A) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).x < 0)
			{//←キーが押された,左移動

				if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y > 0)
				{//A+W,左上移動
					fRotDest = D3DX_PI * 0.75f + Camerarot.y;
				}
				else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y < 0)
				{//A+S,左下移動
					fRotDest = D3DX_PI * 0.25f + Camerarot.y;
				}
				else
				{//A,左移動
					fRotDest = D3DX_PI * 0.5f + Camerarot.y;
				}
			}
			else if (pInputKeyboard->GetPress(DIK_D) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).x > 0)
			{//Dキーが押された,右移動

				if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y > 0)
				{//D+W,右上移動
					fRotDest = -D3DX_PI * 0.75f + Camerarot.y;
				}
				else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y < 0)
				{//D+S,右下移動
					fRotDest = -D3DX_PI * 0.25f + Camerarot.y;
				}
				else
				{//D,右移動
					fRotDest = -D3DX_PI * 0.5f + Camerarot.y;
				}
			}
			else if (pInputKeyboard->GetPress(DIK_W) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y > 0)
			{//Wが押された、上移動
				fRotDest = D3DX_PI * 1.0f + Camerarot.y;
			}
			else if (pInputKeyboard->GetPress(DIK_S) == true || pInputGamepad->GetStickMoveL(m_nMyPlayerIdx).y < 0)
			{//Sが押された、下移動
				fRotDest = D3DX_PI * 0.0f + Camerarot.y;
			}
		}
	}

	if (m_state != STATE_COMPACTUNION &&
		m_state != STATE_RELEASEUNION &&
		CManager::GetInstance()->GetByPlayerPartsType(m_nMyPlayerIdx) != CGameManager::STATUS_SPEED)
	{// 移動中
		m_nCntWalk = (m_nCntWalk + 1) % 4;

		if (m_nCntWalk == 0)
		{
			// モーションの情報取得
			CMotion::Info aInfo = m_pMotion->GetInfo(MOTION_WALK);

			// 攻撃情報の総数取得
			int nNumAttackInfo = aInfo.nNumAttackInfo;

			CEffect3D *pEffect = nullptr;
			// 武器の位置
			for (int nCntAttack = 0; nCntAttack < nNumAttackInfo; nCntAttack++)
			{
				D3DXVECTOR3 weponpos = m_pMotion->GetAttackPosition(GetModel(), *aInfo.AttackInfo[nCntAttack]);

				D3DXVECTOR3 ModelRot = GetModel()[aInfo.AttackInfo[nCntAttack]->nCollisionNum]->GetRotation();
				ModelRot.x = GetModel()[0]->GetRotation().z;

				//D3DXVECTOR3 ModelRot = WorldMtxChangeToRotation(GetModel()[aInfo.AttackInfo[nCntAttack]->nCollisionNum]->GetWorldMtx());

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

				if (pEffect != nullptr)
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
				if (pEffect != nullptr)
				{
					// セットアップ位置設定
					pEffect->SetUp(aInfo.AttackInfo[nCntAttack]->Offset, GetModel()[aInfo.AttackInfo[nCntAttack]->nCollisionNum]->GetPtrWorldMtx(), CObject::GetObject(), SetEffectParent(pEffect));
				}
			}
		}
	}

	// 移動量加算
	newPosition.x += move.x;
	newPosition.z += move.z;

	sakiPos.x = newPosition.x + sinf(D3DX_PI + rot.y) * GetRadius();
	sakiPos.z = newPosition.z + cosf(D3DX_PI + rot.y) * GetRadius();

	// 角度の正規化
	RotNormalize(fRotDest);

	// 現在と目標の差分を求める
	float fRotDiff = fRotDest - rot.y;

	// 角度の正規化
	RotNormalize(fRotDiff);

	// 角度の補正をする
	rot.y += fRotDiff * 0.15f;

	// 角度の正規化
	RotNormalize(rot.y);

	// 重力処理
	if (m_state != STATE_KNOCKBACK && m_state != STATE_DMG && m_state != STATE_DEAD && m_state != STATE_FADEOUT && m_state != STATE_COMPACTUNION)
	{
		move.y -= mylib_const::GRAVITY;

		// 位置更新
		newPosition.y += move.y;
		sakiPos.y = newPosition.y;
	}

	// 射出台の着地判定
	//m_bLandInjectionTable[m_nMyPlayerIdx] = false;

	//**********************************
	// 当たり判定
	//**********************************
	bool bLandStage = Collision(sakiPos, move);

	bool bMove = false;
	if (m_bLandOld == false && bLandStage == true)
	{// 前回は着地していなくて、今回は着地している場合

		bMove = false;
	}

	if (m_bLandOld == true && bLandStage == true)
	{// 前回も今回も着地している場合
		bMove = true;
	}

	if (m_bHitWall == false &&
		(bLandStage == false || bMove == true || m_bLandField == true || m_bJump == true || m_sMotionFrag.bKnockBack == true || m_sMotionFrag.bDead == true))
	{
		pos.x = newPosition.x;
		pos.z = newPosition.z;
		pos.y = sakiPos.y;
		Collision(pos, move);

		// 前回は乗ってたことにする
		m_bLandOld = true;
	}
	else
	{
		D3DXVECTOR3 posOld = GetOldPosition();
		pos.x = posOld.x;
		pos.z = posOld.z;
		pos = posOld;
		move.x = 0.0f;
		pos.y -= mylib_const::GRAVITY * 7.0f;

		if (m_bJump == false)
		{
			m_bJump = true;
		}

		Collision(pos, move);
	}

	// 位置更新
	//pos.y += move.y;

	// 慣性補正
	if (m_state != STATE_KNOCKBACK && m_state != STATE_DMG && m_state != STATE_DEAD && m_state != STATE_FADEOUT)
	{
		move.x += (0.0f - move.x) * 0.25f;
		move.z += (0.0f - move.z) * 0.25f;
	}

	// 位置設定
	SetPosition(pos);

	// 移動量設定
	SetMove(move);

	// 向き設定
	SetRotation(rot);

	// 目標の向き設定
	SetRotDest(fRotDest);

	int nType = m_pMotion->GetType();
	if (nType != MOTION_ATK)
	{
		// 攻撃の入力カウンター減算
		m_nCntInputAtk--;
		if (m_nCntInputAtk <= 0)
		{
			m_nCntInputAtk = 0;
			m_nAtkLevel = 0;
		}
	}

	if (m_state != STATE_DEAD &&
		m_state != STATE_FADEOUT &&
		m_state != STATE_COMPACTUNION)
	{// 行動できるとき

		if (m_sMotionFrag.bATK == false &&
			(pInputGamepad->GetTrigger(CInputGamepad::BUTTON_A, m_nMyPlayerIdx) || pInputKeyboard->GetTrigger(DIK_RETURN)))
		{// 攻撃

		 // 攻撃判定ON
			m_sMotionFrag.bJump = false;
			m_sMotionFrag.bATK = true;

			//if (m_nCntInputAtk >= 0)
			//{// まだ猶予があったら

			//	// 攻撃の段階加算
			//	m_nAtkLevel++;
			//	ValueNormalize(m_nAtkLevel, MAX_ATKCOMBO, 0);
			//}

			// 攻撃の入力カウンターリセット
			/*m_nCntInputAtk = INTERVAL_ATK;*/
		}
	}


//#if _DEBUG
//	static CGameManager::eStatus s_statusType;
//	if (pInputKeyboard->GetTrigger(DIK_RIGHT) == true)
//	{// ←キーが押された,左移動
//		s_statusType = (CGameManager::eStatus)(((int)s_statusType + 1) % (int)CGameManager::STATUS_MAX);
//		SetEvolusion(s_statusType, true);
//	}
//
//	if (pInputKeyboard->GetPress(DIK_UP) == true)
//	{// SPACEが押された,ジャンプ
//
//	 // アイテムドロップ
//		CItem::Create(D3DXVECTOR3(pos.x, pos.y + 100.0f, pos.z), D3DXVECTOR3(0.0f, Random(-31, 31) * 0.1f, 0.0f));
//	}
//#endif
//
//	if (pInputKeyboard->GetTrigger(DIK_LEFT) == true)
//	{
//		CCollisionObject::Create(GetPosition(), mylib_const::DEFAULT_VECTOR3, 10000.0f, 3, 10000, CCollisionObject::TAG_PLAYER);
//	}
}