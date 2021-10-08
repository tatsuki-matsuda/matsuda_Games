//--------------------------------------------------------------------------------
//
// �Q�[������[score.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _SCORE_H_
#define _SCORE_H_

#include "scene.h"
#include "number.h"

//--------------------------------------------------------------------------------
//�}�N����`
//--------------------------------------------------------------------------------
#define MAX_DIGIT      (8)
//================================================================================
//�I�u�W�F�N�g�N���X
//================================================================================
class CScore : public CScene
{

public:
	typedef enum
	{
		SCORETYPE_NORMAL=0,
		SCORETYPE_GRAZE,
		SCORETYPE_MAX

	}SCORETYPE;

	CScore(int nPriority = OBJTYPE_UI);									//�R���X�g���N�^
	~CScore();															//�f�X�g���N�^

	static CScore *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, SCORETYPE scoretype);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);					//����������
	void Uninit(void);													//�I������
	void Update(void);													//�X�V����
	void Draw(void);													//�`�揈��

	void SetScore(int nScore);											//�X�R�A���
	void SetScoreType(SCORETYPE scoretype);								//�X�R�A�^�C�v���

	void AddScore(int nValue);											//�X�R�A����
	void AddGraze(int nValue);											//�O���C�Y����

	int GetScore(void) { return m_nScore; }								//�X�R�A���Z

private:

	SCORETYPE m_ScoreType;												// �X�R�A�^�C�v
	CNumber *m_apNumber[8];
	int m_nDigit;														// ����
	int m_nScore;														// �X�R�A
	D3DXVECTOR3 m_pos;													// �ʒu
	D3DXVECTOR3 m_scale;												// �傫��
};

#endif

