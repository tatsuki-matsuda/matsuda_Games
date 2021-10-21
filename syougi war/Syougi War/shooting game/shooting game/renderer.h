//--------------------------------------------------------------------------------
//
// ゲーム制作[renderer.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

//--------------------------------------------------------------------------------
//マクロ定義
//--------------------------------------------------------------------------------

//================================================================================
//Rendererクラス
//================================================================================
class CRenderer
{

public:

	CRenderer();									//コンストラクタ
	~CRenderer();									//デストラクタ

	HRESULT Init(HWND hWnd, BOOL bWindow);			//初期化処理
	void Uninit(void);								//終了処理
	void Update(void);								//更新処理
	void Draw(void);								//描画処理
	void ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR,D3DXVECTOR3 posU);

	LPDIRECT3DDEVICE9 GetDevice(void) {return m_pD3DDevice;}

private:

	void DrawFPS(void);								// FPSの描画処理

	LPDIRECT3D9 m_pD3D = NULL;						// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9 m_pD3DDevice = NULL;			// Deviceオブジェクト(描画に必要)

	LPDIRECT3DTEXTURE9 m_pTextureMT;				// レンダリングターゲット用のテクスチャ
	LPDIRECT3DSURFACE9 m_pRenderMT;					// テクスチャレンダリング用インターフェース

	LPDIRECT3DSURFACE9 m_pBuffMT;					// テクスチャレンダリング用Zバッファ
	D3DVIEWPORT9 m_viewportMT;						// テクスチャレンダリング用ビューポート

	//D3DXVECTOR3 m_rot;
	//float m_fAngle;
	//float m_Length;

	#ifdef _DEBUG
	LPD3DXFONT m_pFont = NULL;						// フォントへのポインタ
	#endif
};
#endif

