//--------------------------------------------------------------------------------
//
// ゲーム制作[Enemy.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
#include "input.h"

//-------------------------------------------------------------------------------
//マクロ定義
//-------------------------------------------------------------------------------
#define MAX_ENEMY_PARTS (12)				//敵のパーツ数
#define SEARCHRANGE_ENEMY (300)				//敵の索敵範囲
#define SEARCHSTOP_ENEMY (40)				//敵の索敵停止範囲
#define LAUNCHRANGE_BOSSBULLET (2000)		//ボス弾の発射範囲
#define LAUNCHRANGE_BULLET (240)			//敵弾の発射範囲
#define ENEMY_LIFEBOSS (20)					//ボスの体力
#define ENEMY_LIFE000 (5)					//敵1の体力
#define ENEMY_LIFE001 (3)					//敵2の体力
#define MAX_ENEMY (9)						//敵の数

//--------------------------------------------------------------------------------
//敵の状態
//--------------------------------------------------------------------------------
typedef enum
{
	ENEMYSTATE_NOMARL = 0,	//通常状態
	ENEMYSTATE_DAMAGE,		//ダメージ状態
	ENEMYSTATE_MAX
}ENEMYSTATE;

//-------------------------------------------------------------------------------
//モデルの構造体
//-------------------------------------------------------------------------------
typedef struct
{
	LPD3DXMESH MeshModel = NULL;			//メッシュ(頂点情報)へのポインタ
	D3DXMATERIAL*pMat;
	LPD3DXBUFFER BuffMatModel = NULL;		//マテリアル(材質情報)へのポインタ
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 move;						//移動
	D3DXVECTOR3 rot;						//向き
	ENEMYSTATE State;						//状態
	DWORD	nNumMat;						//マテリアルの数
	D3DXMATRIX  mtxWorld;					//ワールドマトリックス
	int	nNumModel;							//モデル(パーツ)数
	float fRadius;							//敵の回転
	int nType;								//種類
	int nCounterBoss;						//ボスの出現カウンター
	int nCounterEnemy;						//敵の出現カウンター
	int nCounterShot;						//弾の発射カウンター
	int nEnemyLife;							//体力
	int nIdxModelParent;					//親のモデルのインデックス
	bool bUse;								//使用しているかどうか
	bool bUseStopShot;						//停止しているときに弾を使用しているかどうか
	bool bSearchRange;						//索敵範囲に入ってるかどうか
	bool bAppearance;						//敵の出現条件
}ENEMYMODEL;

//-------------------------------------------------------------------------------
//敵の構造体
//-------------------------------------------------------------------------------
typedef struct
{
	LPD3DXMESH MeshModel = NULL;			//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER BuffMatModel = NULL;		//マテリアル(材質情報)へのポインタ
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 move;						//移動
	D3DXVECTOR3 rot;						//向き
	DWORD	nNumMat;						//マテリアルの数
	D3DXMATRIX  mtxWorld;					//ワールドマトリックス
	ENEMYMODEL aModel[MAX_ENEMY_PARTS];		//モデル(パーツ)
	int	nNumModel;							//モデル(パーツ)数
	float fRadius;							//敵の回転
	int nType;								//種類
	int nLife;								//体力
	int nEnemyLife;							//体力
	int nIdxModelParent;					//親のモデルのインデックス
	bool bUse;								//使用しているかどうか
	bool bSearchRange;						//索敵範囲に入ってるかどうか

}Enemy;

//--------------------------------------------------------------------------------
//プロトタイプ宣言
//--------------------------------------------------------------------------------
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
//void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move,int nType, int nLife, D3DXCOLOR col);
Enemy*GetEnemy(void);

#endif

