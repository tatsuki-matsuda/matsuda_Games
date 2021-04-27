//--------------------------------------------------------------------------------
//
// �Q�[������[player.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"
#include "input.h"



//--------------------------------------------------------------------------------
//�e���[�V�����̏��
//--------------------------------------------------------------------------------
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,	//�ҋ@���[�V����
	MOTIONTYPE_RUN,		//�p���`���[�V����
}MOTIONTYPE;

//-------------------------------------------------------------------------------
//�L�[�̍\����
//-------------------------------------------------------------------------------
typedef struct
{
	float fPosX;	//�L�[�̈ʒuX
	float fPosY;	//�L�[�̈ʒuY
	float fPosZ;	//�L�[�̈ʒuZ
	float fRotX;	//�L�[�̉�]X
	float fRotY;	//�L�[�̉�]Y
	float fRotZ;	//�L�[�̉�]Z	
}KEY;

//-------------------------------------------------------------------------------
//�L�[���̍\����
//-------------------------------------------------------------------------------
typedef struct
{
	KEY aKey[14];	//�e���f���̃L�[�v�f

	int nFlame;		//�Đ��t���[��
}KEY_INFO;

//-------------------------------------------------------------------------------
//���[�V�������̍\����
//-------------------------------------------------------------------------------
typedef struct
{
	KEY_INFO aKeyInfo[14];	//�L�[���

	int nNumKey;			//�L�[����
	
	float fPosY;			//�L�[�̈ʒuY
	float fPosZ;			//�L�[�̈ʒuZ

	bool bloop;				//���[�v���邩�ǂ���
}MOTION_INFO;


//-------------------------------------------------------------------------------
//���f���̍\����
//-------------------------------------------------------------------------------
typedef struct
{
	LPD3DXMESH MeshModel = NULL;			//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER BuffMatModel = NULL;		//�}�e���A��(�ގ����)�ւ̃|�C���^
	DWORD	nNumMat;						//�}�e���A���̐�
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 Bulletpos;					//���ˈʒu
	D3DXVECTOR3 oldpos;						//�O��̈ʒu
	D3DXVECTOR3 rot;						//����
	D3DXMATRIX  mtxWorld;					//���[���h�}�g���b�N�X

	int nIdxModelParent;					//�e�̃��f���̃C���f�b�N�X
}Model;

//-------------------------------------------------------------------------------
//�v���C���[�̍\����
//-------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 oldpos;						//�O��̈ʒu
	D3DXVECTOR3 move;						//�ړ�
	D3DXVECTOR3 rot;						//����
	D3DXMATRIX  mtxWorld;					//���[���h�}�g���b�N�X

	MOTION_INFO aMotionInfo[2];				//���[�V�������
	Model aModel[14];						//���f��(�p�[�c)

	int	nNumModel;							//���f��(�p�[�c)��
	int nNumMotion;							//���[�V������
	int nCounterMotion;						//���[�V�����J�E���^�[
	int nNumKey;							//�L�[��
	int nKey;								//�L�[No.

	float fRadius;							//���a

	bool bLoopMotion;						//���[�V�����J�E���^�[
	bool bUse;								//�g�p���Ă��邩�ǂ���
}Player;


//--------------------------------------------------------------------------------
//�v���g�^�C�v�錾
//--------------------------------------------------------------------------------
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player*GetPlayer(void);
//bool HitPoligon(void);
#endif
