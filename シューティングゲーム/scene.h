//--------------------------------------------------------------------------------
//
// ゲーム制作[scene.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//--------------------------------------------------------------------------------
//マクロ定義
//--------------------------------------------------------------------------------
#define MAX_POLYGON	(512)												//ポリゴンの最大表示数


//================================================================================
//オブジェクトクラス
//================================================================================
class CScene
{

public:

	//種類分け
	typedef enum
	{
		OBJTYPE_NONE = 0,		
		OBJTYPE_BG,					//背景
		OBJTYPE_EFFECT,				//エフェクト
		OBJTYPE_EXPLOSION,			//爆発
		OBJTYPE_ENEMY,				//敵
		OBJTYPE_PLAYER,				//プレイヤー
		OBJTYPE_ITEM,				//アイテム
		OBJTYPE_BULLET,				//弾
		OBJTYPE_GAME,				
		OBJTYPE_UI,
		OBJTYPE_MAX

	}OBJTYPE;

	CScene(int nPriority = OBJTYPE_PLAYER);								//コンストラクタ
	virtual ~CScene();													//デストラクタ

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale) = 0;		//初期化処理
	virtual void Uninit(void) = 0;										//終了処理
	virtual void Update(void) = 0;										//更新処理
	virtual void Draw(void) = 0;										//描画処理
	void LifeSub(int nPow);												//体力減算処理

	static void ReleaseAll(void);										//開放処理
	static void UpdateAll(void);										//更新処理
	static void DrawAll(void);											//描画処理

	static CScene *GetScene(int nCntPriority,int nCntScene);			//Sceneの取得
	OBJTYPE GetObjType(void);											//種類情報の取得

	void SetObjType(OBJTYPE objType);									//種類情報

protected:

	void Release(void);													//開放処理

private:

	OBJTYPE m_objType;													// オブジェクトの種類

	LPDIRECT3DTEXTURE9 m_pTexture;										// テクスチャ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;							// 頂点バッファのポインタ

	D3DXVECTOR3 m_pos;													// 位置
	D3DXVECTOR3 m_scale;												// 大きさ

	static CScene*m_apScene[OBJTYPE_MAX][MAX_POLYGON];					// ポリゴンの数
	static int m_nNumAll;												// 最大数

	int m_nPriority;													// 優先順位の番号
	int m_nID;															// 格納先番号
	int m_nLife;														// 体力
};

#endif
