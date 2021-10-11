//--------------------------------------------------------------------------------
//
// �Q�[������[game_screen.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _GAME_SCREEN_H_
#define _GAME_SCREEN_H_

#include "scene2D.h"

//================================================================================
//�I�u�W�F�N�g�N���X(�Q�[���w�i)
//================================================================================
class CGame_Screen :public CScene
{
public:

	CGame_Screen(int nPriority = OBJTYPE_GAME);						//�R���X�g���N�^
	~CGame_Screen();												//�f�X�g���N�^

	static CGame_Screen *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�Q�[���w�i�̐���

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				//����������
	void Uninit(void);												//�I������
	void Update(void);												//�X�V����
	void Draw(void);												//�`�揈��

	static HRESULT Load(void);										//�ǂݍ��ݏ���
	static void Unload(void);										//�j������

private:

	static LPDIRECT3DTEXTURE9 m_apTexture[1];						//	�e�N�X�`��
	CScene2D*m_apScene2D[1];										//	CScene2D�̃|�C���^
};
#endif