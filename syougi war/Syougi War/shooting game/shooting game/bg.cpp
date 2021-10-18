//=============================================================================
//
// ���C������ [bg.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "bg.h"
#include "scene2D.h"
#include "manager.h"
#include "renderer.h"
#include "dinput_keyboard.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_BG] = {};			// �e�N�X�`��

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CBg::CBg(int nPriority) :CScene(nPriority)
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CBg::~CBg()
{

}

//*****************************************************************************
// ��������
//*****************************************************************************
CBg *CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//���I�m��
	CBg* pBg;
	pBg = new CBg;

	//�����̌Ăяo��
	pBg->Init(pos, scale);

	//�l��Ԃ�
	return pBg;
}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CBg::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�w�i�̐؂�ւ�
	switch (CManager::GetMode())
	{

	//�Q�[����ʂ������ꍇ
	case CManager::MODE_GAME:

		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			if (m_apScene2D[nCnt] == NULL)
			{
				m_apScene2D[nCnt] = new CScene2D;
				m_apScene2D[nCnt]->Init(pos, scale);
				m_apScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);
			}
		}

		break;

		//�^�C�g����ʂ������ꍇ
	case CManager::MODE_TITLE:

			if (m_apScene2D[0] == NULL)
			{
				m_apScene2D[0] = new CScene2D;
				m_apScene2D[0]->Init(pos, scale);
				m_apScene2D[0]->BindTexture(m_apTexture[2]);
			}

		break;

		//�`���[�g���A����ʂ������ꍇ
	case CManager::MODE_TUTORIAL:

		if (m_apScene2D[0] == NULL)
		{
			m_apScene2D[0] = new CScene2D;
			m_apScene2D[0]->Init(pos, scale);
			m_apScene2D[0]->BindTexture(m_apTexture[4]);
		}

		break;

		//�Q�[����ʂ������ꍇ
	case CManager::MODE_RESULT:

		if (m_apScene2D[0] == NULL)
		{
			m_apScene2D[0] = new CScene2D;
			m_apScene2D[0]->Init(pos, scale);
			m_apScene2D[0]->BindTexture(m_apTexture[3]);
		}

		break;

	default:
		break;
	}

	//���
	SetObjType(OBJTYPE_BG);

	//�l��Ԃ�
	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CBg::Uninit(void)
{

	//�w�i�̐؂�ւ�
	switch (CManager::GetMode())
	{

		//�Q�[����ʂ������ꍇ
	case CManager::MODE_GAME:

		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			if (m_apScene2D[nCnt] == NULL)
			{
				m_apScene2D[nCnt] = new CScene2D;
				m_apScene2D[nCnt]->Uninit();
				m_apScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);
			}
		}

		break;

		//�^�C�g����ʂ������ꍇ
	case CManager::MODE_TITLE:

		if (m_apScene2D[0] == NULL)
		{
			m_apScene2D[0] = new CScene2D;
			m_apScene2D[0]->Uninit();
			m_apScene2D[0]->BindTexture(m_apTexture[2]);
		}

		break;

		//�`���[�g���A����ʂ������ꍇ
	case CManager::MODE_TUTORIAL:

		if (m_apScene2D[0] == NULL)
		{
			m_apScene2D[0] = new CScene2D;
			m_apScene2D[0]->Uninit();
			m_apScene2D[0]->BindTexture(m_apTexture[4]);
		}

		break;

		//�Q�[����ʂ������ꍇ
	case CManager::MODE_RESULT:

		if (m_apScene2D[0] == NULL)
		{
			m_apScene2D[0] = new CScene2D;
			m_apScene2D[0]->Uninit();
			m_apScene2D[0]->BindTexture(m_apTexture[3]);
		}

		break;

	}

	Release();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CBg::Update(void)
{
	//�X�N���[���ړ�
	m_fAnim += 0.0005f;

	//�w�i�̐؂�ւ�
	switch (CManager::GetMode())
	{

		//�Q�[����ʂ������ꍇ
	case CManager::MODE_GAME:

		//�X�V�̌Ăяo��
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			if (m_apScene2D[nCnt] != NULL)
			{
				//����
				m_apScene2D[nCnt]->SetBg(m_fAnim*(nCnt + 1));
			}
		}

		break;
	}
	
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CBg::Draw(void)
{
	m_apScene2D[0]->Draw();
}

//*****************************************************************************
// �e�N�X�`���ǂݍ��ݏ���
//*****************************************************************************
HRESULT CBg::Load(void)
{
	//�f�o�C�X�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bg100.png", &m_apTexture[0]);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bg101.png", &m_apTexture[1]);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Titlebg.png", &m_apTexture[2]);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Resultbg.png", &m_apTexture[3]);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial.png", &m_apTexture[4]);

	return S_OK;
}

//*****************************************************************************
// �e�N�X�`���j������
//*****************************************************************************
void CBg::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		//�e�N�X�`���̊J��
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}