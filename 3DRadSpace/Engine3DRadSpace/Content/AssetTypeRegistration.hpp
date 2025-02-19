#pragma once
#include "AssetFactory.hpp"
#include "../Internal/AssetUUIDReader.hpp"

namespace Engine3DRadSpace::Internal
{
	typedef Content::IAsset* (*AssetCtor1)(GraphicsDevice* device, const std::filesystem::path& path);
	typedef Content::IAsset* (*AssetCtor2)(Physics::PhysicsEngine* device, const std::filesystem::path& path);
	typedef Content::IAsset* (*AssetCtor3)(Audio::AudioEngine* device, const std::filesystem::path& path);

	typedef std::variant<AssetCtor1, AssetCtor2, AssetCtor3> AssetCtor;

	inline std::vector<std::pair<Engine3DRadSpace::Reflection::UUID, Engine3DRadSpace::Internal::AssetCtor>> assetTypes;
}

namespace Engine3DRadSpace::Content
{
	DLLEXPORT IAsset* CreateAssetInstance(const Reflection::UUID &uuid, AssetFactory* factory,const std::filesystem::path& path);

	template<AssetType T>
	bool RegisterAssetType()
	{
		using namespace Engine3DRadSpace::Audio;
		using namespace Engine3DRadSpace::Physics;

		for (auto& [uuid, ctor] : Internal::assetTypes)
		{
			if (uuid == Internal::AssetUUIDReader::GetUUID(Tag<T>()))
				return false;
		}

		if constexpr(ConstructibleFromGraphicsDevice<T>)
		{
			Internal::assetTypes.emplace_back(Internal::AssetUUIDReader::GetUUID(Tag<T>()),
				[](GraphicsDevice* device, const std::filesystem::path& path) -> Content::IAsset*
				{
					return static_cast<Content::IAsset*>(new T(device, path));
				}							  
			);
		}

		if constexpr(ConstructibleFromPhysicsEngine<T>)
		{
			Internal::assetTypes.emplace_back(Internal::AssetUUIDReader::GetUUID(Tag<T>()),
				[](PhysicsEngine* physics, const std::filesystem::path& path) -> Content::IAsset*
				{
					return static_cast<Content::IAsset*>(new T(physics, path));
				}							  
			);
		}

		if constexpr(ConstructibleFromAudioEngine<T>)
		{
			Internal::assetTypes.emplace_back(Internal::AssetUUIDReader::GetUUID(Tag<T>()),
				[](AudioEngine* audio, const std::filesystem::path& path) -> Content::IAsset*
				{
					return static_cast<Content::IAsset*>(new T(audio, path));
				}							  
			);
		}

		return true;
	}
}