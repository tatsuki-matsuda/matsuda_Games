//--------------------------------------------------------------------------------
//
// �Q�[������[explosion.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "scene2D.h"

//--------------------------------------------------------------------------------
//�}�N����`
//--------------------------------------------------------------------------------
#define EXPLOSION_SCALE_Y	(30)
#define EXPLOSION_SCALE_X	(30)

//================================================================================
//�I�u�W�F�N�g�N���X(�v���C���[)
//================================================================================
class CExplosion :public CScene2D
{
public:

	CExplosion(int nPriority = OBJTYPE_EXPLOSION);						//�R���X�g���N�^
	~CExplosion();														//�f�X�g���N�^

	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);		//�����̐���

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);					//����������
	void Uninit(void);													//�I������
	void Update(void);													//�X�V����
	void Draw(void);													//�`�揈��
	static HRESULT Load(void);											//�ǂݍ��ݏ���
	static void Unload(void);											//�j������

private:

	D3DXVECTOR3 m_scale;												//	�傫��
	int m_CounterAnim;													//	�A�j���[�V�����J�E���^�[
	int m_nPatternAnim;													//	�e�N�X�`���̃p�^�[��No.
	static LPDIRECT3DTEXTURE9 m_pTexture;								//	�e�N�X�`��
};
#endif

