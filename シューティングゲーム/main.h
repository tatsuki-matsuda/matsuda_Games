//--------------------------------------------------------------------------------
//
// ゲーム制作[main.h]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#ifndef _MAIN_H_
#define _MAIN_H_

#include<windows.h>
#include"d3dx9.h"	//描画処理に必要
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h" //入力処理に必要
#include "renderer.h" //入力処理に必要
//#include "xaudio2.h"	//サウンド再生に必要

//--------------------------------------------------------------------------------
//ライブラリのリンク
//--------------------------------------------------------------------------------
#pragma comment(lib,"d3d9.lib")		//描画処理に必要
#pragma comment(lib,"d3dx9.lib")	//拡張ライブラリ
#pragma comment(lib,"dxguid.lib")	//コンポーネント使用に必要
#pragma comment(lib,"dinput8.lib")	//入力処理に必要
#pragma comment(lib,"winmm.lib")	//入力処理に必要

//--------------------------------------------------------------------------------
//前方宣言
//--------------------------------------------------------------------------------
class CScene;

//--------------------------------------------------------------------------------
//プロトタイプ宣言
//--------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wRaram, LPARAM lParam);
HRESULT Init(HWND hWnd, bool bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

HRESULT InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);

#ifdef _DEBUG
void DrawFPS(void);
#endif

int GetFPS(void);

#endif