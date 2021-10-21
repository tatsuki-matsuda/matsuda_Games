//=============================================================================
//
// メイン処理 [lifeboss.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================

#include "lifeboss.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
//LPDIRECT3DTEXTURE9 CScore::m_pTexture = NULL;			// テクスチャ


//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CLifeBoss::CLifeBoss(int nPriority) :CScene(nPriority)
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CLifeBoss::~CLifeBoss()
{

}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CLifeBoss *CLifeBoss::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, LIFETYPE lifetype)
{
	//動的確保
	CLifeBoss* pLifeBoss;
	pLifeBoss = new CLifeBoss;

	pLifeBoss->SetLifeType(lifetype);

	//初期の呼び出し
	pLifeBoss->Init(pos, scale);

	//値を返す
	return pLifeBoss;
}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CLifeBoss::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{

	//回数分ボスライフのを表示
	if (m_LifeType == LIFETYPE_BOSS)
	{
		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(pos.x + (float)(nCnt * 30), pos.y, 0.0f), scale);
		}
	}

	m_nLifeCnt = 0;

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CLifeBoss::Uninit(void)
{
	if (m_LifeType == LIFETYPE_BOSS)
	{
		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			//回数分ナンバーを破棄
			if (m_apNumber[nCnt] != NULL)
			{
				m_apNumber[nCnt]->Uninit();
				delete  m_apNumber[nCnt];
			}
		}
	}

	//開放
	CScene::Release();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CLifeBoss::Update(void)
{

}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CLifeBoss::Draw(void)
{
	//ボスのライフカウント描画
	if (m_LifeType == LIFETYPE_BOSS)
	{
		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			m_apNumber[nCnt]->Draw();
		}
	}
}

//*****************************************************************************
// ライフ表示処理
//*****************************************************************************
void CLifeBoss::SetLifeCnt(int nScore)
{

	m_nLifeCnt = nScore;

	//ボスライフカウント計算
	if (m_LifeType == LIFETYPE_BOSS)
	{
		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			int nNumber = (m_nLifeCnt / (int)powf(10.0f, (float)(1 - (nCnt + 1))));
			m_apNumber[nCnt]->SetNumber(nNumber);
		}
	}
}


//*****************************************************************************
// ボスライフカウントの処理
//*****************************************************************************
void CLifeBoss::AddBossLifeCnt(int nValue)
{
	//値を追加
	m_nLifeCnt += nValue;

	//ライフ表示の呼び出し
	SetLifeCnt(m_nLifeCnt);

}