#pragma once
#include "IRenderer.hpp"
#include "../IDepthStencilBuffer.hpp"
#include "../IRasterizerState.hpp"
#include "../IDepthStencilState.hpp"
#include "../Viewport.hpp"
#include "../../Math/Matrix4x4.hpp"
#include "../../Math/Vector3.hpp"

namespace Engine3DRadSpace::Graphics
{
	class Effect;
}

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Renders scene geometry from the light's point of view into a depth-only shadow map.
	/// The resulting depth texture and light view-projection matrix are consumed by the forward
	/// pass to apply per-pixel shadows.
	/// </summary>
	class E3DRSP_GRAPHICS_RENDERING_EXPORT ShadowMapRenderer : public IRenderer
	{
		std::unique_ptr<IDepthStencilBuffer> _shadowMap;
		std::unique_ptr<IRasterizerState> _shadowRasterizerState;
		std::unique_ptr<IDepthStencilState> _shadowDepthState;
		Effect* _depthEffect = nullptr;

		// State captured at Begin() and restored at End() so the following passes are unaffected.
		std::unique_ptr<IRasterizerState> _savedRasterizerState;
		std::unique_ptr<IDepthStencilState> _savedDepthState;

		Math::Matrix4x4 _lightViewProj;

		void _createShadowStates();
	public:
		ShadowMapRenderer(IGraphicsDevice* device);

		/// <summary>
		/// Size of the shadow map as a multiplier of the screen resolution.
		/// </summary>
		float ShadowMapSize = 1.0f;

		// Depth-comparison bias, in shadow-map depth units. With a linear orthographic projection the
		// world-space bias equals ShadowBias * (FarPlane - NearPlane), so this must be small to avoid
		// "peter-panning" (the shadow detaching from the caster near contact).
		float ShadowBias = 0.0004f;
		float ShadowSlopeBias = 0.01f;

		/// <summary>
		/// Shadow intensity (0.0 = fully dark, 1.0 = no shadow). Consumed by the forward pass.
		/// </summary>
		float ShadowIntensity = 0.3f;

		/// <summary>
		/// Half-extent (world units) of the square orthographic light frustum.
		/// </summary>
		float OrthographicExtent = 40.0f;
		float NearPlane = 0.1f;
		// Kept reasonably tight so the linear depth range (and thus the world-space shadow bias)
		// stays small for crisp contact shadows.
		float FarPlane = 250.0f;
		/// <summary>
		/// Distance the light is positioned away from the focus point along the light direction.
		/// </summary>
		float LightDistance = 100.0f;

		/// <summary>
		/// Direction the light points towards. Set before Begin() (synced from RenderingManager::MainLight).
		/// </summary>
		Math::Vector3 LightDirection = Math::Vector3(0.0f, -1.0f, 0.0f);

		/// <summary>
		/// Gets the shadow map depth texture buffer.
		/// </summary>
		IDepthStencilBuffer* GetShadowMap() const noexcept;

		/// <summary>
		/// Gets the light view-projection matrix computed during the last Begin().
		/// </summary>
		Math::Matrix4x4 GetLightViewProj() const noexcept;

		/// <summary>
		/// Computes the light view matrix from the light direction.
		/// </summary>
		Math::Matrix4x4 ComputeLightViewMatrix(const Math::Vector3& lightDirection) const;

		/// <summary>
		/// Computes the orthographic light projection matrix.
		/// </summary>
		Math::Matrix4x4 ComputeLightProjectionMatrix() const;

		void Begin() override;
		void DrawItem(const BatchedDraw& item) override;
		void End() override;

		~ShadowMapRenderer() override = default;
	};
}
