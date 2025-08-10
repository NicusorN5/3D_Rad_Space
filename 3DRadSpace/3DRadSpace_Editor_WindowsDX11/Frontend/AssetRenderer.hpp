#pragma once
#include <Engine3DRadSpace/Graphics/Model3D.hpp>
#include <Engine3DRadSpace/Graphics/Font.hpp>

template<typename T>
bool AssetRenderer(Engine3DRadSpace::Graphics::GraphicsDevice *device, const std::string &imagePath, T *assetPtr) = delete;

template<> bool AssetRenderer<Engine3DRadSpace::Graphics::Texture2D>(
	Engine3DRadSpace::Graphics::GraphicsDevice *device,
	const std::string &imagePath,
	Engine3DRadSpace::Graphics::Texture2D *texture
);

template<> bool AssetRenderer<Engine3DRadSpace::Graphics::Model3D>(
	Engine3DRadSpace::Graphics::GraphicsDevice * device,
	const std::string &imagePath,
	Engine3DRadSpace::Graphics::Model3D *model
);

template<> bool AssetRenderer<Engine3DRadSpace::Graphics::Font>(
	Engine3DRadSpace::Graphics::GraphicsDevice* device,
	const std::string& imagePath,
	Engine3DRadSpace::Graphics::Font* font
);