//=============================================================================
//
// メイン処理 [scene.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CScene*CScene::m_apScene[OBJTYPE_MAX][MAX_POLYGON] = {};	// ポリゴンの数
int CScene::m_nNumAll = NULL;								// 最大数

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
	for (int nCntPriority = 0; nCntPriority < OBJTYPE_MAX; nCntPriority++)
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
	for (int nCntPriority = 0; nCntPriority < OBJTYPE_MAX; nCntPriority++)
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