//--------------------------------------------------------------------------------
//
// ゲーム制作[result.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "bg.h"
#include "player.h"
#include "enemy.h"

//--------------------------------------------------------------------------------
//前方宣言
//--------------------------------------------------------------------------------
class CBg;
class CScore;

//================================================================================
//オブジェクトクラス
//================================================================================
class CResult : CScene
{

public:

	CResult();														//コンストラクタ
	~CResult();														//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				//初期化処理
	void Uninit(void);												//終了処理
	void Update(void);												//更新処理
	void Draw(void);												//描画処理

	static CBg*GetBg(void);											//背景情報の呼び出し
	static CScore*GetScore(void) { return m_pScore; }				//スコア情報の呼び出し
	static CScore*GetGraze(void) { return m_pGraze; }				//グレイズ情報の呼び出し

private:

	static CBg*m_pBg;												// 背景のポインタ
	static CScore*m_pScore;											// スコアのポインタ
	static CScore*m_pGraze;											// グレイズのポインタ

	int m_nScore = 0;												// 基礎となるスコア

};

#endif



