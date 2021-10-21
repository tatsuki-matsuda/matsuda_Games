//=============================================================================
//
// ���C������ [bullet.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "lifegauge.h"
#include "enemy.h"
#include "dinput_keyboard.h"
#include "player.h"
#include "score.h"
#include "game.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CLifeGauge::CLifeGauge(int nPriority) : CScene2D(nPriority)
{
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CLifeGauge::~CLifeGauge()
{

}

//*****************************************************************************
// ��������
//*****************************************************************************
CLifeGauge *CLifeGauge::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int nBaseLife)
{
	//���I�m��
	CLifeGauge* pLifeGauge;
	pLifeGauge = new CLifeGauge;

	//�������������Ăяo��
	pLifeGauge->Init(pos, scale,nBaseLife);

	return pLifeGauge;
}

//*****************************************************************************
//�@����������
//*****************************************************************************
HRESULT CLifeGauge::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale,int nBaseLife)
{

	CScene2D::Init(pos, scale);

	//�ʒu�̍X�V
	SetGaugePosition(pos, scale);

	//�g���Ă��邩�ǂ���
	m_bUninit = false;

	//�Q�[�W���������Ă��邩�ǂ���
	m_bGaugeUp = false;

	//���
	SetObjType(OBJTYPE_UI);

	//��b�ƂȂ�̗͒l
	m_nBaseLife = nBaseLife;

	//��b�ƂȂ�傫��
	m_BaseScale.x = GAUGEBASE_X;

	//��b�ƂȂ�ʒu
	m_BasePos = pos;

	//���݂̗̑͒l
	m_nLife = nBaseLife;

	//�Ԋu�J�E���g
	m_nCntTime = 0;

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CLifeGauge::Uninit(void)
{
	//CScene2D����Ăяo��
	CScene2D::Uninit();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CLifeGauge::Update(void)
{
	//true�ɂȂ�܂ŏ���
	if (m_bGaugeUp == false)
	{
		OnGaugeUp();
	}

	//�̗͂�0�ɂȂ����ꍇ
	if (m_nLife <= 0)
	{
		//����
		m_bUninit = true;
	}

	//���ł����ꍇ
	if (m_bUninit == true)
	{
		//�I�������̌Ăяo��
		Uninit();

		return;
	}

	//�X�V���̌Ăяo��
	CScene2D::Update();

}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CLifeGauge::Draw(void)
{
	//�`��̌Ăяo��
	CScene2D::Draw();
}

//*****************************************************************************
// �Q�[�W�k������
//*****************************************************************************
void CLifeGauge::OnDiffuse(int nDiffuseLife)
{
	//�ʒu�̎擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//�傫���̎擾
	D3DXVECTOR3 scale;
	scale = GetScale();

	//�̗͂�^�����_���[�W�����炷
	m_nLife -= nDiffuseLife;

	if (m_bGaugeUp == true)
	{
		//�o�����̗̑͒l���猻�݂̗̑͒l���������l
		float HpGauge = (float)m_nLife / (float)m_nBaseLife*scale.x;

		//�Q�[�W�����݂̗̑͒l���ɕϊ�����
		scale.x = HpGauge;
	}

	//�ʒu�̍X�V
	SetGaugePosition(pos, scale);

	//�ʒu�̍X�V
	SetScale(scale);
}

//*****************************************************************************
// �Q�[�W��������
//*****************************************************************************
void CLifeGauge::OnGaugeUp(void)
{
	//�ʒu�̎擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//�傫���̎擾
	D3DXVECTOR3 scale;
	scale = GetScale();

	//�ő�Q�[�W�ʂɓ��B����܂ŃQ�[�W�𑝉�
	if (m_BaseScale.x >= scale.x)
	{
		//�l�𑝉�
		scale.x += GAUGEUP_X;

		//��b�ƂȂ�̗͒l��茻�݂̗̑͒l���Ⴂ�ꍇ
		if (m_nBaseLife > m_nLife)
		{
			//���݂̗̑͂̊���
			float fRatio = (float)m_nLife / (float)m_nBaseLife;

			//�̗͂̊������Q�Ƃ��傫���ɑ��
			float scale_x = m_BaseScale.x * fRatio;

			if (scale.x > scale_x)
			{
				scale.x = scale_x;

			}
		}
		else if (m_BaseScale.x <= scale.x)
		{
			//���݂̗̑͂̊���
			float fRatio = (float)m_nLife / (float)m_nBaseLife;

			//�̗͂̊������Q�Ƃ��傫���ɑ��
			float scale_x = m_BaseScale.x * fRatio;

			scale.x = scale_x;
		}

		//�ʒu�̍X�V
		SetGaugePosition(pos, scale);
	}
}