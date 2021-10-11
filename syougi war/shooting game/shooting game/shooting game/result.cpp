//=============================================================================
//
// メイン処理 [result.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "game.h"
#include "fade.h"
#include "result.h"
#include "manager.h"
#include "sound.h"
#include "scene.h"
#include "renderer.h"
#include "score.h"
#include "dinput_keyboard.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CBg*CResult::m_pBg = NULL;							// 背景変数
CScore*CResult::m_pScore = NULL;					// スコア変数
CScore*CResult::m_pGraze = NULL;					// グレイズ変数

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CResult::CResult()
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CResult::~CResult()
{

}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CResult::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{

	//初期化の呼び出し
	//CScene::Init(pos, scale);

	//背景テクスチャのロード
	CBg::Load();

	//ナンバーのロード
	CNumber::Load();

	//背景クラスの生成
	m_pBg = CBg::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0));

	//ナンバークラスの生成
	CManager::GetScore();

	//ナンバークラスの生成
	m_pScore = CScore::Create(D3DXVECTOR3(250, 400, 0), D3DXVECTOR3(80, 120, 0), CScore::SCORETYPE_RESULTSCORE);

	m_pScore->SetScore(CManager::GetScore());

	//グレイズポイントの生成
	//m_pGraze = CScore::Create(D3DXVECTOR3(1000, 450, 0), D3DXVECTOR3(20, 35, 0), CScore::SCORETYPE_GRAZE);

	//サウンドのポインタ
	CSound *pSound = CManager::GetSound();

	pSound->StopSound(CSound::SOUND_LABEL_BGM000);

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CResult::Uninit(void)
{
	//背景テクスチャのアンロード
	CBg::Unload();

	//ナンバーのアンロード
	CNumber::Unload();

	Release();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CResult::Update(void)
{
	CInputKeyBoard *pKeyBoard;
	pKeyBoard = CManager::GetInputKeyBoard();

	if (pKeyBoard->GetTrigger(DIK_RETURN) == true)
	{

		CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TITLE);
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CResult::Draw(void)
{

}


//*****************************************************************************
// 背景情報処理
//*****************************************************************************
CBg*CResult::GetBg(void)
{
	return m_pBg;
}
