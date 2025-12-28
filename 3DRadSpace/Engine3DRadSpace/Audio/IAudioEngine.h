#pragma once
#include "../Core/Libs.h"

typedef void* E3DRSP_IAudioEngine;

enum E3DRSP_AudioError
{
	E3DRSP_AudioError_None = 0,
	E3DRSP_AudioError_BadID,
	E3DRSP_AudioError_InvalidEnum,
	E3DRSP_AudioError_InvalidValue,
	E3DRSP_AudioError_InvalidOperation,
	E3DRSP_AudioError_OutOfMemory,
	E3DRSP_AudioError_Unspecified = 0x7FFFFFFF,
};

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_AUDIO_EXPORT void E3DRSP_IAudioEngine_SwitchAudioDevice(E3DRSP_IAudioEngine audio, const char* deviceName);
	E3DRSP_AUDIO_EXPORT void E3DRSP_IAudioEngine_Update(E3DRSP_IAudioEngine audio);
	E3DRSP_AUDIO_EXPORT enum E3DRSP_AudioError E3DRSP_AudioEngine_CheckErrors(E3DRSP_IAudioEngine audio);
	E3DRSP_AUDIO_EXPORT void E3DRSP_IAudioEngine_Destroy(E3DRSP_IAudioEngine audio);
#ifdef __cplusplus
}
#endif