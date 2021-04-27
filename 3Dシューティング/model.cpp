//-------------------------------------------------------------------------------
//
// ゲーム制作[Model.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include"Model.h"		//ゲーム画面
#include"bullet.h"		//弾の詳細

//-------------------------------------------------------------------------------
//グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3D9 g_apTextureModel[100] = {};	//テクスチャへのポインタ
LPD3DXMESH g_pMeshModel = NULL;			//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatModel = NULL;	//マテリアル(材質情報)へのポインタ
D3DXVECTOR3 g_posModel;					//位置
D3DXVECTOR3 g_rotModel;					//向き
D3DXMATRIX  g_mtxWorldModel;			//ワールドマトリックス
DWORD g_nNumMatModel;					//マテリアルの数
MODEL g_aModel;							//モデル

//-------------------------------------------------------------------------------
//初期化処理
//-------------------------------------------------------------------------------
void InitModel(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\field002.jpg", &g_pTextureModel);

	//xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\car000.x", D3DXMESH_SYSTEMMEM, pDevice,
						NULL, &g_pBuffMatModel, NULL, 
						&g_nNumMatModel,&g_pMeshModel);

	D3DXMATERIAL*pMat;

	//マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				pMat[1].pTextureFilename = "data\\TEXTURE\\eye.jpg";
			}
		}

	//ポリゴンの位置・向きの初期設定
	g_posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

//-------------------------------------------------------------------------------
//終了処理
//-------------------------------------------------------------------------------
void UninitModel(void)
{
	//メッシュの破棄
	if (g_pMeshModel!= NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}

//-------------------------------------------------------------------------------
//更新処理
//-------------------------------------------------------------------------------
void UpdateModel(void)
{
	////変数宣言
	//BULLET*pBullet;
	//int nLife = 50;
	//int nCntBullet = 0;
	//int nCntShot = 0;
	//int nCnt = 0;

	//pBullet = GetBullet();

	//nCntShot++;

	////弾の発射
	//if (GetKeyboardPress(DIK_SPACE) == true && nCntShot % 2 == 0)
	//{
	//	SetBullet(g_posModel, D3DXVECTOR3(sinf(g_rotModel.y), 0.0f, cosf(g_rotModel.y)), nLife, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//	nCntBullet++;
	//	

	//	if (nCntBullet >= 50 )
	//	{
	//		nCnt++;

	//		if (nCnt >= 2)
	//		{
	//			pBullet->bUse = false;
	//			nCntBullet = 0;
	//			nCnt = 0;
	//			nCntShot = 0;
	//		}
	//	}
	//}

	////上移動
	//if (GetKeyboardPress(DIK_UP) == true)
	//{
	//	g_posModel.z += 1.5f;
	//}

	////下移動
	//if (GetKeyboardPress(DIK_DOWN) == true)
	//{
	//	g_posModel.z -= 1.5f;
	//}

	////右移動
	//if (GetKeyboardPress(DIK_RIGHT) == true)
	//{
	//	g_posModel.x += 1.5f;
	//}

	////モデル右回転
	//if (GetKeyboardPress(DIK_RSHIFT) == true)
	//{
	//	//回転πの制限
	//	if (g_rotModel.y < -D3DX_PI)
	//	{
	//		g_rotModel.y += D3DX_PI * 2.0f;
	//	}

	//	//回転
	//	g_rotModel.y -= 0.1f;
	//}

	////左移動
	//if (GetKeyboardPress(DIK_LEFT) == true)
	//{
	//	g_posModel.x -= 1.5f;
	//}

	//if (GetKeyboardPress(DIK_LSHIFT) == true)
	//{
	//	//回転πの制限
	//	if (g_rotModel.y > D3DX_PI)
	//	{
	//		g_rotModel.y += D3DX_PI * 2.0f;
	//	}

	//	//回転
	//	g_rotModel.y += 0.1f;
	//}

}

//-------------------------------------------------------------------------------
//描画処理
//-------------------------------------------------------------------------------
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアルを使用
	D3DXMATERIAL*pMat;				//マテリアルデータへのポインタ

	pDevice = GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		//マテリアルを設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, NULL);

		//モデル(パーツ)の描画
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを返す
	pDevice->SetMaterial(&matDef);
}

MODEL*GetModel(void)
{
	return &g_aModel;
}
