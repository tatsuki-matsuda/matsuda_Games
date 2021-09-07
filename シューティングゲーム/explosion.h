//--------------------------------------------------------------------------------
//
// ゲーム制作[explosion.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "scene2D.h"

//--------------------------------------------------------------------------------
//マクロ定義
//--------------------------------------------------------------------------------
#define EXPLOSION_SCALE_Y	(30)
#define EXPLOSION_SCALE_X	(30)

//================================================================================
//オブジェクトクラス(プレイヤー)
//================================================================================
class CExplosion :public CScene2D
{
public:

	CExplosion(int nPriority = OBJTYPE_EXPLOSION);						//コンストラクタ
	~CExplosion();														//デストラクタ

	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);		//爆発の生成

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);					//初期化処理
	void Uninit(void);													//終了処理
	void Update(void);													//更新処理
	void Draw(void);													//描画処理
	static HRESULT Load(void);											//読み込み処理
	static void Unload(void);											//破棄処理

private:

	D3DXVECTOR3 m_scale;												//	大きさ
	int m_CounterAnim;													//	アニメーションカウンター
	int m_nPatternAnim;													//	テクスチャのパターンNo.
	static LPDIRECT3DTEXTURE9 m_pTexture;								//	テクスチャ
};
#endif

