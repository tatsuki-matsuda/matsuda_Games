//--------------------------------------------------------------------------------
//
// ゲーム制作[Wall.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include"wall.h"		//ゲーム画面

//-------------------------------------------------------------------------------
//グローバル変数
//-------------------------------------------------------------------------------
PDIRECT3DTEXTURE9 g_pTextureWall = NULL;		//テクスチャ情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;	//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9	g_pIdxBuffWall = NULL;	//インデックスバッファへのポインタ
D3DXVECTOR3 aPos[2];			//外積
D3DXVECTOR3 g_posWall;			//位置
D3DXVECTOR3 g_rotWall;			//向き
D3DXMATRIX  g_mtxWorldWall;		//ワールドマトリックス
//MODE g_stage = MODE_STAGE1;	//ステージのモード

//-------------------------------------------------------------------------------
//初期化処理
//-------------------------------------------------------------------------------
HRESULT InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\field002.jpg", &g_pTextureWall);

	//ポリゴンの位置・向き
	g_posWall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotWall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 9,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall, NULL)))
	{
		return E_FAIL;
	}

	//頂点情報へのポインタ
	VERTEX_3D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	/*for(int nCnt)*/
	//頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(-500.0f, 400.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 400.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(500.0f, 400.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(-500.0f, 200.0f, 0.0f);
	pVtx[4].pos = D3DXVECTOR3(0.0f, 200.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(500.0f, 200.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(-500.0f, 0.0f, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[8].pos = D3DXVECTOR3(500.0f, 0.0f, 0.0f);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
	pVtx[5].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[6].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 0.5f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14, D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, D3DPOOL_MANAGED,
		&g_pIdxBuffWall, NULL);

	WORD*pIdx;	//インデックス情報へのポインタ

	//インデックスバッファをロックし、番号データへのポインタを取得
	g_pIdxBuffWall->Lock(0, 0, (void**)&pIdx, 0);

	//番号データの設定
	pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;

	//インデックスバッファをアンロックする
	g_pIdxBuffWall->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//終了処理
//-------------------------------------------------------------------------------
void UninitWall(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}

	//テクスチャの開放
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//インデックスバッファの破棄
	if (g_pIdxBuffWall != NULL)
	{
		g_pIdxBuffWall->Release();
		g_pIdxBuffWall = NULL;
	}
}

//-------------------------------------------------------------------------------
//更新処理
//-------------------------------------------------------------------------------
void UpdateWall(void)
{
}

//-------------------------------------------------------------------------------
//描画処理
//-------------------------------------------------------------------------------
void DrawWall(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldWall);

	//向きを反映する
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotWall.y, g_rotWall.x, g_rotWall.z);
	D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_rotWall.x, g_rotWall.y, g_rotWall.z);
	D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldWall);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffWall);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureWall);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, 0, 12);
}
