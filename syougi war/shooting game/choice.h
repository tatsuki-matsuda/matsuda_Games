////--------------------------------------------------------------------------------
////
//// ゲーム制作[title.h]
//// Author:Tatsuki Matsuda
////
////--------------------------------------------------------------------------------
//#ifndef _CHOICE_H_
//#define _CHOICE_H_
//
//#include "scene2D.h"
//
////--------------------------------------------------------------------------------
////マクロ定義
////--------------------------------------------------------------------------------
//
////================================================================================
////オブジェクトクラス
////================================================================================
//class CChoice : public CScene2D
//{
//
//public:
//
//	//選択種類分け
//	typedef enum
//	{
//		CHOICEYTYPE_NONE = 0,
//		CHOICEYTYPE_GAME,
//		CHOICETYPE_EXIT,
//		CHOICEYTYPE_MAX
//
//	}CHOICEYTYPE;
//
//	CChoice(int nPriority = OBJTYPE_UI);							//コンストラクタ
//	~CChoice();														//デストラクタ
//
//	static CChoice *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,
//		D3DXVECTOR3 move, CHOICEYTYPE choiceType);					//選択肢の生成
//
//	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				//初期化処理
//	void Uninit(void);												//終了処理
//	void Update(void);												//更新処理
//	void Draw(void);												//描画処理
//
//	static void Load(void);											//読み込み処理
//	static void Unload(void);										//破棄処理
//
//private:
//
//	int m_nCnt;														//選択カウント
//
//	D3DXVECTOR3 m_pos;												// 位置
//
//	D3DXVECTOR3 m_scale;											// 大きさ
//	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;						// 頂点バッファのポインタ
//	static LPDIRECT3DTEXTURE9 m_pTexture;							// テクスチャ
//
//};
//
//#endif
