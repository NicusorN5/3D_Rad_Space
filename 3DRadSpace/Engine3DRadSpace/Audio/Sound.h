#pragma once
#include "AudioEngine.h"

typedef void* E3DRSP_Sound;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_AUDIO_EXPORT E3DRSP_Sound E3DRSP_Sound_Create(E3DRSP_AudioEngine audio, const char* path);
	E3DRSP_AUDIO_EXPORT void E3DRSP_Sound_Destroy(E3DRSP_Sound audio);
#ifdef __cplusplus
}
#endif