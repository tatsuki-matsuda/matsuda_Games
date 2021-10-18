//=============================================================================
//
// メイン処理 [bullet.cpp]
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
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBullet::m_pTexture[MAX_TEXTURE] = {};			// テクスチャ


//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CBullet::CBullet(int nPriority) :CScene2D(nPriority)
{
	//大きさの初期値
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//移動の初期値
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//角度の初期値
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//体力値
	m_nLife = 500;

	////回転軸
	//m_fAngle = 0.0;

	//回転速度
	memset(&m_fAngleSpeed[0], 0, sizeof(m_fAngleSpeed));
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CBullet::~CBullet()
{

}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, D3DXVECTOR3 rot,
	BULLETTYPE bulletType, ATTACKTYPE attackType,INFOTYPE infoType)
{
	//動的確保
	CBullet* pBullet;
	pBullet = new CBullet;

	//初期化処理を呼び出し
	pBullet->Init(pos,scale,move,rot);

	//弾の情報の呼び出し
	pBullet->SetBulletType(bulletType);

	//攻撃種類情報の呼び出し
	pBullet->SetAttackType(attackType);

	//攻撃情報の呼び出し
	pBullet->SetInfoType(infoType);

	//テクスチャの呼び出し
	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		pBullet->BindTexture(m_pTexture[nCntTex]);
	}

	return pBullet;
}

//*****************************************************************************
//　初期化処理
//*****************************************************************************
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, D3DXVECTOR3 rot)
{
	//位置を設定
	m_posOrigin = pos;

	//弾に最も近い位置の計算を設定
	m_fLengthObj = 10000.0f;

	//m_nKeepObj = -1;

	m_posDeath = D3DXVECTOR3(0, 0, 0);

	//移動値を設定
	m_move = move;

	//大きさを設定
	m_scale = scale;

	//角度を設定
	m_rot = rot;

	//体力を設定
	m_nLife = 1000;

	//回転の値を設定
	m_fAngle = 0.0;

	//左回転の値を設定
	m_fAngleL = 0.0;

	//右回転の値を設定
	m_fAngleR = 0.0;

	//回転速度
	m_fAngleSpeed[0] = (float)-0.03f;
	m_fAngleSpeed[1] = (float)0.03;

	m_nPlayerCnt = 0;

	//左回転カウントの設定
	m_nCrossingTimeL = 0;

	//右回転カウントの設定
	m_nCrossingTimeR = 0;

	//反射カウントの設定
	m_nReflectionCnt = 0;

	//反射使用設定
	m_bGraze = false;

	//反射使用設定
	m_bReflection = false;

	//使われているかどうか
	m_bUninit = false;

	//種類
	SetObjType(OBJTYPE_BULLET);

	//CScene2Dを呼び出し
	CScene2D::Init(pos,scale);

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CBullet::Uninit(void)
{
	//CScene2Dから呼び出し
	CScene2D::Uninit();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CBullet::Update(void)
{
	//位置の取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//サウンドのポインタ
	CSound *pSound = CManager::GetSound();

	//寿命
	m_nLife--;

	

	if (m_BulletType == BULLETTYPE_ENEMY)
	{
		m_EnemyBulletpos = pos;
	}

	if (m_BulletType == BULLETTYPE_PLAYER)
	{
		m_PlayerBulletpos = pos;
	}


	//追跡弾の場合
	if (m_AttackType == ATTACKTYPE_HOMING)
	{
		m_nCnt++;

		if (m_nCnt % 3 == 0 && m_InfoType == INFOTYPE_1)
		{
			OnHoming();

			m_move.y *= 1.05f;
			m_move.x *= 1.05f;
		}

		//画面外処理
		if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP ||
			pos.y + m_scale.y / 2.0f > SCREEN_HEIGHT ||
			pos.x - m_scale.x / 2.0f < 0.0f ||
			pos.x + m_scale.x / 2.0f > SCREEN_GAMEWIDTH)
		{
			//消滅
			m_bUninit = true;
		}
	}

	//左交差弾の場合
	if (m_AttackType == ATTACKTYPE_CROSSING && m_InfoType == INFOTYPE_1)
	{

		m_Color = D3DXCOLOR(0.8f, 1.0f, 0.7f, 1.0f);

		SetColor(m_Color);

		//カウントが一定値で割れた場合
		if (m_nCrossingTimeL % 5 == 0)
		{
			//交差処理
			OnCrossing();
		}

		//体力が0になった場合
		if (m_nLife <= 0)
		{
			//消滅
			m_bUninit = true;
		}

		//画面外処理
		if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP ||
			pos.x - m_scale.x / 2.0f < 0.0f ||
			pos.x + m_scale.x / 2.0f > SCREEN_GAMEWIDTH)
		{
			//消滅
			m_bUninit = true;
		}

		//値を足す
		m_nCrossingTimeL++;
	}

	//右交差弾の場合
	if (m_AttackType == ATTACKTYPE_CROSSING && m_InfoType == INFOTYPE_2)
	{

		m_Color = D3DXCOLOR(0.9f, 1.0f, 0.8f, 1.0f);

		SetColor(m_Color);

		//カウントが一定値で割れた場合
		if (m_nCrossingTimeR % 5 == 0)
		{
			//交差処理
			OnCrossing();	
		}

		//値を足す
		m_nCrossingTimeR++;

		//体力が0になった場合
		if (m_nLife <= 0)
		{
			//消滅
			m_bUninit = true;
		}

		//画面外処理
		if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP ||
			pos.x - m_scale.x / 2.0f < 0.0f ||
			pos.x + m_scale.x / 2.0f > SCREEN_GAMEWIDTH)
		{
			//消滅
			m_bUninit = true;
		}
	}

	//全方位反射弾の場合
	if (m_AttackType == ATTACKTYPE_REFLECTION && m_InfoType == INFOTYPE_1)
	{
		//反射処理
		OnReflection();

		m_Color = D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f);

		SetColor(m_Color);

		//値が一定値以上の場合
		if (m_bReflection == true)
		{
			//位置が一定の範囲以上の場合
			if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP - 30 ||
				pos.x - m_scale.x / 2.0f < -30.0f ||
				pos.x + m_scale.x / 2.0f > SCREEN_GAMEWIDTH + 30)
			{
				//消滅
				m_bUninit = true;

				//カウンタリセット
				m_bReflection = false;
			}
		}

		//値が一定値以上の場合
		if (pos.y + m_scale.y / 2.0f > SCREEN_HEIGHT + 30)
		{
			//消滅
			m_bUninit = true;
		}

	}

	//上下反射弾の場合
	if (m_AttackType == ATTACKTYPE_REFLECTION && m_InfoType == INFOTYPE_2)
	{
		if (pos.x - m_scale.x / 2.0f < -30.0f ||
			pos.x + m_scale.x / 2.0f > SCREEN_GAMEWIDTH + 10)
		{		
			//消滅
			m_bUninit = true;

		}

		//反射処理
		OnReflection();

		//値が一定値以上の場合
		if (m_nReflectionCnt >= 1)
		{
			//位置が一定の範囲以上の場合
			if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP - 40.0f ||
				pos.y + m_scale.y / 2.0f > SCREEN_HEIGHT + 40.0f )
			{
				//消滅
				m_bUninit = true;

				//カウンタリセット
				m_nReflectionCnt = 0;
			}
		}
	}

	//折り返し弾の場合
	if (m_AttackType == ATTACKTYPE_TURN)
	{
		//折り返し処理
		OnTurn();

		//折り返しカウントが一定値以上の場合
		if (m_TurnCnt >= 2)
		{
			//位置が一定の範囲以上の場合
			if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP - 10 ||
				pos.y + m_scale.y / 2.0f > SCREEN_HEIGHT + 10 ||
				pos.x - m_scale.x / 2.0f < -10.0f ||
				pos.x + m_scale.x / 2.0f > SCREEN_GAMEWIDTH)
			{
				//消滅
				m_bUninit = true;

				//カウンタリセット
				m_TurnCnt = 0;
			}
		}
	}

	//n_way弾1の場合
	if (m_AttackType == ATTACKTYPE_N_WAY1)
	{
		OnDiffusion();

		m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

		SetColor(m_Color);

		//画面外処理
		if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP ||
			pos.y + m_scale.y / 2.0f > SCREEN_HEIGHT ||
			pos.x - m_scale.x / 2.0f < 0.0f ||
			pos.x + m_scale.x / 2.0f > SCREEN_GAMEWIDTH)
		{
			//消滅
			m_bUninit = true;
		}
	}

	//n_way弾の場合
	if (m_AttackType == ATTACKTYPE_N_WAY2)
	{
		//nWay弾カウント
		m_nWayCnt++;

		if (m_nWayCnt == 40)
		{
			m_bUninit = true;

			m_posDeath = pos;

			if(m_bUninit == true)
			{
				//一番端の角度を計算
				float fAngle = (D3DX_PI / 8) + (N_WAY_CREATE - 1) / 2 * (D3DX_PI / -7);

				//値がn_way弾生成数を上回るまで、角度を計算して弾を生成
				for (int nCntway = 0; nCntway < N_WAY_CREATE; nCntway++, fAngle += D3DX_PI / 12)
				{
					//n_way弾の生成
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

			//画面外処理
			if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP ||
				pos.y + m_scale.y / 2.0f > SCREEN_HEIGHT ||
				pos.x - m_scale.x / 2.0f < 0.0f ||
				pos.x + m_scale.x / 2.0f > SCREEN_GAMEWIDTH)
			{
				//消滅
				m_bUninit = true;
			}

	}

	//ボムの場合
	if (m_AttackType == ATTACKTYPE_BOMB)
	{
		m_pTexture[1];

		m_nCntSpiral++;

		OnCollision();


		m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);

		SetColor(m_Color);

		//カウントが一定値で割れた場合
		if (m_nCntSpiral % 5 == 0)
		{
			//交差処理
			OnCrossing();
		}

		//体力が0になった場合
		if (m_nLife <= 0)
		{
			//消滅
			m_bUninit = true;
		}
	}

	//タイプ分け
	if (m_InfoType == INFOTYPE_BIGBULLET)
	{

		//通常弾の場合
		if (m_AttackType == ATTACKTYPE_NORMAL)
		{
			m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);

			SetColor(m_Color);
		}

		//渦巻弾の場合
		if (m_AttackType == ATTACKTYPE_SPIRAL)
		{
			m_Color = D3DXCOLOR(0.2f, 0.5f, 1.0f, 0.7f);

			SetColor(m_Color);
		}
	}

	if (m_InfoType == INFOTYPE_RED)
	{

		//通常弾の場合
		if (m_AttackType == ATTACKTYPE_NORMAL)
		{
			m_Color = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f);

			SetColor(m_Color);
		}

		//渦巻弾の場合
		if (m_AttackType == ATTACKTYPE_SPIRAL)
		{
			//m_Color = D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.9f);
			m_Color = D3DXCOLOR(0.2f, 0.8f, 1.0f, 0.9f);

			SetColor(m_Color);
		}
	}

	if (m_InfoType == INFOTYPE_BLUE)
	{

		//通常弾の場合
		if (m_AttackType == ATTACKTYPE_NORMAL)
		{
			m_Color = D3DXCOLOR(0.0f, 0.3f, 1.0f, 1.0f);

			SetColor(m_Color);
		}

		//渦巻弾の場合
		if (m_AttackType == ATTACKTYPE_SPIRAL)
		{
			m_Color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.9f);

			SetColor(m_Color);
		}
	}


	//判定処理
	OnCollision();

	//移動量を追加
	pos += m_move;

	//位置の更新
	SetPosition(pos, m_scale);


	//プレイヤー消滅状態および画面外の処理
	//敵の弾だった場合
	if (GetBulletType() == BULLETTYPE_ENEMY)
	{
		//プレイヤーの状態が消滅状態だった場合
		if (CGame::GetPlayer()->GetPlayerState() == CPlayer::PLAYERSTATE_DEATH)
		{
			//被弾後カウント
			m_nPlayerCnt++;

			//カウントが一定の値を上回った場合
			if (m_nPlayerCnt % 1 == 0)
			{
				//消滅
				m_bUninit = true;
			}
		}
		else
		{
			//画面外処理
			if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP-30 ||
				pos.y + m_scale.y / 2.0f > SCREEN_HEIGHT+30 ||
				pos.x - m_scale.x / 2.0f < -30.0f ||
				pos.x + m_scale.x / 2.0f > SCREEN_GAMEWIDTH + 30)
				{
					//消滅
					m_bUninit = true;
				}
			else
				{
					//消滅
					m_bUninit = false;
				}
		}
	}

	//消滅した場合
	if (m_bUninit == true)
	{
		//終了処理の呼び出し
		Uninit();
	}
}

//*****************************************************************************
// 判定処理
//*****************************************************************************
void CBullet::OnCollision(void)
{
	//位置の取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//サウンドのポインタ
	CSound *pSound = CManager::GetSound();

	//位置の更新
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
				//弾判定呼び出し
				BULLETTYPE BulletType;
				BulletType = GetBulletType();

				//種類判定呼び出し
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				//プレイヤーの弾でかつタイプが敵の場合
				if (BulletType == BULLETTYPE_PLAYER && objType == OBJTYPE_ENEMY)
				{
					//位置の取得
					CEnemy *pEnemy = (CEnemy*)pScene;
					D3DXVECTOR3 Enemypos;
					Enemypos = pEnemy->GetPosition();

					//位置の取得
					D3DXVECTOR3 Enemyscale;
					Enemyscale = pEnemy->GetScale();

					//当たり判定
					if (pos.x + m_scale.x / 2.0f > Enemypos.x - Enemyscale.x / 2.0f&&
						pos.x - m_scale.x / 2.0f < Enemypos.x + Enemyscale.x / 2.0f&&
						pos.y + m_scale.y / 2.0f > Enemypos.y - Enemyscale.y / 2.0f&&
						pos.y - m_scale.y / 2.0f < Enemypos.y + Enemyscale.y / 2.0f)
					{

						//爆発音
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE_HIT);

						//m_nEnemymoveCnt <= 280;

				/*		if (pEnemy->GetBossType() == pEnemy->BOSSTYPE_REFLECTION_ALL)
						{
						}*/
						//else
						{
							//通常弾の場合
							if (m_AttackType == ATTACKTYPE_NORMAL)
							{
								//ダメージ処理
								int nLife = pEnemy->GetLife();
								nLife -= NORMAL_DAMAGE;
								pEnemy->SetLife(nLife);

								//値を代入
								CLifeGauge *pLifeGauge = pEnemy->GetLifeGauge();

								if (pLifeGauge != NULL)
								{
									//ゲージ縮小処理
									pLifeGauge->OnDiffuse(NORMAL_DAMAGE);
								}

							}

							//ホーミングの場合
							if (m_AttackType == ATTACKTYPE_HOMING)
							{
								//ダメージ処理
								int nLife = pEnemy->GetLife();
								nLife -= HOMING_DAMAGE;
								pEnemy->SetLife(nLife);

								//値を代入
								CLifeGauge *pLifeGauge = pEnemy->GetLifeGauge();

								if (pLifeGauge != NULL)
								{
									//ゲージ縮小処理
									pLifeGauge->OnDiffuse(HOMING_DAMAGE);
								}
							}

							//ボムの場合
							if (m_AttackType == ATTACKTYPE_BOMB)
							{
								//ダメージ処理
								int nLife = pEnemy->GetLife();
								nLife -= BOMB_DAMAGE;
								pEnemy->SetLife(nLife);

								//値を代入
								CLifeGauge *pLifeGauge = pEnemy->GetLifeGauge();

								if (pLifeGauge != NULL)
								{
									//ゲージ縮小処理
									pLifeGauge->OnDiffuse(BOMB_DAMAGE);
								}
							}

							//敵の状態
							pEnemy->SetEnemyState(CEnemy::ENEMYSTATE_DAMAGE);

							if (m_AttackType != ATTACKTYPE_BOMB)
							{
								//消滅
								m_bUninit = true;
							}
						}
					}
				}
	

				//敵の弾でかつタイプがプレイヤーの場合
				if (BulletType == BULLETTYPE_ENEMY && objType == OBJTYPE_PLAYER)
				{
					CPlayer *pPlayer = (CPlayer*)pScene;

					//位置の取得
					D3DXVECTOR3 Playerpos;
					Playerpos = pPlayer->GetPosition();

					//位置の取得
					D3DXVECTOR3 Playerscale;
					Playerscale = pPlayer->GetScale();

					/*bool bPlayer = pPlayer->Uninit();*/

					//渦巻弾の場合
					if (m_AttackType == ATTACKTYPE_SPIRAL)
					{
						if (pos.x + m_scale.x / 8.0f > Playerpos.x - Playerscale.x / 12.0f&&
							pos.x - m_scale.x / 8.0f < Playerpos.x + Playerscale.x / 12.0f&&
							pos.y + m_scale.y / 8.0f > Playerpos.y - Playerscale.y / 12.0f&&
							pos.y - m_scale.y / 8.0f < Playerpos.y + Playerscale.y / 12.0f)
						{
							//被弾時の処理
							if (CGame::GetPlayer()->GetPlayerState() == CPlayer::PLAYERSTATE_NORMAL)
							{
								//サウンドのポインタ
								CSound *pSound = CManager::GetSound();

								//爆発音
								pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

								//値を代入
								m_nPlayerCnt = 0;

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
					//当たり判定
					else if (pos.x + m_scale.x / 1.8f > Playerpos.x - Playerscale.x / 12.0f&&
						pos.x - m_scale.x / 1.8f < Playerpos.x + Playerscale.x / 12.0f&&
						pos.y + m_scale.y / 1.8f > Playerpos.y - Playerscale.y / 12.0f&&
						pos.y - m_scale.y / 1.8f < Playerpos.y + Playerscale.y / 12.0f)
					{

						//被弾時の処理
						if (CGame::GetPlayer()->GetPlayerState() == CPlayer::PLAYERSTATE_NORMAL)
						{
							//サウンドのポインタ
							CSound *pSound = CManager::GetSound();

							//爆発音
							pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXPLOSION);

							//値を代入
							m_nPlayerCnt = 0;

							//爆発の生成
							CExplosion::Create(pos, D3DXVECTOR3(50, 50, 0));

							//プレイヤーの状態
							pPlayer->SetPlayerState(CPlayer::PLAYERSTATE_DEATH);

							// ライフ情報を取得
							int nLife = CGame::GetLife()->GetLife();

							// ライフの設定
							CGame::GetLife()->SetLife(nLife - 1);
						}	
						else if(CGame::GetPlayer()->GetPlayerState() == CPlayer::PLAYERSTATE_REVIVAL)
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

	if(m_AttackType== ATTACKTYPE_BOMB)
	{

		//角度計算
		float VectorX = m_EnemyBulletpos.x - m_PlayerBulletpos.x;
		float VectorY = m_EnemyBulletpos.y - m_PlayerBulletpos.y;
		float fLength = sqrtf(VectorX*VectorX + VectorY*VectorY);

		if (m_BulletType == BULLETTYPE_PLAYER)
		{
			//一定値に入った場合
			if (fLength <= 100)
			{
				//弾消しを有効にする
				m_bUninit = true;

			}
		}
	}
}

//*****************************************************************************
// 追尾処理
//*****************************************************************************
void CBullet::OnHoming(void)
{
	//位置の取得
	D3DXVECTOR3 pos; 
	pos = GetPosition();

	float fLengthMin = 10000.0f;
	float fAngle = 0.0f;

	float fLengthHoming = 2000.0f;
	float fAngleHoming = 0.0f;

	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		//Scene呼び出し	
		CScene*pScene;
		pScene = CScene::GetScene(OBJTYPE_ENEMY,nCntScene);

		if (pScene != NULL)
		{
			//プレイヤーの弾だった場合
			if (m_BulletType == BULLETTYPE_PLAYER)
			{
				//位置の取得
				CEnemy *pEnemy = (CEnemy*)pScene;
				D3DXVECTOR3 Enemypos;
				Enemypos = pEnemy->GetPosition();

				//位置の取得
				CPlayer *pPlayer = (CPlayer*)pScene;
				D3DXVECTOR3 Playerpos;
				Playerpos = pPlayer->GetPosition();

				//敵との角度計算
				float VectorX = Enemypos.x - pos.x;
				float VectorY = Enemypos.y - pos.y;
				float fLengthObj = sqrtf(VectorX*VectorX + VectorY*VectorY);

				//プレイヤーとの角度計算
				float VectorHomingX = Playerpos.x - pos.x;
				float VectorHomingY = Playerpos.y - pos.y;
				float fLengthHoming = sqrtf(VectorHomingX*VectorHomingX + VectorHomingY*VectorHomingY);

				//値が指定値より低い場合
				//if (fLengthHoming >= fLengthHoming)
				{
					//値が指定値より低い場合
					if (fLengthObj <= fLengthMin)
					{
						//範囲を同じに
						fLengthMin = fLengthObj;

						fAngle = atan2f(VectorX, VectorY);

						//ホーミング計算
						float moveX = sinf(fAngle)*PLAYER_HOMING_X / 1.2f;
						float moveY = cosf(fAngle)*PLAYER_HOMING_Y / 1.2f;

						//移動値を同じに
						m_move.x = moveX;
						m_move.y = moveY;
					}
				}
			}
		}
	}

	//for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	//{
	//	//Scene呼び出し
	//	CScene*pScene;
	//	pScene = CScene::GetScene(OBJTYPE_PLAYER, m_nKeepObj);

	//	if (pScene != NULL)
	//	{
	//		//プレイヤーの弾だった場合
	//		if (m_BulletType == BULLETTYPE_ENEMY)
	//		{
	//			//位置の取得
	//			CPlayer *pPlayer = (CPlayer*)pScene;
	//			D3DXVECTOR3 Playerpos;
	//			Playerpos = pPlayer->GetPosition();

	//			//角度計算
	//			float VectorX = Playerpos.x - pos.x;
	//			float VectorY = Playerpos.y - pos.y;

	//			//角度計算
	//			float fangle = atan2f(VectorX, VectorY);

	//			if (m_nCnt % 1 == 0)
	//			{
	//				//角度が一定値を超える場合
	//				if ((fangle < -D3DX_PI / 4.0f&&fangle > -D3DX_PI) ||
	//					(fangle > D3DX_PI / 4.0f&&fangle < D3DX_PI))
	//				{
	//					//ホーミング計算
	//					float moveX = sinf(fangle)*PLAYER_HOMING_X;
	//					float moveY = cosf(fangle)*PLAYER_HOMING_Y;

	//					//移動値を換算
	//					m_move.x = moveX;
	//					m_move.y = moveY;
	//				}
	//			}
	//		}
	//	}
	//}
}

//*****************************************************************************
// 交差処理
//*****************************************************************************
void CBullet::OnCrossing(void)
{
	//位置の取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//タイプが左交差弾の場合
	if (m_AttackType == ATTACKTYPE_CROSSING&&m_InfoType == INFOTYPE_1)
	{
		//回転軸の値
		m_fAngleL -= m_fAngleSpeed[0];

		//回転軸の制御	
		if (m_fAngleL >= D3DX_PI)
		{
			m_fAngleL -= ((D3DX_PI / 2) / 90) * 1 + (m_nCrossingTimeL);
		}

		if (m_posOrigin != pos)
		{
			// 生成された位置から現在の位置までの距離を求める
			D3DXVECTOR3 vec = m_posOrigin - pos;
			float fLength = sqrtf(vec.x * vec.x + vec.y * vec.y);
			float Lf = ((float)SCREEN_WIDTH - m_fAngleL) / (float)SCREEN_WIDTH;

			//カウントが一定値を上回った場合
			if (m_nCrossingTimeL >= 50)
			{

				//回転軸計算
				float LX = (m_move.x*cosf(m_fAngleL) + m_move.y*sinf(m_fAngleL)) / Lf;
				float LY = (-m_move.x*sinf(m_fAngleL) + m_move.y*cosf(m_fAngleL)) / Lf;

				//値を代入
				m_move.x = LX/5.0f;
				m_move.y = LY/5.0f;
				
				//カウントの値をマイナス化
				m_nCrossingTimeL -= 700;
			}

		}
	}

	//タイプが右交差弾の場合
	if (m_AttackType == ATTACKTYPE_CROSSING&&m_InfoType == INFOTYPE_2)
	{
		//回転軸の値
		m_fAngleR -= m_fAngleSpeed[1];

		//回転軸の制御	
		if (m_fAngleR >= D3DX_PI)
		{
			m_fAngleR -= ((D3DX_PI / 2) / 90) * 1 + (m_nCrossingTimeR);
		}

		if (m_posOrigin != pos)
		{
			// 生成された位置から現在の位置までの距離を求める
			D3DXVECTOR3 vec = m_posOrigin - pos;
			float fLength = sqrtf(vec.x * vec.x + vec.y * vec.y);
			float Rf = ((float)SCREEN_WIDTH - m_fAngleR) / (float)SCREEN_WIDTH;

			//カウントが一定値を上回った場合
			if (m_nCrossingTimeR >= 50)
			{
				//回転軸計算
				float RX = (m_move.x*cosf(m_fAngleR) + m_move.y*sinf(m_fAngleR)) / Rf;
				float RY = (-m_move.x*sinf(m_fAngleR) + m_move.y*cosf(m_fAngleR)) / Rf;

				//値を代入
				m_move.x = RX / 5.0f;
				m_move.y = RY / 5.0f;
				
				//カウントの値をマイナス化
				m_nCrossingTimeR -= 700;

			}
		}
	}

	//タイプがボムの場合
	if (m_AttackType == ATTACKTYPE_BOMB)
	{

		//回転軸の値
		m_fAngleBomb -= m_fAngleSpeed[0];

		//回転軸の制御	
		if (m_fAngleBomb >= D3DX_PI)
		{
			m_fAngleBomb -= ((D3DX_PI / 2) / 90) * 1 + (m_nCntSpiral);
		}

		if (m_posOrigin != pos)
		{
			// 生成された位置から現在の位置までの距離を求める
			D3DXVECTOR3 vec = m_posOrigin - pos;
			float fLength = sqrtf(vec.x * vec.x + vec.y * vec.y);
			float Lf = ((float)SCREEN_WIDTH - fLength) / (float)SCREEN_WIDTH;

			//カウントが一定値を上回った場合
			if (m_nCntSpiral <= 78)
			{
				//カウントが一定値を上回った場合
				if (m_nCntSpiral % 5 == 0)
				{
					//回転軸計算
					float LX = (m_move.x*cosf(m_fAngleBomb) + m_move.y*sinf(m_fAngleBomb))*1.0f;
					float LY = (-m_move.x*sinf(m_fAngleBomb) + m_move.y*cosf(m_fAngleBomb))*1.0f;

					//値を代入
					m_move.x = LX / 1.0f;
					m_move.y = LY / 1.0f;

					//カウントの値をマイナス化
				}

			}

			if (m_nCntSpiral >= 78)
			{
				m_nCrossingTimeL = 0;
			}


			//CPlayer *pPlayer;

			//pPlayer = CGame::GetPlayer();

			//D3DXVECTOR3 Playerpos = pPlayer->GetPosition();

			////角度計算
			//float VectorX = Playerpos.x - pos.x;
			//float VectorY = Playerpos.y - pos.y;
			//float fAngle = atan2f(VectorX, VectorY);
			//float fLengthObj = sqrtf(VectorX*VectorX + VectorY*VectorY);

			////値を代入
			//float moveX = sinf(fAngle)*1.5f;
			//float moveY = cosf(fAngle)*1.5f;

			////値を移動値に換算
			//m_move.x = moveX;
			//m_move.y = moveY;

			//範囲
			/*float fLength = 5;*/

			//if (m_nCntSpiral % 20 == 0)
			//{	
			//	//渦巻弾の生成
			//	m_move.x += (sinf(D3DX_PI * 2.0f * ((float)m_nCntSpiral / (float)40)) * 2.0f)/10.0f;
			//	m_move.y += (cosf(D3DX_PI * 2.0f * ((float)m_nCntSpiral / (float)40)) * 2.0f) / 10.0f;

			//}
		}

	}
}

//*****************************************************************************
// 反射処理
//*****************************************************************************
void CBullet::OnReflection(void)
{

	//位置の取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//タイプが全方位反射弾の場合
	if (m_AttackType == ATTACKTYPE_REFLECTION && m_InfoType == INFOTYPE_1)
	{
		//位置が一定の範囲以上の場合
		if (pos.x - m_scale.x / 2.0f < 0.0f ||
			pos.x + m_scale.x / 2.0f > SCREEN_GAMEWIDTH)
		{

			//反射判定が行われていない場合
			if (m_bReflection == false)
			{
				//反射
				m_move.x *= -0.8f;

				//反射判定が行われている状態にする
				m_bReflection = true;
			}

		}

		//位置が一定の範囲以上の場合
		if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP)
		{

			//反射判定が行われていない場合
			if (m_bReflection == false)
			{
				//反射
				m_move.y *= -0.8f;

				//反射判定が行われている状態にする
				m_bReflection = true;
			}
		}
	}

	//タイプが上下反射弾の場合
	if (m_AttackType == ATTACKTYPE_REFLECTION&& m_InfoType == INFOTYPE_2)
	{

		//位置が一定の範囲以上の場合
		if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP + 20 ||
			pos.y - m_scale.y / 2.0f > SCREEN_HEIGHT - 20)
		{


			//反射カウントが一定値に達していない場合
			if (m_nReflectionCnt < 1)
			{

				
				//反射
				m_move.y *= -1.0f;

				//カウント
				m_nReflectionCnt++;
			}
		}
	}

	//タイプが反射渦巻弾の場合
	if (m_AttackType == ATTACKTYPE_SPIRAL && m_InfoType == INFOTYPE_1)
	{
		//位置が一定の範囲以上の場合
		if (pos.x - m_scale.x / 2.0f < -20.0f ||	pos.x + m_scale.x / 2.0f > SCREEN_GAMEWIDTH)
		{
			//反射判定が行われていない場合
			if (m_bReflection == false)
			{
				//反射
				m_move.x *= -1.0f;

				//反射判定が行われている状態にする
				m_bReflection = true;
			}

		}

		//位置が一定の範囲以上の場合
		if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP - 20 || pos.y + m_scale.y / 2.0f > SCREEN_HEIGHT + 20)
		{
			//反射判定が行われていない場合
			if (m_bReflection == false)
			{

				//反射
				m_move.x *= -1.0f;

				//反射判定が行われている状態にする
				m_bReflection = true;
			}
		}
	}
}

//*****************************************************************************
// 折り返し処理
//*****************************************************************************
void CBullet::OnTurn(void)
{
	//位置の取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//タイプが切り替えし弾の場合
	if (m_AttackType == ATTACKTYPE_TURN && m_InfoType == INFOTYPE_1)
	{

		//位置が一定の範囲以上の場合
		if (pos.y - m_scale.y / 2.0f < SCREEN_HEIGHT_TOP ||
			pos.y + m_scale.y / 2.0f > SCREEN_HEIGHT ||
			pos.x - m_scale.x / 2.0f < 0.0f ||
			pos.x + m_scale.x / 2.0f > SCREEN_GAMEWIDTH)
		{
			//切り替えしカウントが一定以下の場合
			if (m_TurnCnt <= 2)
			{

				//切りかえし
				m_move *= -1;

				//カウント
				m_TurnCnt++;
			}
		}
	}
}

//*****************************************************************************
// n_way弾処理
//*****************************************************************************
void CBullet::OnDiffusion(void)
{
	//位置の取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//タイプがn_way弾の場合
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
// ボム処理
//*****************************************************************************
void CBullet::OnBomb(void)
{
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CBullet::Draw(void)
{
	//描画の呼び出し
	CScene2D::Draw();
}

//*****************************************************************************
// テクスチャ読み込み処理
//*****************************************************************************
HRESULT CBullet::Load(void)
{
	//デバイスの設定
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet001.png", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &m_pTexture[1]);

	return S_OK;
}

//*****************************************************************************
// テクスチャ破棄処理
//*****************************************************************************
void CBullet::Unload(void)
{
	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
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
// 弾情報処理
//*****************************************************************************
CBullet::BULLETTYPE CBullet::GetBulletType(void)
{
	return m_BulletType;
}

//*****************************************************************************
// 弾の設定処理
//*****************************************************************************
void CBullet::SetBulletType(BULLETTYPE bulletType)
{
	m_BulletType = bulletType;
}

//*****************************************************************************
// 攻撃種類情報処理
//*****************************************************************************
CBullet::ATTACKTYPE CBullet::GetAttackType(void)
{
	return m_AttackType;
}

//*****************************************************************************
// 攻撃種類設定処理
//*****************************************************************************
void CBullet::SetAttackType(ATTACKTYPE AttackType)
{
	m_AttackType = AttackType;
}

//*****************************************************************************
// 攻撃情報処理
//*****************************************************************************
CBullet::INFOTYPE CBullet::GetInfoType(void)
{
	return m_InfoType;
}

//*****************************************************************************
// 攻撃種類設定処理
//*****************************************************************************
void CBullet::SetInfoType(INFOTYPE infoType)
{
	m_InfoType = infoType;
}

//*****************************************************************************
// グレイズの設定処理
//*****************************************************************************
bool CBullet::GetGraze(void)
{
	return m_bGraze;
}

//*****************************************************************************
// グレイズの情報処理
//*****************************************************************************
void CBullet::SetGraze(bool bgraze)
{
	m_bGraze = bgraze;
}

//*****************************************************************************
// 弾消しの設定処理
//*****************************************************************************
bool CBullet::GetUninit(void)
{
	return m_bUninit;
}

//*****************************************************************************
// 弾消し情報処理
//*****************************************************************************
void CBullet::SetUninit(bool bUninit)
{
	m_bUninit = bUninit;
}
//*****************************************************************************
// 体力の設定処理
//*****************************************************************************
int CBullet::GetLife(void)
{
	return m_nLife;
}

//*****************************************************************************
// 体力情報処理
//*****************************************************************************
void CBullet::SetLife(int nLife)
{
	m_nLife = nLife;
}

//*****************************************************************************
// 移動の設定処理
//*****************************************************************************
D3DXVECTOR3 CBullet::GetMove(void)
{
	return m_move;
}

//*****************************************************************************
// 移動情報処理
//*****************************************************************************
void CBullet::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}


//*****************************************************************************
// テクスチャ情報処理
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBullet::GetTexture(int nCntTex)
{
	return m_pTexture[nCntTex];
}
