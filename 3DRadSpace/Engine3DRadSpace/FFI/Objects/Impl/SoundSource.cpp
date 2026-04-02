#include "SoundSource.h"
#include "../../../Objects/Impl/SoundSource.hpp"

using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

E3DRSP_SoundSource E3DRSP_SoundSource_Create()
{
	return new SoundSource();
}

unsigned E3DRSP_SoundSource_GetSoundID(E3DRSP_SoundSource soundSource)
{
	return static_cast<SoundSource*>(soundSource)->Sound.Get().ID;
}

void E3DRSP_SoundSource_SetSoundID(E3DRSP_SoundSource soundSource, unsigned soundAsset)
{
	static_cast<SoundSource*>(soundSource)->Sound = soundAsset;
}

E3DRSP_Sound E3DRSP_SoundSource_GetSound(E3DRSP_SoundSource soundSource)
{
	return static_cast<SoundSource*>(soundSource)->GetSound();
}

E3DRSP_SoundInstance E3DRSP_SoundSource_GetSoundInstance(E3DRSP_SoundSource soundSource)
{
	return static_cast<SoundSource*>(soundSource)->GetInstance();
}

float E3DRSP_SoundSource_GetVolume(E3DRSP_SoundSource soundSource)
{
	return static_cast<SoundSource*>(soundSource)->Volume;
}

void E3DRSP_SoundSource_SetVolume(E3DRSP_SoundSource soundSource, float volume)
{
	static_cast<SoundSource*>(soundSource)->Volume = volume;
}

float E3DRSP_SoundSource_GetPitch(E3DRSP_SoundSource soundSource)
{
	return static_cast<SoundSource*>(soundSource)->Pitch;
}

void E3DRSP_SoundSource_SetPitch(E3DRSP_SoundSource soundSource, float pitch)
{
	static_cast<SoundSource*>(soundSource)->Pitch = pitch;
}

bool E3DRSP_SoundSource_IsLooping(E3DRSP_SoundSource soundSource)
{
	return static_cast<SoundSource*>(soundSource)->Looping;
}

void E3DRSP_SoundSource_SetLooping(E3DRSP_SoundSource soundSource, bool looping)
{
	static_cast<SoundSource*>(soundSource)->Looping = looping;
}

E3DRSP_Vector3 E3DRSP_SoundSource_GetVelocity(E3DRSP_SoundSource soundSource)
{
	return std::bit_cast<E3DRSP_Vector3>(static_cast<SoundSource*>(soundSource)->Velocity.Get());
}

void E3DRSP_SoundSource_SetVelocity(E3DRSP_SoundSource soundSource, const E3DRSP_Vector3* velocity)
{
	static_cast<SoundSource*>(soundSource)->Velocity = std::bit_cast<Vector3>(*velocity);
}

E3DRSP_Vector3 E3DRSP_SoundSource_GetDirection(E3DRSP_SoundSource soundSource)
{
	return std::bit_cast<E3DRSP_Vector3>(static_cast<SoundSource*>(soundSource)->Direction.Get());
}

void E3DRSP_SoundSource_SetDirection(E3DRSP_SoundSource soundSource, const E3DRSP_Vector3* direction)
{
	static_cast<SoundSource*>(soundSource)->Direction = std::bit_cast<Vector3>(*direction);
}

float E3DRSP_SoundSource_GetMaxDistance(E3DRSP_SoundSource soundSource)
{
	return static_cast<SoundSource*>(soundSource)->MaxDistance;
}

void E3DRSP_SoundSource_SetMaxDistance(E3DRSP_SoundSource soundSource, float distance)
{
	static_cast<SoundSource*>(soundSource)->MaxDistance = distance;
}

float E3DRSP_SoundSource_GetReferenceDistance(E3DRSP_SoundSource soundSource)
{
	return static_cast<SoundSource*>(soundSource)->ReferenceDistance;
}

void E3DRSP_SoundSource_SetReferenceDistance(E3DRSP_SoundSource soundSource, float distance)
{
	static_cast<SoundSource*>(soundSource)->ReferenceDistance = distance;
}

float E3DRSP_SoundSource_GetRolloffFactor(E3DRSP_SoundSource soundSource)
{
	return static_cast<SoundSource*>(soundSource)->RolloffFactor;
}

void E3DRSP_SoundSource_SetRolloffFactor(E3DRSP_SoundSource soundSource, float rolloff)
{
	static_cast<SoundSource*>(soundSource)->RolloffFactor = rolloff;
}

float E3DRSP_SoundSource_GetConeInnerAngle(E3DRSP_SoundSource soundSource)
{
	return static_cast<SoundSource*>(soundSource)->ConeInnerAngle;
}

void E3DRSP_SoundSource_SetConeInnerAngle(E3DRSP_SoundSource soundSource, float angle)
{
	static_cast<SoundSource*>(soundSource)->ConeInnerAngle = angle;
}

float E3DRSP_SoundSource_GetConeOuterAngle(E3DRSP_SoundSource soundSource)
{
	return static_cast<SoundSource*>(soundSource)->ConeOuterAngle;
}

void E3DRSP_SoundSource_SetConeOuterAngle(E3DRSP_SoundSource soundSource, float angle)
{
	static_cast<SoundSource*>(soundSource)->ConeOuterAngle = angle;
}

float E3DRSP_SoundSource_GetConeOuterGain(E3DRSP_SoundSource soundSource)
{
	return static_cast<SoundSource*>(soundSource)->ConeOuterGain;
}

void E3DRSP_SoundSource_SetConeOuterGain(E3DRSP_SoundSource soundSource, float gain)
{
	static_cast<SoundSource*>(soundSource)->ConeOuterGain = gain;
}