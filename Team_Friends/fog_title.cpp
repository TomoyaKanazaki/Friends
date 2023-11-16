//==========================================
//
//  タイトルでのフォグの処理(fog_title.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "fog_title.h"
#include "fog.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXCOLOR TARGET_COLOR = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	const float START_LENGTH = 100.0f; // 初期距離
	const float END_LENGTH = 10000.0f; // 目標距離
	const float FUNCTION = 0.01f; //倍率
}

//==========================================
//  コンストラクタ
//==========================================
CFog_Title::CFog_Title()
{
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_fLength = START_LENGTH;
}

//==========================================
//  デストラクタ
//==========================================
CFog_Title::~CFog_Title()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CFog_Title::Init()
{
	//煙をかける
	Fog::Set(true);

	//フォグの値を設定する
	Fog::SetStart(START_LENGTH);
	Fog::SetEnd(m_fLength);
	Fog::SetCol(m_col);
	
	//タイプ設定
	SetType(CObject::TYPE_NONE);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CFog_Title::Uninit()
{
	//煙を払う
	Fog::Set(false);

	//自身を破棄する
	Release();
}

//==========================================
//  更新処理
//==========================================
void CFog_Title::Update()
{
	// 目標距離まで引き伸ばす
	m_fLength += (END_LENGTH - m_fLength) * FUNCTION;

	// 目標色まで補正する
	m_col += (TARGET_COLOR - m_col) * FUNCTION;

	// 距離を適用する
	Fog::SetEnd(m_fLength);

	// 色を適用する
	Fog::SetCol(m_col);
}

//==========================================
//  描画処理
//==========================================
void CFog_Title::Draw()
{

}
