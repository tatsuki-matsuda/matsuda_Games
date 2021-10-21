//=============================================================================
//
// ���C������ [bg.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "logo.h"
#include "scene2D.h"
#include "manager.h"
#include "fade.h"
#include "sound.h"
#include "renderer.h"
#include "dinput_keyboard.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CLogo::m_apTexture[MAX_LOGO] = {};			// �e�N�X�`��

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CLogo::CLogo(int nPriority) :CScene(nPriority)
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CLogo::~CLogo()
{

}

//*****************************************************************************
// ��������
//*****************************************************************************
CLogo *CLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, LOGOTYPE LogoType)
{
	//���I�m��
	CLogo* pLogo;
	pLogo = new CLogo;

	//�����̌Ăяo��
	pLogo->Init(pos, scale);

	//���S���̌Ăяo��
	pLogo->SetInfoType(LogoType);

	//�l��Ԃ�
	return pLogo;
}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CLogo::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�w�i�̐؂�ւ�
	switch (CManager::GetMode())
	{
		//�^�C�g����ʂ������ꍇ
	case CManager::MODE_TITLE:

		for (int nCnt = 0; nCnt <3; nCnt++)
		{
			if (m_apScene2D[nCnt] == NULL)
			{
				m_apScene2D[nCnt] = new CScene2D;
				m_apScene2D[nCnt]->Init(pos,scale);
				m_apScene2D[nCnt]->BindTexture(m_apTexture[m_LogoType]);
			}
		}

		break;

	//	//�`���[�g���A����ʂ������ꍇ
	//case CManager::MODE_TUTORIAL:

	//	if (m_apScene2D[0] == NULL)
	//	{
	//		m_apScene2D[0] = new CScene2D;
	//		m_apScene2D[0]->Init(pos, scale);
	//		m_apScene2D[0]->BindTexture(m_apTexture[4]);
	//	}

	//	break;

	//	//���U���g��ʂ������ꍇ
	//case CManager::MODE_RESULT:

	//	if (m_apScene2D[0] == NULL)
	//	{
	//		m_apScene2D[0] = new CScene2D;
	//		m_apScene2D[0]->Init(pos, scale);
	//		m_apScene2D[0]->BindTexture(m_apTexture[3]);
	//	}

	//	break;

	}

	//�傫��
	m_scale = scale;

	//�J���[�^�C�}�[
	m_nTimeColor = 0;

	//�^�C�}�[
	m_nTimer = 0;

	//Enter�����������ǂ���
	m_bEnter = false;

	//�Q�[����ʂɈړ��������ǂ���
	m_bGame = false;

	//�ړ��l
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���
	SetObjType(OBJTYPE_LOGO);

	//�l��Ԃ�
	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CLogo::Uninit(void)
{

	//�w�i�̐؂�ւ�
	switch (CManager::GetMode())
	{
		//�^�C�g����ʂ������ꍇ
	case CManager::MODE_TITLE:

		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			if (m_apScene2D[nCnt] == NULL)
			{
				m_apScene2D[nCnt] = new CScene2D;
				m_apScene2D[nCnt]->Uninit();
				m_apScene2D[nCnt]->BindTexture(m_apTexture[m_LogoType]);
			}
		}

		break;

	//	//�`���[�g���A����ʂ������ꍇ
	//case CManager::MODE_TUTORIAL:

	//	if (m_apScene2D[0] == NULL)
	//	{
	//		m_apScene2D[0] = new CScene2D;
	//		m_apScene2D[0]->Uninit();
	//		m_apScene2D[0]->BindTexture(m_apTexture[4]);
	//	}

	//	break;

	//	//���U���g��ʂ������ꍇ
	//case CManager::MODE_RESULT:

	//	if (m_apScene2D[0] == NULL)
	//	{
	//		m_apScene2D[0] = new CScene2D;
	//		m_apScene2D[0]->Uninit();
	//		m_apScene2D[0]->BindTexture(m_apTexture[3]);
	//	}

	//	break;

	}

	Release();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CLogo::Update(void)
{
	CInputKeyBoard *pKeyBoard;
	pKeyBoard = CManager::GetInputKeyBoard();

	//�T�E���h�̃|�C���^
	CSound *pSound = CManager::GetSound();

	//�ʒu�̎擾
	D3DXVECTOR3 pos;
	pos = m_apScene2D[0]->GetPosition();

	//�w�i�̐؂�ւ�
	switch (CManager::GetMode())
	{
		//�^�C�g����ʂ������ꍇ
	case CManager::MODE_TITLE:

		//�^�C�}�[
		m_nTimer++;

		//�F
		m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		if (m_LogoType == LOGOTYPE_START)
		{
			m_apScene2D[0]->BindTexture(m_apTexture[0]);

			//���肪true�̏ꍇ
			if (m_bEnter == true && pKeyBoard->GetTrigger(DIK_RETURN) == true)
			{
				//�Q�[����ʂɍs�����ǂ���
				m_bGame = true;

				//SE
				pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON);
			}
			else if (m_bEnter == false)
			{//���肪false�̏ꍇ

				//�G���^�[�L�[���������ꍇ
				if (pKeyBoard->GetTrigger(DIK_RETURN) == true)
				{
					//�����true�ɕς���
					m_bEnter = true;

					m_nTimeColor = 0;

				}
			}

			//���肪true�̏ꍇ
			if (m_bEnter == true && m_bGame == true)
			{
				m_nTimeColor++;

				

				//�J�E���g��5�Ŋ����0�ɂȂ�ꍇ
				if (m_nTimeColor % 5 == 0)
				{
					//�F
					m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
				else
				{
					//�F
					m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
				}

				//�J�E���g��50�𒴂����ꍇ
				if (m_nTimeColor >= 50)
				{
					//�t�F�[�h
					CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TUTORIAL);

					//�����false�ɕς���
					m_bEnter = false;

					//�����false�ɕς���
					m_bGame = false;

					//�^�C�}�[��0�ɂ���
					m_nTimer = 0;
				}
			}

			//�ʒu�������������ʒu�ɂ��邩���肪false�̏ꍇ
			if (pos.y > 470.0f && m_bEnter == false)
			{
				//�ړ��l
				m_move.y = -8.0f;
			}
			else
			{
				//�ʒu��^����
				pos.y = 470.0f;

				//�ړ��l
				m_move.y = 0.0f;

				//�G���^�[�����������ǂ���
				m_bEnter = true;
			}
		}

		if (m_LogoType == LOGOTYPE_KYOUSYA)
		{
			m_apScene2D[0]->BindTexture(m_apTexture[1]);

			//���肪true�̏ꍇ
			if (m_bEnter == true && pKeyBoard->GetTrigger(DIK_RETURN) == true)
			{
				m_bGame = true;
			}

			if (m_bGame == true)
			{
				//�ړ��l
				m_move.y = -12.0f;
			}
			//�ʒu�������������ʒu�ɂ��邩���肪false�̏ꍇ
			if (pos.y > 475.0f)
			{
				//�ړ��l
				m_move.y = -8.0f;
			}
			else if(m_bGame == false)
			{
				//�ʒu��^����
				pos.y = 475.0f;

				m_bEnter = true;
			}
		}

		break;
	}

	//�ړ��l���ʒu���W�ɑ���
	pos += m_move;

	//�ʒu����^����
	m_apScene2D[0]->SetPosition(pos, m_scale);

	//�F
	m_apScene2D[0]->SetColor(m_Color);

}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CLogo::Draw(void)
{
}

//*****************************************************************************
// �e�N�X�`���ǂݍ��ݏ���
//*****************************************************************************
HRESULT CLogo::Load(void)
{
	//�f�o�C�X�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\StartLogo.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy_Kasya.png", &m_apTexture[1]);

	return S_OK;
}

//*****************************************************************************
// �e�N�X�`���j������
//*****************************************************************************
void CLogo::Unload(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_LOGO; nCnt++)
	{
		//�e�N�X�`���̊J��
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}