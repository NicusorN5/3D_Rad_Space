#pragma once
#include "../Reflection/UUID.hpp"

#include "../Audio/AudioEngine.hpp"
#include "../Physics/PhysicsEngine.hpp"

namespace Engine3DRadSpace
{
	namespace Graphics
	{
		class GraphicsDevice;
	}
	namespace Internal
	{
		struct AssetUUIDReader;
	}
}

namespace Engine3DRadSpace::Content
{
	/// <summary>
	/// Asset base type.
	/// </summary>
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
	concept ConstructibleFromGraphicsDevice = std::is_constructible_v<T, Graphics::GraphicsDevice*, const std::filesystem::path&>;

	template<typename T>
	concept ConstructibleFromAudioEngine = std::is_constructible_v<T, Audio::AudioEngine*, const std::filesystem::path&>;

	template<typename T>
	concept ConstructibleFromPhysicsEngine = std::is_constructible_v<T, Physics::PhysicsEngine*, const std::filesystem::path&>;

	template<typename T>
	concept ConstructibleFromPath = std::is_constructible_v<T, const std::filesystem::path&>;

	template<typename T>
	concept AssetType = std::is_base_of_v<IAsset, T> &&
		( ConstructibleFromGraphicsDevice<T> ||
		ConstructibleFromAudioEngine<T> ||
		ConstructibleFromPhysicsEngine<T> ||
		ConstructibleFromPath<T>);
}