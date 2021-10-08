//--------------------------------------------------------------------------------
//
// �Q�[������[game.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "bg.h"
#include "game_screen.h"
#include "pause.h"
#include "player.h"
#include "enemy.h"

//--------------------------------------------------------------------------------
//�O���錾
//--------------------------------------------------------------------------------
class CScore;
class CPlayer;
class CExplosion;
class CEnemy;
class CBullet;
class CBg;
class CPause;
class CGame_Screen;
class CLife;
class CSound;

//--------------------------------------------------------------------------------
//�}�N����`
//--------------------------------------------------------------------------------
#define ENEMY_RESPAWNTIME (300)

//================================================================================
//�I�u�W�F�N�g�N���X
//================================================================================
class CGame : CScene
{

public:
	// �J�ڏ���
	typedef enum
	{
		TRANSITION_NONE = 0,
		TRANSITION_RESULT,
		TRANSITION_MAX,
	}Transition;

	CGame();																			//�R���X�g���N�^
	~CGame();																			//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);									//����������
	void Uninit(void);																	//�I������
	void Update(void);																	//�X�V����
	void Draw(void);																	//�`�揈��

	static CBullet*GetBullet(void);														//�e���̌Ăяo��
	static CExplosion*GetExplosion(void);												//�������̌Ăяo��
	static CBg*GetBg(void);																//�w�i���̌Ăяo��
	static CGame_Screen*GetGame_Screen(void);											//�Q�[���w�i���̌Ăяo��
	static CPlayer*GetPlayer(void);														//�v���C���[���̌Ăяo��
	static CEnemy*GetEnemy(void);														//�G���̌Ăяo��
	static CScore*GetScore(void);														//�X�R�A���̌Ăяo��
	static CScore*GetGraze(void);														//�O���C�Y���̌Ăяo��
	static CScore*GetBulletNum(void);

	static CLife*GetLife(void);															//���C�t�̏����Ăяo��
	static CPause*GetPause(void) { return m_pPause; }									//�|�[�Y���̌Ăяo��

	static Transition GetTransision(void) { return m_transition; }						//�Q�[�����̑J�ڏ�Ԃ̏����Ăяo��
	static void SetTransition(Transition transition) { m_transition = transition; }		//�Q�[�����̑J�ڏ�Ԃ̏�� 

private:

	static CBullet*m_pBullet;										// �e
	static CExplosion*m_pExplosion;									// ����
	static CBg*m_pBg;												// �w�i
	static CGame_Screen*m_pGame_Screen;								// �Q�[���w�i
	static CPlayer*m_pPlayer;										// �v���C���[
	static CEnemy*m_pEnemy;											// �G
	static CScore*m_pGraze;											// �O���C�Y
	static CScore*m_pScore;											// �X�R�A
	static CScore*m_pBulletNum;
	static CLife*m_pLife;											// ���C�t
	static CPause*m_pPause;											// �|�[�Y
	static Transition m_transition;									// �Q�[�����̑J��
	static CSound*m_pSound;											// BGM

	int m_nEnemyTime;												// �G�̏o���J�E���g
	static int m_nCntResult;										// ���U���g�J�ڃJ�E���g
};

#endif

