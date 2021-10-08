//=============================================================================
//
// メイン処理 [bullet.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "lifegauge.h"
#include "enemy.h"
#include "dinput_keyboard.h"
#include "player.h"
#include "score.h"
#include "game.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CLifeGauge::CLifeGauge(int nPriority) : CScene2D(nPriority)
{
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CLifeGauge::~CLifeGauge()
{

}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CLifeGauge *CLifeGauge::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int nBaseLife)
{
	//動的確保
	CLifeGauge* pLifeGauge;
	pLifeGauge = new CLifeGauge;

	//初期化処理を呼び出し
	pLifeGauge->Init(pos, scale,nBaseLife);

	return pLifeGauge;
}

//*****************************************************************************
//　初期化処理
//*****************************************************************************
HRESULT CLifeGauge::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale,int nBaseLife)
{

	CScene2D::Init(pos, scale);

	//位置の更新
	SetGaugePosition(pos, scale);

	//使われているかどうか
	m_bUninit = false;

	//ゲージが増加しているかどうか
	m_bGaugeUp = false;

	//種類
	SetObjType(OBJTYPE_UI);

	//基礎となる体力値
	m_nBaseLife = nBaseLife;

	//基礎となる大きさ
	m_BaseScale.x = GAUGEBASE_X;

	//基礎となる位置
	m_BasePos = pos;

	//現在の体力値
	m_nLife = nBaseLife;

	//間隔カウント
	m_nCntTime = 0;

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CLifeGauge::Uninit(void)
{
	//CScene2Dから呼び出し
	CScene2D::Uninit();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CLifeGauge::Update(void)
{
	//trueになるまで処理
	if (m_bGaugeUp == false)
	{
		OnGaugeUp();
	}

	//体力が0になった場合
	if (m_nLife <= 0)
	{
		//消滅
		m_bUninit = true;
	}

	//消滅した場合
	if (m_bUninit == true)
	{
		//終了処理の呼び出し
		Uninit();

		return;
	}

	//更新情報の呼び出し
	CScene2D::Update();

}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CLifeGauge::Draw(void)
{
	//描画の呼び出し
	CScene2D::Draw();
}

//*****************************************************************************
// ゲージ縮小処理
//*****************************************************************************
void CLifeGauge::OnDiffuse(int nDiffuseLife)
{
	//位置の取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//大きさの取得
	D3DXVECTOR3 scale;
	scale = GetScale();

	//体力を与えたダメージ分減らす
	m_nLife -= nDiffuseLife;

	if (m_bGaugeUp == true)
	{
		//出現時の体力値から現在の体力値を割った値
		float HpGauge = (float)m_nLife / (float)m_nBaseLife*scale.x;

		//ゲージを現在の体力値分に変換する
		scale.x = HpGauge;
	}

	//位置の更新
	SetGaugePosition(pos, scale);

	//位置の更新
	SetScale(scale);
}

//*****************************************************************************
// ゲージ増加処理
//*****************************************************************************
void CLifeGauge::OnGaugeUp(void)
{
	//位置の取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//大きさの取得
	D3DXVECTOR3 scale;
	scale = GetScale();

	//最大ゲージ量に到達するまでゲージを増加
	if (m_BaseScale.x >= scale.x)
	{
		//値を増加
		scale.x += GAUGEUP_X;

		//基礎となる体力値より現在の体力値が低い場合
		if (m_nBaseLife > m_nLife)
		{
			//現在の体力の割合
			float fRatio = (float)m_nLife / (float)m_nBaseLife;

			//体力の割合を参照し大きさに代入
			float scale_x = m_BaseScale.x * fRatio;

			if (scale.x > scale_x)
			{
				scale.x = scale_x;

			}
		}
		else if (m_BaseScale.x <= scale.x)
		{
			//現在の体力の割合
			float fRatio = (float)m_nLife / (float)m_nBaseLife;

			//体力の割合を参照し大きさに代入
			float scale_x = m_BaseScale.x * fRatio;

			scale.x = scale_x;
		}

		//位置の更新
		SetGaugePosition(pos, scale);
	}
}