//--------------------------------------------------------------------------------
//
// ゲーム制作[player.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"
#include "input.h"



//--------------------------------------------------------------------------------
//各モーションの状態
//--------------------------------------------------------------------------------
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,	//待機モーション
	MOTIONTYPE_RUN,		//パンチモーション
}MOTIONTYPE;

//-------------------------------------------------------------------------------
//キーの構造体
//-------------------------------------------------------------------------------
typedef struct
{
	float fPosX;	//キーの位置X
	float fPosY;	//キーの位置Y
	float fPosZ;	//キーの位置Z
	float fRotX;	//キーの回転X
	float fRotY;	//キーの回転Y
	float fRotZ;	//キーの回転Z	
}KEY;

//-------------------------------------------------------------------------------
//キー情報の構造体
//-------------------------------------------------------------------------------
typedef struct
{
	KEY aKey[14];	//各モデルのキー要素

	int nFlame;		//再生フレーム
}KEY_INFO;

//-------------------------------------------------------------------------------
//モーション情報の構造体
//-------------------------------------------------------------------------------
typedef struct
{
	KEY_INFO aKeyInfo[14];	//キー情報

	int nNumKey;			//キー総数
	
	float fPosY;			//キーの位置Y
	float fPosZ;			//キーの位置Z

	bool bloop;				//ループするかどうか
}MOTION_INFO;


//-------------------------------------------------------------------------------
//モデルの構造体
//-------------------------------------------------------------------------------
typedef struct
{
	LPD3DXMESH MeshModel = NULL;			//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER BuffMatModel = NULL;		//マテリアル(材質情報)へのポインタ
	DWORD	nNumMat;						//マテリアルの数
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 Bulletpos;					//発射位置
	D3DXVECTOR3 oldpos;						//前回の位置
	D3DXVECTOR3 rot;						//向き
	D3DXMATRIX  mtxWorld;					//ワールドマトリックス

	int nIdxModelParent;					//親のモデルのインデックス
}Model;

//-------------------------------------------------------------------------------
//プレイヤーの構造体
//-------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 oldpos;						//前回の位置
	D3DXVECTOR3 move;						//移動
	D3DXVECTOR3 rot;						//向き
	D3DXMATRIX  mtxWorld;					//ワールドマトリックス

	MOTION_INFO aMotionInfo[2];				//モーション情報
	Model aModel[14];						//モデル(パーツ)

	int	nNumModel;							//モデル(パーツ)数
	int nNumMotion;							//モーション数
	int nCounterMotion;						//モーションカウンター
	int nNumKey;							//キー数
	int nKey;								//キーNo.

	float fRadius;							//半径

	bool bLoopMotion;						//モーションカウンター
	bool bUse;								//使用しているかどうか
}Player;


//--------------------------------------------------------------------------------
//プロトタイプ宣言
//--------------------------------------------------------------------------------
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player*GetPlayer(void);
//bool HitPoligon(void);
#endif
