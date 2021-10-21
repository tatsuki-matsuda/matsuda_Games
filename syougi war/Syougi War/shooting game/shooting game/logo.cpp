//=============================================================================
//
// メイン処理 [bg.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "logo.h"
#include "scene2D.h"
#include "manager.h"
#include "fade.h"
#include "sound.h"
#include "renderer.h"
#include "dinput_keyboard.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CLogo::m_apTexture[MAX_LOGO] = {};			// テクスチャ

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CLogo::CLogo(int nPriority) :CScene(nPriority)
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CLogo::~CLogo()
{

}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CLogo *CLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, LOGOTYPE LogoType)
{
	//動的確保
	CLogo* pLogo;
	pLogo = new CLogo;

	//初期の呼び出し
	pLogo->Init(pos, scale);

	//ロゴ情報の呼び出し
	pLogo->SetInfoType(LogoType);

	//値を返す
	return pLogo;
}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CLogo::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//背景の切り替え
	switch (CManager::GetMode())
	{
		//タイトル画面だった場合
	case CManager::MODE_TITLE:

		for (int nCnt = 0; nCnt <3; nCnt++)
		{
			if (m_apScene2D[nCnt] == NULL)
			{
				m_apScene2D[nCnt] = new CScene2D;
				m_apScene2D[nCnt]->Init(pos,scale);
				m_apScene2D[nCnt]->BindTexture(m_apTexture[m_LogoType]);
			}
		}

		break;

	//	//チュートリアル画面だった場合
	//case CManager::MODE_TUTORIAL:

	//	if (m_apScene2D[0] == NULL)
	//	{
	//		m_apScene2D[0] = new CScene2D;
	//		m_apScene2D[0]->Init(pos, scale);
	//		m_apScene2D[0]->BindTexture(m_apTexture[4]);
	//	}

	//	break;

	//	//リザルト画面だった場合
	//case CManager::MODE_RESULT:

	//	if (m_apScene2D[0] == NULL)
	//	{
	//		m_apScene2D[0] = new CScene2D;
	//		m_apScene2D[0]->Init(pos, scale);
	//		m_apScene2D[0]->BindTexture(m_apTexture[3]);
	//	}

	//	break;

	}

	//大きさ
	m_scale = scale;

	//カラータイマー
	m_nTimeColor = 0;

	//タイマー
	m_nTimer = 0;

	//Enterを押したかどうか
	m_bEnter = false;

	//ゲーム画面に移動したかどうか
	m_bGame = false;

	//移動値
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//種類
	SetObjType(OBJTYPE_LOGO);

	//値を返す
	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CLogo::Uninit(void)
{

	//背景の切り替え
	switch (CManager::GetMode())
	{
		//タイトル画面だった場合
	case CManager::MODE_TITLE:

		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			if (m_apScene2D[nCnt] == NULL)
			{
				m_apScene2D[nCnt] = new CScene2D;
				m_apScene2D[nCnt]->Uninit();
				m_apScene2D[nCnt]->BindTexture(m_apTexture[m_LogoType]);
			}
		}

		break;

	//	//チュートリアル画面だった場合
	//case CManager::MODE_TUTORIAL:

	//	if (m_apScene2D[0] == NULL)
	//	{
	//		m_apScene2D[0] = new CScene2D;
	//		m_apScene2D[0]->Uninit();
	//		m_apScene2D[0]->BindTexture(m_apTexture[4]);
	//	}

	//	break;

	//	//リザルト画面だった場合
	//case CManager::MODE_RESULT:

	//	if (m_apScene2D[0] == NULL)
	//	{
	//		m_apScene2D[0] = new CScene2D;
	//		m_apScene2D[0]->Uninit();
	//		m_apScene2D[0]->BindTexture(m_apTexture[3]);
	//	}

	//	break;

	}

	Release();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CLogo::Update(void)
{
	CInputKeyBoard *pKeyBoard;
	pKeyBoard = CManager::GetInputKeyBoard();

	//サウンドのポインタ
	CSound *pSound = CManager::GetSound();

	//位置の取得
	D3DXVECTOR3 pos;
	pos = m_apScene2D[0]->GetPosition();

	//背景の切り替え
	switch (CManager::GetMode())
	{
		//タイトル画面だった場合
	case CManager::MODE_TITLE:

		//タイマー
		m_nTimer++;

		//色
		m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		if (m_LogoType == LOGOTYPE_START)
		{
			m_apScene2D[0]->BindTexture(m_apTexture[0]);

			//判定がtrueの場合
			if (m_bEnter == true && pKeyBoard->GetTrigger(DIK_RETURN) == true)
			{
				//ゲーム画面に行くかどうか
				m_bGame = true;

				//SE
				pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON);
			}
			else if (m_bEnter == false)
			{//判定がfalseの場合

				//エンターキーを押した場合
				if (pKeyBoard->GetTrigger(DIK_RETURN) == true)
				{
					//判定をtrueに変える
					m_bEnter = true;

					m_nTimeColor = 0;

				}
			}

			//判定がtrueの場合
			if (m_bEnter == true && m_bGame == true)
			{
				m_nTimeColor++;

				

				//カウントが5で割ると0になる場合
				if (m_nTimeColor % 5 == 0)
				{
					//色
					m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
				else
				{
					//色
					m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
				}

				//カウントが50を超えた場合
				if (m_nTimeColor >= 50)
				{
					//フェード
					CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TUTORIAL);

					//判定をfalseに変える
					m_bEnter = false;

					//判定をfalseに変える
					m_bGame = false;

					//タイマーを0にする
					m_nTimer = 0;
				}
			}

			//位置が一定よりも高い位置にあるかつ判定がfalseの場合
			if (pos.y > 470.0f && m_bEnter == false)
			{
				//移動値
				m_move.y = -8.0f;
			}
			else
			{
				//位置を与える
				pos.y = 470.0f;

				//移動値
				m_move.y = 0.0f;

				//エンターを押したかどうか
				m_bEnter = true;
			}
		}

		if (m_LogoType == LOGOTYPE_KYOUSYA)
		{
			m_apScene2D[0]->BindTexture(m_apTexture[1]);

			//判定がtrueの場合
			if (m_bEnter == true && pKeyBoard->GetTrigger(DIK_RETURN) == true)
			{
				m_bGame = true;
			}

			if (m_bGame == true)
			{
				//移動値
				m_move.y = -12.0f;
			}
			//位置が一定よりも高い位置にあるかつ判定がfalseの場合
			if (pos.y > 475.0f)
			{
				//移動値
				m_move.y = -8.0f;
			}
			else if(m_bGame == false)
			{
				//位置を与える
				pos.y = 475.0f;

				m_bEnter = true;
			}
		}

		break;
	}

	//移動値を位置座標に足す
	pos += m_move;

	//位置情報を与える
	m_apScene2D[0]->SetPosition(pos, m_scale);

	//色
	m_apScene2D[0]->SetColor(m_Color);

}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CLogo::Draw(void)
{
}

//*****************************************************************************
// テクスチャ読み込み処理
//*****************************************************************************
HRESULT CLogo::Load(void)
{
	//デバイスの設定
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\StartLogo.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy_Kasya.png", &m_apTexture[1]);

	return S_OK;
}

//*****************************************************************************
// テクスチャ破棄処理
//*****************************************************************************
void CLogo::Unload(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < MAX_LOGO; nCnt++)
	{
		//テクスチャの開放
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}