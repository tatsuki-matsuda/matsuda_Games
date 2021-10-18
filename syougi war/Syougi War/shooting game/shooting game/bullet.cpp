//=============================================================================
//
// ���C������ [bullet.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "bullet.h"
#include "fade.h"
#include "lifegauge.h"
#include "explosion.h"
#include "scene2D.h"
#include "manager.h"
#include "renderer.h"
#include "enemy.h"
#include "dinput_keyboard.h"
#include "player.h"
#include "score.h"
#include "game.h"
#include "sound.h"
#include "life.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBullet::m_pTexture[MAX_TEXTURE] = {};			// �e�N�X�`��


//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CBullet::CBullet(int nPriority) :CScene2D(nPriority)
{
	//�傫���̏����l
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�ړ��̏����l
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�p�x�̏����l
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�̗͒l
	m_nLife = 500;

	////��]��
	//m_fAngle = 0.0;

	//��]���x
	memset(&m_fAngleSpeed[0], 0, sizeof(m_fAngleSpeed));
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CBullet::~CBullet()
{

}

//*****************************************************************************
// ��������
//*****************************************************************************
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, D3DXVECTOR3 rot,
	BULLETTYPE bulletType, ATTACKTYPE attackType,INFOTYPE infoType)
{
	//���I�m��
	CBullet* pBullet;
	pBullet = new CBullet;

	//�������������Ăяo��
	pBullet->Init(pos,scale,move,rot);

	//�e�̏��̌Ăяo��
	pBullet->SetBulletType(bulletType);

	//�U����ޏ��̌Ăяo��
	pBullet->SetAttackType(attackType);

	//�U�����̌Ăяo��
	pBullet->SetInfoType(infoType);

	//�e�N�X�`���̌Ăяo��
	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		pBullet->BindTexture(m_pTexture[nCntTex]);
	}

	return pBullet;
}

//*****************************************************************************
//�@����������
//*****************************************************************************
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, D3DXVECTOR3 rot)
{
	//�ʒu��ݒ�
	m_posOrigin = pos;

	//�e�ɍł��߂��ʒu�̌v�Z��ݒ�
	m_fLengthObj = 10000.0f;

	//m_nKeepObj = -1;

	m_posDeath = D3DXVECTOR3(0, 0, 0);

	//�ړ��l��ݒ�
	m_move = move;

	//�傫����ݒ�
	m_scale = scale;

	//�p�x��ݒ�
	m_rot = rot;

	//�̗͂�ݒ�
	m_nLife = 1000;

	//��]�̒l��ݒ�
	m_fAngle = 0.0;

	//����]�̒l��ݒ�
	m_fAngleL = 0.0;

	//�E��]�̒l��ݒ�
	m_fAngleR = 0.0;

	//��]���x
	m_fAngleSpeed[0] = (float)-0.03f;
	m_fAngleSpeed[1] = (float)0.03;

	m_nPlayerCnt = 0;

	//����]�J�E���g�̐ݒ�
	m_nCrossingTimeL = 0;

	//�E��]�J�E���g�̐ݒ�
	m_nCrossingTimeR = 0;

	//���˃J�E���g�̐ݒ�
	m_nReflectionCnt = 0;

	//���ˎg�p�ݒ�
	m_bGraze = false;

	//���ˎg�p�ݒ�
	m_bReflection = false;

	//�g���Ă��邩�ǂ���
	m_bUninit = false;

	//���
	SetObjType(OBJTYPE_BULLET);

	//CScene2D���Ăяo��
	CScene2D::Init(pos,scale);

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CBullet::Uninit(void)
{
	//CScene2D����Ăяo��
	CScene2D::Uninit();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CBullet::Update(void)
{
	//�ʒu�̎擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//�T�E���h�̃|�C���^
	CSound *pSound = CManager::GetSound();

	//����
	m_nLife--;

	

	if (m_BulletType == BULLETTYPE_ENEMY)
	{
		m_EnemyBulletpos = pos;
	}

	if (m_BulletType == BULLETTYPE_PLAYER)
	{
		m_PlayerBulletpos = pos;
	}


	//�ǐՒe�̏ꍇ
	if (m_AttackType == ATTACKTYPE_HOMING)
	{
		m_nCnt++;

		if (m_nCnt % 3 == 0 && m_InfoType == INFOTYPE_1)
		{
			OnHoming();

			m_move.y *= 1.05f;
			m_move.x *= 1.05f;
		}

		//��ʊO����
		if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP ||
			pos.y + m_scale.y / 2.0f > SCREEN_HEIGHT ||
			pos.x - m_scale.x / 2.0f < 0.0f ||
			pos.x + m_scale.x / 2.0f > SCREEN_GAMEWIDTH)
		{
			//����
			m_bUninit = true;
		}
	}

	//�������e�̏ꍇ
	if (m_AttackType == ATTACKTYPE_CROSSING && m_InfoType == INFOTYPE_1)
	{

		m_Color = D3DXCOLOR(0.8f, 1.0f, 0.7f, 1.0f);

		SetColor(m_Color);

		//�J�E���g�����l�Ŋ��ꂽ�ꍇ
		if (m_nCrossingTimeL % 5 == 0)
		{
			//��������
			OnCrossing();
		}

		//�̗͂�0�ɂȂ����ꍇ
		if (m_nLife <= 0)
		{
			//����
			m_bUninit = true;
		}

		//��ʊO����
		if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP ||
			pos.x - m_scale.x / 2.0f < 0.0f ||
			pos.x + m_scale.x / 2.0f > SCREEN_GAMEWIDTH)
		{
			//����
			m_bUninit = true;
		}

		//�l�𑫂�
		m_nCrossingTimeL++;
	}

	//�E�����e�̏ꍇ
	if (m_AttackType == ATTACKTYPE_CROSSING && m_InfoType == INFOTYPE_2)
	{

		m_Color = D3DXCOLOR(0.9f, 1.0f, 0.8f, 1.0f);

		SetColor(m_Color);

		//�J�E���g�����l�Ŋ��ꂽ�ꍇ
		if (m_nCrossingTimeR % 5 == 0)
		{
			//��������
			OnCrossing();	
		}

		//�l�𑫂�
		m_nCrossingTimeR++;

		//�̗͂�0�ɂȂ����ꍇ
		if (m_nLife <= 0)
		{
			//����
			m_bUninit = true;
		}

		//��ʊO����
		if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP ||
			pos.x - m_scale.x / 2.0f < 0.0f ||
			pos.x + m_scale.x / 2.0f > SCREEN_GAMEWIDTH)
		{
			//����
			m_bUninit = true;
		}
	}

	//�S���ʔ��˒e�̏ꍇ
	if (m_AttackType == ATTACKTYPE_REFLECTION && m_InfoType == INFOTYPE_1)
	{
		//���ˏ���
		OnReflection();

		m_Color = D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f);

		SetColor(m_Color);

		//�l�����l�ȏ�̏ꍇ
		if (m_bReflection == true)
		{
			//�ʒu�����͈͈̔ȏ�̏ꍇ
			if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP - 30 ||
				pos.x - m_scale.x / 2.0f < -30.0f ||
				pos.x + m_scale.x / 2.0f > SCREEN_GAMEWIDTH + 30)
			{
				//����
				m_bUninit = true;

				//�J�E���^���Z�b�g
				m_bReflection = false;
			}
		}

		//�l�����l�ȏ�̏ꍇ
		if (pos.y + m_scale.y / 2.0f > SCREEN_HEIGHT + 30)
		{
			//����
			m_bUninit = true;
		}

	}

	//�㉺���˒e�̏ꍇ
	if (m_AttackType == ATTACKTYPE_REFLECTION && m_InfoType == INFOTYPE_2)
	{
		if (pos.x - m_scale.x / 2.0f < -30.0f ||
			pos.x + m_scale.x / 2.0f > SCREEN_GAMEWIDTH + 10)
		{		
			//����
			m_bUninit = true;

		}

		//���ˏ���
		OnReflection();

		//�l�����l�ȏ�̏ꍇ
		if (m_nReflectionCnt >= 1)
		{
			//�ʒu�����͈͈̔ȏ�̏ꍇ
			if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP - 40.0f ||
				pos.y + m_scale.y / 2.0f > SCREEN_HEIGHT + 40.0f )
			{
				//����
				m_bUninit = true;

				//�J�E���^���Z�b�g
				m_nReflectionCnt = 0;
			}
		}
	}

	//�܂�Ԃ��e�̏ꍇ
	if (m_AttackType == ATTACKTYPE_TURN)
	{
		//�܂�Ԃ�����
		OnTurn();

		//�܂�Ԃ��J�E���g�����l�ȏ�̏ꍇ
		if (m_TurnCnt >= 2)
		{
			//�ʒu�����͈͈̔ȏ�̏ꍇ
			if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP - 10 ||
				pos.y + m_scale.y / 2.0f > SCREEN_HEIGHT + 10 ||
				pos.x - m_scale.x / 2.0f < -10.0f ||
				pos.x + m_scale.x / 2.0f > SCREEN_GAMEWIDTH)
			{
				//����
				m_bUninit = true;

				//�J�E���^���Z�b�g
				m_TurnCnt = 0;
			}
		}
	}

	//n_way�e1�̏ꍇ
	if (m_AttackType == ATTACKTYPE_N_WAY1)
	{
		OnDiffusion();

		m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

		SetColor(m_Color);

		//��ʊO����
		if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP ||
			pos.y + m_scale.y / 2.0f > SCREEN_HEIGHT ||
			pos.x - m_scale.x / 2.0f < 0.0f ||
			pos.x + m_scale.x / 2.0f > SCREEN_GAMEWIDTH)
		{
			//����
			m_bUninit = true;
		}
	}

	//n_way�e�̏ꍇ
	if (m_AttackType == ATTACKTYPE_N_WAY2)
	{
		//nWay�e�J�E���g
		m_nWayCnt++;

		if (m_nWayCnt == 40)
		{
			m_bUninit = true;

			m_posDeath = pos;

			if(m_bUninit == true)
			{
				//��Ԓ[�̊p�x���v�Z
				float fAngle = (D3DX_PI / 8) + (N_WAY_CREATE - 1) / 2 * (D3DX_PI / -7);

				//�l��n_way�e������������܂ŁA�p�x���v�Z���Ēe�𐶐�
				for (int nCntway = 0; nCntway < N_WAY_CREATE; nCntway++, fAngle += D3DX_PI / 12)
				{
					//n_way�e�̐���
					CBullet::Create(D3DXVECTOR3(m_posDeath.x, m_posDeath.y, m_posDeath.z), D3DXVECTOR3(20, 20, 0),
						D3DXVECTOR3(sinf(fAngle) * 4, cosf(fAngle) * 4, 0),
						D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_N_WAY1, CBullet::INFOTYPE_2);
				}
			}

		}

		if (m_nWayCnt >= 41)
		{
			m_nWayCnt = 0;
		}

			//��ʊO����
			if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP ||
				pos.y + m_scale.y / 2.0f > SCREEN_HEIGHT ||
				pos.x - m_scale.x / 2.0f < 0.0f ||
				pos.x + m_scale.x / 2.0f > SCREEN_GAMEWIDTH)
			{
				//����
				m_bUninit = true;
			}

	}

	//�{���̏ꍇ
	if (m_AttackType == ATTACKTYPE_BOMB)
	{
		m_pTexture[1];

		m_nCntSpiral++;

		OnCollision();


		m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);

		SetColor(m_Color);

		//�J�E���g�����l�Ŋ��ꂽ�ꍇ
		if (m_nCntSpiral % 5 == 0)
		{
			//��������
			OnCrossing();
		}

		//�̗͂�0�ɂȂ����ꍇ
		if (m_nLife <= 0)
		{
			//����
			m_bUninit = true;
		}
	}

	//�^�C�v����
	if (m_InfoType == INFOTYPE_BIGBULLET)
	{

		//�ʏ�e�̏ꍇ
		if (m_AttackType == ATTACKTYPE_NORMAL)
		{
			m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);

			SetColor(m_Color);
		}

		//�Q���e�̏ꍇ
		if (m_AttackType == ATTACKTYPE_SPIRAL)
		{
			m_Color = D3DXCOLOR(0.2f, 0.5f, 1.0f, 0.7f);

			SetColor(m_Color);
		}
	}

	if (m_InfoType == INFOTYPE_RED)
	{

		//�ʏ�e�̏ꍇ
		if (m_AttackType == ATTACKTYPE_NORMAL)
		{
			m_Color = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f);

			SetColor(m_Color);
		}

		//�Q���e�̏ꍇ
		if (m_AttackType == ATTACKTYPE_SPIRAL)
		{
			//m_Color = D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.9f);
			m_Color = D3DXCOLOR(0.2f, 0.8f, 1.0f, 0.9f);

			SetColor(m_Color);
		}
	}

	if (m_InfoType == INFOTYPE_BLUE)
	{

		//�ʏ�e�̏ꍇ
		if (m_AttackType == ATTACKTYPE_NORMAL)
		{
			m_Color = D3DXCOLOR(0.0f, 0.3f, 1.0f, 1.0f);

			SetColor(m_Color);
		}

		//�Q���e�̏ꍇ
		if (m_AttackType == ATTACKTYPE_SPIRAL)
		{
			m_Color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.9f);

			SetColor(m_Color);
		}
	}


	//���菈��
	OnCollision();

	//�ړ��ʂ�ǉ�
	pos += m_move;

	//�ʒu�̍X�V
	SetPosition(pos, m_scale);


	//�v���C���[���ŏ�Ԃ���щ�ʊO�̏���
	//�G�̒e�������ꍇ
	if (GetBulletType() == BULLETTYPE_ENEMY)
	{
		//�v���C���[�̏�Ԃ����ŏ�Ԃ������ꍇ
		if (CGame::GetPlayer()->GetPlayerState() == CPlayer::PLAYERSTATE_DEATH)
		{
			//��e��J�E���g
			m_nPlayerCnt++;

			//�J�E���g�����̒l���������ꍇ
			if (m_nPlayerCnt % 1 == 0)
			{
				//����
				m_bUninit = true;
			}
		}
		else
		{
			//��ʊO����
			if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP-30 ||
				pos.y + m_scale.y / 2.0f > SCREEN_HEIGHT+30 ||
				pos.x - m_scale.x / 2.0f < -30.0f ||
				pos.x + m_scale.x / 2.0f > SCREEN_GAMEWIDTH + 30)
				{
					//����
					m_bUninit = true;
				}
			else
				{
					//����
					m_bUninit = false;
				}
		}
	}

	//���ł����ꍇ
	if (m_bUninit == true)
	{
		//�I�������̌Ăяo��
		Uninit();
	}
}

//*****************************************************************************
// ���菈��
//*****************************************************************************
void CBullet::OnCollision(void)
{
	//�ʒu�̎擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//�T�E���h�̃|�C���^
	CSound *pSound = CManager::GetSound();

	//�ʒu�̍X�V
	SetPosition(pos, m_scale);

	CScore *pScore;
	pScore = CGame::GetScore();

	for (int nCntPriority = 0; nCntPriority < CScene::OBJTYPE_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			CScene*pScene;
			pScene = CScene::GetScene(nCntPriority, nCntScene);

			if (pScene != NULL)
			{
				//�e����Ăяo��
				BULLETTYPE BulletType;
				BulletType = GetBulletType();

				//��ޔ���Ăяo��
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				//�v���C���[�̒e�ł��^�C�v���G�̏ꍇ
				if (BulletType == BULLETTYPE_PLAYER && objType == OBJTYPE_ENEMY)
				{
					//�ʒu�̎擾
					CEnemy *pEnemy = (CEnemy*)pScene;
					D3DXVECTOR3 Enemypos;
					Enemypos = pEnemy->GetPosition();

					//�ʒu�̎擾
					D3DXVECTOR3 Enemyscale;
					Enemyscale = pEnemy->GetScale();

					//�����蔻��
					if (pos.x + m_scale.x / 2.0f > Enemypos.x - Enemyscale.x / 2.0f&&
						pos.x - m_scale.x / 2.0f < Enemypos.x + Enemyscale.x / 2.0f&&
						pos.y + m_scale.y / 2.0f > Enemypos.y - Enemyscale.y / 2.0f&&
						pos.y - m_scale.y / 2.0f < Enemypos.y + Enemyscale.y / 2.0f)
					{

						//������
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE_HIT);

						//m_nEnemymoveCnt <= 280;

				/*		if (pEnemy->GetBossType() == pEnemy->BOSSTYPE_REFLECTION_ALL)
						{
						}*/
						//else
						{
							//�ʏ�e�̏ꍇ
							if (m_AttackType == ATTACKTYPE_NORMAL)
							{
								//�_���[�W����
								int nLife = pEnemy->GetLife();
								nLife -= NORMAL_DAMAGE;
								pEnemy->SetLife(nLife);

								//�l����
								CLifeGauge *pLifeGauge = pEnemy->GetLifeGauge();

								if (pLifeGauge != NULL)
								{
									//�Q�[�W�k������
									pLifeGauge->OnDiffuse(NORMAL_DAMAGE);
								}

							}

							//�z�[�~���O�̏ꍇ
							if (m_AttackType == ATTACKTYPE_HOMING)
							{
								//�_���[�W����
								int nLife = pEnemy->GetLife();
								nLife -= HOMING_DAMAGE;
								pEnemy->SetLife(nLife);

								//�l����
								CLifeGauge *pLifeGauge = pEnemy->GetLifeGauge();

								if (pLifeGauge != NULL)
								{
									//�Q�[�W�k������
									pLifeGauge->OnDiffuse(HOMING_DAMAGE);
								}
							}

							//�{���̏ꍇ
							if (m_AttackType == ATTACKTYPE_BOMB)
							{
								//�_���[�W����
								int nLife = pEnemy->GetLife();
								nLife -= BOMB_DAMAGE;
								pEnemy->SetLife(nLife);

								//�l����
								CLifeGauge *pLifeGauge = pEnemy->GetLifeGauge();

								if (pLifeGauge != NULL)
								{
									//�Q�[�W�k������
									pLifeGauge->OnDiffuse(BOMB_DAMAGE);
								}
							}

							//�G�̏��
							pEnemy->SetEnemyState(CEnemy::ENEMYSTATE_DAMAGE);

							if (m_AttackType != ATTACKTYPE_BOMB)
							{
								//����
								m_bUninit = true;
							}
						}
					}
				}
	

				//�G�̒e�ł��^�C�v���v���C���[�̏ꍇ
				if (BulletType == BULLETTYPE_ENEMY && objType == OBJTYPE_PLAYER)
				{
					CPlayer *pPlayer = (CPlayer*)pScene;

					//�ʒu�̎擾
					D3DXVECTOR3 Playerpos;
					Playerpos = pPlayer->GetPosition();

					//�ʒu�̎擾
					D3DXVECTOR3 Playerscale;
					Playerscale = pPlayer->GetScale();

					/*bool bPlayer = pPlayer->Uninit();*/

					//�Q���e�̏ꍇ
					if (m_AttackType == ATTACKTYPE_SPIRAL)
					{
						if (pos.x + m_scale.x / 8.0f > Playerpos.x - Playerscale.x / 12.0f&&
							pos.x - m_scale.x / 8.0f < Playerpos.x + Playerscale.x / 12.0f&&
							pos.y + m_scale.y / 8.0f > Playerpos.y - Playerscale.y / 12.0f&&
							pos.y - m_scale.y / 8.0f < Playerpos.y + Playerscale.y / 12.0f)
						{
							//��e���̏���
							if (CGame::GetPlayer()->GetPlayerState() == CPlayer::PLAYERSTATE_NORMAL)
							{
								//�T�E���h�̃|�C���^
								CSound *pSound = CManager::GetSound();

								//������
								pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

								//�l����
								m_nPlayerCnt = 0;

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
					//�����蔻��
					else if (pos.x + m_scale.x / 1.8f > Playerpos.x - Playerscale.x / 12.0f&&
						pos.x - m_scale.x / 1.8f < Playerpos.x + Playerscale.x / 12.0f&&
						pos.y + m_scale.y / 1.8f > Playerpos.y - Playerscale.y / 12.0f&&
						pos.y - m_scale.y / 1.8f < Playerpos.y + Playerscale.y / 12.0f)
					{

						//��e���̏���
						if (CGame::GetPlayer()->GetPlayerState() == CPlayer::PLAYERSTATE_NORMAL)
						{
							//�T�E���h�̃|�C���^
							CSound *pSound = CManager::GetSound();

							//������
							pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

							//�l����
							m_nPlayerCnt = 0;

							//�����̐���
							CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

							//�v���C���[�̏��
							pPlayer->SetPlayerState(CPlayer::PLAYERSTATE_DEATH);

							// ���C�t�����擾
							int nLife = CGame::GetLife()->GetLife();

							// ���C�t�̐ݒ�
							CGame::GetLife()->SetLife(nLife - 1);
						}	
						else if(CGame::GetPlayer()->GetPlayerState() == CPlayer::PLAYERSTATE_REVIVAL)
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

	if(m_AttackType== ATTACKTYPE_BOMB)
	{

		//�p�x�v�Z
		float VectorX = m_EnemyBulletpos.x - m_PlayerBulletpos.x;
		float VectorY = m_EnemyBulletpos.y - m_PlayerBulletpos.y;
		float fLength = sqrtf(VectorX*VectorX + VectorY*VectorY);

		if (m_BulletType == BULLETTYPE_PLAYER)
		{
			//���l�ɓ������ꍇ
			if (fLength <= 100)
			{
				//�e������L���ɂ���
				m_bUninit = true;

			}
		}
	}
}

//*****************************************************************************
// �ǔ�����
//*****************************************************************************
void CBullet::OnHoming(void)
{
	//�ʒu�̎擾
	D3DXVECTOR3 pos; 
	pos = GetPosition();

	float fLengthMin = 10000.0f;
	float fAngle = 0.0f;

	float fLengthHoming = 2000.0f;
	float fAngleHoming = 0.0f;

	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		//Scene�Ăяo��	
		CScene*pScene;
		pScene = CScene::GetScene(OBJTYPE_ENEMY,nCntScene);

		if (pScene != NULL)
		{
			//�v���C���[�̒e�������ꍇ
			if (m_BulletType == BULLETTYPE_PLAYER)
			{
				//�ʒu�̎擾
				CEnemy *pEnemy = (CEnemy*)pScene;
				D3DXVECTOR3 Enemypos;
				Enemypos = pEnemy->GetPosition();

				//�ʒu�̎擾
				CPlayer *pPlayer = (CPlayer*)pScene;
				D3DXVECTOR3 Playerpos;
				Playerpos = pPlayer->GetPosition();

				//�G�Ƃ̊p�x�v�Z
				float VectorX = Enemypos.x - pos.x;
				float VectorY = Enemypos.y - pos.y;
				float fLengthObj = sqrtf(VectorX*VectorX + VectorY*VectorY);

				//�v���C���[�Ƃ̊p�x�v�Z
				float VectorHomingX = Playerpos.x - pos.x;
				float VectorHomingY = Playerpos.y - pos.y;
				float fLengthHoming = sqrtf(VectorHomingX*VectorHomingX + VectorHomingY*VectorHomingY);

				//�l���w��l���Ⴂ�ꍇ
				//if (fLengthHoming >= fLengthHoming)
				{
					//�l���w��l���Ⴂ�ꍇ
					if (fLengthObj <= fLengthMin)
					{
						//�͈͂𓯂���
						fLengthMin = fLengthObj;

						fAngle = atan2f(VectorX, VectorY);

						//�z�[�~���O�v�Z
						float moveX = sinf(fAngle)*PLAYER_HOMING_X / 1.2f;
						float moveY = cosf(fAngle)*PLAYER_HOMING_Y / 1.2f;

						//�ړ��l�𓯂���
						m_move.x = moveX;
						m_move.y = moveY;
					}
				}
			}
		}
	}

	//for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	//{
	//	//Scene�Ăяo��
	//	CScene*pScene;
	//	pScene = CScene::GetScene(OBJTYPE_PLAYER, m_nKeepObj);

	//	if (pScene != NULL)
	//	{
	//		//�v���C���[�̒e�������ꍇ
	//		if (m_BulletType == BULLETTYPE_ENEMY)
	//		{
	//			//�ʒu�̎擾
	//			CPlayer *pPlayer = (CPlayer*)pScene;
	//			D3DXVECTOR3 Playerpos;
	//			Playerpos = pPlayer->GetPosition();

	//			//�p�x�v�Z
	//			float VectorX = Playerpos.x - pos.x;
	//			float VectorY = Playerpos.y - pos.y;

	//			//�p�x�v�Z
	//			float fangle = atan2f(VectorX, VectorY);

	//			if (m_nCnt % 1 == 0)
	//			{
	//				//�p�x�����l�𒴂���ꍇ
	//				if ((fangle < -D3DX_PI / 4.0f&&fangle > -D3DX_PI) ||
	//					(fangle > D3DX_PI / 4.0f&&fangle < D3DX_PI))
	//				{
	//					//�z�[�~���O�v�Z
	//					float moveX = sinf(fangle)*PLAYER_HOMING_X;
	//					float moveY = cosf(fangle)*PLAYER_HOMING_Y;

	//					//�ړ��l�����Z
	//					m_move.x = moveX;
	//					m_move.y = moveY;
	//				}
	//			}
	//		}
	//	}
	//}
}

//*****************************************************************************
// ��������
//*****************************************************************************
void CBullet::OnCrossing(void)
{
	//�ʒu�̎擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//�^�C�v���������e�̏ꍇ
	if (m_AttackType == ATTACKTYPE_CROSSING&&m_InfoType == INFOTYPE_1)
	{
		//��]���̒l
		m_fAngleL -= m_fAngleSpeed[0];

		//��]���̐���	
		if (m_fAngleL >= D3DX_PI)
		{
			m_fAngleL -= ((D3DX_PI / 2) / 90) * 1 + (m_nCrossingTimeL);
		}

		if (m_posOrigin != pos)
		{
			// �������ꂽ�ʒu���猻�݂̈ʒu�܂ł̋��������߂�
			D3DXVECTOR3 vec = m_posOrigin - pos;
			float fLength = sqrtf(vec.x * vec.x + vec.y * vec.y);
			float Lf = ((float)SCREEN_WIDTH - m_fAngleL) / (float)SCREEN_WIDTH;

			//�J�E���g�����l���������ꍇ
			if (m_nCrossingTimeL >= 50)
			{

				//��]���v�Z
				float LX = (m_move.x*cosf(m_fAngleL) + m_move.y*sinf(m_fAngleL)) / Lf;
				float LY = (-m_move.x*sinf(m_fAngleL) + m_move.y*cosf(m_fAngleL)) / Lf;

				//�l����
				m_move.x = LX/5.0f;
				m_move.y = LY/5.0f;
				
				//�J�E���g�̒l���}�C�i�X��
				m_nCrossingTimeL -= 700;
			}

		}
	}

	//�^�C�v���E�����e�̏ꍇ
	if (m_AttackType == ATTACKTYPE_CROSSING&&m_InfoType == INFOTYPE_2)
	{
		//��]���̒l
		m_fAngleR -= m_fAngleSpeed[1];

		//��]���̐���	
		if (m_fAngleR >= D3DX_PI)
		{
			m_fAngleR -= ((D3DX_PI / 2) / 90) * 1 + (m_nCrossingTimeR);
		}

		if (m_posOrigin != pos)
		{
			// �������ꂽ�ʒu���猻�݂̈ʒu�܂ł̋��������߂�
			D3DXVECTOR3 vec = m_posOrigin - pos;
			float fLength = sqrtf(vec.x * vec.x + vec.y * vec.y);
			float Rf = ((float)SCREEN_WIDTH - m_fAngleR) / (float)SCREEN_WIDTH;

			//�J�E���g�����l���������ꍇ
			if (m_nCrossingTimeR >= 50)
			{
				//��]���v�Z
				float RX = (m_move.x*cosf(m_fAngleR) + m_move.y*sinf(m_fAngleR)) / Rf;
				float RY = (-m_move.x*sinf(m_fAngleR) + m_move.y*cosf(m_fAngleR)) / Rf;

				//�l����
				m_move.x = RX / 5.0f;
				m_move.y = RY / 5.0f;
				
				//�J�E���g�̒l���}�C�i�X��
				m_nCrossingTimeR -= 700;

			}
		}
	}

	//�^�C�v���{���̏ꍇ
	if (m_AttackType == ATTACKTYPE_BOMB)
	{

		//��]���̒l
		m_fAngleBomb -= m_fAngleSpeed[0];

		//��]���̐���	
		if (m_fAngleBomb >= D3DX_PI)
		{
			m_fAngleBomb -= ((D3DX_PI / 2) / 90) * 1 + (m_nCntSpiral);
		}

		if (m_posOrigin != pos)
		{
			// �������ꂽ�ʒu���猻�݂̈ʒu�܂ł̋��������߂�
			D3DXVECTOR3 vec = m_posOrigin - pos;
			float fLength = sqrtf(vec.x * vec.x + vec.y * vec.y);
			float Lf = ((float)SCREEN_WIDTH - fLength) / (float)SCREEN_WIDTH;

			//�J�E���g�����l���������ꍇ
			if (m_nCntSpiral <= 78)
			{
				//�J�E���g�����l���������ꍇ
				if (m_nCntSpiral % 5 == 0)
				{
					//��]���v�Z
					float LX = (m_move.x*cosf(m_fAngleBomb) + m_move.y*sinf(m_fAngleBomb))*1.0f;
					float LY = (-m_move.x*sinf(m_fAngleBomb) + m_move.y*cosf(m_fAngleBomb))*1.0f;

					//�l����
					m_move.x = LX / 1.0f;
					m_move.y = LY / 1.0f;

					//�J�E���g�̒l���}�C�i�X��
				}

			}

			if (m_nCntSpiral >= 78)
			{
				m_nCrossingTimeL = 0;
			}


			//CPlayer *pPlayer;

			//pPlayer = CGame::GetPlayer();

			//D3DXVECTOR3 Playerpos = pPlayer->GetPosition();

			////�p�x�v�Z
			//float VectorX = Playerpos.x - pos.x;
			//float VectorY = Playerpos.y - pos.y;
			//float fAngle = atan2f(VectorX, VectorY);
			//float fLengthObj = sqrtf(VectorX*VectorX + VectorY*VectorY);

			////�l����
			//float moveX = sinf(fAngle)*1.5f;
			//float moveY = cosf(fAngle)*1.5f;

			////�l���ړ��l�Ɋ��Z
			//m_move.x = moveX;
			//m_move.y = moveY;

			//�͈�
			/*float fLength = 5;*/

			//if (m_nCntSpiral % 20 == 0)
			//{	
			//	//�Q���e�̐���
			//	m_move.x += (sinf(D3DX_PI * 2.0f * ((float)m_nCntSpiral / (float)40)) * 2.0f)/10.0f;
			//	m_move.y += (cosf(D3DX_PI * 2.0f * ((float)m_nCntSpiral / (float)40)) * 2.0f) / 10.0f;

			//}
		}

	}
}

//*****************************************************************************
// ���ˏ���
//*****************************************************************************
void CBullet::OnReflection(void)
{

	//�ʒu�̎擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//�^�C�v���S���ʔ��˒e�̏ꍇ
	if (m_AttackType == ATTACKTYPE_REFLECTION && m_InfoType == INFOTYPE_1)
	{
		//�ʒu�����͈͈̔ȏ�̏ꍇ
		if (pos.x - m_scale.x / 2.0f < 0.0f ||
			pos.x + m_scale.x / 2.0f > SCREEN_GAMEWIDTH)
		{

			//���˔��肪�s���Ă��Ȃ��ꍇ
			if (m_bReflection == false)
			{
				//����
				m_move.x *= -0.8f;

				//���˔��肪�s���Ă����Ԃɂ���
				m_bReflection = true;
			}

		}

		//�ʒu�����͈͈̔ȏ�̏ꍇ
		if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP)
		{

			//���˔��肪�s���Ă��Ȃ��ꍇ
			if (m_bReflection == false)
			{
				//����
				m_move.y *= -0.8f;

				//���˔��肪�s���Ă����Ԃɂ���
				m_bReflection = true;
			}
		}
	}

	//�^�C�v���㉺���˒e�̏ꍇ
	if (m_AttackType == ATTACKTYPE_REFLECTION&& m_InfoType == INFOTYPE_2)
	{

		//�ʒu�����͈͈̔ȏ�̏ꍇ
		if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP + 20 ||
			pos.y - m_scale.y / 2.0f > SCREEN_HEIGHT - 20)
		{


			//���˃J�E���g�����l�ɒB���Ă��Ȃ��ꍇ
			if (m_nReflectionCnt < 1)
			{

				
				//����
				m_move.y *= -1.0f;

				//�J�E���g
				m_nReflectionCnt++;
			}
		}
	}

	//�^�C�v�����ˉQ���e�̏ꍇ
	if (m_AttackType == ATTACKTYPE_SPIRAL && m_InfoType == INFOTYPE_1)
	{
		//�ʒu�����͈͈̔ȏ�̏ꍇ
		if (pos.x - m_scale.x / 2.0f < -20.0f ||	pos.x + m_scale.x / 2.0f > SCREEN_GAMEWIDTH)
		{
			//���˔��肪�s���Ă��Ȃ��ꍇ
			if (m_bReflection == false)
			{
				//����
				m_move.x *= -1.0f;

				//���˔��肪�s���Ă����Ԃɂ���
				m_bReflection = true;
			}

		}

		//�ʒu�����͈͈̔ȏ�̏ꍇ
		if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP - 20 || pos.y + m_scale.y / 2.0f > SCREEN_HEIGHT + 20)
		{
			//���˔��肪�s���Ă��Ȃ��ꍇ
			if (m_bReflection == false)
			{

				//����
				m_move.x *= -1.0f;

				//���˔��肪�s���Ă����Ԃɂ���
				m_bReflection = true;
			}
		}
	}
}

//*****************************************************************************
// �܂�Ԃ�����
//*****************************************************************************
void CBullet::OnTurn(void)
{
	//�ʒu�̎擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//�^�C�v���؂�ւ����e�̏ꍇ
	if (m_AttackType == ATTACKTYPE_TURN && m_InfoType == INFOTYPE_1)
	{

		//�ʒu�����͈͈̔ȏ�̏ꍇ
		if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP ||
			pos.y + m_scale.y / 2.0f > SCREEN_HEIGHT ||
			pos.x - m_scale.x / 2.0f < 0.0f ||
			pos.x + m_scale.x / 2.0f > SCREEN_GAMEWIDTH)
		{
			//�؂�ւ����J�E���g�����ȉ��̏ꍇ
			if (m_TurnCnt <= 2)
			{

				//�؂肩����
				m_move *= -1;

				//�J�E���g
				m_TurnCnt++;
			}
		}
	}
}

//*****************************************************************************
// n_way�e����
//*****************************************************************************
void CBullet::OnDiffusion(void)
{
	//�ʒu�̎擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//�^�C�v��n_way�e�̏ꍇ
	if (m_AttackType == ATTACKTYPE_N_WAY1 && m_InfoType == INFOTYPE_2)
	{
		m_nCnt++;

	/*	if (m_nCnt % 10 == 0)
		{
			float fAngle = 20.0f;

			m_move+=
		}*/
	}
}

//*****************************************************************************
// �{������
//*****************************************************************************
void CBullet::OnBomb(void)
{
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CBullet::Draw(void)
{
	//�`��̌Ăяo��
	CScene2D::Draw();
}

//*****************************************************************************
// �e�N�X�`���ǂݍ��ݏ���
//*****************************************************************************
HRESULT CBullet::Load(void)
{
	//�f�o�C�X�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet001.png", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &m_pTexture[1]);

	return S_OK;
}

//*****************************************************************************
// �e�N�X�`���j������
//*****************************************************************************
void CBullet::Unload(void)
{
	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
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
// �e��񏈗�
//*****************************************************************************
CBullet::BULLETTYPE CBullet::GetBulletType(void)
{
	return m_BulletType;
}

//*****************************************************************************
// �e�̐ݒ菈��
//*****************************************************************************
void CBullet::SetBulletType(BULLETTYPE bulletType)
{
	m_BulletType = bulletType;
}

//*****************************************************************************
// �U����ޏ�񏈗�
//*****************************************************************************
CBullet::ATTACKTYPE CBullet::GetAttackType(void)
{
	return m_AttackType;
}

//*****************************************************************************
// �U����ސݒ菈��
//*****************************************************************************
void CBullet::SetAttackType(ATTACKTYPE AttackType)
{
	m_AttackType = AttackType;
}

//*****************************************************************************
// �U����񏈗�
//*****************************************************************************
CBullet::INFOTYPE CBullet::GetInfoType(void)
{
	return m_InfoType;
}

//*****************************************************************************
// �U����ސݒ菈��
//*****************************************************************************
void CBullet::SetInfoType(INFOTYPE infoType)
{
	m_InfoType = infoType;
}

//*****************************************************************************
// �O���C�Y�̐ݒ菈��
//*****************************************************************************
bool CBullet::GetGraze(void)
{
	return m_bGraze;
}

//*****************************************************************************
// �O���C�Y�̏�񏈗�
//*****************************************************************************
void CBullet::SetGraze(bool bgraze)
{
	m_bGraze = bgraze;
}

//*****************************************************************************
// �e�����̐ݒ菈��
//*****************************************************************************
bool CBullet::GetUninit(void)
{
	return m_bUninit;
}

//*****************************************************************************
// �e������񏈗�
//*****************************************************************************
void CBullet::SetUninit(bool bUninit)
{
	m_bUninit = bUninit;
}
//*****************************************************************************
// �̗͂̐ݒ菈��
//*****************************************************************************
int CBullet::GetLife(void)
{
	return m_nLife;
}

//*****************************************************************************
// �̗͏�񏈗�
//*****************************************************************************
void CBullet::SetLife(int nLife)
{
	m_nLife = nLife;
}

//*****************************************************************************
// �ړ��̐ݒ菈��
//*****************************************************************************
D3DXVECTOR3 CBullet::GetMove(void)
{
	return m_move;
}

//*****************************************************************************
// �ړ���񏈗�
//*****************************************************************************
void CBullet::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}


//*****************************************************************************
// �e�N�X�`����񏈗�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBullet::GetTexture(int nCntTex)
{
	return m_pTexture[nCntTex];
}
