//--------------------------------------------------------------------------------
//
// �Q�[������[MeshField.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
#include "main.h"
#include "input.h"

//--------------------------------------------------------------------------------
//���b�V���t�B�[���h�̍\����
//--------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//����
}MESHFIELD;

//--------------------------------------------------------------------------------
//�v���g�^�C�v�錾
//--------------------------------------------------------------------------------
HRESULT InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);
MESHFIELD*GetMeshField(void);
//bool HitPoligon(void);
#endif

