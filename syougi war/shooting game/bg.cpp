//=============================================================================
//
// メイン処理 [bg.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "bg.h"
#include "scene2D.h"
#include "manager.h"
#include "renderer.h"
#include "dinput_keyboard.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_BG] = {};			// テクスチャ

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CBg::CBg(int nPriority) :CScene(nPriority)
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CBg::~CBg()
{

}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CBg *CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//動的確保
	CBg* pBg;
	pBg = new CBg;

	//初期の呼び出し
	pBg->Init(pos, scale);

	//値を返す
	return pBg;
}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CBg::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//背景の切り替え
	switch (CManager::GetMode())
	{

	//ゲーム画面だった場合
	case CManager::MODE_GAME:

		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			if (m_apScene2D[nCnt] == NULL)
			{
				m_apScene2D[nCnt] = new CScene2D;
				m_apScene2D[nCnt]->Init(pos, scale);
				m_apScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);
			}
		}

		break;

		//タイトル画面だった場合
	case CManager::MODE_TITLE:

			if (m_apScene2D[0] == NULL)
			{
				m_apScene2D[0] = new CScene2D;
				m_apScene2D[0]->Init(pos, scale);
				m_apScene2D[0]->BindTexture(m_apTexture[2]);
			}

		break;

		//チュートリアル画面だった場合
	case CManager::MODE_TUTORIAL:

		if (m_apScene2D[0] == NULL)
		{
			m_apScene2D[0] = new CScene2D;
			m_apScene2D[0]->Init(pos, scale);
			m_apScene2D[0]->BindTexture(m_apTexture[4]);
		}

		break;

		//ゲーム画面だった場合
	case CManager::MODE_RESULT:

		if (m_apScene2D[0] == NULL)
		{
			m_apScene2D[0] = new CScene2D;
			m_apScene2D[0]->Init(pos, scale);
			m_apScene2D[0]->BindTexture(m_apTexture[3]);
		}

		break;

	default:
		break;
	}

	//種類
	SetObjType(OBJTYPE_BG);

	//値を返す
	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CBg::Uninit(void)
{

	//背景の切り替え
	switch (CManager::GetMode())
	{

		//ゲーム画面だった場合
	case CManager::MODE_GAME:

		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			if (m_apScene2D[nCnt] == NULL)
			{
				m_apScene2D[nCnt] = new CScene2D;
				m_apScene2D[nCnt]->Uninit();
				m_apScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);
			}
		}

		break;

		//タイトル画面だった場合
	case CManager::MODE_TITLE:

		if (m_apScene2D[0] == NULL)
		{
			m_apScene2D[0] = new CScene2D;
			m_apScene2D[0]->Uninit();
			m_apScene2D[0]->BindTexture(m_apTexture[2]);
		}

		break;

		//チュートリアル画面だった場合
	case CManager::MODE_TUTORIAL:

		if (m_apScene2D[0] == NULL)
		{
			m_apScene2D[0] = new CScene2D;
			m_apScene2D[0]->Uninit();
			m_apScene2D[0]->BindTexture(m_apTexture[4]);
		}

		break;

		//ゲーム画面だった場合
	case CManager::MODE_RESULT:

		if (m_apScene2D[0] == NULL)
		{
			m_apScene2D[0] = new CScene2D;
			m_apScene2D[0]->Uninit();
			m_apScene2D[0]->BindTexture(m_apTexture[3]);
		}

		break;

	}

	Release();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CBg::Update(void)
{
	//スクロール移動
	m_fAnim += 0.0005f;

	//背景の切り替え
	switch (CManager::GetMode())
	{

		//ゲーム画面だった場合
	case CManager::MODE_GAME:

		//更新の呼び出し
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			if (m_apScene2D[nCnt] != NULL)
			{
				//制限
				m_apScene2D[nCnt]->SetBg(m_fAnim*(nCnt + 1));
			}
		}

		break;
	}
	
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CBg::Draw(void)
{
	m_apScene2D[0]->Draw();
}

//*****************************************************************************
// テクスチャ読み込み処理
//*****************************************************************************
HRESULT CBg::Load(void)
{
	//デバイスの設定
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bg100.png", &m_apTexture[0]);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bg101.png", &m_apTexture[1]);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Titlebg.png", &m_apTexture[2]);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Resultbg.png", &m_apTexture[3]);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial.png", &m_apTexture[4]);

	return S_OK;
}

//*****************************************************************************
// テクスチャ破棄処理
//*****************************************************************************
void CBg::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		//テクスチャの開放
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}