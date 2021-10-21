//--------------------------------------------------------------------------------
//
// �Q�[������[logo.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _LOGO_H_
#define _LOGO_H_

#include "scene2D.h"

//--------------------------------------------------------------------------------
//�}�N����`
//--------------------------------------------------------------------------------
#define MAX_GAMELOGO			(2)									//�Q�[�����Ŏg���郍�S�̍ő吔
#define MAX_LOGO				(5)									//���S�̍ő吔

//================================================================================
//�I�u�W�F�N�g�N���X(���S)
//================================================================================
class CLogo :public CScene
{
public:

	//�e���蕪��
	typedef enum
	{
		LOGOTYPE_NONE = 0,
		LOGOTYPE_START,												//�X�^�[�g
		LOGOTYPE_KYOUSYA,											//����
		LOGOTYPE_MAX						    

	}LOGOTYPE;

	CLogo(int nPriority = OBJTYPE_LOGO);							//�R���X�g���N�^
	~CLogo();														//�f�X�g���N�^

	static CLogo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,
		LOGOTYPE logoType);											//���S�̐���

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				//����������
	void Uninit(void);												//�I������
	void Update(void);												//�X�V����
	void Draw(void);												//�`�揈��

	static HRESULT Load(void);										//�ǂݍ��ݏ���
	static void Unload(void);										//�j������

	LOGOTYPE GetInfoType(void) { return m_LogoType; }				//���S�^�C�v���̌Ăяo��
	void SetInfoType(LOGOTYPE logoType) {m_LogoType = logoType;}	//�U�����̎擾

private:

	LOGOTYPE m_LogoType;											//  ���S�^�C�v

	bool m_bEnter;													//  �G���^�[�����������ǂ���
	bool m_bGame;													//  �Q�[����ʂɈړ����邩�ǂ���
	int m_nTimeColor;												//	�J���[�^�C�}�[
	int m_nTimer;													//	�^�C�}�[

	D3DXVECTOR3 m_scale;											//	�傫��
	D3DXVECTOR3 m_move;												//	�ړ��l
	D3DXCOLOR	m_Color;											//	�F
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_LOGO];				//	�e�N�X�`��
	CScene2D*m_apScene2D[5];										//	CScene2D�̃|�C���^
};
#endif
