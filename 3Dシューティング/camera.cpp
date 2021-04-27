//-------------------------------------------------------------------------------
//
// ゲーム制作[Camera.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include"Camera.h"		//ゲーム画面
#include"player.h"

//-------------------------------------------------------------------------------
//グローバル変数
//-------------------------------------------------------------------------------
CAMERA g_aCamera;	//カメラの情報

//-------------------------------------------------------------------------------
//初期化処理
//-------------------------------------------------------------------------------
void InitCamera(void)
{
	//カメラの位置
	g_aCamera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aCamera.posV = D3DXVECTOR3(0.0f, MAX_POSV_Y, MAX_POSV_Z);
	g_aCamera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aCamera.posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//g_aCamera.posR.x = g_aCamera.posV.x +- sinf();
}

//-------------------------------------------------------------------------------
//終了処理
//-------------------------------------------------------------------------------
void UninitCamera(void)
{
}

//-------------------------------------------------------------------------------
//更新処理
//-------------------------------------------------------------------------------
void UpdateCamera(void)
{
	Player*pPlayer = GetPlayer();

	g_aCamera.posR.x = pPlayer->pos.x;
	g_aCamera.posR.z = pPlayer->pos.z;
	g_aCamera.posR.y = pPlayer->pos.y;

	//注視点上回転
	if (GetKeyboardPress(DIK_U) == true)
	{
		//注視点πの制限
		if (g_aCamera.rot.y > D3DX_PI)
		{
			g_aCamera.rot.y -= D3DX_PI * 2.0f;
		}
		//注視点移動
		g_aCamera.rot.x += 0.03f;
		g_aCamera.posR.y = g_aCamera.posV.y - sinf(g_aCamera.rot.x)* MAX_POSV_Z;
		g_aCamera.posR.z = g_aCamera.posV.z - cosf(g_aCamera.rot.x)* MAX_POSV_Z;
	}

	//注視点下回転
	if (GetKeyboardPress(DIK_J) == true)
	{
		//注視点πの制限
		if (g_aCamera.rot.y <- D3DX_PI)
		{
			g_aCamera.rot.y -= D3DX_PI * 2.0f;
		}
		//注視点移動
		g_aCamera.rot.x -= 0.1f;
		g_aCamera.posR.y = g_aCamera.posV.y - sinf(g_aCamera.rot.x)* MAX_POSV_Z;
		g_aCamera.posR.z = g_aCamera.posV.z - cosf(g_aCamera.rot.x)* MAX_POSV_Z;
	}

		//視点右回転
		if (GetKeyboardPress(DIK_Z) == true)
		{
			//視点πの制限
			if (g_aCamera.rot.y > D3DX_PI)
			{
				g_aCamera.rot.y -= D3DX_PI * 2.0f;
			}
			//視点移動
			g_aCamera.rot.y += 0.03f;
			g_aCamera.posV.x = g_aCamera.posR.x - sinf(g_aCamera.rot.y)* MAX_POSV_Z;
			g_aCamera.posV.z = g_aCamera.posR.z + cosf(g_aCamera.rot.y)* MAX_POSV_Z;
		}

	//視点左回転
	if (GetKeyboardPress(DIK_C) == true)
	{
		//視点πの制限
		if (g_aCamera.rot.y <-D3DX_PI)
		{
			g_aCamera.rot.y += D3DX_PI * 2.0f;
		}
		//視点移動
		g_aCamera.rot.y -= 0.03f;
		g_aCamera.posV.x = g_aCamera.posR.x - sinf(g_aCamera.rot.y)* MAX_POSV_Z;
		g_aCamera.posV.z = g_aCamera.posR.z + cosf(g_aCamera.rot.y)* MAX_POSV_Z;
	}

	//カメラの移動
	g_aCamera.posV.x = pPlayer->pos.x ;
	g_aCamera.posV.z = pPlayer->pos.z ;
	g_aCamera.posV.y = pPlayer->pos.y ;

	//カメラの移動
	g_aCamera.posV.x = g_aCamera.posR.x - sinf(g_aCamera.rot.y)* MAX_POSV_Z;
	g_aCamera.posV.z = g_aCamera.posR.z - cosf(g_aCamera.rot.y)* MAX_POSV_Z;
	g_aCamera.posV.y = g_aCamera.posR.y + 300;
}


//-------------------------------------------------------------------------------
//設定処理
//-------------------------------------------------------------------------------
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	 //デバイスの取得
	pDevice = GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_aCamera.mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_aCamera.mtxProjection, D3DXToRadian(45.0f),
								(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 1000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_aCamera.mtxProjection);

	//ビューマトリックスを作成
	D3DXMatrixLookAtLH (&g_aCamera.mtxView, &g_aCamera.posV,
						&g_aCamera.posR, &g_aCamera.posU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_aCamera.mtxView);
}

//-------------------------------------------------------------------------------
//カメラの情報
//-------------------------------------------------------------------------------
CAMERA*GetCamera(void)
{
	return &g_aCamera;
}