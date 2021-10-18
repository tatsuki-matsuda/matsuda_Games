//--------------------------------------------------------------------------------
//
// ゲーム制作[bullet.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

#include "scene2D.h"

//--------------------------------------------------------------------------------
//マクロ定義
//--------------------------------------------------------------------------------
#define NORMAL_DAMAGE		(4)								//通常弾ダメージ量
#define BOMB_DAMAGE			(3)								//ボムダメージ量
#define HOMING_DAMAGE		(2)								//ホーミングダメージ量
#define CROSSING_DAMAGE		(1)								//交差弾ダメージ量
#define REFLECTIVE_DAMAGE	(1)								//反射弾ダメージ量
#define WAVE_DAMAGE			(1)								//波紋弾ダメージ量
#define	CREATE_BULLET		(3)								//弾の生成量

#define PLAYER_HOMING_X		(15.0f)							//プレイヤーホーミングX軸移動量
#define PLAYER_HOMING_Y		(23.0f)							//プレイヤーホーミングY軸移動量
#define ENEMY_HOMING_X		(12.0f)							//プレイヤーホーミングX軸移動量
#define ENEMY_HOMING_Y		(23.0f)							//プレイヤーホーミングY軸移動量

//--------------------------------------------------------------------------------
//前方宣言
//--------------------------------------------------------------------------------
class CEnemy;

//================================================================================
//オブジェクトクラス(弾)
//================================================================================
class CBullet :public CScene2D
{
public:

	CBullet(int nPriority = OBJTYPE_BULLET);													//コンストラクタ
	~CBullet();																					//デストラクタ

	//弾判定分け
	typedef enum
	{
		BULLETTYPE_NONE = 0,
		BULLETTYPE_PLAYER,				//プレイヤー
		BULLETTYPE_ENEMY,				//敵
		BULLETTYPE_MAX

	}BULLETTYPE;

	//攻撃種類分け
	typedef enum
	{
		ATTACKTYPE_NONE = 0,
		ATTACKTYPE_NORMAL,				//通常弾
		ATTACKTYPE_HOMING,				//ホーミング
		ATTACKTYPE_CROSSING,			//交差
		ATTACKTYPE_ROTATION,			//回転
		ATTACKTYPE_REFLECTION,			//反射
		ATTACKTYPE_TURN,				//折り返し
		ATTACKTYPE_N_WAY1,				//n_way弾1
		ATTACKTYPE_N_WAY2,				//n_way弾2
		ATTACKTYPE_SPIRAL,				//渦巻弾
		ATTACKTYPE_BOMB,				//ボム
		ATTACKTYPE_MAX

	}ATTACKTYPE;

	//攻撃情報種類分け
	typedef enum
	{
		INFOTYPE_NONE = 0,
		INFOTYPE_1,
		INFOTYPE_2,
		INFOTYPE_3,
		INFOTYPE_RED,
		INFOTYPE_BLUE,
		INFOTYPE_BIGBULLET,
		INFOTYPE_MAX

	}INFOTYPE;

	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, 
		D3DXVECTOR3 move, D3DXVECTOR3 rot, BULLETTYPE bulletType,
		ATTACKTYPE attackType,INFOTYPE infoType);												//弾の生成

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, D3DXVECTOR3 rot);		//初期化処理
	void Uninit(void);																			//終了処理
	void Update(void);																			//更新処理
	void Draw(void);																			//描画処理
	static HRESULT Load(void);																	//読み込み処理
	static void Unload(void);																	//破棄処理

	BULLETTYPE GetBulletType(void);																//弾情報
	void SetBulletType(BULLETTYPE bulletType);													//弾情報の取得

	ATTACKTYPE GetAttackType(void);																//攻撃種類情報
	void SetAttackType(ATTACKTYPE attackType);													//攻撃種類情報の取得

	INFOTYPE GetInfoType(void);																	//攻撃情報
	void SetInfoType(INFOTYPE infoType);														//攻撃情報の取得

	void SetGraze(bool bgraze);																	//グレイズ情報
	bool GetGraze(void);																		//グレイズ情報の取得

	void SetUninit(bool bUninit);																//弾消し情報
	bool GetUninit(void);																		//弾消し情報の取得

	void SetLife(int nLife);																	//体力情報
	int  GetLife(void);																			//体力情報の取得

	void SetMove(D3DXVECTOR3 move);																//移動情報
	D3DXVECTOR3  GetMove(void);																	//移動情報の取得

	static LPDIRECT3DTEXTURE9  GetTexture(int nCntTex);											//テクスチャ情報の取得

protected:

	void OnCrossing(void);																		//	交差処理
	void OnCollision(void);																		//	判定処理
	void OnHoming(void);																		//	追尾処理
	void OnReflection(void);																	//	反射処理
	void OnTurn(void);																			//	折り返し処理
	void OnDiffusion(void);																		//	拡散処理
	void OnBomb(void);																			//	ボム処理

private:

	bool m_bGraze;																				//  グレイズ判定
	bool m_bReflection;																			//	反射判定
	bool m_bUninit;																				//  終了判定

	BULLETTYPE m_BulletType;																	//  弾の種類
	ATTACKTYPE m_AttackType;																	//  攻撃の種類
	INFOTYPE   m_InfoType;																		//	攻撃情報の種類

	float m_fAngleSpeed[2];																		//	回転速度
	float m_fAngle;																				//	回転軸
	float m_fAngleBomb;																			//	ボムの回転軸
	float m_fAngleL;																			//	左回転軸
	float m_fAngleR;																			//	右回転軸
	float m_fLengthObj;																			//　弾に一番近いオブジェクトの位置

	int m_nCrossingTimeL;																		//	左交差時間
	int m_nCrossingTimeR;																		//	右交差時間
	int m_nReflectionCnt;																		//	反射カウント
	int m_nWayCnt;																				//	n_way弾生成カウント
	int m_TurnCnt;																				//	切り替えしカウント
	int m_nCnt;																					//	カウント
	int	m_nPlayerCnt;																			//	プレイヤー消滅後カウント
	int m_nLife;																				//	体力
	int m_nKeepObj;																				//	オブジェクトを保存する値
	int m_nCntDraw;
	int m_nCntSpiral = 0;																		//	渦巻カウント

	D3DXVECTOR3 m_posOrigin;																	//　弾が生成された位置
	D3DXVECTOR3 m_posDeath;																		//	消滅時の座標
	D3DXVECTOR3 m_rot;																			//	角度
	D3DXVECTOR3 m_scale;																		//	大きさ
	D3DXVECTOR3 m_move;																			//	移動量
	D3DXCOLOR	m_Color;																		//	色
	D3DXVECTOR3 m_EnemyBulletpos;																	//	敵の弾の位置
	D3DXVECTOR3 m_PlayerBulletpos;																//	プレイヤーの弾の位置

	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];											//	テクスチャ
	CScene2D*m_apScene2D[MAX_SCENE2D];															//	CScene2Dのポインタ
};
#endif
