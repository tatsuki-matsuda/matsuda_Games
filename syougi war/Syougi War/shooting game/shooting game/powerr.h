//--------------------------------------------------------------------------------
//
// �Q�[������[power.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _POWER_H_
#define _POWER_H_

#include "scene2D.h"

//--------------------------------------------------------------------------------
//�}�N����`
//--------------------------------------------------------------------------------
#define MAX_ITEM				(2)									//�A�C�e���̍ő��

//--------------------------------------------------------------------------------
//�O���錾
//--------------------------------------------------------------------------------
class CEnemy;

//================================================================================
//�I�u�W�F�N�g�N���X(�G)
//================================================================================
class CItem :public CScene2D
{
public:


	//�G�̏��
	typedef enum
	{
		ITEM_NONE = 0,
		ITEM_NORMAL,															//�ʏ�A�C�e��
		ITEM_MAX

	}ITEM;

	CItem(int nPriority = OBJTYPE_ITEM);										//�R���X�g���N�^
	~CItem();																	//�f�X�g���N�^

	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,
		D3DXVECTOR3 move);														//�A�C�e���̐���

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale,
		D3DXVECTOR3 move);														//����������
	void Uninit(void);															//�I������
	void Update(void);															//�X�V����
	void Draw(void);															//�`�揈��

	static void Load(void);														//�ǂݍ��ݏ���
	static void Unload(void);													//�j������

	void EnemyState(void);														//�G�̏��

	static LPDIRECT3DTEXTURE9  GetTexture(int nCntTex);							//�e�N�X�`�����̎擾

	ITEM GetEnemyState(void) { return m_Item; }									//�A�C�e�����̎擾
	void SetEnemyState(ITEM item) { m_Item = item; }							//�A�C�e�����

	int GetLife(void) { return m_nLife; }										//�̗͏��̎擾
	void SetLife(int nLife) { m_nLife = nLife; }								//�̗͏��


private:

	ITEM	m_Item;																// �G�̏��

	bool m_bUninit;																// �I�����菈��

	int	 m_nEnemyAppearanceCnt;													// �G�o���J�E���g
	int	 m_nEnemyCnt;															// �G���ŃJ�E���g
	int	 m_nEnemyTime;															// �o���J�E���g	 
	int	 m_nPlayerCnt = 0;														// �v���C���[���Ō�J�E���g
	int	 m_nEnemymoveCnt;														// �G�ړ��J�E���g
	int	 m_nBulletStartCnt;														// �����n�߃J�E���g
	int	 m_nCntCrossingTime;													// �����Ԋu�J�E���g
	int	 m_nCntTime;															// ���ˊԊu
	int	 m_nCntMadness;															// �����J�E���g
	int	 m_nNormalEnemyMove;													// �ʏ�G�ړ��J�E���g
	int  m_nCntColor;															// �F�̐؂�ւ��Ԋu
	int  m_nCntBullet;															// ���˃J�E���g
	int	 m_timer;																// ���ˎ���
	int  m_nLife;																// �̗�		
	int	 m_nMaxLife;															// �o�����̗̑�

	float m_fangle;																// �p�x
	float m_fLength;															// ����

	static D3DXVECTOR3 m_Craetepos[10];											// �������̍��W��ݒ�
	D3DXVECTOR3 m_posBoss;														// �{�X�̈ʒu��ۑ�
	D3DXVECTOR3 m_posDeath;														// ���ł����Ƃ��̈ʒu��ۑ�
	D3DXVECTOR3 m_moveSave;														// �ړ��l��ۑ�
	D3DXVECTOR3 m_move;															// �ړ�
	D3DXVECTOR3 m_scale;														// �傫��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;									// ���_�o�b�t�@�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];							// �e�N�X�`��
	D3DXCOLOR m_Color;															// �J���[
};
#endif
