//--------------------------------------------------------------------------------
//
// ゲーム制作[game.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "manager.h"
#include "polygon.h"

//--------------------------------------------------------------------------------
//前方宣言
//--------------------------------------------------------------------------------
class CPolygon;

//--------------------------------------------------------------------------------
//マクロ定義
//--------------------------------------------------------------------------------
#define SCREEN_WIDTH		(1280)									//スクリーンの幅
#define SCREEN_HEIGHT		(720)									//スクリーンの高さ
#define SCREEN_GAMEWIDTH	(830)									//ゲーム画面中のスクリーンの幅
#define SCREEN_GAMEHEIGHT	(690)									//ゲーム画面中のスクリーンの高さ
#define SCREEN_CENTER_X		(SCREEN_WIDTH/2)						//スクリーン中心X座標
#define SCREEN_CENTER_Y		(SCREEN_HEIGHT/2)						//スクリーン中心Y座標

//================================================================================
//オブジェクトクラス
//================================================================================
class CFade
{

public:

	//フェード種類
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX

	}FADE;

	CFade();														//コンストラクタ
	~CFade();														//デストラクタ

	static CFade *Create(void);										//フェードの生成
	static HRESULT Init(void);										//初期化処理
	static void Uninit(void);										//終了処理
	static void Update(void);										//更新処理
	static void Draw(void);											//描画処理

	static void SetFade(FADE fade, CManager::Mode modenext);		//フェード情報の取得
	static FADE GetFade(void) { return m_Fade; }					//フェード情報の呼び出し

private:

	static FADE m_Fade;												// フェード
	static CPolygon *m_pPolygon;									// ゲージのポインタ
	static CManager::Mode m_ModeNext;								// 次のモードへ
	static D3DXCOLOR m_Color;										// カラー

};

#endif

