//-------------------------------------------------------------------------------
//
// �Q�[������[Model.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include"sceneX.h"		//�Q�[�����
#include"bullet.h"		//�e�̏ڍ�
#include"manager.h"		//�e�̏ڍ�

//-------------------------------------------------------------------------------
//�O���[�o���ϐ�
//-------------------------------------------------------------------------------

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CSceneX::CSceneX(int nPriority):CScene(nPriority)
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CSceneX::~CSceneX()
{

}



//*****************************************************************************
// ��������
//*****************************************************************************
CSceneX *CSceneX::Create(D3DXVECTOR3 pos)
{
	//���I�m��
	CSceneX* pSceneX;
	pSceneX = new CSceneX;


	//�����̌Ăяo��
	pSceneX->Init(pos,D3DXVECTOR3(0.0f,0.0f,0.0f));

	//�l��Ԃ�
	return pSceneX;
}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CSceneX::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�f�o�C�X�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\field002.jpg", &g_pTextureModel);

	//x�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\SyougiBan001.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &m_pBuffMatModel, NULL,
		&m_nNumMatModel, &m_pMeshModel);

	//D3DXMATERIAL*pMat;

	//�}�e���A�����ɑ΂���|�C���^���擾
	//pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

	//for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
	//{
	//	if (pMat[nCntMat].pTextureFilename != NULL)
	//	{
	//		pMat[1].pTextureFilename = "data\\TEXTURE\\eye.jpg";
	//	}
	//}

	m_rotmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�|���S���̈ʒu�E�����̏����ݒ�
	m_posModel = D3DXVECTOR3(-42.0f, 0.0f, 10.0f);
	m_rotModel = D3DXVECTOR3(-0.2f, 0.4f, -0.9f);

	//���
	SetObjType(OBJTYPE_UI);

	return S_OK;
}

//*****************************************************************************
// 
//*****************************************************************************
void  CSceneX::Uninit(void)
{
	//���b�V���̔j��
	if (m_pMeshModel != NULL)
	{
		m_pMeshModel->Release();
		m_pMeshModel = NULL;
	}

	//�}�e���A���̔j��
	if (m_pBuffMatModel != NULL)
	{
		m_pBuffMatModel->Release();
		m_pBuffMatModel = NULL;
	}
}

//-------------------------------------------------------------------------------
//�X�V����
//-------------------------------------------------------------------------------
void  CSceneX::Update(void)
{
	m_rotModel += m_rotmove;

	m_rotmove.y = 0.002f;
	m_rotmove.z = 0.01f;
}

//-------------------------------------------------------------------------------
//�`�揈��
//-------------------------------------------------------------------------------
void  CSceneX::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A�����g�p
	D3DXMATERIAL*pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//Z�o�b�t�@�̍X�V�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorldModel);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotModel.y, m_rotModel.x, m_rotModel.z);
	D3DXMatrixMultiply(&m_mtxWorldModel, &m_mtxWorldModel, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_posModel.x, m_posModel.y, m_posModel.z);
	D3DXMatrixMultiply(&m_mtxWorldModel, &m_mtxWorldModel, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldModel);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();


	//Z�o�b�t�@�̍X�V��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
	{
		//�}�e���A����ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		//���f��(�p�[�c)�̕`��
		m_pMeshModel->DrawSubset(nCntMat);
	}


	//�ۑ����Ă����}�e���A����Ԃ�
	pDevice->SetMaterial(&matDef);
}
