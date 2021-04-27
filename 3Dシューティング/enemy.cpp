//-------------------------------------------------------------------------------
//
// ゲーム制作[enemy.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include <stdio.h>
#include"Enemy.h"		//敵の詳細
#include"Player.h"		//プレイヤーの詳細
#include"bullet.h"		//弾の詳細
#include"Camera.h"		//カメラの詳細
#include"fade.h"		//フェードの詳細
#include "xinput_gamepad.h"	//Controllerの詳細

#define DEBUG (1)

//-------------------------------------------------------------------------------
//グローバル変数
//-------------------------------------------------------------------------------
ENEMYMODEL g_Model[MAX_ENEMY];		//モデルの情報
Enemy g_Enemy;						//エネミーの情報
int nDeathEnemy = 0;

//-------------------------------------------------------------------------------
//初期化処理
//-------------------------------------------------------------------------------
HRESULT InitEnemy(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// モデル数の総数を設定
	g_Enemy.nNumModel = MAX_ENEMY;
	
		//xファイルの読み込み
		D3DXLoadMeshFromX("data\\MODEL\\EnemyBoss.x", D3DXMESH_SYSTEMMEM, pDevice,
			NULL, &g_Enemy.aModel[0].BuffMatModel, NULL,
			&g_Enemy.aModel[0].nNumMat, &g_Enemy.aModel[0].MeshModel);

		D3DXLoadMeshFromX("data\\MODEL\\Enemy001.x", D3DXMESH_SYSTEMMEM, pDevice,
			NULL, &g_Enemy.aModel[1].BuffMatModel, NULL,
			&g_Enemy.aModel[1].nNumMat, &g_Enemy.aModel[1].MeshModel);

		D3DXLoadMeshFromX("data\\MODEL\\Enemy001.x", D3DXMESH_SYSTEMMEM, pDevice,
			NULL, &g_Enemy.aModel[2].BuffMatModel, NULL,
			&g_Enemy.aModel[2].nNumMat, &g_Enemy.aModel[2].MeshModel);

		D3DXLoadMeshFromX("data\\MODEL\\Enemy002.x", D3DXMESH_SYSTEMMEM, pDevice,
			NULL, &g_Enemy.aModel[3].BuffMatModel, NULL,
			&g_Enemy.aModel[3].nNumMat, &g_Enemy.aModel[3].MeshModel);

		D3DXLoadMeshFromX("data\\MODEL\\Enemy001.x", D3DXMESH_SYSTEMMEM, pDevice,
			NULL, &g_Enemy.aModel[4].BuffMatModel, NULL,
			&g_Enemy.aModel[4].nNumMat, &g_Enemy.aModel[4].MeshModel);

		D3DXLoadMeshFromX("data\\MODEL\\Enemy002.x", D3DXMESH_SYSTEMMEM, pDevice,
			NULL, &g_Enemy.aModel[5].BuffMatModel, NULL,
			&g_Enemy.aModel[5].nNumMat, &g_Enemy.aModel[5].MeshModel);

		D3DXLoadMeshFromX("data\\MODEL\\Enemy002.x", D3DXMESH_SYSTEMMEM, pDevice,
			NULL, &g_Enemy.aModel[6].BuffMatModel, NULL,
			&g_Enemy.aModel[6].nNumMat, &g_Enemy.aModel[6].MeshModel);

		D3DXLoadMeshFromX("data\\MODEL\\Enemy001.x", D3DXMESH_SYSTEMMEM, pDevice,
			NULL, &g_Enemy.aModel[7].BuffMatModel, NULL,
			&g_Enemy.aModel[7].nNumMat, &g_Enemy.aModel[7].MeshModel);

		D3DXLoadMeshFromX("data\\MODEL\\Enemy001.x", D3DXMESH_SYSTEMMEM, pDevice,
			NULL, &g_Enemy.aModel[8].BuffMatModel, NULL,
			&g_Enemy.aModel[8].nNumMat, &g_Enemy.aModel[8].MeshModel);
		
		//ボスの構造設定
		g_Enemy.aModel[0].nIdxModelParent = -1;
		g_Enemy.aModel[0].pos = D3DXVECTOR3(0.0, 60.0, -1000.0);
		g_Enemy.aModel[0].rot = D3DXVECTOR3(0.0, 0.0, 0.0);
		g_Enemy.aModel[0].nType = 0;
		g_Enemy.aModel[0].nEnemyLife = ENEMY_LIFEBOSS;
		g_Enemy.aModel[0].bUse = false;
		g_Enemy.aModel[0].bSearchRange = false;

		//敵の構造設定
		g_Enemy.aModel[1].nIdxModelParent = -1;
		g_Enemy.aModel[1].pos = D3DXVECTOR3(0.0, 60.0, 0.0);
		g_Enemy.aModel[1].rot = D3DXVECTOR3(0.0, 0.0, 0.0);
		g_Enemy.aModel[1].nType = 1;
		g_Enemy.aModel[1].nEnemyLife = ENEMY_LIFE000;
		g_Enemy.aModel[1].bUse = true;
		g_Enemy.aModel[1].nCounterEnemy = false;
		g_Enemy.aModel[1].bUseStopShot = false;
		g_Enemy.aModel[1].bSearchRange = false;
		g_Enemy.aModel[1].bAppearance = false;

		g_Enemy.aModel[2].nIdxModelParent = -1;
		g_Enemy.aModel[2].pos = D3DXVECTOR3(500.0, 60.0, -1300.0);
		g_Enemy.aModel[2].rot = D3DXVECTOR3(0.0, 0.0, 0.0);
		g_Enemy.aModel[2].nType = 1;
		g_Enemy.aModel[2].nEnemyLife = ENEMY_LIFE000;
		g_Enemy.aModel[2].bUse = false;
		g_Enemy.aModel[2].nCounterEnemy = false;
		g_Enemy.aModel[2].bSearchRange = false;
		g_Enemy.aModel[2].bAppearance = false;

		g_Enemy.aModel[3].nIdxModelParent = -1;
		g_Enemy.aModel[3].pos = D3DXVECTOR3(300.0, 60.0, -700.0);
		g_Enemy.aModel[3].rot = D3DXVECTOR3(0.0, 0.0, 0.0);
		g_Enemy.aModel[3].nType = 2;
		g_Enemy.aModel[3].nEnemyLife = ENEMY_LIFE001;
		g_Enemy.aModel[3].bUse = false;
		g_Enemy.aModel[3].nCounterEnemy = false;
		g_Enemy.aModel[3].bUseStopShot = false;
		g_Enemy.aModel[3].bSearchRange = false;
		g_Enemy.aModel[3].bAppearance = false;

		g_Enemy.aModel[4].nIdxModelParent = -1;
		g_Enemy.aModel[4].pos = D3DXVECTOR3(400.0, 60.0, 500.0);
		g_Enemy.aModel[4].rot = D3DXVECTOR3(0.0, 0.0, 0.0);
		g_Enemy.aModel[4].nType = 1;
		g_Enemy.aModel[4].nEnemyLife = ENEMY_LIFE000;
		g_Enemy.aModel[4].bUse = false;
		g_Enemy.aModel[4].nCounterEnemy = false;
		g_Enemy.aModel[4].bSearchRange = false;
		g_Enemy.aModel[4].bAppearance = false;

		g_Enemy.aModel[5].nIdxModelParent = -1;
		g_Enemy.aModel[5].pos = D3DXVECTOR3(0.0, 60.0, -1800.0);
		g_Enemy.aModel[5].rot = D3DXVECTOR3(0.0, 0.0, 0.0);
		g_Enemy.aModel[5].nType = 2;
		g_Enemy.aModel[5].nEnemyLife = ENEMY_LIFE001;
		g_Enemy.aModel[5].bUse = false;
		g_Enemy.aModel[5].nCounterEnemy = false;
		g_Enemy.aModel[5].bUseStopShot = false;
		g_Enemy.aModel[5].bSearchRange = false;
		g_Enemy.aModel[5].bAppearance = false;

		g_Enemy.aModel[6].nIdxModelParent = -1;
		g_Enemy.aModel[6].pos = D3DXVECTOR3(500.0, 60.0, -800.0);
		g_Enemy.aModel[6].rot = D3DXVECTOR3(0.0, 0.0, 0.0);
		g_Enemy.aModel[6].nType = 2;
		g_Enemy.aModel[6].nEnemyLife = ENEMY_LIFE001;
		g_Enemy.aModel[6].bUse = false;
		g_Enemy.aModel[6].nCounterEnemy = false;
		g_Enemy.aModel[6].bSearchRange = false;
		g_Enemy.aModel[6].bAppearance = false;

		g_Enemy.aModel[7].nIdxModelParent = -1;
		g_Enemy.aModel[7].pos = D3DXVECTOR3(-800.0, 60.0, -200.0);
		g_Enemy.aModel[7].rot = D3DXVECTOR3(0.0, 0.0, 0.0);
		g_Enemy.aModel[7].nType = 1;
		g_Enemy.aModel[7].nEnemyLife = ENEMY_LIFE000;
		g_Enemy.aModel[7].bUse = false;
		g_Enemy.aModel[7].nCounterEnemy = false;
		g_Enemy.aModel[7].bUseStopShot = false;
		g_Enemy.aModel[7].bSearchRange = false;
		g_Enemy.aModel[7].bAppearance = false;

		g_Enemy.aModel[8].nIdxModelParent = -1;
		g_Enemy.aModel[8].pos = D3DXVECTOR3(-500.0, 60.0, 400.0);
		g_Enemy.aModel[8].rot = D3DXVECTOR3(0.0, 0.0, 0.0);
		g_Enemy.aModel[8].nType = 1;
		g_Enemy.aModel[8].nEnemyLife = ENEMY_LIFE000;
		g_Enemy.aModel[8].bUse = false;
		g_Enemy.aModel[8].nCounterEnemy = false;
		g_Enemy.aModel[8].bSearchRange = false;
		g_Enemy.aModel[8].bAppearance = false;

	return S_OK;
}

//-------------------------------------------------------------------------------
//終了処理
//-------------------------------------------------------------------------------
void UninitEnemy(void)
{
	for (int nEnemy = 0; nEnemy < g_Enemy.nNumModel; nEnemy++)
	{
		//メッシュの破棄
		if (g_Enemy.aModel[nEnemy].MeshModel != NULL)
		{
			g_Enemy.aModel[nEnemy].MeshModel->Release();
			g_Enemy.aModel[nEnemy].MeshModel = NULL;
		}

		//マテリアルの破棄
		if (g_Enemy.aModel[nEnemy].BuffMatModel != NULL)
		{
			g_Enemy.aModel[nEnemy].BuffMatModel->Release();
			g_Enemy.aModel[nEnemy].BuffMatModel = NULL;
		}
	}
}

//-------------------------------------------------------------------------------
//更新処理
//-------------------------------------------------------------------------------
void UpdateEnemy(void)
{
	//変数宣言
	BULLET*pBullet = GetBullet();
	CAMERA*pCamera = GetCamera();
	Player*pPlayer = GetPlayer();
	XinputGamepad*pXinputGamepad = GetXinputGamepad();

	int nLife = 120;				//弾のライフ
	int nCntTime = 0;				//敵の出現時間
	int nCntDeath = 0;				//敵の消滅カウント
	int nCntAppearance = 0;			//ボスの出現カウント

	//敵の弾
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
	

				//敵1がfalseの時
		if (g_Enemy.aModel[1].bUse == false)
				{

					g_Enemy.aModel[2].bUse = true;


					if (g_Enemy.aModel[2].nEnemyLife <= 0)
					{
						g_Enemy.aModel[2].bUse = false;

						nCntAppearance = 1;

						nCntDeath = 0;
					}
					else
					{
						g_Enemy.aModel[2].bUse = true;
					}
					
				}

				//敵2がfalseの時
				if (g_Enemy.aModel[2].bUse == false && nCntAppearance == 1)
				{

					g_Enemy.aModel[3].bUse = true;

					if (g_Enemy.aModel[3].nEnemyLife <= 0)
					{
						g_Enemy.aModel[3].bUse =false;

						nCntAppearance = 2;

					}
					else
					{
						g_Enemy.aModel[3].bUse = true;
					}

					
				}

				//敵3がfalseの時
				if (g_Enemy.aModel[3].bUse == false && nCntAppearance == 2)
				{
					g_Enemy.aModel[4].bUse = true;
					g_Enemy.aModel[5].bUse = true;


					if (g_Enemy.aModel[4].nEnemyLife <= 0)
					{
						g_Enemy.aModel[4].bUse = false;
						
					}
					else
					{

						g_Enemy.aModel[4].bUse = true;
					}

					if(g_Enemy.aModel[5].nEnemyLife <= 0)
					{
						g_Enemy.aModel[5].bUse = false;

						nCntAppearance = 3;

					}
					else
					{
						
						g_Enemy.aModel[5].bUse = true;
					}

					nCntAppearance = 3;
				}

				//敵4と5がfalseの時
				if (g_Enemy.aModel[5].bUse == false && nCntAppearance == 3)
				{

					g_Enemy.aModel[6].bUse = true;
					g_Enemy.aModel[7].bUse = true;
					g_Enemy.aModel[8].bUse = true;


					if (g_Enemy.aModel[6].nEnemyLife <= 0)
					{
						g_Enemy.aModel[6].bUse = false;

						nCntAppearance = 4;
					
					}
					else
					{
						g_Enemy.aModel[6].bUse = true;
		
					}

					if (g_Enemy.aModel[7].nEnemyLife <= 0)
					{
						
						g_Enemy.aModel[7].bUse = false;

						
					}
					else
					{
					
						g_Enemy.aModel[7].bUse = true;
					}

					if (g_Enemy.aModel[8].nEnemyLife <= 0)
					{
						g_Enemy.aModel[8].bUse = false;


					}
					else
					{
						g_Enemy.aModel[8].bUse = true;

					}

					
				}

				//敵6と7がfalseの時
				if (g_Enemy.aModel[6].bUse == false && nCntAppearance == 4) 		
				{
	
					g_Enemy.aModel[0].bUse = true;
					g_Enemy.aModel[1].bUse = true;
					g_Enemy.aModel[2].bUse = true;


					if (g_Enemy.aModel[0].nEnemyLife <= 0)
					{

						g_Enemy.aModel[0].bUse = false;
						g_Enemy.aModel[1].bUse = false;

						//ボスを倒した時
						SetFade(FADE_OUT, MODE_RESULT);

						pXinputGamepad->bAButton = false;

						nCntAppearance = 0;

					}
					else
					{
						g_Enemy.aModel[0].bUse = true;
						g_Enemy.aModel[1].bUse = true;
					}
					
				}

		//敵がいる場合
		if (g_Enemy.aModel[nCntEnemy].bUse == true)
		{

			D3DXVECTOR3 VecEnemy = pPlayer->pos - g_Enemy.aModel[nCntEnemy].pos;			//敵のベクトル
			float fLengthEnemy = sqrtf(VecEnemy.x * VecEnemy.x + VecEnemy.z * VecEnemy.z);	//自機との距離
			float fAngleEnemy = atan2f(VecEnemy.x, VecEnemy.z);								//自機を狙う角度

			g_Enemy.aModel[nCntEnemy].rot.y += 0.005f;
			
				//接敵
				g_Enemy.aModel[nCntEnemy].bSearchRange = true;


			//索敵範囲
			if (fLengthEnemy <= SEARCHRANGE_ENEMY)
			{
				//接敵
				g_Enemy.aModel[nCntEnemy].bSearchRange = true;
			}

			//接敵した場合
			if (g_Enemy.aModel[nCntEnemy].bSearchRange == true)
			{	
				//ボスだった場合
				if (g_Enemy.aModel[nCntEnemy].nType == 0)
				{
					//ボスが有効になっていた場合
					if (g_Enemy.aModel[0].bUse == true)
					{
						//追跡
						g_Enemy.aModel[0].pos += D3DXVECTOR3(sinf(g_Enemy.aModel[0].rot.y)*1.8f, 0.0f, cosf(g_Enemy.aModel[0].rot.y)*1.8f);
					}


					//ボスの弾の発射範囲
					if (fLengthEnemy <= LAUNCHRANGE_BOSSBULLET)
					{
						int nCntAngle = 0;

						nCntAngle++;

						SetBullet(g_Enemy.aModel[0].pos, D3DXVECTOR3(sinf(g_Enemy.aModel[0].rot.y)*8.0f, 0.0f, cosf(g_Enemy.aModel[0].rot.y)*8.0f),
							BULLETSTATE_ENEMY, nLife, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

						SetBullet(g_Enemy.aModel[0].pos, D3DXVECTOR3(sinf(g_Enemy.aModel[0].rot.y + 1.0f)*8.0f, 0.0f, cosf(g_Enemy.aModel[0].rot.y + 1.0f)*8.0f),
							BULLETSTATE_ENEMY, nLife, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

						SetBullet(g_Enemy.aModel[0].pos, D3DXVECTOR3(sinf(g_Enemy.aModel[0].rot.y + 2.0f)*8.0f, 0.0f, cosf(g_Enemy.aModel[0].rot.y + 2.0f)*8.0f),
							BULLETSTATE_ENEMY, nLife, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

						SetBullet(g_Enemy.aModel[0].pos, D3DXVECTOR3(sinf(g_Enemy.aModel[0].rot.y + 3.0f)*8.0f, 0.0f, cosf(g_Enemy.aModel[0].rot.y + 3.0f)*8.0f),
							BULLETSTATE_ENEMY, nLife, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

						SetBullet(g_Enemy.aModel[0].pos, D3DXVECTOR3(sinf(g_Enemy.aModel[0].rot.y + 4.0f)*8.0f, 0.0f, cosf(g_Enemy.aModel[0].rot.y + 4.0f)*8.0f),
							BULLETSTATE_ENEMY, nLife, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

						SetBullet(g_Enemy.aModel[0].pos, D3DXVECTOR3(sinf(g_Enemy.aModel[0].rot.y + 5.0f)*8.0f, 0.0f, cosf(g_Enemy.aModel[0].rot.y + 5.0f)*8.0f),
							BULLETSTATE_ENEMY, nLife, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					}
				}

				

				//赤い敵だった場合
				if (g_Enemy.aModel[nCntEnemy].nType == 1)
				{
					//索敵停止範囲に入った場合
					if (fLengthEnemy <= SEARCHSTOP_ENEMY)
					{
						//発射カウントを有効
						g_Enemy.aModel[nCntEnemy].bUseStopShot = true;

					}
					else
					{
						//発射カウントが無効の場合
						if (g_Enemy.aModel[nCntEnemy].bUseStopShot == false)
						{
							//追跡
							g_Enemy.aModel[nCntEnemy].pos += D3DXVECTOR3(sinf(fAngleEnemy)*8.0f, 0.0f, cosf(fAngleEnemy)*5.0f);
						}
					}

					//索敵停止範囲内の処理
					if (g_Enemy.aModel[nCntEnemy].bUseStopShot == true)
					{
						//一定時間停止
						g_Enemy.aModel[nCntEnemy].pos += D3DXVECTOR3(sinf(fAngleEnemy)*0.0f, 0.0f, cosf(fAngleEnemy)*0.0f);

						//発射までのカウントを開始
						g_Enemy.aModel[nCntEnemy].nCounterShot++;
					}


					//発射カウントが一定値以上の場合
					if (g_Enemy.aModel[nCntEnemy].nCounterShot >= 35)
					{
						//弾の管理
						SetBullet(g_Enemy.aModel[nCntEnemy].pos, D3DXVECTOR3(D3DXVECTOR3(sinf(fAngleEnemy)*1.5f, 0.0f, cosf(fAngleEnemy)*1.5f)),
							BULLETSTATE_ENEMY, nLife, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

					}

					//一定時間停止後及び発射カウントが一定値以上の場合
					if (g_Enemy.aModel[nCntEnemy].nCounterShot >= 180)
					{
						//発射カウントのリセット
						g_Enemy.aModel[nCntEnemy].nCounterShot = 0;

						//発射カウントを無効化
						g_Enemy.aModel[nCntEnemy].bUseStopShot = false;

					}
				}

				//棘の敵だった場合
				if (g_Enemy.aModel[nCntEnemy].nType == 2)
				{
					//追跡
					g_Enemy.aModel[nCntEnemy].pos += D3DXVECTOR3(sinf(fAngleEnemy)*2.5f, 0.0f, cosf(fAngleEnemy)*2.5f);

					//弾の発射範囲
					if (fLengthEnemy <= LAUNCHRANGE_BULLET)
					{
						int nCntAngle = 0;

						nCntAngle++;

						//弾の発射
						SetBullet(g_Enemy.aModel[nCntEnemy].pos, D3DXVECTOR3(sinf(g_Enemy.aModel[nCntEnemy].rot.y *6.0f)*5.0f, 0.0f, cosf(g_Enemy.aModel[nCntEnemy].rot.y*6.0f)*8.0f),
						BULLETSTATE_ENEMY, nLife, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

						//SetBullet(g_Enemy.aModel[nCntEnemy].pos, D3DXVECTOR3(sinf(fAngleEnemy+1.2f)*12.0f, 0.0f, cosf(fAngleEnemy+1.2f)*12.0f),
						//BULLETSTATE_ENEMY, nLife, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

					}
				}
			}



				//敵の体力が0以下になった場合
				if (g_Enemy.aModel[1].nEnemyLife <= 0)
				{
					//敵消滅                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
					g_Enemy.aModel[1].bUse = false;

				}
				else
				{
					//敵消滅
					g_Enemy.aModel[1].bUse = true;
				}


			
			
			//慣性
			g_Enemy.aModel[nCntEnemy].move.x += (0.0f - g_Enemy.aModel[nCntEnemy].move.x)*0.1f;
			g_Enemy.aModel[nCntEnemy].move.z += (0.0f - g_Enemy.aModel[nCntEnemy].move.z)*0.1f;

			//移動処理
			g_Enemy.aModel[nCntEnemy].pos.x += g_Enemy.aModel[nCntEnemy].move.x;
			g_Enemy.aModel[nCntEnemy].pos.y += g_Enemy.aModel[nCntEnemy].move.y;
			g_Enemy.aModel[nCntEnemy].pos.z += g_Enemy.aModel[nCntEnemy].move.z;

		}

	}

}

//-------------------------------------------------------------------------------
//描画処理
//-------------------------------------------------------------------------------
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;					//計算用マトリックス
	D3DMATERIAL9 matDef;							//現在のマテリアルを使用
	D3DXMATERIAL*pMat;								//

	//マテリアルデータへのポインタ
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy.aModel[nCntEnemy].bUse == true)
		{
			//各ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Enemy.aModel[nCntEnemy].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy.aModel[nCntEnemy].rot.y, g_Enemy.aModel[nCntEnemy].rot.x, g_Enemy.aModel[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_Enemy.aModel[nCntEnemy].mtxWorld, &g_Enemy.aModel[nCntEnemy].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Enemy.aModel[nCntEnemy].pos.x, g_Enemy.aModel[nCntEnemy].pos.y, g_Enemy.aModel[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_Enemy.aModel[nCntEnemy].mtxWorld, &g_Enemy.aModel[nCntEnemy].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy.aModel[nCntEnemy].mtxWorld);

			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Enemy.aModel[nCntEnemy].BuffMatModel->GetBufferPointer();

			for (int nCntcolor = 0; nCntcolor < (int)g_Enemy.aModel[nCntEnemy].nNumMat; nCntcolor++)
			{
				//マテリアルを設定
				pDevice->SetMaterial(&pMat[nCntcolor].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, NULL);

				//モデル(パーツ)の描画
				g_Enemy.aModel[nCntEnemy].MeshModel->DrawSubset(nCntcolor);
			}

			//保存していたマテリアルを返す
			pDevice->SetMaterial(&matDef);

		}
	}
}

////-------------------------------------------------------------------------------
////敵の設定
////-------------------------------------------------------------------------------
//void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType,int nLife, D3DXCOLOR col)
//{
//	//変数宣言
//	Enemy*pEnemy = &g_Enemy;
//
//	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy, pEnemy++)
//	{
//		//弾を使用している場合
//		if (pEnemy->bUse == false)
//		{
//
//			//位置を設定
//			pEnemy->pos = pos;
//
//			//移動量を設定
//			pEnemy->move = move;
//
//			//移動量を設定
//			pEnemy->nType = nType;
//
//			//寿命を設定
//			pEnemy->nLife = nLife;
//
//			//弾を使用していない場合
//			pEnemy->bUse = true;
//
//			break;
//		}
//	}
//}

//-------------------------------------------------------------------------------
//頂点座標の設定
//-------------------------------------------------------------------------------
Enemy *GetEnemy(void)
{
	return &g_Enemy;
}