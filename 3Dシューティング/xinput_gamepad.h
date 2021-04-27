//--------------------------------------------------------------------------------
//
// ゲーム制作[input.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _XINPUTGAMEPAD_H_
#define _XINPUTGAMEPAD_H_

#include "main.h"

//--------------------------------------------------------------------------------
//ゲームパッド(xinput)の構造体
//--------------------------------------------------------------------------------
typedef struct
{
	
	bool bPless = false;
	bool bAButton = false;
	bool bPressLStick = false;
	float fAngle;

}XinputGamepad;

//--------------------------------------------------------------------------------
//プロトタイプ宣言
//--------------------------------------------------------------------------------
void RoadGamePad(void);
void XinputButtons(void);
void XinputSticks(void);
XinputGamepad*GetXinputGamepad(void);
//XinputButton

#endif