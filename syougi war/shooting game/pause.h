//--------------------------------------------------------------------------------
//
// ゲーム制作[bg.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "scene2D.h"

//--------------------------------------------------------------------------------
//マクロ定義
//--------------------------------------------------------------------------------
#define MAX_PAUSEUI				(4)										//ポーズUIの最大数

//================================================================================
//オブジェクトクラス(背景)
//================================================================================
class CPause :public CScene
{
public:

	typedef enum
	{
		PAUSEUI_NONE = 0,
		PAUSEUI_CONTINUE,
		PAUSEUI_RETRY,
		PAUSEUI_TITLE,
		PAUSEUI_MAX

	}PAUSEUI;

	CPause(int nPriority = OBJTYPE_PAUSE);								//	コンストラクタ
	~CPause();															//	デストラクタ

	static CPause *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);			//	プレイヤーの生成

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);					//	初期化処理
	void Uninit(void);													//	終了処理
	void Update(void);													//	更新処理
	void Draw(void);													//	描画処理

	static HRESULT Load(void);											//	読み込み処理
	static void Unload(void);											//	破棄処理



private:

	float m_fMove;													//  移動
	float m_fAnim;													//	アニメーション
	int	  m_ColorCnt;												//	色点滅カウント
	int   m_nSelectCnt;												//	選択カウント
	static LPDIRECT3DTEXTURE9 m_apTexture[PAUSEUI_MAX];				//	テクスチャ
	CScene2D*m_apScene2D[PAUSEUI_MAX];								//	CScene2Dのポインタ
};
#endif