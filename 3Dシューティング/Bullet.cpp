//-------------------------------------------------------------------------------
//
// �Q�[������[bullet.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include "xinput_gamepad.h"
#include "model.h"
#include "fade.h"

//-------------------------------------------------------------------------------
//�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			//�e�N�X�`�����
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posBullet;							//�ʒu
D3DXMATRIX  g_mtxWorldBullet;						//���[���h�}�g���b�N�X
BULLET g_aBullet[MAX_BULLET];						//�e�̏��

//-------------------------------------------------------------------------------
//����������
//-------------------------------------------------------------------------------
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	BULLET*pBullet = GetBullet();				//�e�̏��

	//�ϐ��錾
	VERTEX_3D *pVtx;

	//�e�̏�����
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�e�̈ʒu
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�e�̈ړ�
		g_aBullet[nCntBullet].nLife = 0;								//�e�̗̑�
		g_aBullet[nCntBullet].nType = 0;								//�e�̎��
		//g_aBullet[nCntBullet].nCnt = 0;
		g_aBullet[nCntBullet].bUse = false;								//�e���g�p���Ă��Ȃ��ꍇ
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_pTextureBullet);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(pBullet->pos.x - 10.0f,pBullet->pos.y + 10.0f, pBullet->pos.z );
		pVtx[1].pos = D3DXVECTOR3(pBullet->pos.x + 10.0f,pBullet->pos.y + 10.0f, pBullet->pos.z );
		pVtx[2].pos = D3DXVECTOR3(pBullet->pos.x - 10.0f,pBullet->pos.y - 10.0f, pBullet->pos.z );
		pVtx[3].pos = D3DXVECTOR3(pBullet->pos.x + 10.0f,pBullet->pos.y - 10.0f, pBullet->pos.z );

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_���W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 4;
	}

	g_pVtxBuffBullet->Unlock();
	return S_OK;
}

//-------------------------------------------------------------------------------
//�I������
//-------------------------------------------------------------------------------
void UninitBullet(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
}
//-------------------------------------------------------------------------------
//�X�V����
//-------------------------------------------------------------------------------
void UpdateBullet(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();				//�f�o�C�X�̎擾
	BULLET*pBullet = &g_aBullet[0];							//�e�̏��
	Player*pPlayer = GetPlayer();							//�v���C���[�̏��
	Enemy*pEnemy = GetEnemy();								//�G�̏��
	XinputGamepad*pXinputGamepad = GetXinputGamepad();		//�Q�[���p�b�h�̏��
	MODEL*pModel = GetModel();								//���f���̏��
	VERTEX_3D *pVtx;
	
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);	

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{

			if (pBullet->bUse == true)//�e���g���Ă��邩�ǂ���
			{	
				//�e�̈ړ�����
				pBullet->pos.x += pBullet->move.x;
				pBullet->pos.z += pBullet->move.z;
				pBullet->pos.y += pBullet->move.y;

				//�e�̗̑͌�������
				pBullet->nLife--;

				//���@�̒e�̏ꍇ
				if (pBullet->State == BULLETSTATE_PLAYER)
				{
					for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
					{
						//�G������ꍇ
						pBullet->fRadius = 10.0f;
						pEnemy->fRadius = 10.0f;

						D3DXVECTOR3 VecRadius = pEnemy->aModel[nCntEnemy].pos - pBullet->pos;		//�e�ƓG�̍��W����

						float fLength = sqrtf(VecRadius.x * VecRadius.x + VecRadius.z * VecRadius.z);	//���@�Ƃ̋���		

						//���@�e�ƓG�̓����蔻��
						if (fLength < pBullet->fRadius + pEnemy->fRadius)
						{
							//�ڐG����
							pBullet->bUse = false;

							pEnemy->aModel[nCntEnemy].nEnemyLife--;
						}
						
					}
		
				}


				//�G�̒e�������ꍇ
				if (pBullet->State == BULLETSTATE_ENEMY)
				{
					pBullet->fRadius = 10.0f;
					pPlayer->fRadius = 10.0f;

					D3DXVECTOR3 VecRadius = pBullet->pos - pPlayer->pos;		    //�e�ƓG�̍��W����

					float fLength = sqrtf(VecRadius.x * VecRadius.x + VecRadius.z * VecRadius.z);	//���@�Ƃ̋���		

					//���@�e�ƓG�̓����蔻��
					if (fLength < pBullet->fRadius + pPlayer->fRadius)
					{
						//�ڐG����
						pBullet->bUse = false;

						pPlayer->bUse = false;

						pXinputGamepad->bAButton = false;

						//AButton���������ꍇ
						SetFade(FADE_OUT, MODE_GAMEOVER);
						



					}

				}
		
			//�e�̃��C�t��0�ȉ��ɂȂ����ꍇ
			if (pBullet->nLife <= 0)
			{
				pBullet->bUse = false;
			}
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//-------------------------------------------------------------------------------
//�`�揈��
//-------------------------------------------------------------------------------
void DrawBullet(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X���
	D3DXMATRIX mtxView;							//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxTrans;						//�v�Z�p�}�g���b�N�X

	//�f�o�C�X�̎擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�A���t�@�e�X�g�̗L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//�A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�A���t�@�l�̎Q��
	pDevice->SetRenderState(D3DRS_ALPHAREF,100 );
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_mtxWorldBullet);

		//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
		D3DXMatrixInverse(&g_mtxWorldBullet, NULL, &mtxView);	//�t�s������߂�

		g_mtxWorldBullet._41 = 0.0f;
		g_mtxWorldBullet._42 = 0.0f;
		g_mtxWorldBullet._43 = 0.0f;

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
		D3DXMatrixMultiply(&g_mtxWorldBullet, &g_mtxWorldBullet, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBullet);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBullet);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}

	//�A���t�@�e�X�g�̗L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//�A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);

	//�A���t�@�l�̎Q��
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}

//-------------------------------------------------------------------------------
//�e�̐ݒ�
//-------------------------------------------------------------------------------
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETSTATE state, int nLife, D3DXCOLOR col)
{
	//�ϐ��錾
	BULLET*pBullet = &g_aBullet[0];

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet, pBullet++)
	{
		//�e���g�p���Ă���ꍇ
		if (pBullet->bUse == false)
		{

			//�ʒu��ݒ�
   			pBullet->pos = pos;

			//�ړ��ʂ�ݒ�
			pBullet->move = move;

			//�e�̏��
			pBullet->State = state;

			////�e�̎��
			//pBullet->nType = nType;

			//������ݒ�
			pBullet->nLife = nLife;

			//�e���g�p���Ă��Ȃ��ꍇ
			pBullet->bUse = true;

			break;
		}
	}
}

//-------------------------------------------------------------------------------
//���_���W�̐ݒ�
//-------------------------------------------------------------------------------
void SetVertexBullet(int nIdx)
{
	////�ϐ��錾
	//VERTEX_3D*pVtx;
	//BULLET*pBullet;

	//pBullet = GetBullet();
	//pBullet += nIdx;
	//int nDamage = 0;

	////���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	//g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	//pVtx += nIdx * 4;

	//if (pBullet->nType == 1)
	//{//�ᑬ���̒e
	//	nDamage = 5;

	//	//���_���W�̐ݒ�
	//	pVtx[0].pos = D3DXVECTOR3(-30 + g_aBullet[nIdx].pos.x, 30 + g_aBullet[nIdx].pos.y, 0.0);
	//	pVtx[1].pos = D3DXVECTOR3(-30 + g_aBullet[nIdx].pos.x, -30 + g_aBullet[nIdx].pos.y, 0.0);
	//	pVtx[2].pos = D3DXVECTOR3(30 + g_aBullet[nIdx].pos.x, 30 + g_aBullet[nIdx].pos.y, 0.0);
	//	pVtx[3].pos = D3DXVECTOR3(30 + g_aBullet[nIdx].pos.x, -30 + g_aBullet[nIdx].pos.y, 0.0);
	//}
	//else if (pBullet->nType == 0)
	//{//�ʏ펞�̒e
	//	nDamage = 1;

	//	//���_���W�̐ݒ�
	//	pVtx[0].pos = D3DXVECTOR3(-10 + g_aBullet[nIdx].pos.x, 10 + g_aBullet[nIdx].pos.y, 0.0);
	//	pVtx[1].pos = D3DXVECTOR3(-10 + g_aBullet[nIdx].pos.x, -10 + g_aBullet[nIdx].pos.y, 0.0);
	//	pVtx[2].pos = D3DXVECTOR3(10 + g_aBullet[nIdx].pos.x, 10 + g_aBullet[nIdx].pos.y, 0.0);
	//	pVtx[3].pos = D3DXVECTOR3(10 + g_aBullet[nIdx].pos.x, -10 + g_aBullet[nIdx].pos.y, 0.0);
	//}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//-------------------------------------------------------------------------------
//�e�̏��
//-------------------------------------------------------------------------------
BULLET*GetBullet(void)
{
	//�e�̏��
	return &g_aBullet[0];
}