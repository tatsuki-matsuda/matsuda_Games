//=============================================================================
//
// ���C������ [lifeboss.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================

#include "lifeboss.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
//LPDIRECT3DTEXTURE9 CScore::m_pTexture = NULL;			// �e�N�X�`��


//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CLifeBoss::CLifeBoss(int nPriority) :CScene(nPriority)
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CLifeBoss::~CLifeBoss()
{

}

//*****************************************************************************
// ��������
//*****************************************************************************
CLifeBoss *CLifeBoss::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, LIFETYPE lifetype)
{
	//���I�m��
	CLifeBoss* pLifeBoss;
	pLifeBoss = new CLifeBoss;

	pLifeBoss->SetLifeType(lifetype);

	//�����̌Ăяo��
	pLifeBoss->Init(pos, scale);

	//�l��Ԃ�
	return pLifeBoss;
}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CLifeBoss::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{

	//�񐔕��{�X���C�t�̂�\��
	if (m_LifeType == LIFETYPE_BOSS)
	{
		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(pos.x + (float)(nCnt * 30), pos.y, 0.0f), scale);
		}
	}

	m_nLifeCnt = 0;

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CLifeBoss::Uninit(void)
{
	if (m_LifeType == LIFETYPE_BOSS)
	{
		for (int nCnt = 0; nCnt < 1; nCnt++)
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
void CLifeBoss::Update(void)
{

}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CLifeBoss::Draw(void)
{
	//�{�X�̃��C�t�J�E���g�`��
	if (m_LifeType == LIFETYPE_BOSS)
	{
		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			m_apNumber[nCnt]->Draw();
		}
	}
}

//*****************************************************************************
// ���C�t�\������
//*****************************************************************************
void CLifeBoss::SetLifeCnt(int nScore)
{

	m_nLifeCnt = nScore;

	//�{�X���C�t�J�E���g�v�Z
	if (m_LifeType == LIFETYPE_BOSS)
	{
		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			int nNumber = (m_nLifeCnt / (int)powf(10.0f, (float)(1 - (nCnt + 1))));
			m_apNumber[nCnt]->SetNumber(nNumber);
		}
	}
}


//*****************************************************************************
// �{�X���C�t�J�E���g�̏���
//*****************************************************************************
void CLifeBoss::AddBossLifeCnt(int nValue)
{
	//�l��ǉ�
	m_nLifeCnt += nValue;

	//���C�t�\���̌Ăяo��
	SetLifeCnt(m_nLifeCnt);

}