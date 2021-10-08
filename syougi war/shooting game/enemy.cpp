//=============================================================================
//
// メイン処理 [enemy.cpp]
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

	//敵の状態
	SetEnemyState(ENEMYSTATE_NORMAL);

	////座標生成
	//m_Craetepos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_Craetepos[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_Craetepos[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_Craetepos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_Craetepos[4] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_Craetepos[5] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_Craetepos[6] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_Craetepos[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_Craetepos[8] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_Craetepos[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//生成座標
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

	//値が存在するランダムな位置をボスの位置として保存
	m_posBoss = m_Craetepos[rand() % 10];

	//体力の生成及び種類によってゲージを生成するかどうか決める

	//反射弾を撃つ敵
	if (m_EnemyType == ENEMYTYPE_REFLECTION)
	{
		//体力値の設定
		m_nLife = ENEMY_LIFE;

		//ゲージの生成
		m_pLifeGauge = CLifeGauge::Create(D3DXVECTOR3(50.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 15.0f, 0.0f), m_nLife);
	}

	//上下反射弾を撃つ敵
	if (m_EnemyType == ENEMYTYPE_REFLECTION_UPDAWN)
	{
		//体力値の設定
		m_nLife = ENEMY_LIFE;

		//ゲージの生成
		m_pLifeGauge = CLifeGauge::Create(D3DXVECTOR3(50.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 15.0f, 0.0f), m_nLife);
	}

	//交差弾を撃つ敵
	if (m_EnemyType == ENEMYTYPE_CROSSING)
	{
		//体力値の設定
		m_nLife = ENEMY_LIFE;

		//ゲージの生成
		m_pLifeGauge = CLifeGauge::Create(D3DXVECTOR3(50.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 15.0f, 0.0f), m_nLife);
	}

	//回転弾を撃つ敵
	if (m_EnemyType == ENEMYTYPE_ROTATION)
	{
		//体力値の設定
		m_nLife = ENEMY_LIFE;

		//ゲージの生成
		m_pLifeGauge = CLifeGauge::Create(D3DXVECTOR3(50.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 15.0f, 0.0f), m_nLife);
	}

	//通常弾1を撃つ敵
	if (m_EnemyType == ENEMYTYPE_NORMAL1)
	{
		//体力値の設定
		m_nLife = 250;
	}

	//通常弾3を撃つ敵
	if (m_EnemyType == ENEMYTYPE_NORMAL3_R)
	{
		//体力値の設定
		m_nLife =100;
	}

	//通常弾3を撃つ敵
	if (m_EnemyType == ENEMYTYPE_NORMAL3_L)
	{
		//体力値の設定
		m_nLife = 100;
	}

	//通常弾4Rを撃つ敵
	if (m_EnemyType == ENEMYTYPE_NORMAL4_R)
	{
		//体力値の設定
		m_nLife = 150;
	}

	//通常弾4Lを撃つ敵
	if (m_EnemyType == ENEMYTYPE_NORMAL4_L)
	{
		//体力値の設定
		m_nLife = 150;
	}

	//N_WAY弾を撃つ敵
	if (m_EnemyType == ENEMYTYPE_N_WAY1)
	{
		//体力値の設定
		m_nLife = 350;
	}

	//N_WAY弾を撃つ敵
	if (m_EnemyType == ENEMYTYPE_N_WAY2)
	{
		//体力値の設定
		m_nLife = 350;
	}

	//N_WAY弾を撃つ敵
	if (m_EnemyType == ENEMYTYPE_RUSH)
	{
		//体力値の設定
		m_nLife = 40;
	}

	//つかわれてるかどうか
	m_bUninit = false;

	//交差間隔カウントの初期値
	m_nCntCrossingTime = 0;

	//撃ち始めカウントの初期値
	m_nBulletStartCnt = 0;

	m_nCntTime = 0;

	m_nCntBullet = 0;

	m_fLength = 0;

	//フェーズ状態
	m_PhaseType = PHASETYPE_NONE;

	//敵出現カウント
	m_nEnemyAppearanceCnt = 0;

	//敵消滅後出現カウント
	m_nEnemyCnt = 0;

	//敵移動カウント
	m_nEnemymoveCnt = 0;

	//敵の色
	m_nCntColor = 0;

	//敵死亡時の位置を保存
	m_posDeath = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//通常敵の移動カウント
	m_nNormalEnemyMove=0;

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

	EnemyState();

	//対角線の長さ
	m_fangle = sqrtf(15 * 15 + 15 * 15);

	//対角線の角度
	float fAngle = atan2f(5, 5);

	//発射時間
	m_timer++;

	//サウンドのポインタ
	CSound *pSound = CManager::GetSound();

	m_nCntColor++;

	m_nEnemyAppearanceCnt++;

	//当たり判定
	OnCollision();

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
				if (m_timer % 30 == 0)
				{
					for (int nCnt = 0; nCnt < 20; nCnt++)
					{
						//全方位弾の生成
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

			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

			pScore->AddScore(2000);

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

			pScore->AddScore(350);

			//爆発音
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

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

			pScore->AddScore(350);

			//爆発音
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

			//終了処理の呼び出し
			Uninit();

			return;
		}
	}

	//敵の種類が左側から通常弾4を撃つ敵の場合
	if (m_EnemyType == ENEMYTYPE_NORMAL4_R)
	{
		BindTexture(m_pTexture[0]);
		//m_move.x = 3.0f;

		// 通常敵移動カウント
		m_nNormalEnemyMove++;

		//移動値を保存
		if (m_nNormalEnemyMove < 199)
		{
			m_moveSave = m_move;
		}

		//移動カウントが一定の値を超えるまで
		if (m_nNormalEnemyMove > 200)
		{
			m_move.y = 0.0f;

			m_move.x = 0.0f;

			//発射タイミング
			if (m_timer % 15 == 0)
			{		
				//弾の生成
				CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(25, 25, 0),
					D3DXVECTOR3(0.0f, 2.0f, 0), D3DXVECTOR3(0, 0, 0),
					CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_NORMAL, CBullet::INFOTYPE_1);

				//発射カウント
				m_nCntBullet++;
			}

			//発射カウントが一定の値を超えるまで
			if (m_nCntBullet > 5)
			{
				//カウントをゼロに
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

		//移動カウントが一定の値を超えるまで
		if (m_nNormalEnemyMove < 199)
		{
			//敵が一定の位置を超えるまで
			if ((pos.x - m_scale.x / 2.0f) < 20.0f)
			{
				//判定を計算
				pos.x = m_scale.x / 2.0f + 20.0f;

				//移動
				m_move.x *= -0.9f;

				//情報を代入
				SetPosition(pos, m_scale);
			}
			else if ((pos.x + m_scale.x / 2.0f) > SCREEN_GAMEWIDTH / 2.0f)
			{

				//判定を計算
				m_move.x *= -0.9f;

				//移動
				pos.x = SCREEN_GAMEWIDTH / 2.0f - m_scale.x / 2.0f;

				//情報を代入
				SetPosition(pos, m_scale);
			}
		}

		//下に行くまで
		if ((pos.y + m_scale.y / 2.0f) >= SCREEN_HEIGHT)
		{
			//敵消滅
			m_bUninit = true;
		}

		//体力が0以下になった場合
		if (m_nLife <= 0)
		{
			//敵の消滅
			m_bUninit = true;

			//爆発の生成
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(500);

			//爆発音
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

			//終了処理の呼び出し
			Uninit();

			return;
		}
	}

	//敵の種類が左側から通常弾4を撃つ敵の場合
	if (m_EnemyType == ENEMYTYPE_NORMAL4_L)
	{
		BindTexture(m_pTexture[0]);
		//m_move.x = 3.0f;

		// 通常敵移動カウント
		m_nNormalEnemyMove++;

		//移動値を保存
		if (m_nNormalEnemyMove < 199)
		{
			m_moveSave = m_move;
		}

		//移動カウントが一定の値を超えるまで
		if (m_nNormalEnemyMove > 200)
		{
			m_move.y = 0.0f;

			m_move.x = 0.0f;

			//発射タイミング
			if (m_timer % 15 == 0)
			{
				//弾の生成
				CNormal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z), D3DXVECTOR3(25, 25, 0),
					D3DXVECTOR3(0.0f, 2.0f, 0), D3DXVECTOR3(0, 0, 0),
					CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_NORMAL, CBullet::INFOTYPE_1);

				//発射カウント
				m_nCntBullet++;
			}

			//発射カウントが一定の値を超えるまで
			if (m_nCntBullet > 5)
			{
				//カウントをゼロに
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

		//移動カウントが一定の値を超えるまで
		if (m_nNormalEnemyMove < 199)
		{
			//敵が一定の位置を超えるまで
			if ((pos.x - m_scale.x / 2.0f) < SCREEN_GAMEWIDTH / 2.2f)
			{
				//判定を計算
				pos.x = m_scale.x / 2.0f + SCREEN_GAMEWIDTH / 2.2f;

				//移動
				m_move.x *= -0.9f;

				//情報を代入
				SetPosition(pos, m_scale);
			}
			else if ((pos.x + m_scale.x / 2.0f) > SCREEN_GAMEWIDTH )
			{

				//判定を計算
				m_move.x *= -0.9f;

				//移動
				pos.x = SCREEN_GAMEWIDTH - m_scale.x / 2.0f;

				//情報を代入
				SetPosition(pos, m_scale);
			}
		}

		//下に行くまで
		if ((pos.y + m_scale.y / 2.0f) >= SCREEN_HEIGHT)
		{
			//敵消滅
			m_bUninit = true;
		}

		//体力が0以下になった場合
		if (m_nLife <= 0)
		{
			//敵の消滅
			m_bUninit = true;

			//爆発の生成
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(500);

			//爆発音
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

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

			pScore->AddScore(40000);

			//爆発音
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

			return;
		}

	
	}

	//敵の種類が全方位反射弾を撃つ敵の場合
	if (m_EnemyType == ENEMYTYPE_REFLECTION)
	{

		//敵のテクスチャ
		BindTexture(m_pTexture[4]);

		//移動カウント
		m_nEnemymoveCnt++;

		//値が一定値以下の場合
		if (m_nEnemymoveCnt <= 280)
		{
			//移動
			m_move.y = 0.8f;
		}
		else
		{
			//生成座標
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

			//角度計算
			float VectorX = m_posBoss.x - pos.x;
			float VectorY = m_posBoss.y - pos.y;
			float fAngle = atan2f(VectorX, VectorY);
			float fLengthObj = sqrtf(VectorX*VectorX + VectorY*VectorY);

			//値を代入
			float moveX = sinf(fAngle)*1.5f;
			float moveY = cosf(fAngle)*1.5f;

			//値を移動値に換算
			m_move.x = moveX;
			m_move.y = moveY;

			//座標の範囲
			m_fLength = 5.0f;

			//座標が指定された座標の範囲を超えた場合
			if (fLengthObj <= m_fLength)
			{

				//値が存在するランダムな位置をボスの位置として保存
				m_posBoss = m_Craetepos[rand() % 10];

				//発狂タイムカウント
				m_nCntTime++;

				//値を移動値に換算
				m_move.x = 0.0f;
				m_move.y = 0.0f;

				//カウントが一定の値で0になる場合
				if (m_nCntTime % 3 == 0)
				{
					//敵の位置を参照して弾を生成
					OnDiffuesPos(pos, m_move);
				}

			}

			//発狂1　カウントか残存体力に応じて弾の発射回数を増加させる
			if (m_nCntTime >= 20 || ((float)m_nLife < (float)m_nMaxLife *0.75f))
			{
				//フェーズタイプ
				m_PhaseType = PHASETYPE_1;
			}

			//発狂2
			if (m_nCntTime >= 60 || ((float)m_nLife < (float)m_nMaxLife*0.5f))
			{
				//フェーズタイプ
				m_PhaseType = PHASETYPE_2;
			}

			//発狂3
			if (m_nCntTime >= 100 || ((float)m_nLife < (float)m_nMaxLife *0.25f))
			{
				//フェーズタイプ
				m_PhaseType = PHASETYPE_3;
			}
		}

		//フェーズタイプ
		switch (m_PhaseType)
		{
			case PHASETYPE_1:

				//タイマーが一定の値で0になる場合
				if (m_timer % 480 == 0)
				{
					//敵の位置を参照して弾を生成
					OnDiffuesPos(pos, m_move);
				}

			break;

			case PHASETYPE_2:

				//タイマーが一定の値で0になる場合
				if (m_timer % 360 == 0)
				{
					//敵の位置を参照して弾を生成
					OnDiffuesPos(pos, m_move);
				}

				break;
			case PHASETYPE_3:

				//タイマーが一定の値で0になる場合
				if (m_timer % 240 == 0)
				{
					//敵の位置を参照して弾を生成
					OnDiffuesPos(pos, m_move);
				}

				break;
		}

		//体力が0以下になった場合
		if (m_nLife <= 0)
		{
			//敵の消滅
			m_bUninit = true;

			//終了処理の呼び出し
			Uninit();

			//消滅した位置を保存
			m_posDeath = pos;

			//爆発の生成
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			//爆発音
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

			//スコアの加算
			pScore->AddScore(40000);

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


		if (m_nEnemymoveCnt <= 1)
		{
			//生成座標
			m_Craetepos[0] = D3DXVECTOR3(420, 200, 0.0f);
		}

		//値が存在する位置をボスの位置として保存
		m_posBoss = m_Craetepos[0];


		//角度計算
		float VectorX = m_posBoss.x - pos.x;
		float VectorY = m_posBoss.y - pos.y;
		float fAngle = atan2f(VectorX, VectorY);
		float fLengthObj = sqrtf(VectorX*VectorX + VectorY*VectorY);

		//値を代入
		float moveX = sinf(fAngle)*1.5f;
		float moveY = cosf(fAngle)*1.5f;

		//値を移動値に換算
		m_move.x = moveX;
		m_move.y = moveY;

		//範囲
		m_fLength = 10;

		//座標が指定された座標の範囲を超えた場合
		if (fLengthObj <= m_fLength)
		{
			m_nEnemymoveCnt++;
		}

		//座標の設定
		if (m_timer % 130 == 0)
		{		
			m_Craetepos[0] = D3DXVECTOR3(pos.x, pos.y, 0);
			m_Craetepos[1] = D3DXVECTOR3(pos.x + 15, pos.y, 0);

			OnDiffuesPos(m_Craetepos[rand() % 2 ], m_move);
		}

		//体力が0以下になった場合
		if (m_nLife <= 0)
		{
			//敵の消滅
			m_bUninit = true;

			Uninit();

			//爆発の生成
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(40000);

			//爆発音
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

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
		BindTexture(m_pTexture[2]);

		m_nEnemymoveCnt++;

		m_moveSave = m_move;

		//移動
		if (m_nEnemymoveCnt >= 450 && m_nCntBullet < 5)
		{
			m_move.y = 0.0f;

		}


		//一番端の角度計算
		float fAngle = (D3DX_PI / 8) + (N_WAY_CREATE - 1) / 2 * (D3DX_PI / -7);

		if (m_nEnemymoveCnt >= 500)
		{
			//タイマーが一定の値で0になる場合
			if (m_timer % 50 == 0)
			{
				//値がn_way弾生成数を上回るまで、角度を計算して弾を生成
				for (int nCntway = 0; nCntway < N_WAY_CREATE; nCntway++, fAngle += D3DX_PI / 12)
				{

					//n_way弾の生成
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

	
	

		//下に行くまで
		if ((pos.y + m_scale.y / 2.0f) <= 0.0f&&m_nEnemymoveCnt > 1000)
		{
			//敵消滅
			m_bUninit = true;
		}

		//体力が0以下になった場合
		if (m_nLife <= 0)
		{
			//敵の消滅
			m_bUninit = true;

			//爆発音
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

			Uninit();

			//爆発の生成
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			pScore->AddScore(1500);

			return;
		}
	}

	//敵の種類がn_way2弾を撃つ敵の場合
	if (m_EnemyType == ENEMYTYPE_N_WAY2)
	{
		//敵のテクスチャ
		BindTexture(m_pTexture[3]);

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

				//爆発音
				pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

				return;
			}
		}
	}

	//敵の種類が突進する敵の場合
	if (m_EnemyType == ENEMYTYPE_RUSH)
	{
		//敵のテクスチャ
		BindTexture(m_pTexture[1]);

		//移動カウント
		m_nEnemymoveCnt++;

		//カウントで敵の移動を換算
		if (m_nEnemymoveCnt >= 10)
		{
			//移動値を保存
			m_moveSave = m_move;
		}

		//移動の値が一定値以下の場合
		if (m_moveSave.y <= 1.0f&& m_nEnemymoveCnt>=10)
		{

			//震える動作
			if (m_nEnemymoveCnt >= 70&& m_nEnemymoveCnt <= 300)
			{
				//移動値を0に
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
				//途中から激しく
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

			//突進攻撃
			if (m_nEnemymoveCnt >= 300)
			{
				m_move.y = -20.0f;
			}
		}

		//移動の値が一定値以上の場合
		if (m_moveSave.y >= 1.0f && m_nEnemymoveCnt >= 10)
		{

			//震える動作
			if (m_nEnemymoveCnt >= 70 && m_nEnemymoveCnt <= 300)
			{
				//移動値を0に
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
				//途中から激しく
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

			//突進攻撃
			if (m_nEnemymoveCnt >= 300)
			{
				m_move.y = 20.0f;
			}
		}

		if (m_nEnemymoveCnt > 700)
		{
			m_bUninit = true;
		}

		//体力が0以下になった場合
		if (m_nLife <= 0)
		{
			//敵の消滅
			m_bUninit = true;

			Uninit();

			//爆発の生成
			CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

			//爆発音
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

			pScore->AddScore(700);

			return;
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
// 判定処理
//*****************************************************************************
void CEnemy::OnCollision(void)
{
	//位置の取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//位置の更新
	SetPosition(pos, m_scale);

	for (int nCntPriority = 0; nCntPriority < CScene::OBJTYPE_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			CScene*pScene;
			pScene = CScene::GetScene(nCntPriority, nCntScene);

			if (pScene != NULL)
			{
				//種類判定呼び出し
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				//タイプがプレイヤーの場合
				if (objType == OBJTYPE_PLAYER)
				{
					CPlayer *pPlayer = (CPlayer*)pScene;

					//位置の取得
					D3DXVECTOR3 Playerpos;
					Playerpos = pPlayer->GetPosition();

					//位置の取得
					D3DXVECTOR3 Playerscale;
					Playerscale = pPlayer->GetScale();

					/*bool bPlayer = pPlayer->Uninit();*/

					//当たり判定
					if (pos.x + m_scale.x / 2.0f > Playerpos.x - Playerscale.x / 12.0f&&
						pos.x - m_scale.x / 2.0f < Playerpos.x + Playerscale.x / 12.0f&&
						pos.y + m_scale.y / 2.0f > Playerpos.y - Playerscale.y / 12.0f&&
						pos.y - m_scale.y / 2.0f < Playerpos.y + Playerscale.y / 12.0f)
					{

						//被弾時の処理
						if (CGame::GetPlayer()->GetPlayerState() == CPlayer::PLAYERSTATE_NORMAL)
						{
							//値を代入
							m_nPlayerCnt = 0;

							if (m_EnemyState == ENEMYTYPE_RUSH)
							{
								//敵消滅
								m_bUninit = true;
							}

							//サウンドのポインタ
							CSound *pSound = CManager::GetSound();

							//爆発音
							pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

							//爆発の生成
							CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

							//プレイヤーの状態
							pPlayer->SetPlayerState(CPlayer::PLAYERSTATE_DEATH);

							// ライフ情報を取得
							int nLife = CGame::GetLife()->GetLife();

							// ライフの設定
							CGame::GetLife()->SetLife(nLife - 1);
						}
						else if (CGame::GetPlayer()->GetPlayerState() == CPlayer::PLAYERSTATE_REVIVAL)
						{

							//被弾後カウント
							m_nPlayerCnt++;


							//被弾しても消滅しない
							m_bUninit = false;
						}
					}
				}
			}
		}
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
// 敵の状態
//*****************************************************************************
void CEnemy::EnemyState(void)
{
	switch (GetEnemyState())
	{
		//通常状態の敵だった場合
		 case ENEMYSTATE_NORMAL:

				m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	
	 	break;
	 
	 	//ダメージ状態の敵だった場合
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

		for (int nCnt = 0; nCnt < 180; nCnt++)
		{
			//反射弾の生成
			CBullet::Create(D3DXVECTOR3((pos.x) + fLength * sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)) * 2, -250 + fLength *  cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)), pos.z),
				D3DXVECTOR3(20, 20, 0),
				D3DXVECTOR3(sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)) * 6, cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)) * 6, 0),
				D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_REFLECTION, CBullet::INFOTYPE_2);

			//反射弾の生成
			CBullet::Create(D3DXVECTOR3((pos.x) + fLength * sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)) * 2, SCREEN_HEIGHT + 50 + fLength *  cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)), pos.z),
				D3DXVECTOR3(20, 20, 0), D3DXVECTOR3(sinf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)) * 6, cosf(D3DX_PI * 1.0f * ((float)nCnt / (float)90)) * 6, 0),
				D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_ENEMY, CBullet::ATTACKTYPE_REFLECTION, CBullet::INFOTYPE_2);
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
