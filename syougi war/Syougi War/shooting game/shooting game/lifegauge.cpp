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
#include "manager.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CLifeGauge::m_pTexture = NULL;			// �e�N�X�`��

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CLifeGauge::CLifeGauge(int nPriority)
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
	pLifeGauge = new CLifeGauge();

	//�̗͒l���̌Ăяo��
	pLifeGauge->SetBaseLife(nBaseLife);

	//�������������Ăяo��
	pLifeGauge->Init(pos, scale);

	//�l��Ԃ�
	return pLifeGauge;
}

//*****************************************************************************
//�@����������
//*****************************************************************************
HRESULT CLifeGauge::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�f�o�C�X�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�ʒu�̐ݒ�
	m_pos = pos;

	//�ʒu�̐ݒ�
	m_scale = scale;

	//�g���Ă��邩�ǂ���
	m_bUninit = false;

	//�Q�[�W���������Ă��邩�ǂ���
	m_bGaugeUp = false;

	//��b�ƂȂ�傫��
	m_BaseScale.x = GAUGEBASE_X;

	//���݂̗̑͒l
	m_nLife = m_nBaseLife;

	//��b�ƂȂ�ʒu
	m_BasePos = pos;

	//�Ԋu�J�E���g
	m_nCntTime = 0;

	//�`��D�揇��
	SetObjType(OBJTYPE_UI);

	//�ϐ��錾
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�ʒu��ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_scale.x / 2.0f, m_pos.y + m_scale.y / 2.0f, 0.0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x - m_scale.x / 2.0f, m_pos.y - m_scale.y / 2.0f, 0.0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_scale.x / 2.0f, m_pos.y + m_scale.y / 2.0f, 0.0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_scale.x / 2.0f, m_pos.y - m_scale.y / 2.0f, 0.0);

	// ���_����ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�l��Ԃ�
	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CLifeGauge::Uninit(void)
{
	//���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CLifeGauge::Update(void)
{
	//true�ɂȂ�܂ŏ���
	if (m_bGaugeUp == false)
	{
		//�Q�[�W��������
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

		//�l��Ԃ�
		return;
	}

	//�ʒu���̌Ăяo��
	SetPosition(m_pos, m_scale);
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CLifeGauge::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//*****************************************************************************
// �Q�[�W�k������
//*****************************************************************************
void CLifeGauge::OnDiffuse(int nDiffuseLife)
{
	//�̗͂�^�����_���[�W�����炷
	m_nLife -= nDiffuseLife;

	//���肪true�̏ꍇ
	if (m_bGaugeUp == true)
	{
		//���݂̗̑͒l����o�����̗̑͒l���������l
		float HpGauge = (float)m_nLife / (float)m_nBaseLife*m_scale.x;

		//�Q�[�W�����݂̗̑͒l���ɕϊ�����
		m_scale.x = HpGauge;
	}
}

//*****************************************************************************
// �Q�[�W��������
//*****************************************************************************
void CLifeGauge::OnGaugeUp(void)
{
	//�ő�Q�[�W�ʂɓ��B����܂ŃQ�[�W�𑝉�
	if (m_BaseScale.x >= m_scale.x)
	{
		//�l�𑝉�
		m_scale.x += GAUGEUP_X;

		//��b�ƂȂ�̗͒l��茻�݂̗̑͒l���Ⴂ�ꍇ
		if (m_nBaseLife > m_nLife)
		{
			//���݂̗̑͂̊���
			float fRatio = (float)m_nLife / (float)m_nBaseLife;

			//�̗͂̊������Q�Ƃ��傫���ɑ��
			float scale_x = m_BaseScale.x * fRatio;

			//��������Q�[�W�ʂ�茻�݂̃Q�[�W�ʂ̒l���傫���ꍇ
			if (m_scale.x > scale_x)
			{
				//�l�𓯂��ɂ���
				m_scale.x = scale_x;
			}
		}
		else if (m_BaseScale.x <= m_scale.x)
		{//��b�ƂȂ�̗͒l��茻�݂̗̑͒l�������ꍇ

			//���݂̗̑͂̊���
			float fRatio = (float)m_nLife / (float)m_nBaseLife;

			//�̗͂̊������Q�Ƃ��傫���ɑ��
			float scale_x = m_BaseScale.x * fRatio;

			//�l�𓯂��ɂ���
			m_scale.x = scale_x;
		}
	}
}

//*****************************************************************************
// �ʒu�̐ݒ菈��
//*****************************************************************************
void CLifeGauge::SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�ʒu�̐ݒ�
	m_pos = pos;

	//�ʒu�̐ݒ�
	m_scale = scale;

	//�ϐ��錾
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�ʒu��ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_scale.y / 2.0f, 0.0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x, m_pos.y - m_scale.y / 2.0f, 0.0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y + m_scale.y / 2.0f, 0.0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y - m_scale.y / 2.0f, 0.0);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}