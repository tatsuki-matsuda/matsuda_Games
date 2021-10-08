//--------------------------------------------------------------------------------
//
// ゲーム制作[game_screen.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _GAME_SCREEN_H_
#define _GAME_SCREEN_H_

#include "scene2D.h"

//================================================================================
//オブジェクトクラス(ゲーム背景)
//================================================================================
class CGame_Screen :public CScene
{
public:

	CGame_Screen(int nPriority = OBJTYPE_GAME);						//コンストラクタ
	~CGame_Screen();												//デストラクタ

	static CGame_Screen *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//ゲーム背景の生成

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				//初期化処理
	void Uninit(void);												//終了処理
	void Update(void);												//更新処理
	void Draw(void);												//描画処理

	static HRESULT Load(void);										//読み込み処理
	static void Unload(void);										//破棄処理

private:

	static LPDIRECT3DTEXTURE9 m_apTexture[1];						//	テクスチャ
	CScene2D*m_apScene2D[1];										//	CScene2Dのポインタ
};
#endif