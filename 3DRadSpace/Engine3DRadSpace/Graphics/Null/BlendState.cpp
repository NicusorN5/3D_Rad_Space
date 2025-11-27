#include "BlendState.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Null;
using namespace Engine3DRadSpace::Math;

BlendState::BlendState(IGraphicsDevice* device)
{
}

BlendState::BlendState(IGraphicsDevice *device, bool alphaCoverage, bool indepedentBlend, const RenderTargetBlendState &renderTargetBlendState)
{
}

BlendState::BlendState(IGraphicsDevice *device, bool alphaCoverage, bool indepedentBlend, std::array<RenderTargetBlendState, 8> renderTargetBlendStates)
{
}

Math::Color BlendState::BlendFactor() const noexcept
{
	return Colors::Black;
}

unsigned int BlendState::SampleMask() const noexcept
{
	return 0x00;
}

void* BlendState::GetHandle() const noexcept
{
	return nullptr;
}

IGraphicsDevice* BlendState::GetGraphicsDevice() const noexcept
{
	return nullptr;
}

BlendState BlendState::Opaque(IGraphicsDevice *device)
{
	return BlendState(device);
}

BlendState BlendState::AlphaBlend(IGraphicsDevice *device)
{
	return BlendState(device);
}

BlendState BlendState::Additive(IGraphicsDevice *device)
{
	return BlendState(device);
}

BlendState BlendState::NonPremultiplied(IGraphicsDevice *device)
{
	return BlendState(device);
}

BlendState BlendState::GetCurrentBlendState(IGraphicsDevice* device)
{
	return BlendState(device);
}