//=============================================================================
//
// �T�E���h���� [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <XAudio2.h>

//wwise �~�h���E�F�A
//�{�����[���Ȃǂ̃I�v�V�����͋��ȏ����Ď���

//*****************************************************************************
// �p�����[�^�\���̒�`
//*****************************************************************************
typedef struct
{
	char *pFilename;	// �t�@�C����
	int nCntLoop;		// ���[�v�J�E���g
} SOUNDPARAM;

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************

typedef enum
{
	/*
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_SE_SHOT,		// �e���ˉ�
	SOUND_LABEL_SE_HIT,			// �q�b�g��
	*/
	SOUND_LABEL_BGM_TITLE,			// �^�C�g��
	SOUND_LABEL_BGM_GAME,			// �^�C�g��
	SOUND_LABEL_MAX
} SOUND_LABEL;

// �e���f�ނ̃p�����[�^
static const SOUNDPARAM g_aParam[SOUND_LABEL_MAX] =
{
	/*
	{ "resource/sound/saver_wing.wav",   -1 },			// BGM0				-1 = ���[�v, 0 = �P��
	{ "resource/sound/shot000.wav",       0 },			// �e���ˉ�
	{ "data/sound/explosion000.wav",  0 },			// ������
	*/

	{ "data/sounds/title_BGM.wav",		-1 },			// �^�C�g��BGM
	{ "data/sounds/game_BGM.wav",		-1 },			// �^�C�g��BGM
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//HRESULT InitSound(HWND hWnd);
//void UninitSound(void);
//HRESULT PlaySound(SOUND_LABEL label);
//HRESULT PlaySound(SOUND_LABEL label, float volume);
//void StopSound(SOUND_LABEL label);
//void StopSound(void);

class CSound
{
public:
	HRESULT InitSound(SOUND_LABEL label);
	void UninitSound(void);
	void Release(void);
	HRESULT Play();
	HRESULT Play(float volume);
	void StopSound(SOUND_LABEL label);
	static void StopSoundAll(void);

	static void Init(void);
	static void ReleaseAll(void);
	static CSound* Create(SOUND_LABEL label);

	static HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	static HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:
	IXAudio2SourceVoice *m_SourceVoice;	// �\�[�X�{�C�X
	BYTE *m_DataAudio;					// �I�[�f�B�I�f�[�^
	DWORD m_SizeAudio;					// �I�[�f�B�I�f�[�^�T�C�Y
	SOUND_LABEL m_Label;				// ���x��

	static IXAudio2 *m_XAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	static IXAudio2MasteringVoice *m_MasteringVoice;		// �}�X�^�[�{�C�X
	static CSound* m_Sounds[SOUND_LABEL_MAX];
};

#endif
