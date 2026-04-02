#include "AudioEngine.h"
#include "../../Audio/AudioEngine.hpp"

using namespace Engine3DRadSpace::Audio;

E3DRSP_IAudioEngine E3DRSP_AudioEngine_Create()
{
	return new AudioEngine();
}

E3DRSP_IAudioEngine E3DRSP_AudioEngine_Create1(const char* deviceName)
{
	if(deviceName == nullptr) return E3DRSP_AudioEngine_Create();
	return new AudioEngine(deviceName);
}

char** E3DRSP_AudioEngine_ListAudioDevices()
{
	auto devices = AudioEngine::ListAudioDevices();

	size_t length = devices.size();
	char** result = new char* [length + 1];
	if(result == nullptr) return nullptr;

	for(size_t i = 0; i < length; ++i)
	{
		size_t deviceNameLength = devices[i].length() + 1;

		char* deviceName = new char[deviceNameLength];
		//I had cases where strings inside std::string wasn't null terminated, but somehow valid. (that happened when using ASan few months ago)
		memset(deviceName, 0, deviceNameLength);
		memcpy_s(deviceName, deviceNameLength - 1, devices[i].c_str(), deviceNameLength - 1);

		result[i] = deviceName;
	}
	result[devices.size()] = 0; //null terminate the list of strings.

	return result;
}