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
#define ENEMY_LIFE			(1500)									//敵のライフ
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
		ENEMYTYPE_NORMAL4,				//通常弾4を撃つ敵
		ENEMYTYPE_NORMAL5,				//通常弾5を撃つ敵
		ENEMYTYPE_HOMING,				//追従弾を撃つ敵
		ENEMYTYPE_CROSSING,				//交差弾を撃つ敵
		ENEMYTYPE_REFLECTION,			//反射弾を撃つ敵
		ENEMYTYPE_REFLECTION_UPDAWN,	//上下反射弾を撃つ敵
		ENEMYTYPE_TURN,					//折り返し弾を撃つ敵
		ENEMYTYPE_N_WAY1,				//n_way弾1を撃つ敵
		ENEMYTYPE_N_WAY2,				//n_way弾2を撃つ敵
		ENEMYTYPE_MAX

	}ENEMYTYPE;

	CEnemy(int nPriority = OBJTYPE_ENEMY);							//コンストラクタ
	~CEnemy();														//デストラクタ

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,
		D3DXVECTOR3 move, ENEMYTYPE enemyType);						//敵の生成

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale
		, D3DXVECTOR3 move);										//初期化処理
	void Uninit(void);												//終了処理
	void Update(void);												//更新処理
	void Draw(void);												//描画処理

	static void Load(void);											//読み込み処理
	static void Unload(void);										//破棄処理

	static LPDIRECT3DTEXTURE9  GetTexture(int nCntTex);				//テクスチャ情報の取得

	ENEMYTYPE GetEnemyType(void);									//敵情報の取得
	void SetEnemyType(ENEMYTYPE enemyType);							//敵情報

	int GetLife(void) { return m_nLife; }
	void SetLife(int nLife) { m_nLife = nLife; }

	int GetMaxLife(void) { return m_nMaxLife; }
	void SetMaxLife(int nMaxlife) { m_nMaxLife = nMaxlife; }

	CLifeGauge *GetLifeGauge(void) { return m_pLifeGauge; }

private:

	void OnDiffuesPos(D3DXVECTOR3 pos, D3DXVECTOR3 move);			//	弾の生成位置処理

	ENEMYTYPE m_EnemyType;											// 敵の種類

	bool m_bUninit;													// 終了判定処理

	int	 m_nEnemyAppearanceCnt;										// 敵出現カウント
	int	 m_nEnemyCnt;												// 敵消滅カウント
	int	 m_nEnemyTime;												// 出現カウント	 

	int	 m_nEnemymoveCnt;											// 敵移動カウント
	int	 m_nBulletStartCnt;											// 撃ち始めカウント
	int	 m_nCntCrossingTime;										// 交差間隔カウント
	int	 m_nCntTime;												// 発射間隔
	int	 m_timer;													// 発射時間
	int  m_nLife;													// 体力		
	int	 m_nMaxLife;												// 出現時の体力

	float m_angle;													// 角度

	static D3DXVECTOR3 m_Craetepos[10];								// いくつかの座標を設定
	D3DXVECTOR3 m_posDeath;											// 消滅したときの位置を保存
	D3DXVECTOR3 m_move;												// 移動
	D3DXVECTOR3 m_scale;											// 大きさ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;						// 頂点バッファのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];				//	テクスチャ

	CLifeGauge *m_pLifeGauge;										// ゲージのポインタ
};
#endif