#include "ForwardRenderer.hpp"
#include "ShadowMapRenderer.hpp"
#include "../Effect.hpp"
#include "../IGraphicsCommandList.hpp"
#include "../IDepthStencilBuffer.hpp"
#include "../ISamplerState.hpp"
#include "../../Math/Matrix4x4.hpp"

using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

ForwardRenderer::ForwardRenderer(IGraphicsDevice* device):
	IRenderer(device)
{
	_shadowSampler = _device->CreateSamplerState_LinearClamp();
}

void ForwardRenderer::SetShadowSource(ShadowMapRenderer* shadowPass) noexcept
{
	_shadowPass = shadowPass;
}

void ForwardRenderer::Begin()
{
	if (_beginCalled) return;
	_beginCalled = true;

	_device->ImmediateContext()->SetRenderTargetAndDepth(nullptr, nullptr);
}

void ForwardRenderer::DrawItem(const BatchedDraw& item)
{
	if (item.Material == nullptr || item.Vertices == nullptr || item.Indices == nullptr)
		return;

	// Per-object forward constants (slot 0), captured at submit time.
	if (!item.ForwardConstants.empty())
	{
		item.Material->SetData(
			static_cast<void*>(const_cast<std::byte*>(item.ForwardConstants.data())),
			item.ForwardConstants.size(),
			0
		);
	}

	// Bind the shadow data (slot 1) and shadow map (t0/s0) for lit materials.
	// NOTE: only materials that declare the shadow cbuffer/texture should be submitted while this
	// is active. This is refined in a later increment when more object types are migrated.
	if (_shadowPass != nullptr && _shadowPass->GetShadowMap() != nullptr)
	{
		struct alignas(16) ShadowConstants
		{
			Math::Matrix4x4 LightViewProj;
			float ShadowBias;
			float ShadowIntensity;
			float Pad0;
			float Pad1;
		} shadowData;

		shadowData.LightViewProj = _shadowPass->GetLightViewProj();
		shadowData.ShadowBias = _shadowPass->ShadowBias;
		shadowData.ShadowIntensity = _shadowPass->ShadowIntensity;
		shadowData.Pad0 = 0.0f;
		shadowData.Pad1 = 0.0f;

		item.Material->SetData(static_cast<void*>(&shadowData), sizeof(shadowData), 1);
		item.Material->SetTexture(_shadowPass->GetShadowMap()->GetDepthTexture(), 0);
		if (_shadowSampler) item.Material->SetSampler(_shadowSampler.get(), 0);
	}

	item.Material->SetAll();

	auto cmd = _device->ImmediateContext();
	cmd->SetTopology(VertexTopology::TriangleList);
	cmd->DrawVertexBufferWithindices(item.Vertices, item.Indices);
}

void ForwardRenderer::End()
{
	_beginCalled = false;
}
