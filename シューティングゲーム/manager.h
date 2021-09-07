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
class CPlayer;
class CEnemy;
class CBullet;
class CBg;
class CTitle;
class CGame;

//================================================================================
//�I�u�W�F�N�g�N���X
//================================================================================
class CManager
{

public:

	typedef enum
	{
		MODE_TITLE = 0,
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
	static void SetMode(Mode mode);
	static Mode GetMode(void) { return m_Mode; }						//���[�h�̎擾

private:

	static CTitle*m_pTitle;
	static CGame*m_pGame;
	//static CResult*m_pResult;
	static Mode m_Mode;
	static CRenderer*m_pRenderer;										// Renerer�̃|�C���^
	static CInputKeyBoard*m_pInputKeyBoard;								// �L�[�{�[�h�̃|�C���^

};

//--------------------------------------------------------------------------------
//�v���g�^�C�v�錾
//--------------------------------------------------------------------------------
#endif
