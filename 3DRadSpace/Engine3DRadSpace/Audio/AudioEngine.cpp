#include "AudioEngine.hpp"
#include "../Logging/Exception.hpp"

#include <AL/al.h>
#include <AL/alc.h>

using namespace Engine3DRadSpace::Audio;
using namespace Engine3DRadSpace::Logging;

void AudioEngine::_initializeContext()
{
	//Create audio scene
	_audioContext = alcCreateContext(static_cast<ALCdevice*>(_audioDevice), nullptr);
	if(!_audioContext)
	{
		throw Exception("Failed to create audio scene!");
	}

	alcMakeContextCurrent(static_cast<ALCcontext*>(_audioContext));

	_hasEAX2support = static_cast<bool>(alIsExtensionPresent("EAX2.0"));

	alGetError(); //clear error flag
}

AudioEngine::AudioEngine()
{
	//Createa default audio device
	_audioDevice = alcOpenDevice(nullptr);
	if(!_audioDevice)
	{
		throw Exception("Audio device initialization failed!");
	}

	_initializeContext();
}

AudioEngine::AudioEngine(const std::string& deviceName)
{
	//Createa default audio device
	_audioDevice = alcOpenDevice(deviceName.c_str());
	if(!_audioDevice)
	{
		throw Exception("Audio device initialization failed! " + deviceName +" was specified.");
	}

	_initializeContext();
}

std::vector<std::string> AudioEngine::ListAudioDevices()
{
	std::vector<std::string> deviceList;

	auto str = alcGetString(NULL, ALC_DEVICE_SPECIFIER);

	const ALCchar* device = str, * next = str + 1;

	//https://ffainelli.github.io/openal-example/
	while (device && *device != '\0' && next && *next != '\0') {
		deviceList.push_back(device);

		size_t len = strlen(device);
		device += (len + 1);
		next += (len + 2);
	}

	return deviceList;
}

void AudioEngine::SetListener(const Math::Vector3& vector)
{
	alListener3f(0, vector.X, vector.Y, vector.Z);
}

bool AudioEngine::HasEAX2Support() const noexcept
{
	return _hasEAX2support;
}

AudioEngine::~AudioEngine()
{
	auto context = static_cast<ALCcontext*>(_audioContext);
	auto device = alcGetContextsDevice(context);

	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

void AudioEngine::Update(double dt)
{
}

std::optional<AudioError> AudioEngine::CheckErrors()
{
	ALenum error = alGetError();
	if(error == AL_NO_ERROR) return std::nullopt;

	switch(error)
	{
		case AL_INVALID_NAME:
			return AudioError::BadID;
		case AL_INVALID_ENUM:
			return AudioError::InvalidEnum;
		case AL_INVALID_VALUE:
			return AudioError::InvalidValue;
		case AL_INVALID_OPERATION:
			return AudioError::InvalidOperation;
		case AL_OUT_OF_MEMORY:
			return AudioError::OutOfMemory;
		default:
			return AudioError::Unspecified;
	}
}
