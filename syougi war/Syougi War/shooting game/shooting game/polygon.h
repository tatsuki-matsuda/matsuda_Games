#pragma once
//--------------------------------------------------------------------------------
//
// �Q�[������[scene2D.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "main.h"

//================================================================================
//�I�u�W�F�N�g�N���X(2D�|���S��)
//================================================================================
class CPolygon
{
public:

	CPolygon();														//�R���X�g���N�^
	~CPolygon();													//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				//����������
	void Uninit(void);												//�I������
	void Draw(void);												//�`�揈��

	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);	//�|���S���̐���

	void SetColor(D3DXCOLOR color);									//�J���[�̐ݒ�


private:

	int nCnt;										// �A�j���[�V�����p�^�[��No
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;					// �e�N�X�`��
	D3DXVECTOR3 m_pos;								// �|���S���̈ʒu
	D3DXVECTOR3 m_scale;							// �傫��
};

#endif