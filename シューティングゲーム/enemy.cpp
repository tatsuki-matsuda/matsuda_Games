//=============================================================================
//
// ���C������ [enemy.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "enemy.h"
#include "lifegauge.h"
#include "bullet.h"
#include "normal_bullet.h"
#include "rotate_bullet.h"
#include "explosion.h"
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
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture[MAX_TEXTURE] = {};			// �e�N�X�`��
D3DXVECTOR3 CEnemy::m_Craetepos[10] = {};							// �ʒu

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CEnemy::CEnemy(int nPriority) :CScene2D(nPriority)
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CEnemy::~CEnemy()
{

}

//*****************************************************************************
// ��������
//*****************************************************************************
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, ENEMYTYPE enemyType)
{
	//���I�m��
	CEnemy* pEnemy;
	pEnemy = new CEnemy;


	//�G����
	pEnemy->SetEnemyType(enemyType); 

	//�����̌Ăяo��
	pEnemy->Init(pos, scale, move);

	//�e�N�X�`���̌Ăяo��
	//for (int nCntTex = 0; nCntTex < 1; nCntTex++)
	//{
	//	pEnemy->BindTexture(m_pTexture[nCntTex]);
	//}

	//�l��Ԃ�
	return pEnemy;

}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move)
{
	//�傫����ݒ�
	m_scale = scale;

	//�ړ���ݒ�
	m_move = move;

	//���
	SetObjType(OBJTYPE_ENEMY);

	//�e�����p�̍��W
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

	//�G�̎�ނɂ���ăQ�[�W�𐶐����邩�ǂ������߂�
	if (m_EnemyType == ENEMYTYPE_REFLECTION)
	{
		//�̗͒l�̐ݒ�
		m_nLife = ENEMY_LIFE;

		//�Q�[�W�̐���
		m_pLifeGauge = CLifeGauge::Create(D3DXVECTOR3(50.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 15.0f, 0.0f), m_nLife);
	}

	if (m_EnemyType == ENEMYTYPE_REFLECTION_UPDAWN)
	{
		//�̗͒l�̐ݒ�
		m_nLife = ENEMY_LIFE;

		//�Q�[�W�̐���
		m_pLifeGauge = CLifeGauge::Create(D3DXVECTOR3(50.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 15.0f, 0.0f), m_nLife);
	}

	if (m_EnemyType == ENEMYTYPE_CROSSING)
	{
		//�̗͒l�̐ݒ�
		m_nLife = ENEMY_LIFE;

		//�Q�[�W�̐���
		m_pLifeGauge = CLifeGauge::Create(D3DXVECTOR3(50.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 15.0f, 0.0f), m_nLife);
	}

	if (m_EnemyType == ENEMYTYPE_NORMAL1)
	{
		//�̗͒l�̐ݒ�
		m_nLife = 50;
	}

	if (m_EnemyType == ENEMYTYPE_NORMAL3_R)
	{
		//�̗͒l�̐ݒ�
		m_nLife = 50;
	}

	if (m_EnemyType == ENEMYTYPE_NORMAL3_L)
	{
		//�̗͒l�̐ݒ�
		m_nLife = 50;
	}

	if (m_EnemyType == ENEMYTYPE_NORMAL4)
	{
		//�̗͒l�̐ݒ�
		m_nLife = 150;
	}

	if (m_EnemyType == ENEMYTYPE_N_WAY1)
	{
		//�̗͒l�̐ݒ�
		m_nLife = 150;
	}

	if (m_EnemyType == ENEMYTYPE_N_WAY2)
	{
		//�̗͒l�̐ݒ�
		m_nLife = 150;
	}

	////�̗͒l�̐ݒ�
	//m_nLife = ENEMY_LIFE;

	//�����Ă邩�ǂ���
	m_bUninit = false;

	//�����Ԋu�J�E���g�̏����l
	m_nCntCrossingTime = 0;

	//�����n�߃J�E���g�̏����l
	m_nBulletStartCnt = 0;

	m_nCntTime = 0;

	//�G�o���J�E���g
	m_nEnemyAppearanceCnt = 0;

	//�G���Ō�o���J�E���g
	m_nEnemyCnt = 0;

	//�G�ړ��J�E���g
	m_nEnemymoveCnt = 0;

	m_posDeath = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�@�o�����̗̑͂�ۑ�
	m_nMaxLife = m_nLife;

	//�������̌Ăяo��
	CScene2D::Init(pos, scale);

	//�l��Ԃ�
	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CEnemy::Uninit(void)
{
	//�I���̌Ăяo��
	CScene2D::Uninit();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CEnemy::Update(void)
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

	m_nEnemyAppearanceCnt++;


	//�����e�J�E���g�𑫂�
	m_nCntCrossingTime++;

	//�G�̎�ނ��ʏ�e1�����G�̏ꍇ
	if (m_EnemyType == ENEMYTYPE_NORMAL1)
	{
		BindTexture(m_pTexture[3]);

		if ((pos.y + m_scale.x / 2.0) <= 0.0f&&m_nEnemymoveCnt <= 0)
		{
			m_move.y *= 1;
		}

		if ((pos.y + m_scale.x / 2.0) >= 300.0f&&m_nEnemymoveCnt <= 20)
		{
			m_move.y = 0;

			if ((pos.y + m_scale.x / 2.0) >= 0.0f || (pos.y + m_scale.x / 2.0) <= SCREEN_GAMEHEIGHT)
			{
				//�J�E���g
				if (m_timer % 20 == 0)
				{
					for (int nCnt = 0; nCnt < 20; nCnt++)
					{
						//�S���ʒe�̐���
						CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(20, 20, 0),
							D3DXVECTOR3(sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)10)) * 5, cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)10)) * 5, 0),
							D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_NORMAL,CBullet::INFOTYPE_1);

						
					}

					m_nEnemymoveCnt++;
				}
			}
		}

		if (m_nEnemymoveCnt >= 20)
		{

			if (m_timer % 1200 == 0)
			{
				m_move.y = -2;
			}

			if ((pos.y + m_scale.x / 2.0) <= 0.0f)
			{
				//�G�̏���
				m_bUninit = true;
			}
		}

		//�̗͂�0�ȉ��ɂȂ����ꍇ
		if (m_nLife <= 0)
		{
			//�G�̏���
			m_bUninit = true;

			Uninit();

			//�����̐���
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(200);

			if (m_bUninit = true)
			{
				m_nEnemyCnt++;
			}

			/*if (m_nEnemyAppearanceCnt == 3000)
			{

				CEnemy::Create(D3DXVECTOR3(300, 200, 0), D3DXVECTOR3(100, 100, 0), D3DXVECTOR3(0, 0, 0), CEnemy::ENEMYTYPE_REFLECTION);

			}
			else if (m_nEnemyCnt >= 4 && m_nEnemyAppearanceCnt >= 2500)
			{
				CEnemy::Create(D3DXVECTOR3(300, 200, 0), D3DXVECTOR3(100, 100, 0), D3DXVECTOR3(0, 0, 0), CEnemy::ENEMYTYPE_REFLECTION);

				m_nEnemyCnt = 0;
			}*/


			return;
		}

		
	}

	//�G�̎�ނ��ʏ�e2�����G�̏ꍇ
	if (m_EnemyType == ENEMYTYPE_NORMAL2)
	{
		//if ((pos.y + m_scale.x / 2.0) <= 0.0f&&m_nEnemymoveCnt <= 0)
		//{
		//	m_move.y *= 1;
		//}

		//for (int nCnt = 0; nCnt < 2; nCnt++)
		//{
		//	if ((pos.y + m_scale.x / 2.0) >= 300.0f - (70 * (float)nCnt) && m_nEnemymoveCnt <= 20)
		//	{
		//		m_move.y = 0;

		//		//�J�E���g
		//		if (m_timer % 20 == 0)
		//		{
		//			////�z�[�~���O�e�̐���
		//			//CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(20, 20, 0),
		//			//	D3DXVECTOR3(sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)10)) * 5, cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)10)) * 5, 0),
		//			//	D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_HOMING, CBullet::INFOTYPE_1);

		//			m_nEnemymoveCnt++;
		//		}
		//	}
		//}

		//if (m_nEnemymoveCnt >= 20)
		//{

		//	if (m_timer % 120 == 0)
		//	{
		//		m_move.y = -2;
		//	}

		//	if ((pos.y + m_scale.x / 2.0) <= 0.0f)
		//	{
		//		//�G�̏���
		//		m_bUninit = true;
		//	}
		//}

		////�̗͂�0�ȉ��ɂȂ����ꍇ
		//if (m_nLife <= 0)
		//{
		//	//�G�̏���
		//	m_bUninit = true;

		//	Uninit();

		//	//�����̐���
		//	CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

		//	pScore->AddScore(200);

		//	return;
		//}
	}

	//�G�̎�ނ��E������ʏ�e3�����G�̏ꍇ
	if (m_EnemyType == ENEMYTYPE_NORMAL3_R)
	{
		//�G�̃e�N�X�`��
		BindTexture(m_pTexture[0]);

		//�J�E���g
		if (m_timer % 8 == 0)
		{
			if (m_nCntTime <= 6)
			{
				//�e�̐���
				CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(25, 25, 0),
					D3DXVECTOR3(m_move.x * -0.2f, m_move.y*3.0f, 0), D3DXVECTOR3(0, 0, 0),
					CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_NORMAL, CBullet::INFOTYPE_3);

				//�e�̐���
				CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(25, 25, 0),
					D3DXVECTOR3(m_move.x * -0.2f, m_move.y*-2.0f, 0), D3DXVECTOR3(0, 0, 0),
					CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_NORMAL, CBullet::INFOTYPE_3);

				m_nCntTime++;
			}
		}

		if (m_timer % 150 == 0)
		{
			m_nCntTime = 0;
		}

		if ((pos.y + m_scale.x / 2.0) >= SCREEN_HEIGHT|| (pos.x + m_scale.x / 2.0) <= 0.0f)
		{
			//�G�̏���
			m_bUninit = true;
		}
		//�̗͂�0�ȉ��ɂȂ����ꍇ
		else if (m_nLife <= 0)
		{
			//�G�̏���
			m_bUninit = true;

			//�����̐���
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(200);

			//�I�������̌Ăяo��
			Uninit();

			return;
		}
	}

	//�G�̎�ނ���������ʏ�e3�����G�̏ꍇ
	if (m_EnemyType == ENEMYTYPE_NORMAL3_L)
	{
		//�G�̃e�N�X�`��
		BindTexture(m_pTexture[0]);

		//�J�E���g
		if (m_timer % 8 == 0)
		{
			if (m_nCntTime <= 6)
			{
				//�e�̐���
				CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(25, 25, 0),
					D3DXVECTOR3(m_move.x * -0.2f, m_move.y*3.0f, 0), D3DXVECTOR3(0, 0, 0),
					CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_NORMAL, CBullet::INFOTYPE_3);

				//�e�̐���
				CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(25, 25, 0),
					D3DXVECTOR3(m_move.x * -0.2f, m_move.y*-2.0f, 0), D3DXVECTOR3(0, 0, 0),
					CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_NORMAL,CBullet::INFOTYPE_3);

				m_nCntTime++;
			}
		}

		if (m_timer % 150 == 0)
		{
			m_nCntTime = 0;
		}

		if ((pos.y + m_scale.x / 2.0) >= SCREEN_HEIGHT || (pos.x + m_scale.x / 2.0) >= SCREEN_GAMEWIDTH)
		{
			//�G�̏���
			m_bUninit = true;
		}

		//�̗͂�0�ȉ��ɂȂ����ꍇ
		if (m_nLife <= 0)
		{
			//�G�̏���
			m_bUninit = true;

			//�����̐���
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(200);

			//�I�������̌Ăяo��
			Uninit();

			return;
		}
	}

	//�G�̎�ނ���������ʏ�e3�����G�̏ꍇ
	if (m_EnemyType == ENEMYTYPE_NORMAL4)
	{


		if (pos.y >= 100.0f)
		{
			m_move.x *= 0.0f;

			//�J�E���g
			if (m_timer % 30 == 0)
			{
				if (m_nCntTime <= 5)
				{
					//�e�̐���
					CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(25, 25, 0),
						D3DXVECTOR3(0.0f, m_move.y*2.0f, 0), D3DXVECTOR3(0, 0, 0),
						CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_NORMAL, CBullet::INFOTYPE_1);

					m_nCntTime++;
				}
			}
		}

		if (m_nCntTime <= 5)
		{
			m_move.x = 3.0f;
		}

		//�J�E���g
		if (m_timer % 100 == 0)
		{
			m_nCntTime = 0;
		}

		if ((pos.y + m_scale.x / 2.0) >= SCREEN_HEIGHT || (pos.x + m_scale.x / 2.0) >= SCREEN_GAMEWIDTH)
		{
			//�G�̏���
			m_bUninit = true;
		}

		//�̗͂�0�ȉ��ɂȂ����ꍇ
		if (m_nLife <= 0)
		{
			//�G�̏���
			m_bUninit = true;

			//�����̐���
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(200);

			//�I�������̌Ăяo��
			Uninit();

			return;
		}
	}

	//�G�̎�ނ��Ǐ]�e�����G�̏ꍇ
	if (m_EnemyType == ENEMYTYPE_HOMING)
	{
		////�ړ�
		//if ((pos.x + m_scale.x / 2.0f) >= SCREEN_WIDTH - 400)
		//{
		//	m_move.x *= -1;
		//}

		//if (pos.x - m_scale.x / 2.0f <= 0.0f)
		//{
		//	m_move.x *= -1;
		//}

		////�J�E���g
		//if (m_timer % 120 == 0)
		//{
		//	//�e�̐���
		//	CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 50, pos.z), D3DXVECTOR3(20, 20, 0), D3DXVECTOR3(0, 10, 0),
		//		D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_HOMING, CBullet::INFOTYPE_1);
		//}

		////�̗͂�0�ȉ��ɂȂ����ꍇ
		//if (m_nLife <= 0)
		//{
		//	//�G�̏���
		//	m_bUninit = true;

		//	Uninit();

		//	//�����̐���
		//	CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

		//	pScore->AddScore(200);

		//	return;
		//}
	}

	//�G�̎�ނ��S���ʌ����e�����G�̏ꍇ
	if (m_EnemyType == ENEMYTYPE_CROSSING)
	{
		//�G�̃e�N�X�`��
		BindTexture(m_pTexture[4]);

		m_Craetepos[0] = D3DXVECTOR3(pos.x - 10, pos.y, 0);
		m_Craetepos[1] = D3DXVECTOR3(pos.x + 13, pos.y, 0);


	/*	SetLife(300);*/
		//�ړ�
		if ((pos.x + m_scale.x / 2.0f) >= SCREEN_WIDTH - 930)
		{
			m_move.x *= -1;
		}

		if (pos.x - m_scale.x / 2.0f <= 430)
		{
			m_move.x *= -1;
		}

		//�J�E���g
		if (m_timer % 120 == 0)
		{
			//�G�̈ʒu���Q�Ƃ��Ēe�𐶐�
			OnDiffuesPos(m_Craetepos[m_nCntTime % 2 == 0], m_move);

			m_nCntTime++;

			//���Ԍo�߂Œe�𔭎˂���Ԋu���Z���Ȃ�
			if (m_nCntTime >= 5 && m_nCntTime <= 9)
			{
				//�e�̐�������
				m_timer = 30;
			}

			if (m_nCntTime >= 10 && m_nCntTime <= 19)
			{
				//�e�̐�������
				m_timer = 60;
			}

			if (m_nCntTime >= 20)
			{
				//�e�̐�������
				m_timer = 80;
			}

		}

		//�̗͂�0�ȉ��ɂȂ����ꍇ
		if (m_nLife <= 0)
		{
			//�G�̏���
			m_bUninit = true;

			Uninit();

			//�����̐���
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(1500);

			return;
		}

	
	}

	//�G�̎�ނ��S���ʔ��˒e�����G�̏ꍇ
	if (m_EnemyType == ENEMYTYPE_REFLECTION)
	{

		//�G�̃e�N�X�`��
		BindTexture(m_pTexture[4]);

		//�^�C�}�[�őS���ʔ��˒e�𐶐�
		if (m_timer % 280 == 0)
		{

			//�e�����p�̍��W
			m_Craetepos[0] = D3DXVECTOR3(500.0f, 250.0f, 0.0f);
			m_Craetepos[1] = D3DXVECTOR3(250.0f, 100.0f, 0.0f);
			m_Craetepos[2] = D3DXVECTOR3(200.0f, 200.0f, 0.0f);
			m_Craetepos[3] = D3DXVECTOR3(250.0f, 300.0f, 0.0f);
			m_Craetepos[4] = D3DXVECTOR3(550.0f, 150.0f, 0.0f);
			m_Craetepos[5] = D3DXVECTOR3(450.0f, 120.0f, 0.0f);
			m_Craetepos[6] = D3DXVECTOR3(350.0f, 180.0f, 0.0f);
			m_Craetepos[7] = D3DXVECTOR3(550.0f, 300.0f, 0.0f);
			m_Craetepos[8] = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
			m_Craetepos[9] = D3DXVECTOR3(520.0f, 250.0f, 0.0f);

			//�G�̈ʒu���Q�Ƃ��Ēe�𐶐�
			OnDiffuesPos(m_Craetepos[rand() % 10], m_move);

			//�����^�C���J�E���g
			m_nCntTime++;
			
			//���Ԍo�߂Œe�𔭎˂���Ԋu���Z���Ȃ�
			if ((m_nCntTime >= 10 && m_nCntTime <= 17) ||( (float)m_nLife <= (float)m_nMaxLife *0.75f&& (float)m_nLife >= (float)m_nMaxLife *0.51f))
			{
				//�e�̐�������
				m_timer = 100;
			}

			if ((m_nCntTime >= 18 && m_nCntTime <= 25) || ((float)m_nLife <= (float)m_nMaxLife *0.5f && (float)m_nLife >= (float)m_nMaxLife *0.26f))
			{
				//�e�̐�������
				m_timer = 160;
			}

			if (m_nCntTime >= 26 || ((float)m_nLife <= (float)m_nMaxLife *0.25f))
			{
				//�e�̐�������
				m_timer = 220;
			}
		}

		//�̗͂�0�ȉ��ɂȂ����ꍇ
		if (m_nLife <= 0)
		{
			//�G�̏���
			m_bUninit = true;

			//�I�������̌Ăяo��
			Uninit();

			m_posDeath = pos;

			//�����̐���
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			//�X�R�A�̉��Z
			pScore->AddScore(2000);

			//�㉺���˒e�G�̐���
			Create(m_posDeath, D3DXVECTOR3(100, 100, 0), D3DXVECTOR3(0, 0, 0),ENEMYTYPE_REFLECTION_UPDAWN);

			return;
		}
	}

	//�G�̎�ނ��㉺���˒e�����G�̏ꍇ
	if (m_EnemyType == ENEMYTYPE_REFLECTION_UPDAWN)
	{
		//�G�̃e�N�X�`��
		BindTexture(m_pTexture[4]);

		//�ړ�
		if ((pos.x + m_scale.x / 2.0f) >= SCREEN_WIDTH - 400)
		{
			m_move.x *= -1;
		}

		if (pos.x - m_scale.x / 2.0f <= 0.0f)
		{
			m_move.x *= -1;
		}

		//���W�̐ݒ�
		if (m_timer % 130 == 0)
		{
			
			m_Craetepos[0] = D3DXVECTOR3(pos.x, pos.y, 0);
			m_Craetepos[1] = D3DXVECTOR3(pos.x + 15, pos.y, 0);

			OnDiffuesPos(m_Craetepos[rand() % 2], m_move);

		}

		m_nBulletStartCnt++;

		//�̗͂�0�ȉ��ɂȂ����ꍇ
		if (m_nLife <= 0)
		{
			//�G�̏���
			m_bUninit = true;

			Uninit();

			//�����̐���
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(2000);

			m_nBulletStartCnt = 0;

			return;
		}
	}

	//�G�̎�ނ��S���ʐ܂�Ԃ��e�����G�̏ꍇ
	if (m_EnemyType == ENEMYTYPE_TURN)
	{

		//�G�̃e�N�X�`��
		BindTexture(m_pTexture[4]);

		//�ړ�
		if ((pos.x + m_scale.x / 2.0f) >= SCREEN_WIDTH - 400)
		{
			m_move.x *= -1;
		}

		if (pos.x - m_scale.x / 2.0f <= 0.0f)
		{
			m_move.x *= -1;
		}

		if (m_timer % 120 == 0)
		{
			for (int nCnt = 0; nCnt < 20; nCnt++)
			{
				//�S���ʐ܂�Ԃ��e�̐���
				CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(20, 20, 0),
					D3DXVECTOR3(sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)10)) * 4, cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)10)) * 4, 0),
					D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_TURN, CBullet::INFOTYPE_1);
			}
		}

		//�̗͂�0�ȉ��ɂȂ����ꍇ
		if (m_nLife <= 0)
		{
			//�G�̏���
			m_bUninit = true;

			Uninit();

			//�����̐���
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(1200);

			return;
		}
	}

	//�G�̎�ނ�n_way1�e�����G�̏ꍇ
	if (m_EnemyType == ENEMYTYPE_N_WAY1)
	{
		//�ړ�
		if ((pos.x + m_scale.x / 2.0f) >= SCREEN_WIDTH - 400)
		{
			m_move.x *= -1;
		}

		if (pos.x - m_scale.x / 2.0f <= 0.0f)
		{
			m_move.x *= -1;
		}

		//��Ԓ[�̊p�x�v�Z
		float fAngle = (D3DX_PI / 8) + (N_WAY_CREATE - 1) / 2 * (D3DX_PI / -7);

		//�^�C�}�[�����̒l��0�ɂȂ�ꍇ
		if (m_timer % 20 == 0)
		{
			//�l��n_way�e������������܂ŁA�p�x���v�Z���Ēe�𐶐�
			for (int nCntway = 0; nCntway < N_WAY_CREATE; nCntway++, fAngle += D3DX_PI/12)
			{


			//n_way�e�̐���
			CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(20, 20, 0), 
				D3DXVECTOR3(sinf(fAngle) * 4, cosf(fAngle) * 4, 0),
				D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_N_WAY1, CBullet::INFOTYPE_2);
			}
		}

		//�̗͂�0�ȉ��ɂȂ����ꍇ
		if (m_nLife <= 0)
		{
			//�G�̏���
			m_bUninit = true;

			Uninit();

			//�����̐���
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(500);

			return;
		}
	}

	//�G�̎�ނ�n_way2�e�����G�̏ꍇ
	if (m_EnemyType == ENEMYTYPE_N_WAY2)
	{
		//�G�̃e�N�X�`��
		BindTexture(m_pTexture[4]);

		if ((pos.y + m_scale.x / 2.0) <= 0.0f&&m_nEnemymoveCnt <= 0)
		{
			m_move.y *= 1;
		}

		if ((pos.y + m_scale.x / 2.0) >= 250.0f)
		{
			m_move.y = 0;

			//�^�C�}�[�����̒l��0�ɂȂ�ꍇ
			if (m_timer % 120 == 0)
			{
				CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(25, 25, 0),
					D3DXVECTOR3(0, 2, 0), D3DXVECTOR3(0, 0, 0),
					CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_N_WAY2, CBullet::INFOTYPE_1);
			}

			//�^�C�}�[�����̒l��0�ɂȂ�ꍇ
			if (m_timer % 80 == 0)
			{
				m_nEnemymoveCnt++;
			}
	
			//�J�E���g�����l������܂�
			if (m_nEnemymoveCnt >= 8)
			{	
				//�^�C�}�[�����̒l��0�ɂȂ�ꍇ
				if (m_timer % 120 == 0)
				{
					CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(25, 25, 0),
						D3DXVECTOR3(0, 2, 0), D3DXVECTOR3(0, 0, 0),
						CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_N_WAY2, CBullet::INFOTYPE_1);
				}
					//�ړ�
					m_move.y = -2;

				if ((pos.y + m_scale.x / 2.0) <= 0.0f)
				{
					//�G�̏���
					m_bUninit = true;
				}
			}

			//�̗͂�0�ȉ��ɂȂ����ꍇ
			if (m_nLife <= 0)
			{
				//�G�̏���
				m_bUninit = true;

				Uninit();

				//�����̐���
				CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

				pScore->AddScore(500);

				return;
			}
		}
	}

	//�ړ����Z
	pos += m_move;

	//�ʒu�̍X�V
	SetPosition(pos, m_scale);

	//�傫��
	SetScale(m_scale);

	if (m_bUninit == true)
	{
		Uninit();

		m_pLifeGauge = NULL;
	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CEnemy::Draw(void)
{
	//�`��̌Ăяo��
	CScene2D::Draw();
}

//*****************************************************************************
// �e�N�X�`���ǂݍ��ݏ���
//*****************************************************************************
void CEnemy::Load(void)
{
	//�f�o�C�X�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy_Keima.png", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy_Kasya.png", &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy_Ginsyou.png", &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy_Kinsyou.png", &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy_Ousyou.png", &m_pTexture[4]);
}

//*****************************************************************************
// �e�N�X�`���j������
//*****************************************************************************
void CEnemy::Unload(void)
{
	for (int nCntTex = 0; nCntTex < 5; nCntTex++)
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
// �G��񏈗�
//*****************************************************************************
CEnemy::ENEMYTYPE CEnemy::GetEnemyType(void)
{
	return m_EnemyType;
}

//*****************************************************************************
// �G���̐ݒ菈��
//*****************************************************************************
void CEnemy::SetEnemyType(ENEMYTYPE enemyType)
{
	m_EnemyType = enemyType;
}

//*****************************************************************************
// �e�̈ʒu��������
//*****************************************************************************
void CEnemy::OnDiffuesPos(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// Create���̏��
	// 1 pos, 2 scale. 3 move, 4 rot, 5 bulletType, 6 attackType, 7 infoType

	//��]�ʏ�e�������̏���
	//if (m_EnemyType == ENEMYTYPE_NORMAL2)
	//{

	//	for (int nCnt = 0; nCnt < 40; nCnt++)
	//	{

	//		//�E�����e�̐���
	//		CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(25, 25, 0),
	//			D3DXVECTOR3(sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)20)) * 4, cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)20)) * 4, 0),
	//			D3DXVECTOR3(0, (float)nCnt, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_NORMAL, CBullet::INFOTYPE_2);
	//	}
	//}

	//�S���ʌ����e�������̏���
	if (m_EnemyType == ENEMYTYPE_CROSSING)
	{
		
		for (int nCnt = 0; nCnt < 40; nCnt++)
		{
			//�������e�̐���
			CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(25, 25, 0),
				D3DXVECTOR3(sinf(D3DX_PI * 0.5f * ((float)nCnt / (float)10)) * 4, cosf(D3DX_PI * 0.5f * ((float)nCnt / (float)10)) * 4, 0),
				D3DXVECTOR3(0, (float)nCnt, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_CROSSING, CBullet::INFOTYPE_1);

			//�E�����e�̐���
			CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(25, 25, 0),
				D3DXVECTOR3(sinf(D3DX_PI * 0.5f * ((float)nCnt / (float)10)) * 4, cosf(D3DX_PI * 0.5f * ((float)nCnt / (float)10)) * 4, 0),
				D3DXVECTOR3(10, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_CROSSING, CBullet::INFOTYPE_2);
		}
	}

	//�S���ʔ��˒e�������̏���
	if (m_EnemyType == ENEMYTYPE_REFLECTION)
	{
		for (int nCnt = 0; nCnt < 40; nCnt++)
		{
			//�S���ʒe�̐���
			CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(20, 20, 0),
				D3DXVECTOR3(sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)20)) * 3, cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)20)) * 3, 0),
				D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_REFLECTION, CBullet::INFOTYPE_1);
		}
	}

	//�㉺���˒e�������̏���
	if (m_EnemyType == ENEMYTYPE_REFLECTION_UPDAWN)
	{
		//�ʒu���Q�Ƃ����ꂽ�ʒu����e�𐶐�
		float fLength = 400.0f + rand() % 30;

		if (m_nBulletStartCnt >= 150)
		{
			for (int nCnt = 0; nCnt < 180; nCnt++)
			{
				//���˒e�̐���
				CBullet::Create(D3DXVECTOR3((pos.x) + fLength * sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)) * 2, -250 + fLength *  cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)), pos.z) *1.0f,
					D3DXVECTOR3(20, 20, 0), D3DXVECTOR3(sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)) * 6, cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)) * 6, 0),
					D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_REFLECTION, CBullet::INFOTYPE_2);

				//���˒e�̐���
				CBullet::Create(D3DXVECTOR3((pos.x) + fLength * sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)) * 2, SCREEN_HEIGHT + 50 + fLength *  cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)), pos.z) *1.0f,
					D3DXVECTOR3(20, 20, 0), D3DXVECTOR3(sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)) * 6, cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)) * 6, 0),
					D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_REFLECTION, CBullet::INFOTYPE_2);
			}
		}
	}
}

//*****************************************************************************
// �e�N�X�`����񏈗�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemy::GetTexture(int nCntTex)
{
	return m_pTexture[nCntTex];
}
