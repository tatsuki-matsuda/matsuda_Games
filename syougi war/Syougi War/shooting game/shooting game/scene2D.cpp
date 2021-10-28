//=============================================================================
//
// ���C������ [scene2D.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "scene2D.h"
#include "manager.h"
#include "renderer.h"
#include "dinput_keyboard.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CScene2D*CScene2D::m_apBullet1[10] = {};			// �|���S���̐�

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CScene2D::CScene2D(int nPriority):CScene(nPriority)
{
	for (int nCntpBullet = 0; nCntpBullet < 10; nCntpBullet++)
	{
		if (m_apBullet1[nCntpBullet] == NULL)
		{
			m_apBullet1[nCntpBullet] = this;
			break;
		}
	}
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CScene2D::~CScene2D()
{

}

//*****************************************************************************
//�@����������
//*****************************************************************************
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
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
	m_scale = scale / 2.0f;

	//�_�ƒ��S�_��}�鏈��
	Length();

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�ʒu��ݒ�
	pVtx[0].pos.x = m_pos.x - sinf(m_fAngle + m_rot.z)*(m_fLength);
	pVtx[0].pos.y = m_pos.y + cosf(m_fAngle + m_rot.z)*(m_fLength);
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x - sinf(m_fAngle - m_rot.z)*(m_fLength);
	pVtx[1].pos.y = m_pos.y - cosf(m_fAngle - m_rot.z)*(m_fLength);
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_fAngle - m_rot.z)*(m_fLength);
	pVtx[2].pos.y = m_pos.y + cosf(m_fAngle - m_rot.z)*(m_fLength);
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_fAngle + m_rot.z)*(m_fLength);
	pVtx[3].pos.y = m_pos.y - cosf(m_fAngle + m_rot.z)*(m_fLength);
	pVtx[3].pos.z = 0.0f;

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
void CScene2D::Uninit(void)
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
void CScene2D::Update(void)
{

}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CScene2D::Draw(void)
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
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//���I�m��
	CScene2D* pScene2D;
	pScene2D = new CScene2D;

	if (pScene2D != NULL)
	{
		pScene2D->Init(pos,scale);
	}

	return pScene2D;
}

//*****************************************************************************
// �ʒu����
//*****************************************************************************
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}

//*****************************************************************************
// �ʒu�̐ݒ菈��
//*****************************************************************************
void CScene2D::SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
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
	pVtx[0].pos.x = m_pos.x - sinf(m_fAngle + m_rot.z)*(m_fLength);
	pVtx[0].pos.y = m_pos.y + cosf(m_fAngle + m_rot.z)*(m_fLength);
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x - sinf(m_fAngle - m_rot.z)*(m_fLength);
	pVtx[1].pos.y = m_pos.y - cosf(m_fAngle - m_rot.z)*(m_fLength);
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_fAngle - m_rot.z)*(m_fLength);
	pVtx[2].pos.y = m_pos.y + cosf(m_fAngle - m_rot.z)*(m_fLength);
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_fAngle + m_rot.z)*(m_fLength);
	pVtx[3].pos.y = m_pos.y - cosf(m_fAngle + m_rot.z)*(m_fLength);
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//*****************************************************************************
//�����̐ݒ菈��
//*****************************************************************************
void CScene2D::SetTex(int nCnt)
{
	//�ϐ��錾
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̍X�V
	pVtx[0].tex = D3DXVECTOR2(0.125f*nCnt, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.125f*nCnt, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.125f+ (0.125f*nCnt), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.125f+ (0.125f*nCnt), 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//*****************************************************************************
//�w�i�X�N���[���̐ݒ菈��
//*****************************************************************************
void CScene2D::SetBg(float ScrollBg)
{

	//�ϐ��錾
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̍X�V
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f+ScrollBg);
	pVtx[1].tex = D3DXVECTOR2(0.0f,1.0f+ScrollBg);
	pVtx[2].tex = D3DXVECTOR2(1.0f,0.0f +ScrollBg);
	pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f +ScrollBg);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//*****************************************************************************
// �J���[�̐ݒ菈��
//*****************************************************************************
void CScene2D::SetColor(D3DXCOLOR color)
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

//*****************************************************************************
// ������}�鏈��
//*****************************************************************************
void CScene2D::Length(void)
{
	//���S�_�Ɠ_�Ƃ̋���
	m_fLength = sqrtf(m_scale.x * m_scale.x + m_scale.y * m_scale.y);

	//�p�x
	m_fAngle = atan2f(m_scale.x, m_scale.y);
}


//*****************************************************************************
// �e�N�X�`���̊��蓖�ď���
//*****************************************************************************
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}