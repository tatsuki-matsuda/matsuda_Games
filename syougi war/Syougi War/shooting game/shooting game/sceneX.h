//--------------------------------------------------------------------------------
//
// ゲーム制作[sceneX.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _SCENEX_H_
#define _SCENEX_H_

#include "main.h"
#include "input.h"
#include "scene.h"

//================================================================================
//オブジェクトクラス(背景)
//================================================================================
class CSceneX :public CScene
{
public:

	CSceneX(int nPriority = OBJTYPE_UI);
	~CSceneX();

	static CSceneX *Create(D3DXVECTOR3 pos);							//シーンの生成

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);					//初期化処理
	void Uninit(void);													//終了処理
	void Update(void);													//更新処理
	void Draw(void);													//描画処理

private:

	D3DXVECTOR3	m_rotmove;

	LPDIRECT3D9 m_apTextureModel[100] = {};		//テクスチャへのポインタ
	LPD3DXMESH m_pMeshModel;					//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER m_pBuffMatModel;				//マテリアル(材質情報)へのポインタ
	D3DXVECTOR3 m_posModel;						//位置
	D3DXVECTOR3 m_rotModel;						//向き
	D3DXMATRIX  m_mtxWorldModel;				//ワールドマトリックス
	DWORD m_nNumMatModel;						//マテリアルの数
};
#endif