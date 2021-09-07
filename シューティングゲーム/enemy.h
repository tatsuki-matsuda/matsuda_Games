//--------------------------------------------------------------------------------
//
// �Q�[������[enemy.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "scene2D.h"

//--------------------------------------------------------------------------------
//�}�N����`
//--------------------------------------------------------------------------------
#define ENEMY				(2)										//�G�̐�
#define ENEMY_LIFE			(1500)									//�G�̃��C�t
#define ENEMY_MOVE_X		(3)										//�G��X���ړ�
#define ENEMY_MOVE_Y		(10)									//�G��Y���ړ�
#define N_WAY_CREATE		(5)										//n_way�e�̐�����

//--------------------------------------------------------------------------------
//�O���錾
//--------------------------------------------------------------------------------
class CBullet;
class CLifeGauge;

//================================================================================
//�I�u�W�F�N�g�N���X(�G)
//================================================================================
class CEnemy :public CScene2D
{
public:

	//�U����ޕ���
	typedef enum
	{
		ENEMYTYPE_NONE = 0,
		ENEMYTYPE_NORMAL1,				//�ʏ�e1�����G
		ENEMYTYPE_NORMAL2,				//�ʏ�e2�����G
		ENEMYTYPE_NORMAL3_R,			//�E������ʏ�e3�����G
		ENEMYTYPE_NORMAL3_L,			//��������ʏ�e3�����G
		ENEMYTYPE_NORMAL4,				//�ʏ�e4�����G
		ENEMYTYPE_NORMAL5,				//�ʏ�e5�����G
		ENEMYTYPE_HOMING,				//�Ǐ]�e�����G
		ENEMYTYPE_CROSSING,				//�����e�����G
		ENEMYTYPE_REFLECTION,			//���˒e�����G
		ENEMYTYPE_REFLECTION_UPDAWN,	//�㉺���˒e�����G
		ENEMYTYPE_TURN,					//�܂�Ԃ��e�����G
		ENEMYTYPE_N_WAY1,				//n_way�e1�����G
		ENEMYTYPE_N_WAY2,				//n_way�e2�����G
		ENEMYTYPE_MAX

	}ENEMYTYPE;

	CEnemy(int nPriority = OBJTYPE_ENEMY);							//�R���X�g���N�^
	~CEnemy();														//�f�X�g���N�^

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,
		D3DXVECTOR3 move, ENEMYTYPE enemyType);						//�G�̐���

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale
		, D3DXVECTOR3 move);										//����������
	void Uninit(void);												//�I������
	void Update(void);												//�X�V����
	void Draw(void);												//�`�揈��

	static void Load(void);											//�ǂݍ��ݏ���
	static void Unload(void);										//�j������

	static LPDIRECT3DTEXTURE9  GetTexture(int nCntTex);				//�e�N�X�`�����̎擾

	ENEMYTYPE GetEnemyType(void);									//�G���̎擾
	void SetEnemyType(ENEMYTYPE enemyType);							//�G���

	int GetLife(void) { return m_nLife; }
	void SetLife(int nLife) { m_nLife = nLife; }

	int GetMaxLife(void) { return m_nMaxLife; }
	void SetMaxLife(int nMaxlife) { m_nMaxLife = nMaxlife; }

	CLifeGauge *GetLifeGauge(void) { return m_pLifeGauge; }

private:

	void OnDiffuesPos(D3DXVECTOR3 pos, D3DXVECTOR3 move);			//	�e�̐����ʒu����

	ENEMYTYPE m_EnemyType;											// �G�̎��

	bool m_bUninit;													// �I�����菈��

	int	 m_nEnemyAppearanceCnt;										// �G�o���J�E���g
	int	 m_nEnemyCnt;												// �G���ŃJ�E���g
	int	 m_nEnemyTime;												// �o���J�E���g	 

	int	 m_nEnemymoveCnt;											// �G�ړ��J�E���g
	int	 m_nBulletStartCnt;											// �����n�߃J�E���g
	int	 m_nCntCrossingTime;										// �����Ԋu�J�E���g
	int	 m_nCntTime;												// ���ˊԊu
	int	 m_timer;													// ���ˎ���
	int  m_nLife;													// �̗�		
	int	 m_nMaxLife;												// �o�����̗̑�

	float m_angle;													// �p�x

	static D3DXVECTOR3 m_Craetepos[10];								// �������̍��W��ݒ�
	D3DXVECTOR3 m_posDeath;											// ���ł����Ƃ��̈ʒu��ۑ�
	D3DXVECTOR3 m_move;												// �ړ�
	D3DXVECTOR3 m_scale;											// �傫��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;						// ���_�o�b�t�@�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];				//	�e�N�X�`��

	CLifeGauge *m_pLifeGauge;										// �Q�[�W�̃|�C���^
};
#endif