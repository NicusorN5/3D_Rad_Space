#include "SoundInstance.hpp"
#include "Sound.hpp"
#include <al.h>
#include "../Core/Logging/Exception.hpp"

using namespace Engine3DRadSpace::Audio;
using namespace Engine3DRadSpace::Math;

SoundInstance::SoundInstance(Sound* sound, const AudioSource& source) :
	_source(source),
	_audio(sound->_audio),
	_sound(sound)
{
	//create OpenAL source
	alGenSources(1, &_sourceID);

	//Assign buffer to source.
	SetSource(source);
	alSourcei(_sourceID, AL_BUFFER, sound->_bufferID);
	
	if(_audio->CheckErrors().has_value()) throw Logging::Exception("Failed to assign buffer to source!");
}

SoundInstance::SoundInstance(Sound* sound):
	_audio(sound->_audio),
	_sound(sound)
{
	alGenSources(1, &_sourceID);

	_source = GetSource();
	alSourcei(_sourceID, AL_BUFFER, _sound->_bufferID);
	
	if(_audio->CheckErrors().has_value()) throw Logging::Exception("Failed to assign buffer to source!");
}

const AudioSource& SoundInstance::GetSource()
{
	alGetSourcef(_sourceID, AL_PITCH, &_source.Pitch);
	alGetSourcef(_sourceID, AL_GAIN, &_source.Gain);
	alGetSourcef(_sourceID, AL_MAX_GAIN, &_source.MaxGain);
	alGetSourcef(_sourceID, AL_MIN_GAIN, &_source.MinGain);

	alGetSource3f(
		_sourceID,
		AL_POSITION,
		&_source.Position.X,
		&_source.Position.Y,
		&_source.Position.Z
	);

	alGetSource3f(
		_sourceID,
		AL_VELOCITY,
		&_source.Velocity.X,
		&_source.Velocity.Y,
		&_source.Velocity.Z
	);

	alGetSource3f(
		_sourceID,
		AL_DIRECTION,
		&_source.Direction.X,
		&_source.Direction.Y,
		&_source.Direction.Z
	);

	alGetSourcef(_sourceID, AL_MAX_DISTANCE, &_source.MaxDistance);
	alGetSourcef(_sourceID, AL_REFERENCE_DISTANCE, &_source.ReferenceDistance);
	alGetSourcef(_sourceID, AL_ROLLOFF_FACTOR, &_source.RolloffFactor);
	alGetSourcef(_sourceID, AL_CONE_OUTER_GAIN, &_source.ConeOuterGain);
	alGetSourcef(_sourceID, AL_CONE_INNER_ANGLE, &_source.ConeInnerAngle);
	alGetSourcef(_sourceID, AL_CONE_OUTER_ANGLE, &_source.ConeOuterAngle);

	ALint looping;
	alGetSourcei(_sourceID, AL_LOOPING, &looping);
	_source.Looping = looping == AL_TRUE ? AL_TRUE : AL_FALSE;

	return _source;
}

void SoundInstance::SetSource(const AudioSource& source)
{
	_source = source;

	alSourcef(_sourceID, AL_PITCH, _source.Pitch);
	alSourcef(_sourceID, AL_GAIN, _source.Gain);
	alSourcef(_sourceID, AL_MAX_GAIN, _source.MaxGain);
	alSourcef(_sourceID, AL_MIN_GAIN, _source.MinGain);

	alSource3f(
		_sourceID,
		AL_POSITION,
		_source.Position.X,
		_source.Position.Y,
		_source.Position.Z
	);

	alSource3f(
		_sourceID,
		AL_VELOCITY,
		_source.Velocity.X,
		_source.Velocity.Y,
		_source.Velocity.Z
	);

	alSource3f(
		_sourceID,
		AL_DIRECTION,
		_source.Direction.X,
		_source.Direction.Y,
		_source.Direction.Z
	);

	alSourcef(_sourceID, AL_MAX_DISTANCE, _source.MaxDistance);
	alSourcef(_sourceID, AL_REFERENCE_DISTANCE, _source.ReferenceDistance);
	alSourcef(_sourceID, AL_ROLLOFF_FACTOR, _source.RolloffFactor);
	alSourcef(_sourceID, AL_CONE_OUTER_GAIN, _source.ConeOuterGain);
	alSourcef(_sourceID, AL_CONE_INNER_ANGLE, _source.ConeInnerAngle);
	alSourcef(_sourceID, AL_CONE_OUTER_ANGLE, _source.ConeOuterAngle);

	auto looping = _source.Looping ? AL_TRUE : AL_FALSE;
	alSourcei(_sourceID, AL_LOOPING, looping);

	if(_audio->CheckErrors().has_value()) throw int(5);
}

SoundState SoundInstance::GetState()
{
	int sourceState;
	alGetSourcei(_sourceID, AL_SOURCE_STATE, &sourceState);

	if(_audio->CheckErrors().has_value()) return SoundState::Undefined;

	switch(sourceState)
	{
		case AL_PLAYING:
			return SoundState::Playing;
		case AL_STOPPED:
			return SoundState::Stopped;
		case AL_PAUSED:
			return SoundState::Paused;
		case AL_INITIAL:
			return SoundState::Stopped;
		default:
			return SoundState::Undefined;
	}
}

void SoundInstance::Play()
{
	//if(GetState() == SoundState::Playing) return; //do not overlap the same sound instance
	//alGetError();

	alSourcePlay(_sourceID);

	if(_audio->CheckErrors().has_value()) throw int(5);
}

void Engine3DRadSpace::Audio::SoundInstance::Stop()
{
	alSourceStop(_sourceID);
	if(_audio->CheckErrors().has_value()) throw float(5);
}

void Engine3DRadSpace::Audio::SoundInstance::Pause()
{
	alSourcePause(_sourceID);
	if(_audio->CheckErrors().has_value()) throw float(6);
}

SoundInstance::~SoundInstance()
{
	alDeleteSources( 1, &_sourceID);
}

void SoundInstance::SetPitch(float pitch)
{
	_source.Pitch = pitch;
	alSourcef(_sourceID, AL_PITCH, pitch);
}

void SoundInstance::SetGain(float gain)
{
	_source.Gain = gain;
	alSourcef(_sourceID, AL_GAIN, gain);
}

void SoundInstance::SetMaxGain(float maxGain)
{
	_source.MaxGain = maxGain;
	alGetSourcef(_sourceID, AL_MAX_GAIN, &maxGain);
}

void SoundInstance::SetMinGain(float minGain)
{
	_source.MinGain = minGain;
	alGetSourcef(_sourceID, AL_MIN_GAIN, &minGain);
}

void SoundInstance::SetPosition(const Math::Vector3& pos)
{
	_source.Position = pos;
	alSource3f(
		_sourceID,
		AL_POSITION,
		pos.X,
		pos.Y,
		pos.Z
	);
}

void SoundInstance::SetVelocity(const Math::Vector3& vel)
{
	_source.Velocity = vel;
	alSource3f(
		_sourceID,
		AL_VELOCITY,
		vel.X,
		vel.Y,
		vel.Z
	);
}

void SoundInstance::SetDirection(const Math::Vector3& dir)
{
	_source.Direction = dir;
	alSource3f(
		_sourceID,
		AL_DIRECTION,
		dir.X,
		dir.Y,
		dir.Z
	);
}

void SoundInstance::SetMaxDistance(float distance)
{
	_source.MaxDistance = distance;
	alSourcef(_sourceID, AL_MAX_DISTANCE, distance);
}

void SoundInstance::SetReferenceDistance(float refDistance)
{
	_source.ReferenceDistance = refDistance;
	alSourcef(_sourceID, AL_REFERENCE_DISTANCE, refDistance);
}

void SoundInstance::SetRolloffFactor(float rolloff)
{
	_source.RolloffFactor = rolloff;
	alSourcef(_sourceID, AL_ROLLOFF_FACTOR, rolloff);
}

void SoundInstance::SetConeOuterGain(float outerGain)
{
	_source.ConeOuterGain = outerGain;
	alSourcef(_sourceID, AL_CONE_OUTER_GAIN, outerGain);
}

void SoundInstance::SetConeInnerAngle(float angle)
{
	_source.ConeInnerAngle = angle;
	alSourcef(_sourceID, AL_CONE_INNER_ANGLE, angle);
}

void SoundInstance::SetConeOuterAngle(float angle)
{
	_source.ConeOuterAngle = angle;
	alSourcef(_sourceID, AL_CONE_OUTER_ANGLE, angle);
}

float SoundInstance::GetPitch()
{
	float pitch;
	alGetSourcef(_sourceID, AL_PITCH, &pitch);
	return pitch;
}

float SoundInstance::GetGain()
{
	float gain;
	alGetSourcef(_sourceID, AL_GAIN, &gain);
	return gain;
}

float SoundInstance::GetMaxGain()
{
	float maxGain;
	alGetSourcef(_sourceID, AL_MAX_GAIN, &maxGain);
	return maxGain;
}

float SoundInstance::GetMinGain()
{
	float minGain;
	alGetSourcef(_sourceID, AL_MIN_GAIN, &minGain);
	return minGain;
}

Vector3 SoundInstance::GetPosition()
{
	Vector3 pos;
	alGetSource3f(
		_sourceID,
		AL_POSITION,
		&pos.X,
		&pos.Y,
		&pos.Z
	);
	return pos;
}

Vector3 SoundInstance::GetVelocity()
{
	Vector3 vel;
	alGetBuffer3f(
		_sourceID,
		AL_VELOCITY,
		&vel.X,
		&vel.Y,
		&vel.Z
	);
	return vel;
}

Vector3 SoundInstance::GetDirection()
{
	Vector3 dir;
	alGetSource3f(
		_sourceID,
		AL_VELOCITY,
		&dir.X,
		&dir.Y,
		&dir.Z
	);
	return dir;
}

float SoundInstance::GetMaxDistance()
{
	float maxDistance;
	alGetSourcef(_sourceID, AL_MAX_DISTANCE, &maxDistance);
	return maxDistance;
}

float SoundInstance::GetReferenceDistance()
{
	float ref_dst;
	alGetSourcef(_sourceID, AL_REFERENCE_DISTANCE, &ref_dst);
	return ref_dst;
}

float SoundInstance::GetRolloffFactor()
{
	float rolloff;
	alGetSourcef(_sourceID, AL_ROLLOFF_FACTOR, &rolloff);
	return rolloff;
}

float SoundInstance::GetConeOuterGain()
{
	float coneOuter;
	alGetSourcef(_sourceID, AL_CONE_OUTER_GAIN, &coneOuter);
	return coneOuter;
}

float SoundInstance::GetConeInnerAngle()
{
	float angle;
	alGetSourcef(_sourceID, AL_CONE_INNER_ANGLE, &angle);
	return angle;
}

float SoundInstance::GetConeOuterAngle()
{
	float angle;
	alGetSourcef(_sourceID, AL_CONE_OUTER_ANGLE, &angle);
	return angle;
}

void SoundInstance::SetLooping(bool looping)
{
	ALint a = looping ? AL_TRUE : AL_FALSE;
	alSourcei(_sourceID, AL_LOOPING, a);
}

bool SoundInstance::IsLooping()
{
	ALint looping;
	alGetSourcei(_sourceID, AL_LOOPING, &looping);
	return looping == AL_TRUE;
}
