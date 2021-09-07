//=============================================================================
//
// メイン処理 [game.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "enemy.h"
#include "life.h"
#include "fade.h"
#include "game.h"
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
CScore*CGame::m_pBulletNum = NULL;					// グレイズ変数
CBg*CGame::m_pBg = NULL;							// 背景変数
CGame_Screen*CGame::m_pGame_Screen = NULL;			// ゲーム背景変数
CExplosion*CGame::m_pExplosion = NULL;				// 爆発変数

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

	//初期化の呼び出し
	//CScene::Init(pos, scale);

	//背景テクスチャのロード
	CGame_Screen::Load();

	//背景テクスチャのロード
	CBg::Load();

	//ナンバーのアンロード
	CNumber::Load();

	//プレイヤーテクスチャのロード
	CPlayer::Load();

	//敵テクスチャのロード
	CEnemy::Load();

	//弾テクスチャのロード
	CBullet::Load();

	//爆発テクスチャのロード
	CExplosion::Load();

	//背景クラスの生成
	//m_pGame_Screen = CGame_Screen::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0));

	//背景クラスの生成
	m_pBg = CBg::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0));

	//プレイヤークラスの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(400, 550, 0), D3DXVECTOR3(50, 50, 0));

	//ナンバークラスの生成
	m_pScore = CScore::Create(D3DXVECTOR3(1000, 150, 0), D3DXVECTOR3(25, 45, 0),CScore::SCORETYPE_NORMAL);

	//グレイズポイントの生成
	m_pGraze = CScore::Create(D3DXVECTOR3(1000, 450, 0), D3DXVECTOR3(20, 35, 0), CScore::SCORETYPE_GRAZE);

	m_pBulletNum = CScore::Create(D3DXVECTOR3(1000, 600, 0), D3DXVECTOR3(20, 35, 0), CScore::SCORETYPE_NORMAL);

	m_nEnemyTime = 0;

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

	m_nEnemyTime++;

	//if (pKeyBoard->GetTrigger(DIK_L) == true)
	{
		//通常弾1を撃つ敵を生成
		if (m_nEnemyTime == ENEMY_RESPAWNTIME+1400)
		{
			for (int nCnt = 0; nCnt <= 3; nCnt++)
			{
				m_pEnemy = CEnemy::Create(D3DXVECTOR3(100 + (150.0f*(float)nCnt), -100.0f + (-500.0f*(float)nCnt), 0),
					D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(0, 3.0f, 0), CEnemy::ENEMYTYPE_NORMAL1);


			}
		}

		////通常弾2を撃つ敵を生成
		//if (pKeyBoard->GetTrigger(DIK_2) == true)
		//{

		//	m_pEnemy = CEnemy::Create(D3DXVECTOR3(100, -100.0f, 0),
		//		D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(0, 3.0f, 0), CEnemy::ENEMYTYPE_NORMAL2);


		//}

		//通常弾3を撃つ敵を生成
		if (m_nEnemyTime == ENEMY_RESPAWNTIME)
		{
			for (int nCnt = 0; nCnt <= 3; nCnt++)
			{

				m_pEnemy = CEnemy::Create(D3DXVECTOR3(600 + (200.0f*(float)nCnt), 50.0f, 0),
					D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(-2.0f, 0.8f, 0), CEnemy::ENEMYTYPE_NORMAL3_R);
			}
		}

		if (m_nEnemyTime == ENEMY_RESPAWNTIME+50)
		{
			for (int nCnt = 0; nCnt <= 3; nCnt++)
			{
				m_pEnemy = CEnemy::Create(D3DXVECTOR3(-100 + (-200.0f*(float)nCnt), 50.0f, 0),
					D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(2.0f, 0.8f, 0), CEnemy::ENEMYTYPE_NORMAL3_L);
			}
		}

		if (m_nEnemyTime == ENEMY_RESPAWNTIME+200)
		{
			for (int nCnt = 0; nCnt <= 3; nCnt++)
			{

				m_pEnemy = CEnemy::Create(D3DXVECTOR3(600 + (200.0f*(float)nCnt), 50.0f, 0),
					D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(-2.0f, 0.8f, 0), CEnemy::ENEMYTYPE_NORMAL3_R);
			}
		}

		if (m_nEnemyTime == ENEMY_RESPAWNTIME+360)
		{
			for (int nCnt = 0; nCnt <= 3; nCnt++)
			{
				m_pEnemy = CEnemy::Create(D3DXVECTOR3(-100 + (-200.0f*(float)nCnt), 5.0f, 0),
					D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(2.0f, 0.8f, 0), CEnemy::ENEMYTYPE_NORMAL3_L);
			}
		}

		if (m_nEnemyTime == ENEMY_RESPAWNTIME + 460)
		{
			for (int nCnt = 0; nCnt <= 3; nCnt++)
			{

				m_pEnemy = CEnemy::Create(D3DXVECTOR3(600 + (200.0f*(float)nCnt), 100.0f, 0),
					D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(-2.0f, 0.8f, 0), CEnemy::ENEMYTYPE_NORMAL3_R);
			}
		}

		if (m_nEnemyTime == ENEMY_RESPAWNTIME + 560)
		{
			for (int nCnt = 0; nCnt <= 3; nCnt++)
			{
				m_pEnemy = CEnemy::Create(D3DXVECTOR3(-100 + (-200.0f*(float)nCnt), 100.0f, 0),
					D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(2.0f, 0.8f, 0), CEnemy::ENEMYTYPE_NORMAL3_L);
			}
		}
	}

	////追従弾を撃つ敵を生成
	//if (pKeyBoard->GetTrigger(DIK_4) == true)
	//{
	//	m_pEnemy = CEnemy::Create(D3DXVECTOR3(400, 100, 0), D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(ENEMY_MOVE_X, 0, 0), CEnemy::ENEMYTYPE_HOMING);
	//}

	//通常弾敵4を撃つ敵を生成
	if (pKeyBoard->GetPress(DIK_J) == true)
	{
		CLife::Create(D3DXVECTOR3(1000.0f, 250.0f, 0.0f), D3DXVECTOR3(40.0f, 40.0f, 0.0f));
	}

	//交差弾を撃つ敵を生成
	if (pKeyBoard->GetTrigger(DIK_3) == true)
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(350, 150, 0), D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(0, 0, 0), CEnemy::ENEMYTYPE_CROSSING);
	}

		//反射弾を撃つ敵を生成
		if (m_nEnemyTime == ENEMY_RESPAWNTIME + 2800)
			//if (pKeyBoard->GetTrigger(DIK_6) == true)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(300, 200, 0), D3DXVECTOR3(100, 100, 0), D3DXVECTOR3(0, 0, 0), CEnemy::ENEMYTYPE_REFLECTION);
		}

	////上下反射弾を撃つ敵を生成
	//if (pKeyBoard->GetTrigger(DIK_3) == true)
	//{
	//	m_pEnemy = CEnemy::Create(D3DXVECTOR3(350, 200, 0), D3DXVECTOR3(100, 100, 0), D3DXVECTOR3(0, 0, 0), CEnemy::ENEMYTYPE_REFLECTION_UPDAWN);
	//}

	//折り返し弾を撃つ敵を生成
	if (pKeyBoard->GetTrigger(DIK_4) == true)
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(350, 200, 0), D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(3, 0, 0), CEnemy::ENEMYTYPE_TURN);
	}

	//n_Way弾1を撃つ敵を生成
	if (pKeyBoard->GetTrigger(DIK_1) == true)
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(250, 300, 0), D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(0, 0, 0), CEnemy::ENEMYTYPE_N_WAY1);
	}

	//n_Way弾2を撃つ敵を生成
	if (pKeyBoard->GetTrigger(DIK_2) == true)
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(200, -100, 0), D3DXVECTOR3(60, 60, 0), D3DXVECTOR3(0, 5, 0), CEnemy::ENEMYTYPE_N_WAY2);
	}

	//n_Way弾2を撃つ敵を生成
	if (pKeyBoard->GetTrigger(DIK_K) == true)
	{
		for (int nCnt = 0; nCnt <= 3; nCnt++)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(50, -100 + (-100.0f*(float)nCnt), 0),
				D3DXVECTOR3(45, 45, 0), D3DXVECTOR3(0.0f, 1.0f, 0), CEnemy::ENEMYTYPE_NORMAL4);
		}
	}

	m_pBulletNum->SetScore(0);
	int nCntBullet = 0;
	for (int nCnt = 0; nCnt < MAX_POLYGON; nCnt++)
	{
		CScene *pScene = CScene::GetScene(OBJTYPE_BULLET,nCnt);

		if (pScene != NULL)
		{
			nCntBullet++;
		}
	}

	m_pBulletNum->AddScore(nCntBullet);


	//タイトルへ移動
	if (pKeyBoard->GetTrigger(DIK_RETURN) == true)
	{
		CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TITLE);
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


CScore*CGame::GetBulletNum(void)
{
	return m_pBulletNum;
}

