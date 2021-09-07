//--------------------------------------------------------------------------------
//
// �Q�[������[player.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "scene2D.h"

//--------------------------------------------------------------------------------
//�}�N����`
//--------------------------------------------------------------------------------
#define PLAYER_MOVE_HEIGHT_TOP	(20)								//�v���C���[Y���ړ��\���E
#define PLAYER_MOVE_WIDTH_TOP	(20)								//�v���C���[X���ړ��\���E
#define PLAYER_MOVE_HEIGHT	(700)									//�v���C���[Y���ړ��\���E
#define PLAYER_MOVE_WIDTH	(850)									//�v���C���[X���ړ��\���E


//================================================================================
//�I�u�W�F�N�g�N���X(�v���C���[)
//================================================================================
class CPlayer :public CScene2D
{
public:

	CPlayer(int nPriority=OBJTYPE_PLAYER);							//�R���X�g���N�^
	~CPlayer();														//�f�X�g���N�^

	static CPlayer *Create(D3DXVECTOR3 pos,D3DXVECTOR3 scale);		//�v���C���[�̐���

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				//����������
	void Uninit(void);												//�I������
	void Update(void);												//�X�V����
	void Draw(void);												//�`�揈��
	void CollisionGraze(void);										//�O���C�Y���菈��

	static void Load(void);											//�ǂݍ��ݏ���
	static void Unload(void);										//�j������

private:

	float m_angle;													// �p�x
	int	  m_timer;													// ���ˎ���
	D3DXVECTOR3 m_scale;											// �傫��
	D3DXVECTOR3 m_move;												// �ړ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;						// ���_�o�b�t�@�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture;							// �e�N�X�`��

};
#endif