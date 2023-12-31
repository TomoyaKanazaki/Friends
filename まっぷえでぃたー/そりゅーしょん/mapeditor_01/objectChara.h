//=============================================================================
// 
//  オブジェクトキャラクターヘッダー [objectChara.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _OBJECTCHARA_H_
#define _OBJECTCHARA_H_	// 二重インクルード防止

#include "main.h"
#include "object.h"

class CModel;

//==========================================================================
// クラス定義
//==========================================================================
// オブジェクトキャラクタークラス定義
class CObjectChara : public CObject
{
public:

	// 構造体定義
	struct LoadData
	{
		std::string pModelFile;	// モデルファイル名
		int nType;				// モデル種類
		int nParent;			// 親のインデックス
		int nStart;				// 最初からあるかどうか
		D3DXVECTOR3 pos;		// 位置
		D3DXVECTOR3 rot;		// 向き
	};

	struct Load
	{
		std::string sTextFile;	// テキストファイル名
		int nNumModel;			// モデル数
		float fVelocity;		// 移動速度
		float fRadius;			// 半径
		int nLife;				// 体力
		int nAddScore;			// スコア加算量
		D3DXVECTOR3 posOrigin;	// 最初の位置
		LoadData LoadData[mylib_const::MAX_MODEL];
	};

	// 列挙型定義
	typedef enum
	{
		STATE_NONE = 0,	// なにもない
		STATE_MAX
	}STATE;

	CObjectChara(int nPriority = mylib_const::DEFAULT_PRIORITY);
	~CObjectChara();

	// オーバーライドされた関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Draw(D3DXCOLOR col);
	void Draw(float fAlpha);

	void SetmtxWorld(const D3DXMATRIX mtxWorld);
	D3DXMATRIX GetmtxWorld(void) const;			// ワールドマトリックス取得
	D3DXVECTOR3 GetCenterPosition(void) const;		// 中心の位置取得
	void SetOriginPosition(const D3DXVECTOR3 pos);	// 最初の位置設定
	D3DXVECTOR3 GetOriginPosition(void) const;		// 最初の位置取得
	void SetVelocity(const float fVelocity);	// 移動速度設定
	float GetVelocity(void) const;				// 移動速度取得
	void SetRadius(const float fRadius);		// 半径設定
	float GetRadius(void) const;				// 半径取得
	void SetRotDest(const float fRotDest);		// 目標の向き設定
	float GetRotDest(void) const;				// 目標の向き取得
	void SetLife(const int nLife);				// 体力設定
	int GetLife(void) const;					// 体力取得
	int GetLifeOrigin(void) const;				// 元の体力取得
	int GetAddScoreValue(void) const;			// スコア加算量取得
	void SetEnableWaveHit(void);				// 波の当たり判定ON
	void SetDisableWaveHit(void);				// 波の当たり判定OFF
	bool IsWaveHit(void);						// 波の判定状態取得

	virtual int GetState(void);					// 状態取得
	virtual void SetState(int state);			// 状態設定
	virtual void SetState(int state, int nCntState);	// 状態設定
	virtual int GetCharaType(void);	// 種類取得

	HRESULT ReadText(const std::string pTextFile);	// 外部ファイル読み込み処理
	HRESULT SetCharacter(const std::string pTextFile);

	void ChangeObject(int nDeleteParts, int nNewParts);
	void SetObject(int nNewParts);

	CObjectChara *GetObjectChara(void);
	int GetNumModel(void);		// モデル数取得
	void SetNumModel(int nNumModel);		// モデル数設定
	int GetIdxFile(void);		// ファイルのインデックス番号取得
	Load GetLoadData(int nIdx);	// 読み込み情報取得
	CModel **GetModel(void);
	static CObjectChara *Create(const std::string pTextFile);

private:

	D3DXMATRIX	m_mtxWorld;		// ワールドマトリックス
	D3DXVECTOR3 m_posOrigin;	// 最初の位置
	float m_fVelocity;			// 移動速度
	float m_fRadius;			// 半径
	float m_fRotDest;			// 目標の向き
	int m_nLife;				// 体力
	int m_nLifeOrigin;			// 元の体力
	int m_nAddScore;			// スコア加算量
	int m_nNumModel;			// モデルの数
	int m_nIdxFile;				// ファイルのインデックス番号
	bool m_bWaveHit;			// 波に当たっているかの判定
	CModel *m_apModel[mylib_const::MAX_MODEL];	// モデル(パーツ)のポインタ

	static int m_nNumLoad;	// 読み込んだ数
	static Load m_aLoadData[mylib_const::MAX_MODEL];
};



#endif