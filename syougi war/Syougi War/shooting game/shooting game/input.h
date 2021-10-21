//--------------------------------------------------------------------------------
//
// ゲーム制作[input.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//================================================================================
//オブジェクトクラス
//================================================================================
class CInput
{

public:

	CInput();												//コンストラクタ
	virtual ~CInput();										//デストラクタ

	virtual	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//初期化処理
	virtual void Uninit(void);								//終了処理
	virtual void Update(void) = 0;							//更新処理

protected:

	LPDIRECTINPUTDEVICE8    m_pDevice;						//デバイス情報
	static LPDIRECTINPUT8	m_pInput;						//インプット情報

};

#endif