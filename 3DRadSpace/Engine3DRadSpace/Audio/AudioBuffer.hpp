/// ------------------------------------------------------------------------------------------------
/// File:   Audio/AudioBuffer.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace::Audio
{
	class Sound;
	class AudioBuffer
	{
	protected:
		std::unique_ptr<char[]> _buffer;
		int _channel = 0;
		int _sampleRate = 0;
		int _bps = 0;
		int _format = 0;
		int _size = 0;
	public:
		//AudioBuffer() = default;
		AudioBuffer(char* buffer, int numChannels, int sampleRate, int bps, int format, int size);

		AudioBuffer(const AudioBuffer&) = delete;
		AudioBuffer(AudioBuffer&&) = default;

		AudioBuffer& operator=(const AudioBuffer&) = delete;
		AudioBuffer& operator=(AudioBuffer&&) = default;

		static std::optional<AudioBuffer> FromWAV(const std::filesystem::path& path);

		~AudioBuffer() = default;

		friend class Sound;
	};
}