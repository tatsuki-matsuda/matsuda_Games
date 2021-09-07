//=============================================================================
//
// メイン処理 [explosion.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "explosion.h"
#include "scene2D.h"
#include "manager.h"
#include "renderer.h"
#include "dinput_keyboard.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;			// テクスチャ

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CExplosion::CExplosion(int nPriority) :CScene2D(nPriority)
{
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nPatternAnim = 0;
	m_CounterAnim = 0;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CExplosion::~CExplosion()
{

}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//動的確保
	CExplosion* pExplosion;
	pExplosion = new CExplosion;

	//初期化を呼び出し
	pExplosion->Init(pos, scale);

	//テクスチャを呼び出し
	pExplosion->BindTexture(m_pTexture);

	//値を返す
	return pExplosion;
}

//*****************************************************************************
//　初期化処理
//*****************************************************************************
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//大きさを設定
	m_scale = scale;

	//CScene2Dを呼び出し
	CScene2D::Init(pos, scale);

	CScene2D::SetTex(m_nPatternAnim);

	//種類
	SetObjType(OBJTYPE_EXPLOSION);

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CExplosion::Update(void)
{
	//アニメーションカウンターの更新
	m_CounterAnim++;

	//アニメ―ション処理
	if (m_CounterAnim % 4 == 0)
	{
		//パターンNoの更新
		m_nPatternAnim += 1;

		//テクスチャの呼び出し
		CScene2D::SetTex(m_nPatternAnim);

		//パターンが一定数足された場合
		if (m_nPatternAnim > 7)
		{
			//アニメーションの終了
			Uninit();

		}
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}

//*****************************************************************************
// テクスチャ読み込み処理
//*****************************************************************************
HRESULT CExplosion::Load(void)
{
	//デバイスの設定
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\explosion000.png", &m_pTexture);

	return S_OK;
}

//*****************************************************************************
// テクスチャ破棄処理
//*****************************************************************************
void CExplosion::Unload(void)
{
	//テクスチャの開放
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}