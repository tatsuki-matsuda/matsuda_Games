//--------------------------------------------------------------------------------
//
// �Q�[������[manager.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _MANAGER_H_
#define _MANAGER_H_

//--------------------------------------------------------------------------------
//�}�N����`
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
//�O���錾
//--------------------------------------------------------------------------------
class CRenderer;
class CInputKeyBoard;
class CFade;
class CPlayer;
class CEnemy;
class CScore;
class CBullet;
class CPause;
class CBg;
class CTitle;
class CTutorial;
class CResult;
class CGame;
class CSound;

//================================================================================
//�I�u�W�F�N�g�N���X
//================================================================================
class CManager
{

public:

	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	}Mode;

	CManager();															//�R���X�g���N�^
	~CManager();														//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance,HWND hWnd, BOOL bWindow);			//����������
	void Uninit(void);													//�I������
	void Update(void);													//�X�V����
	void Draw(void);													//�`�揈��

	static CRenderer *GetRenderer(void);								//Renderer�N���X�̏��
	static CInputKeyBoard*GetInputKeyBoard(void);						//���͏��
	static CFade*GetFade(void) { return m_pFade; }						//�t�F�[�h���

	static void SetMode(Mode mode);
	static Mode GetMode(void) { return m_Mode; }						//���[�h�̎擾

	static void SetPause(void);											//�|�[�Y�̎擾
	static void SetPause(bool pause) { m_bPause = pause; }				//�|�[�Y�̎擾�����邩�ǂ���
	static bool GetPause(void) { return m_bPause; }						//�|�[�Y�̏��

	static void SetScore(int savescore) { m_nSaveScore = savescore; }	//�X�R�A�ۑ��̎擾
	static int GetScore(void) { return m_nSaveScore; }					//�X�R�A�ۑ����

	static void SetSound(CSound*sound) { m_pSound = sound; }			//�T�E���h�̎擾
	static CSound*GetSound(void) { return m_pSound; }					//�T�E���h�̏��

private:

	static CTitle*m_pTitle;												// �^�C�g���̃|�C���^
	static CTutorial*m_pTutorial;										// �`���[�g���A���̃|�C���^
	static CGame*m_pGame;												// �Q�[���̃|�C���^
	static CResult*m_pResult;											// ���U���g�̃|�C���^
	static Mode m_Mode;													// ���[�h�̃|�C���^
	static CFade*m_pFade;												// �t�F�[�h�̃|�C���^
	static CRenderer*m_pRenderer;										// Renerer�̃|�C���^
	static CInputKeyBoard*m_pInputKeyBoard;								// �L�[�{�[�h�̃|�C���^
	static CSound*m_pSound;												// BGM

	static int m_nSaveScore;											// �X�R�A��ۑ�����ϐ�
	static bool m_bPause;												// �|�[�Y�����ǂ���

};

//--------------------------------------------------------------------------------
//�v���g�^�C�v�錾
//--------------------------------------------------------------------------------
#endif
