#pragma once

#include "../BufferUsage.hpp"
#include <d3d11.h>

//These functions are used internally by VertexBuffer, Texture2D, etc...

namespace Engine3DRadSpace::Graphics::DirectX11
{
	D3D11_USAGE BufferUsage_ToDirectX11(Engine3DRadSpace::Graphics::BufferUsage usage);
	UINT BufferUsage_ToDX11CPUFlag(Engine3DRadSpace::Graphics::BufferUsage usage);
}