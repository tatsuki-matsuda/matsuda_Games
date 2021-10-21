//=============================================================================
//
// ���C������ [bullet.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "bullet.h"
#include "normal_bullet.h"
#include "explosion.h"
#include "manager.h"
#include "renderer.h"
#include "enemy.h"
#include "dinput_keyboard.h"
#include "player.h"
#include "score.h"
#include "game.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CNormal_Bullet::CNormal_Bullet(int nPriority) :CBullet(nPriority)
{
	//�p�x�̏����l
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CNormal_Bullet::~CNormal_Bullet()
{

}

//*****************************************************************************
// ��������
//*****************************************************************************
CNormal_Bullet *CNormal_Bullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, D3DXVECTOR3 rot, BULLETTYPE bulletType, ATTACKTYPE attackType, INFOTYPE infoType)
{
	//���I�m��
	CNormal_Bullet* pNormal_Bullet;
	pNormal_Bullet = new CNormal_Bullet;

	//�������������Ăяo��
	pNormal_Bullet->Init(pos, scale, move, rot);

	//�e�̏��̌Ăяo��
	pNormal_Bullet->SetBulletType(bulletType);

	//�U����ޏ��̌Ăяo��
	pNormal_Bullet->SetAttackType(attackType);

	//�U�����̌Ăяo��
	pNormal_Bullet->SetInfoType(infoType);

	//�e�N�X�`���̌Ăяo��
	//for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		pNormal_Bullet->BindTexture(GetTexture(1));
	}

	return pNormal_Bullet;
}

//*****************************************************************************
//�@����������
//*****************************************************************************
HRESULT CNormal_Bullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, D3DXVECTOR3 rot)
{

	CBullet::Init(pos, scale, move, rot);

	//�ʒu��ݒ�
	m_posOrigin = pos;

	m_posDeath = D3DXVECTOR3(0, 0, 0);

	//�p�x��ݒ�
	m_rot = rot;

	//�g���Ă��邩�ǂ���
	m_bUninit = false;

	m_nCnt = 0;

	m_nMoveCnt = 0;

	//���
	SetObjType(OBJTYPE_BULLET);

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CNormal_Bullet::Uninit(void)
{
	//CScene2D����Ăяo��
	CBullet::Uninit();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CNormal_Bullet::Update(void)
{
	//�ʒu�̎擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//�ʒu�̎擾
	D3DXVECTOR3 scale;
	scale = GetScale();

	//�ʒu�̎擾
	D3DXVECTOR3 m_move;
	m_move = GetMove();

	//�ʒu�̎擾
	int m_nLife;
	m_nLife = GetLife();

	//�U����ނ̎擾
	INFOTYPE m_InfoType;
	m_InfoType = GetInfoType();

	//CEnemy::ENEMYTYPE m_EnemyType = CEnemy::GetEnemyType();

	//����
	m_nLife--;

	//�ʏ�e�̏ꍇ
	if (m_InfoType == INFOTYPE_1)
	{
		////�ʏ�G1�������ꍇ
		//if (CEnemy::BOSSTYPE() == CEnemy::ENEMYTYPE_NORMAL1)
		//{
		//	m_nCnt++;

		//	if (m_nCnt >= 10 && m_nMoveCnt <= 10)
		//	{
		//		m_move.x = 0.0f;
		//		m_move.y = 0.0f;

		//		m_nMoveCnt++;
		//	}

		//	if (m_nMoveCnt >= 10)
		//	{
		//		m_move.x = 1.0f;
		//		m_move.y = 1.0f;
		//	}
		//}

		//��ʊO����
		if (pos.y - scale.y / 2.0f < SCREEN_HEIGHT_TOP-20 ||
			pos.y + scale.y / 2.0f > SCREEN_HEIGHT+20 ||
			pos.x - scale.x / 2.0f < -20.0f ||
			pos.x + scale.x / 2.0f > SCREEN_GAMEWIDTH + 20)
		{
			//����
			m_bUninit = true;
		}

		//�̗͂�0�ɂȂ����ꍇ
		else if (m_nLife <= 0)
		{
			//����
			m_bUninit = true;
		}

	}

	//�ʏ�e2�̏ꍇ
	if (m_InfoType == INFOTYPE_2)
	{
		//��ʊO����
		if (pos.y - scale.y / 2.0f < SCREEN_HEIGHT_TOP - 30 ||
			pos.x - scale.x / 2.0f < -25.0f ||
			pos.x + scale.x / 2.0f > SCREEN_GAMEWIDTH)
		{
			//����
			m_bUninit = true;
		}
		//�̗͂�0�ɂȂ����ꍇ
		else if (m_nLife <= 0)
		{
			//����
			m_bUninit = true;
		}
	}

	//�ʏ�e3�̏ꍇ
	if (m_InfoType == INFOTYPE_3)
	{
		m_nCnt++;

		if (m_nCnt % 8 == 0)
		{
			m_move.x *= 1.1f;
			m_move.y *= 1.03f;
		}

		if (m_nCnt % 15 == 0)
		{
			scale.x = 20;
			scale.y = 20;

		}

		//��ʊO����
		if (pos.y - scale.y / 2.0f < SCREEN_HEIGHT_TOP ||
			pos.y + scale.y / 2.0f > SCREEN_HEIGHT ||
			pos.x - scale.x / 2.0f < -30.0f ||
			pos.x + scale.x / 2.0f > SCREEN_GAMEWIDTH + 100)
		{
			//����
			m_bUninit = true;
		}
		//�̗͂�0�ɂȂ����ꍇ
		else if (m_nLife <= 0)
		{
			//����
			m_bUninit = true;
		}

	}

	//�ړ��ʂ�ǉ�
	pos += m_move;

	//�ʒu�̍X�V
	SetPosition(pos, scale);

	//�ʒu�̍X�V
	SetScale(scale);

	SetMove(m_move);

	SetLife(m_nLife);


	//���ł����ꍇ
	if (m_bUninit == true)
	{
		//�I�������̌Ăяo��
		Uninit();

		return;
	}

	//�X�V���̌Ăяo��
	CBullet::Update();

}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CNormal_Bullet::Draw(void)
{
	//�`��̌Ăяo��
	CBullet::Draw();
}
