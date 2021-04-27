//-------------------------------------------------------------------------------
//
// �Q�[������[Polygon.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include"Polygon.h"		//�Q�[�����

//-------------------------------------------------------------------------------
//�O���[�o���ϐ�
//-------------------------------------------------------------------------------
PDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;		//�e�N�X�`�����
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;	//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posPolygon;			//�ʒu
D3DXVECTOR3 g_rotPolygon;			//����
D3DXMATRIX  g_mtxWorldPolygon;		//���[���h�}�g���b�N�X
//MODE g_stage = MODE_STAGE1;	//�X�e�[�W�̃��[�h

//-------------------------------------------------------------------------------
//����������
//-------------------------------------------------------------------------------
HRESULT InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\field002.jpg", &g_pTexturePolygon);

	//�|���S���̈ʒu�E����
	g_posPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon, NULL)))
	{
		return E_FAIL;
	}

	//���_���ւ̃|�C���^
		VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

		//if (Mode = MODE_STAGE1)
		//{
		//	//�v���C���[�X�e�[�W1�̕`�揈��
		//	g_aPolygon[0].pos = D3DXVECTOR3(SCREEN_WIDTH, 650.0f, 0.0f);
		//}

		//if (Mode = MODE_STAGE2)
		//{
		//	//�v���C���[�X�e�[�W2�̕`�揈��
		//	g_aPolygon[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 80, 100.0f, 0.0f);
		//}


		/*g_aPolygon[0].pos = D3DXVECTOR3(SCREEN_WIDTH, 650.0f, 0.0f);*/

		//���_���̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-50.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-50.0f, 0.0f, -100.0f);
		pVtx[3].pos = D3DXVECTOR3(50.0f, 0.0f, -100.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f );
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f );
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f );
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f );

		//���_���W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPolygon->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//�I������
//-------------------------------------------------------------------------------
void UninitPolygon(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffPolygon != NULL)
	{

		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon->Release();
		g_pTexturePolygon = NULL;
	}
}

//-------------------------------------------------------------------------------
//�X�V����
//-------------------------------------------------------------------------------
void UpdatePolygon(void)
{


}

//-------------------------------------------------------------------------------
//�`�揈��
//-------------------------------------------------------------------------------
void DrawPolygon(void)
{

	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	 //�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldPolygon);

	//�����𔽉f����
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotPolygon.y, g_rotPolygon.x, g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_rotPolygon.x, g_rotPolygon.y, g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolygon);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0,g_pVtxBuffPolygon,0,sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePolygon);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
