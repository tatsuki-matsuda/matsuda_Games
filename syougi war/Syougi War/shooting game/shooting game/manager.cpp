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
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "title.h"
#include "input.h"
#include "dinput_keyboard.h"
#include "sound.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CManager::Mode CManager::m_Mode= CManager::MODE_TITLE;	// モード変数
CGame*CManager::m_pGame = NULL;							// ゲームモード変数
CResult*CManager::m_pResult = NULL;						// リザルトモード変数
CTitle*CManager::m_pTitle= NULL;						// タイトルモード変数
CTutorial*CManager::m_pTutorial = NULL;					// タイトルモード変数
CRenderer*CManager::m_pRenderer = NULL;					// レンダラー変数
CInputKeyBoard*CManager::m_pInputKeyBoard = NULL;		// 入力変数
CFade*CManager::m_pFade = NULL;							// フェード変数
int CManager::m_nSaveScore = 0;							// 保存スコア変数
bool CManager::m_bPause = false;						// ポーズ使用変数
CSound*CManager::m_pSound = NULL;						// BGM

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
	m_pRenderer->Init(hWnd, bWindow);

	//キーボードクラスの生成
	m_pInputKeyBoard = new CInputKeyBoard;
	m_pInputKeyBoard->Init(hInstance, hWnd);

	// 乱数系列の変更
	srand((unsigned)time(NULL));
	
	SetMode(m_Mode);

	CFade::Init();

	m_pSound = new CSound;
	m_pSound->InitSound(hWnd);

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

	if (m_pSound != NULL)
	{
		m_pSound->UninitSound();
		delete m_pSound;
		m_pSound = NULL;
	}

	//フェードの破棄
	CFade::Uninit();

}


//*****************************************************************************
// 更新処理
//*****************************************************************************
void CManager::Update()
{
	if (m_Mode == MODE_GAME)
	{
		if (m_pInputKeyBoard->GetTrigger(DIK_P))
		{
			SetPause();
		}
	}
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

	case MODE_TUTORIAL:
		//タイトルの終了処理
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			m_pTutorial = NULL;
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

	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
		}
		break;
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

	case MODE_TUTORIAL:

		//タイトルの初期化処理
		m_pTutorial = new CTutorial;
		m_pTutorial->Init(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
		break;

	case MODE_GAME:

		//ゲームの初期化処理
		m_pGame = new CGame;
		m_pGame->Init(D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,0));
		break;

	case MODE_RESULT:
		//リザルトの初期化処理
		m_pResult = new CResult;
		m_pResult->Init(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
		break;
	}
}

//*****************************************************************************
// ポーズ処理
//*****************************************************************************
void CManager::SetPause(void)
{
	if (m_pFade->GetFade() == CFade::FADE_NONE)
	{
		m_bPause = m_bPause ? false : true;

	}
}