#include "AudioBuffer.h"
#include "../../Audio/AudioBuffer.hpp"

using namespace Engine3DRadSpace::Audio;

E3DRSP_AudioBuffer E3DRSP_AudioBuffer_Create(char* buffer, int numChannels, int sampleRate, int bps, int format, int size)
{
	assert(buffer != nullptr);
	return new AudioBuffer(buffer, numChannels, sampleRate, bps, format, size);
}

E3DRSP_AudioBuffer E3DRSP_AudioBuffer_FromWAV(const char* path)
{
	assert(path != nullptr);

	auto audioBuffer = AudioBuffer::FromWAV(path);
	if(audioBuffer.has_value())
	{
		return new AudioBuffer(std::move(audioBuffer.value()));
	}
	else return nullptr;
}

E3DRSP_AudioBuffer E3DRSP_AudioBuffer_FromOGG(const char* path)
{
	assert(path != nullptr);

	auto audioBuffer = AudioBuffer::FromOGG(path);
	if(audioBuffer.has_value())
	{
		return new AudioBuffer(std::move(audioBuffer.value()));
	}
	else return nullptr;
}

void E3DRSP_AudioBuffer_Destroy(E3DRSP_AudioBuffer audioBuffer)
{
	assert(audioBuffer != nullptr);
	delete static_cast<AudioBuffer*>(audioBuffer);
}