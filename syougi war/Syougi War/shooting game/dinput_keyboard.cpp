//-----------------------------------------------------------------------------
//
// �Q�[������[dinput_keyboard.cpp]
// Author:Tatsuki Matsuda
//
//-----------------------------------------------------------------------------
#include "dinput_keyboard.h"

//*****************************************************************************
// 
// �L�[�{�[�h���͏��
// 
//*****************************************************************************

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CInputKeyBoard::CInputKeyBoard()
{
	memset(&m_aKeyState[0],0,sizeof(m_aKeyState));
	memset(&m_aKeyStateTrigger[0], 0, sizeof(m_aKeyStateTrigger));	//�L�[�g���K�[���
	memset(&m_aKeyStateRelease[0], 0, sizeof(m_aKeyStateRelease));	//�L�[�����[�X���
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CInputKeyBoard::~CInputKeyBoard()
{

}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CInputKeyBoard::Init(HINSTANCE hInstance, HWND hWnd)
{

	CInput::Init(hInstance,hWnd);

	//���̓f�o�C�X
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h�̐ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}

	//�A�N�Z�X���̎擾
	m_pDevice->Acquire();

	return S_OK;
}

//*****************************************************************************
// �I������
//****************************************************************************
void CInputKeyBoard::Uninit(void)
{
	CInput::Uninit();
}

//*****************************************************************************
// �X�V����
//****************************************************************************
void CInputKeyBoard::Update(void)
{
	BYTE aKeyState[256];

	//�f�o�C�X��񂩂�f�[�^���擾
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
		//�A�N�Z�X���̎擾
		m_pDevice->Acquire();
	}
}

//*****************************************************************************
// �L�[�{�[�h���̎擾
//*****************************************************************************
//�L�[���������ꍇ
bool CInputKeyBoard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//�L�[���^�b�v�����ꍇ
bool CInputKeyBoard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//�L�[�𗣂����ꍇ
bool CInputKeyBoard::GetRelase(int nKey)
{
	return(m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}