//-------------------------------------------------------------------------------
//
// ゲーム制作[MeshSky.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include"Meshsky.h"		//メッシュフィールドの表示

//-------------------------------------------------------------------------------
//グローバル変数
//-------------------------------------------------------------------------------
PDIRECT3DTEXTURE9 g_pTextureMeshSky = NULL;		//テクスチャ情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshSky = NULL;	//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9	g_pIdxBuffMeshSky = NULL;	//インデックスバッファへのポインタ
D3DXVECTOR3 g_posMeshSky;			//位置
D3DXVECTOR3 g_rotMeshSky;			//向き
D3DXMATRIX  g_mtxWorldMeshSky;	//ワールドマトリックス
									//MeshSky g_aMeshFeild[256];

//-------------------------------------------------------------------------------
//初期化処理
//-------------------------------------------------------------------------------
HRESULT InitMeshSky(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\sky.jpg", &g_pTextureMeshSky);

	//ポリゴンの位置・向き
	g_posMeshSky = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshSky = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 17,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshSky, NULL)))
	{
		return E_FAIL;
	}

	//頂点情報へのポインタ
	VERTEX_3D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMeshSky->Lock(0, 0, (void**)&pVtx, 0);

	/*g_aMeshSky[0].pos = D3DXVECTOR3(SCREEN_WIDTH, 650.0f, 0.0f);*/

		//頂点情報の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 100.0f, -700.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 100.0f, -650.0f);
		pVtx[2].pos = D3DXVECTOR3(3.0f, 100.0f, -600.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 50.0f, -700.0f);
		pVtx[4].pos = D3DXVECTOR3(10.0f, 50.0f, -650.0f);
		pVtx[5].pos = D3DXVECTOR3(3.0f, 50.0f, -600.0f);
		pVtx[6].pos = D3DXVECTOR3(0.0f, 0.0f, -700.0f);
		pVtx[7].pos = D3DXVECTOR3(10.0f, 0.0f, -650.0f);
		pVtx[8].pos = D3DXVECTOR3(3.0f, 0.0f, -600.0f);

		pVtx[9].pos = D3DXVECTOR3(0.0f, 100.0f, -550.0f);
		pVtx[10].pos = D3DXVECTOR3(10.0f, 100.0f, -500.0f);
		pVtx[11].pos = D3DXVECTOR3(3.0f, 100.0f, -550.0f);
		pVtx[12].pos = D3DXVECTOR3(0.0f, 50.0f, -550.0f);
		pVtx[13].pos = D3DXVECTOR3(10.0f, 50.0f, -500.0f);
		pVtx[14].pos = D3DXVECTOR3(3.0f, 50.0f, -550.0f);
		pVtx[15].pos = D3DXVECTOR3(0.0f, 0.0f, -550.0f);
		pVtx[16].pos = D3DXVECTOR3(10.0f, 0.0f, -500.0f);
		pVtx[17].pos = D3DXVECTOR3(3.0f, 0.0f, -550.0f);

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

		pVtx[9].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[10].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[11].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[12].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[13].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[14].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[15].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[16].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[17].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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

		pVtx[9].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[11].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[12].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[13].tex = D3DXVECTOR2(0.5f, 0.5f);
		pVtx[14].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVtx[15].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[16].tex = D3DXVECTOR2(1.0f, 0.5f);
		pVtx[17].tex = D3DXVECTOR2(1.0f, 1.0f);

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

		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffMeshSky->Unlock();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * 28, D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, D3DPOOL_MANAGED,
		&g_pIdxBuffMeshSky, NULL);

	WORD*pIdx;	//インデックス情報へのポインタ

	//インデックスバッファをロックし、番号データへのポインタを取得
	g_pIdxBuffMeshSky->Lock(0, 0, (void**)&pIdx, 0);

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

	pIdx[14] = 12;
	pIdx[15] = 9;
	pIdx[16] = 13;
	pIdx[17] = 10;
	pIdx[18] = 14;
	pIdx[19] = 11;
	pIdx[20] = 11;
	pIdx[21] = 15;
	pIdx[22] = 15;
	pIdx[23] = 12;
	pIdx[24] = 16;
	pIdx[25] = 13;
	pIdx[26] = 17;
	pIdx[27] = 14;

	//インデックスバッファをアンロックする
	g_pIdxBuffMeshSky->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//終了処理
//-------------------------------------------------------------------------------
void UninitMeshSky(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffMeshSky != NULL)
	{
		g_pVtxBuffMeshSky->Release();
		g_pVtxBuffMeshSky = NULL;
	}

	//テクスチャの開放
	if (g_pTextureMeshSky != NULL)
	{
		g_pTextureMeshSky->Release();
		g_pTextureMeshSky = NULL;
	}

	//インデックスバッファの破棄
	if (g_pIdxBuffMeshSky != NULL)
	{
		g_pIdxBuffMeshSky->Release();
		g_pIdxBuffMeshSky = NULL;
	}
}

//-------------------------------------------------------------------------------
//更新処理
//-------------------------------------------------------------------------------
void UpdateMeshSky(void)
{
	////デバイスの取得
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	////頂点情報へのポインタ
	//VERTEX_3D*pVtx;

	//for (int nCntMeshFeild = 0; nCntMeshFeild < 28; nCntMeshFeild++)
	//{
	//	if (GetKeyboardPress(DIK_RETURN) == true)
	//	{
	//		g_MeshSky[nCntMeshFeild] -= D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	//	}
	//}
}

//-------------------------------------------------------------------------------
//描画処理
//-------------------------------------------------------------------------------
void DrawMeshSky(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

								//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshSky);

	//向きを反映する
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshSky.y, g_rotMeshSky.x, g_rotMeshSky.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshSky, &g_mtxWorldMeshSky, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_rotMeshSky.x, g_rotMeshSky.y, g_rotMeshSky.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshSky, &g_mtxWorldMeshSky, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshSky);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshSky, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshSky);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshSky);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 17, 0, 28);
}

//MeshSky*GetMeshSky(void)
//{
//	return &g_aMeshFeild;
//}
