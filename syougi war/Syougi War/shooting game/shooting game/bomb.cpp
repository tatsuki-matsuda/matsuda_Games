//=============================================================================
//
// ���C������ [life.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "fade.h"
#include "bomb.h"
#include "player.h"
#include "scene.h"
#include "scene2D.h"
#include "manager.h"
#include "score.h"
#include "renderer.h"
#include "game.h"
#include "dinput_keyboard.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBomb::m_pTexture[MAX_TEXTURE] = {};			// �e�N�X�`��
D3DXVECTOR3 CBomb::m_Craetepos[5] = {};							// �ʒu

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CBomb::CBomb(int nPriority) :CScene2D(nPriority)
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CBomb::~CBomb()
{

}

//*****************************************************************************
// ��������
//*****************************************************************************
CBomb *CBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//���I�m��
	CBomb* pBomb;
	pBomb = new CBomb;

	//�����̌Ăяo��
	pBomb->Init(pos, scale);

	//�l��Ԃ�
	return pBomb;

}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�傫����ݒ�
	m_scale = scale;

	//���
	SetObjType(OBJTYPE_UI);

	//�����Ă邩�ǂ���
	m_bUninit = false;

	//�o�ߎ���
	m_nCntTime = 0;

	//�{���̌�
	m_nBomb = MAX_PLAYERBOMB;

	//�ǂݍ��݌Ăяo��
	Load();

	//�{���̐�������
	for (int nCnt = 0; nCnt < m_nBomb; nCnt++)
	{
		if (m_apScene2D[nCnt] == NULL)
		{
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Init(D3DXVECTOR3(pos.x + 50.0f * nCnt, pos.y, pos.z), scale);
			m_apScene2D[nCnt]->BindTexture(m_pTexture[0]);
		}
	}

	//�l��Ԃ�
	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CBomb::Uninit(void)
{
	//�I���̌Ăяo��
	for (int nCnt = 0; nCnt < m_nBomb; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Uninit();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[0]);
		}
	}
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CBomb::Update(void)
{
	//�L�[�{�[�h�\���̎擾
	CInputKeyBoard *pKeyboard;
	pKeyboard = CManager::GetInputKeyBoard();

	//�X�R�A�̎擾
	CScore *pScore;
	pScore = CGame::GetScore();


	for (int nCntBomb = 0; nCntBomb < m_nBomb; nCntBomb++)
	{
		if (m_apScene2D[nCntBomb] != NULL)
		{
			m_apScene2D[nCntBomb]->Update();
		}
	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CBomb::Draw(void)
{
	//�`��̌Ăяo��
	for (int nCntLife = 0; nCntLife < m_nBomb; nCntLife++)
	{
		if (m_apScene2D[nCntLife] != NULL)
		{
			m_apScene2D[nCntLife]->Draw();
		}
	}
}

//*****************************************************************************
// �e�N�X�`���ǂݍ��ݏ���
//*****************************************************************************
HRESULT CBomb::Load(void)
{
	//�f�o�C�X�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Bomb_Item.png", &m_pTexture[0]);

	return S_OK;
}

//*****************************************************************************
// �e�N�X�`���j������
//*****************************************************************************
void CBomb::Unload(void)
{
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		//�e�N�X�`���̊J��
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}

//*****************************************************************************
// �A�C�e���̈ʒu��������
//*****************************************************************************
void CBomb::OnDiffuesPos(int nCnt)
{

}