#include "SourceVoice.h"



CSourceVoice::CSourceVoice()
{
}

CSourceVoice::CSourceVoice(CSoundPlayer *pSoundPlayer,TCHAR * strFileName)
{
	this->strFileName = strFileName;
	Create(pSoundPlayer);
}


CSourceVoice::~CSourceVoice()
{
}

HRESULT CSourceVoice::Create(CSoundPlayer *pSoundPlayer)
{
	HANDLE hFile = CreateFile(
		CSourceVoice::strFileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return HRESULT_FROM_WIN32(GetLastError());

	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());

	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	//check the file type, should be fourccWAVE or 'XWMA'
	FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
	DWORD filetype;
	ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
	if (filetype != fourccWAVE)
		return S_FALSE;

	FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
	ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);

	//fill out the audio data buffer with the contents of the fourccDATA chunk
	FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
	BYTE * pDataBuffer = new BYTE[dwChunkSize];
	ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);
	//将读取的文件数据，赋值XAUDIO2_BUFFER 
	buffer.AudioBytes = dwChunkSize;  //buffer containing audio data
	buffer.pAudioData = pDataBuffer;  //size of the audio buffer in bytes
	buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer

	if (FAILED(hr = pSoundPlayer->AddSourceVoice(&pSourceVoice, (WAVEFORMATEX*)&wfx,
		0, XAUDIO2_DEFAULT_FREQ_RATIO, NULL, NULL, NULL))) return hr;


	hr = pSourceVoice->SubmitSourceBuffer(&buffer);//提交内存数据  
	if (FAILED(hr))
		return 0;

	return E_NOTIMPL;
}

TCHAR * CSourceVoice::GetFileName()
{
	return CSourceVoice::strFileName;
}
