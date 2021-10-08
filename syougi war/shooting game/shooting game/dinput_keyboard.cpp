//-----------------------------------------------------------------------------
//
// ゲーム制作[dinput_keyboard.cpp]
// Author:Tatsuki Matsuda
//
//-----------------------------------------------------------------------------
#include "dinput_keyboard.h"

//*****************************************************************************
// 
// キーボード入力情報
// 
//*****************************************************************************

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CInputKeyBoard::CInputKeyBoard()
{
	memset(&m_aKeyState[0],0,sizeof(m_aKeyState));
	memset(&m_aKeyStateTrigger[0], 0, sizeof(m_aKeyStateTrigger));	//キートリガー情報
	memset(&m_aKeyStateRelease[0], 0, sizeof(m_aKeyStateRelease));	//キーリリース情報
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CInputKeyBoard::~CInputKeyBoard()
{

}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CInputKeyBoard::Init(HINSTANCE hInstance, HWND hWnd)
{

	CInput::Init(hInstance,hWnd);

	//入力デバイス
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットの設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードの設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}

	//アクセス権の取得
	m_pDevice->Acquire();

	return S_OK;
}

//*****************************************************************************
// 終了処理
//****************************************************************************
void CInputKeyBoard::Uninit(void)
{
	CInput::Uninit();
}

//*****************************************************************************
// 更新処理
//****************************************************************************
void CInputKeyBoard::Update(void)
{
	BYTE aKeyState[256];

	//デバイス情報からデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nKey = 0; nKey < 256; nKey++)
		{
			m_aKeyStateRelease[nKey] = m_aKeyState[nKey] & (~aKeyState[nKey]);
			m_aKeyStateTrigger[nKey] = ~m_aKeyState[nKey] & (aKeyState[nKey]);
			m_aKeyState[nKey] = aKeyState[nKey];
		}
	}
	else
	{
		//アクセス権の取得
		m_pDevice->Acquire();
	}
}

//*****************************************************************************
// キーボード情報の取得
//*****************************************************************************
//キーを押した場合
bool CInputKeyBoard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//キーをタップした場合
bool CInputKeyBoard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//キーを離した場合
bool CInputKeyBoard::GetRelase(int nKey)
{
	return(m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}