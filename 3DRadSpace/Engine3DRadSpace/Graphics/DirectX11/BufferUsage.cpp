#include "BufferUsage.hpp"

using namespace Engine3DRadSpace::Graphics;

D3D11_USAGE Engine3DRadSpace::Graphics::DirectX11::BufferUsage_ToDirectX11(BufferUsage usage)
{
	switch (usage)
	{
	case BufferUsage::ReadWriteGPU: return D3D11_USAGE_DEFAULT;
	case BufferUsage::ReadOnlyGPU: return D3D11_USAGE_IMMUTABLE;
	case BufferUsage::ReadOnlyGPU_WriteOnlyCPU: return D3D11_USAGE_DYNAMIC;
	case BufferUsage::Staging: return D3D11_USAGE_STAGING;
	default: return D3D11_USAGE_DEFAULT;
	}
}

UINT Engine3DRadSpace::Graphics::DirectX11::BufferUsage_ToDX11CPUFlag(BufferUsage usage)
{
	switch (usage)
	{
	case BufferUsage::ReadOnlyGPU_WriteOnlyCPU: return D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	case BufferUsage::Staging: return D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ;
	default: return 0;
	}
}