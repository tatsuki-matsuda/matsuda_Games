//-------------------------------------------------------------------------------
//
// �Q�[������[camera.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include"camera.h"		//�Q�[�����
#include"player.h"
#include"manager.h"
#include"player.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CCamera::CCamera()
{

}
//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CCamera::~CCamera()
{

}

//*****************************************************************************
// ����������
//*****************************************************************************
void CCamera::InitCamera(void)
{
	//�J�����̈ʒu
	m_apCamera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_apCamera.posV = D3DXVECTOR3(0.0f, MAX_POSV_Y, MAX_POSV_Z);
	m_apCamera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_apCamera.posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//g_aCamera.posR.x = g_aCamera.posV.x +- sinf();
}

//-------------------------------------------------------------------------------
//�I������
//-------------------------------------------------------------------------------
void CCamera::UninitCamera(void)
{
}

//-------------------------------------------------------------------------------
//�X�V����
//-------------------------------------------------------------------------------
void CCamera::UpdateCamera(void)
{
}


//-------------------------------------------------------------------------------
//�ݒ菈��
//-------------------------------------------------------------------------------
void CCamera::SetCamera(void)
{
	//�f�o�C�X�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_apCamera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_apCamera.mtxProjection, D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 1000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_apCamera.mtxProjection);

	//�r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&m_apCamera.mtxView, &m_apCamera.posV,
		&m_apCamera.posR, &m_apCamera.posU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_apCamera.mtxView);
}