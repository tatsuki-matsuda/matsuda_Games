//--------------------------------------------------------------------------------
//
// �Q�[������[scene2D.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "scene.h"

//--------------------------------------------------------------------------------
//�}�N����`
//--------------------------------------------------------------------------------
#define SCREEN_WIDTH		(1280)									//�X�N���[���̕�
#define SCREEN_HEIGHT		(720)									//�X�N���[���̍���
#define SCREEN_GAMEWIDTH	(830)									//�Q�[����ʒ��̃X�N���[���̕�
#define SCREEN_GAMEHEIGHT	(690)									//�Q�[����ʒ��̃X�N���[���̍���
#define SCREEN_CENTER_X		(SCREEN_WIDTH/2)						//�X�N���[�����SX���W
#define SCREEN_CENTER_Y		(SCREEN_HEIGHT/2)						//�X�N���[�����SY���W
#define SCREEN_HEIGHT_TOP	(20)									//�X�N���[��Y���W
#define MAX_TEXTURE			(5)										//�e�N�X�`���̍ő吔
#define MAX_SCENE2D			(2)										//Scene2D�̍ő吔
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//���_�t�H�[�}�b�g

//--------------------------------------------------------------------------------
//���_�t�H�[�}�b�g�ɍ��킹���\����
//--------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//1.0�ŌŒ�
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W

}VERTEX_2D;

//================================================================================
//�I�u�W�F�N�g�N���X(2D�|���S��)
//================================================================================
class CScene2D :public CScene
{
public:

	CScene2D(int nPriority = OBJTYPE_NONE);							//�R���X�g���N�^
	~CScene2D();													//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				//����������
	void Uninit(void);												//�I������
	void Update(void);												//�X�V����
	void Draw(void);												//�`�揈��
	
	static CScene2D *Create(D3DXVECTOR3 pos,D3DXVECTOR3 scale);		//�|���S���̐���

	D3DXVECTOR3 GetPosition(void);									//�ʒu�̎擾
	void SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale);			//�ʒu�̐ݒ�

	void SetBg(float ScrollBg);										//�w�i�X�N���[���̐ݒ�

	void SetLife(float PosLife);									//�̗̓A�C�R���̐ݒ�

	void SetGaugePosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale);		//�Q�[�W�̈ʒu���擾

	D3DXVECTOR3 GetScale(void) {return m_scale; }					//�X�P�[���̎擾
	void SetScale(D3DXVECTOR3 scale) { m_scale = scale; }			//�X�P�[���̐ݒ�

	void SetTex(int nCnt);											//�e�N�X�`�����W�X�V����
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);					//�e�N�X�`�����蓖�ď���

	void SetColor(D3DXCOLOR color);									//�J���[�̐ݒ�

	D3DXVECTOR3 GetMove(void) { return m_move; }					//�ړ��̎擾
	void SetMove(D3DXVECTOR3 move) { m_move = move; }				//�ړ��̐ݒ�
	
	D3DXVECTOR3 GetRot(void) { return m_rot; }						//��]�̎擾
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }					//��]�̐ݒ�

	void Length(void);												//�p�x����

private:

	static CScene2D*m_apBullet1[10];				// ��ʓ��ɂ���v���C���[�̒e�����̃|�C���^
	static CScene2D*m_apBullet2[10];				// ��ʓ��ɂ���G�̒e�����̃|�C���^
	int nCnt;										// �A�j���[�V�����p�^�[��No
	float m_fAngle;									// �p�x
	float m_fLength;								// ����
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;					// �e�N�X�`��
	D3DXVECTOR3 m_pos;								// �|���S���̈ʒu
	D3DXVECTOR3 m_move;								// �ړ�
	D3DXVECTOR3 m_scale;							// �傫��
	D3DXVECTOR3 m_rot;								// ��]

};

#endif

