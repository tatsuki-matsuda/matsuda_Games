//--------------------------------------------------------------------------------
//
// �Q�[������[input.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _XINPUTGAMEPAD_H_
#define _XINPUTGAMEPAD_H_

#include "main.h"

//--------------------------------------------------------------------------------
//�Q�[���p�b�h(xinput)�̍\����
//--------------------------------------------------------------------------------
typedef struct
{
	
	bool bPless = false;
	bool bAButton = false;
	bool bPressLStick = false;
	float fAngle;

}XinputGamepad;

//--------------------------------------------------------------------------------
//�v���g�^�C�v�錾
//--------------------------------------------------------------------------------
void RoadGamePad(void);
void XinputButtons(void);
void XinputSticks(void);
XinputGamepad*GetXinputGamepad(void);
//XinputButton

#endif