#include "SamplerState.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Null;

SamplerState::SamplerState(GraphicsDevice* device)
{
	(void)device;
}

SamplerState::SamplerState(
	GraphicsDevice* device,
	TextureFilter Filter,
	TextureAddressMode AddressU,
	TextureAddressMode AddressV,
	TextureAddressMode AddressW,
	float MipLODBias,
	unsigned MaxAnisotropy,
	ComparisonFunction ComparisionFunction,
	Math::Color BorderColor,
	float MinLOD,
	float MaxLOD
)
{
	(void)device;
	(void)Filter;
	(void)AddressU;
	(void)AddressV;
	(void)AddressW;
	(void)MipLODBias;
	(void)MaxAnisotropy;
	(void)ComparisionFunction;
	(void)BorderColor;
	(void)MinLOD;
	(void)MaxLOD;
}

SamplerState SamplerState::LinearClamp(GraphicsDevice* device)
{
	return SamplerState(device);
}

SamplerState SamplerState::LinearWrap(GraphicsDevice* device)
{
	return SamplerState(device);
}

SamplerState SamplerState::PointClamp(GraphicsDevice* device)
{
	return SamplerState(device);
}

SamplerState SamplerState::PointWrap(GraphicsDevice* device)
{
	return SamplerState(device);
}

SamplerState SamplerState::AnisotropicClamp(GraphicsDevice* device)
{
	return SamplerState(device);
}

SamplerState SamplerState::AnisotropicWrap(GraphicsDevice* device)
{
	return SamplerState(device);
}

const void* SamplerState::GetHandle() const noexcept
{
	return nullptr;
}