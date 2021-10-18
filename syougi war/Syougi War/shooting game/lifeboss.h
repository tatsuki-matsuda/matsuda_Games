//--------------------------------------------------------------------------------
//
// ゲーム制作[score.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _LIFEBOSS_H_
#define _LIFEBOSS_H_

#include "scene.h"
#include "number.h"

//--------------------------------------------------------------------------------
//マクロ定義
//--------------------------------------------------------------------------------
#define MAX_DIGIT      (8)
#define MAX_BOSSLIFE   (3)
//================================================================================
//オブジェクトクラス
//================================================================================
class CLifeBoss : public CScene
{

public:
	typedef enum
	{
		LIFETYPE_NORMAL = 0,
		LIFETYPE_BOSS,
		LIFETYPE_MAX

	}LIFETYPE;

	CLifeBoss(int nPriority = OBJTYPE_UI);								//コンストラクタ
	~CLifeBoss();														//デストラクタ

	static CLifeBoss *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, LIFETYPE lifecount);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);					//初期化処理
	void Uninit(void);													//終了処理
	void Update(void);													//更新処理
	void Draw(void);													//描画処理

	void SetLifeCnt(int nlifecnt);										//ライフカウント情報
	void SetLifeType(LIFETYPE lifeType) { m_LifeType= lifeType; }		//ライフタイプ情報

	void AddBossLifeCnt(int nValue);									//ボスライフカウント処理

private:

	LIFETYPE m_LifeType;												// ライフの種類
	CNumber *m_apNumber[8];												// 画面内の残弾数
	int m_nDigit;														// 桁数
	int m_nLifeCnt;														// ライフカウント
	D3DXVECTOR3 m_pos;													// 位置
	D3DXVECTOR3 m_scale;												// 大きさ
};

#endif
