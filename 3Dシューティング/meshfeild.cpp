//-------------------------------------------------------------------------------
//
// ゲーム制作[MeshField.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include"Meshfield.h"		//メッシュフィールドの表示

//-------------------------------------------------------------------------------
//グローバル変数
//-------------------------------------------------------------------------------
PDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;		//テクスチャ情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;	//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9	g_pIdxBuffMeshField = NULL;	//インデックスバッファへのポインタ
D3DXVECTOR3 g_posMeshField;			//位置
D3DXVECTOR3 g_rotMeshField;			//向き
D3DXMATRIX  g_mtxWorldMeshField;	//ワールドマトリックス
//MESHFIELD g_aMeshFeild[256];

//-------------------------------------------------------------------------------
//初期化処理
//-------------------------------------------------------------------------------
HRESULT InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\space.jpg", &g_pTextureMeshField);

	//ポリゴンの位置・向き
	g_posMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 9,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField, NULL)))
	{
		return E_FAIL;
	}

	//頂点情報へのポインタ
	VERTEX_3D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	/*g_aMeshField[0].pos = D3DXVECTOR3(SCREEN_WIDTH, 650.0f, 0.0f);*/

	//頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(-1500.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(1500.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(-1500.0f, 0.0f, -1000.0f);
	pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	pVtx[5].pos = D3DXVECTOR3(1500.0f, 0.0f, -1000.0f);
	pVtx[6].pos = D3DXVECTOR3(-1500.0f, 0.0f, -2000.0f);
	pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -2000.0f);
	pVtx[8].pos = D3DXVECTOR3(1500.0f, 0.0f, -2000.0f);

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
	g_pVtxBuffMeshField->Unlock();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14, D3DUSAGE_WRITEONLY,
								D3DFMT_INDEX16, D3DPOOL_MANAGED,
								&g_pIdxBuffMeshField,NULL);

	WORD*pIdx;	//インデックス情報へのポインタ

	//インデックスバッファをロックし、番号データへのポインタを取得
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

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
	g_pIdxBuffMeshField->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//終了処理
//-------------------------------------------------------------------------------
void UninitMeshField(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	//テクスチャの開放
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	//インデックスバッファの破棄
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//-------------------------------------------------------------------------------
//更新処理
//-------------------------------------------------------------------------------
void UpdateMeshField(void)
{
	////デバイスの取得
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	////頂点情報へのポインタ
	//VERTEX_3D*pVtx;

	//for (int nCntMeshFeild = 0; nCntMeshFeild < 28; nCntMeshFeild++)
	//{
	//	if (GetKeyboardPress(DIK_RETURN) == true)
	//	{
	//		g_MeshField[nCntMeshFeild] -= D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	//	}
	//}
}

//-------------------------------------------------------------------------------
//描画処理
//-------------------------------------------------------------------------------
void DrawMeshField(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	//向きを反映する
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_rotMeshField.x, g_rotMeshField.y, g_rotMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshField);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshField);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, 0, 14);
}

//MESHFIELD*GetMeshField(void)
//{
//	return &g_aMeshFeild;
//}
