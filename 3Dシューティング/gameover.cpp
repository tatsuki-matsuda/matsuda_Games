//-------------------------------------------------------------------------------
//
// ゲーム制作[GameOver.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include "gameover.h"
#include "input.h"	
#include "fade.h"	
#include "xinput_gamepad.h"

//-------------------------------------------------------------------------------
//グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureGameOver = NULL;			//テクスチャ情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameOver = NULL;		//頂点バッファへのポインタ

//-------------------------------------------------------------------------------
//初期化処理
//-------------------------------------------------------------------------------
HRESULT InitGameOver(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//変数宣言
	VERTEX_2D*pVtx;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gameover.png", &g_pTextureGameOver);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGameOver, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGameOver->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);		//左下の座標
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//左上の座標
	pVtx[2].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);	//右下の座標
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);		//右上の座標

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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//頂点バッファをアンロックする
	g_pVtxBuffGameOver->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//終了処理
//-------------------------------------------------------------------------------
void UninitGameOver(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffGameOver != NULL)
	{
		g_pVtxBuffGameOver->Release();
		g_pVtxBuffGameOver = NULL;
	}

	//テクスチャの開放
	if (g_pTextureGameOver != NULL)
	{
		g_pTextureGameOver->Release();
		g_pTextureGameOver = NULL;
	}
}

//-------------------------------------------------------------------------------
//更新処理
//-------------------------------------------------------------------------------
void UpdateGameOver(void)
{

	XinputGamepad*pXinputGamepad = GetXinputGamepad();

	// 各モードに遷移
	if (pXinputGamepad->bAButton == true)
	{

		pXinputGamepad->bAButton = false;

		//AButtonを押した場合
		SetFade(FADE_OUT, MODE_TITLE);
	}

}

//-------------------------------------------------------------------------------
//描画処理
//-------------------------------------------------------------------------------
void DrawGameOver(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGameOver, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureGameOver);

	//背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}