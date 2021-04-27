//--------------------------------------------------------------------------------
//
// �Q�[������[Billboard.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include"billboard.h"		//�r���{�[�h�̉��

//-------------------------------------------------------------------------------
//�O���[�o���ϐ�
//-------------------------------------------------------------------------------
PDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;		//�e�N�X�`�����
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;	//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posBillboard;							//�ʒu
D3DXMATRIX  g_mtxWorldBillboard;					//���[���h�}�g���b�N�X

//-------------------------------------------------------------------------------
//����������
//-------------------------------------------------------------------------------
HRESULT InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_pTextureBillboard);

	//�|���S���̈ʒu�E����
	g_posBillboard = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard, NULL)))
	{
		return E_FAIL;
	}

	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	//���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-5.0f, 5.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(-5.0f, 15.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(5.0f, 5.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(5.0f, 15.0f,0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
	g_pVtxBuffBillboard->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//�I������
//-------------------------------------------------------------------------------
void UninitBillboard(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBillboard != NULL)
	{

		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
}

//-------------------------------------------------------------------------------
//�X�V����
//-------------------------------------------------------------------------------
void UpdateBillboard(void)
{
}

//-------------------------------------------------------------------------------
//�`�揈��
//-------------------------------------------------------------------------------
void DrawBillboard(void)
{

	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans;//�v�Z�p�}�g���b�N�X

	pDevice = GetDevice();

	//�f�o�C�X�̎擾
	pDevice -> GetTransform(D3DTS_VIEW,&mtxView);

	//Z�o�b�t�@�̍X�V�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldBillboard);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&g_mtxWorldBillboard, NULL, &mtxView);	//�t�s������߂�

	g_mtxWorldBillboard._41 = 0.0f;
	g_mtxWorldBillboard._42 = 0.0f;
	g_mtxWorldBillboard._43 = 0.0f;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posBillboard.x, g_posBillboard.y, g_posBillboard.z);
	D3DXMatrixMultiply(&g_mtxWorldBillboard, &g_mtxWorldBillboard, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBillboard);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//Z�o�b�t�@�̍X�V��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
