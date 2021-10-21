//=============================================================================
//
// ���C������ [scene.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CScene*CScene::m_apScene[OBJTYPE_MAX][MAX_POLYGON] = {};	// �|���S���̐�
int CScene::m_nNumAll = NULL;								// �ő吔
CScene*CScene::m_pTop = NULL;								// �擪�ւ̃|�C���^
CScene*CScene::m_pCur = NULL;								// ����(�Ō���̃I�u�W�F�N�g)�ւ̃|�C���^

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CScene::CScene(int nPriority)
{
	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		if (m_apScene[nPriority][nCntScene] == NULL)
		{
			m_apScene[nPriority][nCntScene] = this;
			m_nID = nCntScene;
			m_nPriority = nPriority;
			m_nNumAll++;
			break;
		}
	}
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CScene::~CScene()
{

}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CScene::UpdateAll()
{
	bool bPause = CManager::GetPause();

	for (int nCntPriority = 0; nCntPriority < OBJTYPE_MAX; nCntPriority++)
	{
		if (CManager::GetPause() == true && nCntPriority == OBJTYPE_PAUSE)
		{
			for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
			{
				if (m_apScene[nCntPriority][nCntScene] != NULL)
				{
					m_apScene[nCntPriority][nCntScene]->Update();
				}
			}
		}
		else if (CManager::GetPause() == false && nCntPriority != OBJTYPE_PAUSE)
		{
			for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
			{
				if (m_apScene[nCntPriority][nCntScene] != NULL)
				{
					m_apScene[nCntPriority][nCntScene]->Update();
				}
			}
		}
	}
}

//*****************************************************************************
// �J������
//*****************************************************************************
void CScene::ReleaseAll()
{
	//�S�ẴI�u�W�F�N�g�̔j��
	for (int nCntPriority = 0; nCntPriority < OBJTYPE_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				m_apScene[nCntPriority][nCntScene]->Uninit();
				delete m_apScene[nCntPriority][nCntScene];
				m_apScene[nCntPriority][nCntScene] = NULL;
			}
		}
	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CScene::DrawAll()
{

	//�f�o�C�X�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//Z�o�b�t�@�̍X�V�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�J�������̌Ăяo��
	CCamera*pCamera = CManager::GetCamera();

	//�J�������
	pCamera->SetCamera();

	for (int nCntPriority = 0; nCntPriority < OBJTYPE_MAX; nCntPriority++)
	{
		if (CManager::GetPause() == true)
		{
			for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
			{
				if (m_apScene[nCntPriority][nCntScene] != NULL)
				{
					m_apScene[nCntPriority][nCntScene]->Draw();
				}
			}
		}
		else if (CManager::GetPause() == false && nCntPriority != OBJTYPE_PAUSE)
		{
			for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
			{
				if (m_apScene[nCntPriority][nCntScene] != NULL)
				{
					m_apScene[nCntPriority][nCntScene]->Draw();
				}
			}
		}
	}

	//Z�o�b�t�@�̍X�V��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CScene::Release(void)
{
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int nID = m_nID;
		int nPriority = m_nPriority;

		//�C���X�^���X�̔j��
		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;
	}
}

//*****************************************************************************
// �̗͌��Z����
//*****************************************************************************
void CScene::LifeSub(int nPow)
{
	m_nLife -= nPow;
}


//=============================================================================
// Scene�N���X�̒l
//=============================================================================
CScene * CScene::GetScene(int nCntPriority,int nCntScene)
{
	return m_apScene[nCntPriority][nCntScene];
}

//*****************************************************************************
// ��ޏ�񏈗�
//*****************************************************************************
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//*****************************************************************************
// ��ނ̐ݒ菈��
//*****************************************************************************
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}