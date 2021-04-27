//-------------------------------------------------------------------------------
//
// �Q�[������[title.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include "title.h"
#include "input.h"
#include "fade.h"
#include "xinput_gamepad.h"	//�R���g���[���[�̏ڍ�
//#include "sound.h"

//-------------------------------------------------------------------------------
//�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureTitle[2] = {};			//�e�N�X�`�����
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posPressEnter;						// �G���^�[�̒��S���W
D3DXCOLOR g_LogoCol;								// �F	
int g_nCnt;
bool g_PressOK;										// �L�[����������
int g_nCntFlash;									// �J�E���g
float g_posY;

//-------------------------------------------------------------------------------
//����������
//-------------------------------------------------------------------------------
HRESULT InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	g_nCnt = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_posPressEnter = D3DXVECTOR3(SCREEN_WIDTH / 2, 450.0f, 0.0f);
	g_posY = 0.0f;
	g_LogoCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_PressOK = false;
	g_nCntFlash = 0;

	//�ϐ��錾
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * 3 ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle, NULL)))
	{
		return E_FAIL;
	}


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\title001.png", &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\TitleName001.png", &g_pTextureTitle[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\PressEnter.png", &g_pTextureTitle[2]);

	for (int nCntTitle = 0; nCntTitle < 2; nCntTitle++)
	{
		switch (nCntTitle)
		{
		case 0:
			pVtx[0].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);				//�����̍��W
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//����̍��W
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);		//�E���̍��W
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);				//�E��̍��W
			break;

		case 1:
			pVtx[0].pos = D3DXVECTOR3(150.0f, SCREEN_HEIGHT, 0.0f);			//�����̍��W
			pVtx[1].pos = D3DXVECTOR3(150.0f, 0.0f, 0.0f);					//����̍��W
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);	//�E���̍��W
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);			//�E��̍��W

		//case 2:
		//	pVtx[0].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);			//�����̍��W
		//	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//����̍��W
		//	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);	//�E���̍��W
		//	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);			//�E��̍��W

		default:
			break;
		}

		//���_���W
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

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//�I������
//-------------------------------------------------------------------------------
void UninitTitle(void)
{//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	for (int nCntTitle = 0; nCntTitle < 2; nCntTitle++)
	{
		//�e�N�X�`���̊J��
		if (g_pTextureTitle[nCntTitle] != NULL)
		{
			g_pTextureTitle[nCntTitle]->Release();
			g_pTextureTitle[nCntTitle] = NULL;
		}
	}

	////���y���I��
	//StopSound();
}

//-------------------------------------------------------------------------------
//�X�V����
//-------------------------------------------------------------------------------
void UpdateTitle(void)
{
	XinputGamepad*pXinputGamepad = GetXinputGamepad();

	bool bTitleOK = false;

	if (bTitleOK == false)
	{


		// �e���[�h�ɑJ��
		if (pXinputGamepad->bAButton == true)
		{

			bTitleOK = true;

			pXinputGamepad->bAButton = false;

			// �Q�[���ɑJ��
			SetFade(FADE_OUT, MODE_TUTORIAL);

			// �T�E���h
			//PlaySound(SOUND_LABEL_SE_OK);
		}
	}
}
	

//	//else if (g_PressOK == true)
//	//{// �_�ł����邽�߂ɃJ�E���g��i�߂�
//	//	g_nCntFlash++;
//
//	//	if (CLEAR_NUMBER == g_nCntFlash % FLASH_INTERBAL)
//	//	{// ����
//	//		g_LogoCol.a = 0.0f;
//	//	}
//	//	else if (LESS_CLEAR_NUMBER == g_nCntFlash % FLASH_INTERBAL)
//	//	{// �s����
//	//		g_LogoCol.a = 1.0f;
//	//	}
//	//	// �J�E���g��������x�i�񂾂�J��
//	//	if (g_nCntFlash >= 50)
//	//	{
//}
//		//}
//		//// ���_���W�̍X�V
//		//SetVertexTitleLogo(3);
//
//		////��ʑJ��
//		//if (GetKeyboardTrigger(DIK_RETURN) == true)
//		//{
//		//	SetFade(FADE_OUT, MODE_TUTORIAL);
//		//}
//	

//-------------------------------------------------------------------------------
//�`�揈��
//-------------------------------------------------------------------------------
void DrawTitle(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	for (int nCnttitle = 0; nCnttitle < 2; nCnttitle++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[nCnttitle]);

		//�w�i�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnttitle * 4, 2);
	}
}

//-----------------------------------------------------------------
// �^�C�g����ʂɓ\��e�N�X�`���̎w��
//-----------------------------------------------------------------
//void SetVertexTitleLogo(int nCntTitleLogo)
//{
//	// �\���̂̃|�C���^�ϐ�
//	VERTEX_2D *pVtx;
//
//	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
//
//	//	���Ԗڂ�
//	pVtx += nCntTitleLogo * 4;
//
//	//{// ���_���W�̍X�V
//		pVtx[0].pos = D3DXVECTOR3(g_posPressEnter.x - (SELECTENTER_X / 2), g_posPressEnter.y + (SELECTENTER_Y / 2), 0.0f);
//		pVtx[1].pos = D3DXVECTOR3(g_posPressEnter.x - (SELECTENTER_X / 2), g_posPressEnter.y - (SELECTENTER_Y / 2), 0.0f);
//		pVtx[2].pos = D3DXVECTOR3(g_posPressEnter.x + (SELECTENTER_X / 2), g_posPressEnter.y + (SELECTENTER_Y / 2), 0.0f);
//		pVtx[3].pos = D3DXVECTOR3(g_posPressEnter.x + (SELECTENTER_X / 2), g_posPressEnter.y - (SELECTENTER_Y / 2), 0.0f);
//
//	// ���_�J���[�̐ݒ�
//	pVtx[0].col = g_LogoCol;
//	pVtx[1].col = g_LogoCol;
//	pVtx[2].col = g_LogoCol;
//	pVtx[3].col = g_LogoCol;
//
//	// ���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffTitle->Unlock();
//}

