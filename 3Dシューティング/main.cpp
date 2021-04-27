//------------------------------------------------------------------------------ -
//
// �Q�[������[main.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include"main.h"
#include"camera.h"			//�J�����̕\��
#include"polygon.h"			//�|���S���̕\��
#include"meshfield.h"		//���b�V���t�B�[���h�̕\��
#include"wall.h"			//�ǂ̕\��
#include"billboard.h"		//�r���{�[�h�̕\��
#include"bullet.h"			//�e�̕\��
#include"light.h"			//���C�g�̕\��
#include"model.h"			//���f���̕\��
#include"player.h"			//�v���C���[�̕\��
#include"input.h"			//���͂̕\��
#include"xinput_gamepad.h"	//Controller�̕\��
#include"stdio.h"			//
#include"title.h"			//�^�C�g����ʂ̕\��
#include"tutorial.h"		//�`���[�g���A����ʂ̕\��
#include"game.h"			//�Q�[����ʂ̕\��
#include"gameover.h"			//�Q�[���I�[�o�[��ʂ̕\��
#include"result.h"			//���U���g��ʂ̕\��
#include"fade.h"			//�t�F�[�h�̕\��

//-------------------------------------------------------------------------------
//�}�N����`
//-------------------------------------------------------------------------------
#define ID_BUTTON000   (101)	//�{�^��000��ID
#define WINDOW_POS_X   (200)	//�E�B���h�E�̍����X���W
#define WINDOW_POS_Y   (220)	//�E�B���h�E�̍����Y���W
#define ID_TIMER	   (121)	//�^�C�}�[��ID
#define	TIMER_INTERVAL (1000/60)//�^�C�}�[�����Ԋu(�~���b)

//-------------------------------------------------------------------------------
//�v���g�^�C�v�錾
//-------------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWind, BOOL bWindow);
void UnInit(void);
void UpDate(void);
void Draw(void);
void DrawFPS(void);
void DrawTXT(void);

//-------------------------------------------------------------------------------
//�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3D9 g_pD3D = NULL;						//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;			//Direct3D�f�o�C�X�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL;						//�t�H���g�ւ̃|�C���^
int g_nCountFPS;								//FPS�J�E���^
MODE g_mode = MODE_TITLE;

//-------------------------------------------------------------------------------
//���C���֐�
//-------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		"Project",
		LoadIcon(NULL,IDI_APPLICATION)
	};
	HWND hWnd;//�E�B���h�E�n���h��
	MSG msg;  //���b�Z�[�W���i�[����

    //�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	RECT rect{ 0,0,SCREEN_WIDTH ,SCREEN_HEIGHT };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, TRUE);

	//�E�B���h�E�̍쐬
	hWnd = CreateWindowEx(
		0,
		"Project",
		"BULLET War",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	dwExecLastTime = timeGetTime();
	dwFPSLastTime = timeGetTime();
	dwCurrentTime = timeGetTime();//���ݎ�����ݒ�
	dwFrameCount = 0;

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)//���b�Z�[�W���擾���Ȃ������ꍇ"0"��Ԃ�
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			if ((dwCurrentTime-dwExecLastTime)>(1000/60))
			{
				//���
				dwExecLastTime = dwCurrentTime;

				//�X�V����
				UpDate();

				//�`�揈��
				Draw();

				//�t���[���J�E���g
				dwFrameCount++;
			}
		}
	}

	//�I������
	UnInit();

	//�E�B���h�E�̓o�^����
	UnregisterClass("Project", wcex.hInstance);
	return (int)msg.wParam;
}

//-------------------------------------------------------------------------------
//�E�B���h�E�v���V�[�W��
//-------------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//�ϐ��錾
	int nID;

	switch (uMsg)
	{//�I����

	case WM_DESTROY:
		PostQuitMessage(0);//WM_QUIT���b�Z�[�W��Ԃ�
		break;

	case WM_CLOSE:
		nID = MessageBox(NULL, "�I�����܂����H", "���b�Z�[�W", MB_YESNO | MB_ICONQUESTION);
		if (nID == IDYES)
		{//YES�̏ꍇ
			DestroyWindow(hWnd);
		}
		else if (nID == IDNO)
		{//NO�̏ꍇ
			return 0;

		}
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{//ESC�������ꍇ
		case VK_ESCAPE:

				DestroyWindow(hWnd);

			break;
		}
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}
//-------------------------------------------------------------------------------
//����������
//-------------------------------------------------------------------------------
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;


	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//�f�B�X�v���C���[�h�̎擾
	if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval= D3DPRESENT_INTERVAL_DEFAULT;

	//Direct3D�f�o�C�X�̐���
	if (FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);			//�J�����O�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);			//���u�����h(���l�̍���)�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);		//�\�[�X(�`�挳)�̍������@�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);//�f�X�e�B�l�[�V����(�`���)�̍������@�̐ݒ�

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�����̕\��
	D3DXCreateFont(g_pD3DDevice, 30, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,"Terminal", &g_pFont);

	//���͂̏���������
	InitKeyBoard(hInstance, hWnd);


	//�t�F�[�h�̏���������
	InitFade(g_mode);

	//���[�h�̐ݒ�
	SetMode(g_mode);

	return S_OK;
}

//-------------------------------------------------------------------------------
//�I������
//-------------------------------------------------------------------------------
void UnInit(void)
{

	//���͂̏I������
	UnInitKeyBoard();

	//�t�F�[�h�̏I������
	UninitFade();

	switch (g_mode)
	{
	case MODE_TITLE:
		//�^�C�g���̏I������
		UninitTitle();
		break;

	case MODE_TUTORIAL:
		//�`���[�g���A���̏I������
		UninitTutorial();
		break;


	case MODE_GAME:
		//�X�e�[�W1�̏I������
		UninitGame();
		break;

	case MODE_GAMEOVER:
		//�Q�[���I�[�o�[�̏I������
		UninitGameOver();
		break;

	case MODE_RESULT:
		//���U���g�̏I������
		UninitResult();
		break;
	}

	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//Direct3D�f�o�C�X�̊J��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g�̊J��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//-------------------------------------------------------------------------------
//�X�V����
//-------------------------------------------------------------------------------
void UpDate(void)
{
	//���͂̍X�V����
	UpdateKeyBoard();

	//�Q�[���p�b�h�̏��
	RoadGamePad();

	//�L�[�{�[�h�̍X�V����
	switch (g_mode)
	{
	case MODE_TITLE:
		//�^�C�g���̍X�V����
		UpdateTitle();
		break;

	case MODE_TUTORIAL:
		//�`���[�g���A���̍X�V����
		UpdateTutorial();
		break;

	case MODE_GAME:
		//�X�e�[�W1�̍X�V����
		UpdateGame();
		break;

	case MODE_GAMEOVER:
		//�Q�[���I�[�o�[�̍X�V����
		UpdateGameOver();
		break;

	case MODE_RESULT:
		//���U���g�̍X�V����
		UpdateResult();
		break;
	}

	//�t�F�[�h�̍X�V����
	UpdateFade();
}

//-------------------------------------------------------------------------------
//�`�揈��
//-------------------------------------------------------------------------------
void Draw(void)
{
	//�o�b�N�o�b�t�@&Z�o�b�t�@�̃N���A(��ʂ̃N���A)
	g_pD3DDevice->Clear(
		0,NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0,0), 1.0f, 0);

	//�J�����̐ݒ�
	SetCamera();

	//�`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_mode)
		{
			case MODE_TITLE:
			//�^�C�g���̕`�揈��
			DrawTitle();
			break;

			case MODE_TUTORIAL:
			//�`���[�g���A���̕`�揈��
			DrawTutorial();
			break;

			case MODE_GAME:
			//�^�C�g���̕`�揈��
			DrawGame();

			//TXT�̕`�揈��
			DrawTXT();
			break;

			case MODE_GAMEOVER:
			//�Q�[���I�[�o�[�̕`�揈��
			DrawGameOver();
			break;

			case MODE_RESULT:
			//���U���g�̕`�揈��
			DrawResult();
			break;
		}

		////FPS�̕`�揈��
		//DrawFPS();

		//�t�F�[�h�̕`�揈��
		DrawFade();

		//�`��̏I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//-------------------------------------------------------------------------------
//�f�o�C�X�̎擾
//-------------------------------------------------------------------------------
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//////-------------------------------------------------------------------------------
////FPS�̕\��
////-------------------------------------------------------------------------------
//void DrawFPS(void)
//{
//	RECT rect = { 1100,650,SCREEN_WIDTH,SCREEN_HEIGHT };
//	char astr[256];
//
//	wsprintf(&astr[0], "FPS:%d\n", g_nCountFPS);
//
//	//�e�L�X�g�̕`��
//	g_pFont->DrawText(NULL, &astr[0], -1, &rect, DT_LEFT,D3DCOLOR_RGBA(255, 255, 255, 255));
//}

void DrawTXT(void)
{
	
	CAMERA*Camera = GetCamera();
	RECT rect = { 0,0,SCREEN_WIDTH,500 };
	char astr[256];

	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		
		//�J�����y�уv���C���[�̉�]��
		int nNum = sprintf(&astr[0], "�J����X��:%0.2f\n", Camera->posV.x);
		nNum += sprintf(&astr[nNum], "�J����Y��:%0.2f\n", Camera->posV.y);
		nNum += sprintf(&astr[nNum], "�J����Z��:%0.2f\n", Camera->posV.z);
		nNum += sprintf(&astr[nNum], "��]Y��:%0.2f\n", Camera->rot.y);

		//�e�L�X�g�̕`��
		g_pFont->DrawText(NULL, &astr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

		//�`��̏I��
		g_pD3DDevice->EndScene();
	}
}

//-------------------------------------------------------------------------------
//���[�h�̐ݒ�
//-------------------------------------------------------------------------------
void SetMode(MODE mode)
{
	switch (g_mode)
	{
		case MODE_TITLE:
			//�^�C�g���̏I������
			UninitTitle();
			break;

		case MODE_TUTORIAL:
			//�`���[�g���A���̏I������
			UninitTutorial();
			break;

		case MODE_GAME:
			//�X�e�[�W1�̏I������
			UninitGame();
			break;


		case MODE_GAMEOVER:
			//�Q�[���I�[�o�[�̏I������
			UninitGameOver();
			break;

		case MODE_RESULT:
			//���U���g�̏I������
			UninitResult();
			break;
	}

	switch (mode)
	{
		case MODE_TITLE:
			//�^�C�g���̏���������
			InitTitle();
			break;

		case MODE_TUTORIAL:
			//�`���[�g���A���̏���������
			InitTutorial();
			break;

		case MODE_GAME:
			//�X�e�[�W1�̏���������
			InitGame();

		case MODE_GAMEOVER:
			//�Q�[���I�[�o�[�̏���������
			InitGameOver();


		case MODE_RESULT:
			//���U���g�̏���������
			InitResult();
			break;
	}
	g_mode = mode;
}
//-------------------------------------------------------------------------------
//��ʃ��[�h�̎擾
//-------------------------------------------------------------------------------
MODE GetMode(void)
{
	return g_mode;
}