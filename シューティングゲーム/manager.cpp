//=============================================================================
//
// ���C������ [manager.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include <windows.h>
#include <time.h>
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "fade.h"
#include "game.h"
#include "title.h"
#include "input.h"
#include "dinput_keyboard.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CManager::Mode CManager::m_Mode= CManager::MODE_TITLE;	// ���[�h�ϐ�
CGame*CManager::m_pGame = NULL;							// �Q�[�����[�h�ϐ�
CTitle*CManager::m_pTitle= NULL;						// �^�C�g�����[�h�ϐ�
CRenderer*CManager::m_pRenderer = NULL;					// �����_���[�ϐ�
CInputKeyBoard*CManager::m_pInputKeyBoard = NULL;		// ���͕ϐ�

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CManager::CManager()
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CManager::~CManager()
{

}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�����_�����O�N���X�̐���
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, true);

	//�L�[�{�[�h�N���X�̐���
	m_pInputKeyBoard = new CInputKeyBoard;
	m_pInputKeyBoard->Init(hInstance, hWnd);

	// �����n��̕ύX
	srand((unsigned)time(NULL));
	
	SetMode(m_Mode);

	CFade::Init();

	return S_OK;

}

//*****************************************************************************
// �I������
//*****************************************************************************
void CManager::Uninit()
{
	//�S�ẴI�u�W�F�N�g�̔j��
	CScene::ReleaseAll();

	//�L�[�{�[�h�̔j��
	if (m_pInputKeyBoard != NULL)
	{
		m_pInputKeyBoard->Uninit();
		delete m_pInputKeyBoard;
		m_pInputKeyBoard = NULL;
	}

	//�����_�����O�̔j��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//�t�F�[�h�̔j��
	CFade::Uninit();

}


//*****************************************************************************
// �X�V����
//*****************************************************************************
void CManager::Update()
{
	//�L�[�{�[�h�̍X�V
	if (m_pInputKeyBoard != NULL)
	{
		m_pInputKeyBoard->Update();
	}

	//renderer�̍X�V
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	CScene::UpdateAll();

	CFade::Update();
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CManager::Draw()
{
	//renderer�̕`��`�F�b�N
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================================================================
// Renderer�N���X�̒l
//=============================================================================
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// �L�[�{�[�h�N���X�̒l
//=============================================================================
CInputKeyBoard * CManager::GetInputKeyBoard(void)
{
	return m_pInputKeyBoard;
}

//-------------------------------------------------------------------------------
//���[�h�̐ݒ�
//-------------------------------------------------------------------------------
void CManager::SetMode(Mode mode)
{

	switch (m_Mode)
	{

	case MODE_TITLE:
		//�^�C�g���̏I������
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;

	case MODE_GAME:
		//�Q�[���̏I������
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;

	//case MODE_RESULT:
	//	//���U���g�̏I������
	//	UninitResult();
	//	break;

	}

	CScene::ReleaseAll();

	m_Mode = mode;

	switch (m_Mode)
	{
	

	case MODE_TITLE:

		//�^�C�g���̏���������
		m_pTitle = new CTitle;
		m_pTitle->Init(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
		break;

	case MODE_GAME:

		//�Q�[���̏���������
		m_pGame = new CGame;
		m_pGame->Init(D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,0));
		break;

	//case MODE_RESULT:
	//	//���U���g�̏���������
	//	InitResult();
	//	break;
	}
}