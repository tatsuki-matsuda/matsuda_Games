//-------------------------------------------------------------------------------
//
// ゲーム制作[bullet.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include "xinput_gamepad.h"
#include "model.h"
#include "fade.h"

//-------------------------------------------------------------------------------
//グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			//テクスチャ情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//頂点バッファへのポインタ
D3DXVECTOR3 g_posBullet;							//位置
D3DXMATRIX  g_mtxWorldBullet;						//ワールドマトリックス
BULLET g_aBullet[MAX_BULLET];						//弾の情報

//-------------------------------------------------------------------------------
//初期化処理
//-------------------------------------------------------------------------------
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	BULLET*pBullet = GetBullet();				//弾の情報

	//変数宣言
	VERTEX_3D *pVtx;

	//弾の初期化
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//弾の位置
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//弾の移動
		g_aBullet[nCntBullet].nLife = 0;								//弾の体力
		g_aBullet[nCntBullet].nType = 0;								//弾の種類
		//g_aBullet[nCntBullet].nCnt = 0;
		g_aBullet[nCntBullet].bUse = false;								//弾を使用していない場合
	}

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_pTextureBullet);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点情報の設定
		pVtx[0].pos = D3DXVECTOR3(pBullet->pos.x - 10.0f,pBullet->pos.y + 10.0f, pBullet->pos.z );
		pVtx[1].pos = D3DXVECTOR3(pBullet->pos.x + 10.0f,pBullet->pos.y + 10.0f, pBullet->pos.z );
		pVtx[2].pos = D3DXVECTOR3(pBullet->pos.x - 10.0f,pBullet->pos.y - 10.0f, pBullet->pos.z );
		pVtx[3].pos = D3DXVECTOR3(pBullet->pos.x + 10.0f,pBullet->pos.y - 10.0f, pBullet->pos.z );

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 4;
	}

	g_pVtxBuffBullet->Unlock();
	return S_OK;
}

//-------------------------------------------------------------------------------
//終了処理
//-------------------------------------------------------------------------------
void UninitBullet(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

	//テクスチャの開放
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
}
//-------------------------------------------------------------------------------
//更新処理
//-------------------------------------------------------------------------------
void UpdateBullet(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();				//デバイスの取得
	BULLET*pBullet = &g_aBullet[0];							//弾の情報
	Player*pPlayer = GetPlayer();							//プレイヤーの情報
	Enemy*pEnemy = GetEnemy();								//敵の情報
	XinputGamepad*pXinputGamepad = GetXinputGamepad();		//ゲームパッドの情報
	MODEL*pModel = GetModel();								//モデルの情報
	VERTEX_3D *pVtx;
	
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);	

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{

			if (pBullet->bUse == true)//弾が使われているかどうか
			{	
				//弾の移動処理
				pBullet->pos.x += pBullet->move.x;
				pBullet->pos.z += pBullet->move.z;
				pBullet->pos.y += pBullet->move.y;

				//弾の体力減少処理
				pBullet->nLife--;

				//自機の弾の場合
				if (pBullet->State == BULLETSTATE_PLAYER)
				{
					for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
					{
						//敵がいる場合
						pBullet->fRadius = 10.0f;
						pEnemy->fRadius = 10.0f;

						D3DXVECTOR3 VecRadius = pEnemy->aModel[nCntEnemy].pos - pBullet->pos;		//弾と敵の座標距離

						float fLength = sqrtf(VecRadius.x * VecRadius.x + VecRadius.z * VecRadius.z);	//自機との距離		

						//自機弾と敵の当たり判定
						if (fLength < pBullet->fRadius + pEnemy->fRadius)
						{
							//接触処理
							pBullet->bUse = false;

							pEnemy->aModel[nCntEnemy].nEnemyLife--;
						}
						
					}
		
				}


				//敵の弾だった場合
				if (pBullet->State == BULLETSTATE_ENEMY)
				{
					pBullet->fRadius = 10.0f;
					pPlayer->fRadius = 10.0f;

					D3DXVECTOR3 VecRadius = pBullet->pos - pPlayer->pos;		    //弾と敵の座標距離

					float fLength = sqrtf(VecRadius.x * VecRadius.x + VecRadius.z * VecRadius.z);	//自機との距離		

					//自機弾と敵の当たり判定
					if (fLength < pBullet->fRadius + pPlayer->fRadius)
					{
						//接触処理
						pBullet->bUse = false;

						pPlayer->bUse = false;

						pXinputGamepad->bAButton = false;

						//AButtonを押した場合
						SetFade(FADE_OUT, MODE_GAMEOVER);
						



					}

				}
		
			//弾のライフが0以下になった場合
			if (pBullet->nLife <= 0)
			{
				pBullet->bUse = false;
			}
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//-------------------------------------------------------------------------------
//描画処理
//-------------------------------------------------------------------------------
void DrawBullet(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイス情報
	D3DXMATRIX mtxView;							//計算用マトリックス
	D3DXMATRIX mtxTrans;						//計算用マトリックス

	//デバイスの取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//アルファテストの有無
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//アルファ値の参照
	pDevice->SetRenderState(D3DRS_ALPHAREF,100 );
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_mtxWorldBullet);

		//ポリゴンをカメラに対して正面に向ける
		D3DXMatrixInverse(&g_mtxWorldBullet, NULL, &mtxView);	//逆行列を求める

		g_mtxWorldBullet._41 = 0.0f;
		g_mtxWorldBullet._42 = 0.0f;
		g_mtxWorldBullet._43 = 0.0f;

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
		D3DXMatrixMultiply(&g_mtxWorldBullet, &g_mtxWorldBullet, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBullet);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBullet);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}

	//アルファテストの有無
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);

	//アルファ値の参照
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}

//-------------------------------------------------------------------------------
//弾の設定
//-------------------------------------------------------------------------------
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETSTATE state, int nLife, D3DXCOLOR col)
{
	//変数宣言
	BULLET*pBullet = &g_aBullet[0];

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet, pBullet++)
	{
		//弾を使用している場合
		if (pBullet->bUse == false)
		{

			//位置を設定
   			pBullet->pos = pos;

			//移動量を設定
			pBullet->move = move;

			//弾の情報
			pBullet->State = state;

			////弾の種類
			//pBullet->nType = nType;

			//寿命を設定
			pBullet->nLife = nLife;

			//弾を使用していない場合
			pBullet->bUse = true;

			break;
		}
	}
}

//-------------------------------------------------------------------------------
//頂点座標の設定
//-------------------------------------------------------------------------------
void SetVertexBullet(int nIdx)
{
	////変数宣言
	//VERTEX_3D*pVtx;
	//BULLET*pBullet;

	//pBullet = GetBullet();
	//pBullet += nIdx;
	//int nDamage = 0;

	////頂点バッファをロックし、頂点情報へのポインタを取得
	//g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	//pVtx += nIdx * 4;

	//if (pBullet->nType == 1)
	//{//低速時の弾
	//	nDamage = 5;

	//	//頂点座標の設定
	//	pVtx[0].pos = D3DXVECTOR3(-30 + g_aBullet[nIdx].pos.x, 30 + g_aBullet[nIdx].pos.y, 0.0);
	//	pVtx[1].pos = D3DXVECTOR3(-30 + g_aBullet[nIdx].pos.x, -30 + g_aBullet[nIdx].pos.y, 0.0);
	//	pVtx[2].pos = D3DXVECTOR3(30 + g_aBullet[nIdx].pos.x, 30 + g_aBullet[nIdx].pos.y, 0.0);
	//	pVtx[3].pos = D3DXVECTOR3(30 + g_aBullet[nIdx].pos.x, -30 + g_aBullet[nIdx].pos.y, 0.0);
	//}
	//else if (pBullet->nType == 0)
	//{//通常時の弾
	//	nDamage = 1;

	//	//頂点座標の設定
	//	pVtx[0].pos = D3DXVECTOR3(-10 + g_aBullet[nIdx].pos.x, 10 + g_aBullet[nIdx].pos.y, 0.0);
	//	pVtx[1].pos = D3DXVECTOR3(-10 + g_aBullet[nIdx].pos.x, -10 + g_aBullet[nIdx].pos.y, 0.0);
	//	pVtx[2].pos = D3DXVECTOR3(10 + g_aBullet[nIdx].pos.x, 10 + g_aBullet[nIdx].pos.y, 0.0);
	//	pVtx[3].pos = D3DXVECTOR3(10 + g_aBullet[nIdx].pos.x, -10 + g_aBullet[nIdx].pos.y, 0.0);
	//}

	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//-------------------------------------------------------------------------------
//弾の情報
//-------------------------------------------------------------------------------
BULLET*GetBullet(void)
{
	//弾の情報
	return &g_aBullet[0];
}