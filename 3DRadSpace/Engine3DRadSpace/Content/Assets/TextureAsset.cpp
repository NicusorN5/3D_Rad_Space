#include "TextureAsset.hpp"
#include "../../Graphics/DirectX11/Texture2D.hpp"
#include "../../Graphics/DirectX11/GraphicsDevice.hpp"
#include "../../Graphics/Null/Texture2D.hpp"
#include "../../Graphics/Null/GraphicsDevice.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Content::Assets;
using namespace Engine3DRadSpace::Graphics;

TextureAsset::TextureAsset(IGraphicsDevice *device, const std::filesystem::path &path) :
	_texture(device->CreateTexture(path))
{
}

Reflection::UUID TextureAsset::GetUUID() const noexcept
{
	// {5AAE5C7A-C0E7-405A-B6FD-03CF9E3E36CC}
	return {0x5aae5c7a, 0xc0e7, 0x405a, { 0xb6, 0xfd, 0x3, 0xcf, 0x9e, 0x3e, 0x36, 0xcc }};
}

const char* TextureAsset::FileExtension() const noexcept
{
	//Image formats supported by Texture2D::Texture2D, with support from DirectXTK.
	return  "Supported image formats (*.bmp;*.dib;.*jpg;*.jpeg;*.gif;*.tiff;*.tif;*.png;*.dds)\0*.bmp;*.jpg;*.jpeg;*.gif;*.tiff;*.tif;*.png;*.dds)\0"
		"Bitmap image(*.bmp;*.dib)\0*.bmp;*.dib\0"
		"Joint Photographic Experts Group (JPEG) image(*.jpg;*.jpeg)\0*.jpg;*.jpeg\0"
		"Graphics Interchange Format (GIF) image(*.gif)\0*.gif\0"
		"Tagged Image File Format (TIFF) image(*.tiff)\0*.tiff\0"
		"Portable Network Graphics (PNG) image(*.png)\0*.png\0"
		"DirectDraw Surface image(*.dds)\0*.dds\0"
		"All Files(*.*)\0*.*\0\0";
}
