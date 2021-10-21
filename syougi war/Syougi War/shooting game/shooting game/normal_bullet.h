//--------------------------------------------------------------------------------
//
// ゲーム制作[normal_bullet.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _NORMAL_BULLET_H_
#define _NORMAL_BULLET_H_

#include "bullet.h"

//--------------------------------------------------------------------------------
//マクロ定義
//--------------------------------------------------------------------------------
#define	CREATE_BULLET		(3)								//弾の生成量

//--------------------------------------------------------------------------------
//前方宣言
//--------------------------------------------------------------------------------
class CEnemy;

//================================================================================
//オブジェクトクラス(通常弾)
//================================================================================
class CNormal_Bullet :public CBullet
{
public:

	CNormal_Bullet(int nPriority = OBJTYPE_BULLET);												//コンストラクタ
	~CNormal_Bullet();																			//デストラクタ


	static CNormal_Bullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,
		D3DXVECTOR3 move, D3DXVECTOR3 rot, BULLETTYPE bulletType,
		ATTACKTYPE attackType, INFOTYPE infoType);												//弾の生成

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, D3DXVECTOR3 rot);		//初期化処理
	void Uninit(void);																			//終了処理
	void Update(void);																			//更新処理
	void Draw(void);																			//描画処理

private:

	bool m_bUninit;																				//  終了判定

	int m_nCnt;																					//	カウント
	int m_nMoveCnt;																				//	移動カウント

	D3DXVECTOR3 m_posOrigin;																	//　弾が生成された位置
	D3DXVECTOR3 m_posDeath;																		//	消滅時の座標
	D3DXVECTOR3 m_rot;																			//	角度

	CScene2D*m_apScene2D[MAX_SCENE2D];															//	CScene2Dのポインタ
};
#endif
