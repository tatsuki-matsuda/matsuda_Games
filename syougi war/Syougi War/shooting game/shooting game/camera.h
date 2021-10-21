//--------------------------------------------------------------------------------
//
// ゲーム制作[camera.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"
#include "dinput_keyboard.h"

//--------------------------------------------------------------------------------
//マクロ定義
//--------------------------------------------------------------------------------
#define	MAX_POSV_Z		(10)		//カメラの奥行き
#define	MAX_POSV_Y		(150)		//カメラの高さ

//--------------------------------------------------------------------------------
//カメラの構造体
//--------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 posV;			//現在の視点
	D3DXVECTOR3 posVDest;		//目的の視点
	D3DXVECTOR3	posR;			//現在の注視点
	D3DXVECTOR3	posRDest;		//目的の注視点
	D3DXVECTOR3	posU;			//上方向ベクトル
	D3DXVECTOR3 rot;			//カメラの向き
	D3DXMATRIX	mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX	mtxView;		//ビューマトリックス
}CAMERA;

//================================================================================
//オブジェクトクラス(カメラ)
//================================================================================
class CCamera
{
public:
	CCamera();
	~CCamera();

	void InitCamera(void);
	void UninitCamera(void);
	void UpdateCamera(void);

	CAMERA GetCamera(void) { return m_apCamera; }
	void SetCamera(void);

private:

	CAMERA m_apCamera;	//カメラの情報
};
#endif
