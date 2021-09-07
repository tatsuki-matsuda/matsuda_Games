////=============================================================================
////
//// ���C������ [rotate_bullet.cpp]
//// Author : Tatsuki Matsuda 
////
////=============================================================================
//#include "rotate_bullet.h"
//#include "explosion.h"
//#include "manager.h"
//#include "renderer.h"
//#include "enemy.h"
//#include "player.h"
//#include "game.h"
//
////*****************************************************************************
//// �R���X�g���N�^
////*****************************************************************************
//CRotate_Bullet::CRotate_Bullet(int nPriority) :CBullet(nPriority)
//{
//	//�p�x�̏����l
//	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//}
//
////*****************************************************************************
//// �f�X�g���N�^
////*****************************************************************************
//CRotate_Bullet::~CRotate_Bullet()
//{
//
//}
//
////*****************************************************************************
//// ��������
////*****************************************************************************
//CRotate_Bullet *CRotate_Bullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, D3DXVECTOR3 rot, BULLETTYPE bulletType, ATTACKTYPE attackType, INFOTYPE infoType)
//{
//	//���I�m��
//	CRotate_Bullet* pRotate_Bullet;
//	pRotate_Bullet = new CRotate_Bullet;
//
//	//�������������Ăяo��
//	pRotate_Bullet->Init(pos, scale, move, rot);
//
//	//�e�̏��̌Ăяo��
//	pRotate_Bullet->SetBulletType(bulletType);
//
//	//�U����ޏ��̌Ăяo��
//	pRotate_Bullet->SetAttackType(attackType);
//
//	//�U�����̌Ăяo��
//	pRotate_Bullet->SetInfoType(infoType);
//
//	//�e�N�X�`���̌Ăяo��
//	//for (int nCntTex = 0; nCntTex < 2; nCntTex++)
//	{
//		pRotate_Bullet->BindTexture(GetTexture(1));
//	}
//
//	return pRotate_Bullet;
//}
//
////*****************************************************************************
////�@����������
////*****************************************************************************
//HRESULT CRotate_Bullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, D3DXVECTOR3 rot)
//{
//
//	CBullet::Init(pos, scale, move, rot);
//
//	//�ʒu��ݒ�
//	m_posOrigin = pos;
//
//	m_posDeath = D3DXVECTOR3(0, 0, 0);
//
//	//�p�x��ݒ�
//	m_rot = rot;
//
//	//��]�̒l��ݒ�
//	m_fAngle = 0.0f;
//
//	//����]�̒l��ݒ�
//	m_fAngleL = 0.0f;
//
//	//�E��]�̒l��ݒ�
//	m_fAngleR = 0.0f;
//
//	//��]���x
//	m_fAngleSpeed[0] = (float)-0.03f;
//	m_fAngleSpeed[1] = (float)0.03f;
//
//	//����]�J�E���g�̐ݒ�
//	m_nCrossingTimeL = 0;
//
//	//�E��]�J�E���g�̐ݒ�
//	m_nCrossingTimeR = 0;
//
//	//�g���Ă��邩�ǂ���
//	m_bUninit = false;
//
//	//���
//	SetObjType(OBJTYPE_BULLET);
//
//	return S_OK;
//}
//
////*****************************************************************************
//// �I������
////*****************************************************************************
//void CRotate_Bullet::Uninit(void)
//{
//	//CScene2D����Ăяo��
//	CBullet::Uninit();
//}
//
////*****************************************************************************
//// �X�V����
////*****************************************************************************
//void CRotate_Bullet::Update(void)
//{
//	//�ʒu�̎擾
//	D3DXVECTOR3 pos;
//	pos = GetPosition();
//
//	//�ʒu�̎擾
//	D3DXVECTOR3 scale;
//	scale = GetScale();
//
//	//�ʒu�̎擾
//	D3DXVECTOR3 m_move;
//	m_move = GetMove();
//
//	//�ʒu�̎擾
//	int m_nLife;
//	m_nLife = GetLife();
//
//	//�U�����̎擾
//	ATTACKTYPE m_AttackType;
//	m_AttackType = GetAttackType();
//
//	//�U����ނ̎擾
//	INFOTYPE m_InfoType;
//	m_InfoType = GetInfoType();
//
//	//����
//	m_nLife--;
//
//	//�������e�̏ꍇ
//	if (m_AttackType == ATTACKTYPE_CROSSING&&m_InfoType == INFOTYPE_1)
//	{
//		//�J�E���g�����l�Ŋ��ꂽ�ꍇ
//		if (m_nCrossingTimeL % 5 == 0)
//		{
//			//��������
//			CBullet::OnCrossing();
//
//			//�̗͂�0�ɂȂ����ꍇ
//			if (m_nLife <= 0)
//			{
//				//����
//				m_bUninit = true;
//			}
//
//			//��ʊO����
//			if (pos.y - scale.y / 2.0f < SCREEN_HEIGHT_TOP - 30 ||
//				pos.x - scale.x / 2.0f < -25.0f ||
//				pos.x + scale.x / 2.0f > SCREEN_GAMEWIDTH)
//			{
//				//����
//				m_bUninit = true;
//			}
//		}
//
//		//�l�𑫂�
//		m_nCrossingTimeL++;
//	}
//
//	//�E�����e�̏ꍇ
//	if (m_AttackType == ATTACKTYPE_CROSSING&&m_InfoType == INFOTYPE_2)
//	{
//		//�J�E���g�����l�Ŋ��ꂽ�ꍇ
//		if (m_nCrossingTimeR % 5 == 0)
//		{
//			//��������
//			OnCrossing();
//
//			//�̗͂�0�ɂȂ����ꍇ
//			if (m_nLife <= 0)
//			{
//				//����
//				m_bUninit = true;
//			}
//
//			//��ʊO����
//			if (pos.y - scale.y / 2.0f < SCREEN_HEIGHT_TOP - 30 ||
//				pos.x - scale.x / 2.0f < -25.0f ||
//				pos.x + scale.x / 2.0f > SCREEN_GAMEWIDTH)
//			{
//				//����
//				m_bUninit = true;
//			}
//		}
//
//		//�l�𑫂�
//		m_nCrossingTimeR++;
//	}
//
//	//�ړ��ʂ�ǉ�
//	pos += m_move;
//
//	//�ʒu�̍X�V
//	SetPosition(pos, scale);
//
//	//�ʒu�̍X�V
//	SetScale(scale);
//
//	SetMove(m_move);
//
//	SetLife(m_nLife);
//
//
//	//���ł����ꍇ
//	if (m_bUninit == true)
//	{
//		//�I�������̌Ăяo��
//		Uninit();
//
//		return;
//	}
//
//	//�X�V���̌Ăяo��
//	CBullet::Update();
//
//}
//
////*****************************************************************************
//// �`�揈��
////*****************************************************************************
//void CRotate_Bullet::Draw(void)
//{
//	//�`��̌Ăяo��
//	CBullet::Draw();
//}
