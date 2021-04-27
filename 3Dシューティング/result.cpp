//-------------------------------------------------------------------------------
//
// �Q�[������[result.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include "result.h"
#include "input.h"	
#include "fade.h"	
#include "xinput_gamepad.h"	//�R���g���[���[�̏ڍ�

//-------------------------------------------------------------------------------
//�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;			//�e�N�X�`�����
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	//���_�o�b�t�@�ւ̃|�C���^

//-------------------------------------------------------------------------------
//����������
//-------------------------------------------------------------------------------
HRESULT InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�ϐ��錾
	VERTEX_2D*pVtx;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\result.png", &g_pTextureResult);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);				//�����̍��W
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//����̍��W
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);		//�E���̍��W
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);				//�E��̍��W

	//���_���
	pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//�I������
//-------------------------------------------------------------------------------
void UninitResult(void)
{//���_�o�b�t�@�̊J��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}
}

//-------------------------------------------------------------------------------
//�X�V����
//-------------------------------------------------------------------------------
void UpdateResult(void)
{
	XinputGamepad*pXinputGamepad = GetXinputGamepad();

	bool bResultOK = false;

	if (bResultOK==false)
	{

		if (pXinputGamepad->bAButton == true)
		{

			bResultOK = true;

			//RETURNKey���������ꍇ
			SetFade(FADE_OUT, MODE_TITLE);


			pXinputGamepad->bAButton = false;

		}
	}
}

//-------------------------------------------------------------------------------
//�`�揈��
//-------------------------------------------------------------------------------
void DrawResult(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResult);

	//�w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}