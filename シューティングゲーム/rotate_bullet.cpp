////=============================================================================
////
//// メイン処理 [rotate_bullet.cpp]
//// Author : Tatsuki Matsuda 
////
////=============================================================================
//#include "rotate_bullet.h"
//#include "explosion.h"
//#include "manager.h"
//#include "renderer.h"
//#include "enemy.h"
//#include "player.h"
//#include "game.h"
//
////*****************************************************************************
//// コンストラクタ
////*****************************************************************************
//CRotate_Bullet::CRotate_Bullet(int nPriority) :CBullet(nPriority)
//{
//	//角度の初期値
//	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//}
//
////*****************************************************************************
//// デストラクタ
////*****************************************************************************
//CRotate_Bullet::~CRotate_Bullet()
//{
//
//}
//
////*****************************************************************************
//// 生成処理
////*****************************************************************************
//CRotate_Bullet *CRotate_Bullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, D3DXVECTOR3 rot, BULLETTYPE bulletType, ATTACKTYPE attackType, INFOTYPE infoType)
//{
//	//動的確保
//	CRotate_Bullet* pRotate_Bullet;
//	pRotate_Bullet = new CRotate_Bullet;
//
//	//初期化処理を呼び出し
//	pRotate_Bullet->Init(pos, scale, move, rot);
//
//	//弾の情報の呼び出し
//	pRotate_Bullet->SetBulletType(bulletType);
//
//	//攻撃種類情報の呼び出し
//	pRotate_Bullet->SetAttackType(attackType);
//
//	//攻撃情報の呼び出し
//	pRotate_Bullet->SetInfoType(infoType);
//
//	//テクスチャの呼び出し
//	//for (int nCntTex = 0; nCntTex < 2; nCntTex++)
//	{
//		pRotate_Bullet->BindTexture(GetTexture(1));
//	}
//
//	return pRotate_Bullet;
//}
//
////*****************************************************************************
////　初期化処理
////*****************************************************************************
//HRESULT CRotate_Bullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, D3DXVECTOR3 rot)
//{
//
//	CBullet::Init(pos, scale, move, rot);
//
//	//位置を設定
//	m_posOrigin = pos;
//
//	m_posDeath = D3DXVECTOR3(0, 0, 0);
//
//	//角度を設定
//	m_rot = rot;
//
//	//回転の値を設定
//	m_fAngle = 0.0f;
//
//	//左回転の値を設定
//	m_fAngleL = 0.0f;
//
//	//右回転の値を設定
//	m_fAngleR = 0.0f;
//
//	//回転速度
//	m_fAngleSpeed[0] = (float)-0.03f;
//	m_fAngleSpeed[1] = (float)0.03f;
//
//	//左回転カウントの設定
//	m_nCrossingTimeL = 0;
//
//	//右回転カウントの設定
//	m_nCrossingTimeR = 0;
//
//	//使われているかどうか
//	m_bUninit = false;
//
//	//種類
//	SetObjType(OBJTYPE_BULLET);
//
//	return S_OK;
//}
//
////*****************************************************************************
//// 終了処理
////*****************************************************************************
//void CRotate_Bullet::Uninit(void)
//{
//	//CScene2Dから呼び出し
//	CBullet::Uninit();
//}
//
////*****************************************************************************
//// 更新処理
////*****************************************************************************
//void CRotate_Bullet::Update(void)
//{
//	//位置の取得
//	D3DXVECTOR3 pos;
//	pos = GetPosition();
//
//	//位置の取得
//	D3DXVECTOR3 scale;
//	scale = GetScale();
//
//	//位置の取得
//	D3DXVECTOR3 m_move;
//	m_move = GetMove();
//
//	//位置の取得
//	int m_nLife;
//	m_nLife = GetLife();
//
//	//攻撃情報の取得
//	ATTACKTYPE m_AttackType;
//	m_AttackType = GetAttackType();
//
//	//攻撃種類の取得
//	INFOTYPE m_InfoType;
//	m_InfoType = GetInfoType();
//
//	//寿命
//	m_nLife--;
//
//	//左交差弾の場合
//	if (m_AttackType == ATTACKTYPE_CROSSING&&m_InfoType == INFOTYPE_1)
//	{
//		//カウントが一定値で割れた場合
//		if (m_nCrossingTimeL % 5 == 0)
//		{
//			//交差処理
//			CBullet::OnCrossing();
//
//			//体力が0になった場合
//			if (m_nLife <= 0)
//			{
//				//消滅
//				m_bUninit = true;
//			}
//
//			//画面外処理
//			if (pos.y - scale.y / 2.0f < SCREEN_HEIGHT_TOP - 30 ||
//				pos.x - scale.x / 2.0f < -25.0f ||
//				pos.x + scale.x / 2.0f > SCREEN_GAMEWIDTH)
//			{
//				//消滅
//				m_bUninit = true;
//			}
//		}
//
//		//値を足す
//		m_nCrossingTimeL++;
//	}
//
//	//右交差弾の場合
//	if (m_AttackType == ATTACKTYPE_CROSSING&&m_InfoType == INFOTYPE_2)
//	{
//		//カウントが一定値で割れた場合
//		if (m_nCrossingTimeR % 5 == 0)
//		{
//			//交差処理
//			OnCrossing();
//
//			//体力が0になった場合
//			if (m_nLife <= 0)
//			{
//				//消滅
//				m_bUninit = true;
//			}
//
//			//画面外処理
//			if (pos.y - scale.y / 2.0f < SCREEN_HEIGHT_TOP - 30 ||
//				pos.x - scale.x / 2.0f < -25.0f ||
//				pos.x + scale.x / 2.0f > SCREEN_GAMEWIDTH)
//			{
//				//消滅
//				m_bUninit = true;
//			}
//		}
//
//		//値を足す
//		m_nCrossingTimeR++;
//	}
//
//	//移動量を追加
//	pos += m_move;
//
//	//位置の更新
//	SetPosition(pos, scale);
//
//	//位置の更新
//	SetScale(scale);
//
//	SetMove(m_move);
//
//	SetLife(m_nLife);
//
//
//	//消滅した場合
//	if (m_bUninit == true)
//	{
//		//終了処理の呼び出し
//		Uninit();
//
//		return;
//	}
//
//	//更新情報の呼び出し
//	CBullet::Update();
//
//}
//
////*****************************************************************************
//// 描画処理
////*****************************************************************************
//void CRotate_Bullet::Draw(void)
//{
//	//描画の呼び出し
//	CBullet::Draw();
//}
