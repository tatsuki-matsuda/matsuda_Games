//--------------------------------------------------------------------------------
//
// �Q�[������[score.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _LIFEBOSS_H_
#define _LIFEBOSS_H_

#include "scene.h"
#include "number.h"

//--------------------------------------------------------------------------------
//�}�N����`
//--------------------------------------------------------------------------------
#define MAX_DIGIT      (8)
#define MAX_BOSSLIFE   (3)
//================================================================================
//�I�u�W�F�N�g�N���X
//================================================================================
class CLifeBoss : public CScene
{

public:
	typedef enum
	{
		LIFETYPE_NORMAL = 0,
		LIFETYPE_BOSS,
		LIFETYPE_MAX

	}LIFETYPE;

	CLifeBoss(int nPriority = OBJTYPE_UI);								//�R���X�g���N�^
	~CLifeBoss();														//�f�X�g���N�^

	static CLifeBoss *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, LIFETYPE lifecount);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);					//����������
	void Uninit(void);													//�I������
	void Update(void);													//�X�V����
	void Draw(void);													//�`�揈��

	void SetLifeCnt(int nlifecnt);										//���C�t�J�E���g���
	void SetLifeType(LIFETYPE lifeType) { m_LifeType= lifeType; }		//���C�t�^�C�v���

	void AddBossLifeCnt(int nValue);									//�{�X���C�t�J�E���g����

private:

	LIFETYPE m_LifeType;												// ���C�t�̎��
	CNumber *m_apNumber[8];												// ��ʓ��̎c�e��
	int m_nDigit;														// ����
	int m_nLifeCnt;														// ���C�t�J�E���g
	D3DXVECTOR3 m_pos;													// �ʒu
	D3DXVECTOR3 m_scale;												// �傫��
};

#endif
