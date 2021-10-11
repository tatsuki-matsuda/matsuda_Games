//--------------------------------------------------------------------------------
//
// �Q�[������[bg.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "scene2D.h"

//--------------------------------------------------------------------------------
//�}�N����`
//--------------------------------------------------------------------------------
#define MAX_PAUSEUI				(4)										//�|�[�YUI�̍ő吔

//================================================================================
//�I�u�W�F�N�g�N���X(�w�i)
//================================================================================
class CPause :public CScene
{
public:

	typedef enum
	{
		PAUSEUI_NONE = 0,
		PAUSEUI_CONTINUE,
		PAUSEUI_RETRY,
		PAUSEUI_TITLE,
		PAUSEUI_MAX

	}PAUSEUI;

	CPause(int nPriority = OBJTYPE_PAUSE);								//	�R���X�g���N�^
	~CPause();															//	�f�X�g���N�^

	static CPause *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);			//	�v���C���[�̐���

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);					//	����������
	void Uninit(void);													//	�I������
	void Update(void);													//	�X�V����
	void Draw(void);													//	�`�揈��

	static HRESULT Load(void);											//	�ǂݍ��ݏ���
	static void Unload(void);											//	�j������



private:

	float m_fMove;													//  �ړ�
	float m_fAnim;													//	�A�j���[�V����
	int	  m_ColorCnt;												//	�F�_�ŃJ�E���g
	int   m_nSelectCnt;												//	�I���J�E���g
	static LPDIRECT3DTEXTURE9 m_apTexture[PAUSEUI_MAX];				//	�e�N�X�`��
	CScene2D*m_apScene2D[PAUSEUI_MAX];								//	CScene2D�̃|�C���^
};
#endif