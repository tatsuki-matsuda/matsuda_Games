//=============================================================================
//
// メイン処理 [life.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "game.h"
#include "life.h"
#include "scene.h"
#include "scene2D.h"
#include "game.h"
#include "manager.h"
#include "score.h"
#include "renderer.h"
#include "dinput_keyboard.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CLife::m_pTexture[MAX_TEXTURE] = {};			// テクスチャ
D3DXVECTOR3 CLife::m_Craetepos[10] = {};				// 位置

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

	//テクスチャの呼び出し
	for (int nCntTex = 0; nCntTex < 1; nCntTex++)
	{
		pLife->BindTexture(m_pTexture[nCntTex]);
	}

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

	//出現経過時間
	m_nCntTime = 0;

	//アイテム出現カウント
	m_nLifeCnt = 0;

	//アイテム生成用の座標
	m_Craetepos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Craetepos[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Craetepos[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Craetepos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Craetepos[4] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Craetepos[5] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Craetepos[6] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Craetepos[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Craetepos[8] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Craetepos[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//初期化の呼び出し
	CScene2D::Init(pos, scale);

	//値を返す
	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CLife::Uninit(void)
{
	//終了の呼び出し
	CScene2D::Uninit();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CLife::Update(void)
{
	//キーボード―情報の取得
	CInputKeyBoard *pKeyboard;
	pKeyboard = CManager::GetInputKeyBoard();

	//位置の取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//スコアの取得
	CScore *pScore;
	pScore = CGame::GetScore();

	//対角線の長さ
	m_angle = sqrtf(15 * 15 + 15 * 15);

	//対角線の角度
	float fAngle = atan2f(5, 5);

	//発射時間
	m_timer++;

	if (pKeyboard->GetTrigger(DIK_U) == true)
	{

		m_nLifeCnt++;

		OnDiffuesPos(m_nLifeCnt);
	}

	//for (int nCntPriority = 0; nCntPriority < CScene::OBJTYPE_MAX; nCntPriority++)
	//{
	//	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	//	{
	//		CScene*pScene;
	//		pScene = CScene::GetScene(nCntPriority, nCntScene);

	//		if (pScene != NULL)
	//		{

	//		}
	//	}
	//}

	//移動換算
	pos += m_move;

	//位置の更新
	SetPosition(pos, m_scale);

	//大きさ
	SetScale(m_scale);
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CLife::Draw(void)
{
	//描画の呼び出し
	CScene2D::Draw();
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
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\zanki.png", &m_pTexture[0]);

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

	//位置の取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	m_nLifeCnt = nCnt;

	// Create内の情報
	// 1 pos, 2 scale

	//回転通常弾生成時の処理
	if (m_nLifeCnt == 2)
	{
		pos.x += 20;
	}

	//全方位交差弾生成時の処理
	if (m_nLifeCnt == 3)
	{
		pos.x += 40;
	}

	//全方位反射弾生成時の処理
	if (m_nLifeCnt == 4)
	{
		pos.x += 60;
	}

	//上下反射弾生成時の処理
	if (m_nLifeCnt == 5)
	{
		pos.x += 80;
	}

	//位置の更新
	SetPosition(pos, m_scale);

	//大きさ
	SetScale(m_scale);
}