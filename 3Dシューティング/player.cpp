//-------------------------------------------------------------------------------
//
// �Q�[������[player.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include <stdio.h>
#include"player.h"			//�v���C���[�̏ڍ�
#include"bullet.h"			//�e�̏ڍ�
#include"Camera.h"			//�J�����̏ڍ�
#include"xinput_gamepad.h"	//X�Q�[���p�b�h�̏ڍ�

#define DEBUG (1)

//-------------------------------------------------------------------------------
//�O���[�o���ϐ�
//-------------------------------------------------------------------------------
Model g_Model;								//���f���̏��
Player g_player;							//�v���C���[�̏��
D3DXVECTOR3 g_aPos[2];						//�����̒��_
D3DXVECTOR3 vecA;							//�v���C���[�Ɣ���̒��_�̋���
D3DXVECTOR3 vecB;							//����̒��_���m�̋���

//-------------------------------------------------------------------------------
//����������
//-------------------------------------------------------------------------------
HRESULT InitPlayer(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���f�����̑�����ݒ�
	g_player.nNumModel = 14;

	//x�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\bodyup.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[0].BuffMatModel, NULL,
		&g_player.aModel[0].nNumMat, &g_player.aModel[0].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\face.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[1].BuffMatModel, NULL,
		&g_player.aModel[1].nNumMat, &g_player.aModel[1].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\armRup.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[2].BuffMatModel, NULL,
		&g_player.aModel[2].nNumMat, &g_player.aModel[2].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\armRdown.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[3].BuffMatModel, NULL,
		&g_player.aModel[3].nNumMat, &g_player.aModel[3].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\handR.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[4].BuffMatModel, NULL,
		&g_player.aModel[4].nNumMat, &g_player.aModel[4].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\armLup.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[5].BuffMatModel, NULL,
		&g_player.aModel[5].nNumMat, &g_player.aModel[5].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\armLdown.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[6].BuffMatModel, NULL,
		&g_player.aModel[6].nNumMat, &g_player.aModel[6].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\handL.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[7].BuffMatModel, NULL,
		&g_player.aModel[7].nNumMat, &g_player.aModel[7].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\regRup.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[8].BuffMatModel, NULL,
		&g_player.aModel[8].nNumMat, &g_player.aModel[8].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\regRdown.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[9].BuffMatModel, NULL,
		&g_player.aModel[9].nNumMat, &g_player.aModel[9].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\regR.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[10].BuffMatModel, NULL,
		&g_player.aModel[10].nNumMat, &g_player.aModel[10].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\regLup.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[11].BuffMatModel, NULL,
		&g_player.aModel[11].nNumMat, &g_player.aModel[11].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\regLdown.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[12].BuffMatModel, NULL,
		&g_player.aModel[12].nNumMat, &g_player.aModel[12].MeshModel);

	D3DXLoadMeshFromX("data\\MODEL\\regL.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &g_player.aModel[13].BuffMatModel, NULL,
		&g_player.aModel[13].nNumMat, &g_player.aModel[13].MeshModel);

	//�e�p�[�c�̊K�w�\���ݒ�
	g_player.aModel[0].nIdxModelParent = -1;
	g_player.aModel[0].pos = D3DXVECTOR3(0.0, 45.0, 0.0);
	g_player.aModel[0].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[1].nIdxModelParent = 0;
	g_player.aModel[1].pos = D3DXVECTOR3(0.0, 25.0, 0.0);
	g_player.aModel[1].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[2].nIdxModelParent = 0;
	g_player.aModel[2].pos = D3DXVECTOR3(-10.0, 20.0, .0);
	g_player.aModel[2].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[3].nIdxModelParent = 2;
	g_player.aModel[3].pos = D3DXVECTOR3(-10.0, 0.0, 0.0);
	g_player.aModel[3].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[4].nIdxModelParent = 3;
	g_player.aModel[4].pos = D3DXVECTOR3(-10.0, 0.0, 0.0);
	g_player.aModel[4].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[5].nIdxModelParent = 0;
	g_player.aModel[5].pos = D3DXVECTOR3(10.0, 20.0, 0.0);
	g_player.aModel[5].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[6].nIdxModelParent = 5;
	g_player.aModel[6].pos = D3DXVECTOR3(10.0, 0.0, 0.0);
	g_player.aModel[6].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[7].nIdxModelParent = 6;
	g_player.aModel[7].pos = D3DXVECTOR3(10.0, 0.0, 0.0);
	g_player.aModel[7].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[8].nIdxModelParent = 0;
	g_player.aModel[8].pos = D3DXVECTOR3(-5.0, 0.0, 0.0);
	g_player.aModel[8].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[9].nIdxModelParent = 8;
	g_player.aModel[9].pos = D3DXVECTOR3(0.0, -20.0, 0.0);
	g_player.aModel[9].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[10].nIdxModelParent = 9;
	g_player.aModel[10].pos = D3DXVECTOR3(0.0, -20.0, 0.0);
	g_player.aModel[10].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[11].nIdxModelParent = 0;
	g_player.aModel[11].pos = D3DXVECTOR3(5.0, 0.0, 0.0);
	g_player.aModel[11].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[12].nIdxModelParent = 11;
	g_player.aModel[12].pos = D3DXVECTOR3(0.0, -20.0, 0.0);
	g_player.aModel[12].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_player.aModel[13].nIdxModelParent = 12;
	g_player.aModel[13].pos = D3DXVECTOR3(0.0, -20.0, 0.0);
	g_player.aModel[13].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	//�v���C���[�̈ʒu
	g_player.pos = D3DXVECTOR3(0.0, 0.0, -1000.0);

	//���@�̗L����
	g_player.bUse = true;

	g_aPos[0] = D3DXVECTOR3(-100.0, 0.0, 500.0);
	g_aPos[1] = D3DXVECTOR3(100.0, 0.0, 500.0);

	g_aPos[0] + g_aPos[1] = vecA;
	g_aPos[0] + g_player.pos = vecB;
	
	return S_OK;
}

//-------------------------------------------------------------------------------
//�I������
//-------------------------------------------------------------------------------
void UninitPlayer(void)
{
	for (int nModel = 0; nModel < g_player.nNumModel; nModel++)
	{
		//���b�V���̔j��
		if (g_player.aModel[nModel].MeshModel != NULL)
		{
			g_player.aModel[nModel].MeshModel->Release();
			g_player.aModel[nModel].MeshModel = NULL;
		}

		//�}�e���A���̔j��
		if (g_player.aModel[nModel].BuffMatModel != NULL)
		{
			g_player.aModel[nModel].BuffMatModel->Release();
			g_player.aModel[nModel].BuffMatModel = NULL;
		}
	}
}

//-------------------------------------------------------------------------------
//�X�V����
//-------------------------------------------------------------------------------
void UpdatePlayer(void)
{
	//�ϐ��錾
	BULLET*pBullet = GetBullet();
	XinputGamepad*pXinputGamepad = GetXinputGamepad();
	CAMERA*pCamera = GetCamera();

	int nLife = 500;
	int nCntBullet = 0;
	int nCntShot = 0;
	int nCnt = 0;

	nCntShot++;

	//���菈��
	g_player.oldpos.z = (vecA.z*vecB.x) - (vecA.x*vecB.z);
	
	if (g_player.oldpos.z <= vecA.z)
	{
		if (g_player.pos.z > vecA.z)
		{
			g_player.pos.z = vecA.z;
		}
	}

	if (g_player.pos.x <= -100.0f && g_player.pos.x >= 100.0f)
	{
		g_player.move.x += 0;
	}

	if (g_player.pos.z <= -100.0f && g_player.pos.z >= 100.0f)
	{
		g_player.move.z = 0;
	}
	
	//����
	g_player.move.x += (0.0f - g_player.move.x)*0.1f;
	g_player.move.z += (0.0f - g_player.move.z)*0.1f;

	//�ړ�����
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;
	g_player.pos.z += g_player.move.z;
}

//-------------------------------------------------------------------------------
//�`�揈��
//-------------------------------------------------------------------------------
void DrawPlayer(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;		//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A�����g�p
	D3DXMATERIAL*pMat;				//�}�e���A���f�[�^�ւ̃|�C���^
	D3DMATERIAL9  MatD3D;			//�}�e���A���f�[�^�̃|�C���^

	D3DXMATRIX mtxShadow;			//�V���h�E�}�g���b�N�X
	D3DXVECTOR4 vecLight;			//���C�g�̃x�N�g��
	D3DXVECTOR3 pos, normal;		//���ʏ�̔C�ӂ̓_�A�@���x�N�g��
	D3DXPLANE plane;				//����

	if (g_player.bUse == true)
	{

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_player.mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
		D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
		D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

		//���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
		{
			//�v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxRotModel, mtxTransModel;

			//�e�̃}�g���b�N�X
			D3DXMATRIX mtxParent;

			//�e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

			//�e�p�[�c�̌����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRot);

			//�e�p�[�c�̈ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTrans);

			//�e�p�[�c�̐e�̃}�g���b�N�X��ݒ�
			if (g_player.aModel[nCntModel].nIdxModelParent != -1)
			{
				mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParent].mtxWorld;
			}
			else
			{
				mtxParent = g_player.mtxWorld;
			}

			//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld,
				&g_player.aModel[nCntModel].mtxWorld,
				&mtxParent);

			//�e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[nCntModel].mtxWorld);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].BuffMatModel->GetBufferPointer();


			for (int nCntcolor = 0; nCntcolor < (int)g_player.aModel[nCntModel].nNumMat; nCntcolor++)
			{
				//�}�e���A����ݒ�
				pDevice->SetMaterial(&pMat[nCntcolor].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);

				//���f��(�p�[�c)�̕`��
				g_player.aModel[nCntModel].MeshModel->DrawSubset(nCntcolor);
			}

			for (int nCntcolor = 0; nCntcolor < (int)g_player.aModel[nCntModel].nNumMat; nCntcolor++)
			{

				//�}�e���A����ݒ�
				pDevice->SetMaterial(&MatD3D);

				//shadow�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&mtxShadow);

				//���C�g�̃x�N�g���ݒ�
				vecLight = D3DXVECTOR4(0.2f, 1.0f, 0.9f, 0.0f);

				//���ʂ̐���
				pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				D3DXPlaneFromPointNormal(&plane, &pos, &normal);

				//�V���h�E�}�g���b�N�X�̐���
				D3DXMatrixShadow(&mtxShadow, &vecLight, &plane);
				D3DXMatrixMultiply(&mtxShadow, &g_player.aModel[nCntModel].mtxWorld, &mtxShadow);

				//�V���h�E�}�g���b�N�X
				pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

				//���f��(�p�[�c)�̕`��
				g_player.aModel[nCntModel].MeshModel->DrawSubset(nCntcolor);
			}
		}

		//�ۑ����Ă����}�e���A����Ԃ�
		pDevice->SetMaterial(&matDef);
	}
}

//-------------------------------------------------------------------------------
//���_���W�̐ݒ�
//-------------------------------------------------------------------------------
Player*GetPlayer(void)
{
	return &g_player;
}