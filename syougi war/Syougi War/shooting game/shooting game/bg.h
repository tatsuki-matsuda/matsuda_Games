//--------------------------------------------------------------------------------
//
// �Q�[������[bg.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _BG_H_
#define _BG_H_

#include "scene2D.h"

//--------------------------------------------------------------------------------
//�}�N����`
//--------------------------------------------------------------------------------
#define SCREEN_WIDTH		(1280)									//�X�N���[���̕�
#define SCREEN_HEIGHT		(720)									//�X�N���[���̍���
#define SCREEN_CENTER_X		(SCREEN_WIDTH/2)						//�X�N���[�����SX���W
#define SCREEN_CENTER_Y		(SCREEN_HEIGHT/2)						//�X�N���[�����SY���W
#define MAX_BG				(5)										//�w�i�̍ő吔

//================================================================================
//�I�u�W�F�N�g�N���X(�w�i)
//================================================================================
class CBg :public CScene
{
public:

	CBg(int nPriority=OBJTYPE_BG);									//�R���X�g���N�^
	~CBg();															//�f�X�g���N�^

	static CBg *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);			//�v���C���[�̐���

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				//����������
	void Uninit(void);												//�I������
	void Update(void);												//�X�V����
	void Draw(void);												//�`�揈��

	static HRESULT Load(void);										//�ǂݍ��ݏ���
	static void Unload(void);										//�j������

private:

	float m_fAnim;													//	�A�j���[�V����
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG];					//	�e�N�X�`��
	CScene2D*m_apScene2D[5] = {};									//	CScene2D�̃|�C���^
};
#endif