//=============================================================================
//
// ���C������ [explosion.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "explosion.h"
#include "scene2D.h"
#include "manager.h"
#include "renderer.h"
#include "dinput_keyboard.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;			// �e�N�X�`��

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CExplosion::CExplosion(int nPriority) :CScene2D(nPriority)
{
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nPatternAnim = 0;
	m_CounterAnim = 0;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CExplosion::~CExplosion()
{

}

//*****************************************************************************
// ��������
//*****************************************************************************
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//���I�m��
	CExplosion* pExplosion;
	pExplosion = new CExplosion;

	//���������Ăяo��
	pExplosion->Init(pos, scale);

	//�e�N�X�`�����Ăяo��
	pExplosion->BindTexture(m_pTexture);

	//�l��Ԃ�
	return pExplosion;
}

//*****************************************************************************
//�@����������
//*****************************************************************************
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�傫����ݒ�
	m_scale = scale;

	//CScene2D���Ăяo��
	CScene2D::Init(pos, scale);

	CScene2D::SetTex(m_nPatternAnim);

	//���
	SetObjType(OBJTYPE_EXPLOSION);

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CExplosion::Update(void)
{
	//�A�j���[�V�����J�E���^�[�̍X�V
	m_CounterAnim++;

	//�A�j���\�V��������
	if (m_CounterAnim % 4 == 0)
	{
		//�p�^�[��No�̍X�V
		m_nPatternAnim += 1;

		//�e�N�X�`���̌Ăяo��
		CScene2D::SetTex(m_nPatternAnim);

		//�p�^�[������萔�����ꂽ�ꍇ
		if (m_nPatternAnim > 7)
		{
			//�A�j���[�V�����̏I��
			Uninit();

		}
	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}

//*****************************************************************************
// �e�N�X�`���ǂݍ��ݏ���
//*****************************************************************************
HRESULT CExplosion::Load(void)
{
	//�f�o�C�X�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\explosion000.png", &m_pTexture);

	return S_OK;
}

//*****************************************************************************
// �e�N�X�`���j������
//*****************************************************************************
void CExplosion::Unload(void)
{
	//�e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}