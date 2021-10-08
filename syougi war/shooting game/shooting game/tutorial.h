//--------------------------------------------------------------------------------
//
// ゲーム制作[title.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "bg.h"
#include "player.h"
#include "enemy.h"

//--------------------------------------------------------------------------------
//前方宣言
//--------------------------------------------------------------------------------
class CBg;

//================================================================================
//オブジェクトクラス
//================================================================================
class CTutorial : CScene
{

public:

	CTutorial();													//コンストラクタ
	~CTutorial();													//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				//初期化処理
	void Uninit(void);												//終了処理
	void Update(void);												//更新処理
	void Draw(void);												//描画処理

	static CBg*GetBg(void);											//背景情報の呼び出し

private:

	static CBg*m_pBg;

};

#endif

