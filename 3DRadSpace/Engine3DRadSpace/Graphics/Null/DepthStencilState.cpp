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

unsigned int DepthStencilState::StencilRef() const noexcept override
{
	return 0;
}
void* DepthStencilState::GetHandle() const noexcept override
{
	return nullptr;
}

static DepthStencilState DepthStencilState::DepthDefault(GraphicsDevice* device)
{
	return DepthStencilState(device);
}
static DepthStencilState DepthNone(GraphicsDevice *device)
{
	return DepthStencilState(device);
}

static DepthStencilState DepthRead(GraphicsDevice *device)
{
	return DepthStencilState(device);
}

static DepthStencilState DepthReverseZ(GraphicsDevice *device)
{
	return DepthStencilState(device);
}

static DepthStencilState DepthReadReverseZ(GraphicsDevice *device)
{
	return DepthStencilState(device);
}