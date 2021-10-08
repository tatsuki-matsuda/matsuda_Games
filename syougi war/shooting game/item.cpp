//=============================================================================
//
// メイン処理 [item.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "item.h"
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
LPDIRECT3DTEXTURE9 CItem::m_pTexture[MAX_TEXTURE] = {};			// テクスチャ
D3DXVECTOR3 CItem::m_Craetepos[10] = {};				// 位置

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CItem::CItem(int nPriority) :CScene2D(nPriority)
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CItem::~CItem()
{

}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, ITEMTYPE itemType)
{
	//動的確保
	CItem* pItem;
	pItem = new CItem;

	//アイテム生成
	pItem->SetItemType(itemType);

	//初期の呼び出し
	pItem->Init(pos, scale, move);

	//テクスチャの呼び出し
	for (int nCntTex = 0; nCntTex < 4; nCntTex++)
	{
		pItem->BindTexture(m_pTexture[nCntTex]);
	}

	//値を返す
	return pItem;

}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move)
{
	//大きさを設定
	m_scale = scale;

	//移動を設定
	m_move = move;

	//種類
	SetObjType(OBJTYPE_ITEM);

	//つかわれてるかどうか
	m_bUninit = false;

	//出現経過時間
	m_nCntTime = 0;

	//アイテム出現カウント
	m_nItemCnt = 0;

	//アイテム移動カウント
	m_nItemmoveCnt = 0;

	//敵が消滅した位置
	m_posDeath = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//アイテム生成用の座標
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

	//初期化の呼び出し
	CScene2D::Init(pos, scale);

	//値を返す
	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CItem::Uninit(void)
{
	//終了の呼び出し
	CScene2D::Uninit();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CItem::Update(void)
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


	for (int nCntPriority = 0; nCntPriority < CScene::OBJTYPE_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			CScene*pScene;
			pScene = CScene::GetScene(nCntPriority, nCntScene);

			if (pScene != NULL)
			{

				//アイテムの種類が残機の場合
				if (m_ItemType == ITEMTYPE_1UP)
				{


				}

				//アイテムの種類がボムの場合
				if (m_ItemType == ITEMTYPE_BOMB)
				{


				}

				//アイテムの種類が残機の場合
				if (m_ItemType == ITEMTYPE_POWERUP)
				{


				}
			}
		}
	}

	

	//移動換算
	pos += m_move;

	//位置の更新
	SetPosition(pos, m_scale);

	//大きさ
	SetScale(m_scale);
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CItem::Draw(void)
{
	//描画の呼び出し
	CScene2D::Draw();
}

////*****************************************************************************
//// 判定処理
////*****************************************************************************
//void CLife::OnCollision(void)
//{
//	//位置の取得
//	D3DXVECTOR3 pos;
//	pos = GetPosition();
//
//	//位置の更新
//	SetPosition(pos, m_scale);
//
//	CScore *pScore;
//	pScore = CGame::GetScore();
//
//	for (int nCntPriority = 0; nCntPriority < CScene::OBJTYPE_MAX; nCntPriority++)
//	{
//		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
//		{
//			CScene*pScene;
//			pScene = CScene::GetScene(nCntPriority, nCntScene);
//
//			if (pScene != NULL)
//			{
//
//
//				//種類判定呼び出し
//				CScene::OBJTYPE objType;
//				objType = pScene->GetObjType();
//
//				CBullet *pBullet = (CBullet*)pBullet;
//
//				//弾判定呼び出し
//				pBullet::BULLETTYPE BulletType;
//				BulletType = GetBulletType();
//
//				//敵の弾でかつタイプがプレイヤーの場合
//				if (BulletType == BULLETTYPE_ENEMY && objType == OBJTYPE_PLAYER)
//				{
//					CPlayer *pPlayer = (CPlayer*)pScene;
//
//					//位置の取得
//					D3DXVECTOR3 Playerpos;
//					Playerpos = pPlayer->GetPosition();
//
//					//位置の取得
//					D3DXVECTOR3 Playerscale;
//					Playerscale = pPlayer->GetScale();
//
//					//当たり判定
//					if (pos.x + m_scale.x / 2.0f > Playerpos.x - Playerscale.x / 12.0f&&
//						pos.x - m_scale.x / 2.0f < Playerpos.x + Playerscale.x / 12.0f&&
//						pos.y + m_scale.y / 2.0f > Playerpos.y - Playerscale.y / 12.0f&&
//						pos.y - m_scale.y / 2.0f < Playerpos.y + Playerscale.y / 12.0f)
//					{
//
//						//消滅
//						m_bUninit = true;
//					}
//				}
//			}
//		}
//	}
//}

//*****************************************************************************
// テクスチャ読み込み処理
//*****************************************************************************
HRESULT CItem::Load(void)
{
	//デバイスの設定
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\zanki.png", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Bomb_Item.png", &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet001.png", &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &m_pTexture[3]);

	return S_OK;
}

//*****************************************************************************
//*****************************************************************************
// テクスチャ破棄処理
void CItem::Unload(void)
{
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
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
// アイテムの位置生成処理
//*****************************************************************************
void CItem::OnDiffuesPos(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// Create内の情報
	// 1 pos, 2 scale. 3 move, 4 rot, 5 bulletType, 6 attackType, 7 infoType

	////回転通常弾生成時の処理
	//if ()
	//{

	//}

	////全方位交差弾生成時の処理
	//if ()
	//{
	//}

	////全方位反射弾生成時の処理
	//if ()
	//{
	//}

	////上下反射弾生成時の処理
	//if ()
	//{
	//	//位置を参照し離れた位置から弾を生成
	//	float fLength = 400.0f + rand() % 30;

	//}
}