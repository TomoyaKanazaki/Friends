//=============================================================================
// 
//  合体プレイヤーヘッダー [player_union.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _PLAYER_UNION_H_
#define _PLAYER_UNION_H_	// 二重インクルード防止

#include "objectChara.h"
#include "motion.h"

//==========================================================================
// マクロ定義
//==========================================================================

// 前方宣言
class CShadow;
class CTargetPoint;
class CHP_GaugePlayer;
class CUnionCore;

//==========================================================================
// クラス定義
//==========================================================================
// 合体プレイヤークラス定義
class CPlayerUnion : public CObject
{
public:

	// 状態定義
	enum STATE
	{
		STATE_NONE = 0,		// なにもない
		STATE_INVINCIBLE,	// 無敵
		STATE_DMG,			// ダメージ
		STATE_KNOCKBACK,	// ノックバック
		STATE_DEAD,			// 死
		STATE_FADEOUT,		// フェードアウト
		STATE_ATTACK,		// 攻撃処理
		STATE_APPEARANCE,	// 出現
		STATE_ULT,			// 必殺技状態
		STATE_MAX
	};

	// 合体種類
	enum eType
	{
		TYPE_ALL = 0,	// 全員合体
		TYPE_BODYtoLEG,	// 胴×脚
		TYPE_BODYtoARM,	// 胴×腕
		TYPE_LEGtoARM,	// 脚×腕
		TYPE_ARMtoARM,	// 腕×腕
		TYPE_MAX
	};

	enum eParts
	{
		PARTS_BODY = 0,
		PARTS_LEG,
		PARTS_R_ARM,
		PARTS_L_ARM,
		PARTS_MAX
	};

	CPlayerUnion(int nPriority = mylib_const::PRIORITY_DEF2D);
	~CPlayerUnion();

	// オーバーライドされた関数
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual bool Hit(const int nValue);	// ヒット処理
	int GetState(void);

	static CPlayerUnion *Create(eType type);	// 生成
	void UninitByMode(void);
	void Kill(void);	// 死亡処理
	void SetPlayerByPartsIdx(int nPartsIdx, int nPlayerIdx);	// プレイヤー毎のパーツインデックス番号設定
	void SetControllMoveIdx(int nIdx);	// 移動の操作するインデックス番号設定

protected:

	// モーションの判定
	struct SMotionFrag
	{
		bool bJump;		// ジャンプ中
		bool bATK;		// 攻撃中
		bool bCharge;	// チャージ中
		bool bMove;		// 移動中
		bool bUltEntry;	// 必殺エントリー
	};


	// 状態処理
	virtual void UpdateState(void);	// 状態更新処理
	virtual void KnockBack(void);	// ノックバック
	virtual void Damage(void);		// ダメージ
	virtual void Dead(void);		// 死亡
	virtual void FadeOut(void);		// フェードアウト
	virtual void Invincible(void);	// 無敵
	virtual void Appearance(void);	// 出現
	virtual void Ultimate(void);	// 必殺技

	void BindByPlayerIdxTexture(int nIdx, int nPartsIdx);	// プレイヤーインデックス毎のテクスチャ設定
	void ReadMultiCharacter(const char *pTextFile);			// 複数キャラクター読み込み
	bool Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &move);	// 当たり判定
	virtual void AttackAction(int nIdx, int nModelNum, CMotion::AttackInfo ATKInfo, int nCntATK);	// 攻撃時処理
	virtual void AttackInDicision(int nIdx, CMotion::AttackInfo ATKInfo, int nCntATK);				// 攻撃判定中処理
	virtual void ControllParts(void);	// パーツのコントロール処理
	virtual void MotionSet(int nIdx);	// モーションの設定
	virtual void Atack(int nIdx);		// 攻撃
	bool ControllMove(int nIdx);	// 移動操作
	void ControllRotation(int nIdx);	// 回転操作
	virtual HRESULT CreateParts(void);	// パーツの設定
	int GetModelIdxtFromPartsIdx(int nModelIdx);	// モデルインデックスからパーツのインデックス取得

	bool m_bJump;				// ジャンプ中かどうか
	bool m_bLandOld;			// 過去の着地情報
	bool m_bHitStage;			// ステージの当たり判定
	bool m_bLandField;			// フィールドの着地判定
	bool m_bHitWall;			// 壁の当たり判定
	bool m_bKnockBack;			// ノックバック中かどうか
	bool m_bDead;			// 死亡中かどうか

	int m_nPartsIdx[mylib_const::MAX_PLAYER];	// プレイヤー毎のパーツインデックス番号
	int m_nMyPlayerIdx;			// プレイヤーインデックス番号
	int m_nControllMoveIdx;		// 移動操作するやつのインデックス番号
	int m_nCntWalk;				// 歩行カウンター
	int m_nUnionLife;			// 合体時間
	int m_nCntInputAtk;			// 攻撃の入力カウンター

	int m_nInputSuperAtkIdx;	// 必殺技入力のインデックス
	int m_nIntervalAlternately;	// 交互入力のインターバル
	int m_nCntInputSuperATK;	// 必殺技の入力回数

	D3DXCOLOR m_mMatcol;		// マテリアルの色
	STATE m_Oldstate;			// 前回の状態
	STATE m_state;			// 状態
	int m_nCntState;			// 状態遷移カウンター
	D3DXVECTOR3 m_posKnokBack;	// ノックバックの位置
	D3DXVECTOR3 m_KnokBackMove;	// ノックバックの移動量
	CMotion *m_pMotion[PARTS_MAX];			// パーツ分のモーションポインタ
	SMotionFrag m_sMotionFrag[PARTS_MAX];	// モーションのフラグ
	CObjectChara *m_pObjChara[PARTS_MAX];	// パーツ分のオブジェクトキャラクターポインタ
	CModel *m_apModel[mylib_const::MAX_MODEL];	// モデル(パーツ)のポインタ
private:

	// コンボ時ワザの種類
	enum eSPSkill
	{
		SKILL_MAX
	};

	// 列挙型定義
	enum MOTION
	{
		MOTION_DEF = 0,				// ニュートラルモーション
		MOTION_WALK,				// 移動モーション
		MOTION_BOOST,				// ブーストモーション
		MOTION_NORMAL_CHARGE,		// 通常チャージ
		MOTION_NORMAL_ATK,			// 通常攻撃
		MOTION_ULT_BEAMCHARGE,		// 必殺技ビームチャージ
		MOTION_ULT_BEAMATK,			// 必殺技ビーム攻撃
		MOTION_ULT_BIGPUNCHCHARGE,	// 必殺技デカパンチチャージ
		MOTION_ULT_BIGPUNCHATK,		// 必殺技デカパンチ攻撃
		MOTION_ULT_RIDERKICKCHARGE,	// 必殺技ライダーキックチャージ
		MOTION_ULT_RIDERKICKATK,	// 必殺技ライダーキック攻撃
		MOTION_ULT_BOOSTPUNCHCHARGE,	// 必殺技ブーストパンチチャージ
		MOTION_ULT_BOOSTPUNCHATK,	// 必殺技ブーストパンチ攻撃
		MOTION_ULT_RUSHCHARGE,		// 必殺技ラッシュチャージ
		MOTION_ULT_RUSHATK,			// 必殺技ラッシュ攻撃
		MOTION_KNOCKBACK,			// やられモーション
		MOTION_DEAD,				// 死亡モーション
		MOTION_APPEARANCE,			// 出現
		MOTION_MAX
	};

	enum eUltAttack
	{
		ULT_BEAM = 0,	// ビーム
		ULT_BIGPUNCH,	// ビッグパンチ
		ULT_RIDERKICK,	// ライダーキック
		ULT_BOOSTPUNCH,	// ブーストパンチ
		ULT_RUSH,		// ラッシュ
		ULT_MAX
	};

	enum eUltBranch
	{
		ULTBRANCH_CHARGE_BEAM = 0,		// ビームチャージ
		ULTBRANCH_ATTACK_BEAM,			// ビーム攻撃
		ULTBRANCH_CHARGE_BIGPUNCH,		// デカパンチチャージ
		ULTBRANCH_ATTACK_BIGPUNCH,		// デカパンチ攻撃
		ULTBRANCH_CHARGE_RIDERKICK,		// ライダーキックチャージ
		ULTBRANCH_ATTACK_RIDERKICK,		// ライダーキック攻撃
		ULTBRANCH_CHARGE_BOOSTPUNCH,	// ブーストパンチチャージ
		ULTBRANCH_ATTACK_BOOSTPUNCH,	// ブーストパンチ攻撃
		ULTBRANCH_CHARGE_RUSH,			// ラッシュチャージ
		ULTBRANCH_ATTACK_RUSH,			// ラッシュ攻撃
		ULTBRANCH_MAX
	};

	//=============================
	// 関数リスト
	//=============================
	typedef void(CPlayerUnion::*ULT_FUNC)(void);
	static ULT_FUNC m_UltFuncList[];	// 必殺技の関数リスト

	// 必殺技関数
	void UltBeam(void);			// ビーム
	void UltBigPunch(void);		// デカパンチ
	void UltRiderKick(void);	// ライダーキック
	void UltBoostPunch(void);	// ブーストパンチ
	void UltRush(void);			// ラッシュ

	// 必殺分岐関数
	void UltChargeBeam(void);		// ビームチャージ
	void UltAttackBeam(void);		// ビーム攻撃
	void UltChargeBigPunch(void);	// デカパンチチャージ
	void UltAttackBigPunch(void);	// デカパンチ攻撃
	void UltChargeRiderKick(void);	// ライダーキックチャージ
	void UltAttackRiderKick(void);	// ライダーキック攻撃
	void UltChargeBoostPunch(void);	// ブーストパンチチャージ
	void UltAttackBoostPunch(void);	// ブーストパンチ攻撃
	void UltChargeRush(void);		// ラッシュチャージ
	void UltAttackRush(void);		// ラッシュ攻撃

	// メンバ関数
	void Controll(void);		// 操作
	void ControllBody(int nIdx, int nLoop);		// 胴操作
	void ControllLeg(int nIdx, int nLoop);			// 脚操作
	void ControllRightArm(int nIdx, int nLoop);	// 右腕操作
	void ControllLeftArm(int nIdx, int nLoop);		// 左腕操作
	void EntryUltimate(int nIdx, int nLoop);	// 必殺エントリー
	void UpdateEntry(void);	// エントリー関連の更新
	void DrawingUlt(int nFirst, int nSecond);	// ウルト先抽選

	// メンバ変数
	int m_nTexIdx;				// テクスチャのインデックス番号
	int m_nIdxXFile;			// Xファイルのインデックス番号
	float m_fRotDest;			// 目標の向き
	CShadow *m_pShadow;			// 影の情報
	CTargetPoint *m_pTargetP;	// 目標の地点
	CHP_GaugePlayer *m_pHPGauge;	// HPゲージの情報
	CUnionCore *m_pUnionCore;		// 合体後コア
	eUltAttack m_UltType;			// 必殺技の種類
	eUltBranch m_UltBranch;			// 必殺技の分岐
	bool m_bUltBigArm;				// ウルトで腕デカくしたか
	float m_fUltGaugeValue[mylib_const::MAX_PLAYER];		// 必殺ゲージの量
	float m_fCooltimeBoost;	// ブーストのクールタイム
	float m_fBoostTime;	// ブーストのタイム
	std::vector<int> m_nModelIdx[mylib_const::MAX_PLAYER];	// 各パーツごとのモデルインデックス番号
	static bool m_bAllLandInjectionTable;	// 全員の射出台着地判定
	static bool m_bLandInjectionTable[mylib_const::MAX_PLAYER];	// 射出台の着地判定

};



#endif