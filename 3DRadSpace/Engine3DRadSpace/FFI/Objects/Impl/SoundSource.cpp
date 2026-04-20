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
	return static_cast<SoundSource*>(soundSource)->GetSoundAsset();
}

void E3DRSP_SoundSource_SetSoundID(E3DRSP_SoundSource soundSource, unsigned soundAsset)
{
	static_cast<SoundSource*>(soundSource)->SetSoundAsset(soundAsset);
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
	return static_cast<SoundSource*>(soundSource)->GetVolume();
}

void E3DRSP_SoundSource_SetVolume(E3DRSP_SoundSource soundSource, float volume)
{
	static_cast<SoundSource*>(soundSource)->SetVolume(volume);
}

float E3DRSP_SoundSource_GetPitch(E3DRSP_SoundSource soundSource)
{
	return static_cast<SoundSource*>(soundSource)->GetPitch();
}

void E3DRSP_SoundSource_SetPitch(E3DRSP_SoundSource soundSource, float pitch)
{
	static_cast<SoundSource*>(soundSource)->SetPitch(pitch);
}

bool E3DRSP_SoundSource_IsLooping(E3DRSP_SoundSource soundSource)
{
	return static_cast<SoundSource*>(soundSource)->IsLooping();
}

void E3DRSP_SoundSource_SetLooping(E3DRSP_SoundSource soundSource, bool looping)
{
	static_cast<SoundSource*>(soundSource)->SetLooping(looping);
}

E3DRSP_Vector3 E3DRSP_SoundSource_GetVelocity(E3DRSP_SoundSource soundSource)
{
	return std::bit_cast<E3DRSP_Vector3>(static_cast<SoundSource*>(soundSource)->GetVelocity());
}

void E3DRSP_SoundSource_SetVelocity(E3DRSP_SoundSource soundSource, const E3DRSP_Vector3* velocity)
{
	static_cast<SoundSource*>(soundSource)->SetVelocity(std::bit_cast<Vector3>(*velocity));
}

E3DRSP_Vector3 E3DRSP_SoundSource_GetDirection(E3DRSP_SoundSource soundSource)
{
	return std::bit_cast<E3DRSP_Vector3>(static_cast<SoundSource*>(soundSource)->GetDirection());
}

void E3DRSP_SoundSource_SetDirection(E3DRSP_SoundSource soundSource, const E3DRSP_Vector3* direction)
{
	static_cast<SoundSource*>(soundSource)->SetDirection(std::bit_cast<Vector3>(*direction));
}

float E3DRSP_SoundSource_GetMaxDistance(E3DRSP_SoundSource soundSource)
{
	return static_cast<SoundSource*>(soundSource)->GetMaxDistance();
}

void E3DRSP_SoundSource_SetMaxDistance(E3DRSP_SoundSource soundSource, float distance)
{
	static_cast<SoundSource*>(soundSource)->SetMaxDistance(distance);
}

float E3DRSP_SoundSource_GetReferenceDistance(E3DRSP_SoundSource soundSource)
{
	return static_cast<SoundSource*>(soundSource)->GetReferenceDistance();
}

void E3DRSP_SoundSource_SetReferenceDistance(E3DRSP_SoundSource soundSource, float distance)
{
	static_cast<SoundSource*>(soundSource)->SetReferenceDistance(distance);
}

float E3DRSP_SoundSource_GetRolloffFactor(E3DRSP_SoundSource soundSource)
{
	return static_cast<SoundSource*>(soundSource)->GetRolloffFactor();
}

void E3DRSP_SoundSource_SetRolloffFactor(E3DRSP_SoundSource soundSource, float rolloff)
{
	static_cast<SoundSource*>(soundSource)->SetRolloffFactor(rolloff);
}

float E3DRSP_SoundSource_GetConeInnerAngle(E3DRSP_SoundSource soundSource)
{
	return static_cast<SoundSource*>(soundSource)->GetConeInnerAngle();
}

void E3DRSP_SoundSource_SetConeInnerAngle(E3DRSP_SoundSource soundSource, float angle)
{
	static_cast<SoundSource*>(soundSource)->SetConeInnerAngle(angle);
}

float E3DRSP_SoundSource_GetConeOuterAngle(E3DRSP_SoundSource soundSource)
{
	return static_cast<SoundSource*>(soundSource)->GetConeOuterAngle();
}

void E3DRSP_SoundSource_SetConeOuterAngle(E3DRSP_SoundSource soundSource, float angle)
{
	static_cast<SoundSource*>(soundSource)->SetConeOuterAngle(angle);
}

float E3DRSP_SoundSource_GetConeOuterGain(E3DRSP_SoundSource soundSource)
{
	return static_cast<SoundSource*>(soundSource)->GetConeOuterGain();
}

void E3DRSP_SoundSource_SetConeOuterGain(E3DRSP_SoundSource soundSource, float gain)
{
	static_cast<SoundSource*>(soundSource)->SetConeOuterGain(gain);
}