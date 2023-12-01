//=============================================================================
// 
//  エリア制限ヘッダー [limitarea.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _LIMITAREA_H_
#define _LIMITAREA_H_	// 二重インクルード防止

#include "meshwall.h"

//==========================================================================
// クラス定義
//==========================================================================
// エリア制限クラス定義
class CLimitErea : public CObject
{
public:

	//モーション列挙
	enum STATE
	{
		STATE_DEF = 0,	// 無し
		STATE_INIT,		// 出現
		STATE_FADEOUT,	// 消滅
		STATE_MAX
	};

	// エリア構造体
	struct sLimitEreaInfo
	{
		float fMinX;	// 最小X
		float fMaxX;	// 最大X
		float fMinZ;	// 最小Z
		float fMaxZ;	// 最大Z
	};

	CLimitErea(int nPriority = 7);
	~CLimitErea();

	// オーバーライドされた関数
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void Release(void);

	static CLimitErea *Create(sLimitEreaInfo info);
	sLimitEreaInfo GetLimitEreaInfo(void);
	STATE GetState(void);
	void CLimitErea::SetState(CLimitErea::STATE state);

protected:

private:

	void UpdateColor(int nIdx);

	STATE m_state;
	CMeshWall *m_pMeshWall[mylib_const::SHAPE_LIMITEREA];	// メッシュウォールのオブジェクト
	sLimitEreaInfo m_sLimitEreaInfo;	// エリア制限情報
	int m_nIdxEreaManager;				// エリア制限マネージャのインデックス番号
};



#endif