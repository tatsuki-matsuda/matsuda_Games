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
	void ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR,D3DXVECTOR3 posU);

	LPDIRECT3DDEVICE9 GetDevice(void) {return m_pD3DDevice;}

private:

	void DrawFPS(void);								// FPS�̕`�揈��

	LPDIRECT3D9 m_pD3D = NULL;						// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice = NULL;			// Device�I�u�W�F�N�g(�`��ɕK�v)

	LPDIRECT3DTEXTURE9 m_pTextureMT;				// �����_�����O�^�[�Q�b�g�p�̃e�N�X�`��
	LPDIRECT3DSURFACE9 m_pRenderMT;					// �e�N�X�`�������_�����O�p�C���^�[�t�F�[�X

	LPDIRECT3DSURFACE9 m_pBuffMT;					// �e�N�X�`�������_�����O�pZ�o�b�t�@
	D3DVIEWPORT9 m_viewportMT;						// �e�N�X�`�������_�����O�p�r���[�|�[�g

	//D3DXVECTOR3 m_rot;
	//float m_fAngle;
	//float m_Length;

	#ifdef _DEBUG
	LPD3DXFONT m_pFont = NULL;						// �t�H���g�ւ̃|�C���^
	#endif
};
#endif

