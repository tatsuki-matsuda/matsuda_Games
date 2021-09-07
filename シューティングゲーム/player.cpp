//=============================================================================
//
// メイン処理 [player.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "bullet.h"
#include "normal_bullet.h"
#include "scene2D.h"
#include "score.h"
#include "manager.h"
#include "renderer.h"
#include "dinput_keyboard.h"

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
	//キーボード―情報の取得
	CInputKeyBoard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyBoard();

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

	//上キー押した場合
	if (pInputKeyboard->GetPress(DIK_UP) == true)
	{
		pos.y -= 6;

		//右斜め
		if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
		{
			pos.x -= sinf(D3DX_PI / 2) * 2;
			pos.y -= cosf(D3DX_PI / 1) * 1;

		}

		else if (pInputKeyboard->GetPress(DIK_LEFT) == true)
		{//左斜め
			pos.x -= sinf(D3DX_PI / 2) * -2;
			pos.y -= cosf(D3DX_PI / 1) * 1;
		}

		if (pInputKeyboard->GetPress(DIK_LSHIFT) == true)
		{
			pos.y += 3;
		}
	}

	//下キー押した場合
	if (pInputKeyboard->GetPress(DIK_DOWN) == true)
	{
		pos.y += 6;

		//右斜め
		if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
		{
			pos.x -= sinf(D3DX_PI / 2) * 2;
			pos.y += cosf(D3DX_PI / 1) * 1;

		}
		else if (pInputKeyboard->GetPress(DIK_LEFT) == true)
		{//左斜め
			pos.x -= sinf(D3DX_PI / 2) * -2;
			pos.y += cosf(D3DX_PI / 1) * 1;
		}

		if (pInputKeyboard->GetPress(DIK_LSHIFT) == true)
		{
			pos.y -= 3;
		}
	}

	//右キー押した場合
	if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
	{
		pos.x += 6;

		if (pInputKeyboard->GetPress(DIK_LSHIFT) == true)
		{
			pos.x -= 3;
		}
	}

	//左キー押した場合
	if (pInputKeyboard->GetPress(DIK_LEFT) == true)
	{
		pos.x -= 6;

		if (pInputKeyboard->GetPress(DIK_LSHIFT) == true)
		{
			pos.x += 3;
		}
	}

	//弾を発射
	if (pInputKeyboard->GetPress(DIK_Z) == true)
	{
		m_timer++;

		if (pInputKeyboard->GetPress(DIK_LSHIFT) == true)
		{
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
			}
		}
		else if (m_timer % 6 == 0)
		{
			//弾の生成
			CNormal_Bullet::Create(D3DXVECTOR3(pos.x + 20, pos.y - 40, pos.z), D3DXVECTOR3(15, 15, 0), D3DXVECTOR3(0, -10, 0),
				D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_PLAYER, CBullet::ATTACKTYPE_NORMAL, CBullet::INFOTYPE_1);

			//弾の生成
			CBullet::Create(D3DXVECTOR3(pos.x, pos.y-40, pos.z), D3DXVECTOR3(15, 15, 0), D3DXVECTOR3(0, -8, 0),
				D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_PLAYER, CBullet::ATTACKTYPE_HOMING, CBullet::INFOTYPE_1);

			//弾の生成
			CNormal_Bullet::Create(D3DXVECTOR3(pos.x-20, pos.y - 40, pos.z), D3DXVECTOR3(15, 15, 0), D3DXVECTOR3(0, -10, 0),
				D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_PLAYER, CBullet::ATTACKTYPE_NORMAL, CBullet::INFOTYPE_1);


		}
	}

	//ボム
	if (pInputKeyboard->GetTrigger(DIK_X) == true)
	{

		//CBullet::Create(D3DXVECTOR3(pos.x, pos.y - 30, pos.z), D3DXVECTOR3(150, 150, 0), D3DXVECTOR3(0, -5, 0),
			//D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_PLAYER, CBullet::ATTACKTYPE_BOMB);

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
							//弾の情報を取得
							bool bulletUninit;
							bulletUninit = pBullet->GetUninit();

							//弾消し判定
							if (bulletUninit == false)
							{
								//弾の座標を取得
								D3DXVECTOR3 bulletPos;
								bulletPos = pBullet->GetPosition();

								//角度計算
								float VectorX = bulletPos.x - pos.x;
								float VectorY = bulletPos.y - pos.y;
								float fLength = sqrtf(VectorX*VectorX + VectorY*VectorY);

								//一定値に入った場合
								if (fLength <= 280)
								{
									//弾消しを有効にする
									bulletUninit = true;

									//弾消し情報の呼び出し
									pBullet->SetUninit(bulletUninit);
								}

						
							}
						}
					}
				}
			}
		}
	}

	//y軸の画面端に行く場合
	if (pos.y - m_scale.y / 2.0f < PLAYER_MOVE_HEIGHT_TOP)
	{
		pos.y = PLAYER_MOVE_HEIGHT_TOP + m_scale.y / 2.0f;
	}

	if (pos.y + m_scale.y / 2.0f > PLAYER_MOVE_HEIGHT)
	{
		pos.y = PLAYER_MOVE_HEIGHT - m_scale.y / 2.0f;
	}

	//x軸の画面端に行く場合
	if (pos.x - m_scale.x / 2.0f < PLAYER_MOVE_WIDTH_TOP)
	{
		pos.x = PLAYER_MOVE_WIDTH_TOP + m_scale.x / 2.0f;
	}

	if (pos.x + m_scale.x / 2.0f > PLAYER_MOVE_WIDTH)
	{
		pos.x = PLAYER_MOVE_WIDTH - m_scale.x / 2.0f;
	}

	//グレイズ処理
	CollisionGraze();

	//位置の更新
	SetPosition(pos,m_scale);
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