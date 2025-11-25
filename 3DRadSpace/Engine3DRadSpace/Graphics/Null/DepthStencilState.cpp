#include "DepthStencilState.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Null;

DepthStencilState::DepthStencilState(GraphicsDevice *device)
{
}

DepthStencilState::DepthStencilState(
	GraphicsDevice *device, 
	bool EnableDepth,
	DepthWriteMask Mask, 
	ComparisonFunction Function,
	bool EnableStencil,
	uint8_t ReadMask,
	uint8_t WriteMask, 
	FaceOperation FrontFace,
	FaceOperation BackFace
)
{
}

unsigned int DepthStencilState::StencilRef() const noexcept
{
	return 0;
}
void* DepthStencilState::GetHandle() const noexcept
{
	return nullptr;
}

IGraphicsDevice* DepthStencilState::GetGraphicsDevice() const noexcept
{
	return nullptr;
}

DepthStencilState DepthStencilState::DepthDefault(GraphicsDevice* device)
{
	return DepthStencilState(device);
}

DepthStencilState DepthStencilState::DepthNone(GraphicsDevice *device)
{
	return DepthStencilState(device);
}

DepthStencilState DepthStencilState::DepthRead(GraphicsDevice *device)
{
	return DepthStencilState(device);
}

DepthStencilState DepthStencilState::DepthReverseZ(GraphicsDevice *device)
{
	return DepthStencilState(device);
}

DepthStencilState DepthStencilState::DepthReadReverseZ(GraphicsDevice *device)
{
	return DepthStencilState(device);
}