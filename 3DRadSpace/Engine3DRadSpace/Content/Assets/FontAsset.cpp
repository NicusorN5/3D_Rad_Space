#include "FontAsset.hpp"
#include "../../Graphics/Font.hpp"
#include "../../Core/AssetUUIDReader.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Content::Assets;
using namespace Engine3DRadSpace::Graphics;

FontAsset::FontAsset(IService* device, const std::filesystem::path & path) :
	IAssetWrapper(std::move(Font(static_cast<IGraphicsDevice*>(device), path)))
{
}

FontAsset::FontAsset(Internal::AssetUUIDReader dummy)
{
	(void)dummy;
}

Reflection::UUID FontAsset::GetUUID() const noexcept
{
	// {7A9DEE1F-A3DE-4E55-B4D8-EC1BFE173B86}
	return {0x7a9dee1f, 0xa3de, 0x4e55, { 0xb4, 0xd8, 0xec, 0x1b, 0xfe, 0x17, 0x3b, 0x86 }};
}

const char* FontAsset::FileExtension() const noexcept
{
	return "TrueType Font (*.ttf)\0*.ttf\0All Files(*.*)\0*.*\0\0";
}

std::type_index FontAsset::InitializationService() const noexcept
{
	return typeid(IGraphicsDevice);
}