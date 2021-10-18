//=============================================================================
//
// メイン処理 [scene2D.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "polygon.h"
#include "manager.h"
#include "scene2D.h"


//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CPolygon::CPolygon()
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CPolygon::~CPolygon()
{

}

//*****************************************************************************
//　初期化処理
//*****************************************************************************
HRESULT CPolygon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//変数宣言
	VERTEX_2D*pVtx;

	//デバイスの設定
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//位置を設定
	m_pos = pos;

	//大きさを設定
	m_scale = scale;

	//頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - scale.x / 2.0f, m_pos.y + scale.y / 2.0f, 0.0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x - scale.x / 2.0f, m_pos.y - scale.y / 2.0f, 0.0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + scale.x / 2.0f, m_pos.y + scale.y / 2.0f, 0.0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + scale.x / 2.0f, m_pos.y - scale.y / 2.0f, 0.0);

	// 頂点情報を設定
	pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CPolygon::Uninit(void)
{
	//頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CPolygon::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CPolygon *CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//動的確保
	CPolygon* Polygon;
	Polygon = new CPolygon;

	if (Polygon != NULL)
	{
		Polygon->Init(pos, scale);
	}

	return Polygon;
}

//*****************************************************************************
// カラーの設定処理
//*****************************************************************************
void CPolygon::SetColor(D3DXCOLOR color)
{
	//変数宣言
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}