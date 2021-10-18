//=============================================================================
//
// ���C������ [life.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "fade.h"
#include "life.h"
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
LPDIRECT3DTEXTURE9 CLife::m_pTexture[MAX_TEXTURE] = {};			// �e�N�X�`��
D3DXVECTOR3 CLife::m_Craetepos[5] = {};							// �ʒu

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CLife::CLife(int nPriority) :CScene2D(nPriority)
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CLife::~CLife()
{

}

//*****************************************************************************
// ��������
//*****************************************************************************
CLife *CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//���I�m��
	CLife* pLife;
	pLife= new CLife;

	//�����̌Ăяo��
	pLife->Init(pos, scale);

	//�l��Ԃ�
	return pLife;

}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CLife::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�傫����ݒ�
	m_scale = scale;

	//���
	SetObjType(OBJTYPE_UI);

	//�����Ă邩�ǂ���
	m_bUninit = false;

	//�o�ߎ���
	m_nCntTime = 0;

	//�c�@�̌�
	m_nLife = MAX_PLAYERLIFE;

	//�ǂݍ��݌Ăяo��
	Load();

	//�c�@���e�N�X�`���𐶐�
	for (int nCnt = 0; nCnt < m_nLife; nCnt++)
	{
		if (m_apScene2D[nCnt] == NULL)
		{
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Init(D3DXVECTOR3(pos.x + 50.0f * nCnt,pos.y,pos.z), scale);
			m_apScene2D[nCnt]->BindTexture(m_pTexture[0]);
		}
	}

	//�l��Ԃ�
	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CLife::Uninit(void)
{
	//�I���̌Ăяo��
	for (int nCnt = 0; nCnt < m_nLife; nCnt++)
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
void CLife::Update(void)
{
	//�L�[�{�[�h�\���̎擾
	CInputKeyBoard *pKeyboard;
	pKeyboard = CManager::GetInputKeyBoard();

	//�X�R�A�̎擾
	CScore *pScore;
	pScore = CGame::GetScore();

	//�Ίp���̒���
	m_angle = sqrtf(15 * 15 + 15 * 15);

	//�Ίp���̊p�x
	float fAngle = atan2f(5, 5);

	for (int nCntLife = 0; nCntLife < m_nLife; nCntLife++)
	{
		if (m_apScene2D[nCntLife] != NULL)
		{
			m_apScene2D[nCntLife]->Update();
		}
	}

	// �J�ڂ��邩�ǂ���
	if (m_nLife == 0)
	{
		m_nCntTime++;

		if (m_nCntTime > 120)
		{
			CGame::SetTransition(CGame::TRANSITION_RESULT);
		}
		
	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CLife::Draw(void)
{
	//�`��̌Ăяo��
	for (int nCntLife = 0; nCntLife < m_nLife; nCntLife++)
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
HRESULT CLife::Load(void)
{
	//�f�o�C�X�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\player001.png", &m_pTexture[0]);

	return S_OK;
}

//*****************************************************************************
//*****************************************************************************
// �e�N�X�`���j������
void CLife::Unload(void)
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
void CLife::OnDiffuesPos(int nCnt)
{

}