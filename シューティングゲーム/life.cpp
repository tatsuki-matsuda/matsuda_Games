//=============================================================================
//
// ���C������ [life.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "game.h"
#include "life.h"
#include "scene.h"
#include "scene2D.h"
#include "game.h"
#include "manager.h"
#include "score.h"
#include "renderer.h"
#include "dinput_keyboard.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CLife::m_pTexture[MAX_TEXTURE] = {};			// �e�N�X�`��
D3DXVECTOR3 CLife::m_Craetepos[10] = {};				// �ʒu

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

	//�e�N�X�`���̌Ăяo��
	for (int nCntTex = 0; nCntTex < 1; nCntTex++)
	{
		pLife->BindTexture(m_pTexture[nCntTex]);
	}

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

	//�o���o�ߎ���
	m_nCntTime = 0;

	//�A�C�e���o���J�E���g
	m_nLifeCnt = 0;

	//�A�C�e�������p�̍��W
	m_Craetepos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Craetepos[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Craetepos[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Craetepos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Craetepos[4] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Craetepos[5] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Craetepos[6] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Craetepos[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Craetepos[8] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Craetepos[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�������̌Ăяo��
	CScene2D::Init(pos, scale);

	//�l��Ԃ�
	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CLife::Uninit(void)
{
	//�I���̌Ăяo��
	CScene2D::Uninit();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CLife::Update(void)
{
	//�L�[�{�[�h�\���̎擾
	CInputKeyBoard *pKeyboard;
	pKeyboard = CManager::GetInputKeyBoard();

	//�ʒu�̎擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//�X�R�A�̎擾
	CScore *pScore;
	pScore = CGame::GetScore();

	//�Ίp���̒���
	m_angle = sqrtf(15 * 15 + 15 * 15);

	//�Ίp���̊p�x
	float fAngle = atan2f(5, 5);

	//���ˎ���
	m_timer++;

	if (pKeyboard->GetTrigger(DIK_U) == true)
	{

		m_nLifeCnt++;

		OnDiffuesPos(m_nLifeCnt);
	}

	//for (int nCntPriority = 0; nCntPriority < CScene::OBJTYPE_MAX; nCntPriority++)
	//{
	//	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	//	{
	//		CScene*pScene;
	//		pScene = CScene::GetScene(nCntPriority, nCntScene);

	//		if (pScene != NULL)
	//		{

	//		}
	//	}
	//}

	//�ړ����Z
	pos += m_move;

	//�ʒu�̍X�V
	SetPosition(pos, m_scale);

	//�傫��
	SetScale(m_scale);
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CLife::Draw(void)
{
	//�`��̌Ăяo��
	CScene2D::Draw();
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
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\zanki.png", &m_pTexture[0]);

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

	//�ʒu�̎擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	m_nLifeCnt = nCnt;

	// Create���̏��
	// 1 pos, 2 scale

	//��]�ʏ�e�������̏���
	if (m_nLifeCnt == 2)
	{
		pos.x += 20;
	}

	//�S���ʌ����e�������̏���
	if (m_nLifeCnt == 3)
	{
		pos.x += 40;
	}

	//�S���ʔ��˒e�������̏���
	if (m_nLifeCnt == 4)
	{
		pos.x += 60;
	}

	//�㉺���˒e�������̏���
	if (m_nLifeCnt == 5)
	{
		pos.x += 80;
	}

	//�ʒu�̍X�V
	SetPosition(pos, m_scale);

	//�傫��
	SetScale(m_scale);
}