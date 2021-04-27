//-------------------------------------------------------------------------------
//
// ゲーム制作[player.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include <stdio.h>
#include"player.h"			//プレイヤーの詳細
#include"bullet.h"			//弾の詳細
#include"Camera.h"			//カメラの詳細
#include"xinput_gamepad.h"	//Xゲームパッドの詳細

#define DEBUG (1)

//-------------------------------------------------------------------------------
//グローバル変数
//-------------------------------------------------------------------------------
Model g_Model;								//モデルの情報
Player g_player;							//プレイヤーの情報
D3DXVECTOR3 g_aPos[2];						//線分の頂点
D3DXVECTOR3 vecA;							//プレイヤーと判定の頂点の距離
D3DXVECTOR3 vecB;							//判定の頂点同士の距離

//-------------------------------------------------------------------------------
//初期化処理
//-------------------------------------------------------------------------------
HRESULT InitPlayer(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// モデル数の総数を設定
	g_player.nNumModel = 14;

	//xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\bodyup.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[0].BuffMatModel, NULL,
		&g_player.aModel[0].nNumMat, &g_player.aModel[0].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\face.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[1].BuffMatModel, NULL,
		&g_player.aModel[1].nNumMat, &g_player.aModel[1].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\armRup.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[2].BuffMatModel, NULL,
		&g_player.aModel[2].nNumMat, &g_player.aModel[2].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\armRdown.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[3].BuffMatModel, NULL,
		&g_player.aModel[3].nNumMat, &g_player.aModel[3].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\handR.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[4].BuffMatModel, NULL,
		&g_player.aModel[4].nNumMat, &g_player.aModel[4].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\armLup.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[5].BuffMatModel, NULL,
		&g_player.aModel[5].nNumMat, &g_player.aModel[5].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\armLdown.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[6].BuffMatModel, NULL,
		&g_player.aModel[6].nNumMat, &g_player.aModel[6].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\handL.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[7].BuffMatModel, NULL,
		&g_player.aModel[7].nNumMat, &g_player.aModel[7].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\regRup.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[8].BuffMatModel, NULL,
		&g_player.aModel[8].nNumMat, &g_player.aModel[8].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\regRdown.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[9].BuffMatModel, NULL,
		&g_player.aModel[9].nNumMat, &g_player.aModel[9].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\regR.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[10].BuffMatModel, NULL,
		&g_player.aModel[10].nNumMat, &g_player.aModel[10].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\regLup.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[11].BuffMatModel, NULL,
		&g_player.aModel[11].nNumMat, &g_player.aModel[11].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\regLdown.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[12].BuffMatModel, NULL,
		&g_player.aModel[12].nNumMat, &g_player.aModel[12].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\regL.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[13].BuffMatModel, NULL,
		&g_player.aModel[13].nNumMat, &g_player.aModel[13].MeshModel);

	//各パーツの階層構造設定
	g_player.aModel[0].nIdxModelParent = -1;
	g_player.aModel[0].pos = D3DXVECTOR3(0.0, 45.0, 0.0);
	g_player.aModel[0].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[1].nIdxModelParent = 0;
	g_player.aModel[1].pos = D3DXVECTOR3(0.0, 25.0, 0.0);
	g_player.aModel[1].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[2].nIdxModelParent = 0;
	g_player.aModel[2].pos = D3DXVECTOR3(-10.0, 20.0, .0);
	g_player.aModel[2].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[3].nIdxModelParent = 2;
	g_player.aModel[3].pos = D3DXVECTOR3(-10.0, 0.0, 0.0);
	g_player.aModel[3].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[4].nIdxModelParent = 3;
	g_player.aModel[4].pos = D3DXVECTOR3(-10.0, 0.0, 0.0);
	g_player.aModel[4].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[5].nIdxModelParent = 0;
	g_player.aModel[5].pos = D3DXVECTOR3(10.0, 20.0, 0.0);
	g_player.aModel[5].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[6].nIdxModelParent = 5;
	g_player.aModel[6].pos = D3DXVECTOR3(10.0, 0.0, 0.0);
	g_player.aModel[6].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[7].nIdxModelParent = 6;
	g_player.aModel[7].pos = D3DXVECTOR3(10.0, 0.0, 0.0);
	g_player.aModel[7].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[8].nIdxModelParent = 0;
	g_player.aModel[8].pos = D3DXVECTOR3(-5.0, 0.0, 0.0);
	g_player.aModel[8].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[9].nIdxModelParent = 8;
	g_player.aModel[9].pos = D3DXVECTOR3(0.0, -20.0, 0.0);
	g_player.aModel[9].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[10].nIdxModelParent = 9;
	g_player.aModel[10].pos = D3DXVECTOR3(0.0, -20.0, 0.0);
	g_player.aModel[10].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[11].nIdxModelParent = 0;
	g_player.aModel[11].pos = D3DXVECTOR3(5.0, 0.0, 0.0);
	g_player.aModel[11].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[12].nIdxModelParent = 11;
	g_player.aModel[12].pos = D3DXVECTOR3(0.0, -20.0, 0.0);
	g_player.aModel[12].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[13].nIdxModelParent = 12;
	g_player.aModel[13].pos = D3DXVECTOR3(0.0, -20.0, 0.0);
	g_player.aModel[13].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	//プレイヤーの位置
	g_player.pos = D3DXVECTOR3(0.0, 0.0, -1000.0);

	//自機の有効化
	g_player.bUse = true;

	g_aPos[0] = D3DXVECTOR3(-100.0, 0.0, 500.0);
	g_aPos[1] = D3DXVECTOR3(100.0, 0.0, 500.0);

	g_aPos[0] + g_aPos[1] = vecA;
	g_aPos[0] + g_player.pos = vecB;
	
	return S_OK;
}

//-------------------------------------------------------------------------------
//終了処理
//-------------------------------------------------------------------------------
void UninitPlayer(void)
{
	for (int nModel = 0; nModel < g_player.nNumModel; nModel++)
	{
		//メッシュの破棄
		if (g_player.aModel[nModel].MeshModel != NULL)
		{
			g_player.aModel[nModel].MeshModel->Release();
			g_player.aModel[nModel].MeshModel = NULL;
		}

		//マテリアルの破棄
		if (g_player.aModel[nModel].BuffMatModel != NULL)
		{
			g_player.aModel[nModel].BuffMatModel->Release();
			g_player.aModel[nModel].BuffMatModel = NULL;
		}
	}
}

//-------------------------------------------------------------------------------
//更新処理
//-------------------------------------------------------------------------------
void UpdatePlayer(void)
{
	//変数宣言
	BULLET*pBullet = GetBullet();
	XinputGamepad*pXinputGamepad = GetXinputGamepad();
	CAMERA*pCamera = GetCamera();

	int nLife = 500;
	int nCntBullet = 0;
	int nCntShot = 0;
	int nCnt = 0;

	nCntShot++;

	//判定処理
	g_player.oldpos.z = (vecA.z*vecB.x) - (vecA.x*vecB.z);
	
	if (g_player.oldpos.z <= vecA.z)
	{
		if (g_player.pos.z > vecA.z)
		{
			g_player.pos.z = vecA.z;
		}
	}

	if (g_player.pos.x <= -100.0f && g_player.pos.x >= 100.0f)
	{
		g_player.move.x += 0;
	}

	if (g_player.pos.z <= -100.0f && g_player.pos.z >= 100.0f)
	{
		g_player.move.z = 0;
	}
	
	//慣性
	g_player.move.x += (0.0f - g_player.move.x)*0.1f;
	g_player.move.z += (0.0f - g_player.move.z)*0.1f;

	//移動処理
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;
	g_player.pos.z += g_player.move.z;
}

//-------------------------------------------------------------------------------
//描画処理
//-------------------------------------------------------------------------------
void DrawPlayer(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;		//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアルを使用
	D3DXMATERIAL*pMat;				//マテリアルデータへのポインタ
	D3DMATERIAL9  MatD3D;			//マテリアルデータのポインタ

	D3DXMATRIX mtxShadow;			//シャドウマトリックス
	D3DXVECTOR4 vecLight;			//ライトのベクトル
	D3DXVECTOR3 pos, normal;		//平面上の任意の点、法線ベクトル
	D3DXPLANE plane;				//平面

	if (g_player.bUse == true)
	{

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_player.mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
		D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
		D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

		//現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
		{
			//計算用マトリックス
			D3DXMATRIX mtxRotModel, mtxTransModel;

			//親のマトリックス
			D3DXMATRIX mtxParent;

			//各パーツのワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

			//各パーツの向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRot);

			//各パーツの位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTrans);

			//各パーツの親のマトリックスを設定
			if (g_player.aModel[nCntModel].nIdxModelParent != -1)
			{
				mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParent].mtxWorld;
			}
			else
			{
				mtxParent = g_player.mtxWorld;
			}

			//算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
			D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld,
				&g_player.aModel[nCntModel].mtxWorld,
				&mtxParent);

			//各パーツのワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[nCntModel].mtxWorld);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].BuffMatModel->GetBufferPointer();


			for (int nCntcolor = 0; nCntcolor < (int)g_player.aModel[nCntModel].nNumMat; nCntcolor++)
			{
				//マテリアルを設定
				pDevice->SetMaterial(&pMat[nCntcolor].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, NULL);

				//モデル(パーツ)の描画
				g_player.aModel[nCntModel].MeshModel->DrawSubset(nCntcolor);
			}

			for (int nCntcolor = 0; nCntcolor < (int)g_player.aModel[nCntModel].nNumMat; nCntcolor++)
			{

				//マテリアルを設定
				pDevice->SetMaterial(&MatD3D);

				//shadowマトリックスの初期化
				D3DXMatrixIdentity(&mtxShadow);

				//ライトのベクトル設定
				vecLight = D3DXVECTOR4(0.2f, 1.0f, 0.9f, 0.0f);

				//平面の生成
				pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				D3DXPlaneFromPointNormal(&plane, &pos, &normal);

				//シャドウマトリックスの生成
				D3DXMatrixShadow(&mtxShadow, &vecLight, &plane);
				D3DXMatrixMultiply(&mtxShadow, &g_player.aModel[nCntModel].mtxWorld, &mtxShadow);

				//シャドウマトリックス
				pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

				//モデル(パーツ)の描画
				g_player.aModel[nCntModel].MeshModel->DrawSubset(nCntcolor);
			}
		}

		//保存していたマテリアルを返す
		pDevice->SetMaterial(&matDef);
	}
}

//-------------------------------------------------------------------------------
//頂点座標の設定
//-------------------------------------------------------------------------------
Player*GetPlayer(void)
{
	return &g_player;
}