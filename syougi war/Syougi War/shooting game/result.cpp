//=============================================================================
//
// ���C������ [result.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "game.h"
#include "fade.h"
#include "result.h"
#include "manager.h"
#include "sound.h"
#include "scene.h"
#include "renderer.h"
#include "score.h"
#include "dinput_keyboard.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CBg*CResult::m_pBg = NULL;							// �w�i�ϐ�
CScore*CResult::m_pScore = NULL;					// �X�R�A�ϐ�
CScore*CResult::m_pGraze = NULL;					// �O���C�Y�ϐ�

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CResult::CResult()
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CResult::~CResult()
{

}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CResult::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{

	//�������̌Ăяo��
	//CScene::Init(pos, scale);

	//�w�i�e�N�X�`���̃��[�h
	CBg::Load();

	//�i���o�[�̃��[�h
	CNumber::Load();

	//�w�i�N���X�̐���
	m_pBg = CBg::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0));

	//�i���o�[�N���X�̐���
	CManager::GetScore();

	//�i���o�[�N���X�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(250, 400, 0), D3DXVECTOR3(80, 120, 0), CScore::SCORETYPE_RESULTSCORE);

	m_pScore->SetScore(CManager::GetScore());

	//�O���C�Y�|�C���g�̐���
	//m_pGraze = CScore::Create(D3DXVECTOR3(1000, 450, 0), D3DXVECTOR3(20, 35, 0), CScore::SCORETYPE_GRAZE);

	//�T�E���h�̃|�C���^
	CSound *pSound = CManager::GetSound();

	pSound->StopSound(CSound::SOUND_LABEL_BGM000);

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CResult::Uninit(void)
{
	//�w�i�e�N�X�`���̃A�����[�h
	CBg::Unload();

	//�i���o�[�̃A�����[�h
	CNumber::Unload();

	Release();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CResult::Update(void)
{
	CInputKeyBoard *pKeyBoard;
	pKeyBoard = CManager::GetInputKeyBoard();

	if (pKeyBoard->GetTrigger(DIK_RETURN) == true)
	{

		CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TITLE);
	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CResult::Draw(void)
{

}


//*****************************************************************************
// �w�i��񏈗�
//*****************************************************************************
CBg*CResult::GetBg(void)
{
	return m_pBg;
}
