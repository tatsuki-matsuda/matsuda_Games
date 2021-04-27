//-------------------------------------------------------------------------------
//
// �Q�[������[Model.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include"Model.h"		//�Q�[�����
#include"bullet.h"		//�e�̏ڍ�

//-------------------------------------------------------------------------------
//�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3D9 g_apTextureModel[100] = {};	//�e�N�X�`���ւ̃|�C���^
LPD3DXMESH g_pMeshModel = NULL;			//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel = NULL;	//�}�e���A��(�ގ����)�ւ̃|�C���^
D3DXVECTOR3 g_posModel;					//�ʒu
D3DXVECTOR3 g_rotModel;					//����
D3DXMATRIX  g_mtxWorldModel;			//���[���h�}�g���b�N�X
DWORD g_nNumMatModel;					//�}�e���A���̐�
MODEL g_aModel;							//���f��

//-------------------------------------------------------------------------------
//����������
//-------------------------------------------------------------------------------
void InitModel(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\field002.jpg", &g_pTextureModel);

	//x�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\car000.x", D3DXMESH_SYSTEMMEM, pDevice,
						NULL, &g_pBuffMatModel, NULL, 
						&g_nNumMatModel,&g_pMeshModel);

	D3DXMATERIAL*pMat;

	//�}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				pMat[1].pTextureFilename = "data\\TEXTURE\\eye.jpg";
			}
		}

	//�|���S���̈ʒu�E�����̏����ݒ�
	g_posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

//-------------------------------------------------------------------------------
//�I������
//-------------------------------------------------------------------------------
void UninitModel(void)
{
	//���b�V���̔j��
	if (g_pMeshModel!= NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}

//-------------------------------------------------------------------------------
//�X�V����
//-------------------------------------------------------------------------------
void UpdateModel(void)
{
	////�ϐ��錾
	//BULLET*pBullet;
	//int nLife = 50;
	//int nCntBullet = 0;
	//int nCntShot = 0;
	//int nCnt = 0;

	//pBullet = GetBullet();

	//nCntShot++;

	////�e�̔���
	//if (GetKeyboardPress(DIK_SPACE) == true && nCntShot % 2 == 0)
	//{
	//	SetBullet(g_posModel, D3DXVECTOR3(sinf(g_rotModel.y), 0.0f, cosf(g_rotModel.y)), nLife, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//	nCntBullet++;
	//	

	//	if (nCntBullet >= 50 )
	//	{
	//		nCnt++;

	//		if (nCnt >= 2)
	//		{
	//			pBullet->bUse = false;
	//			nCntBullet = 0;
	//			nCnt = 0;
	//			nCntShot = 0;
	//		}
	//	}
	//}

	////��ړ�
	//if (GetKeyboardPress(DIK_UP) == true)
	//{
	//	g_posModel.z += 1.5f;
	//}

	////���ړ�
	//if (GetKeyboardPress(DIK_DOWN) == true)
	//{
	//	g_posModel.z -= 1.5f;
	//}

	////�E�ړ�
	//if (GetKeyboardPress(DIK_RIGHT) == true)
	//{
	//	g_posModel.x += 1.5f;
	//}

	////���f���E��]
	//if (GetKeyboardPress(DIK_RSHIFT) == true)
	//{
	//	//��]�΂̐���
	//	if (g_rotModel.y < -D3DX_PI)
	//	{
	//		g_rotModel.y += D3DX_PI * 2.0f;
	//	}

	//	//��]
	//	g_rotModel.y -= 0.1f;
	//}

	////���ړ�
	//if (GetKeyboardPress(DIK_LEFT) == true)
	//{
	//	g_posModel.x -= 1.5f;
	//}

	//if (GetKeyboardPress(DIK_LSHIFT) == true)
	//{
	//	//��]�΂̐���
	//	if (g_rotModel.y > D3DX_PI)
	//	{
	//		g_rotModel.y += D3DX_PI * 2.0f;
	//	}

	//	//��]
	//	g_rotModel.y += 0.1f;
	//}

}

//-------------------------------------------------------------------------------
//�`�揈��
//-------------------------------------------------------------------------------
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A�����g�p
	D3DXMATERIAL*pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	pDevice = GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		//�}�e���A����ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		//���f��(�p�[�c)�̕`��
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����Ԃ�
	pDevice->SetMaterial(&matDef);
}

MODEL*GetModel(void)
{
	return &g_aModel;
}
