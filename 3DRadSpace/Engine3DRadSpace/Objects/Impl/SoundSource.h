#pragma once
#include "IObject3D.h"
#include "../../Audio/SoundInstance.h"

typedef void* E3DRSP_SoundSource;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_SoundSource E3DRSP_SoundSource_Create();

	E3DRSP_OBJECTS_IMPL_EXPORT unsigned E3DRSP_SoundSource_GetSoundID(E3DRSP_SoundSource soundSource);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_SoundSource_SetSoundID(E3DRSP_SoundSource soundSource, unsigned soundAsset);

	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_Sound E3DRSP_SoundSource_GetSound(E3DRSP_SoundSource soundSource);
	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_SoundInstance E3DRSP_SoundSource_GetSoundInstance(E3DRSP_SoundSource soundSource);

	E3DRSP_OBJECTS_IMPL_EXPORT float E3DRSP_SoundSource_GetVolume(E3DRSP_SoundSource soundSource);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_SoundSource_SetVolume(E3DRSP_SoundSource soundSource, float volume);

	E3DRSP_OBJECTS_IMPL_EXPORT float E3DRSP_SoundSource_GetPitch(E3DRSP_SoundSource soundSource);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_SoundSource_SetPitch(E3DRSP_SoundSource soundSource, float pitch);

	E3DRSP_OBJECTS_IMPL_EXPORT bool E3DRSP_SoundSource_IsLooping(E3DRSP_SoundSource soundSource);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_SoundSource_SetLooping(E3DRSP_SoundSource soundSource, bool looping);

	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_Vector3 E3DRSP_SoundSource_GetVelocity(E3DRSP_SoundSource soundSource);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_SoundSource_SetVelocity(E3DRSP_SoundSource soundSource, const E3DRSP_Vector3 *velocity);

	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_Vector3 E3DRSP_SoundSource_GetDirection(E3DRSP_SoundSource soundSource);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_SoundSource_SetDirection(E3DRSP_SoundSource soundSource, const E3DRSP_Vector3* direction);

	E3DRSP_OBJECTS_IMPL_EXPORT float E3DRSP_SoundSource_GetMaxDistance(E3DRSP_SoundSource soundSource);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_SoundSource_SetMaxDistance(E3DRSP_SoundSource soundSource, float distance);

	E3DRSP_OBJECTS_IMPL_EXPORT float E3DRSP_SoundSource_GetReferenceDistance(E3DRSP_SoundSource soundSource);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_SoundSource_SetReferenceDistance(E3DRSP_SoundSource soundSource, float distance);

	E3DRSP_OBJECTS_IMPL_EXPORT float E3DRSP_SoundSource_GetRolloffFactor(E3DRSP_SoundSource soundSource);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_SoundSource_SetRolloffFactor(E3DRSP_SoundSource soundSource, float rolloff);

	E3DRSP_OBJECTS_IMPL_EXPORT float E3DRSP_SoundSource_GetConeInnerAngle(E3DRSP_SoundSource soundSource);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_SoundSource_SetConeInnerAngle(E3DRSP_SoundSource soundSource, float angle);

	E3DRSP_OBJECTS_IMPL_EXPORT float E3DRSP_SoundSource_GetConeOuterAngle(E3DRSP_SoundSource soundSource);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_SoundSource_SetConeOuterAngle(E3DRSP_SoundSource soundSource, float angle);

	E3DRSP_OBJECTS_IMPL_EXPORT float E3DRSP_SoundSource_GetConeOuterGain(E3DRSP_SoundSource soundSource);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_SoundSource_SetConeOuterGain(E3DRSP_SoundSource soundSource, float gain);
#ifdef __cplusplus
}
#endif