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
	CInputKeyBoard();										// �R���X�g���N�^
	~CInputKeyBoard();										// �f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);			// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	bool GetPress(int nKey);								// �L�[�v���X���̌Ăяo��
	bool GetTrigger(int nKey);								// �L�[�g���K�[���̌Ăяo��
	bool GetRelase(int nKey);								// �L�[�����[�X���̌Ăяo��

private:

	BYTE m_aKeyState[256];			//�L�[���
	BYTE m_aKeyStateTrigger[256];	//�L�[�g���K�[���
	BYTE m_aKeyStateRelease[256];	//�L�[�����[�X���
	BYTE m_aKeyStateRepeat[256];	//�L�[���s�[�g���

};

#endif
