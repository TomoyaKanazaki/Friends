//=============================================================================
// 
//  マップヘッダー [map.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _MAP_H_
#define _MAP_H_	// 二重インクルード防止

#include "main.h"

//==========================================================================
// 名前空間
//==========================================================================
namespace map
{
	HRESULT Create(const char *pTextFile);	// 生成処理
	HRESULT ReadTexture(void);	// テクスチャ読み込み処理
	HRESULT ReadXFile(const char *pTextFile);	// もでる読み込み処理
	HRESULT ReadText(const char *pTextFile);	// 外部ファイル読み込み処理
	HRESULT SaveText(void);	// 外部ファイル書き込み処理
	int GetNumModelAll(void);	// 総数取得
	void Release(void);
}

#endif