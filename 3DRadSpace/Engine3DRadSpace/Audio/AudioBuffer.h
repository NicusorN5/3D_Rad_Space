#pragma once
#include "../Core/Libs.h"

typedef void* E3DRSP_AudioBuffer;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_AUDIO_EXPORT E3DRSP_AudioBuffer E3DRSP_AudioBuffer_Create(char* buffer, int numChannels, int sampleRate, int bps, int format, int size);
	E3DRSP_AUDIO_EXPORT E3DRSP_AudioBuffer E3DRSP_AudioBuffer_FromWAV(const char* path);
	E3DRSP_AUDIO_EXPORT E3DRSP_AudioBuffer E3DRSP_AudioBuffer_FromOGG(const char* path);
	E3DRSP_AUDIO_EXPORT void E3DRSP_AudioBuffer_Destroy(E3DRSP_AudioBuffer audioBuffer);
#ifdef __cplusplus
}
#endif