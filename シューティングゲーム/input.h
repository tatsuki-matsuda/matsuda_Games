//--------------------------------------------------------------------------------
//
// �Q�[������[input.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//================================================================================
//�I�u�W�F�N�g�N���X
//================================================================================
class CInput
{

public:

	CInput();
	virtual ~CInput();
	virtual	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:

	LPDIRECTINPUTDEVICE8    m_pDevice;
	static LPDIRECTINPUT8	m_pInput;

};

#endif