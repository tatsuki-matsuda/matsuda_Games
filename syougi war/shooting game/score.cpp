//=============================================================================
//
// メイン処理 [score.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================

#include "score.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
//LPDIRECT3DTEXTURE9 CScore::m_pTexture = NULL;			// テクスチャ


//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CScore::CScore(int nPriority) :CScene(nPriority)
{
	m_nDigit = 1;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CScore::~CScore()
{

}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CScore *CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,SCORETYPE scoretype)
{
	//動的確保
	CScore* pScore;
	pScore = new CScore;

	pScore->SetScoreType(scoretype);

	//初期の呼び出し
	pScore->Init(pos, scale);

	//値を返す
	return pScore;
}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CScore::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//回数分ナンバーを表示
	if (m_ScoreType == SCORETYPE_NORMAL)
	{
		for (int nCnt = 0; nCnt < 8; nCnt++)
		{
			m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(pos.x + (float)(nCnt * 25), pos.y, 0.0f), scale);
		}
	}

	if (m_ScoreType == SCORETYPE_GRAZE)
	{
		m_nDigit = 1;

		for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
		{
			m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(pos.x + (float)(nCnt * 25), pos.y, 0.0f), scale);
		}
	}

	m_nScore = 0;

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CScore::Uninit(void)
{
	if (m_ScoreType == SCORETYPE_NORMAL)
	{
		for (int nCnt = 0; nCnt < 8; nCnt++)
		{
			//回数分ナンバーを破棄
			if (m_apNumber[nCnt] != NULL)
			{
				m_apNumber[nCnt]->Uninit();
				delete  m_apNumber[nCnt];
			}
		}
	}

	if (m_ScoreType == SCORETYPE_GRAZE)
	{
		for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
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
void CScore::Update(void)
{

}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CScore::Draw(void)
{
	//スコアを回数分描画
	if (m_ScoreType == SCORETYPE_NORMAL)
	{
		for (int nCnt = 0; nCnt < 8; nCnt++)
		{
			m_apNumber[nCnt]->Draw();
		}
	}

	//グレイズ描画
	if (m_ScoreType == SCORETYPE_GRAZE)
	{
		for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
		{
			m_apNumber[nCnt]->Draw();
		}
	}
}

//*****************************************************************************
// スコア表示処理
//*****************************************************************************
void CScore::SetScore(int nScore)
{
	//値の代入
	m_nScore = nScore;

	//スコア加算計算
	if (m_ScoreType == SCORETYPE_NORMAL)
	{
		for (int nCnt = 0; nCnt < 8; nCnt++)
		{
			int nNumber = (m_nScore / (int)powf(10.0f, (float)(8 - (nCnt + 1))));
			m_apNumber[nCnt]->SetNumber(nNumber);
		}
	}

	if (m_ScoreType == SCORETYPE_GRAZE)
	{
		for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
		{
			int nNumber = (m_nScore / (int)powf(10.0f, (float)(m_nDigit - (nCnt + 1))));
			m_apNumber[nCnt]->SetNumber(nNumber);
		}
	}
}

//*****************************************************************************
// スコアの加算処理
//*****************************************************************************
void CScore::AddScore(int nValue)
{
	//値を追加
	m_nScore += nValue;

	//スコア表示の呼び出し
	SetScore(m_nScore);
}

//*****************************************************************************
// グレイズの加算処理
//*****************************************************************************
void CScore::AddGraze(int nValue)
{
	//値を追加
	m_nScore += nValue;

	m_nDigit = 1;

	for (int nCntDigit = 1; nCntDigit < MAX_DIGIT; nCntDigit++)
	{
		int nNumber = (m_nScore / (int)powf(10.0f, (float)nCntDigit));

		if (nNumber <= 0)
		{
			break;
		}
		else
		{

			m_nDigit++;

			if (m_apNumber[m_nDigit - 1] == NULL)
			{
				//位置の取得
				D3DXVECTOR3 pos;
				pos = m_apNumber[nCntDigit - 1]->GetPosition();

				//位置の取得
				D3DXVECTOR3 scale;
				scale = m_apNumber[nCntDigit - 1]->GetScale();

				//左詰め
				m_apNumber[m_nDigit - 1] = CNumber::Create(D3DXVECTOR3(pos.x + (float)25, pos.y, 0.0f), scale);
			}
		}
	}

	//スコア表示の呼び出し
	SetScore(m_nScore);
}

//*****************************************************************************
// スコアの設定処理
//*****************************************************************************
void CScore::SetScoreType(SCORETYPE scoretype)
{
	m_ScoreType = scoretype;
}