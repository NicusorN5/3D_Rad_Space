#include "ShadowMapRenderer.hpp"
#include "../IGraphicsCommandList.hpp"
#include "../IShaderCompiler.hpp"
#include "../ShaderDesc.hpp"
#include "../Effect.hpp"
#include "../../Math/Rectangle.hpp"
#include "../../Math/Point.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;
using namespace Engine3DRadSpace::Math;

ShadowMapRenderer::ShadowMapRenderer(IGraphicsDevice* device) : IRenderer(device)
{
	auto resolution = _device->Resolution();
	unsigned int shadowMapWidth = static_cast<unsigned int>(resolution.X * ShadowMapSize);
	unsigned int shadowMapHeight = static_cast<unsigned int>(resolution.Y * ShadowMapSize);

	_shadowMap = _device->CreateDepthStencilBuffer(shadowMapWidth, shadowMapHeight);
	_createShadowStates();

	// Depth-only effect that transforms geometry into light clip space.
	ShaderDescFile vs("Data\\Shaders\\ShadowMapDepth.hlsl", "VS_Main", ShaderType::Vertex);
	ShaderDescFile ps("Data\\Shaders\\ShadowMapDepth.hlsl", "PS_Main", ShaderType::Fragment);
	std::array<ShaderDesc*, 2> depthDesc = { &vs, &ps };

	auto [depthEffect, result] = _device->ShaderCompiler()->CompileEffect(depthDesc);
	if (result.Succeded)
		_depthEffect = depthEffect;
}

void ShadowMapRenderer::_createShadowStates()
{
	// Rasterizer with depth bias to mitigate shadow acne.
	_shadowRasterizerState = _device->CreateRasterizerState(
		RasterizerFillMode::Solid,
		RasterizerCullMode::CullBack,
		false,                                          // frontCounterClockwise
		static_cast<int>(ShadowBias * 100000.0f),       // depthBias (scaled)
		0.0f,                                           // depthBiasClamp
		ShadowSlopeBias,                                // slopeScaledDepthBias
		true,                                           // depthClip
		false,                                          // scissor
		false,                                          // multisample
		false                                           // antialiasedLine
	);

	_shadowDepthState = _device->CreateDepthStencilState_DepthDefault();
}

Math::Matrix4x4 ShadowMapRenderer::ComputeLightViewMatrix(const Math::Vector3& lightDirection) const
{
	// Position the light behind the scene along the light direction, looking at the focus point.
	Vector3 dir = lightDirection;
	float len = std::sqrt(Vector3::Dot(dir, dir));
	if (len > 0.0001f) dir = dir * (1.0f / len);
	else dir = Vector3(0.0f, -1.0f, 0.0f);

	Vector3 lightPos = dir * -LightDistance;
	Vector3 target = Vector3::Zero();
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

	// Avoid a degenerate basis when the light points straight up/down.
	if (std::abs(Vector3::Dot(dir, up)) > 0.99f)
		up = Vector3(1.0f, 0.0f, 0.0f);

	return Math::Matrix4x4::CreateLookAtView(lightPos, target, up);
}

Math::Matrix4x4 ShadowMapRenderer::ComputeLightProjectionMatrix() const
{
	// Orthographic projection sized in world units (square) covering the scene focus area.
	// NOTE: the engine's CreateLookAtView yields NEGATIVE view-space Z for points in front of the
	// camera (matching CreatePerspectiveProjection). The stock CreateOrthographicProjection instead
	// assumes positive Z, which would push clip.z below 0 and get the geometry clipped (empty shadow
	// map). We therefore build the matrix with a negated Z scale so clip.z lands in [0,1] for
	// view-space Z in [-NearPlane, -FarPlane].
	float extent = OrthographicExtent;
	if (extent < 1.0f) extent = 1.0f;

	float w = 2.0f / extent;
	float h = 2.0f / extent;
	float invRange = 1.0f / (FarPlane - NearPlane);

	return Math::Matrix4x4(
		w, 0.0f, 0.0f, 0.0f,
		0.0f, h, 0.0f, 0.0f,
		0.0f, 0.0f, -invRange, 0.0f,
		0.0f, 0.0f, -NearPlane * invRange, 1.0f
	);
}

void ShadowMapRenderer::Begin()
{
	auto context = _device->ImmediateContext();

	auto resolution = _device->Resolution();
	unsigned int shadowMapWidth = static_cast<unsigned int>(resolution.X * ShadowMapSize);
	unsigned int shadowMapHeight = static_cast<unsigned int>(resolution.Y * ShadowMapSize);

	// Capture current states to restore them in End().
	_savedRasterizerState = _device->GetRasterizerState();
	_savedDepthState = _device->GetDepthStencilState();

	// Compute the light transform for this frame.
	_lightViewProj = ComputeLightViewMatrix(LightDirection) * ComputeLightProjectionMatrix();

	// Bind the shadow map as the depth-only render target.
	context->UnbindRenderTargetAndDepth();
	context->SetDepthStencilBuffer(_shadowMap.get());
	context->ClearDepthBuffer(_shadowMap.get());

	Viewport shadowViewport(
		Math::RectangleF(0.0f, 0.0f, static_cast<float>(shadowMapWidth), static_cast<float>(shadowMapHeight)),
		0.0f,
		1.0f
	);
	context->SetViewport(shadowViewport);

	context->SetRasterizerState(_shadowRasterizerState.get());
	context->SetDepthStencilState(_shadowDepthState.get(), 0);
}

void ShadowMapRenderer::DrawItem(const BatchedDraw& item)
{
	if (_depthEffect == nullptr || item.Vertices == nullptr || item.Indices == nullptr)
		return;

	// Transform geometry directly into light clip space: world * lightView * lightProj.
	Math::Matrix4x4 worldLightViewProj = item.World * _lightViewProj;
	_depthEffect->SetData(static_cast<void*>(&worldLightViewProj), sizeof(worldLightViewProj), 0, 0);
	_depthEffect->SetAll();

	auto cmd = _device->ImmediateContext();
	cmd->SetTopology(VertexTopology::TriangleList);
	cmd->DrawVertexBufferWithindices(item.Vertices, item.Indices);
}

void ShadowMapRenderer::End()
{
	auto context = _device->ImmediateContext();

	context->UnbindDepthBuffer();

	auto resolution = _device->Resolution();
	Viewport defaultViewport(
		Math::RectangleF(0.0f, 0.0f, static_cast<float>(resolution.X), static_cast<float>(resolution.Y)),
		0.0f,
		1.0f
	);
	context->SetViewport(defaultViewport);

	// Restore states captured in Begin() so subsequent passes are unaffected.
	if (_savedRasterizerState) context->SetRasterizerState(_savedRasterizerState.get());
	if (_savedDepthState) context->SetDepthStencilState(_savedDepthState.get(), 0);
}

IDepthStencilBuffer* ShadowMapRenderer::GetShadowMap() const noexcept
{
	return _shadowMap.get();
}

Math::Matrix4x4 ShadowMapRenderer::GetLightViewProj() const noexcept
{
	return _lightViewProj;
}
