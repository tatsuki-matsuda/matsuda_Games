//--------------------------------------------------------------------------------
//
// �Q�[������[lifegauge.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _LIFEGAUGE_H_
#define _LIFEGAUGE_H_

#include "scene2D.h"

//--------------------------------------------------------------------------------
//�}�N����`
//--------------------------------------------------------------------------------
#define LIFUGAUGE_Y		(5)										//�Q�[�W�̏c��
#define GAUGEBASE_X		(700)									//�Q�[�W�̍ő剡��
#define GAUGEUP_X		(5)										//���Q�[�W�̑�������l

//--------------------------------------------------------------------------------
//�O���錾
//--------------------------------------------------------------------------------
class CEnemy;

//================================================================================
//�I�u�W�F�N�g�N���X(�Q�[�W)
//================================================================================
class CLifeGauge : public CScene
{
public:

	CLifeGauge(int nPriority = OBJTYPE_UI);												//�R���X�g���N�^
	~CLifeGauge();																		//�f�X�g���N�^

	static CLifeGauge *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,int nBaseLife);		//�̗̓Q�[�W�̐���

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);					//����������
	void Uninit(void);																	//�I������
	void Update(void);																	//�X�V����
	void Draw(void);																	//�`�揈��

	void OnDiffuse(int nDiffuseLife);													//�Q�[�W�k������
	void OnGaugeUp(void);																//�Q�[�W��������

	bool GetGaugeUp(void) { return m_bGaugeUp; }										//�Q�[�W�����������̌Ăяo��
	void SetGaugeUp(bool bGaugeUp) { m_bGaugeUp = bGaugeUp; }							//�Q�[�W�����������̎擾

	int GetBaseLife(void) { return m_nBaseLife; }										//�x�[�X�̗̑͒l���̌Ăяo��
	void SetBaseLife(int nBaseLife) { m_nBaseLife = nBaseLife; }						//�x�[�X�̗̑͒l���̎擾

	D3DXVECTOR3 GetPos(void) { return m_pos; }											//�ʒu���̌Ăяo��
	D3DXVECTOR3 GetScale(void) { return m_scale; }										//�傫�����̌Ăяo��
	void SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale);								//�ꏊ���̎擾

private:

	bool m_bUninit;																		// �I�����菈��
	bool m_bGaugeUp;																	// �Q�[�W��������

	int	 m_nCntTime;																	// �Ԋu
	int	 m_timer;																		// ����
	int  m_nLife;																		// ���݂̗̑͒l
	int  m_nBaseLife;																	// ��b�ƂȂ�̗͒l
	int  m_nSaveLife;																	// �ۑ�����̗͒l

	D3DXVECTOR3 m_scale;																// �傫��
	D3DXVECTOR3 m_pos;																	// �ʒu
	D3DXVECTOR3 m_Scale_move;															// �ړ��l
	D3DXVECTOR3 m_BaseScale;															// ��b�ƂȂ�傫��
	D3DXVECTOR3 m_BasePos;																// ��b�ƂȂ�ʒu
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;											// ���_�o�b�t�@�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture;												// �e�N�X�`��
};
#endif
