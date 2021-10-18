//=============================================================================
//
// ���C������ [pause.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "pause.h"
#include "scene2D.h"
#include "fade.h"
#include "manager.h"
#include "renderer.h"
#include "dinput_keyboard.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPause::m_apTexture[PAUSEUI_MAX] = {};			// �e�N�X�`��

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CPause::CPause(int nPriority) :CScene(nPriority)
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CPause::~CPause()
{

}

//*****************************************************************************
// ��������
//*****************************************************************************
CPause *CPause::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//���I�m��
	CPause* pPause;
	pPause = new CPause;

	//�����̌Ăяo��
	pPause->Init(pos, scale);

	//�l��Ԃ�
	return pPause;
}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CPause::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	D3DXVECTOR3 Pos[PAUSEUI_MAX] = { D3DXVECTOR3(pos.x,pos.y,pos.z),
		D3DXVECTOR3(pos.x + 400.0f,pos.y + 140.0f,pos.z) ,
		D3DXVECTOR3(pos.x + 400.0f,pos.y + 220.0f,pos.z) ,
		D3DXVECTOR3(pos.x + 400.0f,pos.y + 290.0f,pos.z) };

	D3DXVECTOR3 Size[PAUSEUI_MAX] = { D3DXVECTOR3(scale.x,scale.y,scale.z),
		D3DXVECTOR3(300.0f,300.0f,0.0f) ,
		D3DXVECTOR3(300.0f,300.0f,0.0f) ,
		D3DXVECTOR3(300.0f,300.0f,0.0f) };


	for (int nCnt = 0; nCnt < PAUSEUI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt] == NULL)
		{
			m_apScene2D[nCnt] = new CScene2D(CScene::OBJTYPE_PAUSE);
			m_apScene2D[nCnt]->Init(Pos[nCnt], Size[nCnt]);
			m_apScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);
		}
	}

	// �|�[�Y��ʂ̔w�i�F��ς���
	m_apScene2D[PAUSEUI_NONE]->SetColor(D3DXCOLOR(0.0f,0.1f,0.3f,0.2f));

	//�I������Ă���UI�̕ۑ�
	m_nSelectCnt = (int)PAUSEUI_CONTINUE;

	//�I������UI�̐F��ݒ�
	for (int nCntPauseUI = PAUSEUI_CONTINUE; nCntPauseUI < PAUSEUI_MAX; nCntPauseUI++)
	{
		if (m_nSelectCnt == nCntPauseUI)
		{//�I�����Ă���Ƃ��̐F

			m_apScene2D[nCntPauseUI]->SetColor(D3DXCOLOR(1.0f,0.2f,0.2f,1.0f));
		}
		else
		{//�I�����Ă��Ȃ��Ƃ��̐F

			m_apScene2D[nCntPauseUI]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));

		}
	}

	m_fMove = 0.0f;

	//���
	SetObjType(OBJTYPE_PAUSE);

	//�l��Ԃ�
	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CPause::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_PAUSEUI; nCnt++)
	{
		if (m_apScene2D[nCnt] == NULL)
		{
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Uninit();
			m_apScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);
		}
	}

	Release();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CPause::Update(void)
{
	//�L�[�{�[�h���̎擾
	CInputKeyBoard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyBoard();

	//�t�F�[�h���̎擾
	CFade *pFade = CManager::GetFade();

	//�ʒu�̎擾
	D3DXVECTOR3 pos;
	pos = m_apScene2D[m_nSelectCnt]->GetPosition();

	//�ړ��̐ݒ�
	D3DXVECTOR3 move = m_apScene2D[m_nSelectCnt]->GetMove();

	
	//�I������
	if (pInputKeyboard->GetTrigger(DIK_UP) == true)
	{
		//��ɍs���Ƃ��ԍ������炷
		m_nSelectCnt--;

		if (m_nSelectCnt < PAUSEUI_CONTINUE)
		{
			//�R���e�B�j���[��菬�����Ȃ�����
			m_nSelectCnt = PAUSEUI_TITLE;
		}
	}
	else if(pInputKeyboard->GetTrigger(DIK_DOWN) == true)
	{
		//���ɍs���Ƃ��ԍ��𑝂₷
		m_nSelectCnt++;

		if (m_nSelectCnt > PAUSEUI_TITLE)
		{
			//�^�C�g�����傫���Ȃ�����
			m_nSelectCnt = PAUSEUI_CONTINUE;
		}
	}


	//�I�����̏���
	for (int nCntPause = PAUSEUI_CONTINUE; nCntPause < MAX_PAUSEUI; nCntPause++)
	{
		if (m_nSelectCnt == nCntPause)
		{
			move.x++;

			//���ݑI������Ă�����̂̐F��ς���
			m_apScene2D[nCntPause]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			//����ȊO�̓��l��ς���
			m_apScene2D[nCntPause]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputKeyboard->GetTrigger(DIK_Z) == true)
	{
		switch (m_nSelectCnt)
		{
			case PAUSEUI_CONTINUE:

				CManager::SetPause(false);

			break;

			case PAUSEUI_RETRY:

				CManager::SetPause(false);
				pFade->SetFade(CFade::FADE_OUT, CManager::MODE_GAME);

			break;

			case PAUSEUI_TITLE:

				CManager::SetPause(false);
				pFade->SetFade(CFade::FADE_OUT, CManager::MODE_TITLE);
			break;
		}
	}

	pos += move;
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CPause::Draw(void)
{
	m_apScene2D[0]->Draw();
}

//*****************************************************************************
// �e�N�X�`���ǂݍ��ݏ���
//*****************************************************************************
HRESULT CPause::Load(void)
{
	//�f�o�C�X�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\pause_bg.png", &m_apTexture[0]);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\pause_continue.png", &m_apTexture[1]);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\pause_retry.png", &m_apTexture[2]);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\pause_title.png", &m_apTexture[3]);

	return S_OK;
}

//*****************************************************************************
// �e�N�X�`���j������
//*****************************************************************************
void CPause::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_PAUSEUI; nCnt++)
	{
		//�e�N�X�`���̊J��
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}