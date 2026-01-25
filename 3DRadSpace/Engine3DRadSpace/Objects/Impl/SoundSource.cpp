#include "SoundSource.hpp"
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