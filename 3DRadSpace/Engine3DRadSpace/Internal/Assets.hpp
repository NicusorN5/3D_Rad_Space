#pragma once
#include "../Content/IAsset.hpp"

namespace Engine3DRadSpace::Internal
{
	typedef Content::IAsset* (*AssetCtor1)(GraphicsDevice* device, const std::filesystem::path& path);
	typedef Content::IAsset* (*AssetCtor2)(Physics::PhysicsEngine* device, const std::filesystem::path& path);
	typedef Content::IAsset* (*AssetCtor3)(Audio::AudioEngine* device, const std::filesystem::path& path);
	typedef Content::IAsset* (*AssetCtor4)(const std::filesystem::path& path);

	typedef std::variant<AssetCtor1, AssetCtor2, AssetCtor3, AssetCtor4> AssetCtor;

	inline std::vector<std::pair<Engine3DRadSpace::Reflection::UUID, Engine3DRadSpace::Internal::AssetCtor>> asset_types;

	void RegisterDefaultAssets();

	template<Content::AssetType T>
	bool RegisterAssetType()
	{
		using namespace Engine3DRadSpace::Audio;
		using namespace Engine3DRadSpace::Physics;
		using namespace Engine3DRadSpace::Content;
		using namespace Engine3DRadSpace::Internal;

		for (auto& [uuid, ctor] : asset_types)
		{
			if (uuid == AssetUUIDReader::GetUUID(Tag<T>()))
				return false;
		}

		if constexpr(ConstructibleFromGraphicsDevice<T>)
		{
			asset_types.emplace_back(AssetUUIDReader::GetUUID(Tag<T>()),
				[](GraphicsDevice* device, const std::filesystem::path& path) -> Content::IAsset*
				{
					return static_cast<IAsset*>(new T(device, path));
				}							  
			);
		}

		if constexpr(ConstructibleFromPhysicsEngine<T>)
		{
			asset_types.emplace_back(AssetUUIDReader::GetUUID(Tag<T>()),
				[](PhysicsEngine* physics, const std::filesystem::path& path) -> Content::IAsset*
				{
					return static_cast<IAsset*>(new T(physics, path));
				}							  
			);
		}

		if constexpr(ConstructibleFromAudioEngine<T>)
		{
			asset_types.emplace_back(AssetUUIDReader::GetUUID(Tag<T>()),
				[](AudioEngine* audio, const std::filesystem::path& path) -> Content::IAsset*
				{
					return static_cast<IAsset*>(new T(audio, path));
				}							  
			);
		}

		if constexpr(ConstructibleFromPath<T>)
		{
			asset_types.emplace_back(AssetUUIDReader::GetUUID(Tag<T>()),
				[](AudioEngine* audio, const std::filesystem::path& path) -> Content::IAsset*
				{
					return static_cast<IAsset*>(new T(path));
				}							  
			);
		}

		return true;
	}
}