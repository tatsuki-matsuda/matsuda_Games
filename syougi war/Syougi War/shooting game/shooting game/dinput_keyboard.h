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
	CInputKeyBoard();										// コンストラクタ
	~CInputKeyBoard();										// デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);			// 初期化処理
	void Uninit(void);										// 終了処理
	void Update(void);										// 更新処理
	bool GetPress(int nKey);								// キープレス情報の呼び出し
	bool GetTrigger(int nKey);								// キートリガー情報の呼び出し
	bool GetRelase(int nKey);								// キーリリース情報の呼び出し

private:

	BYTE m_aKeyState[256];			//キー情報
	BYTE m_aKeyStateTrigger[256];	//キートリガー情報
	BYTE m_aKeyStateRelease[256];	//キーリリース情報
	BYTE m_aKeyStateRepeat[256];	//キーリピート情報

};

#endif
