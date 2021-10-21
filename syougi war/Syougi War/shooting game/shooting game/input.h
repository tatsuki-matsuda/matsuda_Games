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

	CInput();												//�R���X�g���N�^
	virtual ~CInput();										//�f�X�g���N�^

	virtual	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//����������
	virtual void Uninit(void);								//�I������
	virtual void Update(void) = 0;							//�X�V����

protected:

	LPDIRECTINPUTDEVICE8    m_pDevice;						//�f�o�C�X���
	static LPDIRECTINPUT8	m_pInput;						//�C���v�b�g���

};

#endif