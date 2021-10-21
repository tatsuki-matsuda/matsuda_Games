//=============================================================================
//
// メイン処理 [bullet.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "bullet.h"
#include "normal_bullet.h"
#include "explosion.h"
#include "manager.h"
#include "renderer.h"
#include "enemy.h"
#include "dinput_keyboard.h"
#include "player.h"
#include "score.h"
#include "game.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CNormal_Bullet::CNormal_Bullet(int nPriority) :CBullet(nPriority)
{
	//角度の初期値
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CNormal_Bullet::~CNormal_Bullet()
{

}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CNormal_Bullet *CNormal_Bullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, D3DXVECTOR3 rot, BULLETTYPE bulletType, ATTACKTYPE attackType, INFOTYPE infoType)
{
	//動的確保
	CNormal_Bullet* pNormal_Bullet;
	pNormal_Bullet = new CNormal_Bullet;

	//初期化処理を呼び出し
	pNormal_Bullet->Init(pos, scale, move, rot);

	//弾の情報の呼び出し
	pNormal_Bullet->SetBulletType(bulletType);

	//攻撃種類情報の呼び出し
	pNormal_Bullet->SetAttackType(attackType);

	//攻撃情報の呼び出し
	pNormal_Bullet->SetInfoType(infoType);

	//テクスチャの呼び出し
	//for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		pNormal_Bullet->BindTexture(GetTexture(1));
	}

	return pNormal_Bullet;
}

//*****************************************************************************
//　初期化処理
//*****************************************************************************
HRESULT CNormal_Bullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, D3DXVECTOR3 rot)
{

	CBullet::Init(pos, scale, move, rot);

	//位置を設定
	m_posOrigin = pos;

	m_posDeath = D3DXVECTOR3(0, 0, 0);

	//角度を設定
	m_rot = rot;

	//使われているかどうか
	m_bUninit = false;

	m_nCnt = 0;

	m_nMoveCnt = 0;

	//種類
	SetObjType(OBJTYPE_BULLET);

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CNormal_Bullet::Uninit(void)
{
	//CScene2Dから呼び出し
	CBullet::Uninit();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CNormal_Bullet::Update(void)
{
	//位置の取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//位置の取得
	D3DXVECTOR3 scale;
	scale = GetScale();

	//位置の取得
	D3DXVECTOR3 m_move;
	m_move = GetMove();

	//位置の取得
	int m_nLife;
	m_nLife = GetLife();

	//攻撃種類の取得
	INFOTYPE m_InfoType;
	m_InfoType = GetInfoType();

	//CEnemy::ENEMYTYPE m_EnemyType = CEnemy::GetEnemyType();

	//寿命
	m_nLife--;

	//通常弾の場合
	if (m_InfoType == INFOTYPE_1)
	{
		////通常敵1だった場合
		//if (CEnemy::BOSSTYPE() == CEnemy::ENEMYTYPE_NORMAL1)
		//{
		//	m_nCnt++;

		//	if (m_nCnt >= 10 && m_nMoveCnt <= 10)
		//	{
		//		m_move.x = 0.0f;
		//		m_move.y = 0.0f;

		//		m_nMoveCnt++;
		//	}

		//	if (m_nMoveCnt >= 10)
		//	{
		//		m_move.x = 1.0f;
		//		m_move.y = 1.0f;
		//	}
		//}

		//画面外処理
		if (pos.y - scale.y / 2.0f < SCREEN_HEIGHT_TOP-20 ||
			pos.y + scale.y / 2.0f > SCREEN_HEIGHT+20 ||
			pos.x - scale.x / 2.0f < -20.0f ||
			pos.x + scale.x / 2.0f > SCREEN_GAMEWIDTH + 20)
		{
			//消滅
			m_bUninit = true;
		}

		//体力が0になった場合
		else if (m_nLife <= 0)
		{
			//消滅
			m_bUninit = true;
		}

	}

	//通常弾2の場合
	if (m_InfoType == INFOTYPE_2)
	{
		//画面外処理
		if (pos.y - scale.y / 2.0f < SCREEN_HEIGHT_TOP - 30 ||
			pos.x - scale.x / 2.0f < -25.0f ||
			pos.x + scale.x / 2.0f > SCREEN_GAMEWIDTH)
		{
			//消滅
			m_bUninit = true;
		}
		//体力が0になった場合
		else if (m_nLife <= 0)
		{
			//消滅
			m_bUninit = true;
		}
	}

	//通常弾3の場合
	if (m_InfoType == INFOTYPE_3)
	{
		m_nCnt++;

		if (m_nCnt % 8 == 0)
		{
			m_move.x *= 1.1f;
			m_move.y *= 1.03f;
		}

		if (m_nCnt % 15 == 0)
		{
			scale.x = 20;
			scale.y = 20;

		}

		//画面外処理
		if (pos.y - scale.y / 2.0f < SCREEN_HEIGHT_TOP ||
			pos.y + scale.y / 2.0f > SCREEN_HEIGHT ||
			pos.x - scale.x / 2.0f < -30.0f ||
			pos.x + scale.x / 2.0f > SCREEN_GAMEWIDTH + 100)
		{
			//消滅
			m_bUninit = true;
		}
		//体力が0になった場合
		else if (m_nLife <= 0)
		{
			//消滅
			m_bUninit = true;
		}

	}

	//移動量を追加
	pos += m_move;

	//位置の更新
	SetPosition(pos, scale);

	//位置の更新
	SetScale(scale);

	SetMove(m_move);

	SetLife(m_nLife);


	//消滅した場合
	if (m_bUninit == true)
	{
		//終了処理の呼び出し
		Uninit();

		return;
	}

	//更新情報の呼び出し
	CBullet::Update();

}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CNormal_Bullet::Draw(void)
{
	//描画の呼び出し
	CBullet::Draw();
}
