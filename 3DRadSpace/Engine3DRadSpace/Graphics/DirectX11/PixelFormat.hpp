#pragma once
#include "../PixelFormat.hpp"
#include <dxgiformat.h>

namespace Engine3DRadSpace::Graphics::DirectX11
{
	DXGI_FORMAT PixelFormat_ToDX11(PixelFormat format);
	PixelFormat PixelFormat_FromDX11(DXGI_FORMAT format);
}