//--------------------------------------------------------------------------------
//
// �Q�[������[result.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "bg.h"
#include "player.h"
#include "enemy.h"

//--------------------------------------------------------------------------------
//�O���錾
//--------------------------------------------------------------------------------
class CBg;
class CScore;

//================================================================================
//�I�u�W�F�N�g�N���X
//================================================================================
class CResult : CScene
{

public:

	CResult();														//�R���X�g���N�^
	~CResult();														//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				//����������
	void Uninit(void);												//�I������
	void Update(void);												//�X�V����
	void Draw(void);												//�`�揈��

	static CBg*GetBg(void);											//�w�i���̌Ăяo��
	static CScore*GetScore(void) { return m_pScore; }				//�X�R�A���̌Ăяo��
	static CScore*GetGraze(void) { return m_pGraze; }				//�O���C�Y���̌Ăяo��

private:

	static CBg*m_pBg;												// �w�i�̃|�C���^
	static CScore*m_pScore;											// �X�R�A�̃|�C���^
	static CScore*m_pGraze;											// �O���C�Y�̃|�C���^

	int m_nScore = 0;												// ��b�ƂȂ�X�R�A

};

#endif



