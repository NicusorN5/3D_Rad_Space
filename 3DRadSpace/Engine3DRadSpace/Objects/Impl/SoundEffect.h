#pragma once
#include "../IObject.h"
#include "../../Audio/SoundInstance.h"

typedef void* E3DRSP_SoundEffect;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_SoundEffect E3DRSP_SoundEffect_Create();

	E3DRSP_OBJECTS_IMPL_EXPORT unsigned E3DRSP_SoundEffect_GetSoundID(E3DRSP_SoundEffect soundEffect);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_SoundEffect_SetSoundID(E3DRSP_SoundEffect soundEffect, unsigned soundAsset);

	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_Sound E3DRSP_SoundEffect_GetSound(E3DRSP_SoundEffect soundEffect);
	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_SoundInstance E3DRSP_SoundEffect_GetSoundInstance(E3DRSP_SoundEffect soundEffect);

	E3DRSP_OBJECTS_IMPL_EXPORT float E3DRSP_SoundEffect_GetVolume(E3DRSP_SoundEffect soundEffect);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_SoundEffect_SetVolume(E3DRSP_SoundEffect soundEffect, float volume);

	E3DRSP_OBJECTS_IMPL_EXPORT float E3DRSP_SoundEffect_GetPitch(E3DRSP_SoundEffect soundEffect);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_SoundEffect_SetPitch(E3DRSP_SoundEffect soundEffect, float pitch);

	E3DRSP_OBJECTS_IMPL_EXPORT bool E3DRSP_SoundEffect_IsLooping(E3DRSP_SoundEffect soundEffect);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_SoundEffect_SetLooping(E3DRSP_SoundEffect soundEffect, bool looping);
#ifdef __cplusplus
}
#endif