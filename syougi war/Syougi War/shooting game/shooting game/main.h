//--------------------------------------------------------------------------------
//
// �Q�[������[main.h]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#ifndef _MAIN_H_
#define _MAIN_H_

#include<windows.h>
#include"d3dx9.h"	//�`�揈���ɕK�v
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h" //���͏����ɕK�v
#include "renderer.h" //���͏����ɕK�v
//#include "xaudio2.h"	//�T�E���h�Đ��ɕK�v

//--------------------------------------------------------------------------------
//���C�u�����̃����N
//--------------------------------------------------------------------------------
#pragma comment(lib,"d3d9.lib")		//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	//�g�����C�u����
#pragma comment(lib,"dxguid.lib")	//�R���|�[�l���g�g�p�ɕK�v
#pragma comment(lib,"dinput8.lib")	//���͏����ɕK�v
#pragma comment(lib,"winmm.lib")	//���͏����ɕK�v

//--------------------------------------------------------------------------------
//�O���錾
//--------------------------------------------------------------------------------
class CScene;

//--------------------------------------------------------------------------------
//�v���g�^�C�v�錾
//--------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wRaram, LPARAM lParam);

#ifdef _DEBUG
void DrawFPS(void);
#endif

int GetFPS(void);

#endif