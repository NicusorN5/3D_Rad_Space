#include "SoundEffect.hpp"
#include "SoundEffect.h"
#include "../Games/Game.hpp"
#include "../Content/ContentManager.hpp"
#include "SoundSource.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Audio;
using namespace Engine3DRadSpace::Objects;

#define SE_INITIALIZE \
Volume(this), \
Pitch(this), \
Looping(this), \
_volume(1.0f), \
_pitch(1.0f), \
_looping(false)

#define SE_SETPARAM \
_setVolume(_volume); \
_setPitch(_pitch); \
_setLooping(_looping);

float SoundEffect::_getVolume() const noexcept
{
	return _instance != nullptr ? _instance->GetGain() : _volume;
}

void SoundEffect::_setVolume(float volume) noexcept
{
	if(_instance != nullptr)
		_instance->SetGain(volume);
	else _volume = volume;
}

float SoundEffect::_getPitch() const noexcept
{
	return _instance != nullptr ? _instance->GetPitch() : _pitch;
}

void SoundEffect::_setPitch(float pitch) noexcept
{
	if(_instance != nullptr)
		_instance->SetPitch(pitch);
	else _pitch = pitch;
}

bool SoundEffect::_getLooping() const noexcept
{
	return _instance != nullptr ? _instance->IsLooping() : _looping;
}

void SoundEffect::_setLooping(bool looping) noexcept
{
	if(_instance != nullptr)
		_instance->SetLooping(looping);
	else _looping = looping;
}

SoundEffect::SoundEffect() : IObject("SoundEffect", true),
	_sound(nullptr),
	SE_INITIALIZE
{
}

SoundEffect::SoundEffect(
	const std::string& name,
	bool enabled,
	RefSound sound
) : IObject(name, enabled),
	Sound(sound),
	_sound(nullptr),
	SE_INITIALIZE
{
}

SoundEffect::SoundEffect(
	const std::string& name,
	bool enabled,
	const std::filesystem::path& path
) : SoundEffect(name, enabled, 0)
{
	_path = std::make_unique<std::string>(path.string());
}

Sound* SoundEffect::GetSound() const noexcept
{
	return _sound;
}

SoundInstance* SoundEffect::GetInstance() const noexcept
{
	return _instance.get();
}

void SoundEffect::Initialize()
{
}

void SoundEffect::Load()
{
	auto game = static_cast<Game*>(_game);

	if (_path != nullptr)
	{
		_sound = game->Content->Load<class Sound>(*_path);
		_path.reset();
	}
	if(Sound)
	{
		_sound = static_cast<class Sound*>((*game->Content)[Sound]);
	}

	if(_sound) _instance = std::make_unique<SoundInstance>(_sound);

	SE_SETPARAM;
}

void SoundEffect::Load(const std::filesystem::path& path)
{
	auto game = static_cast<Game*>(_game);

	_sound = game->Content->Load<class Sound>(*_path);
	if(_sound) _instance = std::make_unique<SoundInstance>(_sound);

	SE_SETPARAM;
}

void SoundEffect::Update()
{
}

void SoundEffect::Enable()
{
	IObject::Enable();
	_instance->Play();
}

void SoundEffect::Disable()
{
	IObject::Disable();
	_instance->Pause();
}

bool SoundEffect::Switch()
{
	auto r = IObject::Switch();
	_instance->GetState() == Audio::SoundState::Playing ? _instance->Pause() : _instance->Play();
	return r;
}

Reflection::UUID SoundEffect::GetUUID() const noexcept
{
	// {4C9A4E2A-99DC-4E61-B5CB-3D75B569531F}
	return { 0x4c9a4e2a, 0x99dc, 0x4e61, { 0xb5, 0xcb, 0x3d, 0x75, 0xb5, 0x69, 0x53, 0x1f } };
}

Gizmos::IGizmo* SoundEffect::GetGizmo() const noexcept
{
	return nullptr;
}

#undef SE_INITIALIZE
#undef SE_SETPARAM

REFL_BEGIN(SoundEffect, "SoundEffect", "Sound", "Background sound")
REFL_FIELD(SoundEffect, std::string, Name, "Name", "SoundEffect", "ObjectName")
REFL_FIELD(SoundEffect, bool, Enabled, "Play at start", true, "If playing when initialized.")
REFL_FIELD(SoundEffect, RefSound, Sound, "Sound", 0, "Sound asset")
REFL_FIELD_GS(SoundEffect, Looping, "Looping", false, "Is the sound looping")
REFL_FIELD_GS(SoundEffect, Volume, "Volume", 1.0f, "Volume (0-1 range)")
REFL_FIELD_GS(SoundEffect, Pitch, "Pitch", 0.5f, "Pitch (??-?? range), ?? default")
REFL_END

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
	return static_cast<SoundEffect*>(soundEffect)->Volume;
}

void E3DRSP_SoundEffect_SetVolume(E3DRSP_SoundEffect soundEffect, float volume)
{
	static_cast<SoundEffect*>(soundEffect)->Volume = volume;
}

float E3DRSP_SoundEffect_GetPitch(E3DRSP_SoundEffect soundEffect)
{
	return static_cast<SoundEffect*>(soundEffect)->Pitch;
}

void E3DRSP_SoundEffect_SetPitch(E3DRSP_SoundEffect soundEffect, float pitch)
{
	static_cast<SoundEffect*>(soundEffect)->Pitch = pitch;
}

bool E3DRSP_SoundEffect_IsLooping(E3DRSP_SoundEffect soundEffect)
{
	return static_cast<SoundEffect*>(soundEffect)->Looping;
}

void E3DRSP_SoundEffect_SetLooping(E3DRSP_SoundEffect soundEffect, bool looping)
{
	static_cast<SoundEffect*>(soundEffect)->Looping = looping;
}