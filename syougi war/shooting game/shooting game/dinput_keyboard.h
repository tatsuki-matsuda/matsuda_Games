//--------------------------------------------------------------------------------
//
// �Q�[������[dinput_keyboard.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_

#include "input.h"

//================================================================================
//�I�u�W�F�N�g�N���X
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
	BYTE m_aKeyStateTrigger[256];	//�L�[�g���K�[���
	BYTE m_aKeyStateRelease[256];	//�L�[�����[�X���
	BYTE m_aKeyStateRepeat[256];	//�L�[���s�[�g���

};

#endif
