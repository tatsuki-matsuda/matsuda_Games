//--------------------------------------------------------------------------------
//
// ゲーム制作[game.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "bg.h"
#include "game_screen.h"
#include "pause.h"
#include "player.h"
#include "enemy.h"
#include "lifeboss.h"

//--------------------------------------------------------------------------------
//前方宣言
//--------------------------------------------------------------------------------
class CScore;
class CPlayer;
class CExplosion;
class CEnemy;
class CBullet;
class CBg;
class CPause;
class CGame_Screen;
class CLife;
class CBomb;
class CLifeBoss;
class CSound;

//--------------------------------------------------------------------------------
//マクロ定義
//--------------------------------------------------------------------------------
#define ENEMY_RESPAWNTIME (300)

//================================================================================
//オブジェクトクラス
//================================================================================
class CGame : CScene
{

public:
	// 遷移条件
	typedef enum
	{
		TRANSITION_NONE = 0,
		TRANSITION_RESULT,
		TRANSITION_MAX,
	}Transition;

	CGame();																			//コンストラクタ
	~CGame();																			//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);									//初期化処理
	void Uninit(void);																	//終了処理
	void Update(void);																	//更新処理
	void Draw(void);																	//描画処理

	static CBullet*GetBullet(void);														//弾情報の呼び出し
	static CExplosion*GetExplosion(void);												//爆発情報の呼び出し
	static CBg*GetBg(void);																//背景情報の呼び出し
	static CGame_Screen*GetGame_Screen(void);											//ゲーム背景情報の呼び出し
	static CPlayer*GetPlayer(void);														//プレイヤー情報の呼び出し
	static CEnemy*GetEnemy(void);														//敵情報の呼び出し
	static CScore*GetScore(void);														//スコア情報の呼び出し
	static CScore*GetGraze(void);														//グレイズ情報の呼び出し
	static CScore*GetBulletNum(void);
	static CLifeBoss*GetBossLifeCnt(void) { return m_pBossLifeCnt; }					//ボスライフカウント情報の呼び出し

	static CLife*GetLife(void);															//ライフの情報を呼び出し
	static CBomb*GetBomb(void) { return m_pBomb; }										//ボムの情報を呼び出し
	static CPause*GetPause(void) { return m_pPause; }									//ポーズ情報の呼び出し

	static Transition GetTransision(void) { return m_transition; }						//ゲーム中の遷移状態の情報を呼び出し
	static void SetTransition(Transition transition) { m_transition = transition; }		//ゲーム中の遷移状態の情報 

private:

	static CBullet*m_pBullet;										// 弾
	static CExplosion*m_pExplosion;									// 爆発
	static CBg*m_pBg;												// 背景
	static CGame_Screen*m_pGame_Screen;								// ゲーム背景
	static CPlayer*m_pPlayer;										// プレイヤー
	static CEnemy*m_pEnemy;											// 敵
	static CScore*m_pGraze;											// グレイズ
	static CScore*m_pScore;											// スコア
	static CLifeBoss*m_pBossLifeCnt;								// ボスライフカウント
	static CScore*m_pBulletNum;										// 画面内の弾数
	static CLife*m_pLife;											// ライフ
	static CBomb*m_pBomb;											// ボム
	static CPause*m_pPause;											// ポーズ
	static Transition m_transition;									// ゲーム中の遷移
	static CSound*m_pSound;											// BGM

	int m_nEnemyTime;												// 敵の出現カウント
	static int m_nCntResult;										// リザルト遷移カウント
};

#endif

