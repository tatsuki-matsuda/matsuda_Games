//=============================================================================
//
// メイン処理 [scene.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CScene*CScene::m_apScene[OBJTYPE_MAX][MAX_POLYGON] = {};	// ポリゴンの数
int CScene::m_nNumAll = NULL;								// 最大数
CScene*CScene::m_pTop = NULL;								// 先頭へのポインタ
CScene*CScene::m_pCur = NULL;								// 現在(最後尾のオブジェクト)へのポインタ

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CScene::CScene(int nPriority)
{
	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		if (m_apScene[nPriority][nCntScene] == NULL)
		{
			m_apScene[nPriority][nCntScene] = this;
			m_nID = nCntScene;
			m_nPriority = nPriority;
			m_nNumAll++;
			break;
		}
	}
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CScene::~CScene()
{

}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CScene::UpdateAll()
{
	bool bPause = CManager::GetPause();

	for (int nCntPriority = 0; nCntPriority < OBJTYPE_MAX; nCntPriority++)
	{
		if (CManager::GetPause() == true && nCntPriority == OBJTYPE_PAUSE)
		{
			for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
			{
				if (m_apScene[nCntPriority][nCntScene] != NULL)
				{
					m_apScene[nCntPriority][nCntScene]->Update();
				}
			}
		}
		else if (CManager::GetPause() == false && nCntPriority != OBJTYPE_PAUSE)
		{
			for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
			{
				if (m_apScene[nCntPriority][nCntScene] != NULL)
				{
					m_apScene[nCntPriority][nCntScene]->Update();
				}
			}
		}
	}
}

//*****************************************************************************
// 開放処理
//*****************************************************************************
void CScene::ReleaseAll()
{
	//全てのオブジェクトの破棄
	for (int nCntPriority = 0; nCntPriority < OBJTYPE_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				m_apScene[nCntPriority][nCntScene]->Uninit();
				delete m_apScene[nCntPriority][nCntScene];
				m_apScene[nCntPriority][nCntScene] = NULL;
			}
		}
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CScene::DrawAll()
{

	//デバイスの設定
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//Zバッファの更新を無効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//カメラ情報の呼び出し
	CCamera*pCamera = CManager::GetCamera();

	//カメラ情報
	pCamera->SetCamera();

	for (int nCntPriority = 0; nCntPriority < OBJTYPE_MAX; nCntPriority++)
	{
		if (CManager::GetPause() == true)
		{
			for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
			{
				if (m_apScene[nCntPriority][nCntScene] != NULL)
				{
					m_apScene[nCntPriority][nCntScene]->Draw();
				}
			}
		}
		else if (CManager::GetPause() == false && nCntPriority != OBJTYPE_PAUSE)
		{
			for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
			{
				if (m_apScene[nCntPriority][nCntScene] != NULL)
				{
					m_apScene[nCntPriority][nCntScene]->Draw();
				}
			}
		}
	}

	//Zバッファの更新を有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CScene::Release(void)
{
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int nID = m_nID;
		int nPriority = m_nPriority;

		//インスタンスの破棄
		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;
	}
}

//*****************************************************************************
// 体力減算処理
//*****************************************************************************
void CScene::LifeSub(int nPow)
{
	m_nLife -= nPow;
}


//=============================================================================
// Sceneクラスの値
//=============================================================================
CScene * CScene::GetScene(int nCntPriority,int nCntScene)
{
	return m_apScene[nCntPriority][nCntScene];
}

//*****************************************************************************
// 種類情報処理
//*****************************************************************************
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//*****************************************************************************
// 種類の設定処理
//*****************************************************************************
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}