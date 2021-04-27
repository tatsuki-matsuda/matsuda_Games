//--------------------------------------------------------------------------------
//
// �Q�[������[input.cpp]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#include "xinput_gamepad.h"	//Controller�̏ڍ�
#include "player.h"			//�v���C���[�̏ڍ�
#include"Model.h"			//���f���̏��
#include"bullet.h"			//�e�̏ڍ�
#include "camera.h"			//�J�����̏ڍ�

//--------------------------------------------------------------------------------
//�O���[�o���ϐ�
//-------------------------------------------------------------------------------
XINPUT_STATE g_state;
XinputGamepad  g_XinputGamepad;
bool g_Bullet = false;

//--------------------------------------------------------------------------------
//�Q�[���p�b�h�̓ǂݍ���
//--------------------------------------------------------------------------------
void RoadGamePad(void)
{

	ZeroMemory(&g_state, sizeof(XINPUT_STATE));

	// Simply get the state of the controller from XInput.
	DWORD dwResult = XInputGetState(0, &g_state);

	if (dwResult == ERROR_SUCCESS)
	{// �{�^���������ꂽ���ǂ���
		XinputButtons();

		// �X�e�B�b�N��|������
		XinputSticks();
	}
	else
	{
		// Controller is not connected
	}
}

//--------------------------------------------------------------------------------
//�{�^�����
//--------------------------------------------------------------------------------
void XinputButtons(void)
{
	//�ϐ��錾
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

	//�e�̔���
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
	
	//��ړ�
	if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
	{
		//�\����{�^���������ꂽ
		//�ړ���
		pPlayer->move.x += 1.5f*sinf(pCamera->rot.y);
		pPlayer->move.z += 1.5f*cosf(pCamera->rot.y);

		//����
		pPlayer->rot.y = pCamera->rot.y - D3DX_PI;
	}
	
	//���ړ�
	if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
	{
		//�\�����{�^���������ꂽ
		//�ړ���
		pPlayer->move.x -= 1.5f*sinf(pCamera->rot.y);
		pPlayer->move.z -= 1.5f*cosf(pCamera->rot.y);

		//����
		pPlayer->rot.y = pCamera->rot.y;
	}
	
	//�E�ړ�
	if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
	{
		//�\���E�{�^���������ꂽ
		//�ړ���
		pPlayer->move.x += 1.5f*cosf(pCamera->rot.y);
		pPlayer->move.z -= 1.5f*sinf(pCamera->rot.y);

		//����
		pPlayer->rot.y = pCamera->rot.y + D3DX_PI * 1.5f;
	}
	
	//���ړ�
	if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
	{
		//�\�����{�^���������ꂽ
		//�ړ���
		pPlayer->move.x -= 1.5f*cosf(pCamera->rot.y);
		pPlayer->move.z += 1.5f*sinf(pCamera->rot.y);

		//����
		pPlayer->rot.y = pCamera->rot.y - D3DX_PI * 1.5f;
	}

	//���_�E��]
	if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
	{
		//���_�΂̐���
		if (pCamera->rot.y > D3DX_PI)
		{
			pCamera->rot.y -= D3DX_PI * 2.0f;
		}

		//���_�ړ�
		pCamera->rot.y -= 0.03f;
		pCamera->posV.x = pCamera->posR.x - sinf(pCamera->rot.y)* MAX_POSV_Z;
		pCamera->posV.z = pCamera->posR.z + cosf(pCamera->rot.y)* MAX_POSV_Z;

	}

	//���_����]
	if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
	{
		//���_�΂̐���
		if (pCamera->rot.y <-D3DX_PI)
		{
			pCamera->rot.y += D3DX_PI * 2.0f;
		}

		//���_�ړ�
		pCamera->rot.y += 0.03f;
		pCamera->posV.x = pCamera->posR.x - sinf(pCamera->rot.y)* MAX_POSV_Z;
		pCamera->posV.z = pCamera->posR.z + cosf(pCamera->rot.y)* MAX_POSV_Z;
	}
	g_Bullet = bBullet;
}

//--------------------------------------------------------------------------------
//�X�e�B�b�N���
//--------------------------------------------------------------------------------
void XinputSticks(void)
{

	Player*pPlayer = GetPlayer();
	CAMERA*pCamera = GetCamera();

	//�f�b�h�]�[���̓���
	if ((g_state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		g_state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(g_state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			g_state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		g_state.Gamepad.sThumbLX = 0;
		g_state.Gamepad.sThumbLY = 0;
	}
	//JOYPAD�̃X�e�B�b�N����
	if (g_state.Gamepad.sThumbLX != 0 || g_state.Gamepad.sThumbLY != 0)
	{//�X�e�B�b�N�̓��͊p�x
		g_XinputGamepad.fAngle = atan2f((float)g_state.Gamepad.sThumbLX, (float)g_state.Gamepad.sThumbLY*-1);
		
		//�X�e�B�b�N�̓��͂�`����
		g_XinputGamepad.bPressLStick = true;

		pPlayer->move.x -= 0.4f*sinf(pCamera->rot.y - g_XinputGamepad.fAngle);
		pPlayer->move.z -= 0.4f*cosf(pCamera->rot.y - g_XinputGamepad.fAngle);

		if(g_state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			pPlayer->move.x -= 0.6f*sinf(pCamera->rot.y - g_XinputGamepad.fAngle);
			pPlayer->move.z -= 0.6f*cosf(pCamera->rot.y - g_XinputGamepad.fAngle);
		}

		//����
		pPlayer->rot.y = pCamera->rot.y - g_XinputGamepad.fAngle;
	}
}

XinputGamepad*GetXinputGamepad(void)
{
	return &g_XinputGamepad;
}