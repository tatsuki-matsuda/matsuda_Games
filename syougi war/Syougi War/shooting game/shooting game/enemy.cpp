//=============================================================================
//
// ���C������ [enemy.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "enemy.h"
#include "sound.h"
#include "lifegauge.h"
#include "bullet.h"
#include "normal_bullet.h"
#include "rotate_bullet.h"
#include "explosion.h"
#include "scene.h"
#include "scene2D.h"
#include "Life.h"
#include "LifeBoss.h"
#include "fade.h"
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
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, ENEMYTYPE enemyType,BOSSTYPE BossType)
{
	//���I�m��
	CEnemy* pEnemy;
	pEnemy = new CEnemy;

	//�G����
	pEnemy->SetEnemyType(enemyType); 

	//�G����
	pEnemy->SetBossType(BossType);

	//�����̌Ăяo��
	pEnemy->Init(pos, scale, move);

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

	//�G�̏��
	SetEnemyState(ENEMYSTATE_NORMAL);

	//�������W
	m_Craetepos[0] = D3DXVECTOR3(500.0f, 250.0f, 0.0f);
	m_Craetepos[1] = D3DXVECTOR3(150.0f, 180.0f, 0.0f);
	m_Craetepos[2] = D3DXVECTOR3(200.0f, 200.0f, 0.0f);
	m_Craetepos[3] = D3DXVECTOR3(250.0f, 170.0f, 0.0f);
	m_Craetepos[4] = D3DXVECTOR3(550.0f, 100.0f, 0.0f);
	m_Craetepos[5] = D3DXVECTOR3(450.0f, 180.0f, 0.0f);
	m_Craetepos[6] = D3DXVECTOR3(340.0f, 130.0f, 0.0f);
	m_Craetepos[7] = D3DXVECTOR3(490.0f, 130.0f, 0.0f);
	m_Craetepos[8] = D3DXVECTOR3(300.0f, 200.0f, 0.0f);
	m_Craetepos[9] = D3DXVECTOR3(120.0f, 250.0f, 0.0f);

	//�l�����݂��郉���_���Ȉʒu���{�X�̈ʒu�Ƃ��ĕۑ�
	m_posBoss = m_Craetepos[rand() % 10];

	//�G���G�̗̑͊Ǘ�//

	//�ʏ�e1�����G
	if (m_EnemyType == ENEMYTYPE_NORMAL1)
	{
		//�̗͒l�̐ݒ�
		m_nLife = ENEMY_LIFE + 100;
	}

	//�ʏ�e3�����G
	if (m_EnemyType == ENEMYTYPE_NORMAL3_R)
	{
		//�̗͒l�̐ݒ�
		m_nLife = ENEMY_MINLIFE;
	}

	//�ʏ�e3�����G
	if (m_EnemyType == ENEMYTYPE_NORMAL3_L)
	{
		//�̗͒l�̐ݒ�
		m_nLife = ENEMY_MINLIFE;
	}

	//�ʏ�e4R�����G
	if (m_EnemyType == ENEMYTYPE_NORMAL4_R)
	{
		//�̗͒l�̐ݒ�
		m_nLife = ENEMY_MINLIFE - 20;
	}

	//�ʏ�e4L�����G
	if (m_EnemyType == ENEMYTYPE_NORMAL4_L)
	{
		//�̗͒l�̐ݒ�
		m_nLife = ENEMY_MINLIFE - 20;
	}

	//N_WAY�e�����G
	if (m_EnemyType == ENEMYTYPE_N_WAY1)
	{
		//�̗͒l�̐ݒ�
		m_nLife = ENEMY_LIFE + 100;
	}

	//N_WAY�e�����G
	if (m_EnemyType == ENEMYTYPE_N_WAY2)
	{
		//�̗͒l�̐ݒ�
		m_nLife = ENEMY_LIFE + 100;
	}

	//�ːi����G
	if (m_EnemyType == ENEMYTYPE_RUSH)
	{
		//�̗͒l�̐ݒ�
		m_nLife = ENEMY_MINLIFE + 30;
	}


	//�{�X�̗̑͊Ǘ��y�уQ�[�W����//

	//���˒e�����{�X
	if (m_BossType == BOSSTYPE_REFLECTION_ALL)
	{
		//�̗͒l�̐ݒ�
		m_nLife = BOSS_LIFE;

		//�Q�[�W�̐���
		m_pLifeGauge = CLifeGauge::Create(D3DXVECTOR3(80.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 15.0f, 0.0f), m_nLife);
	}

	//�㉺���˒e�����{�X
	if (m_BossType == BOSSTYPE_REFLECTION_VERTICAL)
	{
		//�̗͒l�̐ݒ�
		m_nLife = BOSS_MINLIFE;

		//�Q�[�W�̐���
		m_pLifeGauge = CLifeGauge::Create(D3DXVECTOR3(80.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 15.0f, 0.0f), m_nLife);
	}

	//�����e�����{�X
	if (m_BossType == BOSSTYPE_CROSSING)
	{
		//�̗͒l�̐ݒ�
		m_nLife = BOSS_LIFE;

		//�Q�[�W�̐���
		m_pLifeGauge = CLifeGauge::Create(D3DXVECTOR3(80.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 15.0f, 0.0f), m_nLife);
	}

	//�Q���e�e�����{�X
	if (m_BossType == BOSSTYPE_SPIRAL)
	{
		//�̗͒l�̐ݒ�
		m_nLife = BOSS_LASTLIFE;

		//�Q�[�W�̐���
		m_pLifeGauge = CLifeGauge::Create(D3DXVECTOR3(80.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 15.0f, 0.0f), m_nLife);
	}

	//�����Ă邩�ǂ���
	m_bUninit = false;

	//�����Ԋu�J�E���g�̏����l
	m_nCntCrossingTime = 0;

	//�����n�߃J�E���g�̏����l
	m_nBulletStartCnt = 0;

	//���ˊԊu
	m_nCntTime = 0;

	//�����J�E���g
	m_nCntMadness = 0;

	//���˃J�E���g
	m_nCntBullet = 0;

	//����
	m_fLength = 0;

	//�t�F�[�Y���
	m_PhaseType = PHASETYPE_NONE;

	//�G�o���J�E���g
	m_nEnemyAppearanceCnt = 0;

	//�G���Ō�o���J�E���g
	m_nEnemyCnt = 0;

	//�G�ړ��J�E���g
	m_nEnemymoveCnt = 0;

	//�G�̐F
	m_nCntColor = 0;

	//�G���S���̈ʒu��ۑ�
	m_posDeath = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�ʏ�G�̈ړ��J�E���g
	m_nNormalEnemyMove=0;

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

	//�X�R�A�̎擾
	CLifeBoss *pLifeboss;
	pLifeboss = CGame::GetBossLifeCnt();

	EnemyState();

	//�Ίp���̒���
	m_fangle = sqrtf(15 * 15 + 15 * 15);

	//�Ίp���̊p�x
	float fAngle = atan2f(5, 5);

	//���ˎ���
	m_timer++;

	//�T�E���h�̃|�C���^
	CSound *pSound = CManager::GetSound();

	m_nCntColor++;

	m_nEnemyAppearanceCnt++;

	//�����蔻��
	OnCollision();

	//�����e�J�E���g�𑫂�
	m_nCntCrossingTime++;

	// �G���G�̍s������//

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
				if (m_timer % 30 == 0)
				{
					for (int nCnt = 0; nCnt < 20; nCnt++)
					{

						//�S���ʒe�̐���
						CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(20, 20, 0),
							D3DXVECTOR3(sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)10)) * 3, cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)10)) * 3, 0),
							D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_NORMAL,CBullet::INFOTYPE_1);

						
					}

					m_nEnemymoveCnt++;
				}
			}
		}

		if (m_nEnemymoveCnt >= 15)
		{

			if (m_timer % 150 == 0)
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

			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

			pScore->AddScore(7000);

			if (m_bUninit = true)
			{
				m_nEnemyCnt++;
			}

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

			pScore->AddScore(1000);

			//������
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

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

			pScore->AddScore(1000);

			//������
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

			//�I�������̌Ăяo��
			Uninit();

			return;
		}
	}

	//�G�̎�ނ���������ʏ�e4�����G�̏ꍇ
	if (m_EnemyType == ENEMYTYPE_NORMAL4_R)
	{
		BindTexture(m_pTexture[0]);
		//m_move.x = 3.0f;

		// �ʏ�G�ړ��J�E���g
		m_nNormalEnemyMove++;

		//�ړ��l��ۑ�
		if (m_nNormalEnemyMove < 199)
		{
			m_moveSave = m_move;
		}

		//�ړ��J�E���g�����̒l�𒴂���܂�
		if (m_nNormalEnemyMove > 200)
		{
			m_move.y = 0.0f;

			m_move.x = 0.0f;

			//���˃^�C�~���O
			if (m_timer % 15 == 0)
			{		
				//�e�̐���
				CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(25, 25, 0),
					D3DXVECTOR3(0.0f, 2.0f, 0), D3DXVECTOR3(0, 0, 0),
					CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_NORMAL, CBullet::INFOTYPE_1);

				//���˃J�E���g
				m_nCntBullet++;
			}

			//���˃J�E���g�����̒l�𒴂���܂�
			if (m_nCntBullet > 5)
			{
				//�J�E���g���[����
				m_nNormalEnemyMove = 0;

				m_nCntBullet = 0;

				m_move.y += 1.4f;

				if (m_moveSave.x > 1.0f)
				{
					m_move.x += 2.0f;
					
				}

				if (m_moveSave.x < 1.0f)
				{
					m_move.x += -2.0f;
				}
			}
		}

		//�ړ��J�E���g�����̒l�𒴂���܂�
		if (m_nNormalEnemyMove < 199)
		{
			//�G�����̈ʒu�𒴂���܂�
			if ((pos.x - m_scale.x / 2.0f) < 20.0f)
			{
				//������v�Z
				pos.x = m_scale.x / 2.0f + 20.0f;

				//�ړ�
				m_move.x *= -0.9f;

				//������
				SetPosition(pos, m_scale);
			}
			else if ((pos.x + m_scale.x / 2.0f) > SCREEN_GAMEWIDTH / 2.0f)
			{

				//������v�Z
				m_move.x *= -0.9f;

				//�ړ�
				pos.x = SCREEN_GAMEWIDTH / 2.0f - m_scale.x / 2.0f;

				//������
				SetPosition(pos, m_scale);
			}
		}

		//���ɍs���܂�
		if ((pos.y + m_scale.y / 2.0f) >= SCREEN_HEIGHT)
		{
			//�G����
			m_bUninit = true;
		}

		//�̗͂�0�ȉ��ɂȂ����ꍇ
		if (m_nLife <= 0)
		{
			//�G�̏���
			m_bUninit = true;

			//�����̐���
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(1800);

			//������
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

			//�I�������̌Ăяo��
			Uninit();

			return;
		}
	}

	//�G�̎�ނ���������ʏ�e4�����G�̏ꍇ
	if (m_EnemyType == ENEMYTYPE_NORMAL4_L)
	{
		BindTexture(m_pTexture[0]);
		//m_move.x = 3.0f;

		// �ʏ�G�ړ��J�E���g
		m_nNormalEnemyMove++;

		//�ړ��l��ۑ�
		if (m_nNormalEnemyMove < 199)
		{
			m_moveSave = m_move;
		}

		//�ړ��J�E���g�����̒l�𒴂���܂�
		if (m_nNormalEnemyMove > 200)
		{
			m_move.y = 0.0f;

			m_move.x = 0.0f;

			//���˃^�C�~���O
			if (m_timer % 15 == 0)
			{
				//�e�̐���
				CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(25, 25, 0),
					D3DXVECTOR3(0.0f, 2.0f, 0), D3DXVECTOR3(0, 0, 0),
					CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_NORMAL, CBullet::INFOTYPE_1);

				//���˃J�E���g
				m_nCntBullet++;
			}

			//���˃J�E���g�����̒l�𒴂���܂�
			if (m_nCntBullet > 5)
			{
				//�J�E���g���[����
				m_nNormalEnemyMove = 0;

				m_nCntBullet = 0;

				m_move.y += 1.4f;

				if (m_moveSave.x > 1.0f)
				{
					m_move.x += 2.0f;

				}

				if (m_moveSave.x < 1.0f)
				{
					m_move.x += -2.0f;
				}
			}
		}

		//�ړ��J�E���g�����̒l�𒴂���܂�
		if (m_nNormalEnemyMove < 199)
		{
			//�G�����̈ʒu�𒴂���܂�
			if ((pos.x - m_scale.x / 2.0f) < SCREEN_GAMEWIDTH / 2.2f)
			{
				//������v�Z
				pos.x = m_scale.x / 2.0f + SCREEN_GAMEWIDTH / 2.2f;

				//�ړ�
				m_move.x *= -0.9f;

				//������
				SetPosition(pos, m_scale);
			}
			else if ((pos.x + m_scale.x / 2.0f) > SCREEN_GAMEWIDTH )
			{

				//������v�Z
				m_move.x *= -0.9f;

				//�ړ�
				pos.x = SCREEN_GAMEWIDTH - m_scale.x / 2.0f;

				//������
				SetPosition(pos, m_scale);
			}
		}

		//���ɍs���܂�
		if ((pos.y + m_scale.y / 2.0f) >= SCREEN_HEIGHT)
		{
			//�G����
			m_bUninit = true;
		}

		//�̗͂�0�ȉ��ɂȂ����ꍇ
		if (m_nLife <= 0)
		{
			//�G�̏���
			m_bUninit = true;

			//�����̐���
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(1800);

			//������
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

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
		BindTexture(m_pTexture[2]);

		m_nEnemymoveCnt++;

		m_moveSave = m_move;

		//�ړ�
		if (m_nEnemymoveCnt >= 450 && m_nCntBullet < 5)
		{
			m_move.y = 0.0f;

		}


		//��Ԓ[�̊p�x�v�Z
		float fAngle = (D3DX_PI / 8) + (N_WAY_CREATE - 1) / 2 * (D3DX_PI / -7);

		if (m_nEnemymoveCnt >= 500)
		{
			//�^�C�}�[�����̒l��0�ɂȂ�ꍇ
			if (m_timer % 50 == 0)
			{
				//�l��n_way�e������������܂ŁA�p�x���v�Z���Ēe�𐶐�
				for (int nCntway = 0; nCntway < N_WAY_CREATE; nCntway++, fAngle += D3DX_PI / 12)
				{

					//n_way�e�̐���
					CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(20, 20, 0),
						D3DXVECTOR3(sinf(fAngle) * 4, cosf(fAngle) * 4, 0),
						D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_N_WAY1, CBullet::INFOTYPE_2);

					
				}

				m_nCntBullet++;
			}

			if (m_nCntBullet  >  5)
			{

				m_move.y = -1.0f;
			}

		}

	
	

		//���ɍs���܂�
		if ((pos.y + m_scale.y / 2.0f) <= 0.0f&&m_nEnemymoveCnt > 1000)
		{
			//�G����
			m_bUninit = true;
		}

		//�̗͂�0�ȉ��ɂȂ����ꍇ
		if (m_nLife <= 0)
		{
			//�G�̏���
			m_bUninit = true;

			//������
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

			Uninit();

			//�����̐���
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(4000);

			return;
		}
	}

	//�G�̎�ނ�n_way1�e�����G�̏ꍇ
	if (m_EnemyType == ENEMYTYPE_N_WAY2)
	{
		BindTexture(m_pTexture[2]);

		m_nEnemymoveCnt++;

		m_moveSave = m_move;

		//�ړ�
		if (m_nEnemymoveCnt >= 450 && m_nCntBullet < 5)
		{
			m_move.y = 0.0f;

		}


		//��Ԓ[�̊p�x�v�Z
		float fAngle = (D3DX_PI / 8) + (N_WAY_CREATE - 1) / 2 * (D3DX_PI / -7);

		if (m_nEnemymoveCnt >= 500)
		{
			//�^�C�}�[�����̒l��0�ɂȂ�ꍇ
			if (m_timer % 50 == 0)
			{
				//�l��n_way�e������������܂ŁA�p�x���v�Z���Ēe�𐶐�
				for (int nCntway = 0; nCntway < N_WAY_CREATE; nCntway++, fAngle += D3DX_PI / 12)
				{

					//n_way�e�̐���
					CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(20, 20, 0),
						D3DXVECTOR3(sinf(fAngle) * 4, cosf(fAngle) * 4, 0),
						D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_N_WAY1, CBullet::INFOTYPE_2);


				}

				m_nCntBullet++;
			}

			if (m_nCntBullet  >  5)
			{

				m_move.y = -1.0f;
			}

		}




		//���ɍs���܂�
		if ((pos.y + m_scale.y / 2.0f) <= 0.0f&&m_nEnemymoveCnt > 1000)
		{
			//�G����
			m_bUninit = true;
		}

		//�̗͂�0�ȉ��ɂȂ����ꍇ
		if (m_nLife <= 0)
		{
			//�G�̏���
			m_bUninit = true;

			//������
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

			Uninit();

			//�����̐���
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(4000);

			return;
		}
	}

	//�G�̎�ނ��ːi����G�̏ꍇ
	if (m_EnemyType == ENEMYTYPE_RUSH)
	{
		//�G�̃e�N�X�`��
		BindTexture(m_pTexture[1]);

		//�ړ��J�E���g
		m_nEnemymoveCnt++;

		//�J�E���g�œG�̈ړ������Z
		if (m_nEnemymoveCnt >= 10)
		{
			//�ړ��l��ۑ�
			m_moveSave = m_move;
		}

		//�ړ��̒l�����l�ȉ��̏ꍇ
		if (m_moveSave.y <= 1.0f&& m_nEnemymoveCnt>=10)
		{

			//�k���铮��
			if (m_nEnemymoveCnt >= 70&& m_nEnemymoveCnt <= 300)
			{
				//�ړ��l��0��
				m_move.y = 0.0f;

				if (m_nEnemymoveCnt <= 170)
				{
					if (m_nEnemymoveCnt % 3 == 0)
					{
						m_move.y = -1.0f;
					}

					if (m_nEnemymoveCnt % 5 == 0)
					{
						m_move.y = 1.0f;
					}
				}
				//�r�����猃����
				if (m_nEnemymoveCnt >= 170 && m_nEnemymoveCnt <= 300)
				{
					if (m_nEnemymoveCnt % 2 == 0)
					{
						m_move.y = -1.2f;
					}
					else if (m_nEnemymoveCnt % 3 == 0)
					{
						m_move.y = 1.0f;
					}
				}
			}

			//�ːi�U��
			if (m_nEnemymoveCnt >= 300)
			{
				m_move.y = -20.0f;
			}
		}

		//�ړ��̒l�����l�ȏ�̏ꍇ
		if (m_moveSave.y >= 1.0f && m_nEnemymoveCnt >= 10)
		{

			//�k���铮��
			if (m_nEnemymoveCnt >= 70 && m_nEnemymoveCnt <= 300)
			{
				//�ړ��l��0��
				m_move.y = 0.0f;

				if (m_nEnemymoveCnt <= 170)
				{
					if (m_nEnemymoveCnt % 3 == 0)
					{
						m_move.y = -1.0f;
					}

					if (m_nEnemymoveCnt % 5 == 0)
					{
						m_move.y = 1.0f;
					}
				}
				//�r�����猃����
				if (m_nEnemymoveCnt >= 170 && m_nEnemymoveCnt <= 300)
				{
					if (m_nEnemymoveCnt % 2 == 0)
					{
						m_move.y = -1.0f;
					}

					if (m_nEnemymoveCnt % 3 == 0)
					{
						m_move.y = 1.2f;
					}
				}
			}

			//�ːi�U��
			if (m_nEnemymoveCnt >= 300)
			{
				m_move.y = 20.0f;
			}
		}

		if (m_nEnemymoveCnt > 700)
		{
			m_bUninit = true;
		}

		//�̗͂�0�ȉ��ɂȂ����ꍇ
		if (m_nLife <= 0)
		{
			//�G�̏���
			m_bUninit = true;

			Uninit();

			//�����̐���
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			//������
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

			pScore->AddScore(1200);

			return;
		}
	}

	//�{�X�̍s������//

	//�{�X�̎�ނ��S���ʌ����e�����G�̏ꍇ
	if (m_BossType == BOSSTYPE_CROSSING)
	{
		//�G�̃e�N�X�`��
		BindTexture(m_pTexture[4]);

		m_Craetepos[0] = D3DXVECTOR3(pos.x - 10, pos.y, 0);
		m_Craetepos[1] = D3DXVECTOR3(pos.x + 15, pos.y, 0);
		m_Craetepos[2] = D3DXVECTOR3(pos.x - 5, pos.y, 0);
		m_Craetepos[3] = D3DXVECTOR3(pos.x + 6, pos.y, 0);


		if (m_timer % 320 == 0)
		{
			//�J�E���g
			if (((float)m_nLife > (float)m_nMaxLife *0.75f))
			{
				//�J�E���g
				if (m_nCntMadness < 8)
				{
					//�G�̈ʒu���Q�Ƃ��Ēe�𐶐�
					OnDiffuesPos(m_Craetepos[m_nCntMadness % 4 == 0], m_move);
				}

			}

			m_nCntMadness++;
		}

		//��������
		OnMadnessBullet();


		//�̗͂�0�ȉ��ɂȂ����ꍇ
		if (m_nLife <= 0)
		{
			//�G�̏���
			m_bUninit = true;

			Uninit();

			//�����̐���
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(40000);

			//������
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

			return;
		}


	}

	//�{�X�̎�ނ��S���ʔ��˒e�����G�̏ꍇ
	if (m_BossType == BOSSTYPE_REFLECTION_ALL)
	{

		//�G�̃e�N�X�`��
		BindTexture(m_pTexture[4]);

		//�ړ��J�E���g
		m_nEnemymoveCnt++;

		//�l�����l�ȉ��̏ꍇ
		if (m_nEnemymoveCnt <= 280)
		{
			//�ړ�
			m_move.y = 0.8f;
		}
		else
		{
			//�������W
			m_Craetepos[0] = D3DXVECTOR3(500.0f, 250.0f, 0.0f);
			m_Craetepos[1] = D3DXVECTOR3(150.0f, 180.0f, 0.0f);
			m_Craetepos[2] = D3DXVECTOR3(200.0f, 200.0f, 0.0f);
			m_Craetepos[3] = D3DXVECTOR3(250.0f, 170.0f, 0.0f);
			m_Craetepos[4] = D3DXVECTOR3(550.0f, 100.0f, 0.0f);
			m_Craetepos[5] = D3DXVECTOR3(450.0f, 180.0f, 0.0f);
			m_Craetepos[6] = D3DXVECTOR3(340.0f, 130.0f, 0.0f);
			m_Craetepos[7] = D3DXVECTOR3(490.0f, 130.0f, 0.0f);
			m_Craetepos[8] = D3DXVECTOR3(300.0f, 200.0f, 0.0f);
			m_Craetepos[9] = D3DXVECTOR3(120.0f, 250.0f, 0.0f);

			//�p�x�v�Z
			float VectorX = m_posBoss.x - pos.x;
			float VectorY = m_posBoss.y - pos.y;
			float fAngle = atan2f(VectorX, VectorY);
			float fLengthObj = sqrtf(VectorX*VectorX + VectorY*VectorY);

			//�l����
			float moveX = sinf(fAngle)*1.5f;
			float moveY = cosf(fAngle)*1.5f;

			//�l���ړ��l�Ɋ��Z
			m_move.x = moveX;
			m_move.y = moveY;

			//���W�͈̔�
			m_fLength = 5.0f;

			//���W���w�肳�ꂽ���W�͈̔͂𒴂����ꍇ
			if (fLengthObj <= m_fLength)
			{

				//�l�����݂��郉���_���Ȉʒu���{�X�̈ʒu�Ƃ��ĕۑ�
				m_posBoss = m_Craetepos[rand() % 10];

				//�����^�C���J�E���g
				m_nCntMadness++;

				//�l���ړ��l�Ɋ��Z
				m_move.x = 0.0f;
				m_move.y = 0.0f;

				//�J�E���g�����̒l��0�ɂȂ�ꍇ
				if (m_nCntMadness % 3 == 0)
				{
					if (m_nCntMadness <= 15 && (float)m_nLife >= (float)m_nMaxLife *0.75f)
					{
						//�G�̈ʒu���Q�Ƃ��Ēe�𐶐�
						OnDiffuesPos(pos, m_move);
					}
				}

			}

			//��������
			OnMadnessBullet();

			//�̗͂�0�ȉ��ɂȂ����ꍇ
			if (m_nLife <= 0)
			{
				//�G�̏���
				m_bUninit = true;

				//�I�������̌Ăяo��
				Uninit();

				//���ł����ʒu��ۑ�
				m_posDeath = pos;

				//�����̐���
				CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

				//������
				pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

				//�X�R�A�̉��Z
				pScore->AddScore(180000);

				pLifeboss->AddBossLifeCnt(-1);

				//�㉺���˒e�G�̐���
				Create(m_posDeath, D3DXVECTOR3(100, 100, 0), D3DXVECTOR3(0, 0, 0), ENEMYTYPE_NONE, BOSSTYPE_REFLECTION_VERTICAL);

				return;
			}
		}
	}

	//�{�X�̎�ނ��㉺���˒e�����G�̏ꍇ
	if (m_BossType == BOSSTYPE_REFLECTION_VERTICAL)
	{
		//�G�̃e�N�X�`��
		BindTexture(m_pTexture[4]);


		if (m_nEnemymoveCnt <= 1)
		{
			//�������W
			m_Craetepos[0] = D3DXVECTOR3(420, 200, 0.0f);
		}

		//�l�����݂���ʒu���{�X�̈ʒu�Ƃ��ĕۑ�
		m_posBoss = m_Craetepos[0];


		//�p�x�v�Z
		float VectorX = m_posBoss.x - pos.x;
		float VectorY = m_posBoss.y - pos.y;
		float fAngle = atan2f(VectorX, VectorY);
		float fLengthObj = sqrtf(VectorX*VectorX + VectorY*VectorY);

		//�l����
		float moveX = sinf(fAngle)*1.5f;
		float moveY = cosf(fAngle)*1.5f;

		//�l���ړ��l�Ɋ��Z
		m_move.x = moveX;
		m_move.y = moveY;

		//�͈�
		m_fLength = 5;

		//���W���w�肳�ꂽ���W�͈̔͂𒴂����ꍇ
		if (fLengthObj <= m_fLength)
		{
			m_move.x = 0;
			m_move.y = 0;

			m_nEnemymoveCnt++;
		}
		
		if (m_nEnemymoveCnt >= 1)
		{
			//���W�̐ݒ�
			if (m_timer % 130 == 0)
			{
				m_Craetepos[0] = D3DXVECTOR3(pos.x, pos.y, 0);
				m_Craetepos[1] = D3DXVECTOR3(pos.x + 15, pos.y, 0);

				OnDiffuesPos(m_Craetepos[rand() % 2], m_move);
			}
		}

		//�̗͂�0�ȉ��ɂȂ����ꍇ
		if (m_nLife <= 0)
		{
			//�G�̏���
			m_bUninit = true;

			Uninit();

			//���ł����ʒu��ۑ�
			m_posDeath = pos;

			//�����̐���
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(60000);

			//������
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

			m_nBulletStartCnt = 0;

			//�Q���e�e�G�̐���
			Create(m_posDeath, D3DXVECTOR3(100, 100, 0), D3DXVECTOR3(0, 0, 0), ENEMYTYPE_NONE, BOSSTYPE_SPIRAL);

			pLifeboss->AddBossLifeCnt(-1);

			return;
		}
	}

	//�{�X�̎�ނ��Q���e�����G�������ꍇ
	if (m_BossType == BOSSTYPE_SPIRAL)
	{
		BindTexture(m_pTexture[3]);

		if (m_nEnemymoveCnt <= 1)
		{
			//�������W
			m_Craetepos[0] = D3DXVECTOR3(400.0f, 300.0f, 0.0f);
		}

		//�l�����݂���ʒu���{�X�̈ʒu�Ƃ��ĕۑ�
		m_posBoss = m_Craetepos[0];

		//�p�x�v�Z
		float VectorX = m_posBoss.x - pos.x;
		float VectorY = m_posBoss.y - pos.y;
		float fAngle = atan2f(VectorX, VectorY);
		float fLengthObj = sqrtf(VectorX*VectorX + VectorY*VectorY);

		//�l����
		float moveX = sinf(fAngle)*1.5f;
		float moveY = cosf(fAngle)*1.5f;

		//�l���ړ��l�Ɋ��Z
		m_move.x = moveX;
		m_move.y = moveY;

		//�͈�
		m_fLength = 5;

		//���W���w�肳�ꂽ���W�͈̔͂𒴂����ꍇ
		if (fLengthObj <= m_fLength)
		{
			m_move.x = 0;
			m_move.y = 0;

			m_nEnemyCnt++;
		}

		if (m_nEnemyCnt >= 20)
		{
			if (m_timer % 2 == 0)
			{

				if (m_timer % 5 == 0)
				{
					//�Q���e�̐���
					CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(30, 30, 0),
						D3DXVECTOR3(sinf(D3DX_PI * 2.0f * ((float)m_nEnemymoveCnt / (float)40)) * 2.0f, cosf(D3DX_PI * 2.0f * ((float)m_nEnemymoveCnt / (float)40)) * 2.0f, 0),
						D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_NORMAL, CBullet::INFOTYPE_1);

					//�����^�C���J�E���g
					m_nCntMadness++;
				}




				if (m_nEnemymoveCnt > 12 + m_nCntTime - 4)
				{
					m_nEnemymoveCnt = 0 + m_nCntTime;

					m_nCntTime += 5;
				}


				//��������
				OnMadnessBullet();

				m_nEnemymoveCnt++;


			}
		}

		//�̗͂�0�ȉ��ɂȂ����ꍇ
		if (m_nLife <= 0)
		{
			//�G�̏���
			m_bUninit = true;

			//�I�������̌Ăяo��
			Uninit();

			//������
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

			//�����̐���
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(320000);

			pLifeboss->Uninit();

			//���U���g�ֈړ�
			CFade::SetFade(CFade::FADE_OUT, CManager::MODE_RESULT);

			return;
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
// ���菈��
//*****************************************************************************
void CEnemy::OnCollision(void)
{
	//�ʒu�̎擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//�ʒu�̍X�V
	SetPosition(pos, m_scale);

	for (int nCntPriority = 0; nCntPriority < CScene::OBJTYPE_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			CScene*pScene;
			pScene = CScene::GetScene(nCntPriority, nCntScene);

			if (pScene != NULL)
			{
				//��ޔ���Ăяo��
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				//�^�C�v���v���C���[�̏ꍇ
				if (objType == OBJTYPE_PLAYER)
				{
					CPlayer *pPlayer = (CPlayer*)pScene;

					//�ʒu�̎擾
					D3DXVECTOR3 Playerpos;
					Playerpos = pPlayer->GetPosition();

					//�ʒu�̎擾
					D3DXVECTOR3 Playerscale;
					Playerscale = pPlayer->GetScale();

					/*bool bPlayer = pPlayer->Uninit();*/

					//�����蔻��
					if (pos.x + m_scale.x / 2.0f > Playerpos.x - Playerscale.x / 12.0f&&
						pos.x - m_scale.x / 2.0f < Playerpos.x + Playerscale.x / 12.0f&&
						pos.y + m_scale.y / 2.0f > Playerpos.y - Playerscale.y / 12.0f&&
						pos.y - m_scale.y / 2.0f < Playerpos.y + Playerscale.y / 12.0f)
					{

						//��e���̏���
						if (CGame::GetPlayer()->GetPlayerState() == CPlayer::PLAYERSTATE_NORMAL)
						{
							//�l����
							m_nPlayerCnt = 0;

							if (m_EnemyState == ENEMYTYPE_RUSH)
							{
								//�G����
								m_bUninit = true;
							}

							//�T�E���h�̃|�C���^
							CSound *pSound = CManager::GetSound();

							//������
							pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

							//�����̐���
							CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

							//�v���C���[�̏��
							pPlayer->SetPlayerState(CPlayer::PLAYERSTATE_DEATH);

							// ���C�t�����擾
							int nLife = CGame::GetLife()->GetLife();

							// ���C�t�̐ݒ�
							CGame::GetLife()->SetLife(nLife - 1);
						}
						else if (CGame::GetPlayer()->GetPlayerState() == CPlayer::PLAYERSTATE_REVIVAL)
						{

							//��e��J�E���g
							m_nPlayerCnt++;


							//��e���Ă����ł��Ȃ�
							m_bUninit = false;
						}
					}
				}
			}
		}
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
// �G�̏��
//*****************************************************************************
void CEnemy::EnemyState(void)
{
	switch (GetEnemyState())
	{
		//�ʏ��Ԃ̓G�������ꍇ
		 case ENEMYSTATE_NORMAL:

				m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	
	 	break;
	 
	 	//�_���[�W��Ԃ̓G�������ꍇ
		case ENEMYSTATE_DAMAGE:

			m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

			if (m_nCntColor % 2 == 0)
			{
				m_EnemyState = ENEMYSTATE_NORMAL;
			}

			break;

	}

	SetColor(m_Color);
}

//*****************************************************************************
// �e�̈ʒu��������
//*****************************************************************************
void CEnemy::OnDiffuesPos(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// Create���̏��
	// 1 pos, 2 scale. 3 move, 4 rot, 5 bulletType, 6 attackType, 7 infoType


	//�S���ʌ����e�������̏���
	if (m_BossType == BOSSTYPE_CROSSING)
	{
		
		for (int nCnt = 0; nCnt < 40; nCnt++)
		{
			//�������e�̐���
			CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(25, 25, 0),
				D3DXVECTOR3(sinf(D3DX_PI * 0.5f * ((float)nCnt / (float)10)) * 6, cosf(D3DX_PI * 0.5f * ((float)nCnt / (float)10)) * 6, 0),
				D3DXVECTOR3(0, (float)nCnt, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_CROSSING, CBullet::INFOTYPE_1);

			//�E�����e�̐���
			CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(25, 25, 0),
				D3DXVECTOR3(sinf(D3DX_PI * 0.5f * ((float)nCnt / (float)10)) * 6, cosf(D3DX_PI * 0.5f * ((float)nCnt / (float)10)) * 6, 0),
				D3DXVECTOR3(10, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_CROSSING, CBullet::INFOTYPE_2);
		}
	}

	//�S���ʔ��˒e�������̏���
	if (m_BossType == BOSSTYPE_REFLECTION_ALL)
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
	if (m_BossType == BOSSTYPE_REFLECTION_VERTICAL)
	{
		//�ʒu���Q�Ƃ����ꂽ�ʒu����e�𐶐�
		float fLength = 400.0f + rand() % 30;

		for (int nCnt = 0; nCnt < 180; nCnt++)
		{
			//���˒e�̐���
			CBullet::Create(D3DXVECTOR3((pos.x) + fLength * sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)) * 2, -250 + fLength *  cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)), pos.z),
				D3DXVECTOR3(20, 20, 0),
				D3DXVECTOR3(sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)) * 6, cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)) * 6, 0),
				D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_REFLECTION, CBullet::INFOTYPE_2);

			//���˒e�̐���
			CBullet::Create(D3DXVECTOR3((pos.x) + fLength * sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)) * 2, SCREEN_HEIGHT + 50 + fLength *  cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)), pos.z),
				D3DXVECTOR3(20, 20, 0), D3DXVECTOR3(sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)) * 6, cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)) * 6, 0),
				D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_REFLECTION, CBullet::INFOTYPE_2);
		}
	}
}

//*****************************************************************************
//�����̊Ǘ�����
//*****************************************************************************
void CEnemy::OnMadnessBullet(void)
{

	//�ʒu�̎擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//�S���ʌ����e�̔������̏���
	if (m_BossType == BOSSTYPE_CROSSING)
	{
		//����1�@�J�E���g���c���̗͂ɉ����Ēe�̔��ˉ񐔂𑝉�������
		if (((float)m_nLife < (float)m_nMaxLife *0.75f) && ((float)m_nLife >= (float)m_nMaxLife *0.5f))
		{
			//�t�F�[�Y�^�C�v
			m_PhaseType = PHASETYPE_1;
		}
		else if (m_nCntMadness > 8 && m_nCntMadness <= 18)
		{
			//�t�F�[�Y�^�C�v
			m_PhaseType = PHASETYPE_1;
		}

		//����2
		if (((float)m_nLife < (float)m_nMaxLife*0.5f) && ((float)m_nLife >= (float)m_nMaxLife *0.25f))
		{
			//�t�F�[�Y�^�C�v
			m_PhaseType = PHASETYPE_2;
		}
		else if (m_nCntMadness > 18 && m_nCntMadness <= 40)
		{
			//�t�F�[�Y�^�C�v
			m_PhaseType = PHASETYPE_1;
		}

		//����3
		if (((float)m_nLife < (float)m_nMaxLife *0.25f))
		{
			//�t�F�[�Y�^�C�v
			m_PhaseType = PHASETYPE_3;
		}
		else if (m_nCntMadness > 40)
		{
			//�t�F�[�Y�^�C�v
			m_PhaseType = PHASETYPE_1;
		}

		//�t�F�[�Y�^�C�v
		switch (m_PhaseType)
		{
		case PHASETYPE_1:

			if (m_timer % 160 == 0)
			{
				//�G�̈ʒu���Q�Ƃ��Ēe�𐶐�
				OnDiffuesPos(m_Craetepos[m_nCntTime % 4 == 0], m_move);
			}

			break;

		case PHASETYPE_2:

			//�^�C�}�[�����̒l��0�ɂȂ�ꍇ
			if (m_timer % 80 == 0)
			{
				//�G�̈ʒu���Q�Ƃ��Ēe�𐶐�
				OnDiffuesPos(m_Craetepos[m_nCntTime % 4 == 0], m_move);
			}

			break;

		case PHASETYPE_3:

			//�^�C�}�[�����̒l��0�ɂȂ�ꍇ
			if (m_timer % 40 == 0)
			{
				//�G�̈ʒu���Q�Ƃ��Ēe�𐶐�
				OnDiffuesPos(m_Craetepos[m_nCntTime % 4 == 0], m_move);
			}

			break;
		}

	}

	//�S���ʔ��˒e�̔������̏���
	if (m_BossType == BOSSTYPE_REFLECTION_ALL)
	{
		//����1�@�J�E���g���c���̗͂ɉ����Ēe�̔��ˉ񐔂𑝉�������
		if (((float)m_nLife <= (float)m_nMaxLife *0.75f)&& ((float)m_nLife > (float)m_nMaxLife *0.5f))
		{
			//�t�F�[�Y�^�C�v
			m_PhaseType = PHASETYPE_1;
		}
		//����1�@�J�E���g���c���̗͂ɉ����Ēe�̔��ˉ񐔂𑝉�������
		else if (m_nCntMadness > 15 && m_nCntMadness <= 30)
		{
			//�t�F�[�Y�^�C�v
			m_PhaseType = PHASETYPE_1;
		}

		//����2
		if (((float)m_nLife <= (float)m_nMaxLife *0.5f) && ((float)m_nLife >(float)m_nMaxLife *0.25f))
		{
			//�t�F�[�Y�^�C�v
			m_PhaseType = PHASETYPE_2;
		}
		//����1�@�J�E���g���c���̗͂ɉ����Ēe�̔��ˉ񐔂𑝉�������
		else if (m_nCntMadness > 30 && m_nCntMadness <= 45)
		{
			//�t�F�[�Y�^�C�v
			m_PhaseType = PHASETYPE_2;
		}

		//����3
		if (((float)m_nLife < (float)m_nMaxLife *0.25f))
		{
			//�t�F�[�Y�^�C�v
			m_PhaseType = PHASETYPE_3;
		}
		else if (m_nCntMadness > 45)
		{
			//�t�F�[�Y�^�C�v
			m_PhaseType = PHASETYPE_3;
		}

		//�t�F�[�Y�^�C�v
		switch (m_PhaseType)
		{
		case PHASETYPE_1:

			//�^�C�}�[�����̒l��0�ɂȂ�ꍇ
			if (m_timer % 300 == 0)
			{
				//�G�̈ʒu���Q�Ƃ��Ēe�𐶐�
				OnDiffuesPos(pos, m_move);
			}

			break;

		case PHASETYPE_2:

			//�^�C�}�[�����̒l��0�ɂȂ�ꍇ
			if (m_timer % 240 == 0)
			{
				//�G�̈ʒu���Q�Ƃ��Ēe�𐶐�
				OnDiffuesPos(pos, m_move);
			}

			break;

		case PHASETYPE_3:

			//�^�C�}�[�����̒l��0�ɂȂ�ꍇ
			if (m_timer % 180 == 0)
			{
				//�G�̈ʒu���Q�Ƃ��Ēe�𐶐�
				OnDiffuesPos(pos, m_move);
			}

			break;
		}
	}

	//�Q���e�̔������̏���
	if (m_BossType == BOSSTYPE_SPIRAL)
	{
		//����1�@�J�E���g���c���̗͂ɉ����Ēe��ǉ�����
		if ((float)m_nLife <= (float)m_nMaxLife *0.75f)
		{
			if (m_timer % 10 == 0)
			{
				//�Q���e�̐���
				CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(30, 30, 0),
					D3DXVECTOR3(sinf(D3DX_PI * -20.0f * ((float)m_nEnemymoveCnt / (float)200)) * 1.0f, cosf(D3DX_PI * -20.0f * ((float)m_nEnemymoveCnt / (float)200)) * 1.0f, 0),
					D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_SPIRAL, CBullet::INFOTYPE_RED);
			}
		}
		//����1�@�����J�E���g�Q��
		else if (m_nCntMadness > 400)
		{
			if (m_timer % 10 == 0)
			{
				//�Q���e�̐���
				CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(30, 30, 0),
					D3DXVECTOR3(sinf(D3DX_PI * -20.0f * ((float)m_nEnemymoveCnt / (float)200)) * 1.0f, cosf(D3DX_PI * -20.0f * ((float)m_nEnemymoveCnt / (float)200)) * 1.0f, 0),
					D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_SPIRAL, CBullet::INFOTYPE_RED);
			}
		}

		//����2	 �c���̗͎Q��
		if (((float)m_nLife <= (float)m_nMaxLife *0.5f))
		{
			if (m_nEnemymoveCnt >= 4 + m_nCntTime)
			{
				//�Q���e�̐���
				CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(70, 70, 0),
					D3DXVECTOR3(sinf(D3DX_PI * -3.0f * ((float)m_nEnemymoveCnt / (float)40)) * 1.5f, cosf(D3DX_PI * -3.0f * ((float)m_nEnemymoveCnt / (float)40)) * 1.5f, 0),
					D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_SPIRAL, CBullet::INFOTYPE_BIGBULLET);

				//�Q���e�̐���
				CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(30, 30, 0),
					D3DXVECTOR3(sinf(D3DX_PI * -3.0f * ((float)m_nEnemymoveCnt / (float)40)) * 1.5f, cosf(D3DX_PI * -3.0f * ((float)m_nEnemymoveCnt / (float)40)) * 1.5f, 0),
					D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_NORMAL, CBullet::INFOTYPE_BIGBULLET);
			}
		}
		//����2�@�����J�E���g�Q��
		else if (m_nCntMadness > 800)
		{
			if (m_nEnemymoveCnt >= 4 + m_nCntTime)
			{
				//�Q���e�̐���
				CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(70, 70, 0),
					D3DXVECTOR3(sinf(D3DX_PI * -3.0f * ((float)m_nEnemymoveCnt / (float)40)) * 1.5f, cosf(D3DX_PI * -3.0f * ((float)m_nEnemymoveCnt / (float)40)) * 1.5f, 0),
					D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_SPIRAL, CBullet::INFOTYPE_BIGBULLET);

				//�Q���e�̐���
				CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(30, 30, 0),
					D3DXVECTOR3(sinf(D3DX_PI * -3.0f * ((float)m_nEnemymoveCnt / (float)40)) * 1.5f, cosf(D3DX_PI * -3.0f * ((float)m_nEnemymoveCnt / (float)40)) * 1.5f, 0),
					D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_NORMAL, CBullet::INFOTYPE_BIGBULLET);
			}
		}

		//����3	�c���̗͎Q��
		if (((float)m_nLife < (float)m_nMaxLife *0.25f))
		{
			if (m_timer % 20 == 0)
			{
				for (int nCnt = 0; nCnt < 8; nCnt++)
				{
					//�Q���e�̐���
					CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(40, 40, 0),
						D3DXVECTOR3(sinf(D3DX_PI * 10.0f * ((float)nCnt / (float)40)) * 2.5f, cosf(D3DX_PI * 10.0f * ((float)nCnt / (float)40)) * 2.5f, 0),
						D3DXVECTOR3(0, 0, 0), CBullet
						::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_NORMAL, CBullet::INFOTYPE_BLUE);
				}
			}
		}
		//����3	�����J�E���g�Q��
		else if (m_nCntMadness > 1200)
		{
			if (m_timer % 20 == 0)
			{
				for (int nCnt = 0; nCnt < 8; nCnt++)
				{
					//�Q���e�̐���
					CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(40, 40, 0),
						D3DXVECTOR3(sinf(D3DX_PI * 10.0f * ((float)nCnt / (float)40)) * 2.5f, cosf(D3DX_PI * 10.0f * ((float)nCnt / (float)40)) * 2.5f, 0),
						D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_NORMAL, CBullet::INFOTYPE_BLUE);
				}
			}
		}

		//�t�F�[�Y�^�C�v
		switch (m_PhaseType)
		{
		case PHASETYPE_1:

	

			break;

		case PHASETYPE_2:

			break;

		case PHASETYPE_3:

			break;
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
