//------------------------------------------------------------------------------ -
//
// ゲーム制作[main.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include"main.h"
#include"camera.h"			//カメラの表示
#include"polygon.h"			//ポリゴンの表示
#include"meshfield.h"		//メッシュフィールドの表示
#include"wall.h"			//壁の表示
#include"billboard.h"		//ビルボードの表示
#include"bullet.h"			//弾の表示
#include"light.h"			//ライトの表示
#include"model.h"			//モデルの表示
#include"player.h"			//プレイヤーの表示
#include"input.h"			//入力の表示
#include"xinput_gamepad.h"	//Controllerの表示
#include"stdio.h"			//
#include"title.h"			//タイトル画面の表示
#include"tutorial.h"		//チュートリアル画面の表示
#include"game.h"			//ゲーム画面の表示
#include"gameover.h"			//ゲームオーバー画面の表示
#include"result.h"			//リザルト画面の表示
#include"fade.h"			//フェードの表示

//-------------------------------------------------------------------------------
//マクロ定義
//-------------------------------------------------------------------------------
#define ID_BUTTON000   (101)	//ボタン000のID
#define WINDOW_POS_X   (200)	//ウィンドウの左上のX座標
#define WINDOW_POS_Y   (220)	//ウィンドウの左上のY座標
#define ID_TIMER	   (121)	//タイマーのID
#define	TIMER_INTERVAL (1000/60)//タイマー発生間隔(ミリ秒)

//-------------------------------------------------------------------------------
//プロトタイプ宣言
//-------------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWind, BOOL bWindow);
void UnInit(void);
void UpDate(void);
void Draw(void);
void DrawFPS(void);
void DrawTXT(void);

//-------------------------------------------------------------------------------
//グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3D9 g_pD3D = NULL;						//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;			//Direct3Dデバイスへのポインタ
LPD3DXFONT g_pFont = NULL;						//フォントへのポインタ
int g_nCountFPS;								//FPSカウンタ
MODE g_mode = MODE_TITLE;

//-------------------------------------------------------------------------------
//メイン関数
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
	HWND hWnd;//ウィンドウハンドル
	MSG msg;  //メッセージを格納する

    //ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	RECT rect{ 0,0,SCREEN_WIDTH ,SCREEN_HEIGHT };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, TRUE);

	//ウィンドウの作成
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

	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	dwExecLastTime = timeGetTime();
	dwFPSLastTime = timeGetTime();
	dwCurrentTime = timeGetTime();//現在時刻を設定
	dwFrameCount = 0;

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)//メッセージを取得しなかった場合"0"を返す
		{//windowsの処理
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
		{//DirectXの処理
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			if ((dwCurrentTime-dwExecLastTime)>(1000/60))
			{
				//代入
				dwExecLastTime = dwCurrentTime;

				//更新処理
				UpDate();

				//描画処理
				Draw();

				//フレームカウント
				dwFrameCount++;
			}
		}
	}

	//終了処理
	UnInit();

	//ウィンドウの登録解除
	UnregisterClass("Project", wcex.hInstance);
	return (int)msg.wParam;
}

//-------------------------------------------------------------------------------
//ウィンドウプロシージャ
//-------------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//変数宣言
	int nID;

	switch (uMsg)
	{//終了時

	case WM_DESTROY:
		PostQuitMessage(0);//WM_QUITメッセージを返す
		break;

	case WM_CLOSE:
		nID = MessageBox(NULL, "終了しますか？", "メッセージ", MB_YESNO | MB_ICONQUESTION);
		if (nID == IDYES)
		{//YESの場合
			DestroyWindow(hWnd);
		}
		else if (nID == IDNO)
		{//NOの場合
			return 0;

		}
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{//ESC押した場合
		case VK_ESCAPE:

				DestroyWindow(hWnd);

			break;
		}
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}
//-------------------------------------------------------------------------------
//初期化処理
//-------------------------------------------------------------------------------
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;


	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//ディスプレイモードの取得
	if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
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

	//Direct3Dデバイスの生成
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

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);			//カリングの設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);			//αブレンド(α値の合成)の設定
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);		//ソース(描画元)の合成方法の設定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);//デスティネーション(描画先)の合成方法の設定

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//文字の表示
	D3DXCreateFont(g_pD3DDevice, 30, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,"Terminal", &g_pFont);

	//入力の初期化処理
	InitKeyBoard(hInstance, hWnd);


	//フェードの初期化処理
	InitFade(g_mode);

	//モードの設定
	SetMode(g_mode);

	return S_OK;
}

//-------------------------------------------------------------------------------
//終了処理
//-------------------------------------------------------------------------------
void UnInit(void)
{

	//入力の終了処理
	UnInitKeyBoard();

	//フェードの終了処理
	UninitFade();

	switch (g_mode)
	{
	case MODE_TITLE:
		//タイトルの終了処理
		UninitTitle();
		break;

	case MODE_TUTORIAL:
		//チュートリアルの終了処理
		UninitTutorial();
		break;


	case MODE_GAME:
		//ステージ1の終了処理
		UninitGame();
		break;

	case MODE_GAMEOVER:
		//ゲームオーバーの終了処理
		UninitGameOver();
		break;

	case MODE_RESULT:
		//リザルトの終了処理
		UninitResult();
		break;
	}

	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//Direct3Dデバイスの開放
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの開放
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//-------------------------------------------------------------------------------
//更新処理
//-------------------------------------------------------------------------------
void UpDate(void)
{
	//入力の更新処理
	UpdateKeyBoard();

	//ゲームパッドの情報
	RoadGamePad();

	//キーボードの更新処理
	switch (g_mode)
	{
	case MODE_TITLE:
		//タイトルの更新処理
		UpdateTitle();
		break;

	case MODE_TUTORIAL:
		//チュートリアルの更新処理
		UpdateTutorial();
		break;

	case MODE_GAME:
		//ステージ1の更新処理
		UpdateGame();
		break;

	case MODE_GAMEOVER:
		//ゲームオーバーの更新処理
		UpdateGameOver();
		break;

	case MODE_RESULT:
		//リザルトの更新処理
		UpdateResult();
		break;
	}

	//フェードの更新処理
	UpdateFade();
}

//-------------------------------------------------------------------------------
//描画処理
//-------------------------------------------------------------------------------
void Draw(void)
{
	//バックバッファ&Zバッファのクリア(画面のクリア)
	g_pD3DDevice->Clear(
		0,NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0,0), 1.0f, 0);

	//カメラの設定
	SetCamera();

	//描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_mode)
		{
			case MODE_TITLE:
			//タイトルの描画処理
			DrawTitle();
			break;

			case MODE_TUTORIAL:
			//チュートリアルの描画処理
			DrawTutorial();
			break;

			case MODE_GAME:
			//タイトルの描画処理
			DrawGame();

			//TXTの描画処理
			DrawTXT();
			break;

			case MODE_GAMEOVER:
			//ゲームオーバーの描画処理
			DrawGameOver();
			break;

			case MODE_RESULT:
			//リザルトの描画処理
			DrawResult();
			break;
		}

		////FPSの描画処理
		//DrawFPS();

		//フェードの描画処理
		DrawFade();

		//描画の終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//-------------------------------------------------------------------------------
//デバイスの取得
//-------------------------------------------------------------------------------
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//////-------------------------------------------------------------------------------
////FPSの表示
////-------------------------------------------------------------------------------
//void DrawFPS(void)
//{
//	RECT rect = { 1100,650,SCREEN_WIDTH,SCREEN_HEIGHT };
//	char astr[256];
//
//	wsprintf(&astr[0], "FPS:%d\n", g_nCountFPS);
//
//	//テキストの描画
//	g_pFont->DrawText(NULL, &astr[0], -1, &rect, DT_LEFT,D3DCOLOR_RGBA(255, 255, 255, 255));
//}

void DrawTXT(void)
{
	
	CAMERA*Camera = GetCamera();
	RECT rect = { 0,0,SCREEN_WIDTH,500 };
	char astr[256];

	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		
		//カメラ及びプレイヤーの回転軸
		int nNum = sprintf(&astr[0], "カメラX軸:%0.2f\n", Camera->posV.x);
		nNum += sprintf(&astr[nNum], "カメラY軸:%0.2f\n", Camera->posV.y);
		nNum += sprintf(&astr[nNum], "カメラZ軸:%0.2f\n", Camera->posV.z);
		nNum += sprintf(&astr[nNum], "回転Y軸:%0.2f\n", Camera->rot.y);

		//テキストの描画
		g_pFont->DrawText(NULL, &astr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

		//描画の終了
		g_pD3DDevice->EndScene();
	}
}

//-------------------------------------------------------------------------------
//モードの設定
//-------------------------------------------------------------------------------
void SetMode(MODE mode)
{
	switch (g_mode)
	{
		case MODE_TITLE:
			//タイトルの終了処理
			UninitTitle();
			break;

		case MODE_TUTORIAL:
			//チュートリアルの終了処理
			UninitTutorial();
			break;

		case MODE_GAME:
			//ステージ1の終了処理
			UninitGame();
			break;


		case MODE_GAMEOVER:
			//ゲームオーバーの終了処理
			UninitGameOver();
			break;

		case MODE_RESULT:
			//リザルトの終了処理
			UninitResult();
			break;
	}

	switch (mode)
	{
		case MODE_TITLE:
			//タイトルの初期化処理
			InitTitle();
			break;

		case MODE_TUTORIAL:
			//チュートリアルの初期化処理
			InitTutorial();
			break;

		case MODE_GAME:
			//ステージ1の初期化処理
			InitGame();

		case MODE_GAMEOVER:
			//ゲームオーバーの初期化処理
			InitGameOver();


		case MODE_RESULT:
			//リザルトの初期化処理
			InitResult();
			break;
	}
	g_mode = mode;
}
//-------------------------------------------------------------------------------
//画面モードの取得
//-------------------------------------------------------------------------------
MODE GetMode(void)
{
	return g_mode;
}