//=============================================================================
//
// メイン処理 [manager.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include <windows.h>
#include <time.h>
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "fade.h"
#include "game.h"
#include "title.h"
#include "input.h"
#include "dinput_keyboard.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CManager::Mode CManager::m_Mode= CManager::MODE_TITLE;	// モード変数
CGame*CManager::m_pGame = NULL;							// ゲームモード変数
CTitle*CManager::m_pTitle= NULL;						// タイトルモード変数
CRenderer*CManager::m_pRenderer = NULL;					// レンダラー変数
CInputKeyBoard*CManager::m_pInputKeyBoard = NULL;		// 入力変数

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CManager::CManager()
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CManager::~CManager()
{

}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//レンダリングクラスの生成
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, true);

	//キーボードクラスの生成
	m_pInputKeyBoard = new CInputKeyBoard;
	m_pInputKeyBoard->Init(hInstance, hWnd);

	// 乱数系列の変更
	srand((unsigned)time(NULL));
	
	SetMode(m_Mode);

	CFade::Init();

	return S_OK;

}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CManager::Uninit()
{
	//全てのオブジェクトの破棄
	CScene::ReleaseAll();

	//キーボードの破棄
	if (m_pInputKeyBoard != NULL)
	{
		m_pInputKeyBoard->Uninit();
		delete m_pInputKeyBoard;
		m_pInputKeyBoard = NULL;
	}

	//レンダリングの破棄
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//フェードの破棄
	CFade::Uninit();

}


//*****************************************************************************
// 更新処理
//*****************************************************************************
void CManager::Update()
{
	//キーボードの更新
	if (m_pInputKeyBoard != NULL)
	{
		m_pInputKeyBoard->Update();
	}

	//rendererの更新
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	CScene::UpdateAll();

	CFade::Update();
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CManager::Draw()
{
	//rendererの描画チェック
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================================================================
// Rendererクラスの値
//=============================================================================
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// キーボードクラスの値
//=============================================================================
CInputKeyBoard * CManager::GetInputKeyBoard(void)
{
	return m_pInputKeyBoard;
}

//-------------------------------------------------------------------------------
//モードの設定
//-------------------------------------------------------------------------------
void CManager::SetMode(Mode mode)
{

	switch (m_Mode)
	{

	case MODE_TITLE:
		//タイトルの終了処理
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;

	case MODE_GAME:
		//ゲームの終了処理
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;

	//case MODE_RESULT:
	//	//リザルトの終了処理
	//	UninitResult();
	//	break;

	}

	CScene::ReleaseAll();

	m_Mode = mode;

	switch (m_Mode)
	{
	

	case MODE_TITLE:

		//タイトルの初期化処理
		m_pTitle = new CTitle;
		m_pTitle->Init(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
		break;

	case MODE_GAME:

		//ゲームの初期化処理
		m_pGame = new CGame;
		m_pGame->Init(D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,0));
		break;

	//case MODE_RESULT:
	//	//リザルトの初期化処理
	//	InitResult();
	//	break;
	}
}