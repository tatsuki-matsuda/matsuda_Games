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
class CFade;
class CPlayer;
class CEnemy;
class CScore;
class CBullet;
class CPause;
class CBg;
class CTitle;
class CTutorial;
class CResult;
class CGame;
class CSound;

//================================================================================
//オブジェクトクラス
//================================================================================
class CManager
{

public:

	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
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
	static CFade*GetFade(void) { return m_pFade; }						//フェード情報

	static void SetMode(Mode mode);
	static Mode GetMode(void) { return m_Mode; }						//モードの取得

	static void SetPause(void);											//ポーズの取得
	static void SetPause(bool pause) { m_bPause = pause; }				//ポーズの取得をするかどうか
	static bool GetPause(void) { return m_bPause; }						//ポーズの情報

	static void SetScore(int savescore) { m_nSaveScore = savescore; }	//スコア保存の取得
	static int GetScore(void) { return m_nSaveScore; }					//スコア保存情報

	static void SetSound(CSound*sound) { m_pSound = sound; }			//サウンドの取得
	static CSound*GetSound(void) { return m_pSound; }					//サウンドの情報

private:

	static CTitle*m_pTitle;												// タイトルのポインタ
	static CTutorial*m_pTutorial;										// チュートリアルのポインタ
	static CGame*m_pGame;												// ゲームのポインタ
	static CResult*m_pResult;											// リザルトのポインタ
	static Mode m_Mode;													// モードのポインタ
	static CFade*m_pFade;												// フェードのポインタ
	static CRenderer*m_pRenderer;										// Renererのポインタ
	static CInputKeyBoard*m_pInputKeyBoard;								// キーボードのポインタ
	static CSound*m_pSound;												// BGM

	static int m_nSaveScore;											// スコアを保存する変数
	static bool m_bPause;												// ポーズ中かどうか

};

//--------------------------------------------------------------------------------
//プロトタイプ宣言
//--------------------------------------------------------------------------------
#endif
