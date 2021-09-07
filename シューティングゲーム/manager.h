//--------------------------------------------------------------------------------
//
// ゲーム制作[manager.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _MANAGER_H_
#define _MANAGER_H_

//--------------------------------------------------------------------------------
//マクロ定義
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
//前方宣言
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
//オブジェクトクラス
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

	CManager();															//コンストラクタ
	~CManager();														//デストラクタ

	HRESULT Init(HINSTANCE hInstance,HWND hWnd, BOOL bWindow);			//初期化処理
	void Uninit(void);													//終了処理
	void Update(void);													//更新処理
	void Draw(void);													//描画処理
	static CRenderer *GetRenderer(void);								//Rendererクラスの情報
	static CInputKeyBoard*GetInputKeyBoard(void);						//入力情報
	static void SetMode(Mode mode);
	static Mode GetMode(void) { return m_Mode; }						//モードの取得

private:

	static CTitle*m_pTitle;
	static CGame*m_pGame;
	//static CResult*m_pResult;
	static Mode m_Mode;
	static CRenderer*m_pRenderer;										// Renererのポインタ
	static CInputKeyBoard*m_pInputKeyBoard;								// キーボードのポインタ

};

//--------------------------------------------------------------------------------
//プロトタイプ宣言
//--------------------------------------------------------------------------------
#endif
