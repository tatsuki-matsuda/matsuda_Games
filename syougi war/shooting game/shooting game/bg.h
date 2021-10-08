//--------------------------------------------------------------------------------
//
// ゲーム制作[bg.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _BG_H_
#define _BG_H_

#include "scene2D.h"

//--------------------------------------------------------------------------------
//マクロ定義
//--------------------------------------------------------------------------------
#define SCREEN_WIDTH		(1280)									//スクリーンの幅
#define SCREEN_HEIGHT		(720)									//スクリーンの高さ
#define SCREEN_CENTER_X		(SCREEN_WIDTH/2)						//スクリーン中心X座標
#define SCREEN_CENTER_Y		(SCREEN_HEIGHT/2)						//スクリーン中心Y座標
#define MAX_BG				(5)										//背景の最大数

//================================================================================
//オブジェクトクラス(背景)
//================================================================================
class CBg :public CScene
{
public:

	CBg(int nPriority=OBJTYPE_BG);									//コンストラクタ
	~CBg();															//デストラクタ

	static CBg *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);			//プレイヤーの生成

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				//初期化処理
	void Uninit(void);												//終了処理
	void Update(void);												//更新処理
	void Draw(void);												//描画処理

	static HRESULT Load(void);										//読み込み処理
	static void Unload(void);										//破棄処理

private:

	float m_fAnim;													//	アニメーション
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG];					//	テクスチャ
	CScene2D*m_apScene2D[5] = {};									//	CScene2Dのポインタ
};
#endif