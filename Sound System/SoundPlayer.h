#pragma once

#include "ReadDataFormWaveFile.h"
#include "X3daudio.h"
#include "Xaudio2.h"
#include "SourceVoice.h"

class CSoundPlayer
{
public:
	CSoundPlayer();
	~CSoundPlayer();
	HRESULT InitSoundPlayer();
	HRESULT AddSourceVoice(IXAudio2SourceVoice** ppSourceVoice,
		WAVEFORMATEX* pSourceFormat,
		UINT32 Flags,
		float MaxFrequencyRatio,
		IXAudio2VoiceCallback* pCallback ,
		XAUDIO2_VOICE_SENDS* pSendList,
		XAUDIO2_EFFECT_CHAIN* pEffectChain
	);
	

private:
	HRESULT hr;
	IXAudio2 *pXAudio2 = NULL;
	IXAudio2MasteringVoice *pMasterVoice = NULL;



};

