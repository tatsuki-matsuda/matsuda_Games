//--------------------------------------------------------------------------------
//
// ゲーム制作[bullet.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//-------------------------------------------------------------------------------
//マクロ定義
//-------------------------------------------------------------------------------
#define MAX_BULLET (2560)

//-------------------------------------------------------------------------------
//弾の状態
//-------------------------------------------------------------------------------
typedef enum
{
	BULLETSTATE_PLAYER = 0,	//自機弾
	BULLETSTATE_ENEMY,		//敵弾
	BULLETSTATE_FALSE,		//消滅
	BULLETSTATE_MAX

}BULLETSTATE;

//-------------------------------------------------------------------------------
//構造体の宣言
//-------------------------------------------------------------------------------
typedef struct
{
	BULLETSTATE State;			//状態
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 move;			//移動量
	float fRadius;
	int nType;					//弾の切り替え
	int nLife;					//寿命
	int nCnt;
	bool bUse;					//使用しているかどうか
}BULLET;

//--------------------------------------------------------------------------------
//プロトタイプ宣言
//--------------------------------------------------------------------------------
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETSTATE state, int nLife, D3DXCOLOR col);
void SetVertexBullet(int nIdx);
BULLET*GetBullet(void);
#endif
