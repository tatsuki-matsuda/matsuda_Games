//--------------------------------------------------------------------------------
//
// ゲーム制作[power.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _POWER_H_
#define _POWER_H_

#include "scene2D.h"

//--------------------------------------------------------------------------------
//マクロ定義
//--------------------------------------------------------------------------------
#define MAX_ITEM				(2)									//アイテムの最大個数

//--------------------------------------------------------------------------------
//前方宣言
//--------------------------------------------------------------------------------
class CEnemy;

//================================================================================
//オブジェクトクラス(敵)
//================================================================================
class CItem :public CScene2D
{
public:


	//敵の状態
	typedef enum
	{
		ITEM_NONE = 0,
		ITEM_NORMAL,															//通常アイテム
		ITEM_MAX

	}ITEM;

	CItem(int nPriority = OBJTYPE_ITEM);										//コンストラクタ
	~CItem();																	//デストラクタ

	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,
		D3DXVECTOR3 move);														//アイテムの生成

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale,
		D3DXVECTOR3 move);														//初期化処理
	void Uninit(void);															//終了処理
	void Update(void);															//更新処理
	void Draw(void);															//描画処理

	static void Load(void);														//読み込み処理
	static void Unload(void);													//破棄処理

	void EnemyState(void);														//敵の状態

	static LPDIRECT3DTEXTURE9  GetTexture(int nCntTex);							//テクスチャ情報の取得

	ITEM GetEnemyState(void) { return m_Item; }									//アイテム情報の取得
	void SetEnemyState(ITEM item) { m_Item = item; }							//アイテム情報

	int GetLife(void) { return m_nLife; }										//体力情報の取得
	void SetLife(int nLife) { m_nLife = nLife; }								//体力情報


private:

	ITEM	m_Item;																// 敵の状態

	bool m_bUninit;																// 終了判定処理

	int	 m_nEnemyAppearanceCnt;													// 敵出現カウント
	int	 m_nEnemyCnt;															// 敵消滅カウント
	int	 m_nEnemyTime;															// 出現カウント	 
	int	 m_nPlayerCnt = 0;														// プレイヤー消滅後カウント
	int	 m_nEnemymoveCnt;														// 敵移動カウント
	int	 m_nBulletStartCnt;														// 撃ち始めカウント
	int	 m_nCntCrossingTime;													// 交差間隔カウント
	int	 m_nCntTime;															// 発射間隔
	int	 m_nCntMadness;															// 発狂カウント
	int	 m_nNormalEnemyMove;													// 通常敵移動カウント
	int  m_nCntColor;															// 色の切り替わり間隔
	int  m_nCntBullet;															// 発射カウント
	int	 m_timer;																// 発射時間
	int  m_nLife;																// 体力		
	int	 m_nMaxLife;															// 出現時の体力

	float m_fangle;																// 角度
	float m_fLength;															// 長さ

	static D3DXVECTOR3 m_Craetepos[10];											// いくつかの座標を設定
	D3DXVECTOR3 m_posBoss;														// ボスの位置を保存
	D3DXVECTOR3 m_posDeath;														// 消滅したときの位置を保存
	D3DXVECTOR3 m_moveSave;														// 移動値を保存
	D3DXVECTOR3 m_move;															// 移動
	D3DXVECTOR3 m_scale;														// 大きさ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;									// 頂点バッファのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];							// テクスチャ
	D3DXCOLOR m_Color;															// カラー
};
#endif
