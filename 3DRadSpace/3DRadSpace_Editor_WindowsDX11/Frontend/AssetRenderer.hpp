#pragma once
#include <Engine3DRadSpace/Content/Assets/ModelAsset.hpp>
#include <Engine3DRadSpace/Content/Assets/FontAsset.hpp>
#include <Engine3DRadSpace/Content/Assets/SkyboxAsset.hpp>
#include <Engine3DRadSpace/Content/Assets/TextureAsset.hpp>

template<typename T>
bool AssetRenderer(Engine3DRadSpace::Graphics::IGraphicsDevice *device, const std::string &imagePath, T *assetPtr) = delete;

template<> bool AssetRenderer<Engine3DRadSpace::Content::Assets::TextureAsset>(
	Engine3DRadSpace::Graphics::IGraphicsDevice *device,
	const std::string &imagePath,
	Engine3DRadSpace::Content::Assets::TextureAsset *texture
);

template<> bool AssetRenderer<Engine3DRadSpace::Content::Assets::ModelAsset>(
	Engine3DRadSpace::Graphics::IGraphicsDevice * device,
	const std::string &imagePath,
	Engine3DRadSpace::Content::Assets::ModelAsset *model
);

template<> bool AssetRenderer<Engine3DRadSpace::Content::Assets::FontAsset>(
	Engine3DRadSpace::Graphics::IGraphicsDevice* device,
	const std::string& imagePath,
	Engine3DRadSpace::Content::Assets::FontAsset* font
);

template<> bool AssetRenderer<Engine3DRadSpace::Content::Assets::SkyboxAsset>
(
	Engine3DRadSpace::Graphics::IGraphicsDevice* device,
	const std::string& imagePath,
	Engine3DRadSpace::Content::Assets::SkyboxAsset* path
);