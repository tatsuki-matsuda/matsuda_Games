//--------------------------------------------------------------------------------
//
// �Q�[������[sound.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
#include "xaudio2.h"	//�T�E���h�Đ��ɕK�v

//================================================================================
//�I�u�W�F�N�g�N���X
//================================================================================
class CSound
{

public:

	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,		// BGM0
		SOUND_LABEL_BGM001,			// BGM1
		SOUND_LABEL_BGM002,			// BGM2
		SOUND_LABEL_SE_SHOT,		// �e���ˉ�
		SOUND_LABEL_SE_HIT,			// �q�b�g��
		SOUND_LABEL_SE_EXPLOSION,	// ������
		SOUND_LABEL_SE_BUTTON,		// ���艹
		SOUND_LABEL_MAX,

	} SOUND_LABEL;

	CSound();															//�R���X�g���N�^
	virtual ~CSound();													//�f�X�g���N�^

	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);


private:

	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDPARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

																// �e���f�ނ̃p�����[�^
	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];
};
#endif