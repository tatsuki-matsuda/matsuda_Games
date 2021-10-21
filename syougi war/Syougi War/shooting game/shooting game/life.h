//--------------------------------------------------------------------------------
//
// ゲーム制作[item.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _LIFE_H_
#define _LIFE_H_

#include "scene2D.h"

//--------------------------------------------------------------------------------
//マクロ定義
//--------------------------------------------------------------------------------
#define ITEM_MOVE_X		(3)										//アイテムのX軸移動
#define ITEM_MOVE_Y		(10)									//アイテムのY軸移動
#define	MAX_PLAYERLIFE	(5)										//残機数

//--------------------------------------------------------------------------------
//前方宣言
//--------------------------------------------------------------------------------
class CBullet;

//================================================================================
//オブジェクトクラス(ライフ)
//================================================================================
class CLife :public CScene2D
{
public:

	CLife(int nPriority = OBJTYPE_UI);								//コンストラクタ
	~CLife();														//デストラクタ

	static CLife *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);		//残機表示の生成

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				//初期化処理
	void Uninit(void);												//終了処理
	void Update(void);												//更新処理
	void Draw(void);												//描画処理

	static HRESULT Load(void);										//読み込み処理
	static void Unload(void);										//破棄処理

	int GetLife(void) { return m_nLife; }							//現在のライフ数を呼びだし
	void SetLife(int nLife) { m_nLife = nLife; }					//体力の設定

private:

	void OnDiffuesPos(int nCnt);									// カウントでライフ生成

	bool m_bUninit;													// 終了判定処理

	int	 m_nLife;													// 残機カウント
	int	 m_nCntTime;												// 間隔
	int	 m_timer;													// 経過時間

	float m_angle;													// 角度

	static D3DXVECTOR3 m_Craetepos[5];								// いくつかの座標を設定
	D3DXVECTOR3 m_posDeath;											// 消滅したときの位置を保存
	D3DXVECTOR3 m_move;												// 移動
	D3DXVECTOR3 m_scale;											// 大きさ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;						// 頂点バッファのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];				// テクスチャ
	CScene2D*m_apScene2D[5];										// CScene2Dのポインタ
};
#endif
