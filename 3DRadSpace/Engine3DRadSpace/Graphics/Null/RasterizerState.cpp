#include "RasterizerState.hpp"
#include "GraphicsDevice.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Null;

RasterizerState::RasterizerState(
	GraphicsDevice *device,
	RasterizerFillMode filling,
	RasterizerCullMode culling,
	bool switchFrontBack,
	int depthBias,
	float depthBiasClamp,
	float slopeScaleDepthBias,
	bool depthClip,
	bool scissor,
	bool multisample,
	bool aaLine
)
{
	(void)device;
	(void)filling;
	(void)culling;
	(void)switchFrontBack;
	(void)depthBias;
	(void)depthBiasClamp;
	(void)slopeScaleDepthBias;
	(void)depthClip;
	(void)scissor;
	(void)multisample;
	(void)aaLine;
}

void* RasterizerState::GetHandle() const noexcept
{
	return nullptr;
}

IGraphicsDevice* RasterizerState::GetGraphicsDevice() const noexcept
{
	return nullptr;
}

RasterizerState RasterizerState::CullNone(GraphicsDevice *device)
{
	return RasterizerState(device);
}

RasterizerState RasterizerState::CullClockwise(GraphicsDevice * device)
{
	return RasterizerState(device);
}
RasterizerState RasterizerState::CullCounterClockwise(GraphicsDevice *device)
{
	return RasterizerState(device);
}

RasterizerState RasterizerState::Wireframe(GraphicsDevice *device)
{
	return RasterizerState(device);
}

std::unique_ptr<RasterizerState> GetCurrentRasterizerState(IGraphicsDevice* device)
{
	return std::make_unique<RasterizerState>(static_cast<GraphicsDevice*>(device));
}