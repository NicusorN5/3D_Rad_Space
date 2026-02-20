#include "SoundSource.hpp"
#include "SoundSource.h"
#include "Gizmos.hpp"
#include "Gizmos/SoundSourceGizmo.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Audio;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Objects::Gizmos;

#define SS_INITIALIZE \
Sound(this), \
Volume(this), \
Pitch(this), \
Looping(this), \
Velocity(this), \
Direction(this), \
MaxDistance(this), \
ReferenceDistance(this), \
RolloffFactor(this), \
ConeOuterGain(this), \
ConeInnerAngle(this), \
ConeOuterAngle(this), \
_volume(1.0f), \
_pitch(1.0f), \
_looping(false), \
_maxDistance(std::numeric_limits<float>::max()), \
_referenceDistance(1.0f), \
_rolloffFactor(1.0f), \
_coneOuterGain(0.0f), \
_coneInnerAngle(360.0f), \
_coneOuterAngle(360.0f)

#define SS_SETPARAM \
_setVolume(_volume); \
_setPitch(_pitch); \
_setLooping(_looping); \
_setVelocity(_velocity); \
_setDirection(_direction); \
_setMaxDistance(_maxDistance); \
_setReferenceDistance(_referenceDistance); \
_setRolloffFactor(_rolloffFactor); \
_setConeOuterGain(_coneOuterGain); \
_setConeInnerAngle(_coneInnerAngle); \
_setConeOuterAngle(_coneOuterAngle); 

SoundSource::SoundSource() : SS_INITIALIZE
{
}

SoundSource::SoundSource(
	const std::string& name,
	bool enabled,
	RefSound sound,
	const Vector3& position
) : IObject3D(name, enabled, false, Position),
	SS_INITIALIZE
{
	_underlying.Sound = sound;
}

SoundSource::SoundSource(
	const std::string & name,
	bool enabled, 
	const std::filesystem::path & soundFile,
	const Math::Vector3 &position
) : IObject3D(name, enabled, false, Position),
	SS_INITIALIZE
{
}

RefSound SoundSource::_getAsset() const noexcept
{
	return _underlying.Sound;
}

void SoundSource::_setAsset(RefSound sound) noexcept
{
	_underlying.Sound = sound;
}

float SoundSource::_getVolume() const noexcept
{
	return _underlying.Volume;
}

void SoundSource::_setVolume(float volume) noexcept
{
	_underlying.Volume = volume;
}

float SoundSource::_getPitch() const noexcept
{
	return _underlying.Pitch;
}

void SoundSource::_setPitch(float pitch) noexcept
{
	_underlying.Pitch = pitch;
}

bool SoundSource::_getLooping() const noexcept
{
	return _underlying.Looping;
}

void SoundSource::_setLooping(bool looping) noexcept
{
	_underlying.Looping = looping;
}


Vector3 SoundSource::_getVelocity() const noexcept
{
	auto instance = GetInstance();
	return instance ? instance->GetVelocity() : _velocity;
}

void SoundSource::_setVelocity(const Vector3 &velocity) noexcept
{
	auto instance = GetInstance();
	if(instance)
		instance->SetVelocity(velocity);
	else
		_velocity = velocity;
}

Vector3 SoundSource::_getDirection() const noexcept
{
	auto instance = GetInstance();
	return instance ? instance->GetVelocity() : _direction;
}

void SoundSource::_setDirection(const Vector3& direction) noexcept
{
	auto instance = GetInstance();
	if(instance)
		instance->SetDirection(direction);
	else
		_direction = direction;
}

float SoundSource::_getMaxDistance() const noexcept
{
	auto instance = GetInstance();
	return instance ? instance->GetMaxDistance() : _maxDistance;
}

void SoundSource::_setMaxDistance(float distance) noexcept
{
	auto instance = GetInstance();
	if(instance)
		instance->SetMaxDistance(distance);
	else _maxDistance = distance;
}

float SoundSource::_getReferenceDistance() const noexcept
{
	auto instance = GetInstance();
	return instance ? instance->GetReferenceDistance() : _referenceDistance;
}

void SoundSource::_setReferenceDistance(float refDst) noexcept
{
	auto instance = GetInstance();
	if(instance)
		instance->SetReferenceDistance(refDst);
	else
		_referenceDistance = refDst;
}

float SoundSource::_getRolloffFactor() const noexcept
{
	auto instance = GetInstance();
	return instance ? instance->GetRolloffFactor() : _rolloffFactor;
}

void SoundSource::_setRolloffFactor(float rollOff) noexcept
{
	auto instance = GetInstance();
	if(instance)
		instance->SetRolloffFactor(rollOff);
	else
		_rolloffFactor = rollOff;
}

float SoundSource::_getConeInnerAngle() const noexcept
{
	auto instance = GetInstance();
	return instance ? instance->GetConeInnerAngle() : _coneInnerAngle;
}

void SoundSource::_setConeInnerAngle(float innerAngle) noexcept
{
	auto instance = GetInstance();
	if(instance)
		instance->SetConeInnerAngle(innerAngle);
	else
		_coneInnerAngle = innerAngle;
}

float SoundSource::_getConeOuterAngle() const noexcept
{
	auto instance = GetInstance();
	return instance ? instance->GetConeOuterAngle() : _coneOuterAngle;
}

void SoundSource::_setConeOuterAngle(float outerAngle) noexcept
{
	auto instance = GetInstance();
	if(instance)
		instance->SetConeOuterAngle(outerAngle);
	else
		_coneOuterAngle = outerAngle;
}

float SoundSource::_getConeOuterGain() const noexcept
{
	auto instance = GetInstance();
	return instance ? instance->GetConeOuterGain() : _coneOuterGain;
}

void SoundSource::_setConeOuterGain(float outerGain) noexcept
{
	auto instance = GetInstance();
	if(instance)
		instance->SetConeOuterGain(outerGain);
	else
		_coneOuterGain = outerGain;
}

void SoundSource::Draw3D()
{
}

float SoundSource::Intersects(const Math::Ray & r)
{
	return r.Intersects(Math::BoundingSphere(Position, 1.0f));
}

Reflection::UUID SoundSource::GetUUID() const noexcept
{
	// {4F91C443-67C3-40C3-9676-A13A84715D2B}
	return {0x4f91c443, 0x67c3, 0x40c3, { 0x96, 0x76, 0xa1, 0x3a, 0x84, 0x71, 0x5d, 0x2b }};
}

void SoundSource::Initialize()
{
	_underlying.Initialize();
}

void SoundSource::Update()
{
	_underlying.Update();

	auto instance = _underlying.GetInstance();
	if(instance != nullptr)
		instance->SetPosition(Position);
}

void SoundSource::Load()
{
	_underlying.Load();
	SS_SETPARAM
}

void SoundSource::Load(const std::filesystem::path &path)
{
	_underlying.Load(path);
	//SS_SETPARAM;
}

Objects::Gizmos::IGizmo *SoundSource::GetGizmo() const noexcept
{
	return Internal::GizmoOf<SoundSource>(this);
}

void SoundSource::Enable()
{
	_underlying.Enable();
}

void SoundSource::Disable()
{
	_underlying.Disable();
}

bool SoundSource::Switch()
{
	return _underlying.Switch();
}

Sound* SoundSource::GetSound() const noexcept
{
	return _underlying.GetSound();
}

SoundInstance* SoundSource::GetInstance() const noexcept
{
	return _underlying.GetInstance();
}

#undef SS_INITIALIZE
#undef SS_SETPARAM

REFL_BEGIN(SoundSource, "SoundSource", "Sound", "3D Localized sound source")
REFL_FIELD(SoundSource, std::string, Name, "Name", "SoundSource", "Name of the object")
REFL_FIELD(SoundSource, bool, Enabled, "Playing at start",true, "Playing at startup")
REFL_FIELD(SoundSource, RefSound, Sound, "Sound asset", 0, "Sound asset")
REFL_FIELD(SoundSource, Vector3, Position, "Position", Vector3::Zero(), "Sound position")
REFL_FIELD(SoundSource, float, Volume, "Volume", 1.0f, "Sound gain")
REFL_FIELD(SoundSource, float, Pitch, "Pitch", 0.5f, "Sound pitch")
REFL_FIELD(SoundSource, bool, Looping, "Is looping", true, "Is the sound looping?")
REFL_END

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