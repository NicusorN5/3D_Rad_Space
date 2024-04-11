#pragma once
#include "../GraphicsDevice.hpp"
#include "../Reflection/UUID.hpp"

#include "../IGraphicsDevice.hpp"
#include "../Audio/AudioEngine.hpp"
#include "../Physics/PhysicsEngine.hpp"

namespace Engine3DRadSpace::Internal
{
	struct AssetUUIDReader;
}

namespace Engine3DRadSpace::Content
{
	class DLLEXPORT IAsset
	{
	protected:
		IAsset() = default;
	public:
		virtual Reflection::UUID GetUUID() = 0;
		virtual ~IAsset() = default;
	};

	template<typename T>
	concept AssetType = std::is_base_of_v<IAsset, T> &&
		(std::is_constructible_v<T, GraphicsDevice*, const std::filesystem::path&>) ||
		(std::is_constructible_v<T, Audio::AudioEngine*, const std::filesystem::path&>) ||
		(std::is_constructible_v<T, Physics::PhysicsEngine*, const std::filesystem::path&>);
}