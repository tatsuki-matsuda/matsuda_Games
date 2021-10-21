//--------------------------------------------------------------------------------
//
// �Q�[������[normal_bullet.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _NORMAL_BULLET_H_
#define _NORMAL_BULLET_H_

#include "bullet.h"

//--------------------------------------------------------------------------------
//�}�N����`
//--------------------------------------------------------------------------------
#define	CREATE_BULLET		(3)								//�e�̐�����

//--------------------------------------------------------------------------------
//�O���錾
//--------------------------------------------------------------------------------
class CEnemy;

//================================================================================
//�I�u�W�F�N�g�N���X(�ʏ�e)
//================================================================================
class CNormal_Bullet :public CBullet
{
public:

	CNormal_Bullet(int nPriority = OBJTYPE_BULLET);												//�R���X�g���N�^
	~CNormal_Bullet();																			//�f�X�g���N�^


	static CNormal_Bullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,
		D3DXVECTOR3 move, D3DXVECTOR3 rot, BULLETTYPE bulletType,
		ATTACKTYPE attackType, INFOTYPE infoType);												//�e�̐���

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, D3DXVECTOR3 rot);		//����������
	void Uninit(void);																			//�I������
	void Update(void);																			//�X�V����
	void Draw(void);																			//�`�揈��

private:

	bool m_bUninit;																				//  �I������

	int m_nCnt;																					//	�J�E���g
	int m_nMoveCnt;																				//	�ړ��J�E���g

	D3DXVECTOR3 m_posOrigin;																	//�@�e���������ꂽ�ʒu
	D3DXVECTOR3 m_posDeath;																		//	���Ŏ��̍��W
	D3DXVECTOR3 m_rot;																			//	�p�x

	CScene2D*m_apScene2D[MAX_SCENE2D];															//	CScene2D�̃|�C���^
};
#endif
