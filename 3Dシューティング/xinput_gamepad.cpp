//--------------------------------------------------------------------------------
//
// ゲーム制作[input.cpp]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#include "xinput_gamepad.h"	//Controllerの詳細
#include "player.h"			//プレイヤーの詳細
#include"Model.h"			//モデルの情報
#include"bullet.h"			//弾の詳細
#include "camera.h"			//カメラの詳細

//--------------------------------------------------------------------------------
//グローバル変数
//-------------------------------------------------------------------------------
XINPUT_STATE g_state;
XinputGamepad  g_XinputGamepad;
bool g_Bullet = false;

//--------------------------------------------------------------------------------
//ゲームパッドの読み込み
//--------------------------------------------------------------------------------
void RoadGamePad(void)
{

	ZeroMemory(&g_state, sizeof(XINPUT_STATE));

	// Simply get the state of the controller from XInput.
	DWORD dwResult = XInputGetState(0, &g_state);

	if (dwResult == ERROR_SUCCESS)
	{// ボタンが押されたかどうか
		XinputButtons();

		// スティックを倒したら
		XinputSticks();
	}
	else
	{
		// Controller is not connected
	}
}

//--------------------------------------------------------------------------------
//ボタン情報
//--------------------------------------------------------------------------------
void XinputButtons(void)
{
	//変数宣言
	Player*pPlayer = GetPlayer();
	CAMERA*pCamera = GetCamera();
	BULLET*pBullet = GetBullet();
	MODEL*pModel = GetModel();

	int nLife = 50;
	int nCntBullet = 0;
	int nCntShot = 0;
	int nCnt = 0;
	bool bBullet = false;
	bool bBoolAttack = false;

	//弾の発射
	if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
	{
		bBullet = true;

		if (bBullet != g_Bullet)
		{
			
				SetBullet(D3DXVECTOR3(pPlayer->pos.x /** sinf(pPlayer->rot.y)*/, pPlayer->aModel[0].pos.y + 20, pPlayer->pos.z /** cosf(pPlayer->rot.y)*/),
					D3DXVECTOR3(sinf(pPlayer->rot.y) * -10.0f, 0.0f, cosf(pPlayer->rot.y) * -10.0f),
					BULLETSTATE_PLAYER, nLife, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

				g_XinputGamepad.bAButton = true;
			
		}
		else
		{
			g_XinputGamepad.bAButton = false;
		}
	
	}
	
	//上移動
	if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
	{
		//十字上ボタンが押された
		//移動量
		pPlayer->move.x += 1.5f*sinf(pCamera->rot.y);
		pPlayer->move.z += 1.5f*cosf(pCamera->rot.y);

		//向き
		pPlayer->rot.y = pCamera->rot.y - D3DX_PI;
	}
	
	//下移動
	if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
	{
		//十字下ボタンが押された
		//移動量
		pPlayer->move.x -= 1.5f*sinf(pCamera->rot.y);
		pPlayer->move.z -= 1.5f*cosf(pCamera->rot.y);

		//向き
		pPlayer->rot.y = pCamera->rot.y;
	}
	
	//右移動
	if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
	{
		//十字右ボタンが押された
		//移動量
		pPlayer->move.x += 1.5f*cosf(pCamera->rot.y);
		pPlayer->move.z -= 1.5f*sinf(pCamera->rot.y);

		//向き
		pPlayer->rot.y = pCamera->rot.y + D3DX_PI * 1.5f;
	}
	
	//左移動
	if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
	{
		//十字左ボタンが押された
		//移動量
		pPlayer->move.x -= 1.5f*cosf(pCamera->rot.y);
		pPlayer->move.z += 1.5f*sinf(pCamera->rot.y);

		//向き
		pPlayer->rot.y = pCamera->rot.y - D3DX_PI * 1.5f;
	}

	//視点右回転
	if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
	{
		//視点πの制限
		if (pCamera->rot.y > D3DX_PI)
		{
			pCamera->rot.y -= D3DX_PI * 2.0f;
		}

		//視点移動
		pCamera->rot.y -= 0.03f;
		pCamera->posV.x = pCamera->posR.x - sinf(pCamera->rot.y)* MAX_POSV_Z;
		pCamera->posV.z = pCamera->posR.z + cosf(pCamera->rot.y)* MAX_POSV_Z;

	}

	//視点左回転
	if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
	{
		//視点πの制限
		if (pCamera->rot.y <-D3DX_PI)
		{
			pCamera->rot.y += D3DX_PI * 2.0f;
		}

		//視点移動
		pCamera->rot.y += 0.03f;
		pCamera->posV.x = pCamera->posR.x - sinf(pCamera->rot.y)* MAX_POSV_Z;
		pCamera->posV.z = pCamera->posR.z + cosf(pCamera->rot.y)* MAX_POSV_Z;
	}
	g_Bullet = bBullet;
}

//--------------------------------------------------------------------------------
//スティック情報
//--------------------------------------------------------------------------------
void XinputSticks(void)
{

	Player*pPlayer = GetPlayer();
	CAMERA*pCamera = GetCamera();

	//デッドゾーンの入力
	if ((g_state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		g_state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(g_state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			g_state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		g_state.Gamepad.sThumbLX = 0;
		g_state.Gamepad.sThumbLY = 0;
	}
	//JOYPADのスティック入力
	if (g_state.Gamepad.sThumbLX != 0 || g_state.Gamepad.sThumbLY != 0)
	{//スティックの入力角度
		g_XinputGamepad.fAngle = atan2f((float)g_state.Gamepad.sThumbLX, (float)g_state.Gamepad.sThumbLY*-1);
		
		//スティックの入力を伝える
		g_XinputGamepad.bPressLStick = true;

		pPlayer->move.x -= 0.4f*sinf(pCamera->rot.y - g_XinputGamepad.fAngle);
		pPlayer->move.z -= 0.4f*cosf(pCamera->rot.y - g_XinputGamepad.fAngle);

		if(g_state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			pPlayer->move.x -= 0.6f*sinf(pCamera->rot.y - g_XinputGamepad.fAngle);
			pPlayer->move.z -= 0.6f*cosf(pCamera->rot.y - g_XinputGamepad.fAngle);
		}

		//向き
		pPlayer->rot.y = pCamera->rot.y - g_XinputGamepad.fAngle;
	}
}

XinputGamepad*GetXinputGamepad(void)
{
	return &g_XinputGamepad;
}