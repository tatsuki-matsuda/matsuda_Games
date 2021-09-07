//--------------------------------------------------------------------------------
//
// �Q�[������[renderer.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

//--------------------------------------------------------------------------------
//�}�N����`
//--------------------------------------------------------------------------------

//================================================================================
//Renderer�N���X
//================================================================================
class CRenderer
{

public:

	CRenderer();									//�R���X�g���N�^
	~CRenderer();									//�f�X�g���N�^

	HRESULT Init(HWND hWnd, BOOL bWindow);			//����������
	void Uninit(void);								//�I������
	void Update(void);								//�X�V����
	void Draw(void);								//�`�揈��

	LPDIRECT3DDEVICE9 GetDevice(void) {return m_pD3DDevice;}

private:
	void DrawFPS(void);								// FPS�̕`�揈��

	LPDIRECT3D9 m_pD3D = NULL;						// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice = NULL;			// Device�I�u�W�F�N�g(�`��ɕK�v)

	
	//D3DXVECTOR3 m_rot;
	//float m_fAngle;
	//float m_Length;


	#ifdef _DEBUG
	LPD3DXFONT m_pFont = NULL;						// �t�H���g�ւ̃|�C���^
	#endif
};
#endif

