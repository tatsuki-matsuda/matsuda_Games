//=============================================================================
//
// メイン処理 [bg.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "game_screen.h"
#include "scene2D.h"
#include "manager.h"
#include "renderer.h"
#include "dinput_keyboard.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CGame_Screen::m_apTexture[1] = {};			// テクスチャ

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CGame_Screen::CGame_Screen(int nPriority) :CScene(nPriority)
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CGame_Screen::~CGame_Screen()
{

}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CGame_Screen *CGame_Screen::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//動的確保
	CGame_Screen* pGame_Screen;
	pGame_Screen = new CGame_Screen;

	//初期の呼び出し
	pGame_Screen->Init(pos, scale);

	//値を返す
	return pGame_Screen;
}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CGame_Screen::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{

	m_apScene2D[0] = new CScene2D(CScene::OBJTYPE_GAME);
	m_apScene2D[0]->Init(pos, scale);
	m_apScene2D[0]->BindTexture(m_apTexture[0]);

	//種類
	m_apScene2D[0]->SetObjType(OBJTYPE_GAME);

	//値を返す
	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CGame_Screen::Uninit(void)
{
	if (m_apScene2D[0] != NULL)
	{
		m_apScene2D[0]->Uninit();
		m_apScene2D[0] = NULL;
	}

	Release();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CGame_Screen::Update(void)
{
	
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CGame_Screen::Draw(void)
{
	m_apScene2D[0]->Draw();
}

//*****************************************************************************
// テクスチャ読み込み処理
//*****************************************************************************
HRESULT CGame_Screen::Load(void)
{
	//デバイスの設定
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\game_screen.png", &m_apTexture[0]);

	return S_OK;
}

//*****************************************************************************
// テクスチャ破棄処理
//*****************************************************************************
void CGame_Screen::Unload(void)
{
	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		//テクスチャの開放
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}