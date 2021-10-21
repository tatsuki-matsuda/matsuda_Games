//=============================================================================
//
// メイン処理 [life.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "fade.h"
#include "life.h"
#include "player.h"
#include "scene.h"
#include "scene2D.h"
#include "manager.h"
#include "score.h"
#include "renderer.h"
#include "game.h"
#include "dinput_keyboard.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CLife::m_pTexture[MAX_TEXTURE] = {};			// テクスチャ
D3DXVECTOR3 CLife::m_Craetepos[5] = {};							// 位置

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CLife::CLife(int nPriority) :CScene2D(nPriority)
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CLife::~CLife()
{

}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CLife *CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//動的確保
	CLife* pLife;
	pLife= new CLife;

	//初期の呼び出し
	pLife->Init(pos, scale);

	//値を返す
	return pLife;

}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CLife::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//大きさを設定
	m_scale = scale;

	//種類
	SetObjType(OBJTYPE_UI);

	//つかわれてるかどうか
	m_bUninit = false;

	//経過時間
	m_nCntTime = 0;

	//残機の個数
	m_nLife = MAX_PLAYERLIFE;

	//読み込み呼び出し
	Load();

	//残機分テクスチャを生成
	for (int nCnt = 0; nCnt < m_nLife; nCnt++)
	{
		if (m_apScene2D[nCnt] == NULL)
		{
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Init(D3DXVECTOR3(pos.x + 50.0f * nCnt,pos.y,pos.z), scale);
			m_apScene2D[nCnt]->BindTexture(m_pTexture[0]);
		}
	}

	//値を返す
	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CLife::Uninit(void)
{
	//終了の呼び出し
	for (int nCnt = 0; nCnt < m_nLife; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Uninit();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[0]);
		}
	}
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CLife::Update(void)
{
	//キーボード―情報の取得
	CInputKeyBoard *pKeyboard;
	pKeyboard = CManager::GetInputKeyBoard();

	//スコアの取得
	CScore *pScore;
	pScore = CGame::GetScore();

	//対角線の長さ
	m_angle = sqrtf(15 * 15 + 15 * 15);

	//対角線の角度
	float fAngle = atan2f(5, 5);

	for (int nCntLife = 0; nCntLife < m_nLife; nCntLife++)
	{
		if (m_apScene2D[nCntLife] != NULL)
		{
			m_apScene2D[nCntLife]->Update();
		}
	}

	// 遷移するかどうか
	if (m_nLife == 0)
	{
		m_nCntTime++;

		if (m_nCntTime > 120)
		{
			CGame::SetTransition(CGame::TRANSITION_RESULT);
		}
		
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CLife::Draw(void)
{
	//描画の呼び出し
	for (int nCntLife = 0; nCntLife < m_nLife; nCntLife++)
	{
		if (m_apScene2D[nCntLife] != NULL)
		{
			m_apScene2D[nCntLife]->Draw();
		}
	}
}

//*****************************************************************************
// テクスチャ読み込み処理
//*****************************************************************************
HRESULT CLife::Load(void)
{
	//デバイスの設定
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\player001.png", &m_pTexture[0]);

	return S_OK;
}

//*****************************************************************************
//*****************************************************************************
// テクスチャ破棄処理
void CLife::Unload(void)
{
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		//テクスチャの開放
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}

//*****************************************************************************
// アイテムの位置生成処理
//*****************************************************************************
void CLife::OnDiffuesPos(int nCnt)
{

}