//-------------------------------------------------------------------------------
//
// ゲーム制作[result.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include "result.h"
#include "input.h"	
#include "fade.h"	
#include "xinput_gamepad.h"	//コントローラーの詳細

//-------------------------------------------------------------------------------
//グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;			//テクスチャ情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	//頂点バッファへのポインタ

//-------------------------------------------------------------------------------
//初期化処理
//-------------------------------------------------------------------------------
HRESULT InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//変数宣言
	VERTEX_2D*pVtx;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\result.png", &g_pTextureResult);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);				//左下の座標
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//左上の座標
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);		//右下の座標
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);				//右上の座標

	//頂点情報
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
	g_pVtxBuffResult->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//終了処理
//-------------------------------------------------------------------------------
void UninitResult(void)
{//頂点バッファの開放
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	//テクスチャの開放
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}
}

//-------------------------------------------------------------------------------
//更新処理
//-------------------------------------------------------------------------------
void UpdateResult(void)
{
	XinputGamepad*pXinputGamepad = GetXinputGamepad();

	bool bResultOK = false;

	if (bResultOK==false)
	{

		if (pXinputGamepad->bAButton == true)
		{

			bResultOK = true;

			//RETURNKeyを押した場合
			SetFade(FADE_OUT, MODE_TITLE);


			pXinputGamepad->bAButton = false;

		}
	}
}

//-------------------------------------------------------------------------------
//描画処理
//-------------------------------------------------------------------------------
void DrawResult(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResult);

	//背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}