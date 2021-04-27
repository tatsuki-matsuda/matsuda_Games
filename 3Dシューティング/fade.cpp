//-------------------------------------------------------------------------------
//
// ゲーム制作[polygon.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include "fade.h"

//-------------------------------------------------------------------------------
//マクロ定義
//-------------------------------------------------------------------------------
#define MOVE_ALPHA  (0.1f)	//α値の最小

//-------------------------------------------------------------------------------
//グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;			//テクスチャ情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;		//頂点バッファへのポインタ
FADE g_fade;			//フェードの状態
MODE g_modeNext;		//次のモード
D3DXCOLOR g_colorFade;	//フェード色

//-------------------------------------------------------------------------------
//初期化処理
//-------------------------------------------------------------------------------
HRESULT InitFade(MODE modeNext)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	VERTEX_2D*pVtx;

	//代入
	g_fade = FADE_IN;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(0, 960, 0.0);		//左下の座標
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0);		//左上の座標
	pVtx[2].pos = D3DXVECTOR3(1280, 960, 0.0);	//右下の座標
	pVtx[3].pos = D3DXVECTOR3(1280, 0, 0.0);	//右上の座標
									
	//頂点座標
	pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;

	//頂点バッファをアンロックする
	g_pVtxBuffFade->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//終了処理
//-------------------------------------------------------------------------------
void UninitFade(void)
{//頂点バッファの開放
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}

	//テクスチャの開放
	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}
}

//-------------------------------------------------------------------------------
//更新処理
//-------------------------------------------------------------------------------
void UpdateFade(void)
{
	//変数宣言
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;

	//頂点バッファをアンロックする
	g_pVtxBuffFade->Unlock();
	if (g_fade == FADE_IN)
	{//フェードイン
		g_colorFade.a -= MOVE_ALPHA;
		if (g_colorFade.a <= 0.0f)
		{
			g_fade = FADE_NONE;
		}
	}
	else if (g_fade == FADE_OUT)
	{//フェードアウト
		g_colorFade.a += MOVE_ALPHA;
		if (g_colorFade.a >= 1.0f)
		{
			g_fade = FADE_IN;
			SetMode(g_modeNext);
		}
	}
}

//-------------------------------------------------------------------------------
//描画処理
//-------------------------------------------------------------------------------
void DrawFade(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureFade);

	//背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//-------------------------------------------------------------------------------
//フェード設定
//-------------------------------------------------------------------------------
void SetFade(FADE fade, MODE modeNext)
{
	//代入
	g_fade = fade;
	g_modeNext = modeNext;
}

//-------------------------------------------------------------------------------
//フェード情報の取得
//-------------------------------------------------------------------------------
FADE GetFade(void)
{
	return g_fade;
}