#include "SoundPlayer.h"



CSoundPlayer::CSoundPlayer()
{
	InitSoundPlayer();
}


CSoundPlayer::~CSoundPlayer()
{
}

HRESULT CSoundPlayer::InitSoundPlayer()
{
	if (NULL == pXAudio2) {
	hr = XAudio2Create(&pXAudio2);//��������  
	if (FAILED(hr))
		return 0;

	hr = pXAudio2->CreateMasteringVoice(&pMasterVoice);//������������Ĭ���������ǰ������  
	if (FAILED(hr))
		return 0;
	}
	return E_NOTIMPL;
}

HRESULT CSoundPlayer::AddSourceVoice(IXAudio2SourceVoice ** ppSourceVoice, WAVEFORMATEX * pSourceFormat, UINT32 Flags, float MaxFrequencyRatio, IXAudio2VoiceCallback * pCallback, XAUDIO2_VOICE_SENDS * pSendList, XAUDIO2_EFFECT_CHAIN * pEffectChain)
{
	if (FAILED(hr = pXAudio2->CreateSourceVoice(ppSourceVoice, (WAVEFORMATEX*)&pSourceFormat,
		Flags, MaxFrequencyRatio, pCallback, pSendList, pEffectChain))) return hr;

	return E_NOTIMPL;
}



