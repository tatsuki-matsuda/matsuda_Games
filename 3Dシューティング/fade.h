//--------------------------------------------------------------------------------
//
// ゲーム制作[fade.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"

//--------------------------------------------------------------------------------
//フェードの状態
//--------------------------------------------------------------------------------
typedef enum
{
	FADE_NONE = 0,	//何もしてない
	FADE_IN,		//フェードイン
	FADE_OUT,		//フェードアウト
	FADE_MAX
}FADE;

//--------------------------------------------------------------------------------
//プロトタイプ宣言
//--------------------------------------------------------------------------------
HRESULT InitFade(MODE modeNext);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(FADE fade, MODE modeNext);
FADE GetFade(void);

#endif

