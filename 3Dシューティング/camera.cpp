//-------------------------------------------------------------------------------
//
// �Q�[������[Camera.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include"Camera.h"		//�Q�[�����
#include"player.h"

//-------------------------------------------------------------------------------
//�O���[�o���ϐ�
//-------------------------------------------------------------------------------
CAMERA g_aCamera;	//�J�����̏��

//-------------------------------------------------------------------------------
//����������
//-------------------------------------------------------------------------------
void InitCamera(void)
{
	//�J�����̈ʒu
	g_aCamera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aCamera.posV = D3DXVECTOR3(0.0f, MAX_POSV_Y, MAX_POSV_Z);
	g_aCamera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aCamera.posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//g_aCamera.posR.x = g_aCamera.posV.x +- sinf();
}

//-------------------------------------------------------------------------------
//�I������
//-------------------------------------------------------------------------------
void UninitCamera(void)
{
}

//-------------------------------------------------------------------------------
//�X�V����
//-------------------------------------------------------------------------------
void UpdateCamera(void)
{
	Player*pPlayer = GetPlayer();

	g_aCamera.posR.x = pPlayer->pos.x;
	g_aCamera.posR.z = pPlayer->pos.z;
	g_aCamera.posR.y = pPlayer->pos.y;

	//�����_���]
	if (GetKeyboardPress(DIK_U) == true)
	{
		//�����_�΂̐���
		if (g_aCamera.rot.y > D3DX_PI)
		{
			g_aCamera.rot.y -= D3DX_PI * 2.0f;
		}
		//�����_�ړ�
		g_aCamera.rot.x += 0.03f;
		g_aCamera.posR.y = g_aCamera.posV.y - sinf(g_aCamera.rot.x)* MAX_POSV_Z;
		g_aCamera.posR.z = g_aCamera.posV.z - cosf(g_aCamera.rot.x)* MAX_POSV_Z;
	}

	//�����_����]
	if (GetKeyboardPress(DIK_J) == true)
	{
		//�����_�΂̐���
		if (g_aCamera.rot.y <- D3DX_PI)
		{
			g_aCamera.rot.y -= D3DX_PI * 2.0f;
		}
		//�����_�ړ�
		g_aCamera.rot.x -= 0.1f;
		g_aCamera.posR.y = g_aCamera.posV.y - sinf(g_aCamera.rot.x)* MAX_POSV_Z;
		g_aCamera.posR.z = g_aCamera.posV.z - cosf(g_aCamera.rot.x)* MAX_POSV_Z;
	}

		//���_�E��]
		if (GetKeyboardPress(DIK_Z) == true)
		{
			//���_�΂̐���
			if (g_aCamera.rot.y > D3DX_PI)
			{
				g_aCamera.rot.y -= D3DX_PI * 2.0f;
			}
			//���_�ړ�
			g_aCamera.rot.y += 0.03f;
			g_aCamera.posV.x = g_aCamera.posR.x - sinf(g_aCamera.rot.y)* MAX_POSV_Z;
			g_aCamera.posV.z = g_aCamera.posR.z + cosf(g_aCamera.rot.y)* MAX_POSV_Z;
		}

	//���_����]
	if (GetKeyboardPress(DIK_C) == true)
	{
		//���_�΂̐���
		if (g_aCamera.rot.y <-D3DX_PI)
		{
			g_aCamera.rot.y += D3DX_PI * 2.0f;
		}
		//���_�ړ�
		g_aCamera.rot.y -= 0.03f;
		g_aCamera.posV.x = g_aCamera.posR.x - sinf(g_aCamera.rot.y)* MAX_POSV_Z;
		g_aCamera.posV.z = g_aCamera.posR.z + cosf(g_aCamera.rot.y)* MAX_POSV_Z;
	}

	//�J�����̈ړ�
	g_aCamera.posV.x = pPlayer->pos.x ;
	g_aCamera.posV.z = pPlayer->pos.z ;
	g_aCamera.posV.y = pPlayer->pos.y ;

	//�J�����̈ړ�
	g_aCamera.posV.x = g_aCamera.posR.x - sinf(g_aCamera.rot.y)* MAX_POSV_Z;
	g_aCamera.posV.z = g_aCamera.posR.z - cosf(g_aCamera.rot.y)* MAX_POSV_Z;
	g_aCamera.posV.y = g_aCamera.posR.y + 300;
}


//-------------------------------------------------------------------------------
//�ݒ菈��
//-------------------------------------------------------------------------------
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	 //�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_aCamera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_aCamera.mtxProjection, D3DXToRadian(45.0f),
								(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 1000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_aCamera.mtxProjection);

	//�r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH (&g_aCamera.mtxView, &g_aCamera.posV,
						&g_aCamera.posR, &g_aCamera.posU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_aCamera.mtxView);
}

//-------------------------------------------------------------------------------
//�J�����̏��
//-------------------------------------------------------------------------------
CAMERA*GetCamera(void)
{
	return &g_aCamera;
}