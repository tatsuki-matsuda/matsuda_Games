//=============================================================================
//
// メイン処理 [enemy.cpp]
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
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture[MAX_TEXTURE] = {};			// テクスチャ
D3DXVECTOR3 CEnemy::m_Craetepos[10] = {};							// 位置

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CEnemy::CEnemy(int nPriority) :CScene2D(nPriority)
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CEnemy::~CEnemy()
{

}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, ENEMYTYPE enemyType)
{
	//動的確保
	CEnemy* pEnemy;
	pEnemy = new CEnemy;


	//敵生成
	pEnemy->SetEnemyType(enemyType); 

	//初期の呼び出し
	pEnemy->Init(pos, scale, move);

	//テクスチャの呼び出し
	//for (int nCntTex = 0; nCntTex < 1; nCntTex++)
	//{
	//	pEnemy->BindTexture(m_pTexture[nCntTex]);
	//}

	//値を返す
	return pEnemy;

}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move)
{
	//大きさを設定
	m_scale = scale;

	//移動を設定
	m_move = move;

	//種類
	SetObjType(OBJTYPE_ENEMY);

	//弾生成用の座標
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

	//敵の種類によってゲージを生成するかどうか決める
	if (m_EnemyType == ENEMYTYPE_REFLECTION)
	{
		//体力値の設定
		m_nLife = ENEMY_LIFE;

		//ゲージの生成
		m_pLifeGauge = CLifeGauge::Create(D3DXVECTOR3(50.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 15.0f, 0.0f), m_nLife);
	}

	if (m_EnemyType == ENEMYTYPE_REFLECTION_UPDAWN)
	{
		//体力値の設定
		m_nLife = ENEMY_LIFE;

		//ゲージの生成
		m_pLifeGauge = CLifeGauge::Create(D3DXVECTOR3(50.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 15.0f, 0.0f), m_nLife);
	}

	if (m_EnemyType == ENEMYTYPE_CROSSING)
	{
		//体力値の設定
		m_nLife = ENEMY_LIFE;

		//ゲージの生成
		m_pLifeGauge = CLifeGauge::Create(D3DXVECTOR3(50.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 15.0f, 0.0f), m_nLife);
	}

	if (m_EnemyType == ENEMYTYPE_NORMAL1)
	{
		//体力値の設定
		m_nLife = 50;
	}

	if (m_EnemyType == ENEMYTYPE_NORMAL3_R)
	{
		//体力値の設定
		m_nLife = 50;
	}

	if (m_EnemyType == ENEMYTYPE_NORMAL3_L)
	{
		//体力値の設定
		m_nLife = 50;
	}

	if (m_EnemyType == ENEMYTYPE_NORMAL4)
	{
		//体力値の設定
		m_nLife = 150;
	}

	if (m_EnemyType == ENEMYTYPE_N_WAY1)
	{
		//体力値の設定
		m_nLife = 150;
	}

	if (m_EnemyType == ENEMYTYPE_N_WAY2)
	{
		//体力値の設定
		m_nLife = 150;
	}

	////体力値の設定
	//m_nLife = ENEMY_LIFE;

	//つかわれてるかどうか
	m_bUninit = false;

	//交差間隔カウントの初期値
	m_nCntCrossingTime = 0;

	//撃ち始めカウントの初期値
	m_nBulletStartCnt = 0;

	m_nCntTime = 0;

	//敵出現カウント
	m_nEnemyAppearanceCnt = 0;

	//敵消滅後出現カウント
	m_nEnemyCnt = 0;

	//敵移動カウント
	m_nEnemymoveCnt = 0;

	m_posDeath = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//　出現時の体力を保存
	m_nMaxLife = m_nLife;

	//初期化の呼び出し
	CScene2D::Init(pos, scale);

	//値を返す
	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CEnemy::Uninit(void)
{
	//終了の呼び出し
	CScene2D::Uninit();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CEnemy::Update(void)
{
	//位置の取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//スコアの取得
	CScore *pScore;
	pScore = CGame::GetScore();

	//対角線の長さ
	m_angle = sqrtf(15 * 15 + 15 * 15);

	//対角線の角度
	float fAngle = atan2f(5, 5);

	//発射時間
	m_timer++;

	m_nEnemyAppearanceCnt++;


	//交差弾カウントを足す
	m_nCntCrossingTime++;

	//敵の種類が通常弾1を撃つ敵の場合
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
				//カウント
				if (m_timer % 20 == 0)
				{
					for (int nCnt = 0; nCnt < 20; nCnt++)
					{
						//全方位弾の生成
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
				//敵の消滅
				m_bUninit = true;
			}
		}

		//体力が0以下になった場合
		if (m_nLife <= 0)
		{
			//敵の消滅
			m_bUninit = true;

			Uninit();

			//爆発の生成
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

	//敵の種類が通常弾2を撃つ敵の場合
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

		//		//カウント
		//		if (m_timer % 20 == 0)
		//		{
		//			////ホーミング弾の生成
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
		//		//敵の消滅
		//		m_bUninit = true;
		//	}
		//}

		////体力が0以下になった場合
		//if (m_nLife <= 0)
		//{
		//	//敵の消滅
		//	m_bUninit = true;

		//	Uninit();

		//	//爆発の生成
		//	CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

		//	pScore->AddScore(200);

		//	return;
		//}
	}

	//敵の種類が右側から通常弾3を撃つ敵の場合
	if (m_EnemyType == ENEMYTYPE_NORMAL3_R)
	{
		//敵のテクスチャ
		BindTexture(m_pTexture[0]);

		//カウント
		if (m_timer % 8 == 0)
		{
			if (m_nCntTime <= 6)
			{
				//弾の生成
				CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(25, 25, 0),
					D3DXVECTOR3(m_move.x * -0.2f, m_move.y*3.0f, 0), D3DXVECTOR3(0, 0, 0),
					CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_NORMAL, CBullet::INFOTYPE_3);

				//弾の生成
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
			//敵の消滅
			m_bUninit = true;
		}
		//体力が0以下になった場合
		else if (m_nLife <= 0)
		{
			//敵の消滅
			m_bUninit = true;

			//爆発の生成
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(200);

			//終了処理の呼び出し
			Uninit();

			return;
		}
	}

	//敵の種類が左側から通常弾3を撃つ敵の場合
	if (m_EnemyType == ENEMYTYPE_NORMAL3_L)
	{
		//敵のテクスチャ
		BindTexture(m_pTexture[0]);

		//カウント
		if (m_timer % 8 == 0)
		{
			if (m_nCntTime <= 6)
			{
				//弾の生成
				CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(25, 25, 0),
					D3DXVECTOR3(m_move.x * -0.2f, m_move.y*3.0f, 0), D3DXVECTOR3(0, 0, 0),
					CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_NORMAL, CBullet::INFOTYPE_3);

				//弾の生成
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
			//敵の消滅
			m_bUninit = true;
		}

		//体力が0以下になった場合
		if (m_nLife <= 0)
		{
			//敵の消滅
			m_bUninit = true;

			//爆発の生成
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(200);

			//終了処理の呼び出し
			Uninit();

			return;
		}
	}

	//敵の種類が左側から通常弾3を撃つ敵の場合
	if (m_EnemyType == ENEMYTYPE_NORMAL4)
	{


		if (pos.y >= 100.0f)
		{
			m_move.x *= 0.0f;

			//カウント
			if (m_timer % 30 == 0)
			{
				if (m_nCntTime <= 5)
				{
					//弾の生成
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

		//カウント
		if (m_timer % 100 == 0)
		{
			m_nCntTime = 0;
		}

		if ((pos.y + m_scale.x / 2.0) >= SCREEN_HEIGHT || (pos.x + m_scale.x / 2.0) >= SCREEN_GAMEWIDTH)
		{
			//敵の消滅
			m_bUninit = true;
		}

		//体力が0以下になった場合
		if (m_nLife <= 0)
		{
			//敵の消滅
			m_bUninit = true;

			//爆発の生成
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(200);

			//終了処理の呼び出し
			Uninit();

			return;
		}
	}

	//敵の種類が追従弾を撃つ敵の場合
	if (m_EnemyType == ENEMYTYPE_HOMING)
	{
		////移動
		//if ((pos.x + m_scale.x / 2.0f) >= SCREEN_WIDTH - 400)
		//{
		//	m_move.x *= -1;
		//}

		//if (pos.x - m_scale.x / 2.0f <= 0.0f)
		//{
		//	m_move.x *= -1;
		//}

		////カウント
		//if (m_timer % 120 == 0)
		//{
		//	//弾の生成
		//	CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 50, pos.z), D3DXVECTOR3(20, 20, 0), D3DXVECTOR3(0, 10, 0),
		//		D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_HOMING, CBullet::INFOTYPE_1);
		//}

		////体力が0以下になった場合
		//if (m_nLife <= 0)
		//{
		//	//敵の消滅
		//	m_bUninit = true;

		//	Uninit();

		//	//爆発の生成
		//	CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

		//	pScore->AddScore(200);

		//	return;
		//}
	}

	//敵の種類が全方位交差弾を撃つ敵の場合
	if (m_EnemyType == ENEMYTYPE_CROSSING)
	{
		//敵のテクスチャ
		BindTexture(m_pTexture[4]);

		m_Craetepos[0] = D3DXVECTOR3(pos.x - 10, pos.y, 0);
		m_Craetepos[1] = D3DXVECTOR3(pos.x + 13, pos.y, 0);


	/*	SetLife(300);*/
		//移動
		if ((pos.x + m_scale.x / 2.0f) >= SCREEN_WIDTH - 930)
		{
			m_move.x *= -1;
		}

		if (pos.x - m_scale.x / 2.0f <= 430)
		{
			m_move.x *= -1;
		}

		//カウント
		if (m_timer % 120 == 0)
		{
			//敵の位置を参照して弾を生成
			OnDiffuesPos(m_Craetepos[m_nCntTime % 2 == 0], m_move);

			m_nCntTime++;

			//時間経過で弾を発射する間隔が短くなる
			if (m_nCntTime >= 5 && m_nCntTime <= 9)
			{
				//弾の生成時間
				m_timer = 30;
			}

			if (m_nCntTime >= 10 && m_nCntTime <= 19)
			{
				//弾の生成時間
				m_timer = 60;
			}

			if (m_nCntTime >= 20)
			{
				//弾の生成時間
				m_timer = 80;
			}

		}

		//体力が0以下になった場合
		if (m_nLife <= 0)
		{
			//敵の消滅
			m_bUninit = true;

			Uninit();

			//爆発の生成
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(1500);

			return;
		}

	
	}

	//敵の種類が全方位反射弾を撃つ敵の場合
	if (m_EnemyType == ENEMYTYPE_REFLECTION)
	{

		//敵のテクスチャ
		BindTexture(m_pTexture[4]);

		//タイマーで全方位反射弾を生成
		if (m_timer % 280 == 0)
		{

			//弾生成用の座標
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

			//敵の位置を参照して弾を生成
			OnDiffuesPos(m_Craetepos[rand() % 10], m_move);

			//発狂タイムカウント
			m_nCntTime++;
			
			//時間経過で弾を発射する間隔が短くなる
			if ((m_nCntTime >= 10 && m_nCntTime <= 17) ||( (float)m_nLife <= (float)m_nMaxLife *0.75f&& (float)m_nLife >= (float)m_nMaxLife *0.51f))
			{
				//弾の生成時間
				m_timer = 100;
			}

			if ((m_nCntTime >= 18 && m_nCntTime <= 25) || ((float)m_nLife <= (float)m_nMaxLife *0.5f && (float)m_nLife >= (float)m_nMaxLife *0.26f))
			{
				//弾の生成時間
				m_timer = 160;
			}

			if (m_nCntTime >= 26 || ((float)m_nLife <= (float)m_nMaxLife *0.25f))
			{
				//弾の生成時間
				m_timer = 220;
			}
		}

		//体力が0以下になった場合
		if (m_nLife <= 0)
		{
			//敵の消滅
			m_bUninit = true;

			//終了処理の呼び出し
			Uninit();

			m_posDeath = pos;

			//爆発の生成
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			//スコアの加算
			pScore->AddScore(2000);

			//上下反射弾敵の生成
			Create(m_posDeath, D3DXVECTOR3(100, 100, 0), D3DXVECTOR3(0, 0, 0),ENEMYTYPE_REFLECTION_UPDAWN);

			return;
		}
	}

	//敵の種類が上下反射弾を撃つ敵の場合
	if (m_EnemyType == ENEMYTYPE_REFLECTION_UPDAWN)
	{
		//敵のテクスチャ
		BindTexture(m_pTexture[4]);

		//移動
		if ((pos.x + m_scale.x / 2.0f) >= SCREEN_WIDTH - 400)
		{
			m_move.x *= -1;
		}

		if (pos.x - m_scale.x / 2.0f <= 0.0f)
		{
			m_move.x *= -1;
		}

		//座標の設定
		if (m_timer % 130 == 0)
		{
			
			m_Craetepos[0] = D3DXVECTOR3(pos.x, pos.y, 0);
			m_Craetepos[1] = D3DXVECTOR3(pos.x + 15, pos.y, 0);

			OnDiffuesPos(m_Craetepos[rand() % 2], m_move);

		}

		m_nBulletStartCnt++;

		//体力が0以下になった場合
		if (m_nLife <= 0)
		{
			//敵の消滅
			m_bUninit = true;

			Uninit();

			//爆発の生成
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(2000);

			m_nBulletStartCnt = 0;

			return;
		}
	}

	//敵の種類が全方位折り返し弾を撃つ敵の場合
	if (m_EnemyType == ENEMYTYPE_TURN)
	{

		//敵のテクスチャ
		BindTexture(m_pTexture[4]);

		//移動
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
				//全方位折り返し弾の生成
				CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(20, 20, 0),
					D3DXVECTOR3(sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)10)) * 4, cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)10)) * 4, 0),
					D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_TURN, CBullet::INFOTYPE_1);
			}
		}

		//体力が0以下になった場合
		if (m_nLife <= 0)
		{
			//敵の消滅
			m_bUninit = true;

			Uninit();

			//爆発の生成
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(1200);

			return;
		}
	}

	//敵の種類がn_way1弾を撃つ敵の場合
	if (m_EnemyType == ENEMYTYPE_N_WAY1)
	{
		//移動
		if ((pos.x + m_scale.x / 2.0f) >= SCREEN_WIDTH - 400)
		{
			m_move.x *= -1;
		}

		if (pos.x - m_scale.x / 2.0f <= 0.0f)
		{
			m_move.x *= -1;
		}

		//一番端の角度計算
		float fAngle = (D3DX_PI / 8) + (N_WAY_CREATE - 1) / 2 * (D3DX_PI / -7);

		//タイマーが一定の値で0になる場合
		if (m_timer % 20 == 0)
		{
			//値がn_way弾生成数を上回るまで、角度を計算して弾を生成
			for (int nCntway = 0; nCntway < N_WAY_CREATE; nCntway++, fAngle += D3DX_PI/12)
			{


			//n_way弾の生成
			CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(20, 20, 0), 
				D3DXVECTOR3(sinf(fAngle) * 4, cosf(fAngle) * 4, 0),
				D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_N_WAY1, CBullet::INFOTYPE_2);
			}
		}

		//体力が0以下になった場合
		if (m_nLife <= 0)
		{
			//敵の消滅
			m_bUninit = true;

			Uninit();

			//爆発の生成
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(500);

			return;
		}
	}

	//敵の種類がn_way2弾を撃つ敵の場合
	if (m_EnemyType == ENEMYTYPE_N_WAY2)
	{
		//敵のテクスチャ
		BindTexture(m_pTexture[4]);

		if ((pos.y + m_scale.x / 2.0) <= 0.0f&&m_nEnemymoveCnt <= 0)
		{
			m_move.y *= 1;
		}

		if ((pos.y + m_scale.x / 2.0) >= 250.0f)
		{
			m_move.y = 0;

			//タイマーが一定の値で0になる場合
			if (m_timer % 120 == 0)
			{
				CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(25, 25, 0),
					D3DXVECTOR3(0, 2, 0), D3DXVECTOR3(0, 0, 0),
					CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_N_WAY2, CBullet::INFOTYPE_1);
			}

			//タイマーが一定の値で0になる場合
			if (m_timer % 80 == 0)
			{
				m_nEnemymoveCnt++;
			}
	
			//カウントが一定値を上回るまで
			if (m_nEnemymoveCnt >= 8)
			{	
				//タイマーが一定の値で0になる場合
				if (m_timer % 120 == 0)
				{
					CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(25, 25, 0),
						D3DXVECTOR3(0, 2, 0), D3DXVECTOR3(0, 0, 0),
						CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_N_WAY2, CBullet::INFOTYPE_1);
				}
					//移動
					m_move.y = -2;

				if ((pos.y + m_scale.x / 2.0) <= 0.0f)
				{
					//敵の消滅
					m_bUninit = true;
				}
			}

			//体力が0以下になった場合
			if (m_nLife <= 0)
			{
				//敵の消滅
				m_bUninit = true;

				Uninit();

				//爆発の生成
				CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

				pScore->AddScore(500);

				return;
			}
		}
	}

	//移動換算
	pos += m_move;

	//位置の更新
	SetPosition(pos, m_scale);

	//大きさ
	SetScale(m_scale);

	if (m_bUninit == true)
	{
		Uninit();

		m_pLifeGauge = NULL;
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CEnemy::Draw(void)
{
	//描画の呼び出し
	CScene2D::Draw();
}

//*****************************************************************************
// テクスチャ読み込み処理
//*****************************************************************************
void CEnemy::Load(void)
{
	//デバイスの設定
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy_Keima.png", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy_Kasya.png", &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy_Ginsyou.png", &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy_Kinsyou.png", &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy_Ousyou.png", &m_pTexture[4]);
}

//*****************************************************************************
// テクスチャ破棄処理
//*****************************************************************************
void CEnemy::Unload(void)
{
	for (int nCntTex = 0; nCntTex < 5; nCntTex++)
	{
		//テクスチャの開放
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}

//*****************************************************************************
// 敵情報処理
//*****************************************************************************
CEnemy::ENEMYTYPE CEnemy::GetEnemyType(void)
{
	return m_EnemyType;
}

//*****************************************************************************
// 敵情報の設定処理
//*****************************************************************************
void CEnemy::SetEnemyType(ENEMYTYPE enemyType)
{
	m_EnemyType = enemyType;
}

//*****************************************************************************
// 弾の位置生成処理
//*****************************************************************************
void CEnemy::OnDiffuesPos(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// Create内の情報
	// 1 pos, 2 scale. 3 move, 4 rot, 5 bulletType, 6 attackType, 7 infoType

	//回転通常弾生成時の処理
	//if (m_EnemyType == ENEMYTYPE_NORMAL2)
	//{

	//	for (int nCnt = 0; nCnt < 40; nCnt++)
	//	{

	//		//右交差弾の生成
	//		CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(25, 25, 0),
	//			D3DXVECTOR3(sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)20)) * 4, cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)20)) * 4, 0),
	//			D3DXVECTOR3(0, (float)nCnt, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_NORMAL, CBullet::INFOTYPE_2);
	//	}
	//}

	//全方位交差弾生成時の処理
	if (m_EnemyType == ENEMYTYPE_CROSSING)
	{
		
		for (int nCnt = 0; nCnt < 40; nCnt++)
		{
			//左交差弾の生成
			CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(25, 25, 0),
				D3DXVECTOR3(sinf(D3DX_PI * 0.5f * ((float)nCnt / (float)10)) * 4, cosf(D3DX_PI * 0.5f * ((float)nCnt / (float)10)) * 4, 0),
				D3DXVECTOR3(0, (float)nCnt, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_CROSSING, CBullet::INFOTYPE_1);

			//右交差弾の生成
			CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(25, 25, 0),
				D3DXVECTOR3(sinf(D3DX_PI * 0.5f * ((float)nCnt / (float)10)) * 4, cosf(D3DX_PI * 0.5f * ((float)nCnt / (float)10)) * 4, 0),
				D3DXVECTOR3(10, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_CROSSING, CBullet::INFOTYPE_2);
		}
	}

	//全方位反射弾生成時の処理
	if (m_EnemyType == ENEMYTYPE_REFLECTION)
	{
		for (int nCnt = 0; nCnt < 40; nCnt++)
		{
			//全方位弾の生成
			CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(20, 20, 0),
				D3DXVECTOR3(sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)20)) * 3, cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)20)) * 3, 0),
				D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_REFLECTION, CBullet::INFOTYPE_1);
		}
	}

	//上下反射弾生成時の処理
	if (m_EnemyType == ENEMYTYPE_REFLECTION_UPDAWN)
	{
		//位置を参照し離れた位置から弾を生成
		float fLength = 400.0f + rand() % 30;

		if (m_nBulletStartCnt >= 150)
		{
			for (int nCnt = 0; nCnt < 180; nCnt++)
			{
				//反射弾の生成
				CBullet::Create(D3DXVECTOR3((pos.x) + fLength * sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)) * 2, -250 + fLength *  cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)), pos.z) *1.0f,
					D3DXVECTOR3(20, 20, 0), D3DXVECTOR3(sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)) * 6, cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)) * 6, 0),
					D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_REFLECTION, CBullet::INFOTYPE_2);

				//反射弾の生成
				CBullet::Create(D3DXVECTOR3((pos.x) + fLength * sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)) * 2, SCREEN_HEIGHT + 50 + fLength *  cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)), pos.z) *1.0f,
					D3DXVECTOR3(20, 20, 0), D3DXVECTOR3(sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)) * 6, cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)) * 6, 0),
					D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_REFLECTION, CBullet::INFOTYPE_2);
			}
		}
	}
}

//*****************************************************************************
// テクスチャ情報処理
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemy::GetTexture(int nCntTex)
{
	return m_pTexture[nCntTex];
}
