//--------------------------------------------------------------------------------
//
// �Q�[������[item.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _ITEM_H_
#define _ITEM_H_

#include "scene2D.h"

//--------------------------------------------------------------------------------
//�}�N����`
//--------------------------------------------------------------------------------
#define ITEM_MOVE_X		(3)										//�A�C�e����X���ړ�
#define ITEM_MOVE_Y		(10)									//�A�C�e����Y���ړ�

//--------------------------------------------------------------------------------
//�O���錾
//--------------------------------------------------------------------------------
class CBullet;

//================================================================================
//�I�u�W�F�N�g�N���X(�G)
//================================================================================
class CItem :public CScene2D
{
public:

	//�A�C�e�����
	typedef enum
	{
		ITEMTYPE_NONE = 0,
		ITEMTYPE_1UP,
		ITEMTYPE_BOMB,
		ITEMTYPE_POWERUP,
		ITEMTYPE_MAX

	}ITEMTYPE;

	CItem(int nPriority = OBJTYPE_ITEM);							//�R���X�g���N�^
	~CItem();														//�f�X�g���N�^

	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,
		D3DXVECTOR3 move, ITEMTYPE itemType);						//�A�C�e���̐���

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale
		, D3DXVECTOR3 move);										//����������
	void Uninit(void);												//�I������
	void Update(void);												//�X�V����
	void Draw(void);												//�`�揈��

	static HRESULT Load(void);										//�ǂݍ��ݏ���
	static void Unload(void);										//�j������

	ITEMTYPE GetItemType(void) { return m_ItemType; }				//�A�C�e�����̎擾
	void SetItemType(ITEMTYPE itemType) { m_ItemType = itemType; }	//�A�C�e�����

private:

	void OnDiffuesPos(D3DXVECTOR3 pos, D3DXVECTOR3 move);			// �A�C�e���̐����ʒu����

	ITEMTYPE m_ItemType;											// �A�C�e���̎��

	bool m_bUninit;													// �I�����菈��

	int	 m_nItemCnt;												// �A�C�e���o���J�E���g
	int	 m_nItemmoveCnt;											// �A�C�e���ړ��J�E���g
	int	 m_nCntTime;												// �Ԋu
	int	 m_timer;													// �o�ߎ���

	float m_angle;													// �p�x

	static D3DXVECTOR3 m_Craetepos[10];								// �������̍��W��ݒ�
	D3DXVECTOR3 m_posDeath;											// ���ł����Ƃ��̈ʒu��ۑ�
	D3DXVECTOR3 m_move;												// �ړ�
	D3DXVECTOR3 m_scale;											// �傫��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;						// ���_�o�b�t�@�̃|�C���^

	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];											//	�e�N�X�`��
	CScene2D*m_apScene2D[MAX_SCENE2D];															//	CScene2D�̃|�C���^
};
#endif