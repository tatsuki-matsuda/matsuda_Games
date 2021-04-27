//--------------------------------------------------------------------------------
//
// ゲーム制作[MeshField.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
#include "main.h"
#include "input.h"

//--------------------------------------------------------------------------------
//メッシュフィールドの構造体
//--------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 rot;			//向き
}MESHFIELD;

//--------------------------------------------------------------------------------
//プロトタイプ宣言
//--------------------------------------------------------------------------------
HRESULT InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);
MESHFIELD*GetMeshField(void);
//bool HitPoligon(void);
#endif

