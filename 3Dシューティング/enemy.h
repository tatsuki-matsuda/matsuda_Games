//--------------------------------------------------------------------------------
//
// �Q�[������[Enemy.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
#include "input.h"

//-------------------------------------------------------------------------------
//�}�N����`
//-------------------------------------------------------------------------------
#define MAX_ENEMY_PARTS (12)				//�G�̃p�[�c��
#define SEARCHRANGE_ENEMY (300)				//�G�̍��G�͈�
#define SEARCHSTOP_ENEMY (40)				//�G�̍��G��~�͈�
#define LAUNCHRANGE_BOSSBULLET (2000)		//�{�X�e�̔��˔͈�
#define LAUNCHRANGE_BULLET (240)			//�G�e�̔��˔͈�
#define ENEMY_LIFEBOSS (20)					//�{�X�̗̑�
#define ENEMY_LIFE000 (5)					//�G1�̗̑�
#define ENEMY_LIFE001 (3)					//�G2�̗̑�
#define MAX_ENEMY (9)						//�G�̐�

//--------------------------------------------------------------------------------
//�G�̏��
//--------------------------------------------------------------------------------
typedef enum
{
	ENEMYSTATE_NOMARL = 0,	//�ʏ���
	ENEMYSTATE_DAMAGE,		//�_���[�W���
	ENEMYSTATE_MAX
}ENEMYSTATE;

//-------------------------------------------------------------------------------
//���f���̍\����
//-------------------------------------------------------------------------------
typedef struct
{
	LPD3DXMESH MeshModel = NULL;			//���b�V��(���_���)�ւ̃|�C���^
	D3DXMATERIAL*pMat;
	LPD3DXBUFFER BuffMatModel = NULL;		//�}�e���A��(�ގ����)�ւ̃|�C���^
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 move;						//�ړ�
	D3DXVECTOR3 rot;						//����
	ENEMYSTATE State;						//���
	DWORD	nNumMat;						//�}�e���A���̐�
	D3DXMATRIX  mtxWorld;					//���[���h�}�g���b�N�X
	int	nNumModel;							//���f��(�p�[�c)��
	float fRadius;							//�G�̉�]
	int nType;								//���
	int nCounterBoss;						//�{�X�̏o���J�E���^�[
	int nCounterEnemy;						//�G�̏o���J�E���^�[
	int nCounterShot;						//�e�̔��˃J�E���^�[
	int nEnemyLife;							//�̗�
	int nIdxModelParent;					//�e�̃��f���̃C���f�b�N�X
	bool bUse;								//�g�p���Ă��邩�ǂ���
	bool bUseStopShot;						//��~���Ă���Ƃ��ɒe���g�p���Ă��邩�ǂ���
	bool bSearchRange;						//���G�͈͂ɓ����Ă邩�ǂ���
	bool bAppearance;						//�G�̏o������
}ENEMYMODEL;

//-------------------------------------------------------------------------------
//�G�̍\����
//-------------------------------------------------------------------------------
typedef struct
{
	LPD3DXMESH MeshModel = NULL;			//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER BuffMatModel = NULL;		//�}�e���A��(�ގ����)�ւ̃|�C���^
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 move;						//�ړ�
	D3DXVECTOR3 rot;						//����
	DWORD	nNumMat;						//�}�e���A���̐�
	D3DXMATRIX  mtxWorld;					//���[���h�}�g���b�N�X
	ENEMYMODEL aModel[MAX_ENEMY_PARTS];		//���f��(�p�[�c)
	int	nNumModel;							//���f��(�p�[�c)��
	float fRadius;							//�G�̉�]
	int nType;								//���
	int nLife;								//�̗�
	int nEnemyLife;							//�̗�
	int nIdxModelParent;					//�e�̃��f���̃C���f�b�N�X
	bool bUse;								//�g�p���Ă��邩�ǂ���
	bool bSearchRange;						//���G�͈͂ɓ����Ă邩�ǂ���

}Enemy;

//--------------------------------------------------------------------------------
//�v���g�^�C�v�錾
//--------------------------------------------------------------------------------
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
//void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move,int nType, int nLife, D3DXCOLOR col);
Enemy*GetEnemy(void);

#endif

