/// ------------------------------------------------------------------------------------------------
/// File:   Content/AssetTypeRegistration.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include "AssetTypeRegistration.hpp"
#include "../Graphics/Texture2D.hpp"
#include "../Graphics/Model3D.hpp"
#include "../Graphics/Font.hpp"
#include "../Tag.hpp"
#include "../Internal/AssetUUIDReader.hpp"
#include "../Audio/Sound.hpp"
#include "AssetFactory.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Internal;

IAsset* Engine3DRadSpace::Content::CreateAssetInstance(Reflection::UUID nuuid, AssetFactory* factory,const std::filesystem::path& path)
{
	if (Internal::assetTypes.empty())
	{
		RegisterAssetType<Graphics::Texture2D>();
		RegisterAssetType<Graphics::Model3D>();
		RegisterAssetType<Graphics::Font>();
		RegisterAssetType<Audio::Sound>();
	}
	if (factory == nullptr) return nullptr;
	
	for (auto& [uuid, ctor] : Internal::assetTypes)
	{
		if(uuid == nuuid)
		{
			switch(ctor.index())
			{
				case 0:
					return std::get<AssetCtor1>(ctor)(factory->Device(), path);
				case 1:
					return std::get<AssetCtor2>(ctor)(factory->Physics(), path);
				case 2:
					return std::get<AssetCtor3>(ctor)(factory->Audio(), path);
				default:
					std::unreachable();
			}
		}
	}
	return nullptr;
}