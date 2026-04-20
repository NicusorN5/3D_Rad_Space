#include "SoundEffect.h"
#include "../../../Objects/Impl/SoundEffect.hpp"

using namespace Engine3DRadSpace::Objects;

E3DRSP_SoundEffect E3DRSP_SoundEffect_Create()
{
	return new SoundEffect();
}

unsigned E3DRSP_SoundEffect_GetSoundID(E3DRSP_SoundEffect soundEffect)
{
	return static_cast<SoundEffect*>(soundEffect)->Sound.ID;
}

void E3DRSP_SoundEffect_SetSoundID(E3DRSP_SoundEffect soundEffect, unsigned soundAsset)
{
	static_cast<SoundEffect*>(soundEffect)->Sound.ID = soundAsset;
}

E3DRSP_Sound E3DRSP_SoundEffect_GetSound(E3DRSP_SoundEffect soundEffect)
{
	return static_cast<SoundEffect*>(soundEffect)->GetSound();
}

E3DRSP_SoundInstance E3DRSP_SoundEffect_GetSoundInstance(E3DRSP_SoundEffect soundEffect)
{
	return static_cast<SoundEffect*>(soundEffect)->GetInstance();
}

float E3DRSP_SoundEffect_GetVolume(E3DRSP_SoundEffect soundEffect)
{
	return static_cast<SoundEffect*>(soundEffect)->GetVolume();
}

void E3DRSP_SoundEffect_SetVolume(E3DRSP_SoundEffect soundEffect, float volume)
{
	static_cast<SoundEffect*>(soundEffect)->SetVolume(volume);
}

float E3DRSP_SoundEffect_GetPitch(E3DRSP_SoundEffect soundEffect)
{
	return static_cast<SoundEffect*>(soundEffect)->GetPitch();
}

void E3DRSP_SoundEffect_SetPitch(E3DRSP_SoundEffect soundEffect, float pitch)
{
	static_cast<SoundEffect*>(soundEffect)->SetPitch(pitch);
}

bool E3DRSP_SoundEffect_IsLooping(E3DRSP_SoundEffect soundEffect)
{
	return static_cast<SoundEffect*>(soundEffect)->IsLooping();
}

void E3DRSP_SoundEffect_SetLooping(E3DRSP_SoundEffect soundEffect, bool looping)
{
	static_cast<SoundEffect*>(soundEffect)->SetLooping(looping);
}