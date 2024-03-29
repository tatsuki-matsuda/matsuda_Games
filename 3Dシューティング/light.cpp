//-------------------------------------------------------------------------------
//
// ゲーム制作[Camera.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include"Camera.h"		//ゲーム画面

//-------------------------------------------------------------------------------
//グローバル変数
//-------------------------------------------------------------------------------
D3DLIGHT9 g_aLight[3];	//カメラの情報

//-------------------------------------------------------------------------------
//初期化処理
//-------------------------------------------------------------------------------
HRESULT InitLight(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスへのポインタ
	D3DXVECTOR3	VecDir;							//設定用方向ベクトル

	//ライトをクリアする
	ZeroMemory(&g_aLight, sizeof(D3DLIGHT9));

	for (int nCntLight = 0; nCntLight < 3; nCntLight++)
	{
		//ライトの種類を設定
		g_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		//ライトの拡散光を設定
		g_aLight[nCntLight].Diffuse = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

		//ライトの方向を設定
		VecDir = D3DXVECTOR3(0.2f, 0.0f, -0.9f);
		VecDir = D3DXVECTOR3(0.2f, -0.8f, 0.7f);
		//VecDir = D3DXVECTOR3(0.2f, 0.0f, 0.7f);

		D3DXVec3Normalize(&VecDir, &VecDir);
		g_aLight[nCntLight].Direction = VecDir;

		//リライトを設定する
		pDevice->SetLight(nCntLight, &g_aLight[nCntLight]);

		//ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}

	return S_OK;
}

//-------------------------------------------------------------------------------
//終了処理
//-------------------------------------------------------------------------------
void UninitLight(void)
{
}

//-------------------------------------------------------------------------------
//更新処理
//-------------------------------------------------------------------------------
void UpdateLight(void)
{
}


//-------------------------------------------------------------------------------
//設定処理
//-------------------------------------------------------------------------------
void SetLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();
}
