//=============================================================================
//
// ���C������ [scene2D.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "polygon.h"
#include "manager.h"
#include "scene2D.h"


//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CPolygon::CPolygon()
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CPolygon::~CPolygon()
{

}

//*****************************************************************************
//�@����������
//*****************************************************************************
HRESULT CPolygon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�ϐ��錾
	VERTEX_2D*pVtx;

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

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CPolygon::Uninit(void)
{
	//���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CPolygon::Draw(void)
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
// ��������
//*****************************************************************************
CPolygon *CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//���I�m��
	CPolygon* Polygon;
	Polygon = new CPolygon;

	if (Polygon != NULL)
	{
		Polygon->Init(pos, scale);
	}

	return Polygon;
}

//*****************************************************************************
// �J���[�̐ݒ菈��
//*****************************************************************************
void CPolygon::SetColor(D3DXCOLOR color)
{
	//�ϐ��錾
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}