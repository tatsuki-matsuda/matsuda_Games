//--------------------------------------------------------------------------------
//
// �Q�[������[rotate_bullet.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _ROTATE_BULLET_H_
#define _ROTATE_BULLET_H_

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
//�I�u�W�F�N�g�N���X(��]�e)
//================================================================================
class CRotate_Bullet :public CBullet
{
public:

	CRotate_Bullet(int nPriority = OBJTYPE_BULLET);												//�R���X�g���N�^
	~CRotate_Bullet();																			//�f�X�g���N�^


	static CRotate_Bullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,
		D3DXVECTOR3 move, D3DXVECTOR3 rot, BULLETTYPE bulletType,
		ATTACKTYPE attackType, INFOTYPE infoType);												//�e�̐���

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, D3DXVECTOR3 rot);		//����������
	void Uninit(void);																			//�I������
	void Update(void);																			//�X�V����
	void Draw(void);																			//�`�揈��

private:

	bool m_bUninit;																				//  �I������

	float m_fAngleSpeed[2];																		//	��]���x
	float m_fAngle;																				//	��]��
	float m_fAngleL;																			//	����]��
	float m_fAngleR;																			//	�E��]��

	int m_nCrossingTimeL;																		//	����������
	int m_nCrossingTimeR;																		//	�E��������

	int m_nCnt;																					//	�J�E���g

	D3DXVECTOR3 m_posOrigin;																	//�@�e���������ꂽ�ʒu
	D3DXVECTOR3 m_posDeath;																		//	���Ŏ��̍��W
	D3DXVECTOR3 m_rot;																			//	�p�x

	CScene2D*m_apScene2D[MAX_SCENE2D];															//	CScene2D�̃|�C���^
};
#endif

