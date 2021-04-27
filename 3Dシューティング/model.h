//--------------------------------------------------------------------------------
//
// �Q�[������[Model.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"
#include "input.h"

//--------------------------------------------------------------------------------
//���f���̍\����
//--------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;			//���݂̈ʒu
	D3DXVECTOR3 posDest;		//�ړI�̈ʒu
	D3DXVECTOR3 rot;			//���݂̌���
	D3DXVECTOR3 rotDest;		//�ړI�̌���
}MODEL;

//--------------------------------------------------------------------------------
//�v���g�^�C�v�錾
//--------------------------------------------------------------------------------
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
MODEL*GetModel(void);
//bool HitPoligon(void);
#endif


