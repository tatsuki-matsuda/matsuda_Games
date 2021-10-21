#pragma once
//--------------------------------------------------------------------------------
//
// ゲーム制作[scene2D.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "main.h"

//================================================================================
//オブジェクトクラス(2Dポリゴン)
//================================================================================
class CPolygon
{
public:

	CPolygon();														//コンストラクタ
	~CPolygon();													//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				//初期化処理
	void Uninit(void);												//終了処理
	void Draw(void);												//描画処理

	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);	//ポリゴンの生成

	void SetColor(D3DXCOLOR color);									//カラーの設定


private:

	int nCnt;										// アニメーションパターンNo
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;					// テクスチャ
	D3DXVECTOR3 m_pos;								// ポリゴンの位置
	D3DXVECTOR3 m_scale;							// 大きさ
};

#endif