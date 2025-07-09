#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Audio
{
	class Sound;
	class E3DRSP_AUDIO_EXPORT AudioBuffer
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

		enum class WAVLoadError
		{
			None,
			CannotOpen,
			RIFFNotFound,
			NoFormatMarker,
			WrongFormatLength,
			NotPCM,
			NullSize,
			OutOfMemory
		};

		static std::expected<AudioBuffer, WAVLoadError> FromWAV(const std::filesystem::path& path);
		
		enum class OGGLoadError
		{
			None,
			CannotOpen,
			Invalid,
			InfoFail,
			OutOfMemory,
		};
		
		static std::expected<AudioBuffer, OGGLoadError> FromOGG(const std::filesystem::path& path);

		~AudioBuffer() = default;

		friend class Sound;
	};
}