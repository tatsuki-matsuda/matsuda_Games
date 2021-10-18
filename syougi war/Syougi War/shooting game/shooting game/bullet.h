//--------------------------------------------------------------------------------
//
// �Q�[������[bullet.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

#include "scene2D.h"

//--------------------------------------------------------------------------------
//�}�N����`
//--------------------------------------------------------------------------------
#define NORMAL_DAMAGE		(4)								//�ʏ�e�_���[�W��
#define BOMB_DAMAGE			(3)								//�{���_���[�W��
#define HOMING_DAMAGE		(2)								//�z�[�~���O�_���[�W��
#define CROSSING_DAMAGE		(1)								//�����e�_���[�W��
#define REFLECTIVE_DAMAGE	(1)								//���˒e�_���[�W��
#define WAVE_DAMAGE			(1)								//�g��e�_���[�W��
#define	CREATE_BULLET		(3)								//�e�̐�����

#define PLAYER_HOMING_X		(15.0f)							//�v���C���[�z�[�~���OX���ړ���
#define PLAYER_HOMING_Y		(23.0f)							//�v���C���[�z�[�~���OY���ړ���
#define ENEMY_HOMING_X		(12.0f)							//�v���C���[�z�[�~���OX���ړ���
#define ENEMY_HOMING_Y		(23.0f)							//�v���C���[�z�[�~���OY���ړ���

//--------------------------------------------------------------------------------
//�O���錾
//--------------------------------------------------------------------------------
class CEnemy;

//================================================================================
//�I�u�W�F�N�g�N���X(�e)
//================================================================================
class CBullet :public CScene2D
{
public:

	CBullet(int nPriority = OBJTYPE_BULLET);													//�R���X�g���N�^
	~CBullet();																					//�f�X�g���N�^

	//�e���蕪��
	typedef enum
	{
		BULLETTYPE_NONE = 0,
		BULLETTYPE_PLAYER,				//�v���C���[
		BULLETTYPE_ENEMY,				//�G
		BULLETTYPE_MAX

	}BULLETTYPE;

	//�U����ޕ���
	typedef enum
	{
		ATTACKTYPE_NONE = 0,
		ATTACKTYPE_NORMAL,				//�ʏ�e
		ATTACKTYPE_HOMING,				//�z�[�~���O
		ATTACKTYPE_CROSSING,			//����
		ATTACKTYPE_ROTATION,			//��]
		ATTACKTYPE_REFLECTION,			//����
		ATTACKTYPE_TURN,				//�܂�Ԃ�
		ATTACKTYPE_N_WAY1,				//n_way�e1
		ATTACKTYPE_N_WAY2,				//n_way�e2
		ATTACKTYPE_SPIRAL,				//�Q���e
		ATTACKTYPE_BOMB,				//�{��
		ATTACKTYPE_MAX

	}ATTACKTYPE;

	//�U������ޕ���
	typedef enum
	{
		INFOTYPE_NONE = 0,
		INFOTYPE_1,
		INFOTYPE_2,
		INFOTYPE_3,
		INFOTYPE_RED,
		INFOTYPE_BLUE,
		INFOTYPE_BIGBULLET,
		INFOTYPE_MAX

	}INFOTYPE;

	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, 
		D3DXVECTOR3 move, D3DXVECTOR3 rot, BULLETTYPE bulletType,
		ATTACKTYPE attackType,INFOTYPE infoType);												//�e�̐���

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, D3DXVECTOR3 rot);		//����������
	void Uninit(void);																			//�I������
	void Update(void);																			//�X�V����
	void Draw(void);																			//�`�揈��
	static HRESULT Load(void);																	//�ǂݍ��ݏ���
	static void Unload(void);																	//�j������

	BULLETTYPE GetBulletType(void);																//�e���
	void SetBulletType(BULLETTYPE bulletType);													//�e���̎擾

	ATTACKTYPE GetAttackType(void);																//�U����ޏ��
	void SetAttackType(ATTACKTYPE attackType);													//�U����ޏ��̎擾

	INFOTYPE GetInfoType(void);																	//�U�����
	void SetInfoType(INFOTYPE infoType);														//�U�����̎擾

	void SetGraze(bool bgraze);																	//�O���C�Y���
	bool GetGraze(void);																		//�O���C�Y���̎擾

	void SetUninit(bool bUninit);																//�e�������
	bool GetUninit(void);																		//�e�������̎擾

	void SetLife(int nLife);																	//�̗͏��
	int  GetLife(void);																			//�̗͏��̎擾

	void SetMove(D3DXVECTOR3 move);																//�ړ����
	D3DXVECTOR3  GetMove(void);																	//�ړ����̎擾

	static LPDIRECT3DTEXTURE9  GetTexture(int nCntTex);											//�e�N�X�`�����̎擾

protected:

	void OnCrossing(void);																		//	��������
	void OnCollision(void);																		//	���菈��
	void OnHoming(void);																		//	�ǔ�����
	void OnReflection(void);																	//	���ˏ���
	void OnTurn(void);																			//	�܂�Ԃ�����
	void OnDiffusion(void);																		//	�g�U����
	void OnBomb(void);																			//	�{������

private:

	bool m_bGraze;																				//  �O���C�Y����
	bool m_bReflection;																			//	���˔���
	bool m_bUninit;																				//  �I������

	BULLETTYPE m_BulletType;																	//  �e�̎��
	ATTACKTYPE m_AttackType;																	//  �U���̎��
	INFOTYPE   m_InfoType;																		//	�U�����̎��

	float m_fAngleSpeed[2];																		//	��]���x
	float m_fAngle;																				//	��]��
	float m_fAngleBomb;																			//	�{���̉�]��
	float m_fAngleL;																			//	����]��
	float m_fAngleR;																			//	�E��]��
	float m_fLengthObj;																			//�@�e�Ɉ�ԋ߂��I�u�W�F�N�g�̈ʒu

	int m_nCrossingTimeL;																		//	����������
	int m_nCrossingTimeR;																		//	�E��������
	int m_nReflectionCnt;																		//	���˃J�E���g
	int m_nWayCnt;																				//	n_way�e�����J�E���g
	int m_TurnCnt;																				//	�؂�ւ����J�E���g
	int m_nCnt;																					//	�J�E���g
	int	m_nPlayerCnt;																			//	�v���C���[���Ō�J�E���g
	int m_nLife;																				//	�̗�
	int m_nKeepObj;																				//	�I�u�W�F�N�g��ۑ�����l
	int m_nCntDraw;
	int m_nCntSpiral = 0;																		//	�Q���J�E���g

	D3DXVECTOR3 m_posOrigin;																	//�@�e���������ꂽ�ʒu
	D3DXVECTOR3 m_posDeath;																		//	���Ŏ��̍��W
	D3DXVECTOR3 m_rot;																			//	�p�x
	D3DXVECTOR3 m_scale;																		//	�傫��
	D3DXVECTOR3 m_move;																			//	�ړ���
	D3DXCOLOR	m_Color;																		//	�F
	D3DXVECTOR3 m_EnemyBulletpos;																	//	�G�̒e�̈ʒu
	D3DXVECTOR3 m_PlayerBulletpos;																//	�v���C���[�̒e�̈ʒu

	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];											//	�e�N�X�`��
	CScene2D*m_apScene2D[MAX_SCENE2D];															//	CScene2D�̃|�C���^
};
#endif
