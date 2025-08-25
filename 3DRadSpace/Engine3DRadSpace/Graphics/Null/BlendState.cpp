#include "BlendState.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Null;
using namespace Engine3DRadSpace::Math;

BlendState::BlendState(GraphicsDevice* device)
{
}

BlendState::BlendState(GraphicsDevice *device, bool alphaCoverage, bool indepedentBlend, const RenderTargetBlendState &renderTargetBlendState)
{
}

BlendState::BlendState(GraphicsDevice *device, bool alphaCoverage, bool indepedentBlend, std::array<RenderTargetBlendState, 8> renderTargetBlendStates)
{
}

Math::Color BlendState::BlendFactor() const noexcept override
{
	return Colors::Black;
}
unsigned int BlendState::SampleMask() const noexcept override
{
	return 0x00;
}

void* BlendState::GetHandle() const noexcept override
{
	return nullptr;
}

virtual IGraphicsDevice* BlendState::GetGraphicsDevice() const noexcept override
{
	return nullptr;
}

BlendState BlendState::Opaque(GraphicsDevice *device)
{
	return BlendState(device);
}

BlendState BlendState::AlphaBlend(GraphicsDevice *device)
{
	return BlendState(device);
}

BlendState BlendState::Additive(GraphicsDevice *device)
{
	return BlendState(device);
}

BlendState BlendState::NonPremultiplied(GraphicsDevice *device)
{
	return BlendState(device);
}

BlendState BlendState::GetCurrentBlendState(GraphicsDevice* device)
{
	return BlendState(device);
}