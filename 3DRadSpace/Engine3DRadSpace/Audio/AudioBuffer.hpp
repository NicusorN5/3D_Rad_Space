#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Audio
{
	class Sound;

	/// <summary>
	/// Represents a PCM audio buffer.
	/// </summary>
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
		/// <summary>
		/// Constructs a AudioBuffer from specified arguments.
		/// </summary>
		/// <param name="buffer">PCM buffer</param>
		/// <param name="numChannels">Number of channels</param>
		/// <param name="sampleRate">Audio sample rate</param>
		/// <param name="bps">Beats per second</param>
		/// <param name="format">OpenAL format</param>
		/// <param name="size">Buffer size</param>
		AudioBuffer(char* buffer, int numChannels, int sampleRate, int bps, int format, int size);

		AudioBuffer(const AudioBuffer&) = delete;
		AudioBuffer(AudioBuffer&&) noexcept = default;

		AudioBuffer& operator=(const AudioBuffer&) = delete;
		AudioBuffer& operator=(AudioBuffer&&) noexcept = default;

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