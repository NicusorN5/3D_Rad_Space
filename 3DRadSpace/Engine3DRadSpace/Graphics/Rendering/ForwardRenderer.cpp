#include "ForwardRenderer.hpp"
#include "ShadowMapRenderer.hpp"
#include "../Effect.hpp"
#include "../IGraphicsCommandList.hpp"
#include "../IDepthStencilBuffer.hpp"
#include "../IDepthStencilState.hpp"
#include "../IBlendState.hpp"
#include "../IRasterizerState.hpp"
#include "../ISamplerState.hpp"
#include "../../Math/Matrix4x4.hpp"

using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

ForwardRenderer::~ForwardRenderer() = default;

ForwardRenderer::ForwardRenderer(IGraphicsDevice* device):
	IRenderer(device)
{
	// Point sampling: each PCF tap must read a real shadow-map texel (linear filtering would
	// interpolate depth values, which is incorrect for the depth comparison).
	_shadowSampler = _device->CreateSamplerState_PointClamp();

	_depthState = _device->CreateDepthStencilState_DepthDefault();
	_blendState = _device->CreateBlendState_Opaque();
	_rasterState = _device->CreateRasterizerState_CullNone();
}

void ForwardRenderer::SetShadowSource(ShadowMapRenderer* shadowPass) noexcept
{
	_shadowPass = shadowPass;
}

void ForwardRenderer::Begin()
{
	if (_beginCalled) return;
	_beginCalled = true;

	auto cmd = _device->ImmediateContext();
	cmd->SetRenderTargetAndDepth(nullptr, nullptr);
	// Force a clean opaque pipeline state: depth test/write on, opaque blending, no culling.
	// Editor overlays and the 2D sprite batch leave alpha blending / odd states bound otherwise.
	cmd->SetDepthStencilState(_depthState.get(), 0);
	cmd->SetBlendState(_blendState.get());
	cmd->SetRasterizerState(_rasterState.get());
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
			float TexelU;
			float TexelV;
		} shadowData;

		auto resolution = _device->Resolution();
		float shadowW = resolution.X * _shadowPass->ShadowMapSize;
		float shadowH = resolution.Y * _shadowPass->ShadowMapSize;

		shadowData.LightViewProj = _shadowPass->GetLightViewProj();
		shadowData.ShadowBias = _shadowPass->ShadowBias;
		shadowData.ShadowIntensity = _shadowPass->ShadowIntensity;
		shadowData.TexelU = (shadowW > 0.0f) ? (1.0f / shadowW) : 0.0f;
		shadowData.TexelV = (shadowH > 0.0f) ? (1.0f / shadowH) : 0.0f;

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
