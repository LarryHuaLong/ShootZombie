#pragma once
#include "xaudio2.h"
#include "windows.h"
#include "ReadDataFormWaveFile.h"
#include "SoundPlayer.h"

class CSourceVoice
{
public:
				CSourceVoice();
				CSourceVoice(CSoundPlayer *pSoundPlayer, TCHAR *strFileName);
				~CSourceVoice();
	HRESULT		Create(CSoundPlayer *pSoundPlayer);
	TCHAR *		GetFileName();

private:
	HRESULT				   hr;
	TCHAR				 * strFileName;
	IXAudio2SourceVoice	 * pSourceVoice;
	XAUDIO2_BUFFER		   buffer = { 0 };
	WAVEFORMATEXTENSIBLE   wfx = { 0 };


};

