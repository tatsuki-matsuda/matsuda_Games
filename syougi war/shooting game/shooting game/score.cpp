//=============================================================================
//
// ���C������ [score.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================

#include "score.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
//LPDIRECT3DTEXTURE9 CScore::m_pTexture = NULL;			// �e�N�X�`��


//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CScore::CScore(int nPriority) :CScene(nPriority)
{
	m_nDigit = 1;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CScore::~CScore()
{

}

//*****************************************************************************
// ��������
//*****************************************************************************
CScore *CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,SCORETYPE scoretype)
{
	//���I�m��
	CScore* pScore;
	pScore = new CScore;

	pScore->SetScoreType(scoretype);

	//�����̌Ăяo��
	pScore->Init(pos, scale);

	//�l��Ԃ�
	return pScore;
}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CScore::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�񐔕��i���o�[��\��
	if (m_ScoreType == SCORETYPE_NORMAL)
	{
		for (int nCnt = 0; nCnt < 8; nCnt++)
		{
			m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(pos.x + (float)(nCnt * 25), pos.y, 0.0f), scale);
		}
	}

	if (m_ScoreType == SCORETYPE_GRAZE)
	{
		m_nDigit = 1;

		for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
		{
			m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(pos.x + (float)(nCnt * 25), pos.y, 0.0f), scale);
		}
	}

	m_nScore = 0;

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CScore::Uninit(void)
{
	if (m_ScoreType == SCORETYPE_NORMAL)
	{
		for (int nCnt = 0; nCnt < 8; nCnt++)
		{
			//�񐔕��i���o�[��j��
			if (m_apNumber[nCnt] != NULL)
			{
				m_apNumber[nCnt]->Uninit();
				delete  m_apNumber[nCnt];
			}
		}
	}

	if (m_ScoreType == SCORETYPE_GRAZE)
	{
		for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
		{
			//�񐔕��i���o�[��j��
			if (m_apNumber[nCnt] != NULL)
			{
				m_apNumber[nCnt]->Uninit();
				delete  m_apNumber[nCnt];
			}
		}
	}

	//�J��
	CScene::Release();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CScore::Update(void)
{

}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CScore::Draw(void)
{
	//�X�R�A���񐔕��`��
	if (m_ScoreType == SCORETYPE_NORMAL)
	{
		for (int nCnt = 0; nCnt < 8; nCnt++)
		{
			m_apNumber[nCnt]->Draw();
		}
	}

	//�O���C�Y�`��
	if (m_ScoreType == SCORETYPE_GRAZE)
	{
		for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
		{
			m_apNumber[nCnt]->Draw();
		}
	}
}

//*****************************************************************************
// �X�R�A�\������
//*****************************************************************************
void CScore::SetScore(int nScore)
{
	//�l�̑��
	m_nScore = nScore;

	//�X�R�A���Z�v�Z
	if (m_ScoreType == SCORETYPE_NORMAL)
	{
		for (int nCnt = 0; nCnt < 8; nCnt++)
		{
			int nNumber = (m_nScore / (int)powf(10.0f, (float)(8 - (nCnt + 1))));
			m_apNumber[nCnt]->SetNumber(nNumber);
		}
	}

	if (m_ScoreType == SCORETYPE_GRAZE)
	{
		for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
		{
			int nNumber = (m_nScore / (int)powf(10.0f, (float)(m_nDigit - (nCnt + 1))));
			m_apNumber[nCnt]->SetNumber(nNumber);
		}
	}
}

//*****************************************************************************
// �X�R�A�̉��Z����
//*****************************************************************************
void CScore::AddScore(int nValue)
{
	//�l��ǉ�
	m_nScore += nValue;

	//�X�R�A�\���̌Ăяo��
	SetScore(m_nScore);
}

//*****************************************************************************
// �O���C�Y�̉��Z����
//*****************************************************************************
void CScore::AddGraze(int nValue)
{
	//�l��ǉ�
	m_nScore += nValue;

	m_nDigit = 1;

	for (int nCntDigit = 1; nCntDigit < MAX_DIGIT; nCntDigit++)
	{
		int nNumber = (m_nScore / (int)powf(10.0f, (float)nCntDigit));

		if (nNumber <= 0)
		{
			break;
		}
		else
		{

			m_nDigit++;

			if (m_apNumber[m_nDigit - 1] == NULL)
			{
				//�ʒu�̎擾
				D3DXVECTOR3 pos;
				pos = m_apNumber[nCntDigit - 1]->GetPosition();

				//�ʒu�̎擾
				D3DXVECTOR3 scale;
				scale = m_apNumber[nCntDigit - 1]->GetScale();

				//���l��
				m_apNumber[m_nDigit - 1] = CNumber::Create(D3DXVECTOR3(pos.x + (float)25, pos.y, 0.0f), scale);
			}
		}
	}

	//�X�R�A�\���̌Ăяo��
	SetScore(m_nScore);
}

//*****************************************************************************
// �X�R�A�̐ݒ菈��
//*****************************************************************************
void CScore::SetScoreType(SCORETYPE scoretype)
{
	m_ScoreType = scoretype;
}