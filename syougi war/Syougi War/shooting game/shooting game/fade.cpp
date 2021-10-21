//=============================================================================
//
// メイン処理 [fade.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "fade.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CFade::FADE CFade::m_Fade = FADE_IN;
CPolygon*CFade::m_pPolygon = NULL;						// ポリゴン変数
CManager::Mode CFade::m_ModeNext;
D3DXCOLOR CFade::m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CFade::CFade()
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CFade::~CFade()
{

}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CFade *CFade::Create(void)
{
	//動的確保
	CFade* pFade;
	pFade = new CFade;

	//初期の呼び出し
	pFade->Init();

	//値を返す
	return pFade;
}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CFade::Init(void)
{
	//ポリゴンの生成
	m_pPolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	
	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CFade::Uninit(void)
{
	//ポリゴンの破棄
	if (m_pPolygon != NULL)
	{
		m_pPolygon->Uninit();
		m_pPolygon = NULL;
	}
	
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CFade::Update(void)
{

	if (m_Fade == FADE_IN)
	{
		m_Color.a -= 0.05f;

		if (m_Color.a <= 0.0f)
		{
			m_Fade = FADE_NONE;
		}
	}
	else if (m_Fade == FADE_OUT)
	{
		m_Color.a += 0.05f;
		if (m_Color.a >= 1.0f)
		{
			m_Fade = FADE_IN;
			
			CManager::SetMode(m_ModeNext);
		}
	}

	m_pPolygon->SetColor(m_Color);
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CFade::Draw(void)
{
	//ポリゴンの描画
	if (m_pPolygon != NULL)
	{
		m_pPolygon->Draw();

	}
}


//*****************************************************************************
// 描画処理
//*****************************************************************************
void CFade::SetFade(FADE fade, CManager::Mode modenext)
{
	//代入
	m_Fade = fade;
	m_ModeNext = modenext;
}


