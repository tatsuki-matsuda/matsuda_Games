////--------------------------------------------------------------------------------
////
//// �Q�[������[title.h]
//// Author:Tatsuki Matsuda
////
////--------------------------------------------------------------------------------
//#ifndef _CHOICE_H_
//#define _CHOICE_H_
//
//#include "scene2D.h"
//
////--------------------------------------------------------------------------------
////�}�N����`
////--------------------------------------------------------------------------------
//
////================================================================================
////�I�u�W�F�N�g�N���X
////================================================================================
//class CChoice : public CScene2D
//{
//
//public:
//
//	//�I����ޕ���
//	typedef enum
//	{
//		CHOICEYTYPE_NONE = 0,
//		CHOICEYTYPE_GAME,
//		CHOICETYPE_EXIT,
//		CHOICEYTYPE_MAX
//
//	}CHOICEYTYPE;
//
//	CChoice(int nPriority = OBJTYPE_UI);							//�R���X�g���N�^
//	~CChoice();														//�f�X�g���N�^
//
//	static CChoice *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,
//		D3DXVECTOR3 move, CHOICEYTYPE choiceType);					//�I�����̐���
//
//	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				//����������
//	void Uninit(void);												//�I������
//	void Update(void);												//�X�V����
//	void Draw(void);												//�`�揈��
//
//	static void Load(void);											//�ǂݍ��ݏ���
//	static void Unload(void);										//�j������
//
//private:
//
//	int m_nCnt;														//�I���J�E���g
//
//	D3DXVECTOR3 m_pos;												// �ʒu
//
//	D3DXVECTOR3 m_scale;											// �傫��
//	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;						// ���_�o�b�t�@�̃|�C���^
//	static LPDIRECT3DTEXTURE9 m_pTexture;							// �e�N�X�`��
//
//};
//
//#endif
