//--------------------------------------------------------------------------------
//
// ゲーム制作[number.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"

//--------------------------------------------------------------------------------
//マクロ定義
//--------------------------------------------------------------------------------
#define SCREEN_WIDTH		(1280)									//スクリーンの幅
#define SCREEN_HEIGHT		(720)									//スクリーンの高さ
#define SCREEN_CENTER_X		(SCREEN_WIDTH/2)						//スクリーン中心X座標
#define SCREEN_CENTER_Y		(SCREEN_HEIGHT/2)						//スクリーン中心Y座標
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//頂点フォーマット

//================================================================================
//オブジェクトクラス
//================================================================================
class CNumber
{

public:

	CNumber();														//コンストラクタ
	~CNumber();														//デストラクタ

	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				//初期化処理
	void Uninit(void);												//終了処理
	void Update(void);												//更新処理
	void Draw(void);												//描画処理
	void SetNumber(int nNumber);									//スコア表示処理
	D3DXVECTOR3 GetPosition(void);									//位置の取得
	D3DXVECTOR3 GetScale(void);										//大きさ情報の取得
	static void Load(void);											//読み込み処理
	static void Unload(void);										//破棄処理
private:


	static LPDIRECT3DTEXTURE9 m_pTexture;								// テクスチャ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;							// 頂点バッファのポインタ
	D3DXVECTOR3 m_pos;													// 位置
	D3DXVECTOR3 m_scale;												// 大きさ
};

#endif