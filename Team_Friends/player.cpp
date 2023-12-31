//=============================================================================
// 
//  プレイヤー処理 [player.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "game.h"
#include "player.h"
#include "player_union.h"
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
#include "instantfade.h"
#include "fade.h"
#include "listmanager.h"
#include "item.h"
#include "injectiontable.h"
#include "object_circlegauge2D.h"
#include "statuswindow.h"
#include "collisionobject.h"
#include "limitereamanager.h"
#include "beam.h"
#include "statusup.h"

// 派生先
#include "tutorialplayer.h"

//==========================================================================
// 定数定義
//==========================================================================
namespace
{
	const char* CHARAFILE = "data\\TEXT\\character\\player\\motion_player.txt";	// キャラクターファイル
	const char* EVOLUSIONFILE[CGameManager::STATUS_MAX] =						// 進化先のファイル
	{
		"data\\TEXT\\character\\player\\motion_pUPArm.txt",		// 火力
		"data\\TEXT\\character\\player\\motion_pUPLeg.txt",		// 駆動性
		"data\\TEXT\\character\\player\\motion_pUPBody.txt",	// 耐久
	};
	const char* TEXTURE_INITPLAYER[mylib_const::MAX_PLAYER][mylib_const::MAX_PLAYER] =	// 初期プレイヤーのテクスチャ
	{
		{// 初期プレイヤー
			"data\\TEXTURE\\player\\init\\init_UV.jpg",
			"data\\TEXTURE\\player\\init\\init_UV_Blue.jpg",
			"data\\TEXTURE\\player\\init\\init_UV_Green.jpg",
			"data\\TEXTURE\\player\\init\\init_UV_Yellow.jpg",
		},
		{// 変更タグ1(腕)
			"data\\TEXTURE\\player\\pUP_arm01\\arm_UV_Red.jpg",
			"data\\TEXTURE\\player\\pUP_arm01\\arm_UV_Blue.jpg",
			"data\\TEXTURE\\player\\pUP_arm01\\arm_UV_Green.jpg",
			"data\\TEXTURE\\player\\pUP_arm01\\arm_UV_Yellow.jpg",
		},
		{// 変更タグ2(脚)
			"data\\TEXTURE\\player\\pUP_leg01\\feet_UV_Red.jpg",
			"data\\TEXTURE\\player\\pUP_leg01\\feet_UV_Blue.jpg",
			"data\\TEXTURE\\player\\pUP_leg01\\feet_UV_Green.jpg",
			"data\\TEXTURE\\player\\pUP_leg01\\feet_UV_Yellow.jpg",
		},
		{// 変更タグ3(胴)
			"data\\TEXTURE\\player\\pUP_body01\\body_UV_Red.jpg",
			"data\\TEXTURE\\player\\pUP_body01\\body_UV_Blue.jpg",
			"data\\TEXTURE\\player\\pUP_body01\\body_UV_Green.jpg",
			"data\\TEXTURE\\player\\pUP_body01\\body_UV_Yellow.jpg",
		}
	};
	const D3DXCOLOR EFFECTCOLOR[mylib_const::MAX_PLAYER] =	// エフェクトの色
	{
		{ 0.9f, 0.1f, 0.1f, 1.0f },
		{ 0.1f, 0.1f, 0.9f, 1.0f },
		{ 0.1f, 0.9f, 0.1f, 1.0f },
		{ 0.9f, 0.6f, 0.1f, 1.0f },
	};
	const float JUMP = 20.0f * 1.5f;	// ジャンプ力初期値
	const int INVINCIBLE_INT = 2;		// 無敵の間隔
	const int INVINCIBLE_TIME = 90;		// 無敵の時間
	const int DEADTIME = 120;			// 死亡時の時間
	const int FADEOUTTIME = 60;			// フェードアウトの時間
	const int MAX_ATKCOMBO = 2;			// 攻撃コンボの最大数
	const int INTERVAL_ATK = 15;		// 攻撃の猶予
	const int MAX_BUFFSTATUS = 100;		// ステータスのバフ最大値
}

//==========================================================================
// 静的メンバ変数宣言
//==========================================================================
bool CPlayer::m_bAllLandInjectionTable = false;						// 全員の射出台着地判定
bool CPlayer::m_bLandInjectionTable[mylib_const::MAX_PLAYER] = {};	// 射出台の着地判定
int CPlayer::m_nChaseTopIdx = 0;	// 追従の先頭インデックス番号

//==========================================================================
// コンストラクタ
//==========================================================================
CPlayer::CPlayer(int nPriority) : CObjectChara(nPriority)
{
	// 値のクリア
	// 共有変数
	m_bJump = false;					// ジャンプ中かどうか
	m_bLandOld = false;					// 過去の着地情報
	m_bHitStage = false;				// ステージの当たり判定
	m_bLandField = false;				// フィールドの着地判定
	m_bHitWall = false;					// 壁の当たり判定
	m_nCntWalk = 0;						// 歩行カウンター
	m_nCntInputAtk = 0;					// 攻撃の入力カウンター
	m_nAtkLevel = 0;					// 攻撃の段階
	m_state = STATE_NONE;				// 状態
	m_pMotion = NULL;					// モーションの情報
	m_sMotionFrag.bATK = false;			// モーションのフラグ
	m_sMotionFrag.bJump = false;		// モーションのフラグ
	m_sMotionFrag.bKnockBack = false;	// モーションのフラグ
	m_sMotionFrag.bDead = false;		// モーションのフラグ
	m_sMotionFrag.bMove = false;		// モーションのフラグ

	// プライベート変数
	memset(&m_sStatus, 0, sizeof(m_sStatus));		// ステータス情報
	m_Oldstate = STATE_NONE;						// 前回の状態
	m_mMatcol = mylib_const::DEFAULT_COLOR;			// マテリアルの色
	m_posKnokBack = mylib_const::DEFAULT_VECTOR3;	// ノックバックの位置
	m_KnokBackMove = mylib_const::DEFAULT_VECTOR3;	// ノックバックの移動量
	m_nCntState = 0;								// 状態遷移カウンター
	m_nEvolveType = 0;								// 進化先の種類
	m_nNextEvolveType = 0;							// 次の進化先
	m_nMyPlayerIdx = 0;								// プレイヤーインデックス番号
	m_pShadow = NULL;								// 影の情報
	m_pTargetP = NULL;								// 目標の地点
}

//==========================================================================
// デストラクタ
//==========================================================================
CPlayer::~CPlayer()
{

}

//==========================================================================
// 生成処理
//==========================================================================
CPlayer *CPlayer::Create(int nIdx)
{
	// 生成用のオブジェクト
	CPlayer *pPlayer = NULL;

	if (pPlayer == NULL)
	{// NULLだったら

		// メモリの確保
		switch (CManager::GetInstance()->GetMode())
		{
		case CScene::MODE_GAME:
			pPlayer = DEBUG_NEW CPlayer;
			break;

		case CScene::MODE_TUTORIAL:
			pPlayer = DEBUG_NEW CTutorialPlayer;
			break;

		default:
			return NULL;
			break;
		}

		if (pPlayer != NULL)
		{// メモリの確保が出来ていたら

			// プレイヤーインデックス番号
			pPlayer->m_nMyPlayerIdx = nIdx;

			// 初期化処理
			pPlayer->Init();
		}

		return pPlayer;
	}

	return NULL;
}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CPlayer::Init(void)
{
	// 種類の設定
	SetType(TYPE_PLAYER);

	m_state = STATE_NONE;	// 状態
	m_nCntState = 0;		// 状態遷移カウンター
	m_bLandOld = true;		// 前回の着地状態
	m_bAllLandInjectionTable = false;	// 全員の射出台着地判定
	memset(&m_bLandInjectionTable[0], false, sizeof(m_bLandInjectionTable));	// 射出台の着地判定
	m_nChaseTopIdx = 0;		// 追従の先頭インデックス番号

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

	//if (m_nMyPlayerIdx == 2 ||
	//	m_nMyPlayerIdx == 3)
	//{// うで
	//	SetEvolusion(CGameManager::STATUS_POWER);
	//}
	//if (m_nMyPlayerIdx == 0)
	//{// 胴
	//	SetEvolusion(CGameManager::STATUS_LIFE);
	//}

	//if (m_nMyPlayerIdx == 1)
	//{// 胴
	//	SetEvolusion(CGameManager::STATUS_SPEED);
	//}
	//SetEvolusion(CGameManager::STATUS_POWER);

	// プレイヤー毎のインデックス追加
	BindByPlayerIdxTexture();

	// バフ計算
	m_sStatus.fPowerBuff = 1.0f;
	m_sStatus.fSpeedBuff = 1.0f;
	m_sStatus.fLifeBuff = 1.0f;
	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CPlayer::Uninit(void)
{
	if (m_pMotion != NULL)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = NULL;
	}

	// 影を消す
	if (m_pShadow != NULL)
	{
		//m_pShadow->Uninit();
		m_pShadow = NULL;
	}

	// 終了処理
	CObjectChara::Uninit();

	// モード別終了処理
	UninitByMode();
}

//==========================================================================
// モード別終了処理
//==========================================================================
void  CPlayer::UninitByMode(void)
{
	CScene *pScene = CManager::GetInstance()->GetScene();
	if (pScene != NULL)
	{
		// プレイヤーをNULL
		CManager::GetInstance()->GetScene()->UninitPlayer(m_nMyPlayerIdx);
	}
}

//==========================================================================
// 終了処理
//==========================================================================
void CPlayer::Kill(void)
{

	my_particle::Create(GetPosition(), my_particle::TYPE_ENEMY_FADE);

	// 影を消す
	if (m_pShadow != NULL)
	{
		m_pShadow->Uninit();
		m_pShadow = NULL;
	}
}

//==========================================================================
// 更新処理
//==========================================================================
void CPlayer::Update(void)
{
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

	// エディット中は抜ける
	if (CGame::GetElevation()->IsEdit())
	{
		return;
	}

	// エディット中は抜ける
	if (CGame::GetEditType() != CGame::EDITTYPE_OFF)
	{
		return;
	}

	// コンボ演出中は抜ける
	if (CGame::GetEnemyManager()->GetState() == CEnemyManager::STATE_COMBOANIM)
	{
		return;
	}

	// 過去の位置保存
	SetOldPosition(GetPosition());

	// 操作
	Controll();

	// モーションの設定処理
	MotionSet();

	// モーション更新
	if (m_pMotion != NULL)
	{
		m_pMotion->Update(m_sStatus.fSpeedBuff);
	}

	// 攻撃処理
	Atack();

	// 状態更新
	UpdateState();

	// ゲージの割合更新
	CStatusWindow *pStatusWindow = CGame::GetStatusWindow(m_nMyPlayerIdx);
	if (pStatusWindow != NULL)
	{
		pStatusWindow->GetGauge(CGameManager::STATUS_LIFE)->SetRateDest((float)GetLife() / (float)GetLifeOrigin());
	}

	// 位置取得
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 posCenter = GetCenterPosition();

	// 移動量取得
	D3DXVECTOR3 move = GetMove();

	// 向き取得
	D3DXVECTOR3 rot = GetRotation();

	// 追従目標の情報設定
	if (m_nChaseTopIdx == m_nMyPlayerIdx)
	{
		// カメラの情報取得
		CCamera *pCamera = CManager::GetInstance()->GetCamera();
		pCamera->SetTargetPosition(pos);
		pCamera->SetTargetRotation(rot);
	}

	// 影の位置更新
	if (m_pShadow != NULL)
	{
		m_pShadow->SetPosition(D3DXVECTOR3(pos.x, m_pShadow->GetPosition().y, pos.z));
	}

	// モーションの情報取得
	if (m_pMotion != NULL)
	{
		CMotion::Info aInfo = m_pMotion->GetInfo(MOTION_WALK);

		// 攻撃情報の総数取得
		int nNumAttackInfo = aInfo.nNumAttackInfo;

		int nCntEffect = 0;
		int nNumEffect = GetEffectParentNum();
		for (int i = 0; i < mylib_const::MAX_OBJ; i++)
		{
			CEffect3D *pEffect = GetEffectParent(i);
			if (pEffect == NULL)
			{// NULLだったら
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

#if 0
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
// 操作処理
//==========================================================================
void CPlayer::Controll(void)
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
	float fMove = GetVelocity() * m_sStatus.fSpeedBuff;

	// 経過時間取得
	float fCurrentTime = CManager::GetInstance()->GetDeltaTime();

	if (CGame::GetGameManager()->IsControll())
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

			CEffect3D *pEffect = NULL;
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
	m_bLandInjectionTable[m_nMyPlayerIdx] = false;

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

	if (CGame::GetGameManager()->IsControll() &&
		m_state != STATE_DEAD &&
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
			m_nCntInputAtk = INTERVAL_ATK;
		}
	}


#if _DEBUG
	static CGameManager::eStatus s_statusType;
	if (pInputKeyboard->GetTrigger(DIK_RIGHT) == true)
	{// ←キーが押された,左移動
		s_statusType = (CGameManager::eStatus)(((int)s_statusType + 1) % (int)CGameManager::STATUS_MAX);
		SetEvolusion(s_statusType, false);
	}

	if (pInputKeyboard->GetPress(DIK_UP) == true)
	{// SPACEが押された,ジャンプ

		// アイテムドロップ
		CItem::Create(D3DXVECTOR3(pos.x, pos.y + 100.0f, pos.z), D3DXVECTOR3(0.0f, Random(-31, 31) * 0.1f, 0.0f));
	}

	if (pInputKeyboard->GetTrigger(DIK_LEFT) == true)
	{
		CCollisionObject::Create(GetPosition(), mylib_const::DEFAULT_VECTOR3, 100000.0f, 3, 10000, CCollisionObject::TAG_PLAYER);
	}
#endif
}

//==========================================================================
// モーションの設定
//==========================================================================
void CPlayer::MotionSet(void)
{
	if (m_pMotion == NULL)
	{// モーションがNULLだったら
		return;
	}

	if (m_pMotion->IsFinish() == true)
	{// 終了していたら

		// 現在の種類取得
		int nType = m_pMotion->GetType();
		int nOldType = m_pMotion->GetOldType();

		if (m_sMotionFrag.bMove == true && m_sMotionFrag.bATK == false && m_sMotionFrag.bKnockBack == false && m_sMotionFrag.bDead == false && m_bJump == false)
		{// 移動していたら

			m_sMotionFrag.bMove = false;	// 移動判定OFF

			// 移動モーション
			m_pMotion->Set(MOTION_WALK);
		}
		else if (m_sMotionFrag.bJump == true && m_sMotionFrag.bATK == false && m_sMotionFrag.bKnockBack == false && m_sMotionFrag.bDead == false)
		{// ジャンプ中

			// ジャンプのフラグOFF
			m_sMotionFrag.bJump = false;

			// ジャンプモーション
			m_pMotion->Set(MOTION_JUMP);
		}
		else if (m_bJump == true && m_sMotionFrag.bJump == false && m_sMotionFrag.bATK == false && m_sMotionFrag.bKnockBack == false && m_sMotionFrag.bDead == false)
		{// ジャンプ中&&ジャンプモーションが終わってる時

			// 落下モーション
			m_pMotion->Set(MOTION_FALL);
		}
		else if (m_sMotionFrag.bKnockBack == true)
		{// やられ中だったら

			// やられモーション
			m_pMotion->Set(MOTION_KNOCKBACK);
		}
		else if (m_sMotionFrag.bDead == true)
		{// 死亡中だったら

			// やられモーション
			m_pMotion->Set(MOTION_DEAD);
		}
		else if (m_sMotionFrag.bATK == true)
		{// 攻撃していたら

			m_sMotionFrag.bATK = false;		// 攻撃判定OFF

			//(MAX_ATKCOMBO - m_nCntInputAtk) - 1;
			m_pMotion->Set(MOTION_ATK + m_nAtkLevel, true);

			// 攻撃の段階加算
			m_nAtkLevel++;
			if (m_nAtkLevel >= MAX_ATKCOMBO)
			{
				m_nAtkLevel = 0;
			}

		}
		else
		{
			// ニュートラルモーション
			m_pMotion->Set(MOTION_DEF);
		}
	}
}

//==========================================================================
// 攻撃
//==========================================================================
void CPlayer::Atack(void)
{
	if (m_pMotion == NULL)
	{// モーションがNULLだったら
		return;
	}

	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// 向き取得
	D3DXVECTOR3 rot = GetRotation();

	// カメラの情報取得
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	// カメラの向き取得
	D3DXVECTOR3 Camerarot = pCamera->GetRotation();

	// モーションの情報取得
	CMotion::Info aInfo = m_pMotion->GetInfo(m_pMotion->GetType());

	// 攻撃情報の総数取得
	int nNumAttackInfo = aInfo.nNumAttackInfo;

	for (int nCntAttack = 0; nCntAttack < nNumAttackInfo; nCntAttack++)
	{
		if (aInfo.AttackInfo[nCntAttack] == NULL)
		{// NULLだったら
			continue;
		}

		if (m_pMotion->IsImpactFrame(*aInfo.AttackInfo[nCntAttack]))
		{// 衝撃のカウントと同じとき

			// 種類別
			switch (m_pMotion->GetType())
			{
			case MOTION_ATK:
			case MOTION_ATK2:

				switch (CManager::GetInstance()->GetByPlayerPartsType(m_nMyPlayerIdx))
				{
				case CPlayerUnion::PARTS_BODY:
					AttackBody(*aInfo.AttackInfo[nCntAttack]);
					break;

				case CPlayerUnion::PARTS_R_ARM:
				case CPlayerUnion::PARTS_L_ARM:
					AttackArm(*aInfo.AttackInfo[nCntAttack]);
					break;

				case CPlayerUnion::PARTS_LEG:
					AttackLeg(*aInfo.AttackInfo[nCntAttack]);
					break;

				default:
					AttackNormal(*aInfo.AttackInfo[nCntAttack]);
					break;
				}

				// スイング音再生
				CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_SWING);
				break;

			case MOTION_EVOLUTION:

				// 進化先別
				switch ((m_nEvolveType - 1))
				{
				case CGameManager::STATUS_LIFE:
				case CGameManager::STATUS_POWER:
				case CGameManager::STATUS_SPEED:
					my_particle::Create(GetCenterPosition(), my_particle::TYPE_EVOLUSION_DECIDE);
					break;

				default:

					// 進化先変更
					m_nEvolveType = m_nNextEvolveType;

					// パーツ変更
					ChangeObject(m_nEvolveType);

					// モーション切り替え
					ChangeMotion(EVOLUSIONFILE[static_cast<int>(m_nEvolveType) - 1]);

					// プレイヤー毎のインデックス追加
					BindByPlayerIdxTexture();

					// ポーズのリセット
					m_pMotion->ResetPose(MOTION_EVOLUTION);
					m_pMotion->Set(MOTION_EVOLUTION);
					break;
				}
				break;
			}
		}

		// モーションカウンター取得
		float fAllCount = m_pMotion->GetAllCount();
		if (fAllCount > aInfo.AttackInfo[nCntAttack]->nMinCnt && fAllCount < aInfo.AttackInfo[nCntAttack]->nMaxCnt)
		{// 攻撃判定中
			
			// 武器の位置
			D3DXVECTOR3 weponpos = m_pMotion->GetAttackPosition(GetModel(), *aInfo.AttackInfo[nCntAttack]);

			CEffect3D *pEffect = NULL;

			switch (m_pMotion->GetType())
			{
			case MOTION_EVOLUTION:
			{
				D3DXVECTOR3 nor = (aInfo.AttackInfo[nCntAttack]->Offset);
				D3DXVec3Normalize(&nor, &nor);

				D3DXVECTOR3 move = D3DXVECTOR3(10.0f, 0.0f, 0.0f);

				// 炎
				float fMove = 4.5f + Random(-10, 10) * 0.1f;
				float fRot = Random(-20, 20) * 0.01f;

				pEffect = CEffect3D::Create(
					weponpos,
					(fMove * nor),
					D3DXCOLOR(1.0f + Random(-10, 0) * 0.01f, 0.0f, 0.0f, 1.0f),
					20.0f + (float)Random(-10, 10),
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
					(fMove * nor),
					D3DXCOLOR(0.8f + Random(-10, 0) * 0.01f, 0.5f + Random(-10, 0) * 0.01f, 0.0f, 1.0f),
					12.0f + (float)Random(-5, 5),
					15,
					CEffect3D::MOVEEFFECT_ADD,
					CEffect3D::TYPE_SMOKE);
				if (pEffect != NULL)
				{
					// セットアップ位置設定
					pEffect->SetUp(aInfo.AttackInfo[nCntAttack]->Offset, GetModel()[aInfo.AttackInfo[nCntAttack]->nCollisionNum]->GetPtrWorldMtx(), CObject::GetObject(), SetEffectParent(pEffect));
				}

				if ((int)fAllCount % 8 == 0)
				{
					for (int i = 0; i < 1; i++)
					{
						int repeat = (int)(fAllCount / 8.0f);
						CEffect3D::Create(
							D3DXVECTOR3(GetCenterPosition().x, GetCenterPosition().y + 100.0f, GetCenterPosition().z - 200.0f),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							EFFECTCOLOR[m_nMyPlayerIdx],
							20.0f, 20, CEffect3D::MOVEEFFECT_ADD, CEffect3D::TYPE_NORMAL, repeat * 1.1f);
					}
				}
			}
				break;

			case MOTION_ATK:
			case MOTION_ATK2:
				// 進化先別
				switch (CManager::GetInstance()->GetByPlayerPartsType(m_nMyPlayerIdx))
				{
				case CPlayerUnion::PARTS_BODY:
					my_particle::Create(weponpos, my_particle::TYPE_ATTACK_BODY);

					if ((int)fAllCount % 8 == 0)
					{
						for (int i = 0; i < 4; i++)
						{
							int repeat = (int)(fAllCount / 8.0f);
							CEffect3D::Create(
								weponpos,
								D3DXVECTOR3(0.0f, 0.0f, 0.0f),
								mylib_const::PLAYERBEAM_COLOR,
								20.0f, 16, CEffect3D::MOVEEFFECT_ADD, CEffect3D::TYPE_POINT, repeat * 4.0f);
						}
					}
					break;

				case CPlayerUnion::PARTS_R_ARM:
				case CPlayerUnion::PARTS_L_ARM:
					break;

				case CPlayerUnion::PARTS_LEG:
					break;

				default:
					break;
				}
				break;
			}

#if _DEBUG
			//CEffect3D::Create(weponpos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), aInfo.AttackInfo[nCntAttack]->fRangeSize, 10, CEffect3D::MOVEEFFECT_NONE, CEffect3D::TYPE_NORMAL);
#endif

			if (CManager::GetInstance()->GetScene()->GetMode() != CScene::MODE_GAME)
			{// ゲーム以外は通るな
				CManager::GetInstance()->GetDebugProc()->Print(
					"モーションカウンター：%d\n", m_pMotion->GetAllCount());

				continue;
			}

			// 敵取得
			CEnemy **ppEnemy = CGame::GetEnemyManager()->GetEnemy();

			// 総数取得
			int nNumAll = CGame::GetEnemyManager()->GetNumAll();
			int i = -1, nCntEnemy = 0;

			while (1)
			{
				if (nCntEnemy >= nNumAll)
				{// 総数超えたら終わり
					break;
				}

				// インデックス加算
				i++;
				if (ppEnemy[i] == NULL)
				{
					continue;
				}

				// 敵の位置取得
				D3DXVECTOR3 TargetPos = ppEnemy[i]->GetPosition();

				// 判定サイズ取得
				float fTargetRadius = ppEnemy[i]->GetRadius();

				if (SphereRange(weponpos, TargetPos, aInfo.AttackInfo[nCntAttack]->fRangeSize, fTargetRadius))
				{// 球の判定

					int nDamage = (int)((float)aInfo.AttackInfo[nCntAttack]->nDamage * m_sStatus.fPowerBuff);
					if (ppEnemy[i]->Hit(nDamage) == true)
					{// 当たってたら

					}
				}

				// 敵の数加算
				nCntEnemy++;
			}
		}
	}

	CManager::GetInstance()->GetDebugProc()->Print(
		"モーションカウンター：%d\n", m_pMotion->GetAllCount());
}

//==========================================================================
// 通常攻撃
//==========================================================================
void CPlayer::AttackNormal(CMotion::AttackInfo attackInfo)
{
	// 向き取得
	D3DXVECTOR3 rot = GetRotation();
	D3DXVECTOR3 weponpos = m_pMotion->GetAttackPosition(GetModel(), attackInfo);

	// 武器の位置
	for (int i = 0; i < 4; i++)
	{
		// 炎
		float fMove = 7.0f + Random(-2, 5);
		float fRot = Random(-20, 20) * 0.01f;
		float fRotMove = Random(-10, 10) * 0.01f;

		// 炎
		CEffect3D *pEffect = CEffect3D::Create(
			weponpos,
			D3DXVECTOR3(
				sinf(D3DX_PI + rot.y + fRotMove) * fMove,
				fRotMove,
				cosf(D3DX_PI + rot.y + fRotMove) * fMove),
			D3DXCOLOR(1.0f + Random(-10, 0) * 0.01f, 0.0f, 0.0f, 1.0f),
			90.0f + (float)Random(-10, 10),
			15,
			CEffect3D::MOVEEFFECT_ADD,
			CEffect3D::TYPE_SMOKE);

		// 炎
		CEffect3D::Create(
			weponpos,
			D3DXVECTOR3(
				sinf(D3DX_PI + rot.y + fRotMove) * fMove,
				fRotMove,
				cosf(D3DX_PI + rot.y + fRotMove) * fMove),
			D3DXCOLOR(0.8f + Random(-10, 0) * 0.01f, 0.5f + Random(-10, 0) * 0.01f, 0.0f, 1.0f),
			60.0f + (float)Random(-10, 10),
			15,
			CEffect3D::MOVEEFFECT_ADD,
			CEffect3D::TYPE_SMOKE);

		int nDamage = (int)((float)attackInfo.nDamage * m_sStatus.fPowerBuff);
		CCollisionObject::Create(pEffect->GetPosition(), pEffect->GetMove(), pEffect->GetSize().x, 15, nDamage, CCollisionObject::TAG_PLAYER);
	}
}

//==========================================================================
// 腕攻撃
//==========================================================================
void CPlayer::AttackArm(CMotion::AttackInfo attackInfo)
{

}

//==========================================================================
// 脚攻撃
//==========================================================================
void CPlayer::AttackLeg(CMotion::AttackInfo attackInfo)
{

}

//==========================================================================
// 胴攻撃
//==========================================================================
void CPlayer::AttackBody(CMotion::AttackInfo attackInfo)
{
	// 向き取得
	D3DXVECTOR3 rot = GetRotation();
	D3DXVECTOR3 weponpos = m_pMotion->GetAttackPosition(GetModel(), attackInfo);
	int nDamage = (int)((float)attackInfo.nDamage * m_sStatus.fPowerBuff);
	float fMove = 28.0f;
	D3DXCOLOR col = D3DXCOLOR(
		mylib_const::PLAYERBEAM_COLOR.r + Random(-100, 100) * 0.001f,
		mylib_const::PLAYERBEAM_COLOR.g + Random(-100, 100) * 0.001f,
		mylib_const::PLAYERBEAM_COLOR.b + Random(-100, 100) * 0.001f,	// 色
		1.0f);

	switch (m_pMotion->GetType())
	{
	case MOTION_ATK:
		CBeam::Create(
			weponpos,
			D3DXVECTOR3(
				sinf(D3DX_PI + rot.y) * fMove,	// 位置
				cosf(D3DX_PI * 0.65f) * fMove,
				cosf(D3DX_PI + rot.y) * fMove),	// 移動量
			col,	// 色
			20.0f,	// 半径
			200.0f,	// 長さ
			15,		// 寿命
			18,		// 密度
			nDamage,	// ダメージ
			CCollisionObject::TAG_PLAYER	// タグ
		);
		break;

	case MOTION_ATK2:
		fMove = 32.0f;
		CBeam::Create(
			weponpos,
			D3DXVECTOR3(
				sinf(D3DX_PI + rot.y) * fMove,	// 位置
				cosf(D3DX_PI * 0.65f) * fMove,
				cosf(D3DX_PI + rot.y) * fMove),	// 移動量
			col,		// 色
			25.0f,		// 半径
			200.0f,		// 長さ
			40,			// 寿命
			24,			// 密度
			nDamage,	// ダメージ
			CCollisionObject::TAG_PLAYER	// タグ
		);
		break;
	}

	col.a = 0.8f;
	// 衝撃波生成
	CImpactWave::Create
	(
		weponpos,	// 位置
		D3DXVECTOR3(D3DX_PI * 0.5f, D3DX_PI + rot.y, 0.0f),				// 向き
		col,			// 色
		18.0f,						// 幅
		8.0f,						// 高さ
		20.0f,						// 中心からの距離
		10,							// 寿命
		10.0f,						// 幅の移動量
		CImpactWave::TYPE_PURPLE4,	// テクスチャタイプ
		true						// 加算合成するか
	);
}

//==========================================================================
// 当たり判定
//==========================================================================
bool CPlayer::Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &move)
{

	// 向き取得
	D3DXVECTOR3 rot = GetRotation();

	// 着地したかどうか
	bool bLand = false;
	float fHeight = 0.0f;
	m_bLandField = false;
	m_bHitWall = false;			// 壁の当たり判定

	// 高さ取得
	if (m_state != STATE_KNOCKBACK && m_state != STATE_DMG && m_state != STATE_DEAD && m_state != STATE_FADEOUT)
	{
		fHeight = CManager::GetInstance()->GetScene()->GetElevation()->GetHeight(pos, bLand);
	}
	else
	{
		fHeight = pos.y;
	}

	if (fHeight > pos.y)
	{// 地面の方が自分より高かったら

	 // 地面の高さに補正
		pos.y = fHeight;
		m_bLandField = true;

		if (bLand == true)
		{// 着地してたら

		 // ジャンプ使用可能にする
			m_bJump = false;
			move.y = 0.0f;
			m_bLandOld = true;
		}
	}


	// Xファイルとの判定
	CStage *pStage = CGame::GetStage();
	if (pStage == NULL)
	{// NULLだったら
		return false;
	}

	bool bNowLand = false;

	// ステージに当たった判定
	m_bHitStage = false;
	for (int nCntStage = 0; nCntStage < pStage->GetNumAll(); nCntStage++)
	{
		// オブジェクト取得
		CObjectX *pObjX = pStage->GetObj(nCntStage);

		if (pObjX == NULL)
		{// NULLだったら
			continue;
		}

		// 高さ取得
		bool bLand = false;
		fHeight = pObjX->GetHeight(pos, bLand);

		if (bLand == true && fHeight > pos.y)
		{// 地面の方が自分より高かったら

		 // 地面の高さに補正
			if (pos.y + 50.0f <= fHeight)
			{// 自分より壁が高すぎる
				m_bHitWall = true;
			}
			else
			{
				pos.y = fHeight;
			}

			m_bHitStage = true;
			m_bLandField = false;

			if (bLand == true)
			{// 着地してたら

				if ((m_sMotionFrag.bKnockBack || m_bJump == true) && GetPosition().y >= fHeight)
				{
					m_bLandOld = true;
				}

				if (m_bJump == true)
				{// ジャンプ中だったら
					m_pMotion->ToggleFinish(true);
				}

				// ジャンプ使用可能にする
				m_bJump = false;
				move.y = 0.0f;
				bNowLand = true;
				m_sMotionFrag.bJump = false;
			}
		}
	}

	// オブジェクト取得
	CObjectX *pObjX = pStage->GetInjectionTable();

	// 高さ取得
	bLand = false;
	fHeight = pObjX->GetHeight(pos, bLand);

	if (bLand == true && fHeight > pos.y)
	{// 地面の方が自分より高かったら

		// 地面の高さに補正
		if (pos.y + 50.0f <= fHeight)
		{// 自分より壁が高すぎる
			m_bHitWall = true;
		}
		else
		{
			pos.y = fHeight;
		}

		m_bHitStage = true;
		m_bLandField = false;

		if (bLand == true)
		{// 着地してたら

			if ((m_sMotionFrag.bKnockBack || m_bJump == true) && GetPosition().y >= fHeight)
			{
				m_bLandOld = true;
			}

			if (m_bJump == true)
			{// ジャンプ中だったら
				m_pMotion->ToggleFinish(true);
			}

			// ジャンプ使用可能にする
			m_bJump = false;
			move.y = 0.0f;
			bNowLand = true;
			m_sMotionFrag.bJump = false;

			// 射出台の着地判定
			m_bLandInjectionTable[m_nMyPlayerIdx] = true;

		}
	}

	int nLandNum = 0;
	for (int i = 0; i < CManager::GetInstance()->GetNumPlayer(); i++)
	{
		// 射出台の着地確認
		if (m_bLandInjectionTable[i] == true)
		{
			nLandNum++;
		}
	}

	// 全員着地状態設定
	if (nLandNum >= CManager::GetInstance()->GetNumPlayer())
	{
		m_bAllLandInjectionTable = true;
	}
	else
	{
		m_bAllLandInjectionTable = false;
	}

	if (CGame::GetGameManager()->GetType() == CGameManager::SCENE_MAINCLEAR &&
		pStage->GetInjectionTable()->GetState() != CInjectionTable::STATE_UP)
	{// 通常クリアだったら

		if (m_bAllLandInjectionTable == true)
		{// 全員射出台に乗っている

			// チャージ状態
			pStage->GetInjectionTable()->SetState(CInjectionTable::STATE_CHARGE);
		}
		else
		{
			// リセット
			pStage->GetInjectionTable()->SetState(CInjectionTable::STATE_NONE, 0);
		}
	}


	// エリア制限情報取得
	CLimitAreaManager *pLimitManager = CGame::GetLimitEreaManager();
	CLimitArea **ppLimit = pLimitManager->GetLimitErea();

	// 総数取得
	int nNumAll = pLimitManager->GetNumAll();
	int i = -1, nCntErea = 0;

	while (1)
	{
		if (nCntErea >= nNumAll)
		{// 総数超えたら終わり
			break;
		}

		// インデックス加算
		i++;
		if (ppLimit[i] == NULL)
		{
			continue;
		}
		CLimitArea::sLimitEreaInfo info = ppLimit[i]->GetLimitEreaInfo();

		// 大人の壁を適用
		if (pos.x + GetRadius() >= info.fMaxX) { pos.x = info.fMaxX - GetRadius(); }
		if (pos.x - GetRadius() <= info.fMinX) { pos.x = info.fMinX + GetRadius(); }
		if (pos.z + GetRadius() >= info.fMaxZ) { pos.z = info.fMaxZ - GetRadius(); }
		if (pos.z - GetRadius() <= info.fMinZ) { pos.z = info.fMinZ + GetRadius(); }

		// エリアの数加算
		nCntErea++;
	}

	// 向き設定
	SetRotation(rot);

	return bNowLand;
}

//==========================================================================
// ヒット処理
//==========================================================================
bool CPlayer::Hit(const int nValue)
{
	// 体力取得
	int nLife = GetLife();

	//if (nLife <= 0)
	//{
	//	// 死んだ
	//	return true;
	//}

	if (m_state != STATE_DMG &&
		m_state != STATE_KNOCKBACK &&
		m_state != STATE_INVINCIBLE &&
		m_state != STATE_DEAD &&
		m_state != STATE_FADEOUT &&
		m_state != STATE_COMPACTUNION &&
		m_state != STATE_RELEASEUNION)
	{// ダメージ受付状態の時

		// 体力減らす
		nLife -= nValue;


		// ゲームパッド情報取得
		CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();
		pInputGamepad->SetVibration(CInputGamepad::VIBRATION_STATE_DMG, 0);

		m_KnokBackMove.y += 18.0f;
		m_bHitStage = false;

		// 体力設定
		SetLife(nLife);

		if (nLife <= 0)
		{// 体力がなくなったら

			// 死状態
			m_state = STATE_DEAD;

			m_KnokBackMove.y = 8.0f;

			// 遷移カウンター設定
			m_nCntState = DEADTIME;

			// 体力設定
			SetLife(0);

			// ノックバック判定にする
			m_sMotionFrag.bKnockBack = true;

			// やられモーション
			m_pMotion->Set(MOTION_KNOCKBACK);

			// ノックバックの位置更新
			D3DXVECTOR3 pos = GetPosition();
			D3DXVECTOR3 rot = GetRotation();
			m_posKnokBack = pos;

			// 衝撃波生成
			CImpactWave::Create
			(
				D3DXVECTOR3(pos.x, pos.y + 80.0f, pos.z),	// 位置
				D3DXVECTOR3(D3DX_PI * 0.5f, D3DX_PI + rot.y, D3DX_PI),				// 向き
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f),			// 色
				80.0f,										// 幅
				80.0f,										// 高さ
				0.0f,										// 中心からの間隔
				20,											// 寿命
				10.0f,										// 幅の移動量
				CImpactWave::TYPE_GIZAWHITE,				// テクスチャタイプ
				false										// 加算合成するか
			);

			CManager::GetInstance()->SetEnableHitStop(18);

			// 振動
			CManager::GetInstance()->GetCamera()->SetShake(21, 30.0f, 0.0f);

			// 死んだ
			return true;
		}

		// 過去の状態保存
		m_Oldstate = m_state;

		// 色設定
		m_mMatcol = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		// ダメージ状態にする
		m_state = STATE_DMG;

		// 遷移カウンター設定
		m_nCntState = 0;

		// ノックバックの位置更新
		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 rot = GetRotation();
		m_posKnokBack = pos;

		// ノックバック判定にする
		m_sMotionFrag.bKnockBack = true;

		// やられモーション
		m_pMotion->Set(MOTION_KNOCKBACK);

		// 衝撃波生成
		CImpactWave::Create
		(
			D3DXVECTOR3(pos.x, pos.y + 80.0f, pos.z),	// 位置
			D3DXVECTOR3(D3DX_PI * 0.5f, D3DX_PI + rot.y, D3DX_PI),				// 向き
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f),			// 色
			80.0f,										// 幅
			80.0f,										// 高さ
			0.0f,										// 中心からの間隔
			20,											// 寿命
			10.0f,										// 幅の移動量
			CImpactWave::TYPE_GIZAWHITE,				// テクスチャタイプ
			false										// 加算合成するか
		);

		CManager::GetInstance()->SetEnableHitStop(12);

		// 振動
		CManager::GetInstance()->GetCamera()->SetShake(12, 25.0f, 0.0f);

		// サウンド再生
		CManager::GetInstance()->GetSound()->PlaySound(CSound::LABEL_SE_PLAYERDMG);
	}

	// 死んでない
	return false;
}

//==========================================================================
// ステータス付与
//==========================================================================
bool CPlayer::GiveStatus(CGameManager::eStatus status)
{
	// 取得判定
	bool bGet = false;

	// 強化
	int nStatus = 0;
	switch (status)
	{
	case CGameManager::STATUS_POWER:
		if (m_sStatus.nPower < MAX_BUFFSTATUS)
		{
			m_sStatus.nPower++;
			bGet = true;
		}
		nStatus = m_sStatus.nPower;
		break;

	case CGameManager::STATUS_SPEED:
		if (m_sStatus.nSpeed < MAX_BUFFSTATUS)
		{
			m_sStatus.nSpeed++;
			bGet = true;
		}
		nStatus = m_sStatus.nSpeed;
		break;

	case CGameManager::STATUS_LIFE:
		if (m_sStatus.nLife < MAX_BUFFSTATUS)
		{
			m_sStatus.nLife++;
			bGet = true;
		}
		break;
	}

	// 割合
	float fRate = (float)nStatus / (float)MAX_BUFFSTATUS;

	// バフ計算
	m_sStatus.fPowerBuff = 1.0f + ((float)m_sStatus.nPower * 0.01f);
	m_sStatus.fSpeedBuff = 1.0f + ((float)m_sStatus.nSpeed * 0.01f);
	m_sStatus.fLifeBuff = 1.0f + ((float)m_sStatus.nLife * 0.1f);

	if (status == CGameManager::STATUS_POWER || status == CGameManager::STATUS_SPEED)
	{
		// ステータスウィンドウ
		CStatusWindow *pStatusWindow = CGame::GetStatusWindow(m_nMyPlayerIdx);
		if (pStatusWindow != NULL)
		{
			// ゲージの割合更新
			pStatusWindow->GetGauge(status)->SetRateDest(fRate);
		}
	}

	if (bGet)
	{// 取得している場合
		D3DXVECTOR3 pos = GetPosition();
		pos.y += 50.0f;

		// ステータス上昇UI生成
		CStatusUp::Create(pos, status);
	}
	return bGet;
}

//==========================================================================
// 進化先抽選
//==========================================================================
void CPlayer::DrawingEvolusion(void)
{
	// 進化先のインデックス番号
	int nIdxPowerLeft = 0, nIdxPowerRight = 0, nIdxSpeed = 0, nIdxLife = 0;

	// プレイヤーの取得
	for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
	{
		CPlayer *pPlayer = CManager::GetInstance()->GetScene()->GetPlayer(i);
		if (pPlayer == NULL)
		{
			continue;
		}

	}
}

//==========================================================================
// 進化先設定
//==========================================================================
void CPlayer::SetEvolusion(CGameManager::eStatus statusType, bool bFast)
{
	// プレイヤー毎の担当パーツ種類設定
	switch (statusType)
	{
	case CGameManager::STATUS_POWER:
	{
		bool bR_Arm = false, bL_Arm = false;
		for (int i = 0; i < mylib_const::MAX_PLAYER; i++)
		{
			int nPartsType = CManager::GetInstance()->GetByPlayerPartsType(i);
			if (nPartsType == CPlayerUnion::PARTS_R_ARM)
			{
				bR_Arm = true;
			}
			else if (nPartsType == CPlayerUnion::PARTS_L_ARM)
			{
				bL_Arm = true;
			}
		}

		// 腕の使用状況別設定
		if (bR_Arm == false && bL_Arm == false)
		{
			CManager::GetInstance()->SetByPlayerPartsType(m_nMyPlayerIdx, CPlayerUnion::PARTS_R_ARM);
		}
		else if (bR_Arm == true && bL_Arm == false)
		{
			CManager::GetInstance()->SetByPlayerPartsType(m_nMyPlayerIdx, CPlayerUnion::PARTS_L_ARM);
		}
		else
		{
			CManager::GetInstance()->SetByPlayerPartsType(m_nMyPlayerIdx, CPlayerUnion::PARTS_R_ARM);
		}
	}
		break;

	case CGameManager::STATUS_SPEED:
		CManager::GetInstance()->SetByPlayerPartsType(m_nMyPlayerIdx, CPlayerUnion::PARTS_LEG);
		break;

	case CGameManager::STATUS_LIFE:
		CManager::GetInstance()->SetByPlayerPartsType(m_nMyPlayerIdx, CPlayerUnion::PARTS_BODY);
		break;
	}

	if (bFast)
	{
		// 進化先の種類
		m_nEvolveType = (int)statusType + 1;

		// パーツ変更
		ChangeObject(m_nEvolveType);

		// モーション切り替え
		ChangeMotion(EVOLUSIONFILE[(int)statusType]);

		// プレイヤー毎のインデックス追加
		BindByPlayerIdxTexture();
	}
	else
	{
		// 次の進化先
		m_nNextEvolveType = (int)statusType + 1;

		// 進化状態にする
		m_state = STATE_EVOLUSION;

		// 進化モーション設定
		m_pMotion->Set(MOTION_EVOLUTION);

		// 目標の向き設定
		SetRotDest(0.0f);

		// 進化中
		CGame::GetGameManager()->SetType(CGameManager::SCENE_EVOLUSION);
	}
}

//==========================================================================
// プレイヤーインデックス毎のテクスチャ設定
//==========================================================================
void CPlayer::BindByPlayerIdxTexture(void)
{
	// ファイルインデックス番号取得
	int nIdxXFile = GetIdxFile();
	CObjectChara::Load LoadData = GetLoadData(nIdxXFile);

	// モデル取得
	CModel **ppModel = GetModel();

	// 初期テクスチャ
	int nIdxTex = CManager::GetInstance()->GetTexture()->Regist(TEXTURE_INITPLAYER[0][m_nMyPlayerIdx]);
	for (int i = 0; i < GetNumModel(); i++)
	{
		if (ppModel[i] == NULL)
		{
			continue;
		}

		// Xファイルのデータ取得
		CXLoad::SXFile *pXData = CScene::GetXLoad()->GetMyObject(ppModel[i]->GetIdxXFile());

		for (int nMat = 0; nMat < (int)pXData->dwNumMat; nMat++)
		{
			ppModel[i]->SetIdxTexture(nMat, nIdxTex);
		}
	}

	// 種類別テクスチャ切り替え
	for (int i = 0; i < LoadData.nNumModel; i++)
	{
		if (LoadData.LoadData[i].nSwitchType != m_nEvolveType)
		{// 変更のタグと違うもの
			continue;
		}

		if (LoadData.LoadData[i].nIDSwitchModel < 0)
		{// 新しいパーツ

			// テクスチャ読み込み
			int nIdxTex = CManager::GetInstance()->GetTexture()->Regist(TEXTURE_INITPLAYER[m_nEvolveType][m_nMyPlayerIdx]);

			// Xファイルのデータ取得
			CXLoad::SXFile *pXData = CScene::GetXLoad()->GetMyObject(ppModel[i]->GetIdxXFile());

			for (int nMat = 0; nMat < (int)pXData->dwNumMat; nMat++)
			{
				ppModel[i]->SetIdxTexture(nMat, nIdxTex);
			}
		}
		else
		{// 切り替えの場合

			if (ppModel[LoadData.LoadData[i].nIDSwitchModel] == NULL)
			{
				continue;
			}

			// テクスチャ読み込み
			int nIdxTex = CManager::GetInstance()->GetTexture()->Regist(TEXTURE_INITPLAYER[m_nEvolveType][m_nMyPlayerIdx]);

			// Xファイルのデータ取得
			CXLoad::SXFile *pXData = CScene::GetXLoad()->GetMyObject(ppModel[LoadData.LoadData[i].nIDSwitchModel]->GetIdxXFile());

			for (int nMat = 0; nMat < (int)pXData->dwNumMat; nMat++)
			{
				ppModel[LoadData.LoadData[i].nIDSwitchModel]->SetIdxTexture(nMat, nIdxTex);
			}
		}
	}
}

//==========================================================================
// モーションファイル
//==========================================================================
void CPlayer::ChangeMotion(const char* pMotionFile)
{
	if (m_pMotion != NULL)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = NULL;
	}

	// モーションの生成処理
	m_pMotion = CMotion::Create(pMotionFile);

	// オブジェクトキャラクターの情報取得
	CObjectChara *pObjChar = GetObjectChara();

	// モーションの設定
	m_pMotion->SetModel(pObjChar->GetModel(), pObjChar->GetNumModel(), CObjectChara::GetObjectChara());

	// ポーズのリセット
	m_pMotion->ResetPose(MOTION_DEF);
}

//==========================================================================
// 状態更新処理
//==========================================================================
void CPlayer::UpdateState(void)
{
	switch (m_state)
	{
	case STATE_NONE:
		// 色設定
		m_mMatcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;

	case STATE_INVINCIBLE:
		Invincible();
		break;

	case STATE_DMG:
		Damage();
		break;

	case STATE_DEAD:
		Dead();
		break;

	case STATE_FADEOUT:
		FadeOut();
		break;

	case STATE_KNOCKBACK:
		KnockBack();
		break;

	case STATE_COMPACTUNION:
		StateCompactUnion();
		break;

	case STATE_RELEASEUNION:
		StateReleaseUnion();
		break;

	case STATE_EVOLUSION:
		StateEvolusion();
		break;
	}
}

//==========================================================================
// 無敵
//==========================================================================
void CPlayer::Invincible(void)
{
	// 状態遷移カウンター減算
	m_nCntState--;

	if (m_nCntState % INVINCIBLE_INT == 0)
	{// 規定間隔
		
		// 色設定
		if (m_mMatcol.a == 1.0f)
		{
			m_mMatcol.a = 0.4f;
		}
		else
		{
			m_mMatcol.a = 1.0f;
		}
	}

	if (m_nCntState <= 0)
	{// 遷移カウンターが0になったら

		// なにもない状態にする
		m_state = STATE_NONE;
		m_nCntState = 0;

		// 色設定
		m_mMatcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

}

//==========================================================================
// ダメージ
//==========================================================================
void CPlayer::Damage(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// 移動量取得
	D3DXVECTOR3 move = GetMove();

	// 向き取得
	D3DXVECTOR3 rot = GetRotation();

	// 状態遷移カウンター減算
	m_nCntState++;

	// 色設定
	m_mMatcol = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	// 位置更新
	pos.y = (-0.4f * (float)(m_nCntState * m_nCntState) + m_KnokBackMove.y * (float)m_nCntState) + m_posKnokBack.y;
	pos.x += move.x;
	/*pos.x += move.x;
	pos.z += move.z;*/

	// 起伏との判定
	if ((CManager::GetInstance()->GetScene()->GetElevation()->IsHit(pos) || m_bHitStage) && m_nCntState >= 10)
	{// 地面と当たっていたら
		m_state = STATE_INVINCIBLE;
		m_nCntState = INVINCIBLE_TIME;
		m_KnokBackMove.y = 0.0f;	// 移動量ゼロ
		m_bLandOld = true;

		// 色設定
		m_mMatcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ノックバック判定消す
		m_sMotionFrag.bKnockBack = false;
		m_pMotion->ToggleFinish(true);


		// Xファイルとの判定
		CStage *pStage = CGame::GetStage();
		if (pStage == NULL)
		{// NULLだったら
			return;
		}

		// ステージに当たった判定
		for (int nCntStage = 0; nCntStage < pStage->GetNumAll(); nCntStage++)
		{
			// オブジェクト取得
			CObjectX *pObjX = pStage->GetObj(nCntStage);

			if (pObjX == NULL)
			{// NULLだったら
				continue;
			}

			// 高さ取得
			bool bLand = false;
			pos.y = pObjX->GetHeight(pos, bLand);
		}


	}
	else if (m_nCntState >= 30)
	{// 遷移カウンターが30になったら

		// ノックバック状態にする
		m_state = STATE_KNOCKBACK;
	}


	// 位置設定
	SetPosition(pos);

	// 移動量設定
	SetMove(move);

	// 向き設定
	SetRotation(rot);
}

//==========================================================================
// 死亡
//==========================================================================
void CPlayer::Dead(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// 移動量取得
	D3DXVECTOR3 move = GetMove();

	// 位置更新
	if (m_nCntState > 0)
	{
		int nCnt = DEADTIME - m_nCntState;
		pos.y = (-0.1f * (float)(nCnt * nCnt) + m_KnokBackMove.y * (float)nCnt) + m_posKnokBack.y;
		pos.x += move.x;
	}

	// 状態遷移カウンター減算
	m_nCntState--;

	// 起伏との判定
	if ((CManager::GetInstance()->GetScene()->GetElevation()->IsHit(pos) || m_bHitStage) && m_nCntState >= 10)
	{// 地面と当たっていたら

		//// フェードを設定する
		//CManager::GetInstance()->GetInstantFade()->SetFade();

		//if (CManager::GetInstance()->GetInstantFade()->GetState() == CInstantFade::STATE_FADECOMPLETION)
		//{// フェード完了した時



		//}

		m_state = STATE_FADEOUT;	// フェードアウト
		m_nCntState = FADEOUTTIME;
		m_KnokBackMove.y = 0.0f;	// 移動量ゼロ
		m_bLandOld = true;
		move.x = 0.0f;

		// 色設定
		m_mMatcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ノックバック判定消す
		m_sMotionFrag.bKnockBack = false;
		m_sMotionFrag.bDead = true;
		//m_pMotion->ToggleFinish(true);

		// ぶっ倒れモーション
		m_pMotion->Set(MOTION_DEAD);

		// Xファイルとの判定
		CStage *pStage = CGame::GetStage();
		if (pStage == NULL)
		{// NULLだったら
			return;
		}

		// ステージに当たった判定
		for (int nCntStage = 0; nCntStage < pStage->GetNumAll(); nCntStage++)
		{
			// オブジェクト取得
			CObjectX *pObjX = pStage->GetObj(nCntStage);

			if (pObjX == NULL)
			{// NULLだったら
				continue;
			}

			// 高さ取得
			bool bLand = false;
			pos.y = pObjX->GetHeight(pos, bLand);
		}
	}

	// 位置設定
	SetPosition(pos);

	// 移動量設定
	SetMove(move);
}

//==========================================================================
// フェードアウト
//==========================================================================
void CPlayer::FadeOut(void)
{

	// 状態遷移カウンター減算
	m_nCntState--;

	// 色設定
	m_mMatcol.a = (float)m_nCntState / (float)FADEOUTTIME;

	if (m_nCntState <= 0)
	{// 遷移カウンターが0になったら

		// モード設定
		//CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RESULT);

		// 死亡処理
		Kill();

		// 終了処理
		Uninit();
		return;
	}
}

//==========================================================================
// ノックバック
//==========================================================================
void CPlayer::KnockBack(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// 移動量取得
	D3DXVECTOR3 move = GetMove();

	// 向き取得
	D3DXVECTOR3 rot = GetRotation();

	// 目標の向き取得
	float fRotDest = GetRotDest();

	// 移動量取得
	float fMove = GetVelocity();

	// 現在と目標の差分
	float fRotDiff = 0.0f;

	// 距離の判定
	bool bLen = false;


	// 状態遷移カウンター減算
	m_nCntState++;

	// 位置更新
	pos.y = (-0.4f * (float)(m_nCntState * m_nCntState) + m_KnokBackMove.y * (float)m_nCntState) + m_posKnokBack.y;
	pos.x += move.x;
	/*pos.x += move.x;
	pos.z += move.z;*/

	// 起伏との判定
	if ((CManager::GetInstance()->GetScene()->GetElevation()->IsHit(pos) || m_bHitStage))
	{// 地面と当たっていたら
		m_state = STATE_INVINCIBLE;
		m_nCntState = INVINCIBLE_TIME;
		m_KnokBackMove.y = 0.0f;	// 移動量ゼロ
		m_bLandOld = true;

		// 色設定
		m_mMatcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		
		// ノックバック判定消す
		m_sMotionFrag.bKnockBack = false;
		m_pMotion->ToggleFinish(true);

		// Xファイルとの判定
		CStage *pStage = CGame::GetStage();
		if (pStage == NULL)
		{// NULLだったら
			return;
		}

		// ステージに当たった判定
		for (int nCntStage = 0; nCntStage < pStage->GetNumAll(); nCntStage++)
		{
			// オブジェクト取得
			CObjectX *pObjX = pStage->GetObj(nCntStage);

			if (pObjX == NULL)
			{// NULLだったら
				continue;
			}

			// 高さ取得
			bool bLand = false;
			pos.y = pObjX->GetHeight(pos, bLand);
		}
	}


	// 位置設定
	SetPosition(pos);

	// 移動量設定
	SetMove(move);

	// 向き設定
	SetRotation(rot);

	// 目標の向き設定
	SetRotDest(fRotDest);
}

//==========================================================================
// 簡易合体
//==========================================================================
void CPlayer::StateCompactUnion(void)
{
	// 影を消す
	if (m_pShadow != NULL)
	{
		m_pShadow->Uninit();
		m_pShadow = NULL;
	}
}

//==========================================================================
// 合体解除
//==========================================================================
void CPlayer::StateReleaseUnion(void)
{
	// 状態遷移カウンター減算
	m_nCntState--;

	if (m_nCntState <= 0)
	{// 遷移カウンターが0になったら

		m_nCntState = 0;
		m_state = STATE_NONE;

		// 影の生成
		if (m_pShadow == NULL)
		{
			m_pShadow = CShadow::Create(GetPosition(), 50.0f);
		}
		return;
	}
}

//==========================================================================
// 進化
//==========================================================================
void CPlayer::StateEvolusion(void)
{
	int nType = m_pMotion->GetType();
	if (nType == MOTION_EVOLUTION && m_pMotion->IsFinish() == true)
	{// キック攻撃が終わってたら

		// 通常状態にする
		m_state = STATE_NONE;

		// 待機モーション設定
		m_pMotion->Set(MOTION_DEF);

		// 元に戻す
		CGame::GetGameManager()->SetType(CGameManager::SCENE_MAIN);
		return;
	}

	// 向き取得
	D3DXVECTOR3 rot = GetRotation();

	// 目標の向き取得
	float fRotDest = GetRotDest();

	// 補正
	rot.y += (fRotDest - rot.y) * 0.1f;

	// 向きの設定
	RotNormalize(rot.y);
	SetRotation(rot);

	if (nType != MOTION_EVOLUTION)
	{
		// 進化モーション設定
		m_pMotion->Set(MOTION_EVOLUTION);
	}
}

//==========================================================================
// 描画処理
//==========================================================================
void CPlayer::Draw(void)
{

	// 描画処理
	if (m_state == STATE_DMG)
	{
		CObjectChara::Draw(m_mMatcol);
	}
	else if (m_state == STATE_INVINCIBLE || m_state == STATE_FADEOUT)
	{
		CObjectChara::Draw(m_mMatcol.a);
	}
	else if(m_state != STATE_COMPACTUNION)
	{
		CObjectChara::Draw();
	}
}

//==========================================================================
// 状態設定
//==========================================================================
void CPlayer::SetState(STATE state, int nCntState)
{
	m_state = state;
	m_nCntState = nCntState;
}

//==========================================================================
// 状態取得
//==========================================================================
int CPlayer::GetState(void)
{
	return m_state;
}

//==========================================================================
// ステータス取得
//==========================================================================
CPlayer::sStatus CPlayer::GetStatus(void)
{
	return m_sStatus;
}
