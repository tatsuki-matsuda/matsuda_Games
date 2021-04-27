//-------------------------------------------------------------------------------
//
// �Q�[������[polygon.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include "fade.h"

//-------------------------------------------------------------------------------
//�}�N����`
//-------------------------------------------------------------------------------
#define MOVE_ALPHA  (0.1f)	//���l�̍ŏ�

//-------------------------------------------------------------------------------
//�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;			//�e�N�X�`�����
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;		//���_�o�b�t�@�ւ̃|�C���^
FADE g_fade;			//�t�F�[�h�̏��
MODE g_modeNext;		//���̃��[�h
D3DXCOLOR g_colorFade;	//�t�F�[�h�F

//-------------------------------------------------------------------------------
//����������
//-------------------------------------------------------------------------------
HRESULT InitFade(MODE modeNext)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	VERTEX_2D*pVtx;

	//���
	g_fade = FADE_IN;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(0, 960, 0.0);		//�����̍��W
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0);		//����̍��W
	pVtx[2].pos = D3DXVECTOR3(1280, 960, 0.0);	//�E���̍��W
	pVtx[3].pos = D3DXVECTOR3(1280, 0, 0.0);	//�E��̍��W
									
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
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFade->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//�I������
//-------------------------------------------------------------------------------
void UninitFade(void)
{//���_�o�b�t�@�̊J��
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}
}

//-------------------------------------------------------------------------------
//�X�V����
//-------------------------------------------------------------------------------
void UpdateFade(void)
{
	//�ϐ��錾
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFade->Unlock();
	if (g_fade == FADE_IN)
	{//�t�F�[�h�C��
		g_colorFade.a -= MOVE_ALPHA;
		if (g_colorFade.a <= 0.0f)
		{
			g_fade = FADE_NONE;
		}
	}
	else if (g_fade == FADE_OUT)
	{//�t�F�[�h�A�E�g
		g_colorFade.a += MOVE_ALPHA;
		if (g_colorFade.a >= 1.0f)
		{
			g_fade = FADE_IN;
			SetMode(g_modeNext);
		}
	}
}

//-------------------------------------------------------------------------------
//�`�揈��
//-------------------------------------------------------------------------------
void DrawFade(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureFade);

	//�w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//-------------------------------------------------------------------------------
//�t�F�[�h�ݒ�
//-------------------------------------------------------------------------------
void SetFade(FADE fade, MODE modeNext)
{
	//���
	g_fade = fade;
	g_modeNext = modeNext;
}

//-------------------------------------------------------------------------------
//�t�F�[�h���̎擾
//-------------------------------------------------------------------------------
FADE GetFade(void)
{
	return g_fade;
}