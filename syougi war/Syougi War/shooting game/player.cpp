//=============================================================================
//
// メイン処理 [player.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "sound.h"
#include "bullet.h"
#include "normal_bullet.h"
#include "scene2D.h"
#include "score.h"
#include "manager.h"
#include "renderer.h"
#include "dinput_keyboard.h"
#include "life.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;			// テクスチャ

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CPlayer::CPlayer(int nPriority):CScene2D(nPriority)
{
	m_timer = 0;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CPlayer::~CPlayer()
{

}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//動的確保
	CPlayer* pPlayer;
	pPlayer = new CPlayer;

	//初期の呼び出し
	pPlayer->Init(pos, scale);

	//テクスチャ生成
	pPlayer->BindTexture(m_pTexture);

	//値を返す
	return pPlayer;
}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//大きさを設定
	m_scale = scale;

	//種類
	SetObjType(OBJTYPE_PLAYER);

	//初期化の呼び出し
	CScene2D::Init(pos,scale);

	//状態変化カウント
	m_nCntNormal = 0;

	//プレイヤーの色
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//消滅切り替わり間隔
	m_nDeathColor = 0;

	//状態変化中の移動カウント
	m_nCntStateMove = 0;

	//出現カウント
	m_nCntStart = 0;

	//被弾したかどうか
	m_bState = false;
	
	//プレイヤーの状態
	SetPlayerState(PLAYERSTATE_REVIVAL);

	//値を返す
	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CPlayer::Uninit(void)
{
	//終了の呼び出し
	CScene2D::Uninit();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CPlayer::Update(void)
{
	//キーボード情報の取得
	CInputKeyBoard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyBoard();

	//サウンドのポインタ
	CSound *pSound = CManager::GetSound();

	//位置の取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	CScore *pScore;
	pScore = CGame::GetScore();

	//移動量を追加
	pos += m_move;

	//対角線の長さ
	m_angle = sqrtf(30 * 30 + 30 * 30);

	//対角線の角度
	float fAngle = atan2f(5, 5);

	//状態
	PlayerState();

	//プレイヤーの状態が通常状態の場合
	if (m_PlayerState == PLAYERSTATE_NORMAL)
	{
		m_nCntStateMove = 1;

	}

	//プレイヤーの状態が通常状態の場合
	if (m_PlayerState != PLAYERSTATE_DEATH&&m_nCntStateMove >= 1)
	{
		//上キー押した場合
		if (pInputKeyboard->GetPress(DIK_UP) == true)
		{
			//上移動
			pos.y -= 8;
	
			if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
			{//右斜め
				pos.x -= sinf(D3DX_PI / 2) * 2;
				pos.y -= cosf(D3DX_PI / 1) * 1;

			}
			else if (pInputKeyboard->GetPress(DIK_LEFT) == true)
			{//左斜め
				pos.x -= sinf(D3DX_PI / 2) * -2;
				pos.y -= cosf(D3DX_PI / 1) * 1;
			}

			//低速移動
			if (pInputKeyboard->GetPress(DIK_LSHIFT) == true)
			{
				//減速処理
				pos.y += 5;
			}
		}

		//下キー押した場合
		if (pInputKeyboard->GetPress(DIK_DOWN) == true)
		{
			//下移動
			pos.y += 8;

			
			if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
			{//右斜め
				pos.x -= sinf(D3DX_PI / 2) * 2;
				pos.y += cosf(D3DX_PI / 1) * 1;

			}
			else if (pInputKeyboard->GetPress(DIK_LEFT) == true)
			{//左斜め
				pos.x -= sinf(D3DX_PI / 2) * -2;
				pos.y += cosf(D3DX_PI / 1) * 1;
			}

			//低速移動
			if (pInputKeyboard->GetPress(DIK_LSHIFT) == true)
			{
				//減速処理
				pos.y -= 5;
			}
		}

		//右キー押した場合
		if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
		{
			//右移動
			pos.x += 8;

			//低速移動
			if (pInputKeyboard->GetPress(DIK_LSHIFT) == true)
			{
				//減速処理
				pos.x -= 5;
			}
		}

		//左キー押した場合
		if (pInputKeyboard->GetPress(DIK_LEFT) == true)
		{
			//左移動
			pos.x -= 8;

			//低速移動
			if (pInputKeyboard->GetPress(DIK_LSHIFT) == true)
			{
				//減速処理
				pos.x += 5;
			}
		}

		//弾を発射
		if (pInputKeyboard->GetPress(DIK_Z) == true)
		{
			m_timer++;

			if (pInputKeyboard->GetPress(DIK_LSHIFT) == true)
			{//低速移動中の発射
				if (m_timer % 6 == 0)
				{
					//弾の生成
					CBullet::Create(D3DXVECTOR3(pos.x + 20, pos.y - 30, pos.z), D3DXVECTOR3(15, 15, 0), D3DXVECTOR3(0, -8, 0),
						D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_PLAYER, CBullet::ATTACKTYPE_HOMING, CBullet::INFOTYPE_1);

					//弾の生成
					CBullet::Create(D3DXVECTOR3(pos.x - 20, pos.y - 30, pos.z), D3DXVECTOR3(15, 15, 0), D3DXVECTOR3(0, -8, 0),
						D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_PLAYER, CBullet::ATTACKTYPE_HOMING, CBullet::INFOTYPE_1);

					//弾の生成
					CBullet::Create(D3DXVECTOR3(pos.x, pos.y - 40, pos.z), D3DXVECTOR3(15, 15, 0), D3DXVECTOR3(0, -8, 0),
						D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_PLAYER, CBullet::ATTACKTYPE_HOMING, CBullet::INFOTYPE_1);

					//音の生成
					pSound->PlaySoundA(CSound::SOUND_LABEL_SE_SHOT);

				
				}
			}
			else if (m_timer % 6 == 0)
			{//通常移動中の発射

				//弾の生成
				CNormal_Bullet::Create(D3DXVECTOR3(pos.x + 20, pos.y - 40, pos.z), D3DXVECTOR3(15, 15, 0), D3DXVECTOR3(0, -10, 0),
					D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_PLAYER, CBullet::ATTACKTYPE_NORMAL, CBullet::INFOTYPE_1);

				//弾の生成
				CBullet::Create(D3DXVECTOR3(pos.x, pos.y - 40, pos.z), D3DXVECTOR3(15, 15, 0), D3DXVECTOR3(0, -8, 0),
					D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_PLAYER, CBullet::ATTACKTYPE_HOMING, CBullet::INFOTYPE_1);

				//弾の生成
				CNormal_Bullet::Create(D3DXVECTOR3(pos.x - 20, pos.y - 40, pos.z), D3DXVECTOR3(15, 15, 0), D3DXVECTOR3(0, -10, 0),
					D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_PLAYER, CBullet::ATTACKTYPE_NORMAL, CBullet::INFOTYPE_1);

				//音の生成
				pSound->PlaySoundA(CSound::SOUND_LABEL_SE_SHOT);

			}
		}

		m_nCntBomb++;

		if (m_nCntBomb >= 220)
		{
			//ボム
			if (pInputKeyboard->GetTrigger(DIK_X) == true)
			{

				m_nCntBomb = 0;

				m_nCntUse -= 1;

				m_timer++;

				if (m_nCntUse >= 0)
				{
					for (int nCnt = 0; nCnt < 8; nCnt++)
					{
						//ボムの生成
						CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(100, 100, 0),
							D3DXVECTOR3(sinf(D3DX_PI * 5.0f * ((float)nCnt / (float)20)) * 6, cosf(D3DX_PI * 5.0f * ((float)nCnt / (float)20)) * 6, 0),
							D3DXVECTOR3(0, (float)nCnt, 0), CBullet::BULLETTYPE_PLAYER, CBullet::ATTACKTYPE_BOMB, CBullet::INFOTYPE_1);
					}

					//for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
					//{
					//	//Scene呼び出し
					//	CScene*pScene;
					//	pScene = CScene::GetScene(OBJTYPE_BULLET, nCntScene);

					//	if (pScene != NULL)
					//	{
					//		//種類判定呼び出し
					//		CScene::OBJTYPE objType;
					//		objType = pScene->GetObjType();

					//		if (objType != NULL)
					//		{
					//			//オブジェクトの情報が弾だった場合
					//			if (objType == OBJTYPE_BULLET)
					//			{
					//				//sceneを弾の情報へと再定義
					//				CBullet*pBullet;
					//				pBullet = (CBullet*)pScene;

					//				//弾の種類情報を取得
					//				CBullet::BULLETTYPE bulletType;
					//				bulletType = pBullet->GetBulletType();


					//				//敵の弾だった場合
					//				if (bulletType == CBullet::BULLETTYPE_ENEMY)
					//				{
					//					//弾の情報を取得
					//					bool bulletUninit;
					//					bulletUninit = pBullet->GetUninit();

					//					//弾消し判定
					//					if (bulletUninit == false)
					//					{
					//						//弾の座標を取得
					//						D3DXVECTOR3 bulletPos;
					//						bulletPos = pBullet->GetPosition();

					//						//角度計算
					//						float VectorX = bulletPos.x - pos.x;
					//						float VectorY = bulletPos.y - pos.y;
					//						float fLength = sqrtf(VectorX*VectorX + VectorY*VectorY);

					//						//一定値に入った場合
					//						if (fLength <= 280)
					//						{
					//							//弾消しを有効にする
					//							bulletUninit = true;

					//							//弾消し情報の呼び出し
					//							pBullet->SetUninit(bulletUninit);
					//						}


					//					}
					//				}
					//			}
					//		}
					//	}
					//}
				}
			}
		}

		//y軸の画面端上に行く場合
		if (pos.y - m_scale.y / 2.0f < PLAYER_MOVE_HEIGHT_TOP)
		{
			pos.y = PLAYER_MOVE_HEIGHT_TOP + m_scale.y / 2.0f;
		}

		//y軸の画面端下に行く場合
		if (pos.y + m_scale.y / 2.0f > PLAYER_MOVE_HEIGHT)
		{
			pos.y = PLAYER_MOVE_HEIGHT - m_scale.y / 2.0f;
		}

		//x軸の画面端右に行く場合
		if (pos.x - m_scale.x / 2.0f < PLAYER_MOVE_WIDTH_TOP)
		{
			pos.x = PLAYER_MOVE_WIDTH_TOP + m_scale.x / 2.0f;
		}

		//x軸の画面端左に行く場合
		if (pos.x + m_scale.x / 2.0f > PLAYER_MOVE_WIDTH)
		{
			pos.x = PLAYER_MOVE_WIDTH - m_scale.x / 2.0f;
		}

		//グレイズ処理
		CollisionGraze();
	}

	//復活状態
	if (m_PlayerState == PLAYERSTATE_DEATH&&m_nCntStateMove > 60)
	{
		//位置の指定
		pos = D3DXVECTOR3(420.0f, 620.0f, 0.0f);

		//プレイヤーの状態を復活状態へ
		m_PlayerState = PLAYERSTATE_REVIVAL;
	}

	//復活状態
	if (m_PlayerState == PLAYERSTATE_REVIVAL&&m_nCntStateMove == 0)
	{
		//移動値を与える
		pos.y += -0.8f;
	}
	
	//位置の更新
	SetPosition(pos, m_scale);

}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CPlayer::Draw(void)
{
	//描画の呼び出し
	CScene2D::Draw();
}

//*****************************************************************************
// グレイズ判定処理
//*****************************************************************************
void CPlayer::CollisionGraze(void)
{
	//位置の取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		//Scene呼び出し
		CScene*pScene;
		pScene = CScene::GetScene(OBJTYPE_BULLET,nCntScene);

		if (pScene != NULL)
		{
			//種類判定呼び出し
			CScene::OBJTYPE objType;
			objType = pScene->GetObjType();

			if (objType != NULL)
			{
				//オブジェクトの情報が弾だった場合
				if (objType == OBJTYPE_BULLET)
				{
					//sceneを弾の情報へと再定義
					CBullet*pBullet;
					pBullet = (CBullet*)pScene;

					//弾の種類情報を取得
					CBullet::BULLETTYPE bulletType;
					bulletType = pBullet->GetBulletType();

					//敵の弾だった場合
					if (bulletType == CBullet::BULLETTYPE_ENEMY)
					{
						//弾の座標を取得
						D3DXVECTOR3 bulletPos;
						bulletPos = pBullet->GetPosition();

						//グレイズ判定情報の取得
						bool bGraze;
						bGraze = pBullet->GetGraze();

						//グレイズ情報呼び出し
						CScore *pScore;
						pScore = CGame::GetGraze();

						//角度計算
						float VectorX = bulletPos.x - pos.x;
						float VectorY = bulletPos.y - pos.y;
						float fLength = sqrtf(VectorX*VectorX + VectorY*VectorY);


						//一定値に入った場合
						if (fLength <= 40)
						{	
							//グレイズの判定が行われていない場合
							if (bGraze == false)
							{
								//グレイズ加算
								pScore->AddGraze(1);

								//グレイズの判定を行う
								bGraze = true;

								//サウンドのポインタ
								CSound *pSound = CManager::GetSound();

								//爆発音
								pSound->PlaySoundA(CSound::SOUND_LABEL_SE_GRAZE);

								//グレイズ判定
								pBullet->SetGraze(bGraze);
							}
						}
					}
				}
			}
		}
	}
}

//*****************************************************************************
// テクスチャ読み込み処理
//*****************************************************************************
void CPlayer::Load(void)
{
	//デバイスの設定
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\player001.png", &m_pTexture);
}

//*****************************************************************************
// テクスチャ破棄処理
//*****************************************************************************
void CPlayer::Unload(void)
{
	//テクスチャの開放
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//*****************************************************************************
// プレイヤーの状態
//*****************************************************************************
void CPlayer::PlayerState(void)
{
	//サウンドのポインタ
	CSound *pSound = CManager::GetSound();

	//位置の取得
	D3DXVECTOR3 pos;
	pos = GetPosition();
	int nLife = CGame::GetLife()->GetLife();

	switch (GetPlayerState())
	{
		//通常状態だった場合
	case PLAYERSTATE_NORMAL:

		//色
		m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		break;

		//死亡状態だった場合
	case PLAYERSTATE_DEATH:

		//色の切り替わり間隔
		m_nCntColor++;

		//状態変化中の移動カウント
		m_nCntStateMove++;

		//消滅変化カウントが一定値を超えるまで値をカウント
		if (m_nDeathColor < 100)
		{
			//消滅変化カウント
			m_nDeathColor++;
		}

		//徐々に色を変化
		m_Color = D3DXCOLOR(1.0f, 0.5f, 0.5f, (1.0f / ((float)m_nDeathColor*0.25f)));

		//カウントが一定値を上回り、trasition_Result状態になっていない場合
		if (m_nCntColor % 100 == 0 && CGame::GetTransision() != CGame::TRANSITION_RESULT)
		{

			//色の切り替わり間隔
			m_nCntColor = 0;
		}

		break;

		//復活状態だった場合
	case PLAYERSTATE_REVIVAL:

		//色の切り替わり間隔
		m_nCntColor++;

		m_nCntUse = 3;

		//消滅切り替わり間隔
		m_nDeathColor = 0;

		//カウントが一定値で0になる度に色を変化
		if (m_nCntColor % 7 == 0)
		{
			//色
			m_Color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.2f);
		}
		else
		{
			//色
			m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		//カウントが一定値で0になるとプレイヤーの状態、カウントの値を変える
		if (m_nCntColor % 150 == 0)
		{

			//状態
			m_PlayerState = PLAYERSTATE_NORMAL;

			//状態変化中の移動カウント
			m_nCntStateMove = 0;

			//色の切り替えカウント
			m_nCntColor = 0;

		}

	break;

	default:
		break;
	}

	//色情報の呼び出し
	SetColor(m_Color);
}
