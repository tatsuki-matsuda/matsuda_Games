//--------------------------------------------------------------------------------
//
// ゲーム制作[player.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "scene2D.h"

//--------------------------------------------------------------------------------
//マクロ定義
//--------------------------------------------------------------------------------
#define PLAYER_MOVE_HEIGHT_TOP	(20)								//プレイヤーY軸移動可能限界
#define PLAYER_MOVE_WIDTH_TOP	(20)								//プレイヤーX軸移動可能限界
#define PLAYER_MOVE_HEIGHT	(700)									//プレイヤーY軸移動可能限界
#define PLAYER_MOVE_WIDTH	(850)									//プレイヤーX軸移動可能限界


//================================================================================
//オブジェクトクラス(プレイヤー)
//================================================================================
class CPlayer :public CScene2D
{
public:

	CPlayer(int nPriority=OBJTYPE_PLAYER);							//コンストラクタ
	~CPlayer();														//デストラクタ

	static CPlayer *Create(D3DXVECTOR3 pos,D3DXVECTOR3 scale);		//プレイヤーの生成

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				//初期化処理
	void Uninit(void);												//終了処理
	void Update(void);												//更新処理
	void Draw(void);												//描画処理
	void CollisionGraze(void);										//グレイズ判定処理

	static void Load(void);											//読み込み処理
	static void Unload(void);										//破棄処理

private:

	float m_angle;													// 角度
	int	  m_timer;													// 発射時間
	D3DXVECTOR3 m_scale;											// 大きさ
	D3DXVECTOR3 m_move;												// 移動
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;						// 頂点バッファのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture;							// テクスチャ

};
#endif