//--------------------------------------------------------------------------------
//
// �Q�[������[item.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _LIFE_H_
#define _LIFE_H_

#include "scene2D.h"

//--------------------------------------------------------------------------------
//�}�N����`
//--------------------------------------------------------------------------------
#define ITEM_MOVE_X		(3)										//�A�C�e����X���ړ�
#define ITEM_MOVE_Y		(10)									//�A�C�e����Y���ړ�
#define	MAX_PLAYERLIFE	(5)										//�c�@��

//--------------------------------------------------------------------------------
//�O���錾
//--------------------------------------------------------------------------------
class CBullet;

//================================================================================
//�I�u�W�F�N�g�N���X(���C�t)
//================================================================================
class CLife :public CScene2D
{
public:

	CLife(int nPriority = OBJTYPE_UI);								//�R���X�g���N�^
	~CLife();														//�f�X�g���N�^

	static CLife *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);		//�A�C�e���̐���

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				//����������
	void Uninit(void);												//�I������
	void Update(void);												//�X�V����
	void Draw(void);												//�`�揈��

	static HRESULT Load(void);										//�ǂݍ��ݏ���
	static void Unload(void);										//�j������

	int GetLife(void) { return m_nLife; }							// ���݂̃��C�t���擾�p
	void SetLife(int nLife) { m_nLife = nLife; }					// �̗͂̐ݒ�

private:

	void OnDiffuesPos(int nCnt);									// �J�E���g�Ń��C�t����

	bool m_bUninit;													// �I�����菈��

	int	 m_nLife;													// �c�@�J�E���g
	int	 m_nCntTime;												// �Ԋu
	int	 m_timer;													// �o�ߎ���

	float m_angle;													// �p�x

	static D3DXVECTOR3 m_Craetepos[5];								// �������̍��W��ݒ�
	D3DXVECTOR3 m_posDeath;											// ���ł����Ƃ��̈ʒu��ۑ�
	D3DXVECTOR3 m_move;												// �ړ�
	D3DXVECTOR3 m_scale;											// �傫��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;						// ���_�o�b�t�@�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];				//	�e�N�X�`��
	CScene2D*m_apScene2D[5];										//	CScene2D�̃|�C���^
};
#endif