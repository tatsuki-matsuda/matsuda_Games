//--------------------------------------------------------------------------------
//
// ゲーム制作[item.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _ITEM_H_
#define _ITEM_H_

#include "scene2D.h"

//--------------------------------------------------------------------------------
//マクロ定義
//--------------------------------------------------------------------------------
#define ITEM_MOVE_X		(3)										//アイテムのX軸移動
#define ITEM_MOVE_Y		(10)									//アイテムのY軸移動

//--------------------------------------------------------------------------------
//前方宣言
//--------------------------------------------------------------------------------
class CBullet;

//================================================================================
//オブジェクトクラス(敵)
//================================================================================
class CItem :public CScene2D
{
public:

	//アイテム種類
	typedef enum
	{
		ITEMTYPE_NONE = 0,
		ITEMTYPE_1UP,
		ITEMTYPE_BOMB,
		ITEMTYPE_POWERUP,
		ITEMTYPE_MAX

	}ITEMTYPE;

	CItem(int nPriority = OBJTYPE_ITEM);							//コンストラクタ
	~CItem();														//デストラクタ

	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,
		D3DXVECTOR3 move, ITEMTYPE itemType);						//アイテムの生成

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale
		, D3DXVECTOR3 move);										//初期化処理
	void Uninit(void);												//終了処理
	void Update(void);												//更新処理
	void Draw(void);												//描画処理

	static HRESULT Load(void);										//読み込み処理
	static void Unload(void);										//破棄処理

	ITEMTYPE GetItemType(void) { return m_ItemType; }				//アイテム情報の取得
	void SetItemType(ITEMTYPE itemType) { m_ItemType = itemType; }	//アイテム情報

private:

	void OnDiffuesPos(D3DXVECTOR3 pos, D3DXVECTOR3 move);			// アイテムの生成位置処理

	ITEMTYPE m_ItemType;											// アイテムの種類

	bool m_bUninit;													// 終了判定処理

	int	 m_nItemCnt;												// アイテム出現カウント
	int	 m_nItemmoveCnt;											// アイテム移動カウント
	int	 m_nCntTime;												// 間隔
	int	 m_timer;													// 経過時間

	float m_angle;													// 角度

	static D3DXVECTOR3 m_Craetepos[10];								// いくつかの座標を設定
	D3DXVECTOR3 m_posDeath;											// 消滅したときの位置を保存
	D3DXVECTOR3 m_move;												// 移動
	D3DXVECTOR3 m_scale;											// 大きさ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;						// 頂点バッファのポインタ

	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];											//	テクスチャ
	CScene2D*m_apScene2D[MAX_SCENE2D];															//	CScene2Dのポインタ
};
#endif