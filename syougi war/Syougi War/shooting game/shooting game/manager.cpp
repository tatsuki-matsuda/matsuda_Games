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
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "title.h"
#include "input.h"
#include "dinput_keyboard.h"
#include "sound.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CManager::Mode CManager::m_Mode= CManager::MODE_TITLE;	// ���[�h�ϐ�
CGame*CManager::m_pGame = NULL;							// �Q�[�����[�h�ϐ�
CResult*CManager::m_pResult = NULL;						// ���U���g���[�h�ϐ�
CTitle*CManager::m_pTitle= NULL;						// �^�C�g�����[�h�ϐ�
CTutorial*CManager::m_pTutorial = NULL;					// �^�C�g�����[�h�ϐ�
CRenderer*CManager::m_pRenderer = NULL;					// �����_���[�ϐ�
CInputKeyBoard*CManager::m_pInputKeyBoard = NULL;		// ���͕ϐ�
CFade*CManager::m_pFade = NULL;							// �t�F�[�h�ϐ�
int CManager::m_nSaveScore = 0;							// �ۑ��X�R�A�ϐ�
bool CManager::m_bPause = false;						// �|�[�Y�g�p�ϐ�
CSound*CManager::m_pSound = NULL;						// BGM

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
	m_pRenderer->Init(hWnd, bWindow);

	//�L�[�{�[�h�N���X�̐���
	m_pInputKeyBoard = new CInputKeyBoard;
	m_pInputKeyBoard->Init(hInstance, hWnd);

	// �����n��̕ύX
	srand((unsigned)time(NULL));
	
	SetMode(m_Mode);

	CFade::Init();

	m_pSound = new CSound;
	m_pSound->InitSound(hWnd);

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

	if (m_pSound != NULL)
	{
		m_pSound->UninitSound();
		delete m_pSound;
		m_pSound = NULL;
	}

	//�t�F�[�h�̔j��
	CFade::Uninit();

}


//*****************************************************************************
// �X�V����
//*****************************************************************************
void CManager::Update()
{
	if (m_Mode == MODE_GAME)
	{
		if (m_pInputKeyBoard->GetTrigger(DIK_P))
		{
			SetPause();
		}
	}
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

	case MODE_TUTORIAL:
		//�^�C�g���̏I������
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			m_pTutorial = NULL;
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

	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
		}
		break;
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

	case MODE_TUTORIAL:

		//�^�C�g���̏���������
		m_pTutorial = new CTutorial;
		m_pTutorial->Init(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
		break;

	case MODE_GAME:

		//�Q�[���̏���������
		m_pGame = new CGame;
		m_pGame->Init(D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,0));
		break;

	case MODE_RESULT:
		//���U���g�̏���������
		m_pResult = new CResult;
		m_pResult->Init(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
		break;
	}
}

//*****************************************************************************
// �|�[�Y����
//*****************************************************************************
void CManager::SetPause(void)
{
	if (m_pFade->GetFade() == CFade::FADE_NONE)
	{
		m_bPause = m_bPause ? false : true;

	}
}