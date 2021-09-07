//--------------------------------------------------------------------------------
//
// �Q�[������[scene.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//--------------------------------------------------------------------------------
//�}�N����`
//--------------------------------------------------------------------------------
#define MAX_POLYGON	(512)												//�|���S���̍ő�\����


//================================================================================
//�I�u�W�F�N�g�N���X
//================================================================================
class CScene
{

public:

	//��ޕ���
	typedef enum
	{
		OBJTYPE_NONE = 0,		
		OBJTYPE_BG,					//�w�i
		OBJTYPE_EFFECT,				//�G�t�F�N�g
		OBJTYPE_EXPLOSION,			//����
		OBJTYPE_ENEMY,				//�G
		OBJTYPE_PLAYER,				//�v���C���[
		OBJTYPE_ITEM,				//�A�C�e��
		OBJTYPE_BULLET,				//�e
		OBJTYPE_GAME,				
		OBJTYPE_UI,
		OBJTYPE_MAX

	}OBJTYPE;

	CScene(int nPriority = OBJTYPE_PLAYER);								//�R���X�g���N�^
	virtual ~CScene();													//�f�X�g���N�^

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale) = 0;		//����������
	virtual void Uninit(void) = 0;										//�I������
	virtual void Update(void) = 0;										//�X�V����
	virtual void Draw(void) = 0;										//�`�揈��
	void LifeSub(int nPow);												//�̗͌��Z����

	static void ReleaseAll(void);										//�J������
	static void UpdateAll(void);										//�X�V����
	static void DrawAll(void);											//�`�揈��

	static CScene *GetScene(int nCntPriority,int nCntScene);			//Scene�̎擾
	OBJTYPE GetObjType(void);											//��ޏ��̎擾

	void SetObjType(OBJTYPE objType);									//��ޏ��

protected:

	void Release(void);													//�J������

private:

	OBJTYPE m_objType;													// �I�u�W�F�N�g�̎��

	LPDIRECT3DTEXTURE9 m_pTexture;										// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;							// ���_�o�b�t�@�̃|�C���^

	D3DXVECTOR3 m_pos;													// �ʒu
	D3DXVECTOR3 m_scale;												// �傫��

	static CScene*m_apScene[OBJTYPE_MAX][MAX_POLYGON];					// �|���S���̐�
	static int m_nNumAll;												// �ő吔

	int m_nPriority;													// �D�揇�ʂ̔ԍ�
	int m_nID;															// �i�[��ԍ�
	int m_nLife;														// �̗�
};

#endif
