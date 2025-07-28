#pragma once
#include "../Core/Libs.h"

typedef void* E3DRSP_AudioEngine;

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
	/// <summary>
	/// Creates an audio engine, with default device.
	/// </summary>
	/// <remarks>
	/// Any AudioEngine instance will need to be freed using E3DRSP_AudioEngine_Destroy.
	/// </remarks>
	/// <returns>Pointer to a AudioEngine instance.</returns>
	E3DRSP_AUDIO_EXPORT E3DRSP_AudioEngine E3DRSP_AudioEngine_Create();
	/// <summary>
	/// Creates an audio engine, with specfied device name.
	/// </summary>
	/// <param name="deviceName">Device name.</param>
	/// <returns>AudioEngine instance</returns>
	E3DRSP_AUDIO_EXPORT E3DRSP_AudioEngine E3DRSP_AudioEngine_Create1(const char* deviceName);
	/// <summary>
	/// Lists audio devices.
	/// </summary>
	/// <remarks>
	/// Any AudioEngine instance will need to be freed using E3DRSP_AudioEngine_Destroy.
	/// </remarks>
	/// <returns>A list of strings that's dynamically allocated. Each string should be freed first, then free the list.</returns>
	E3DRSP_AUDIO_EXPORT char** E3DRSP_AudioEngine_ListAudioDevices();

	E3DRSP_AUDIO_EXPORT void E3DRSP_AudioEngine_SwitchAudioDevice(E3DRSP_AudioEngine audio, const char* deviceName);
	E3DRSP_AUDIO_EXPORT void E3DRSP_AudioEngine_Update(E3DRSP_AudioEngine audio);
	E3DRSP_AUDIO_EXPORT enum E3DRSP_AudioError E3DRSP_AudioEngine_CheckErrors(E3DRSP_AudioEngine audio);
	E3DRSP_AUDIO_EXPORT void E3DRSP_AudioEngine_Destroy(E3DRSP_AudioEngine audio);
#ifdef __cplusplus
}
#endif