//=============================================================================
//
// ���C������ [number.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "number.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;			// �e�N�X�`��

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CNumber::CNumber()
{
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CNumber::~CNumber()
{

}

//*****************************************************************************
// ��������
//*****************************************************************************
CNumber *CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//���I�m��
	CNumber* pNumber;
	pNumber = new CNumber;

	//�����̌Ăяo��
	pNumber->Init(pos, scale);

	//�l��Ԃ�
	return pNumber;
}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CNumber::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//�f�o�C�X�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

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
	m_pos = pos;

	//�傫����ݒ�
	m_scale = scale;

	//���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - scale.x / 2.0f, m_pos.y + scale.y / 2.0f, 0.0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x - scale.x / 2.0f, m_pos.y - scale.y / 2.0f, 0.0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + scale.x / 2.0f, m_pos.y + scale.y / 2.0f, 0.0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + scale.x / 2.0f, m_pos.y - scale.y / 2.0f, 0.0);

	// ���_����ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);

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

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CNumber::Uninit(void)
{
	//���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CNumber::Update(void)
{
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CNumber::Draw(void)
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
// �ʒu�擾����
//*****************************************************************************
D3DXVECTOR3 CNumber::GetPosition(void)
{
	return m_pos;
}

//*****************************************************************************
// �傫���擾����
//*****************************************************************************
D3DXVECTOR3 CNumber::GetScale(void)
{
	return m_scale;
}

//*****************************************************************************
// �X�R�A�\������
//*****************************************************************************
void CNumber::SetNumber(int nNumber)
{
	//�\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`���̍X�V
	pVtx[0].tex = D3DXVECTOR2(0.0f + nNumber * 0.1f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + nNumber * 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((1.0f / 10.0f) + nNumber * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((1.0f / 10.0f)  + nNumber * 0.1f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}



//*****************************************************************************
// �e�N�X�`���ǂݍ��ݏ���
//*****************************************************************************
void CNumber::Load(void)
{
	//�f�o�C�X�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number000.png", &m_pTexture);
}

//*****************************************************************************
// �e�N�X�`���j������
//*****************************************************************************
void CNumber::Unload(void)
{
	//�e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}