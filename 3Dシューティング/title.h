//--------------------------------------------------------------------------------
//
// ゲーム制作[title.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _TITLE_H_
#define _TITLE_H_
#include "main.h"

//--------------------------------------------------------------------------------
//マクロ定義
//--------------------------------------------------------------------------------
#define	FLASH_INTERBAL	(30)


//--------------------------------------------------------------------------------
//プロトタイプ宣言
//--------------------------------------------------------------------------------
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
//void SetVertexTitleLogo(int nCntTitleLogo);

#endif
