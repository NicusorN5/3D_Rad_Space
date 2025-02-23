#pragma once
#include "PickingShader.hpp"
#include "..\..\Graphics\RenderTarget.hpp"
#include "..\..\IDrawable3D.hpp"
#include "..\..\Graphics\Model3D.hpp"
#include "..\..\Content\ShaderManager.hpp"
#include "..\..\Math\Point.hpp"
#include "../../Graphics/Rendering/IRenderer.hpp"

namespace Engine3DRadSpace::Algorithms::Picking
{
	/// <summary>
	/// Represents a render pass that draws object IDs into a texture. Used for mouse picking inside the editor.
	/// </summary>
	class DLLEXPORT PickingRenderTargetRender : public Graphics::Rendering::IRenderer
	{
		std::shared_ptr<PickingShader> _shader;
		std::unique_ptr<Graphics::RenderTarget> _renderTarget;

		bool _isDrawing = false;
	public:
		/// <summary>
		/// Instantiates the render pass.
		/// </summary>
		/// <param name="device">Device context</param>
		PickingRenderTargetRender(GraphicsDevice* device);

		/// <summary>
		/// Begins the pass.
		/// </summary>
		/// <remarks>
		/// This binds the render target containing IDs.
		/// </remarks>
		void Begin() override;

		/// <summary>
		/// Restores the default render target.
		/// </summary>
		void End() override;

		/// <summary>
		/// Picks an ID from the texture.
		/// </summary>
		/// <param name="mouseCoords">Window relative mouse coordinates.</param>
		/// <returns></returns>
		std::optional<unsigned> Pick(const Math::Point& mouseCoords);
	};
}

