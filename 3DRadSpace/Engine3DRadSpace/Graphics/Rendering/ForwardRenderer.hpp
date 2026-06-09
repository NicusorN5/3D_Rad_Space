#pragma once
#include "IRenderer.hpp"

namespace Engine3DRadSpace::Graphics
{
	class ISamplerState;
}

namespace Engine3DRadSpace::Graphics::Rendering
{
	class ShadowMapRenderer;

	/// <summary>
	/// A trivial forward renderer.
	/// </summary>
	class E3DRSP_GRAPHICS_RENDERING_EXPORT ForwardRenderer : public IRenderer
	{
		bool _beginCalled = false;

		// Optional shadow source: when set, the shadow map and light matrix are bound for lit materials.
		ShadowMapRenderer* _shadowPass = nullptr;
		std::unique_ptr<ISamplerState> _shadowSampler;
	public:
		/// <summary>
		/// Constructs a forward renderer pipeline.
		/// </summary>
		/// <param name="device"></param>
		ForwardRenderer(IGraphicsDevice* device);

		/// <summary>
		/// Sets the shadow pass whose shadow map and light view-projection are bound to lit materials.
		/// </summary>
		/// <param name="shadowPass">Shadow map renderer, or nullptr to disable shadows.</param>
		void SetShadowSource(ShadowMapRenderer* shadowPass) noexcept;

		/// <summary>
		/// Begins drawing.
		/// </summary>
		void Begin() override;
		/// <summary>
		/// Draws a single batched submission using its material effect and forward constants.
		/// </summary>
		/// <param name="item">Batched submission to draw.</param>
		void DrawItem(const BatchedDraw& item) override;
		/// <summary>
		/// Ends drawing.
		/// </summary>
		void End() override;

		~ForwardRenderer() override = default;
	};
}
