//--------------------------------------------------------------------------------
//
// �Q�[������[game.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "manager.h"
#include "polygon.h"

//--------------------------------------------------------------------------------
//�O���錾
//--------------------------------------------------------------------------------
class CPolygon;

//--------------------------------------------------------------------------------
//�}�N����`
//--------------------------------------------------------------------------------
#define SCREEN_WIDTH		(1280)									//�X�N���[���̕�
#define SCREEN_HEIGHT		(720)									//�X�N���[���̍���
#define SCREEN_GAMEWIDTH	(830)									//�Q�[����ʒ��̃X�N���[���̕�
#define SCREEN_GAMEHEIGHT	(690)									//�Q�[����ʒ��̃X�N���[���̍���
#define SCREEN_CENTER_X		(SCREEN_WIDTH/2)						//�X�N���[�����SX���W
#define SCREEN_CENTER_Y		(SCREEN_HEIGHT/2)						//�X�N���[�����SY���W

//================================================================================
//�I�u�W�F�N�g�N���X
//================================================================================
class CFade
{

public:

	//�t�F�[�h���
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX

	}FADE;

	CFade();														//�R���X�g���N�^
	~CFade();														//�f�X�g���N�^

	static CFade *Create(void);										//�t�F�[�h�̐���
	static HRESULT Init(void);										//����������
	static void Uninit(void);										//�I������
	static void Update(void);										//�X�V����
	static void Draw(void);											//�`�揈��

	static void SetFade(FADE fade, CManager::Mode modenext);		//�t�F�[�h���̎擾
	static FADE GetFade(void) { return m_Fade; }					//�t�F�[�h���̌Ăяo��

private:

	static FADE m_Fade;												// �t�F�[�h
	static CPolygon *m_pPolygon;									// �Q�[�W�̃|�C���^
	static CManager::Mode m_ModeNext;								// ���̃��[�h��
	static D3DXCOLOR m_Color;										// �J���[

};

#endif

