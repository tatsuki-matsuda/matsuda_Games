//=============================================================================
//
// ���C������ [item.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "item.h"
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
LPDIRECT3DTEXTURE9 CItem::m_pTexture[MAX_TEXTURE] = {};			// �e�N�X�`��
D3DXVECTOR3 CItem::m_Craetepos[10] = {};				// �ʒu

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CItem::CItem(int nPriority) :CScene2D(nPriority)
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CItem::~CItem()
{

}

//*****************************************************************************
// ��������
//*****************************************************************************
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, ITEMTYPE itemType)
{
	//���I�m��
	CItem* pItem;
	pItem = new CItem;

	//�A�C�e������
	pItem->SetItemType(itemType);

	//�����̌Ăяo��
	pItem->Init(pos, scale, move);

	//�e�N�X�`���̌Ăяo��
	for (int nCntTex = 0; nCntTex < 4; nCntTex++)
	{
		pItem->BindTexture(m_pTexture[nCntTex]);
	}

	//�l��Ԃ�
	return pItem;

}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move)
{
	//�傫����ݒ�
	m_scale = scale;

	//�ړ���ݒ�
	m_move = move;

	//���
	SetObjType(OBJTYPE_ITEM);

	//�����Ă邩�ǂ���
	m_bUninit = false;

	//�o���o�ߎ���
	m_nCntTime = 0;

	//�A�C�e���o���J�E���g
	m_nItemCnt = 0;

	//�A�C�e���ړ��J�E���g
	m_nItemmoveCnt = 0;

	//�G�����ł����ʒu
	m_posDeath = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
void CItem::Uninit(void)
{
	//�I���̌Ăяo��
	CScene2D::Uninit();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CItem::Update(void)
{
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


	for (int nCntPriority = 0; nCntPriority < CScene::OBJTYPE_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			CScene*pScene;
			pScene = CScene::GetScene(nCntPriority, nCntScene);

			if (pScene != NULL)
			{

				//�A�C�e���̎�ނ��c�@�̏ꍇ
				if (m_ItemType == ITEMTYPE_1UP)
				{


				}

				//�A�C�e���̎�ނ��{���̏ꍇ
				if (m_ItemType == ITEMTYPE_BOMB)
				{


				}

				//�A�C�e���̎�ނ��c�@�̏ꍇ
				if (m_ItemType == ITEMTYPE_POWERUP)
				{


				}
			}
		}
	}

	

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
void CItem::Draw(void)
{
	//�`��̌Ăяo��
	CScene2D::Draw();
}

////*****************************************************************************
//// ���菈��
////*****************************************************************************
//void CLife::OnCollision(void)
//{
//	//�ʒu�̎擾
//	D3DXVECTOR3 pos;
//	pos = GetPosition();
//
//	//�ʒu�̍X�V
//	SetPosition(pos, m_scale);
//
//	CScore *pScore;
//	pScore = CGame::GetScore();
//
//	for (int nCntPriority = 0; nCntPriority < CScene::OBJTYPE_MAX; nCntPriority++)
//	{
//		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
//		{
//			CScene*pScene;
//			pScene = CScene::GetScene(nCntPriority, nCntScene);
//
//			if (pScene != NULL)
//			{
//
//
//				//��ޔ���Ăяo��
//				CScene::OBJTYPE objType;
//				objType = pScene->GetObjType();
//
//				CBullet *pBullet = (CBullet*)pBullet;
//
//				//�e����Ăяo��
//				pBullet::BULLETTYPE BulletType;
//				BulletType = GetBulletType();
//
//				//�G�̒e�ł��^�C�v���v���C���[�̏ꍇ
//				if (BulletType == BULLETTYPE_ENEMY && objType == OBJTYPE_PLAYER)
//				{
//					CPlayer *pPlayer = (CPlayer*)pScene;
//
//					//�ʒu�̎擾
//					D3DXVECTOR3 Playerpos;
//					Playerpos = pPlayer->GetPosition();
//
//					//�ʒu�̎擾
//					D3DXVECTOR3 Playerscale;
//					Playerscale = pPlayer->GetScale();
//
//					//�����蔻��
//					if (pos.x + m_scale.x / 2.0f > Playerpos.x - Playerscale.x / 12.0f&&
//						pos.x - m_scale.x / 2.0f < Playerpos.x + Playerscale.x / 12.0f&&
//						pos.y + m_scale.y / 2.0f > Playerpos.y - Playerscale.y / 12.0f&&
//						pos.y - m_scale.y / 2.0f < Playerpos.y + Playerscale.y / 12.0f)
//					{
//
//						//����
//						m_bUninit = true;
//					}
//				}
//			}
//		}
//	}
//}

//*****************************************************************************
// �e�N�X�`���ǂݍ��ݏ���
//*****************************************************************************
HRESULT CItem::Load(void)
{
	//�f�o�C�X�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\zanki.png", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Bomb_Item.png", &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet001.png", &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &m_pTexture[3]);

	return S_OK;
}

//*****************************************************************************
//*****************************************************************************
// �e�N�X�`���j������
void CItem::Unload(void)
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
void CItem::OnDiffuesPos(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// Create���̏��
	// 1 pos, 2 scale. 3 move, 4 rot, 5 bulletType, 6 attackType, 7 infoType

	////��]�ʏ�e�������̏���
	//if ()
	//{

	//}

	////�S���ʌ����e�������̏���
	//if ()
	//{
	//}

	////�S���ʔ��˒e�������̏���
	//if ()
	//{
	//}

	////�㉺���˒e�������̏���
	//if ()
	//{
	//	//�ʒu���Q�Ƃ����ꂽ�ʒu����e�𐶐�
	//	float fLength = 400.0f + rand() % 30;

	//}
}