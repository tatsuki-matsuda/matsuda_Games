//=============================================================================
//
// ���C������ [player.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "sound.h"
#include "bullet.h"
#include "normal_bullet.h"
#include "scene2D.h"
#include "score.h"
#include "manager.h"
#include "renderer.h"
#include "dinput_keyboard.h"
#include "life.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;			// �e�N�X�`��

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CPlayer::CPlayer(int nPriority):CScene2D(nPriority)
{
	m_timer = 0;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CPlayer::~CPlayer()
{

}

//*****************************************************************************
// ��������
//*****************************************************************************
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//���I�m��
	CPlayer* pPlayer;
	pPlayer = new CPlayer;

	//�����̌Ăяo��
	pPlayer->Init(pos, scale);

	//�e�N�X�`������
	pPlayer->BindTexture(m_pTexture);

	//�l��Ԃ�
	return pPlayer;
}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�傫����ݒ�
	m_scale = scale;

	//���
	SetObjType(OBJTYPE_PLAYER);

	//�������̌Ăяo��
	CScene2D::Init(pos,scale);

	//��ԕω��J�E���g
	m_nCntNormal = 0;

	//�v���C���[�̐F
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���Ő؂�ւ��Ԋu
	m_nDeathColor = 0;

	//��ԕω����̈ړ��J�E���g
	m_nCntStateMove = 0;

	//�o���J�E���g
	m_nCntStart = 0;

	//��e�������ǂ���
	m_bState = false;
	
	//�v���C���[�̏��
	SetPlayerState(PLAYERSTATE_REVIVAL);

	//�l��Ԃ�
	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CPlayer::Uninit(void)
{
	//�I���̌Ăяo��
	CScene2D::Uninit();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CPlayer::Update(void)
{
	//�L�[�{�[�h���̎擾
	CInputKeyBoard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyBoard();

	//�T�E���h�̃|�C���^
	CSound *pSound = CManager::GetSound();

	//�ʒu�̎擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	CScore *pScore;
	pScore = CGame::GetScore();

	//�ړ��ʂ�ǉ�
	pos += m_move;

	//�Ίp���̒���
	m_angle = sqrtf(30 * 30 + 30 * 30);

	//�Ίp���̊p�x
	float fAngle = atan2f(5, 5);

	//���
	PlayerState();

	//�v���C���[�̏�Ԃ��ʏ��Ԃ̏ꍇ
	if (m_PlayerState == PLAYERSTATE_NORMAL)
	{
		m_nCntStateMove = 1;

	}

	//�v���C���[�̏�Ԃ��ʏ��Ԃ̏ꍇ
	if (m_PlayerState != PLAYERSTATE_DEATH&&m_nCntStateMove >= 1)
	{
		//��L�[�������ꍇ
		if (pInputKeyboard->GetPress(DIK_UP) == true)
		{
			//��ړ�
			pos.y -= 8;
	
			if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
			{//�E�΂�
				pos.x -= sinf(D3DX_PI / 2) * 2;
				pos.y -= cosf(D3DX_PI / 1) * 1;

			}
			else if (pInputKeyboard->GetPress(DIK_LEFT) == true)
			{//���΂�
				pos.x -= sinf(D3DX_PI / 2) * -2;
				pos.y -= cosf(D3DX_PI / 1) * 1;
			}

			//�ᑬ�ړ�
			if (pInputKeyboard->GetPress(DIK_LSHIFT) == true)
			{
				//��������
				pos.y += 5;
			}
		}

		//���L�[�������ꍇ
		if (pInputKeyboard->GetPress(DIK_DOWN) == true)
		{
			//���ړ�
			pos.y += 8;

			
			if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
			{//�E�΂�
				pos.x -= sinf(D3DX_PI / 2) * 2;
				pos.y += cosf(D3DX_PI / 1) * 1;

			}
			else if (pInputKeyboard->GetPress(DIK_LEFT) == true)
			{//���΂�
				pos.x -= sinf(D3DX_PI / 2) * -2;
				pos.y += cosf(D3DX_PI / 1) * 1;
			}

			//�ᑬ�ړ�
			if (pInputKeyboard->GetPress(DIK_LSHIFT) == true)
			{
				//��������
				pos.y -= 5;
			}
		}

		//�E�L�[�������ꍇ
		if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
		{
			//�E�ړ�
			pos.x += 8;

			//�ᑬ�ړ�
			if (pInputKeyboard->GetPress(DIK_LSHIFT) == true)
			{
				//��������
				pos.x -= 5;
			}
		}

		//���L�[�������ꍇ
		if (pInputKeyboard->GetPress(DIK_LEFT) == true)
		{
			//���ړ�
			pos.x -= 8;

			//�ᑬ�ړ�
			if (pInputKeyboard->GetPress(DIK_LSHIFT) == true)
			{
				//��������
				pos.x += 5;
			}
		}

		//�e�𔭎�
		if (pInputKeyboard->GetPress(DIK_Z) == true)
		{
			m_timer++;

			if (pInputKeyboard->GetPress(DIK_LSHIFT) == true)
			{//�ᑬ�ړ����̔���
				if (m_timer % 6 == 0)
				{
					//�e�̐���
					CBullet::Create(D3DXVECTOR3(pos.x + 20, pos.y - 30, pos.z), D3DXVECTOR3(15, 15, 0), D3DXVECTOR3(0, -8, 0),
						D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_PLAYER, CBullet::ATTACKTYPE_HOMING, CBullet::INFOTYPE_1);

					//�e�̐���
					CBullet::Create(D3DXVECTOR3(pos.x - 20, pos.y - 30, pos.z), D3DXVECTOR3(15, 15, 0), D3DXVECTOR3(0, -8, 0),
						D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_PLAYER, CBullet::ATTACKTYPE_HOMING, CBullet::INFOTYPE_1);

					//�e�̐���
					CBullet::Create(D3DXVECTOR3(pos.x, pos.y - 40, pos.z), D3DXVECTOR3(15, 15, 0), D3DXVECTOR3(0, -8, 0),
						D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_PLAYER, CBullet::ATTACKTYPE_HOMING, CBullet::INFOTYPE_1);

					//���̐���
					pSound->PlaySoundA(CSound::SOUND_LABEL_SE_SHOT);

				
				}
			}
			else if (m_timer % 6 == 0)
			{//�ʏ�ړ����̔���

				//�e�̐���
				CNormal_Bullet::Create(D3DXVECTOR3(pos.x + 20, pos.y - 40, pos.z), D3DXVECTOR3(15, 15, 0), D3DXVECTOR3(0, -10, 0),
					D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_PLAYER, CBullet::ATTACKTYPE_NORMAL, CBullet::INFOTYPE_1);

				//�e�̐���
				CBullet::Create(D3DXVECTOR3(pos.x, pos.y - 40, pos.z), D3DXVECTOR3(15, 15, 0), D3DXVECTOR3(0, -8, 0),
					D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_PLAYER, CBullet::ATTACKTYPE_HOMING, CBullet::INFOTYPE_1);

				//�e�̐���
				CNormal_Bullet::Create(D3DXVECTOR3(pos.x - 20, pos.y - 40, pos.z), D3DXVECTOR3(15, 15, 0), D3DXVECTOR3(0, -10, 0),
					D3DXVECTOR3(0, 0, 0), CBullet::BULLETTYPE_PLAYER, CBullet::ATTACKTYPE_NORMAL, CBullet::INFOTYPE_1);

				//���̐���
				pSound->PlaySoundA(CSound::SOUND_LABEL_SE_SHOT);

			}
		}

		m_nCntBomb++;

		if (m_nCntBomb >= 220)
		{
			//�{��
			if (pInputKeyboard->GetTrigger(DIK_X) == true)
			{

				m_nCntBomb = 0;

				m_nCntUse -= 1;

				m_timer++;

				if (m_nCntUse >= 0)
				{
					for (int nCnt = 0; nCnt < 8; nCnt++)
					{
						//�{���̐���
						CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(100, 100, 0),
							D3DXVECTOR3(sinf(D3DX_PI * 5.0f * ((float)nCnt / (float)20)) * 6, cosf(D3DX_PI * 5.0f * ((float)nCnt / (float)20)) * 6, 0),
							D3DXVECTOR3(0, (float)nCnt, 0), CBullet::BULLETTYPE_PLAYER, CBullet::ATTACKTYPE_BOMB, CBullet::INFOTYPE_1);
					}

					//for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
					//{
					//	//Scene�Ăяo��
					//	CScene*pScene;
					//	pScene = CScene::GetScene(OBJTYPE_BULLET, nCntScene);

					//	if (pScene != NULL)
					//	{
					//		//��ޔ���Ăяo��
					//		CScene::OBJTYPE objType;
					//		objType = pScene->GetObjType();

					//		if (objType != NULL)
					//		{
					//			//�I�u�W�F�N�g�̏�񂪒e�������ꍇ
					//			if (objType == OBJTYPE_BULLET)
					//			{
					//				//scene��e�̏��ւƍĒ�`
					//				CBullet*pBullet;
					//				pBullet = (CBullet*)pScene;

					//				//�e�̎�ޏ����擾
					//				CBullet::BULLETTYPE bulletType;
					//				bulletType = pBullet->GetBulletType();


					//				//�G�̒e�������ꍇ
					//				if (bulletType == CBullet::BULLETTYPE_ENEMY)
					//				{
					//					//�e�̏����擾
					//					bool bulletUninit;
					//					bulletUninit = pBullet->GetUninit();

					//					//�e��������
					//					if (bulletUninit == false)
					//					{
					//						//�e�̍��W���擾
					//						D3DXVECTOR3 bulletPos;
					//						bulletPos = pBullet->GetPosition();

					//						//�p�x�v�Z
					//						float VectorX = bulletPos.x - pos.x;
					//						float VectorY = bulletPos.y - pos.y;
					//						float fLength = sqrtf(VectorX*VectorX + VectorY*VectorY);

					//						//���l�ɓ������ꍇ
					//						if (fLength <= 280)
					//						{
					//							//�e������L���ɂ���
					//							bulletUninit = true;

					//							//�e�������̌Ăяo��
					//							pBullet->SetUninit(bulletUninit);
					//						}


					//					}
					//				}
					//			}
					//		}
					//	}
					//}
				}
			}
		}

		//y���̉�ʒ[��ɍs���ꍇ
		if (pos.y - m_scale.y / 2.0f < PLAYER_MOVE_HEIGHT_TOP)
		{
			pos.y = PLAYER_MOVE_HEIGHT_TOP + m_scale.y / 2.0f;
		}

		//y���̉�ʒ[���ɍs���ꍇ
		if (pos.y + m_scale.y / 2.0f > PLAYER_MOVE_HEIGHT)
		{
			pos.y = PLAYER_MOVE_HEIGHT - m_scale.y / 2.0f;
		}

		//x���̉�ʒ[�E�ɍs���ꍇ
		if (pos.x - m_scale.x / 2.0f < PLAYER_MOVE_WIDTH_TOP)
		{
			pos.x = PLAYER_MOVE_WIDTH_TOP + m_scale.x / 2.0f;
		}

		//x���̉�ʒ[���ɍs���ꍇ
		if (pos.x + m_scale.x / 2.0f > PLAYER_MOVE_WIDTH)
		{
			pos.x = PLAYER_MOVE_WIDTH - m_scale.x / 2.0f;
		}

		//�O���C�Y����
		CollisionGraze();
	}

	//�������
	if (m_PlayerState == PLAYERSTATE_DEATH&&m_nCntStateMove > 60)
	{
		//�ʒu�̎w��
		pos = D3DXVECTOR3(420.0f, 620.0f, 0.0f);

		//�v���C���[�̏�Ԃ𕜊���Ԃ�
		m_PlayerState = PLAYERSTATE_REVIVAL;
	}

	//�������
	if (m_PlayerState == PLAYERSTATE_REVIVAL&&m_nCntStateMove == 0)
	{
		//�ړ��l��^����
		pos.y += -0.8f;
	}
	
	//�ʒu�̍X�V
	SetPosition(pos, m_scale);

}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CPlayer::Draw(void)
{
	//�`��̌Ăяo��
	CScene2D::Draw();
}

//*****************************************************************************
// �O���C�Y���菈��
//*****************************************************************************
void CPlayer::CollisionGraze(void)
{
	//�ʒu�̎擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		//Scene�Ăяo��
		CScene*pScene;
		pScene = CScene::GetScene(OBJTYPE_BULLET,nCntScene);

		if (pScene != NULL)
		{
			//��ޔ���Ăяo��
			CScene::OBJTYPE objType;
			objType = pScene->GetObjType();

			if (objType != NULL)
			{
				//�I�u�W�F�N�g�̏�񂪒e�������ꍇ
				if (objType == OBJTYPE_BULLET)
				{
					//scene��e�̏��ւƍĒ�`
					CBullet*pBullet;
					pBullet = (CBullet*)pScene;

					//�e�̎�ޏ����擾
					CBullet::BULLETTYPE bulletType;
					bulletType = pBullet->GetBulletType();

					//�G�̒e�������ꍇ
					if (bulletType == CBullet::BULLETTYPE_ENEMY)
					{
						//�e�̍��W���擾
						D3DXVECTOR3 bulletPos;
						bulletPos = pBullet->GetPosition();

						//�O���C�Y������̎擾
						bool bGraze;
						bGraze = pBullet->GetGraze();

						//�O���C�Y���Ăяo��
						CScore *pScore;
						pScore = CGame::GetGraze();

						//�p�x�v�Z
						float VectorX = bulletPos.x - pos.x;
						float VectorY = bulletPos.y - pos.y;
						float fLength = sqrtf(VectorX*VectorX + VectorY*VectorY);


						//���l�ɓ������ꍇ
						if (fLength <= 40)
						{	
							//�O���C�Y�̔��肪�s���Ă��Ȃ��ꍇ
							if (bGraze == false)
							{
								//�O���C�Y���Z
								pScore->AddGraze(1);

								//�O���C�Y�̔�����s��
								bGraze = true;

								//�T�E���h�̃|�C���^
								CSound *pSound = CManager::GetSound();

								//������
								pSound->PlaySoundA(CSound::SOUND_LABEL_SE_GRAZE);

								//�O���C�Y����
								pBullet->SetGraze(bGraze);
							}
						}
					}
				}
			}
		}
	}
}

//*****************************************************************************
// �e�N�X�`���ǂݍ��ݏ���
//*****************************************************************************
void CPlayer::Load(void)
{
	//�f�o�C�X�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\player001.png", &m_pTexture);
}

//*****************************************************************************
// �e�N�X�`���j������
//*****************************************************************************
void CPlayer::Unload(void)
{
	//�e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//*****************************************************************************
// �v���C���[�̏��
//*****************************************************************************
void CPlayer::PlayerState(void)
{
	//�T�E���h�̃|�C���^
	CSound *pSound = CManager::GetSound();

	//�ʒu�̎擾
	D3DXVECTOR3 pos;
	pos = GetPosition();
	int nLife = CGame::GetLife()->GetLife();

	switch (GetPlayerState())
	{
		//�ʏ��Ԃ������ꍇ
	case PLAYERSTATE_NORMAL:

		//�F
		m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		break;

		//���S��Ԃ������ꍇ
	case PLAYERSTATE_DEATH:

		//�F�̐؂�ւ��Ԋu
		m_nCntColor++;

		//��ԕω����̈ړ��J�E���g
		m_nCntStateMove++;

		//���ŕω��J�E���g�����l�𒴂���܂Œl���J�E���g
		if (m_nDeathColor < 100)
		{
			//���ŕω��J�E���g
			m_nDeathColor++;
		}

		//���X�ɐF��ω�
		m_Color = D3DXCOLOR(1.0f, 0.5f, 0.5f, (1.0f / ((float)m_nDeathColor*0.25f)));

		//�J�E���g�����l������Atrasition_Result��ԂɂȂ��Ă��Ȃ��ꍇ
		if (m_nCntColor % 100 == 0 && CGame::GetTransision() != CGame::TRANSITION_RESULT)
		{

			//�F�̐؂�ւ��Ԋu
			m_nCntColor = 0;
		}

		break;

		//������Ԃ������ꍇ
	case PLAYERSTATE_REVIVAL:

		//�F�̐؂�ւ��Ԋu
		m_nCntColor++;

		m_nCntUse = 3;

		//���Ő؂�ւ��Ԋu
		m_nDeathColor = 0;

		//�J�E���g�����l��0�ɂȂ�x�ɐF��ω�
		if (m_nCntColor % 7 == 0)
		{
			//�F
			m_Color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.2f);
		}
		else
		{
			//�F
			m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		//�J�E���g�����l��0�ɂȂ�ƃv���C���[�̏�ԁA�J�E���g�̒l��ς���
		if (m_nCntColor % 150 == 0)
		{

			//���
			m_PlayerState = PLAYERSTATE_NORMAL;

			//��ԕω����̈ړ��J�E���g
			m_nCntStateMove = 0;

			//�F�̐؂�ւ��J�E���g
			m_nCntColor = 0;

		}

	break;

	default:
		break;
	}

	//�F���̌Ăяo��
	SetColor(m_Color);
}
