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
		throw ServiceBadCastException<IGraphicsDevice>();
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
		
		std::array<ITexture2D, 6> cubeMap =
		{
			_device->CreateTexture2D(device, texturePaths[0]),
			_device->CreateTexture2D(device, texturePaths[1]),
			_device->CreateTexture2D(device, texturePaths[2]),
			_device->CreateTexture2D(device, texturePaths[3]),
			_device->CreateTexture2D(device, texturePaths[4]),
			_device->CreateTexture2D(device, texturePaths[5]),
		};

		return CubeMapSkybox(device, std::move(cubeMap));
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

SkyboxAsset::SkyboxAsset(Internal::AssetUUIDReader dummy) :
	_skybox(nullptr)
{
	(void)dummy;
}

SkyboxAsset::SkyboxAsset(IService *device, const std::filesystem::path& path) :
	_skybox(_loadCubeMap(dynamic_cast<IGraphicsDevice*>(device), path))
{
}

CubeMapSkybox& SkyboxAsset::GetSkybox() noexcept
{
	return _skybox;
}

CubeMapSkybox* SkyboxAsset::operator->() noexcept
{
	return &_skybox;
}

CubeMapSkybox& SkyboxAsset::operator() noexcept
{
	return *_skybox;
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
