#pragma once
//#include "../GraphicsDevice.hpp"
#include "../Reflection/UUID.hpp"

#include "../Audio/AudioEngine.hpp"
#include "../Physics/PhysicsEngine.hpp"

namespace Engine3DRadSpace
{
	class GraphicsDevice;
	namespace Internal
	{
		struct AssetUUIDReader;
	}
}

namespace Engine3DRadSpace::Content
{
	class DLLEXPORT IAsset
	{
	protected:
		IAsset() = default;
	public:
		/// <summary>
		/// Represents a unique identifier for the asset type.
		/// </summary>
		/// <returns></returns>
		virtual Reflection::UUID GetUUID() const noexcept = 0;
		/// <summary>
		/// File extension used as a filter for the editor.
		/// </summary>
		/// <returns></returns>
		virtual const char* FileExtension() const noexcept = 0;

		virtual ~IAsset() = default;
	};

	template<typename T>
	concept AssetType = std::is_base_of_v<IAsset, T> &&
		(std::is_constructible_v<T, GraphicsDevice*, const std::filesystem::path&>) ||
		(std::is_constructible_v<T, Audio::AudioEngine*, const std::filesystem::path&>) ||
		(std::is_constructible_v<T, Physics::PhysicsEngine*, const std::filesystem::path&>);
}