//=============================================================================
//
// サウンド処理 [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <XAudio2.h>

//wwise ミドルウェア
//ボリュームなどのオプションは教科書見て自作

//*****************************************************************************
// パラメータ構造体定義
//*****************************************************************************
typedef struct
{
	char *pFilename;	// ファイル名
	int nCntLoop;		// ループカウント
} SOUNDPARAM;

//*****************************************************************************
// サウンドファイル
//*****************************************************************************

typedef enum
{
	/*
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_SE_SHOT,		// 弾発射音
	SOUND_LABEL_SE_HIT,			// ヒット音
	*/
	SOUND_LABEL_BGM_TITLE,			// タイトル
	SOUND_LABEL_BGM_GAME,			// タイトル
	SOUND_LABEL_MAX
} SOUND_LABEL;

// 各音素材のパラメータ
static const SOUNDPARAM g_aParam[SOUND_LABEL_MAX] =
{
	/*
	{ "resource/sound/saver_wing.wav",   -1 },			// BGM0				-1 = ループ, 0 = 単発
	{ "resource/sound/shot000.wav",       0 },			// 弾発射音
	{ "data/sound/explosion000.wav",  0 },			// 爆発音
	*/

	{ "data/sounds/title_BGM.wav",		-1 },			// タイトルBGM
	{ "data/sounds/game_BGM.wav",		-1 },			// タイトルBGM
};

//*****************************************************************************
// プロトタイプ宣言
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
	IXAudio2SourceVoice *m_SourceVoice;	// ソースボイス
	BYTE *m_DataAudio;					// オーディオデータ
	DWORD m_SizeAudio;					// オーディオデータサイズ
	SOUND_LABEL m_Label;				// ラベル

	static IXAudio2 *m_XAudio2;								// XAudio2オブジェクトへのインターフェイス
	static IXAudio2MasteringVoice *m_MasteringVoice;		// マスターボイス
	static CSound* m_Sounds[SOUND_LABEL_MAX];
};

#endif
