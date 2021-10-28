//=============================================================================
//
// メイン処理 [scene2D.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "scene2D.h"
#include "manager.h"
#include "renderer.h"
#include "dinput_keyboard.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CScene2D*CScene2D::m_apBullet1[10] = {};			// ポリゴンの数

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CScene2D::CScene2D(int nPriority):CScene(nPriority)
{
	for (int nCntpBullet = 0; nCntpBullet < 10; nCntpBullet++)
	{
		if (m_apBullet1[nCntpBullet] == NULL)
		{
			m_apBullet1[nCntpBullet] = this;
			break;
		}
	}
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CScene2D::~CScene2D()
{

}

//*****************************************************************************
//　初期化処理
//*****************************************************************************
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
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
	m_scale = scale / 2.0f;

	//点と中心点を図る処理
	Length();

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//位置を設定
	pVtx[0].pos.x = m_pos.x - sinf(m_fAngle + m_rot.z)*(m_fLength);
	pVtx[0].pos.y = m_pos.y + cosf(m_fAngle + m_rot.z)*(m_fLength);
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x - sinf(m_fAngle - m_rot.z)*(m_fLength);
	pVtx[1].pos.y = m_pos.y - cosf(m_fAngle - m_rot.z)*(m_fLength);
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_fAngle - m_rot.z)*(m_fLength);
	pVtx[2].pos.y = m_pos.y + cosf(m_fAngle - m_rot.z)*(m_fLength);
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_fAngle + m_rot.z)*(m_fLength);
	pVtx[3].pos.y = m_pos.y - cosf(m_fAngle + m_rot.z)*(m_fLength);
	pVtx[3].pos.z = 0.0f;

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
void CScene2D::Uninit(void)
{
	//頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CScene2D::Update(void)
{

}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CScene2D::Draw(void)
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
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//動的確保
	CScene2D* pScene2D;
	pScene2D = new CScene2D;

	if (pScene2D != NULL)
	{
		pScene2D->Init(pos,scale);
	}

	return pScene2D;
}

//*****************************************************************************
// 位置処理
//*****************************************************************************
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}

//*****************************************************************************
// 位置の設定処理
//*****************************************************************************
void CScene2D::SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//位置の設定
	m_pos = pos;

	//位置の設定
	m_scale = scale;

	//変数宣言
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//位置を設定
	pVtx[0].pos.x = m_pos.x - sinf(m_fAngle + m_rot.z)*(m_fLength);
	pVtx[0].pos.y = m_pos.y + cosf(m_fAngle + m_rot.z)*(m_fLength);
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x - sinf(m_fAngle - m_rot.z)*(m_fLength);
	pVtx[1].pos.y = m_pos.y - cosf(m_fAngle - m_rot.z)*(m_fLength);
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_fAngle - m_rot.z)*(m_fLength);
	pVtx[2].pos.y = m_pos.y + cosf(m_fAngle - m_rot.z)*(m_fLength);
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_fAngle + m_rot.z)*(m_fLength);
	pVtx[3].pos.y = m_pos.y - cosf(m_fAngle + m_rot.z)*(m_fLength);
	pVtx[3].pos.z = 0.0f;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//*****************************************************************************
//爆発の設定処理
//*****************************************************************************
void CScene2D::SetTex(int nCnt)
{
	//変数宣言
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の更新
	pVtx[0].tex = D3DXVECTOR2(0.125f*nCnt, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.125f*nCnt, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.125f+ (0.125f*nCnt), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.125f+ (0.125f*nCnt), 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//*****************************************************************************
//背景スクロールの設定処理
//*****************************************************************************
void CScene2D::SetBg(float ScrollBg)
{

	//変数宣言
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の更新
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f+ScrollBg);
	pVtx[1].tex = D3DXVECTOR2(0.0f,1.0f+ScrollBg);
	pVtx[2].tex = D3DXVECTOR2(1.0f,0.0f +ScrollBg);
	pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f +ScrollBg);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//*****************************************************************************
// カラーの設定処理
//*****************************************************************************
void CScene2D::SetColor(D3DXCOLOR color)
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

//*****************************************************************************
// 長さを図る処理
//*****************************************************************************
void CScene2D::Length(void)
{
	//中心点と点との距離
	m_fLength = sqrtf(m_scale.x * m_scale.x + m_scale.y * m_scale.y);

	//角度
	m_fAngle = atan2f(m_scale.x, m_scale.y);
}


//*****************************************************************************
// テクスチャの割り当て処理
//*****************************************************************************
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}