//-------------------------------------------------------------------------------
//
// ゲーム制作[Polygon.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include"Polygon.h"		//ゲーム画面

//-------------------------------------------------------------------------------
//グローバル変数
//-------------------------------------------------------------------------------
PDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;		//テクスチャ情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;	//頂点バッファへのポインタ
D3DXVECTOR3 g_posPolygon;			//位置
D3DXVECTOR3 g_rotPolygon;			//向き
D3DXMATRIX  g_mtxWorldPolygon;		//ワールドマトリックス
//MODE g_stage = MODE_STAGE1;	//ステージのモード

//-------------------------------------------------------------------------------
//初期化処理
//-------------------------------------------------------------------------------
HRESULT InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\field002.jpg", &g_pTexturePolygon);

	//ポリゴンの位置・向き
	g_posPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon, NULL)))
	{
		return E_FAIL;
	}

	//頂点情報へのポインタ
		VERTEX_3D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

		//if (Mode = MODE_STAGE1)
		//{
		//	//プレイヤーステージ1の描画処理
		//	g_aPolygon[0].pos = D3DXVECTOR3(SCREEN_WIDTH, 650.0f, 0.0f);
		//}

		//if (Mode = MODE_STAGE2)
		//{
		//	//プレイヤーステージ2の描画処理
		//	g_aPolygon[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 80, 100.0f, 0.0f);
		//}


		/*g_aPolygon[0].pos = D3DXVECTOR3(SCREEN_WIDTH, 650.0f, 0.0f);*/

		//頂点情報の設定
		pVtx[0].pos = D3DXVECTOR3(-50.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-50.0f, 0.0f, -100.0f);
		pVtx[3].pos = D3DXVECTOR3(50.0f, 0.0f, -100.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f );
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f );
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f );
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f );

		//頂点座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffPolygon->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//終了処理
//-------------------------------------------------------------------------------
void UninitPolygon(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffPolygon != NULL)
	{

		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}

	//テクスチャの開放
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon->Release();
		g_pTexturePolygon = NULL;
	}
}

//-------------------------------------------------------------------------------
//更新処理
//-------------------------------------------------------------------------------
void UpdatePolygon(void)
{


}

//-------------------------------------------------------------------------------
//描画処理
//-------------------------------------------------------------------------------
void DrawPolygon(void)
{

	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	 //デバイスの取得
	pDevice = GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldPolygon);

	//向きを反映する
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotPolygon.y, g_rotPolygon.x, g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_rotPolygon.x, g_rotPolygon.y, g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolygon);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0,g_pVtxBuffPolygon,0,sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePolygon);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
