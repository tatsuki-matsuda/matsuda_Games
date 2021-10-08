//--------------------------------------------------------------------------------
//
// ゲーム制作[score.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _SCORE_H_
#define _SCORE_H_

#include "scene.h"
#include "number.h"

//--------------------------------------------------------------------------------
//マクロ定義
//--------------------------------------------------------------------------------
#define MAX_DIGIT      (8)
//================================================================================
//オブジェクトクラス
//================================================================================
class CScore : public CScene
{

public:
	typedef enum
	{
		SCORETYPE_NORMAL=0,
		SCORETYPE_GRAZE,
		SCORETYPE_MAX

	}SCORETYPE;

	CScore(int nPriority = OBJTYPE_UI);									//コンストラクタ
	~CScore();															//デストラクタ

	static CScore *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, SCORETYPE scoretype);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);					//初期化処理
	void Uninit(void);													//終了処理
	void Update(void);													//更新処理
	void Draw(void);													//描画処理

	void SetScore(int nScore);											//スコア情報
	void SetScoreType(SCORETYPE scoretype);								//スコアタイプ情報

	void AddScore(int nValue);											//スコア処理
	void AddGraze(int nValue);											//グレイズ処理

	int GetScore(void) { return m_nScore; }								//スコア加算

private:

	SCORETYPE m_ScoreType;												// スコアタイプ
	CNumber *m_apNumber[8];
	int m_nDigit;														// 桁数
	int m_nScore;														// スコア
	D3DXVECTOR3 m_pos;													// 位置
	D3DXVECTOR3 m_scale;												// 大きさ
};

#endif

