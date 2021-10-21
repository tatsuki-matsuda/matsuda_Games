//--------------------------------------------------------------------------------
//
// �Q�[������[sceneX.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _SCENEX_H_
#define _SCENEX_H_

#include "main.h"
#include "input.h"
#include "scene.h"

//================================================================================
//�I�u�W�F�N�g�N���X(�w�i)
//================================================================================
class CSceneX :public CScene
{
public:

	CSceneX(int nPriority = OBJTYPE_UI);
	~CSceneX();

	static CSceneX *Create(D3DXVECTOR3 pos);							//�V�[���̐���

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);					//����������
	void Uninit(void);													//�I������
	void Update(void);													//�X�V����
	void Draw(void);													//�`�揈��

private:

	D3DXVECTOR3	m_rotmove;

	LPDIRECT3D9 m_apTextureModel[100] = {};		//�e�N�X�`���ւ̃|�C���^
	LPD3DXMESH m_pMeshModel;					//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMatModel;				//�}�e���A��(�ގ����)�ւ̃|�C���^
	D3DXVECTOR3 m_posModel;						//�ʒu
	D3DXVECTOR3 m_rotModel;						//����
	D3DXMATRIX  m_mtxWorldModel;				//���[���h�}�g���b�N�X
	DWORD m_nNumMatModel;						//�}�e���A���̐�
};
#endif