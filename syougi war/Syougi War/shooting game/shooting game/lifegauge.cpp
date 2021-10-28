//=============================================================================
//
// メイン処理 [bullet.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "lifegauge.h"
#include "enemy.h"
#include "dinput_keyboard.h"
#include "player.h"
#include "score.h"
#include "game.h"
#include "manager.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CLifeGauge::m_pTexture = NULL;			// テクスチャ

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CLifeGauge::CLifeGauge(int nPriority)
{
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CLifeGauge::~CLifeGauge()
{
}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CLifeGauge *CLifeGauge::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int nBaseLife)
{
	//動的確保
	CLifeGauge* pLifeGauge;
	pLifeGauge = new CLifeGauge();

	//体力値情報の呼び出し
	pLifeGauge->SetBaseLife(nBaseLife);

	//初期化処理を呼び出し
	pLifeGauge->Init(pos, scale);

	//値を返す
	return pLifeGauge;
}

//*****************************************************************************
//　初期化処理
//*****************************************************************************
HRESULT CLifeGauge::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//デバイスの設定
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//位置の設定
	m_pos = pos;

	//位置の設定
	m_scale = scale;

	//使われているかどうか
	m_bUninit = false;

	//ゲージが増加しているかどうか
	m_bGaugeUp = false;

	//基礎となる大きさ
	m_BaseScale.x = GAUGEBASE_X;

	//現在の体力値
	m_nLife = m_nBaseLife;

	//基礎となる位置
	m_BasePos = pos;

	//間隔カウント
	m_nCntTime = 0;

	//描画優先順位
	SetObjType(OBJTYPE_UI);

	//変数宣言
	VERTEX_2D*pVtx;

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
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_scale.x / 2.0f, m_pos.y + m_scale.y / 2.0f, 0.0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x - m_scale.x / 2.0f, m_pos.y - m_scale.y / 2.0f, 0.0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_scale.x / 2.0f, m_pos.y + m_scale.y / 2.0f, 0.0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_scale.x / 2.0f, m_pos.y - m_scale.y / 2.0f, 0.0);

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

	//値を返す
	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CLifeGauge::Uninit(void)
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
void CLifeGauge::Update(void)
{
	//trueになるまで処理
	if (m_bGaugeUp == false)
	{
		//ゲージ増加処理
		OnGaugeUp();
	}

	//体力が0になった場合
	if (m_nLife <= 0)
	{
		//消滅
		m_bUninit = true;
	}

	//消滅した場合
	if (m_bUninit == true)
	{
		//終了処理の呼び出し
		Uninit();

		//値を返す
		return;
	}

	//位置情報の呼び出し
	SetPosition(m_pos, m_scale);
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CLifeGauge::Draw(void)
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
// ゲージ縮小処理
//*****************************************************************************
void CLifeGauge::OnDiffuse(int nDiffuseLife)
{
	//体力を与えたダメージ分減らす
	m_nLife -= nDiffuseLife;

	//判定がtrueの場合
	if (m_bGaugeUp == true)
	{
		//現在の体力値から出現時の体力値を割った値
		float HpGauge = (float)m_nLife / (float)m_nBaseLife*m_scale.x;

		//ゲージを現在の体力値分に変換する
		m_scale.x = HpGauge;
	}
}

//*****************************************************************************
// ゲージ増加処理
//*****************************************************************************
void CLifeGauge::OnGaugeUp(void)
{
	//最大ゲージ量に到達するまでゲージを増加
	if (m_BaseScale.x >= m_scale.x)
	{
		//値を増加
		m_scale.x += GAUGEUP_X;

		//基礎となる体力値より現在の体力値が低い場合
		if (m_nBaseLife > m_nLife)
		{
			//現在の体力の割合
			float fRatio = (float)m_nLife / (float)m_nBaseLife;

			//体力の割合を参照し大きさに代入
			float scale_x = m_BaseScale.x * fRatio;

			//代入したゲージ量より現在のゲージ量の値が大きい場合
			if (m_scale.x > scale_x)
			{
				//値を同じにする
				m_scale.x = scale_x;
			}
		}
		else if (m_BaseScale.x <= m_scale.x)
		{//基礎となる体力値より現在の体力値が高い場合

			//現在の体力の割合
			float fRatio = (float)m_nLife / (float)m_nBaseLife;

			//体力の割合を参照し大きさに代入
			float scale_x = m_BaseScale.x * fRatio;

			//値を同じにする
			m_scale.x = scale_x;
		}
	}
}

//*****************************************************************************
// 位置の設定処理
//*****************************************************************************
void CLifeGauge::SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
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
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_scale.y / 2.0f, 0.0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x, m_pos.y - m_scale.y / 2.0f, 0.0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y + m_scale.y / 2.0f, 0.0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y - m_scale.y / 2.0f, 0.0);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}