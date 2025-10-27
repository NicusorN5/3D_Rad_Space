#include "Sound.hpp"
#include "Sound.h"
#include "../Internal/AssetUUIDReader.hpp"
#include "../Core/Logging/Exception.hpp"
#include <al.h>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Audio;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Reflection;

AudioBuffer Sound::_attemptLoading(const std::filesystem::path& path)
{
	auto wav = AudioBuffer::FromWAV(path);
	if(wav.has_value()) return std::move(wav.value());

	auto ogg = AudioBuffer::FromOGG(path);
	if(ogg.has_value()) return std::move(ogg.value());

	throw Exception("Failed to load a sound file! Invalid format or corrupted file!");
}

Sound::Sound(Internal::AssetUUIDReader dummy) :
	_audio(nullptr),
	_bufferID(0)
{
}

Sound::Sound(IService *audio, const std::filesystem::path& path) :
	_audio(static_cast<AudioEngine*>(audio))
{
	AudioBuffer sound(std::move(_attemptLoading(path)));

	//Generate OpenAL sound buffer
	alGenBuffers(1, &_bufferID); //Create one buffer
	alBufferData(_bufferID, sound._format, sound._buffer.get(), sound._size, sound._sampleRate); //Set buffer.
	if(_audio->CheckErrors().has_value()) throw Exception("Failed to copy OpenAL buffer!");
}

Sound::Sound(Sound&& snd) noexcept
{
	*this = std::move(snd);
}

Sound& Sound::operator=(Sound&& snd) noexcept
{
	if(this == &snd) return *this;

	if(this->_bufferID != snd._bufferID)
	{
		alDeleteBuffers(1, &_bufferID);
		_bufferID = snd._bufferID;
		snd._bufferID = 0;
	}

	this->_audio = snd._audio;
	snd._audio = nullptr;

	return *this;
}

Reflection::UUID Sound::GetUUID() const noexcept
{
	// {D975E8DE-7373-4560-90FB-9C19B846FCD6}
	return { 0xd975e8de, 0x7373, 0x4560, { 0x90, 0xfb, 0x9c, 0x19, 0xb8, 0x46, 0xfc, 0xd6 } };
}

const char* Sound::FileExtension() const noexcept
{
	return "All supported audio formats(*.wav;*.wave;*.ogg)\0*.wav;*.wave;*.ogg\0"
			"Waveform Audio File Format(*.wav;*.wave)\0*.wav;*.wave\0"
			"Ogg Vorbis Compressed Audio Format(*.ogg)\0*.ogg\0"
			"All Files(*.*)\0*.*\0\0";
}

std::type_index Sound::InitializationService() const noexcept
{
	return typeid(AudioEngine);
}

Sound::~Sound()
{
	alDeleteBuffers( 1, &_bufferID);
}

E3DRSP_Sound E3DRSP_Sound_Create(E3DRSP_AudioEngine audio, const char* path)
{
	return new Sound(static_cast<AudioEngine*>(audio), path);
}

void E3DRSP_Sound_Destroy(E3DRSP_Sound audio)
{
	delete static_cast<Sound*>(audio);
}