//--------------------------------------------------------------------------------
//
// �Q�[������[number.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"

//--------------------------------------------------------------------------------
//�}�N����`
//--------------------------------------------------------------------------------
#define SCREEN_WIDTH		(1280)									//�X�N���[���̕�
#define SCREEN_HEIGHT		(720)									//�X�N���[���̍���
#define SCREEN_CENTER_X		(SCREEN_WIDTH/2)						//�X�N���[�����SX���W
#define SCREEN_CENTER_Y		(SCREEN_HEIGHT/2)						//�X�N���[�����SY���W
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//���_�t�H�[�}�b�g

//================================================================================
//�I�u�W�F�N�g�N���X
//================================================================================
class CNumber
{

public:

	CNumber();														//�R���X�g���N�^
	~CNumber();														//�f�X�g���N�^

	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				//����������
	void Uninit(void);												//�I������
	void Update(void);												//�X�V����
	void Draw(void);												//�`�揈��
	void SetNumber(int nNumber);									//�X�R�A�\������
	D3DXVECTOR3 GetPosition(void);									//�ʒu�̎擾
	D3DXVECTOR3 GetScale(void);										//�傫�����̎擾
	static void Load(void);											//�ǂݍ��ݏ���
	static void Unload(void);										//�j������
private:


	static LPDIRECT3DTEXTURE9 m_pTexture;								// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;							// ���_�o�b�t�@�̃|�C���^
	D3DXVECTOR3 m_pos;													// �ʒu
	D3DXVECTOR3 m_scale;												// �傫��
};

#endif