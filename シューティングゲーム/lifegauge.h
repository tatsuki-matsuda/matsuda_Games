//--------------------------------------------------------------------------------
//
// ゲーム制作[lifegauge.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _LIFEGAUGE_H_
#define _LIFEGAUGE_H_

#include "scene2D.h"

//--------------------------------------------------------------------------------
//マクロ定義
//--------------------------------------------------------------------------------
#define LIFUGAUGE_Y		(5)										//ゲージの縦幅
#define GAUGEBASE_X	(600)									//ゲージの最大横幅
#define GAUGEUP_X		(5)										//横ゲージの増加する値

//--------------------------------------------------------------------------------
//前方宣言
//--------------------------------------------------------------------------------
class CEnemy;

//================================================================================
//オブジェクトクラス(敵)
//================================================================================
class CLifeGauge : public CScene2D
{
public:

	CLifeGauge(int nPriority = OBJTYPE_UI);							//コンストラクタ
	~CLifeGauge();													//デストラクタ

	static CLifeGauge *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,int nBaseLife);			//体力ゲージの生成

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int nBaseLife);					//初期化処理
	void Uninit(void);																		//終了処理
	void Update(void);																		//更新処理
	void Draw(void);																		//描画処理

	void OnDiffuse(int nDiffuseLife);														//ゲージ縮小処理
	void OnGaugeUp(void);																	//ゲージ増加処理

	bool GetGaugeUp(void) { return m_bGaugeUp; }
	void SetGaugeUp(bool bGaugeUp) { m_bGaugeUp = bGaugeUp; }

private:

	bool m_bUninit;													// 終了判定処理
	bool m_bGaugeUp;												// ゲージ増加判定

	int	 m_nCntTime;												// 間隔
	int	 m_timer;													// 時間
	int  m_nLife;													// 体力	
	int  m_nBaseLife;												// 基礎となる体力値
	int  m_nSaveLife;												// 保存する体力値


	D3DXVECTOR3 m_Scale_move;
	D3DXVECTOR3 m_BaseScale;										// 基礎となる大きさ
	D3DXVECTOR3 m_BasePos;											// 基礎となる大きさ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;						// 頂点バッファのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture;							// テクスチャ
};
#endif
