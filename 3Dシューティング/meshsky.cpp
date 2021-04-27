//-------------------------------------------------------------------------------
//
// �Q�[������[MeshSky.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include"Meshsky.h"		//���b�V���t�B�[���h�̕\��

//-------------------------------------------------------------------------------
//�O���[�o���ϐ�
//-------------------------------------------------------------------------------
PDIRECT3DTEXTURE9 g_pTextureMeshSky = NULL;		//�e�N�X�`�����
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshSky = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9	g_pIdxBuffMeshSky = NULL;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posMeshSky;			//�ʒu
D3DXVECTOR3 g_rotMeshSky;			//����
D3DXMATRIX  g_mtxWorldMeshSky;	//���[���h�}�g���b�N�X
									//MeshSky g_aMeshFeild[256];

//-------------------------------------------------------------------------------
//����������
//-------------------------------------------------------------------------------
HRESULT InitMeshSky(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\sky.jpg", &g_pTextureMeshSky);

	//�|���S���̈ʒu�E����
	g_posMeshSky = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshSky = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 17,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshSky, NULL)))
	{
		return E_FAIL;
	}

	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshSky->Lock(0, 0, (void**)&pVtx, 0);

	/*g_aMeshSky[0].pos = D3DXVECTOR3(SCREEN_WIDTH, 650.0f, 0.0f);*/

		//���_���̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 100.0f, -700.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 100.0f, -650.0f);
		pVtx[2].pos = D3DXVECTOR3(3.0f, 100.0f, -600.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 50.0f, -700.0f);
		pVtx[4].pos = D3DXVECTOR3(10.0f, 50.0f, -650.0f);
		pVtx[5].pos = D3DXVECTOR3(3.0f, 50.0f, -600.0f);
		pVtx[6].pos = D3DXVECTOR3(0.0f, 0.0f, -700.0f);
		pVtx[7].pos = D3DXVECTOR3(10.0f, 0.0f, -650.0f);
		pVtx[8].pos = D3DXVECTOR3(3.0f, 0.0f, -600.0f);

		pVtx[9].pos = D3DXVECTOR3(0.0f, 100.0f, -550.0f);
		pVtx[10].pos = D3DXVECTOR3(10.0f, 100.0f, -500.0f);
		pVtx[11].pos = D3DXVECTOR3(3.0f, 100.0f, -550.0f);
		pVtx[12].pos = D3DXVECTOR3(0.0f, 50.0f, -550.0f);
		pVtx[13].pos = D3DXVECTOR3(10.0f, 50.0f, -500.0f);
		pVtx[14].pos = D3DXVECTOR3(3.0f, 50.0f, -550.0f);
		pVtx[15].pos = D3DXVECTOR3(0.0f, 0.0f, -550.0f);
		pVtx[16].pos = D3DXVECTOR3(10.0f, 0.0f, -500.0f);
		pVtx[17].pos = D3DXVECTOR3(3.0f, 0.0f, -550.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[9].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[10].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[11].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[12].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[13].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[14].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[15].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[16].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[17].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_���W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
		pVtx[5].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVtx[6].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 0.5f);
		pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx[9].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[11].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[12].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[13].tex = D3DXVECTOR2(0.5f, 0.5f);
		pVtx[14].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVtx[15].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[16].tex = D3DXVECTOR2(1.0f, 0.5f);
		pVtx[17].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshSky->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * 28, D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, D3DPOOL_MANAGED,
		&g_pIdxBuffMeshSky, NULL);

	WORD*pIdx;	//�C���f�b�N�X���ւ̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshSky->Lock(0, 0, (void**)&pIdx, 0);

	//�ԍ��f�[�^�̐ݒ�
	pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;

	pIdx[14] = 12;
	pIdx[15] = 9;
	pIdx[16] = 13;
	pIdx[17] = 10;
	pIdx[18] = 14;
	pIdx[19] = 11;
	pIdx[20] = 11;
	pIdx[21] = 15;
	pIdx[22] = 15;
	pIdx[23] = 12;
	pIdx[24] = 16;
	pIdx[25] = 13;
	pIdx[26] = 17;
	pIdx[27] = 14;

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshSky->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//�I������
//-------------------------------------------------------------------------------
void UninitMeshSky(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffMeshSky != NULL)
	{
		g_pVtxBuffMeshSky->Release();
		g_pVtxBuffMeshSky = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTextureMeshSky != NULL)
	{
		g_pTextureMeshSky->Release();
		g_pTextureMeshSky = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshSky != NULL)
	{
		g_pIdxBuffMeshSky->Release();
		g_pIdxBuffMeshSky = NULL;
	}
}

//-------------------------------------------------------------------------------
//�X�V����
//-------------------------------------------------------------------------------
void UpdateMeshSky(void)
{
	////�f�o�C�X�̎擾
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	////���_���ւ̃|�C���^
	//VERTEX_3D*pVtx;

	//for (int nCntMeshFeild = 0; nCntMeshFeild < 28; nCntMeshFeild++)
	//{
	//	if (GetKeyboardPress(DIK_RETURN) == true)
	//	{
	//		g_MeshSky[nCntMeshFeild] -= D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	//	}
	//}
}

//-------------------------------------------------------------------------------
//�`�揈��
//-------------------------------------------------------------------------------
void DrawMeshSky(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

								//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshSky);

	//�����𔽉f����
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshSky.y, g_rotMeshSky.x, g_rotMeshSky.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshSky, &g_mtxWorldMeshSky, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_rotMeshSky.x, g_rotMeshSky.y, g_rotMeshSky.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshSky, &g_mtxWorldMeshSky, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshSky);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshSky, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshSky);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshSky);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 17, 0, 28);
}

//MeshSky*GetMeshSky(void)
//{
//	return &g_aMeshFeild;
//}
