//--------------------------------------------------------------------------------
//
// �Q�[������[bullet.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//-------------------------------------------------------------------------------
//�}�N����`
//-------------------------------------------------------------------------------
#define MAX_BULLET (2560)

//-------------------------------------------------------------------------------
//�e�̏��
//-------------------------------------------------------------------------------
typedef enum
{
	BULLETSTATE_PLAYER = 0,	//���@�e
	BULLETSTATE_ENEMY,		//�G�e
	BULLETSTATE_FALSE,		//����
	BULLETSTATE_MAX

}BULLETSTATE;

//-------------------------------------------------------------------------------
//�\���̂̐錾
//-------------------------------------------------------------------------------
typedef struct
{
	BULLETSTATE State;			//���
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 move;			//�ړ���
	float fRadius;
	int nType;					//�e�̐؂�ւ�
	int nLife;					//����
	int nCnt;
	bool bUse;					//�g�p���Ă��邩�ǂ���
}BULLET;

//--------------------------------------------------------------------------------
//�v���g�^�C�v�錾
//--------------------------------------------------------------------------------
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETSTATE state, int nLife, D3DXCOLOR col);
void SetVertexBullet(int nIdx);
BULLET*GetBullet(void);
#endif
