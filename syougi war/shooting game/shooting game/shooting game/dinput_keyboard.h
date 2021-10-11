//--------------------------------------------------------------------------------
//
// ゲーム制作[dinput_keyboard.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_

#include "input.h"

//================================================================================
//オブジェクトクラス
//================================================================================
class CInputKeyBoard :public CInput
{

public:
	CInputKeyBoard();
	~CInputKeyBoard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelase(int nKey);

private:

	BYTE m_aKeyState[256];
	BYTE m_aKeyStateTrigger[256];	//キートリガー情報
	BYTE m_aKeyStateRelease[256];	//キーリリース情報
	BYTE m_aKeyStateRepeat[256];	//キーリピート情報

};

#endif
