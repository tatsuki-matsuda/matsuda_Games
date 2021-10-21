//-------------------------------------------------------------------------------
//
// ゲーム制作[Model.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include"sceneX.h"		//ゲーム画面
#include"bullet.h"		//弾の詳細
#include"manager.h"		//弾の詳細

//-------------------------------------------------------------------------------
//グローバル変数
//-------------------------------------------------------------------------------

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CSceneX::CSceneX(int nPriority):CScene(nPriority)
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CSceneX::~CSceneX()
{

}



//*****************************************************************************
// 生成処理
//*****************************************************************************
CSceneX *CSceneX::Create(D3DXVECTOR3 pos)
{
	//動的確保
	CSceneX* pSceneX;
	pSceneX = new CSceneX;


	//初期の呼び出し
	pSceneX->Init(pos,D3DXVECTOR3(0.0f,0.0f,0.0f));

	//値を返す
	return pSceneX;
}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CSceneX::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//デバイスの設定
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\field002.jpg", &g_pTextureModel);

	//xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\SyougiBan001.x", D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &m_pBuffMatModel, NULL,
		&m_nNumMatModel, &m_pMeshModel);

	//D3DXMATERIAL*pMat;

	//マテリアル情報に対するポインタを取得
	//pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

	//for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
	//{
	//	if (pMat[nCntMat].pTextureFilename != NULL)
	//	{
	//		pMat[1].pTextureFilename = "data\\TEXTURE\\eye.jpg";
	//	}
	//}

	m_rotmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//ポリゴンの位置・向きの初期設定
	m_posModel = D3DXVECTOR3(-42.0f, 0.0f, 10.0f);
	m_rotModel = D3DXVECTOR3(-0.2f, 0.4f, -0.9f);

	//種類
	SetObjType(OBJTYPE_UI);

	return S_OK;
}

//*****************************************************************************
// 
//*****************************************************************************
void  CSceneX::Uninit(void)
{
	//メッシュの破棄
	if (m_pMeshModel != NULL)
	{
		m_pMeshModel->Release();
		m_pMeshModel = NULL;
	}

	//マテリアルの破棄
	if (m_pBuffMatModel != NULL)
	{
		m_pBuffMatModel->Release();
		m_pBuffMatModel = NULL;
	}
}

//-------------------------------------------------------------------------------
//更新処理
//-------------------------------------------------------------------------------
void  CSceneX::Update(void)
{
	m_rotModel += m_rotmove;

	m_rotmove.y = 0.002f;
	m_rotmove.z = 0.01f;
}

//-------------------------------------------------------------------------------
//描画処理
//-------------------------------------------------------------------------------
void  CSceneX::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアルを使用
	D3DXMATERIAL*pMat;				//マテリアルデータへのポインタ

	//デバイスの設定
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//Zバッファの更新を無効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorldModel);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotModel.y, m_rotModel.x, m_rotModel.z);
	D3DXMatrixMultiply(&m_mtxWorldModel, &m_mtxWorldModel, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_posModel.x, m_posModel.y, m_posModel.z);
	D3DXMatrixMultiply(&m_mtxWorldModel, &m_mtxWorldModel, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldModel);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();


	//Zバッファの更新を有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
	{
		//マテリアルを設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, NULL);

		//モデル(パーツ)の描画
		m_pMeshModel->DrawSubset(nCntMat);
	}


	//保存していたマテリアルを返す
	pDevice->SetMaterial(&matDef);
}
