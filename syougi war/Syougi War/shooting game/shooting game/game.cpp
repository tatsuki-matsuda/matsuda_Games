//=============================================================================
//
// メイン処理 [game.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "enemy.h"
#include "life.h"
#include "bomb.h"
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
// 静的メンバ変数の初期化
//*****************************************************************************
CPlayer*CGame::m_pPlayer = NULL;					// プレイヤー変数
CEnemy*CGame::m_pEnemy = NULL;						// 敵変数
CBullet*CGame::m_pBullet = NULL;					// 弾変数
CScore*CGame::m_pScore = NULL;						// スコア変数
CScore*CGame::m_pGraze = NULL;						// グレイズ変数
CLifeBoss*CGame::m_pBossLifeCnt = NULL;				// ボスライフカウント変数
CScore*CGame::m_pBulletNum = NULL;					// 弾判定変数
CBg*CGame::m_pBg = NULL;							// 背景変数
CGame_Screen*CGame::m_pGame_Screen = NULL;			// ゲーム背景変数
CPause*CGame::m_pPause = NULL;						// ポーズ変数
CExplosion*CGame::m_pExplosion = NULL;				// 爆発変数
CLife*CGame::m_pLife = NULL;						// ライフ変数
CBomb*CGame::m_pBomb = NULL;						// ボム変数
//CSound*CGame::m_pSound = NULL;					// サウンド変数
int CGame::m_nCntResult = 0;
int CGame::m_nCntBullet = 0;
CGame::Transition CGame::m_transition = CGame::TRANSITION_NONE;

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CGame::CGame()
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CGame::~CGame()
{

}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CGame::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//背景テクスチャのロード
	CGame_Screen::Load();

	//背景テクスチャのロード
	CBg::Load();

	//ナンバーのアンロード
	CNumber::Load();

	//プレイヤーテクスチャのロード
	CPlayer::Load();

	//ポーズテクスチャのロード
	CPause::Load();

	//敵テクスチャのロード
	CEnemy::Load();

	//弾テクスチャのロード
	CBullet::Load();

	//爆発テクスチャのロード
	CExplosion::Load();

	//ゲーム背景クラスの生成
	m_pGame_Screen = CGame_Screen::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0));

	//背景クラスの生成
	m_pBg = CBg::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0));

	//プレイヤークラスの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(420, 730, 0), D3DXVECTOR3(50, 50, 0));

	// ライフクラスの生成
	m_pLife = CLife::Create(D3DXVECTOR3(1000.0f, 235.0f, 0.0f), D3DXVECTOR3(40.0f, 40.0f, 0.0f));

	//ボムクラスの生成
	m_pBomb = CBomb::Create(D3DXVECTOR3(1000.0f, 295.0f, 0.0f), D3DXVECTOR3(40.0f, 40.0f, 0.0f));

	//ナンバークラスの生成
	m_pScore = CScore::Create(D3DXVECTOR3(1050, 70, 0), D3DXVECTOR3(25, 45, 0),CScore::SCORETYPE_NORMAL);

	//グレイズポイントの生成
	m_pGraze = CScore::Create(D3DXVECTOR3(1000, 450, 0), D3DXVECTOR3(20, 35, 0), CScore::SCORETYPE_GRAZE);

	//ポーズクラスの作成
	m_pPause = CPause::Create(D3DXVECTOR3(640, 360, 0), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0));

	//ゲーム画面の弾量確認クラスの作成
	//m_pBulletNum = CScore::Create(D3DXVECTOR3(1000, 600, 0), D3DXVECTOR3(20, 35, 0), CScore::SCORETYPE_NORMAL);

	m_nEnemyTime = 0;

	//サウンドのポインタ
	CSound *pSound = CManager::GetSound();

	//BGM
	pSound->PlaySoundA(CSound::SOUND_LABEL_BGM000);

	m_nCntBullet = 0;

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CGame::Uninit(void)
{	
	//ナンバーのアンロード
	CNumber::Unload();

	//プレイヤーテクスチャのアンロード
	CPlayer::Unload();

	//敵テクスチャのアンロード
	CEnemy::Unload();

	//弾テクスチャのアンロード
	CBullet::Unload();

	//爆発テクスチャのアンロード
	CExplosion::Unload();

	//ポーズテクスチャのアンロード
	CPause::Unload();

	//背景テクスチャのアンロード
	CBg::Unload();

	//ゲーム背景テクスチャのアンロード
	CGame_Screen::Unload();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CGame::Update(void)
{
	CInputKeyBoard *pKeyBoard;
	pKeyBoard = CManager::GetInputKeyBoard();

	m_nCntBullet++;

	if (m_nCntBullet % 300 == 0)
	{
		m_nCntBullet = 0;
	}

	//if (pKeyBoard->GetTrigger(DIK_S) == true)
	{
		m_nEnemyTime++;
	}

	//通常弾3を撃つ敵を生成
	if (m_nEnemyTime == ENEMY_RESPAWNTIME)
	{
		for (int nCnt = 0; nCnt <= 3; nCnt++)
		{

			m_pEnemy = CEnemy::Create(D3DXVECTOR3(900 + (200.0f*(float)nCnt), 50.0f, 0.0f),
				D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(-2.0f, 0.8f, 0), CEnemy::ENEMYTYPE_NORMAL3_R, CEnemy::BOSSTYPE_NONE);
		}
	}

	if (m_nEnemyTime == ENEMY_RESPAWNTIME+50)
	{
		for (int nCnt = 0; nCnt <= 3; nCnt++)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-100 + (-200.0f*(float)nCnt), 50.0f, 0.0f),
				D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(2.0f, 0.8f, 0), CEnemy::ENEMYTYPE_NORMAL3_L, CEnemy::BOSSTYPE_NONE);
		}
	}

	if (m_nEnemyTime == ENEMY_RESPAWNTIME+200)
	{
		for (int nCnt = 0; nCnt <= 3; nCnt++)
		{

			m_pEnemy = CEnemy::Create(D3DXVECTOR3(960 + (200.0f*(float)nCnt), 50.0f, 0.0f),
				D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(-2.0f, 0.8f, 0), CEnemy::ENEMYTYPE_NORMAL3_R, CEnemy::BOSSTYPE_NONE);
		}
	}

	if (m_nEnemyTime == ENEMY_RESPAWNTIME+360)
	{
		for (int nCnt = 0; nCnt <= 3; nCnt++)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-120 + (-200.0f*(float)nCnt), 5.0f, 0.0f),
				D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(2.0f, 0.8f, 0), CEnemy::ENEMYTYPE_NORMAL3_L, CEnemy::BOSSTYPE_NONE);
		}
	}

	if (m_nEnemyTime == ENEMY_RESPAWNTIME + 460)
	{
		for (int nCnt = 0; nCnt <= 3; nCnt++)
		{

			m_pEnemy = CEnemy::Create(D3DXVECTOR3(980 + (200.0f*(float)nCnt), 100.0f, 0.0f),
				D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(-2.0f, 0.8f, 0), CEnemy::ENEMYTYPE_NORMAL3_R, CEnemy::BOSSTYPE_NONE);
		}
	}

	if (m_nEnemyTime == ENEMY_RESPAWNTIME + 560)
	{
		for (int nCnt = 0; nCnt <= 3; nCnt++)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-150 + (-200.0f*(float)nCnt), 100.0f, 0.0f),
				D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(2.0f, 0.8f, 0), CEnemy::ENEMYTYPE_NORMAL3_L, CEnemy::BOSSTYPE_NONE);
		}
	}

	//通常弾1を撃つ敵を生成
	//if (pKeyBoard->GetTrigger(DIK_M) == true)
	if (m_nEnemyTime == ENEMY_RESPAWNTIME + 1400)
	{
		for (int nCnt = 0; nCnt <= 3; nCnt++)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(160 + (160.0f*(float)nCnt), -100.0f + (-500.0f*(float)nCnt), 0.0f),
				D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(0, 3.0f, 0), CEnemy::ENEMYTYPE_NORMAL1, CEnemy::BOSSTYPE_NONE);
		}
	}

	//渦巻弾を撃つ敵を生成
	if (pKeyBoard->GetTrigger(DIK_N) == true)
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(100, 300, 0.0f), D3DXVECTOR3(100, 100, 0), D3DXVECTOR3(0, 0, 0), CEnemy::ENEMYTYPE_NONE,CEnemy::BOSSTYPE_SPIRAL);

		m_pBossLifeCnt = CLifeBoss::Create(D3DXVECTOR3(50, 33, 0), D3DXVECTOR3(17, 30, 0), CLifeBoss::LIFETYPE_BOSS);

		m_pBossLifeCnt->AddBossLifeCnt(0);
	}

	//全方位交差弾を撃つ敵を生成
	if (pKeyBoard->GetTrigger(DIK_3) == true)
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(400, 250, 0.0f), D3DXVECTOR3(100, 100, 0), D3DXVECTOR3(0, 0, 0), CEnemy::ENEMYTYPE_NONE,CEnemy::BOSSTYPE_CROSSING);

		
	}

	//反射弾を撃つ敵を生成
	if (m_nEnemyTime == ENEMY_RESPAWNTIME + 5100)
	//if (pKeyBoard->GetTrigger(DIK_6) == true)
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(420, -10, 0.0f), D3DXVECTOR3(100, 100, 0), D3DXVECTOR3(0, 0, 0), CEnemy::ENEMYTYPE_NONE,CEnemy::BOSSTYPE_REFLECTION_ALL);

		m_pBossLifeCnt = CLifeBoss::Create(D3DXVECTOR3(50, 33, 0), D3DXVECTOR3(17, 30, 0), CLifeBoss::LIFETYPE_BOSS);

		m_pBossLifeCnt->AddBossLifeCnt(2);
	}

	//縦反射弾を撃つ敵を生成
	//if (m_nEnemyTime == ENEMY_RESPAWNTIME + 5400)
	if (pKeyBoard->GetTrigger(DIK_7) == true)
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(600, 300, 0.0f), D3DXVECTOR3(100, 100, 0), D3DXVECTOR3(0, 0, 0), CEnemy::ENEMYTYPE_NONE, CEnemy::BOSSTYPE_REFLECTION_VERTICAL);

		m_pBossLifeCnt = CLifeBoss::Create(D3DXVECTOR3(50, 33, 0), D3DXVECTOR3(17, 30, 0), CLifeBoss::LIFETYPE_BOSS);

		m_pBossLifeCnt->AddBossLifeCnt(1);
	}

	//折り返し弾を撃つ敵を生成
	if (pKeyBoard->GetTrigger(DIK_4) == true)
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(350, 200, 0.0f), D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(3, 0, 0), CEnemy::ENEMYTYPE_TURN, CEnemy::BOSSTYPE_NONE);
	}

	//n_Way弾1を撃つ敵を生成
	if (pKeyBoard->GetTrigger(DIK_1) == true)
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(250, 300, 0.0f), D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(0, 0, 0), CEnemy::ENEMYTYPE_N_WAY1, CEnemy::BOSSTYPE_NONE);
	}

	//n_Way弾2を撃つ敵を生成
	if (pKeyBoard->GetTrigger(DIK_2) == true)
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(200, -100, 0.0f), D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(0, 5, 0), CEnemy::ENEMYTYPE_N_WAY2, CEnemy::BOSSTYPE_NONE);
	}

	//複数体の敵を生成
	if (m_nEnemyTime == ENEMY_RESPAWNTIME + 3500)
	{
		for (int nCnt = 0; nCnt <= 5; nCnt++)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3((120 * (float)nCnt), -10 + (-80.0f*(float)nCnt), 0.0f),
				D3DXVECTOR3(45, 45, 0), D3DXVECTOR3(2.0f, 1.2f, 0), CEnemy::ENEMYTYPE_NORMAL4_R, CEnemy::BOSSTYPE_NONE);
		}

		for (int nCnt = 0; nCnt <= 1; nCnt++)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(500+((float)nCnt*200), -200.0f, 0.0f), D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(0.0f, 1.0f, 1.0f), CEnemy::ENEMYTYPE_N_WAY1, CEnemy::BOSSTYPE_NONE);
		}
	}

	//複数体の敵を生成
	//if (pKeyBoard->GetTrigger(DIK_J) == true)
	if (m_nEnemyTime == ENEMY_RESPAWNTIME + 2600)
	{
		for (int nCnt = 0; nCnt <= 3; nCnt++)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3((500 + ((float)nCnt) * 63) , -10 + (-120.0f*(float)nCnt), 0.0f),
				D3DXVECTOR3(45, 45, 0), D3DXVECTOR3(2.0f, 1.2f, 0), CEnemy::ENEMYTYPE_NORMAL4_L, CEnemy::BOSSTYPE_NONE);
		}

		for (int nCnt = 0; nCnt <= 2; nCnt++)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(100 + ((float)nCnt * 200), -700.0f, 0.0f), D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(0.0f, 2.2f, 0.0f), CEnemy::ENEMYTYPE_N_WAY1, CEnemy::BOSSTYPE_NONE);
		}
	}

	//突進する敵を生成
	//if (pKeyBoard->GetTrigger(DIK_J) == true)
	if (m_nEnemyTime == ENEMY_RESPAWNTIME + 4500)
	{
		for (int nCnt = 0; nCnt <= 7; nCnt++)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3((70 + ((float)nCnt) * 100), 0.0f, 0.0f),
				D3DXVECTOR3(45, 45, 0), D3DXVECTOR3(0.0f, 1.2f, 0), CEnemy::ENEMYTYPE_RUSH, CEnemy::BOSSTYPE_NONE);
		}

	}

	//突進する敵を生成
	//if (pKeyBoard->GetTrigger(DIK_K) == true)
	if (m_nEnemyTime == ENEMY_RESPAWNTIME + 4700)
	{
		for (int nCnt = 0; nCnt <= 7; nCnt++)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3((40 + ((float)nCnt) * 100), 0.0f, 0.0f),
				D3DXVECTOR3(45, 45, 0), D3DXVECTOR3(0.0f, 1.2f, 0), CEnemy::ENEMYTYPE_RUSH, CEnemy::BOSSTYPE_NONE);
		}

	}

	//幻覚弾を撃つ敵を生成
	if (pKeyBoard->GetTrigger(DIK_I) == true)
	//if (m_nCntBullet % 300 == 0)
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(400, 200, 0.0f), D3DXVECTOR3(100, 100, 0), D3DXVECTOR3(0, 0, 0), CEnemy::ENEMYTYPE_NONE, CEnemy::BOSSTYPE_ILLUSION);

	}

	//追尾弾を撃つ敵を生成
	if (pKeyBoard->GetTrigger(DIK_M) == true)
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(400, 150, 0.0f), D3DXVECTOR3(25, 25, 0), D3DXVECTOR3(0, 0, 0), CEnemy::ENEMYTYPE_NORMAL2, CEnemy::BOSSTYPE_NONE);

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

	//リザルトへ移動
	if (m_transition == TRANSITION_RESULT)
	{
		if (m_pPlayer->CPlayer::GetPlayerState() == CPlayer::PLAYERSTATE_DEATH)
		{
			m_nCntResult++;

			//スコアの保存
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
// 描画処理
//*****************************************************************************
void CGame::Draw(void)
{

}

//*****************************************************************************
// 爆発情報処理
//*****************************************************************************
CExplosion*CGame::GetExplosion(void)
{
	return m_pExplosion;
}

//*****************************************************************************
// 弾情報処理
//*****************************************************************************
CBullet*CGame::GetBullet(void)
{
	return m_pBullet;
}

//*****************************************************************************
// 背景情報処理
//*****************************************************************************
CBg*CGame::GetBg(void)
{
	return m_pBg;
}

//*****************************************************************************
// ゲーム背景情報処理
//*****************************************************************************
CGame_Screen*CGame::GetGame_Screen(void)
{
	return m_pGame_Screen;
}

//*****************************************************************************
// プレイヤー情報処理
//*****************************************************************************
CPlayer*CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//*****************************************************************************
// 敵情報処理
//*****************************************************************************
CEnemy*CGame::GetEnemy(void)
{
	return m_pEnemy;
}

//*****************************************************************************
// スコア情報処理
//*****************************************************************************
CScore*CGame::GetScore(void)
{
	return m_pScore;
}

//*****************************************************************************
// スコア情報処理
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