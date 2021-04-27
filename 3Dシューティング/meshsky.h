//--------------------------------------------------------------------------------
//
// �Q�[������[Meshsky.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _MESHSKY_H_
#define _MESHSKY_H_
#include "main.h"
#include "input.h"

//--------------------------------------------------------------------------------
//���b�V���X�J�C�̍\����
//--------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//����
}MESHSKY;

//--------------------------------------------------------------------------------
//�v���g�^�C�v�錾
//--------------------------------------------------------------------------------
HRESULT InitMeshSky(void);
void UninitMeshSky(void);
void UpdateMeshSky(void);
void DrawMeshSky(void);
MESHSKY*GetMeshSky(void);
//bool HitPoligon(void);
#endif

