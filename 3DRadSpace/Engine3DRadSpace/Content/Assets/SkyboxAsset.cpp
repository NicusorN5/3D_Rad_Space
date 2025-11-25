#include "SkyboxAsset.hpp"
#include "../../Core/Logging/AssetLoadingError.hpp"
#include "../../Core/Logging/ServiceBadCastException.hpp"
#include "../../Core/AssetUUIDReader.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Content::Assets;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Reflection;

CubeMapSkybox SkyboxAsset::_loadCubeMap(Graphics::IGraphicsDevice* device, const std::filesystem::path& path)
{
	if (device == nullptr)
	{
		throw ServiceBadCastException(Tag<IGraphicsDevice>{});
	}

	if(!std::filesystem::exists(path))
	{
		throw AssetLoadingError(Tag<SkyboxAsset>{}, path, "File does not exist");
	}

	std::ifstream file(path);

	if(!file.is_open())
	{
		throw Logging::AssetLoadingError(Tag<SkyboxAsset>{}, path, "Failed to open file");
	}

	if(path.extension() == ".skybox")
	{
		std::array<std::filesystem::path, 6> texturePaths;

		for(int i = 0; i < 6; ++i)
		{
			std::string texturePath;
			std::getline(file, texturePath);

			texturePaths[i] = std::filesystem::path(path).remove_filename().append(texturePath);
		}
		
		std::array<ITexture2D*, 6> cubeMap =
		{
			device->CreateTexture2D(texturePaths[0]).release(),
			device->CreateTexture2D(texturePaths[1]).release(),
			device->CreateTexture2D(texturePaths[2]).release(),
			device->CreateTexture2D(texturePaths[3]).release(),
			device->CreateTexture2D(texturePaths[4]).release(),
			device->CreateTexture2D(texturePaths[5]).release(),
		};

		return CubeMapSkybox(device, cubeMap);
	}
	else if(path.extension() == ".dds")
	{
		//TODO: Implement DDS loading
		throw AssetLoadingError(Tag<SkyboxAsset>{}, path, "DDS loading not implemented");
	}
	else
	{
		throw AssetLoadingError(Tag<SkyboxAsset>{}, path, "Unsupported file format");
	}
}

SkyboxAsset::SkyboxAsset(Internal::AssetUUIDReader dummy)
{
	(void)dummy;
}

SkyboxAsset::SkyboxAsset(IService *device, const std::filesystem::path& path) :
	IAssetWrapper(std::move(_loadCubeMap(dynamic_cast<IGraphicsDevice*>(device), path)))
{
}

Reflection::UUID SkyboxAsset::GetUUID() const noexcept
{
	// {9B7A328E-9B10-4FFC-9E3B-0A79214BB6CA}
	return { 0x9b7a328e, 0x9b10, 0x4ffc, { 0x9e, 0x3b, 0xa, 0x79, 0x21, 0x4b, 0xb6, 0xca } };
}

const char* SkyboxAsset::FileExtension() const noexcept
{
	return "Skybox file(*.skybox)\0*.skybox\0"
			"Direct Draw Surface(*.dds)\0*.dds\0"
			"All Files(*.*)\0*.*\0\0";
}

std::type_index Engine3DRadSpace::Content::Assets::SkyboxAsset::InitializationService() const noexcept
{
	return typeid(IGraphicsDevice);
}