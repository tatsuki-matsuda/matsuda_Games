//--------------------------------------------------------------------------------
//
// �Q�[������[input.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"

//--------------------------------------------------------------------------------
//�v���g�^�C�v�錾
//--------------------------------------------------------------------------------
HRESULT InitKeyBoard(HINSTANCE hInstance, HWND hWnd);
void UnInitKeyBoard(void);
void UpdateKeyBoard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRelase(int nKey);
#endif