//=============================================================================
//
// ���C������ [game.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "enemy.h"
#include "life.h"
#include "fade.h"
#include "game.h"
#include "sound.h"
#include "bullet.h"
#include "explosion.h"
#include "manager.h"
#include "scene.h"
#include "score.h"
#include "renderer.h"
#include "dinput_keyboard.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CPlayer*CGame::m_pPlayer = NULL;					// �v���C���[�ϐ�
CEnemy*CGame::m_pEnemy = NULL;						// �G�ϐ�
CBullet*CGame::m_pBullet = NULL;					// �e�ϐ�
CScore*CGame::m_pScore = NULL;						// �X�R�A�ϐ�
CScore*CGame::m_pGraze = NULL;						// �O���C�Y�ϐ�
CScore*CGame::m_pBulletNum = NULL;					// �e����ϐ�
CBg*CGame::m_pBg = NULL;							// �w�i�ϐ�
CGame_Screen*CGame::m_pGame_Screen = NULL;			// �Q�[���w�i�ϐ�
CPause*CGame::m_pPause = NULL;						// �|�[�Y�ϐ�
CExplosion*CGame::m_pExplosion = NULL;				// �����ϐ�
CLife*CGame::m_pLife = NULL;						// ���C�t�ϐ�
//CSound*CGame::m_pSound = NULL;					// �T�E���h�ϐ�
int CGame::m_nCntResult = 0;
CGame::Transition CGame::m_transition = CGame::TRANSITION_NONE;

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CGame::CGame()
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CGame::~CGame()
{

}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CGame::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{

	//�������̌Ăяo��
	//CScene::Init(pos, scale);

	//�w�i�e�N�X�`���̃��[�h
	CGame_Screen::Load();

	//�w�i�e�N�X�`���̃��[�h
	CBg::Load();

	//�i���o�[�̃A�����[�h
	CNumber::Load();

	//�v���C���[�e�N�X�`���̃��[�h
	CPlayer::Load();

	//�|�[�Y�e�N�X�`���̃��[�h
	CPause::Load();

	//�G�e�N�X�`���̃��[�h
	CEnemy::Load();

	//�e�e�N�X�`���̃��[�h
	CBullet::Load();

	//�����e�N�X�`���̃��[�h
	CExplosion::Load();

	//�Q�[���w�i�N���X�̐���
	m_pGame_Screen = CGame_Screen::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0));

	//�w�i�N���X�̐���
	m_pBg = CBg::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0));

	//�v���C���[�N���X�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(420, 730, 0), D3DXVECTOR3(50, 50, 0));

	// ���C�t�N���X�̐���
	m_pLife = CLife::Create(D3DXVECTOR3(1000.0f, 235.0f, 0.0f), D3DXVECTOR3(40.0f, 40.0f, 0.0f));

	//�i���o�[�N���X�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(1050, 70, 0), D3DXVECTOR3(25, 45, 0),CScore::SCORETYPE_NORMAL);

	//�O���C�Y�|�C���g�̐���
	m_pGraze = CScore::Create(D3DXVECTOR3(1000, 450, 0), D3DXVECTOR3(20, 35, 0), CScore::SCORETYPE_GRAZE);

	//�|�[�Y�N���X�̍쐬
	m_pPause = CPause::Create(D3DXVECTOR3(640, 360, 0), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0));

	//�Q�[����ʂ̒e�ʊm�F�N���X�̍쐬
	//m_pBulletNum = CScore::Create(D3DXVECTOR3(1000, 600, 0), D3DXVECTOR3(20, 35, 0), CScore::SCORETYPE_NORMAL);

	m_nEnemyTime = 0;

	//�T�E���h�̃|�C���^
	CSound *pSound = CManager::GetSound();

	//BGM
	pSound->PlaySoundA(CSound::SOUND_LABEL_BGM000);

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CGame::Uninit(void)
{	
	//�i���o�[�̃A�����[�h
	CNumber::Unload();

	//�v���C���[�e�N�X�`���̃A�����[�h
	CPlayer::Unload();

	//�G�e�N�X�`���̃A�����[�h
	CEnemy::Unload();

	//�e�e�N�X�`���̃A�����[�h
	CBullet::Unload();

	//�����e�N�X�`���̃A�����[�h
	CExplosion::Unload();

	//�|�[�Y�e�N�X�`���̃A�����[�h
	CPause::Unload();

	//�w�i�e�N�X�`���̃A�����[�h
	CBg::Unload();

	//�Q�[���w�i�e�N�X�`���̃A�����[�h
	CGame_Screen::Unload();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CGame::Update(void)
{
	CInputKeyBoard *pKeyBoard;
	pKeyBoard = CManager::GetInputKeyBoard();

	//if (pKeyBoard->GetTrigger(DIK_S) == true)
	{
		m_nEnemyTime++;
	}

	//if (pKeyBoard->GetTrigger(DIK_L) == true)
	{
		//�ʏ�e1�����G�𐶐�
		if (m_nEnemyTime == ENEMY_RESPAWNTIME+1450)
		{
			for (int nCnt = 0; nCnt <= 3; nCnt++)
			{
				m_pEnemy = CEnemy::Create(D3DXVECTOR3(160 + (160.0f*(float)nCnt), -100.0f + (-500.0f*(float)nCnt), 0.0f),
					D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(0, 3.0f, 0), CEnemy::ENEMYTYPE_NORMAL1);
			}
		}

		//�ʏ�e3�����G�𐶐�
		if (m_nEnemyTime == ENEMY_RESPAWNTIME)
		{
			for (int nCnt = 0; nCnt <= 3; nCnt++)
			{

				m_pEnemy = CEnemy::Create(D3DXVECTOR3(900 + (200.0f*(float)nCnt), 50.0f, 0.0f),
					D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(-2.0f, 0.8f, 0), CEnemy::ENEMYTYPE_NORMAL3_R);
			}
		}

		if (m_nEnemyTime == ENEMY_RESPAWNTIME+50)
		{
			for (int nCnt = 0; nCnt <= 3; nCnt++)
			{
				m_pEnemy = CEnemy::Create(D3DXVECTOR3(-100 + (-200.0f*(float)nCnt), 50.0f, 0.0f),
					D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(2.0f, 0.8f, 0), CEnemy::ENEMYTYPE_NORMAL3_L);
			}
		}

		if (m_nEnemyTime == ENEMY_RESPAWNTIME+200)
		{
			for (int nCnt = 0; nCnt <= 3; nCnt++)
			{

				m_pEnemy = CEnemy::Create(D3DXVECTOR3(960 + (200.0f*(float)nCnt), 50.0f, 0.0f),
					D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(-2.0f, 0.8f, 0), CEnemy::ENEMYTYPE_NORMAL3_R);
			}
		}

		if (m_nEnemyTime == ENEMY_RESPAWNTIME+360)
		{
			for (int nCnt = 0; nCnt <= 3; nCnt++)
			{
				m_pEnemy = CEnemy::Create(D3DXVECTOR3(-120 + (-200.0f*(float)nCnt), 5.0f, 0.0f),
					D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(2.0f, 0.8f, 0), CEnemy::ENEMYTYPE_NORMAL3_L);
			}
		}

		if (m_nEnemyTime == ENEMY_RESPAWNTIME + 460)
		{
			for (int nCnt = 0; nCnt <= 3; nCnt++)
			{

				m_pEnemy = CEnemy::Create(D3DXVECTOR3(980 + (200.0f*(float)nCnt), 100.0f, 0.0f),
					D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(-2.0f, 0.8f, 0), CEnemy::ENEMYTYPE_NORMAL3_R);
			}
		}

		if (m_nEnemyTime == ENEMY_RESPAWNTIME + 560)
		{
			for (int nCnt = 0; nCnt <= 3; nCnt++)
			{
				m_pEnemy = CEnemy::Create(D3DXVECTOR3(-150 + (-200.0f*(float)nCnt), 100.0f, 0.0f),
					D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(2.0f, 0.8f, 0), CEnemy::ENEMYTYPE_NORMAL3_L);
			}
		}
	}

	//�����e�����G�𐶐�
	if (pKeyBoard->GetTrigger(DIK_3) == true)
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(350, 150, 0.0f), D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(0, 0, 0), CEnemy::ENEMYTYPE_CROSSING);
	}

	//���˒e�����G�𐶐�
	if (m_nEnemyTime == ENEMY_RESPAWNTIME + 5400)
	//if (pKeyBoard->GetTrigger(DIK_6) == true)
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(420, -10, 0.0f), D3DXVECTOR3(100, 100, 0), D3DXVECTOR3(0, 0, 0), CEnemy::ENEMYTYPE_REFLECTION);
	}

	//�܂�Ԃ��e�����G�𐶐�
	if (pKeyBoard->GetTrigger(DIK_4) == true)
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(350, 200, 0.0f), D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(3, 0, 0), CEnemy::ENEMYTYPE_TURN);
	}

	//n_Way�e1�����G�𐶐�
	if (pKeyBoard->GetTrigger(DIK_1) == true)
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(250, 300, 0.0f), D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(0, 0, 0), CEnemy::ENEMYTYPE_N_WAY1);
	}

	//n_Way�e2�����G�𐶐�
	if (pKeyBoard->GetTrigger(DIK_2) == true)
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(200, -100, 0.0f), D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(0, 5, 0), CEnemy::ENEMYTYPE_N_WAY2);
	}

	//�����̂̓G�𐶐�
	if (m_nEnemyTime == ENEMY_RESPAWNTIME + 4200)
	{
		for (int nCnt = 0; nCnt <= 5; nCnt++)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3((120 * (float)nCnt), -10 + (-80.0f*(float)nCnt), 0.0f),
				D3DXVECTOR3(45, 45, 0), D3DXVECTOR3(2.0f, 1.2f, 0), CEnemy::ENEMYTYPE_NORMAL4_R);
		}

		for (int nCnt = 0; nCnt <= 1; nCnt++)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(500+((float)nCnt*200), -200.0f, 0.0f), D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(0.0f, 1.0f, 1.0f), CEnemy::ENEMYTYPE_N_WAY1);
		}
	}

	//�����̂̓G�𐶐�
	//if (pKeyBoard->GetTrigger(DIK_J) == true)
	if (m_nEnemyTime == ENEMY_RESPAWNTIME + 3100)
	{
		for (int nCnt = 0; nCnt <= 3; nCnt++)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3((500 + ((float)nCnt) * 63) , -10 + (-120.0f*(float)nCnt), 0.0f),
				D3DXVECTOR3(45, 45, 0), D3DXVECTOR3(2.0f, 1.2f, 0), CEnemy::ENEMYTYPE_NORMAL4_L);
		}

		for (int nCnt = 0; nCnt <= 2; nCnt++)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(100 + ((float)nCnt * 200), -700.0f, 0.0f), D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(0.0f, 2.2f, 0.0f), CEnemy::ENEMYTYPE_N_WAY1);
		}
	}

	//�ːi����G�𐶐�
	//if (pKeyBoard->GetTrigger(DIK_J) == true)
	if (m_nEnemyTime == ENEMY_RESPAWNTIME + 4800)
	{
		for (int nCnt = 0; nCnt <= 7; nCnt++)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3((70 + ((float)nCnt) * 100), 720.0f, 0.0f),
				D3DXVECTOR3(45, 45, 0), D3DXVECTOR3(0.0f, -1.2f, 0), CEnemy::ENEMYTYPE_RUSH);
		}

	}

	//�ːi����G�𐶐�
	//if (pKeyBoard->GetTrigger(DIK_K) == true)
	if (m_nEnemyTime == ENEMY_RESPAWNTIME + 5000)
	{
		for (int nCnt = 0; nCnt <= 7; nCnt++)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3((20 + ((float)nCnt) * 100), 720.0f, 0.0f),
				D3DXVECTOR3(45, 45, 0), D3DXVECTOR3(0.0f, -1.2f, 0), CEnemy::ENEMYTYPE_RUSH);
		}

	}

	//m_pBulletNum->SetScore(0);
	int nCntBullet = 0;
	for (int nCnt = 0; nCnt < MAX_POLYGON; nCnt++)
	{
		CScene *pScene = CScene::GetScene(OBJTYPE_BULLET,nCnt);

		if (pScene != NULL)
		{
			nCntBullet++;
		}
	}

	//m_pBulletNum->AddScore(nCntBullet);

	//���U���g�ֈړ�
	if (m_transition == TRANSITION_RESULT)
	{
		if (m_pPlayer->CPlayer::GetPlayerState() == CPlayer::PLAYERSTATE_DEATH)
		{
			m_nCntResult++;

			//�X�R�A�̕ۑ�
			//CManager::SetScore(m_pScore->AddScore);

			if (m_nCntResult == 45)
			{
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_RESULT);

				m_transition = TRANSITION_NONE;

				m_nCntResult = 0;
			}

		}
	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CGame::Draw(void)
{

}

//*****************************************************************************
// ������񏈗�
//*****************************************************************************
CExplosion*CGame::GetExplosion(void)
{
	return m_pExplosion;
}

//*****************************************************************************
// �e��񏈗�
//*****************************************************************************
CBullet*CGame::GetBullet(void)
{
	return m_pBullet;
}

//*****************************************************************************
// �w�i��񏈗�
//*****************************************************************************
CBg*CGame::GetBg(void)
{
	return m_pBg;
}

//*****************************************************************************
// �Q�[���w�i��񏈗�
//*****************************************************************************
CGame_Screen*CGame::GetGame_Screen(void)
{
	return m_pGame_Screen;
}

//*****************************************************************************
// �v���C���[��񏈗�
//*****************************************************************************
CPlayer*CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//*****************************************************************************
// �G��񏈗�
//*****************************************************************************
CEnemy*CGame::GetEnemy(void)
{
	return m_pEnemy;
}

//*****************************************************************************
// �X�R�A��񏈗�
//*****************************************************************************
CScore*CGame::GetScore(void)
{
	return m_pScore;
}

//*****************************************************************************
// �X�R�A��񏈗�
//*****************************************************************************
CScore*CGame::GetGraze(void)
{
	return m_pGraze;
}


//CScore*CGame::GetBulletNum(void)
//{
//	return m_pBulletNum;
//}

CLife*CGame::GetLife(void)
{
	return m_pLife;
}