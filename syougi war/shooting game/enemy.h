//--------------------------------------------------------------------------------
//
// ゲーム制作[enemy.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "scene2D.h"

//--------------------------------------------------------------------------------
//マクロ定義
//--------------------------------------------------------------------------------
#define ENEMY				(2)										//敵の数
#define ENEMY_LIFE			(2500)									//敵のライフ
#define ENEMY_MOVE_X		(3)										//敵のX軸移動
#define ENEMY_MOVE_Y		(10)									//敵のY軸移動
#define N_WAY_CREATE		(5)										//n_way弾の生成数

//--------------------------------------------------------------------------------
//前方宣言
//--------------------------------------------------------------------------------
class CBullet;
class CLifeGauge;

//================================================================================
//オブジェクトクラス(敵)
//================================================================================
class CEnemy :public CScene2D
{
public:

	//攻撃種類分け
	typedef enum
	{
		ENEMYTYPE_NONE = 0,
		ENEMYTYPE_NORMAL1,				//通常弾1を撃つ敵
		ENEMYTYPE_NORMAL2,				//通常弾2を撃つ敵
		ENEMYTYPE_NORMAL3_R,			//右側から通常弾3を撃つ敵
		ENEMYTYPE_NORMAL3_L,			//左側から通常弾3を撃つ敵
		ENEMYTYPE_NORMAL4_R,			//右側から通常弾4を撃つ敵
		ENEMYTYPE_NORMAL4_L,			//左側から通常弾4を撃つ敵
		ENEMYTYPE_NORMAL5,				//通常弾5を撃つ敵
		ENEMYTYPE_HOMING,				//追従弾を撃つ敵
		ENEMYTYPE_CROSSING,				//交差弾を撃つ敵
		ENEMYTYPE_ROTATION,				//回転弾を撃つ敵
		ENEMYTYPE_REFLECTION,			//反射弾を撃つ敵
		ENEMYTYPE_REFLECTION_UPDAWN,	//上下反射弾を撃つ敵
		ENEMYTYPE_TURN,					//折り返し弾を撃つ敵
		ENEMYTYPE_N_WAY1,				//n_way弾1を撃つ敵
		ENEMYTYPE_N_WAY2,				//n_way弾2を撃つ敵
		ENEMYTYPE_RUSH,					//突進する敵
		ENEMYTYPE_MAX

	}ENEMYTYPE;

	//フェーズ分け
	typedef enum
	{
		PHASETYPE_NONE = 0,
		PHASETYPE_1,
		PHASETYPE_2,		
		PHASETYPE_3,
		PHASETYPE_MAX

	}PHASETYPE;

	//敵の状態
	typedef enum
	{
		ENEMYSTATE_NONE = 0,
		ENEMYSTATE_NORMAL,				//通常状態
		ENEMYSTATE_DAMAGE,				//ダメージ状態
		ENEMYSTATE_MAX

	}ENEMYSTATE;

	CEnemy(int nPriority = OBJTYPE_ENEMY);										//コンストラクタ
	~CEnemy();																	//デストラクタ

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,
		D3DXVECTOR3 move, ENEMYTYPE enemyType);									//敵の生成

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale
		, D3DXVECTOR3 move);													//初期化処理
	void Uninit(void);															//終了処理
	void Update(void);															//更新処理
	void Draw(void);															//描画処理

	static void Load(void);														//読み込み処理
	static void Unload(void);													//破棄処理

	void EnemyState(void);														//敵の状態

	static LPDIRECT3DTEXTURE9  GetTexture(int nCntTex);							//テクスチャ情報の取得

	ENEMYTYPE GetEnemyType(void);												//敵情報の取得
	void SetEnemyType(ENEMYTYPE enemyType);										//敵情報

	ENEMYSTATE GetEnemyState(void) { return m_EnemyState; }						//状態情報の取得
	void SetEnemyState(ENEMYSTATE enemyState) { m_EnemyState = enemyState; }	//状態情報

	PHASETYPE GetFaseType(void) { return m_PhaseType; }							//フェーズ情報の取得
	void SetPhaseType(PHASETYPE phasetype) { m_PhaseType = phasetype; }			//フェーズ情報

	int GetLife(void) { return m_nLife; }										//体力情報の取得
	void SetLife(int nLife) { m_nLife = nLife; }								//体力情報

	int GetMaxLife(void) { return m_nMaxLife; }									//最大体力情報の取得
	void SetMaxLife(int nMaxlife) { m_nMaxLife = nMaxlife; }					//最大体力情報

	CLifeGauge *GetLifeGauge(void) { return m_pLifeGauge; }						//体力ゲージの取得

private:

	void OnCollision(void);														//	判定処理
	void OnDiffuesPos(D3DXVECTOR3 pos, D3DXVECTOR3 move);						//　弾の生成位置処理

	ENEMYTYPE m_EnemyType;														// 敵の種類
	ENEMYSTATE	m_EnemyState;													// 敵の状態
	PHASETYPE m_PhaseType;														// フェーズの状態

	bool m_bUninit;																// 終了判定処理

	int	 m_nEnemyAppearanceCnt;													// 敵出現カウント
	int	 m_nEnemyCnt;															// 敵消滅カウント
	int	 m_nEnemyTime;															// 出現カウント	 
	int	 m_nPlayerCnt = 0;														// プレイヤー消滅後カウント
	int	 m_nEnemymoveCnt;														// 敵移動カウント
	int	 m_nBulletStartCnt;														// 撃ち始めカウント
	int	 m_nCntCrossingTime;													// 交差間隔カウント
	int	 m_nCntTime;															// 発射間隔
	int	 m_nNormalEnemyMove;													// 通常敵移動カウント
	int  m_nCntColor;															// 色の切り替わり間隔
	int  m_nCntBullet;															// 発射カウント
	int	 m_timer;																// 発射時間
	int  m_nLife;																// 体力		
	int	 m_nMaxLife;															// 出現時の体力

	float m_fangle;																// 角度
	float m_fLength;															// 長さ

	static D3DXVECTOR3 m_Craetepos[10];											// いくつかの座標を設定
	D3DXVECTOR3 m_posBoss;														// ボスの位置を保存
	D3DXVECTOR3 m_posDeath;														// 消滅したときの位置を保存
	D3DXVECTOR3 m_moveSave;														// 移動値を保存
	D3DXVECTOR3 m_move;															// 移動
	D3DXVECTOR3 m_scale;														// 大きさ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;									// 頂点バッファのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];							// テクスチャ
	D3DXCOLOR m_Color;															// カラー

	CLifeGauge *m_pLifeGauge;													// ゲージのポインタ
};
#endif