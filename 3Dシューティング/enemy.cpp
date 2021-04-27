//-------------------------------------------------------------------------------
//
// �Q�[������[enemy.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include <stdio.h>
#include"Enemy.h"		//�G�̏ڍ�
#include"Player.h"		//�v���C���[�̏ڍ�
#include"bullet.h"		//�e�̏ڍ�
#include"Camera.h"		//�J�����̏ڍ�
#include"fade.h"		//�t�F�[�h�̏ڍ�
#include "xinput_gamepad.h"	//Controller�̏ڍ�

#define DEBUG (1)

//-------------------------------------------------------------------------------
//�O���[�o���ϐ�
//-------------------------------------------------------------------------------
ENEMYMODEL g_Model[MAX_ENEMY];		//���f���̏��
Enemy g_Enemy;						//�G�l�~�[�̏��
int nDeathEnemy = 0;

//-------------------------------------------------------------------------------
//����������
//-------------------------------------------------------------------------------
HRESULT InitEnemy(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���f�����̑�����ݒ�
	g_Enemy.nNumModel = MAX_ENEMY;
	
		//x�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data\\MODEL\\EnemyBoss.x", D3DXMESH_SYSTEMMEM, pDevice,
			NULL, &g_Enemy.aModel[0].BuffMatModel, NULL,
			&g_Enemy.aModel[0].nNumMat, &g_Enemy.aModel[0].MeshModel);

		D3DXLoadMeshFromX("data\\MODEL\\Enemy001.x", D3DXMESH_SYSTEMMEM, pDevice,
			NULL, &g_Enemy.aModel[1].BuffMatModel, NULL,
			&g_Enemy.aModel[1].nNumMat, &g_Enemy.aModel[1].MeshModel);

		D3DXLoadMeshFromX("data\\MODEL\\Enemy001.x", D3DXMESH_SYSTEMMEM, pDevice,
			NULL, &g_Enemy.aModel[2].BuffMatModel, NULL,
			&g_Enemy.aModel[2].nNumMat, &g_Enemy.aModel[2].MeshModel);

		D3DXLoadMeshFromX("data\\MODEL\\Enemy002.x", D3DXMESH_SYSTEMMEM, pDevice,
			NULL, &g_Enemy.aModel[3].BuffMatModel, NULL,
			&g_Enemy.aModel[3].nNumMat, &g_Enemy.aModel[3].MeshModel);

		D3DXLoadMeshFromX("data\\MODEL\\Enemy001.x", D3DXMESH_SYSTEMMEM, pDevice,
			NULL, &g_Enemy.aModel[4].BuffMatModel, NULL,
			&g_Enemy.aModel[4].nNumMat, &g_Enemy.aModel[4].MeshModel);

		D3DXLoadMeshFromX("data\\MODEL\\Enemy002.x", D3DXMESH_SYSTEMMEM, pDevice,
			NULL, &g_Enemy.aModel[5].BuffMatModel, NULL,
			&g_Enemy.aModel[5].nNumMat, &g_Enemy.aModel[5].MeshModel);

		D3DXLoadMeshFromX("data\\MODEL\\Enemy002.x", D3DXMESH_SYSTEMMEM, pDevice,
			NULL, &g_Enemy.aModel[6].BuffMatModel, NULL,
			&g_Enemy.aModel[6].nNumMat, &g_Enemy.aModel[6].MeshModel);

		D3DXLoadMeshFromX("data\\MODEL\\Enemy001.x", D3DXMESH_SYSTEMMEM, pDevice,
			NULL, &g_Enemy.aModel[7].BuffMatModel, NULL,
			&g_Enemy.aModel[7].nNumMat, &g_Enemy.aModel[7].MeshModel);

		D3DXLoadMeshFromX("data\\MODEL\\Enemy001.x", D3DXMESH_SYSTEMMEM, pDevice,
			NULL, &g_Enemy.aModel[8].BuffMatModel, NULL,
			&g_Enemy.aModel[8].nNumMat, &g_Enemy.aModel[8].MeshModel);
		
		//�{�X�̍\���ݒ�
		g_Enemy.aModel[0].nIdxModelParent = -1;
		g_Enemy.aModel[0].pos = D3DXVECTOR3(0.0, 60.0, -1000.0);
		g_Enemy.aModel[0].rot = D3DXVECTOR3(0.0, 0.0, 0.0);
		g_Enemy.aModel[0].nType = 0;
		g_Enemy.aModel[0].nEnemyLife = ENEMY_LIFEBOSS;
		g_Enemy.aModel[0].bUse = false;
		g_Enemy.aModel[0].bSearchRange = false;

		//�G�̍\���ݒ�
		g_Enemy.aModel[1].nIdxModelParent = -1;
		g_Enemy.aModel[1].pos = D3DXVECTOR3(0.0, 60.0, 0.0);
		g_Enemy.aModel[1].rot = D3DXVECTOR3(0.0, 0.0, 0.0);
		g_Enemy.aModel[1].nType = 1;
		g_Enemy.aModel[1].nEnemyLife = ENEMY_LIFE000;
		g_Enemy.aModel[1].bUse = true;
		g_Enemy.aModel[1].nCounterEnemy = false;
		g_Enemy.aModel[1].bUseStopShot = false;
		g_Enemy.aModel[1].bSearchRange = false;
		g_Enemy.aModel[1].bAppearance = false;

		g_Enemy.aModel[2].nIdxModelParent = -1;
		g_Enemy.aModel[2].pos = D3DXVECTOR3(500.0, 60.0, -1300.0);
		g_Enemy.aModel[2].rot = D3DXVECTOR3(0.0, 0.0, 0.0);
		g_Enemy.aModel[2].nType = 1;
		g_Enemy.aModel[2].nEnemyLife = ENEMY_LIFE000;
		g_Enemy.aModel[2].bUse = false;
		g_Enemy.aModel[2].nCounterEnemy = false;
		g_Enemy.aModel[2].bSearchRange = false;
		g_Enemy.aModel[2].bAppearance = false;

		g_Enemy.aModel[3].nIdxModelParent = -1;
		g_Enemy.aModel[3].pos = D3DXVECTOR3(300.0, 60.0, -700.0);
		g_Enemy.aModel[3].rot = D3DXVECTOR3(0.0, 0.0, 0.0);
		g_Enemy.aModel[3].nType = 2;
		g_Enemy.aModel[3].nEnemyLife = ENEMY_LIFE001;
		g_Enemy.aModel[3].bUse = false;
		g_Enemy.aModel[3].nCounterEnemy = false;
		g_Enemy.aModel[3].bUseStopShot = false;
		g_Enemy.aModel[3].bSearchRange = false;
		g_Enemy.aModel[3].bAppearance = false;

		g_Enemy.aModel[4].nIdxModelParent = -1;
		g_Enemy.aModel[4].pos = D3DXVECTOR3(400.0, 60.0, 500.0);
		g_Enemy.aModel[4].rot = D3DXVECTOR3(0.0, 0.0, 0.0);
		g_Enemy.aModel[4].nType = 1;
		g_Enemy.aModel[4].nEnemyLife = ENEMY_LIFE000;
		g_Enemy.aModel[4].bUse = false;
		g_Enemy.aModel[4].nCounterEnemy = false;
		g_Enemy.aModel[4].bSearchRange = false;
		g_Enemy.aModel[4].bAppearance = false;

		g_Enemy.aModel[5].nIdxModelParent = -1;
		g_Enemy.aModel[5].pos = D3DXVECTOR3(0.0, 60.0, -1800.0);
		g_Enemy.aModel[5].rot = D3DXVECTOR3(0.0, 0.0, 0.0);
		g_Enemy.aModel[5].nType = 2;
		g_Enemy.aModel[5].nEnemyLife = ENEMY_LIFE001;
		g_Enemy.aModel[5].bUse = false;
		g_Enemy.aModel[5].nCounterEnemy = false;
		g_Enemy.aModel[5].bUseStopShot = false;
		g_Enemy.aModel[5].bSearchRange = false;
		g_Enemy.aModel[5].bAppearance = false;

		g_Enemy.aModel[6].nIdxModelParent = -1;
		g_Enemy.aModel[6].pos = D3DXVECTOR3(500.0, 60.0, -800.0);
		g_Enemy.aModel[6].rot = D3DXVECTOR3(0.0, 0.0, 0.0);
		g_Enemy.aModel[6].nType = 2;
		g_Enemy.aModel[6].nEnemyLife = ENEMY_LIFE001;
		g_Enemy.aModel[6].bUse = false;
		g_Enemy.aModel[6].nCounterEnemy = false;
		g_Enemy.aModel[6].bSearchRange = false;
		g_Enemy.aModel[6].bAppearance = false;

		g_Enemy.aModel[7].nIdxModelParent = -1;
		g_Enemy.aModel[7].pos = D3DXVECTOR3(-800.0, 60.0, -200.0);
		g_Enemy.aModel[7].rot = D3DXVECTOR3(0.0, 0.0, 0.0);
		g_Enemy.aModel[7].nType = 1;
		g_Enemy.aModel[7].nEnemyLife = ENEMY_LIFE000;
		g_Enemy.aModel[7].bUse = false;
		g_Enemy.aModel[7].nCounterEnemy = false;
		g_Enemy.aModel[7].bUseStopShot = false;
		g_Enemy.aModel[7].bSearchRange = false;
		g_Enemy.aModel[7].bAppearance = false;

		g_Enemy.aModel[8].nIdxModelParent = -1;
		g_Enemy.aModel[8].pos = D3DXVECTOR3(-500.0, 60.0, 400.0);
		g_Enemy.aModel[8].rot = D3DXVECTOR3(0.0, 0.0, 0.0);
		g_Enemy.aModel[8].nType = 1;
		g_Enemy.aModel[8].nEnemyLife = ENEMY_LIFE000;
		g_Enemy.aModel[8].bUse = false;
		g_Enemy.aModel[8].nCounterEnemy = false;
		g_Enemy.aModel[8].bSearchRange = false;
		g_Enemy.aModel[8].bAppearance = false;

	return S_OK;
}

//-------------------------------------------------------------------------------
//�I������
//-------------------------------------------------------------------------------
void UninitEnemy(void)
{
	for (int nEnemy = 0; nEnemy < g_Enemy.nNumModel; nEnemy++)
	{
		//���b�V���̔j��
		if (g_Enemy.aModel[nEnemy].MeshModel != NULL)
		{
			g_Enemy.aModel[nEnemy].MeshModel->Release();
			g_Enemy.aModel[nEnemy].MeshModel = NULL;
		}

		//�}�e���A���̔j��
		if (g_Enemy.aModel[nEnemy].BuffMatModel != NULL)
		{
			g_Enemy.aModel[nEnemy].BuffMatModel->Release();
			g_Enemy.aModel[nEnemy].BuffMatModel = NULL;
		}
	}
}

//-------------------------------------------------------------------------------
//�X�V����
//-------------------------------------------------------------------------------
void UpdateEnemy(void)
{
	//�ϐ��錾
	BULLET*pBullet = GetBullet();
	CAMERA*pCamera = GetCamera();
	Player*pPlayer = GetPlayer();
	XinputGamepad*pXinputGamepad = GetXinputGamepad();

	int nLife = 120;				//�e�̃��C�t
	int nCntTime = 0;				//�G�̏o������
	int nCntDeath = 0;				//�G�̏��ŃJ�E���g
	int nCntAppearance = 0;			//�{�X�̏o���J�E���g

	//�G�̒e
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
	

				//�G1��false�̎�
		if (g_Enemy.aModel[1].bUse == false)
				{

					g_Enemy.aModel[2].bUse = true;


					if (g_Enemy.aModel[2].nEnemyLife <= 0)
					{
						g_Enemy.aModel[2].bUse = false;

						nCntAppearance = 1;

						nCntDeath = 0;
					}
					else
					{
						g_Enemy.aModel[2].bUse = true;
					}
					
				}

				//�G2��false�̎�
				if (g_Enemy.aModel[2].bUse == false && nCntAppearance == 1)
				{

					g_Enemy.aModel[3].bUse = true;

					if (g_Enemy.aModel[3].nEnemyLife <= 0)
					{
						g_Enemy.aModel[3].bUse =false;

						nCntAppearance = 2;

					}
					else
					{
						g_Enemy.aModel[3].bUse = true;
					}

					
				}

				//�G3��false�̎�
				if (g_Enemy.aModel[3].bUse == false && nCntAppearance == 2)
				{
					g_Enemy.aModel[4].bUse = true;
					g_Enemy.aModel[5].bUse = true;


					if (g_Enemy.aModel[4].nEnemyLife <= 0)
					{
						g_Enemy.aModel[4].bUse = false;
						
					}
					else
					{

						g_Enemy.aModel[4].bUse = true;
					}

					if(g_Enemy.aModel[5].nEnemyLife <= 0)
					{
						g_Enemy.aModel[5].bUse = false;

						nCntAppearance = 3;

					}
					else
					{
						
						g_Enemy.aModel[5].bUse = true;
					}

					nCntAppearance = 3;
				}

				//�G4��5��false�̎�
				if (g_Enemy.aModel[5].bUse == false && nCntAppearance == 3)
				{

					g_Enemy.aModel[6].bUse = true;
					g_Enemy.aModel[7].bUse = true;
					g_Enemy.aModel[8].bUse = true;


					if (g_Enemy.aModel[6].nEnemyLife <= 0)
					{
						g_Enemy.aModel[6].bUse = false;

						nCntAppearance = 4;
					
					}
					else
					{
						g_Enemy.aModel[6].bUse = true;
		
					}

					if (g_Enemy.aModel[7].nEnemyLife <= 0)
					{
						
						g_Enemy.aModel[7].bUse = false;

						
					}
					else
					{
					
						g_Enemy.aModel[7].bUse = true;
					}

					if (g_Enemy.aModel[8].nEnemyLife <= 0)
					{
						g_Enemy.aModel[8].bUse = false;


					}
					else
					{
						g_Enemy.aModel[8].bUse = true;

					}

					
				}

				//�G6��7��false�̎�
				if (g_Enemy.aModel[6].bUse == false && nCntAppearance == 4) 		
				{
	
					g_Enemy.aModel[0].bUse = true;
					g_Enemy.aModel[1].bUse = true;
					g_Enemy.aModel[2].bUse = true;


					if (g_Enemy.aModel[0].nEnemyLife <= 0)
					{

						g_Enemy.aModel[0].bUse = false;
						g_Enemy.aModel[1].bUse = false;

						//�{�X��|������
						SetFade(FADE_OUT, MODE_RESULT);

						pXinputGamepad->bAButton = false;

						nCntAppearance = 0;

					}
					else
					{
						g_Enemy.aModel[0].bUse = true;
						g_Enemy.aModel[1].bUse = true;
					}
					
				}

		//�G������ꍇ
		if (g_Enemy.aModel[nCntEnemy].bUse == true)
		{

			D3DXVECTOR3 VecEnemy = pPlayer->pos - g_Enemy.aModel[nCntEnemy].pos;			//�G�̃x�N�g��
			float fLengthEnemy = sqrtf(VecEnemy.x * VecEnemy.x + VecEnemy.z * VecEnemy.z);	//���@�Ƃ̋���
			float fAngleEnemy = atan2f(VecEnemy.x, VecEnemy.z);								//���@��_���p�x

			g_Enemy.aModel[nCntEnemy].rot.y += 0.005f;
			
				//�ړG
				g_Enemy.aModel[nCntEnemy].bSearchRange = true;


			//���G�͈�
			if (fLengthEnemy <= SEARCHRANGE_ENEMY)
			{
				//�ړG
				g_Enemy.aModel[nCntEnemy].bSearchRange = true;
			}

			//�ړG�����ꍇ
			if (g_Enemy.aModel[nCntEnemy].bSearchRange == true)
			{	
				//�{�X�������ꍇ
				if (g_Enemy.aModel[nCntEnemy].nType == 0)
				{
					//�{�X���L���ɂȂ��Ă����ꍇ
					if (g_Enemy.aModel[0].bUse == true)
					{
						//�ǐ�
						g_Enemy.aModel[0].pos += D3DXVECTOR3(sinf(g_Enemy.aModel[0].rot.y)*1.8f, 0.0f, cosf(g_Enemy.aModel[0].rot.y)*1.8f);
					}


					//�{�X�̒e�̔��˔͈�
					if (fLengthEnemy <= LAUNCHRANGE_BOSSBULLET)
					{
						int nCntAngle = 0;

						nCntAngle++;

						SetBullet(g_Enemy.aModel[0].pos, D3DXVECTOR3(sinf(g_Enemy.aModel[0].rot.y)*8.0f, 0.0f, cosf(g_Enemy.aModel[0].rot.y)*8.0f),
							BULLETSTATE_ENEMY, nLife, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

						SetBullet(g_Enemy.aModel[0].pos, D3DXVECTOR3(sinf(g_Enemy.aModel[0].rot.y + 1.0f)*8.0f, 0.0f, cosf(g_Enemy.aModel[0].rot.y + 1.0f)*8.0f),
							BULLETSTATE_ENEMY, nLife, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

						SetBullet(g_Enemy.aModel[0].pos, D3DXVECTOR3(sinf(g_Enemy.aModel[0].rot.y + 2.0f)*8.0f, 0.0f, cosf(g_Enemy.aModel[0].rot.y + 2.0f)*8.0f),
							BULLETSTATE_ENEMY, nLife, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

						SetBullet(g_Enemy.aModel[0].pos, D3DXVECTOR3(sinf(g_Enemy.aModel[0].rot.y + 3.0f)*8.0f, 0.0f, cosf(g_Enemy.aModel[0].rot.y + 3.0f)*8.0f),
							BULLETSTATE_ENEMY, nLife, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

						SetBullet(g_Enemy.aModel[0].pos, D3DXVECTOR3(sinf(g_Enemy.aModel[0].rot.y + 4.0f)*8.0f, 0.0f, cosf(g_Enemy.aModel[0].rot.y + 4.0f)*8.0f),
							BULLETSTATE_ENEMY, nLife, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

						SetBullet(g_Enemy.aModel[0].pos, D3DXVECTOR3(sinf(g_Enemy.aModel[0].rot.y + 5.0f)*8.0f, 0.0f, cosf(g_Enemy.aModel[0].rot.y + 5.0f)*8.0f),
							BULLETSTATE_ENEMY, nLife, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					}
				}

				

				//�Ԃ��G�������ꍇ
				if (g_Enemy.aModel[nCntEnemy].nType == 1)
				{
					//���G��~�͈͂ɓ������ꍇ
					if (fLengthEnemy <= SEARCHSTOP_ENEMY)
					{
						//���˃J�E���g��L��
						g_Enemy.aModel[nCntEnemy].bUseStopShot = true;

					}
					else
					{
						//���˃J�E���g�������̏ꍇ
						if (g_Enemy.aModel[nCntEnemy].bUseStopShot == false)
						{
							//�ǐ�
							g_Enemy.aModel[nCntEnemy].pos += D3DXVECTOR3(sinf(fAngleEnemy)*8.0f, 0.0f, cosf(fAngleEnemy)*5.0f);
						}
					}

					//���G��~�͈͓��̏���
					if (g_Enemy.aModel[nCntEnemy].bUseStopShot == true)
					{
						//��莞�Ԓ�~
						g_Enemy.aModel[nCntEnemy].pos += D3DXVECTOR3(sinf(fAngleEnemy)*0.0f, 0.0f, cosf(fAngleEnemy)*0.0f);

						//���˂܂ł̃J�E���g���J�n
						g_Enemy.aModel[nCntEnemy].nCounterShot++;
					}


					//���˃J�E���g�����l�ȏ�̏ꍇ
					if (g_Enemy.aModel[nCntEnemy].nCounterShot >= 35)
					{
						//�e�̊Ǘ�
						SetBullet(g_Enemy.aModel[nCntEnemy].pos, D3DXVECTOR3(D3DXVECTOR3(sinf(fAngleEnemy)*1.5f, 0.0f, cosf(fAngleEnemy)*1.5f)),
							BULLETSTATE_ENEMY, nLife, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

					}

					//��莞�Ԓ�~��y�є��˃J�E���g�����l�ȏ�̏ꍇ
					if (g_Enemy.aModel[nCntEnemy].nCounterShot >= 180)
					{
						//���˃J�E���g�̃��Z�b�g
						g_Enemy.aModel[nCntEnemy].nCounterShot = 0;

						//���˃J�E���g�𖳌���
						g_Enemy.aModel[nCntEnemy].bUseStopShot = false;

					}
				}

				//���̓G�������ꍇ
				if (g_Enemy.aModel[nCntEnemy].nType == 2)
				{
					//�ǐ�
					g_Enemy.aModel[nCntEnemy].pos += D3DXVECTOR3(sinf(fAngleEnemy)*2.5f, 0.0f, cosf(fAngleEnemy)*2.5f);

					//�e�̔��˔͈�
					if (fLengthEnemy <= LAUNCHRANGE_BULLET)
					{
						int nCntAngle = 0;

						nCntAngle++;

						//�e�̔���
						SetBullet(g_Enemy.aModel[nCntEnemy].pos, D3DXVECTOR3(sinf(g_Enemy.aModel[nCntEnemy].rot.y *6.0f)*5.0f, 0.0f, cosf(g_Enemy.aModel[nCntEnemy].rot.y*6.0f)*8.0f),
						BULLETSTATE_ENEMY, nLife, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

						//SetBullet(g_Enemy.aModel[nCntEnemy].pos, D3DXVECTOR3(sinf(fAngleEnemy+1.2f)*12.0f, 0.0f, cosf(fAngleEnemy+1.2f)*12.0f),
						//BULLETSTATE_ENEMY, nLife, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

					}
				}
			}



				//�G�̗̑͂�0�ȉ��ɂȂ����ꍇ
				if (g_Enemy.aModel[1].nEnemyLife <= 0)
				{
					//�G����                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
					g_Enemy.aModel[1].bUse = false;

				}
				else
				{
					//�G����
					g_Enemy.aModel[1].bUse = true;
				}


			
			
			//����
			g_Enemy.aModel[nCntEnemy].move.x += (0.0f - g_Enemy.aModel[nCntEnemy].move.x)*0.1f;
			g_Enemy.aModel[nCntEnemy].move.z += (0.0f - g_Enemy.aModel[nCntEnemy].move.z)*0.1f;

			//�ړ�����
			g_Enemy.aModel[nCntEnemy].pos.x += g_Enemy.aModel[nCntEnemy].move.x;
			g_Enemy.aModel[nCntEnemy].pos.y += g_Enemy.aModel[nCntEnemy].move.y;
			g_Enemy.aModel[nCntEnemy].pos.z += g_Enemy.aModel[nCntEnemy].move.z;

		}

	}

}

//-------------------------------------------------------------------------------
//�`�揈��
//-------------------------------------------------------------------------------
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;					//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;							//���݂̃}�e���A�����g�p
	D3DXMATERIAL*pMat;								//

	//�}�e���A���f�[�^�ւ̃|�C���^
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy.aModel[nCntEnemy].bUse == true)
		{
			//�e���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Enemy.aModel[nCntEnemy].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy.aModel[nCntEnemy].rot.y, g_Enemy.aModel[nCntEnemy].rot.x, g_Enemy.aModel[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_Enemy.aModel[nCntEnemy].mtxWorld, &g_Enemy.aModel[nCntEnemy].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Enemy.aModel[nCntEnemy].pos.x, g_Enemy.aModel[nCntEnemy].pos.y, g_Enemy.aModel[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_Enemy.aModel[nCntEnemy].mtxWorld, &g_Enemy.aModel[nCntEnemy].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy.aModel[nCntEnemy].mtxWorld);

			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Enemy.aModel[nCntEnemy].BuffMatModel->GetBufferPointer();

			for (int nCntcolor = 0; nCntcolor < (int)g_Enemy.aModel[nCntEnemy].nNumMat; nCntcolor++)
			{
				//�}�e���A����ݒ�
				pDevice->SetMaterial(&pMat[nCntcolor].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);

				//���f��(�p�[�c)�̕`��
				g_Enemy.aModel[nCntEnemy].MeshModel->DrawSubset(nCntcolor);
			}

			//�ۑ����Ă����}�e���A����Ԃ�
			pDevice->SetMaterial(&matDef);

		}
	}
}

////-------------------------------------------------------------------------------
////�G�̐ݒ�
////-------------------------------------------------------------------------------
//void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType,int nLife, D3DXCOLOR col)
//{
//	//�ϐ��錾
//	Enemy*pEnemy = &g_Enemy;
//
//	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy, pEnemy++)
//	{
//		//�e���g�p���Ă���ꍇ
//		if (pEnemy->bUse == false)
//		{
//
//			//�ʒu��ݒ�
//			pEnemy->pos = pos;
//
//			//�ړ��ʂ�ݒ�
//			pEnemy->move = move;
//
//			//�ړ��ʂ�ݒ�
//			pEnemy->nType = nType;
//
//			//������ݒ�
//			pEnemy->nLife = nLife;
//
//			//�e���g�p���Ă��Ȃ��ꍇ
//			pEnemy->bUse = true;
//
//			break;
//		}
//	}
//}

//-------------------------------------------------------------------------------
//���_���W�̐ݒ�
//-------------------------------------------------------------------------------
Enemy *GetEnemy(void)
{
	return &g_Enemy;
}