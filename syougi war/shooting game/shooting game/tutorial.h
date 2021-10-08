//--------------------------------------------------------------------------------
//
// �Q�[������[title.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "bg.h"
#include "player.h"
#include "enemy.h"

//--------------------------------------------------------------------------------
//�O���錾
//--------------------------------------------------------------------------------
class CBg;

//================================================================================
//�I�u�W�F�N�g�N���X
//================================================================================
class CTutorial : CScene
{

public:

	CTutorial();													//�R���X�g���N�^
	~CTutorial();													//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				//����������
	void Uninit(void);												//�I������
	void Update(void);												//�X�V����
	void Draw(void);												//�`�揈��

	static CBg*GetBg(void);											//�w�i���̌Ăяo��

private:

	static CBg*m_pBg;

};

#endif

