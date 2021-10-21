//--------------------------------------------------------------------------------
//
// �Q�[������[title.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "bg.h"
#include "logo.h"

//--------------------------------------------------------------------------------
//�O���錾
//--------------------------------------------------------------------------------
class CBg;
class CLogo;

//================================================================================
//�I�u�W�F�N�g�N���X
//================================================================================
class CTitle : CScene
{

public:

	CTitle();														//�R���X�g���N�^
	~CTitle();														//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				//����������
	void Uninit(void);												//�I������
	void Update(void);												//�X�V����
	void Draw(void);												//�`�揈��

	static CBg*GetBg(void);											//�w�i���̌Ăяo��
	static CLogo*GetLogo(void);										//���S���̌Ăяo��

private:

	static CBg*m_pBg;												//�w�i���̃|�C���^
	static CLogo*m_pLogo;											//���S���̃|�C���^

};

#endif


