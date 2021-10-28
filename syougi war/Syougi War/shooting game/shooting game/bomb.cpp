//=============================================================================
//
// メイン処理 [life.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "fade.h"
#include "bomb.h"
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
LPDIRECT3DTEXTURE9 CBomb::m_pTexture[MAX_TEXTURE] = {};			// テクスチャ
D3DXVECTOR3 CBomb::m_Craetepos[5] = {};							// 位置

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CBomb::CBomb(int nPriority) :CScene2D(nPriority)
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CBomb::~CBomb()
{

}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CBomb *CBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//動的確保
	CBomb* pBomb;
	pBomb = new CBomb;

	//初期の呼び出し
	pBomb->Init(pos, scale);

	//値を返す
	return pBomb;

}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//大きさを設定
	m_scale = scale;

	//種類
	SetObjType(OBJTYPE_UI);

	//つかわれてるかどうか
	m_bUninit = false;

	//経過時間
	m_nCntTime = 0;

	//ボムの個数
	m_nBomb = MAX_PLAYERBOMB;

	//読み込み呼び出し
	Load();

	//ボムの数分生成
	for (int nCnt = 0; nCnt < m_nBomb; nCnt++)
	{
		if (m_apScene2D[nCnt] == NULL)
		{
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Init(D3DXVECTOR3(pos.x + 50.0f * nCnt, pos.y, pos.z), scale);
			m_apScene2D[nCnt]->BindTexture(m_pTexture[0]);
		}
	}

	//値を返す
	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CBomb::Uninit(void)
{
	//終了の呼び出し
	for (int nCnt = 0; nCnt < m_nBomb; nCnt++)
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
void CBomb::Update(void)
{
	//キーボード―情報の取得
	CInputKeyBoard *pKeyboard;
	pKeyboard = CManager::GetInputKeyBoard();

	//スコアの取得
	CScore *pScore;
	pScore = CGame::GetScore();


	for (int nCntBomb = 0; nCntBomb < m_nBomb; nCntBomb++)
	{
		if (m_apScene2D[nCntBomb] != NULL)
		{
			m_apScene2D[nCntBomb]->Update();
		}
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CBomb::Draw(void)
{
	//描画の呼び出し
	for (int nCntLife = 0; nCntLife < m_nBomb; nCntLife++)
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
HRESULT CBomb::Load(void)
{
	//デバイスの設定
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Bomb_Item.png", &m_pTexture[0]);

	return S_OK;
}

//*****************************************************************************
// テクスチャ破棄処理
//*****************************************************************************
void CBomb::Unload(void)
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
void CBomb::OnDiffuesPos(int nCnt)
{

}