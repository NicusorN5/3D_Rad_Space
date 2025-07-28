#include "AudioEngine.hpp"
#include "AudioEngine.h"
#include "../Core/Logging/Exception.hpp"

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
		throw Exception("Failed to create audio context!");
	}

	alcMakeContextCurrent(static_cast<ALCcontext*>(_audioContext));

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

void AudioEngine::SwitchAudioDevice(const std::string& deviceName)
{
	this->~AudioEngine();

	_audioDevice = alcOpenDevice(deviceName.c_str());
	if (!_audioDevice)
	{
		throw Exception("Audio device initialization failed! " + deviceName + " was specified.");
	}

	_initializeContext();
}

AudioEngine::~AudioEngine()
{
	auto context = static_cast<ALCcontext*>(_audioContext);
	auto device = alcGetContextsDevice(context);

	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

void AudioEngine::Update() const noexcept
{
	if(this->Listener.Enabled)
	{
		alListenerf(AL_GAIN, this->Listener.Volume);

		alListener3f(
			AL_POSITION,
			this->Listener.Position.X,
			this->Listener.Position.Y,
			this->Listener.Position.Z
		);

		alListener3f(
			AL_VELOCITY,
			this->Listener.Velocity.X,
			this->Listener.Velocity.Y,
			this->Listener.Velocity.Z
		);

		float orientation[6] =
		{
			this->Listener.Direction.X,
			this->Listener.Direction.Y,
			this->Listener.Direction.Z,
			this->Listener.Normal.X,
			this->Listener.Normal.Y,
			this->Listener.Normal.Z,
		};

		alListenerfv(AL_ORIENTATION, orientation);
	}
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

E3DRSP_AudioEngine E3DRSP_AudioEngine_Create()
{
	return new AudioEngine();
}

E3DRSP_AudioEngine E3DRSP_AudioEngine_Create1(const char* deviceName)
{
	return new AudioEngine(deviceName);
}

char** E3DRSP_AudioEngine_ListAudioDevices()
{
	auto devices = AudioEngine::ListAudioDevices();

	size_t length = devices.size();
	char** result = new char*[length + 1];
	if(result == nullptr) return nullptr;

	for(size_t i = 0; i < length; ++i)
	{
		size_t deviceNameLength = devices[i].length() + 1;

		char* deviceName = new char[deviceNameLength];
		//I had cases where strings inside std::string wasn't null terminated, but somehow valid. (that happened when using ASan few months ago)
		memset(deviceName, 0, deviceNameLength);
		memcpy(deviceName, devices[i].c_str(), deviceNameLength - 1); 

		result[i] = deviceName;
	}
	result[devices.size()] = 0; //null terminate the list of strings.

	return result;
}

void E3DRSP_AudioEngine_Update(E3DRSP_AudioEngine audio)
{
	static_cast<AudioEngine*>(audio)->Update();
}

E3DRSP_AudioError E3DRSP_AudioEngine_CheckErrors(E3DRSP_AudioEngine audio)
{
	auto err = static_cast<AudioEngine*>(audio)->CheckErrors();
	if(!err.has_value()) return E3DRSP_AudioError_None;
	else return static_cast<E3DRSP_AudioError>(err.value());
}

void E3DRSP_AudioEngine_SwitchAudioDevice(E3DRSP_AudioEngine audio, const char* deviceName)
{
	static_cast<AudioEngine*>(audio)->SwitchAudioDevice(deviceName);
}

void E3DRSP_AudioEngine_Destroy(E3DRSP_AudioEngine audio)
{
	delete static_cast<AudioEngine*>(audio);
}