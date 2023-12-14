//=============================================================================
// 
//  ビーム処理 [beam.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "beam.h"
#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "calculation.h"
#include "3D_effect.h"
#include "camera.h"
#include "particle.h"
#include "ballast.h"
#include "texture.h"

namespace
{
	const char* TEXTURE = "data\\TEXTURE\\effect\\effect000.jpg";
}

int CBeam::m_nTexIdx = 0;		// テクスチャのインデックス番号

//==========================================================================
// コンストラクタ
//==========================================================================
CBeam::CBeam(int nPriority) : CObject(nPriority)
{
	m_fRadius = 0.0f;	// 半径
	m_fLength = 0.0f;	// 長さ
	m_nDisity = 0;		// 密度
	m_nDamage = 0;		// ダメージ
	m_color = mylib_const::DEFAULT_COLOR;	// 色
	m_pEffect.clear();	// エフェクトのオブジェクト
	m_pObjBillboard.clear();	// ビルボードのオブジェクト
	m_Tag = CCollisionObject::TAG_NONE;	// タグ
	m_nLife = 0;	// 寿命
	m_nLifeOrigin = 0;	// 寿命
}

//==========================================================================
// デストラクタ
//==========================================================================
CBeam::~CBeam()
{
	
}

//==========================================================================
// 生成処理
//==========================================================================
CBeam *CBeam::Create(
	const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXCOLOR col,
	const float fRadius, const float fLength, const int nLife,
	const int nDisity, const int nDamage, CCollisionObject::eMyTag TagType, eBeamType BeamType)
{
	// 生成用のオブジェクト
	CBeam *pBallast = NULL;

	if (pBallast == NULL)
	{// NULLだったら

		// メモリの確保
		pBallast = DEBUG_NEW CBeam;

		if (pBallast != NULL)
		{// メモリの確保が出来ていたら

			pBallast->m_fRadius = fRadius;	// 半径
			pBallast->m_fLength = fLength;	// 長さ
			pBallast->m_nLife = nLife;		// 寿命
			pBallast->SetPosition(pos);		// 位置
			pBallast->SetMove(move);		// 移動量
			pBallast->m_color = col;		// 色
			pBallast->m_nDisity = nDisity;	// 密度
			pBallast->m_nDamage = nDamage;	// ダメージ
			pBallast->m_Tag = TagType;		// タグ
			pBallast->m_BeamType = BeamType;	// ビームの種類

			// 初期化処理
			HRESULT hr = pBallast->Init();
			if (FAILED(hr))
			{
				return NULL;
			}
		}

		return pBallast;
	}

	return NULL;
}

//==========================================================================
// 加算合成取り消し
//==========================================================================
void CBeam::SetDisableAddAlpha(void)
{
	for (int i = 0; i < static_cast<int>(m_pEffect.size()); i++)
	{
		if (m_pEffect[i] == nullptr)
		{
			continue;
		}

		m_pEffect[i]->SetDisableAddAlpha();
	}
}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CBeam::Init(void)
{
	// 種類の設定
	SetType(TYPE_OBJECT3D);

	// 位置取得
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 vecmove = move - mylib_const::DEFAULT_VECTOR3;

	m_nLifeOrigin = m_nLife;

	// ベクトルを正規化
	D3DXVec3Normalize(&vecmove, &vecmove);

	float fDistance = m_fLength / (float)m_nDisity;
	float fLen = 0.0f;
	for (int nCntBallast = 0; nCntBallast < m_nDisity; nCntBallast++)
	{
		switch (m_BeamType)
		{
		case CBeam::TYPE_NORMAL:
		{
			// 生成処理
			CEffect3D *pEffect = CEffect3D::Create(
				pos + vecmove * fLen,
				move,
				m_color,
				m_fRadius,
				m_nLife,
				CEffect3D::MOVEEFFECT_SUB,
				CEffect3D::TYPE_NORMAL,
				0.0f);

			// エフェクト追加
			m_pEffect.push_back(pEffect);
		}
			break;

		case CBeam::TYPE_RESIDUAL:
		{
			// 生成処理
			CObjectBillboard *pEffect = CObjectBillboard::Create(pos + vecmove * fLen, mylib_const::DEFAULT_VECTOR3);
			pEffect->SetMove(move);
			pEffect->SetColor(m_color);
			pEffect->SetSize(D3DXVECTOR2(m_fRadius, m_fRadius));
			pEffect->SetSizeOrigin(D3DXVECTOR2(m_fRadius, m_fRadius));
			pEffect->SetType(CObject::TYPE_NONE);

			if (m_nTexIdx == 0)
			{
				m_nTexIdx = CManager::GetInstance()->GetTexture()->Regist(TEXTURE);
			}
			pEffect->BindTexture(m_nTexIdx);

			// ビルビード追加
			m_pObjBillboard.push_back(pEffect);
		}
			break;
		}

		// 当たり判定オブジェクト生成
		CCollisionObject::Create(pos + vecmove * fLen, move, m_fRadius, m_nLife, m_nDamage, m_Tag);

		// 距離加算
		fLen += fDistance;
	}

	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CBeam::Uninit(void)
{
	// 要素全削除
	m_pEffect.clear();

	for (int i = 0; i < static_cast<int>(m_pObjBillboard.size()); i++)
	{
		if (m_pObjBillboard[i] == nullptr)
		{
			continue;
		}
		m_pObjBillboard[i]->Uninit();
		m_pObjBillboard[i] = nullptr;
	}

	// 情報削除
	Release();
}

//==========================================================================
// 更新処理
//==========================================================================
void CBeam::Update(void)
{
	// 寿命減算
	m_nLife--;

	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}

	switch (m_BeamType)
	{
	case CBeam::TYPE_NORMAL:
		UpdateEffect();
		break;

	case CBeam::TYPE_RESIDUAL:
		UpdateBillboard();
		break;
	}
	
}

//==========================================================================
// エフェクトの更新
//==========================================================================
void CBeam::UpdateEffect(void)
{
	for (int i = 0; i < static_cast<int>(m_pEffect.size()); i++)
	{
		if (m_pEffect[i] == nullptr)
		{
			continue;
		}

		// 位置取得
		D3DXVECTOR3 pos = m_pEffect[i]->GetPosition();

		if (CGame::GetElevation()->IsHit(pos) == true)
		{
			// 振動
			CManager::GetInstance()->GetCamera()->SetShake(6, 4.0f, 0.0f);

			// 瓦礫
			CBallast::Create(pos, D3DXVECTOR3(2.0f, 6.0f, 2.0f), 1, 1.0f, CBallast::TYPE_STONE);

			// ビームヒットパーティクル
			my_particle::Create(pos, my_particle::TYPE_BEAMHIT_FIELD);

			m_pEffect[i]->Uninit();
			m_pEffect[i] = nullptr;

			// 着地したものを削除
			m_pEffect.erase(m_pEffect.begin() + i);
		}
	}
}

//==========================================================================
// ビルビードの更新
//==========================================================================
void CBeam::UpdateBillboard(void)
{
	float fAlpha = (float)m_nLife / (float)m_nLifeOrigin;

	// 要素分繰り返し
	for (int i = static_cast<int>(m_pObjBillboard.size()) - 1; i >= 0; --i)
	{
		const auto& billboard = m_pObjBillboard[i];

		if (billboard == nullptr)
		{
			continue;
		}

		// 色
		D3DXCOLOR col = billboard->GetColor();
		col.a = fAlpha;
		billboard->SetColor(col);

		// 位置取得
		D3DXVECTOR3 pos = billboard->GetPosition();

		// 移動量取得
		D3DXVECTOR3 move = billboard->GetMove();

		// サイズ取得
		D3DXVECTOR2 sizeorigin = billboard->GetSizeOrigin();

		// 位置更新
		pos += move;
		billboard->SetPosition(pos);

		m_fRadius = sizeorigin.x * fAlpha;
		billboard->SetSize(D3DXVECTOR2(m_fRadius, m_fRadius));


		if (CGame::GetElevation()->IsHit(pos) == true)
		{
			// 振動
			CManager::GetInstance()->GetCamera()->SetShake(6, 4.0f, 0.0f);

			// 瓦礫
			CBallast::Create(pos, D3DXVECTOR3(2.0f, 6.0f, 2.0f), 1, 1.0f, CBallast::TYPE_STONE);

			// ビームヒットパーティクル
			my_particle::Create(pos, my_particle::TYPE_BEAMHIT_FIELD);

			billboard->Uninit();
			//billboard = nullptr;

			// 着地したものを削除
			m_pObjBillboard.erase(m_pObjBillboard.begin() + i);
			continue;
		}

		// 更新
		billboard->Update();
	}
}

//==========================================================================
// 描画処理
//==========================================================================
void CBeam::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// リストコピー
	std::vector<CObjectBillboard*> pObjectSort = m_pObjBillboard;

	// Zソート
	std::sort(pObjectSort.begin(), pObjectSort.end(), ZSort);

	for (int i = 0; i < (int)pObjectSort.size(); i++)
	{
		if (pObjectSort[i] == nullptr)
		{
			continue;
		}
		pObjectSort[i]->Draw();
	}

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// ライティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


}
