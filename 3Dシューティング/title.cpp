//-------------------------------------------------------------------------------
//
// ゲーム制作[title.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include "title.h"
#include "input.h"
#include "fade.h"
#include "xinput_gamepad.h"	//コントローラーの詳細
//#include "sound.h"

//-------------------------------------------------------------------------------
//グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureTitle[2] = {};			//テクスチャ情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//頂点バッファへのポインタ
D3DXVECTOR3 g_posPressEnter;						// エンターの中心座標
D3DXCOLOR g_LogoCol;								// 色	
int g_nCnt;
bool g_PressOK;										// キーを押したか
int g_nCntFlash;									// カウント
float g_posY;

//-------------------------------------------------------------------------------
//初期化処理
//-------------------------------------------------------------------------------
HRESULT InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	g_nCnt = 0;

	//デバイスの取得
	pDevice = GetDevice();

	g_posPressEnter = D3DXVECTOR3(SCREEN_WIDTH / 2, 450.0f, 0.0f);
	g_posY = 0.0f;
	g_LogoCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_PressOK = false;
	g_nCntFlash = 0;

	//変数宣言
	VERTEX_2D*pVtx;

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * 3 ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle, NULL)))
	{
		return E_FAIL;
	}


	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\title001.png", &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\TitleName001.png", &g_pTextureTitle[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\PressEnter.png", &g_pTextureTitle[2]);

	for (int nCntTitle = 0; nCntTitle < 2; nCntTitle++)
	{
		switch (nCntTitle)
		{
		case 0:
			pVtx[0].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);				//左下の座標
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//左上の座標
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);		//右下の座標
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);				//右上の座標
			break;

		case 1:
			pVtx[0].pos = D3DXVECTOR3(150.0f, SCREEN_HEIGHT, 0.0f);			//左下の座標
			pVtx[1].pos = D3DXVECTOR3(150.0f, 0.0f, 0.0f);					//左上の座標
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);	//右下の座標
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);			//右上の座標

		//case 2:
		//	pVtx[0].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);			//左下の座標
		//	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//左上の座標
		//	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);	//右下の座標
		//	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);			//右上の座標

		default:
			break;
		}

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

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//終了処理
//-------------------------------------------------------------------------------
void UninitTitle(void)
{//頂点バッファの開放
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	for (int nCntTitle = 0; nCntTitle < 2; nCntTitle++)
	{
		//テクスチャの開放
		if (g_pTextureTitle[nCntTitle] != NULL)
		{
			g_pTextureTitle[nCntTitle]->Release();
			g_pTextureTitle[nCntTitle] = NULL;
		}
	}

	////音楽を終了
	//StopSound();
}

//-------------------------------------------------------------------------------
//更新処理
//-------------------------------------------------------------------------------
void UpdateTitle(void)
{
	XinputGamepad*pXinputGamepad = GetXinputGamepad();

	bool bTitleOK = false;

	if (bTitleOK == false)
	{


		// 各モードに遷移
		if (pXinputGamepad->bAButton == true)
		{

			bTitleOK = true;

			pXinputGamepad->bAButton = false;

			// ゲームに遷移
			SetFade(FADE_OUT, MODE_TUTORIAL);

			// サウンド
			//PlaySound(SOUND_LABEL_SE_OK);
		}
	}
}
	

//	//else if (g_PressOK == true)
//	//{// 点滅させるためにカウントを進める
//	//	g_nCntFlash++;
//
//	//	if (CLEAR_NUMBER == g_nCntFlash % FLASH_INTERBAL)
//	//	{// 透明
//	//		g_LogoCol.a = 0.0f;
//	//	}
//	//	else if (LESS_CLEAR_NUMBER == g_nCntFlash % FLASH_INTERBAL)
//	//	{// 不透明
//	//		g_LogoCol.a = 1.0f;
//	//	}
//	//	// カウントがある程度進んだら遷移
//	//	if (g_nCntFlash >= 50)
//	//	{
//}
//		//}
//		//// 頂点座標の更新
//		//SetVertexTitleLogo(3);
//
//		////画面遷移
//		//if (GetKeyboardTrigger(DIK_RETURN) == true)
//		//{
//		//	SetFade(FADE_OUT, MODE_TUTORIAL);
//		//}
//	

//-------------------------------------------------------------------------------
//描画処理
//-------------------------------------------------------------------------------
void DrawTitle(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	for (int nCnttitle = 0; nCnttitle < 2; nCnttitle++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[nCnttitle]);

		//背景の描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnttitle * 4, 2);
	}
}

//-----------------------------------------------------------------
// タイトル画面に貼るテクスチャの指定
//-----------------------------------------------------------------
//void SetVertexTitleLogo(int nCntTitleLogo)
//{
//	// 構造体のポインタ変数
//	VERTEX_2D *pVtx;
//
//	// 頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
//
//	//	何番目か
//	pVtx += nCntTitleLogo * 4;
//
//	//{// 頂点座標の更新
//		pVtx[0].pos = D3DXVECTOR3(g_posPressEnter.x - (SELECTENTER_X / 2), g_posPressEnter.y + (SELECTENTER_Y / 2), 0.0f);
//		pVtx[1].pos = D3DXVECTOR3(g_posPressEnter.x - (SELECTENTER_X / 2), g_posPressEnter.y - (SELECTENTER_Y / 2), 0.0f);
//		pVtx[2].pos = D3DXVECTOR3(g_posPressEnter.x + (SELECTENTER_X / 2), g_posPressEnter.y + (SELECTENTER_Y / 2), 0.0f);
//		pVtx[3].pos = D3DXVECTOR3(g_posPressEnter.x + (SELECTENTER_X / 2), g_posPressEnter.y - (SELECTENTER_Y / 2), 0.0f);
//
//	// 頂点カラーの設定
//	pVtx[0].col = g_LogoCol;
//	pVtx[1].col = g_LogoCol;
//	pVtx[2].col = g_LogoCol;
//	pVtx[3].col = g_LogoCol;
//
//	// 頂点バッファをアンロックする
//	g_pVtxBuffTitle->Unlock();
//}

